// See SetupX_Template.h for all options available

#define ILI9488_DRIVER

//https://item.taobao.com/item.htm?spm=a1z09.2.0.0.60cd2e8dimnYTj&id=579565847719&_u=sn0i24c0d77
//这家的ILI9488，需要增加反色处理，景园电子的不需要

#define TFT_INVERSION_OFF //关闭反色
//#define TFT_INVERSION_ON //打开反色

#define TFT_RGB_ORDER TFT_BGR

/*不要用4线SPI模式，刷新率犹如放PPT*/
//#define TFT_MISO 19
//#define TFT_MOSI 23
//#define TFT_SCLK 18
//#define TFT_CS   5  // Chip select control pin
//#define TFT_DC    27  // Data Command control pin
//#define TFT_RST   26 // Reset pin (could connect to RST pin)


//使用8位并行接口
#define TFT_PARALLEL_8_BIT
#define TFT_CS   33  // Chip select control pin (library pulls permanently low
#define TFT_DC   15  // Data Command control pin - must use a pin in the range 0-31
#define TFT_RST  32  // Reset pin, toggles on startup

#define TFT_WR    4  // Write strobe control pin - must use a pin in the range 0-31
#define TFT_RD    2  // Read strobe control pin

#define TFT_D0   12  // Must use pins in the range 0-31 for the data bus
#define TFT_D1   13  // so a single register write sets/clears all bits.
#define TFT_D2   26  // Pins can be randomly assigned, this does not affect
#define TFT_D3   25  // TFT screen update performance.
#define TFT_D4   17
#define TFT_D5   16
#define TFT_D6   27
#define TFT_D7   14

//#define TOUCH_CS   21

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT


// #define SPI_FREQUENCY  20000000
// #define SPI_FREQUENCY  8000000
// #define SPI_FREQUENCY  40000000
// #define SPI_FREQUENCY  80000000

// Optional reduced SPI frequency for reading TFT
#define SPI_READ_FREQUENCY  16000000

#define SPI_TOUCH_FREQUENCY  2500000
