#!/bin/sh
set -e

# 1. 定义版本与基础路径
REALM_VERSION="v2.9.6"
INSTALL_DIR="/usr/local/bin"
CONFIG_PATH="/root/config.toml"

echo "====== 开始安装 realm ======"

# 2. 识别系统发行版与初始化系统类型
INIT_SYS="unknown"
if [ -d /run/systemd/system ] || [ "$(readlink -f /sbin/init 2>/dev/null)" = "/lib/systemd/systemd" ]; then
    INIT_SYS="systemd"
elif [ -f /sbin/openrc-run ] || command -v rc-service >/dev/null 2>&1; then
    INIT_SYS="openrc"
else
    echo "❌ 错误: 未检测到支持的初始化系统 (仅支持 systemd 或 openrc)"
    exit 1
fi
echo "⚙️ 检测到系统初始化管理器为: ${INIT_SYS}"

# 3. 安装必备依赖 (wget, tar, ca-certificates)
if [ "${INIT_SYS}" = "systemd" ] && command -v apt-get >/dev/null 2>&1; then
    if ! command -v wget >/dev/null 2>&1 || ! command -v tar >/dev/null 2>&1; then
        echo "正在安装基础依赖 (wget, tar, ca-certificates)..."
        apt-get update -qq && apt-get install -y -qq wget tar ca-certificates >/dev/null 2>&1
    fi
elif [ "${INIT_SYS}" = "openrc" ] && command -v apk >/dev/null 2>&1; then
    if ! command -v wget >/dev/null 2>&1 || ! command -v tar >/dev/null 2>&1; then
        echo "正在安装基础依赖 (wget, tar, ca-certificates)..."
        apk add --no-cache wget tar ca-certificates >/dev/null 2>&1
    fi
fi

# 4. 自动判断 CPU 架构并组合下载链接
ARCH=$(uname -m)
case "$ARCH" in
    x86_64)
        REALM_ARCH="x86_64"
        ;;
    aarch64)
        REALM_ARCH="aarch64"
        ;;
    *)
        echo "❌ 错误: 暂不支持当前的系统架构: $ARCH"
        exit 1
        ;;
esac

DOWNLOAD_URL="https://github.com/zhboner/realm/releases/download/${REALM_VERSION}/realm-slim-${REALM_ARCH}-unknown-linux-musl.tar.gz"
echo "🌐 检测到 CPU 架构为: ${ARCH}，使用 musl 静态版本: ${REALM_ARCH}"

# 5. 停止旧服务并清理旧文件
echo "正在清理可能存在的旧版本..."
if [ "${INIT_SYS}" = "systemd" ]; then
    systemctl stop realm >/dev/null 2>&1 || true
elif [ "${INIT_SYS}" = "openrc" ]; then
    rc-service realm stop >/dev/null 2>&1 || true
fi

mkdir -p "${INSTALL_DIR}"
rm -f "${INSTALL_DIR}/realm"
rm -f /tmp/realm-slim /tmp/realm-slim.tar.gz

# 6. 下载并解压 realm
echo "正在下载 realm (${REALM_VERSION})..."
wget -O /tmp/realm-slim.tar.gz "${DOWNLOAD_URL}"

echo "正在解压并安装..."
tar -xzf /tmp/realm-slim.tar.gz -C /tmp/
mv /tmp/realm-slim "${INSTALL_DIR}/realm"
chmod +x "${INSTALL_DIR}/realm"
rm -f /tmp/realm-slim.tar.gz

# 7. 检查配置文件
if [ ! -f "${CONFIG_PATH}" ]; then
    echo "⚠️ 未在 ${CONFIG_PATH} 发现配置文件，正在创建默认配置..."
    cat <<EOF > "${CONFIG_PATH}"
# realm 配置文件示例
[network]
zero_copy = true
fast_open = true

[[endpoints]]
listen = "0.0.0.0:10000"
remote = "8.8.8.8:53"
EOF
else
    echo "✅ 已找到配置文件: ${CONFIG_PATH}"
fi

# 8. 根据初始化系统配置服务文件与自启
if [ "${INIT_SYS}" = "systemd" ]; then
    echo "正在生成 systemd 服务 (/etc/systemd/system/realm.service)..."
    cat << 'EOF' > /etc/systemd/system/realm.service
[Unit]
Description=Realm High-Performance Relay Service
After=network.target

[Service]
Type=simple
User=root
ExecStart=/usr/local/bin/realm -c /root/config.toml
Restart=always
RestartSec=5
LimitNOFILE=1048576

[Install]
WantedBy=multi-user.target
EOF

    systemctl daemon-reload
    systemctl enable realm >/dev/null 2>&1 || true
    echo "正在重启 realm 服务..."
    systemctl restart realm
    echo "====== realm 安装并配置完成 ======"
    systemctl status realm --no-pager

elif [ "${INIT_SYS}" = "openrc" ]; then
    echo "正在生成 OpenRC 服务 (/etc/init.d/realm)..."
    cat << 'EOF' > /etc/init.d/realm
#!/sbin/openrc-run

description="Realm port forwarding service"
command="/usr/local/bin/realm"
command_args="-c /root/config.toml"
command_background="yes"
pidfile="/run/${RC_SVCNAME}.pid"
output_log="/var/log/realm.log"
error_log="/var/log/realm.err"
rc_ulimit="-n 1048576"

depend() {
    need net
    after firewall
}
EOF

    chmod +x /etc/init.d/realm
    echo "正在设置开机自启..."
    rc-update add realm default >/dev/null 2>&1 || true
    echo "正在重启 realm 服务..."
    rc-service realm restart
    echo "====== realm 安装并配置完成 ======"
    rc-service realm status
fi
