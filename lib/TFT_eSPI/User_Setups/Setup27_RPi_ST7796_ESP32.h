//                            USER DEFINED SETTINGS
//   Set driver type, fonts to be loaded, pins used and SPI control method etc
//
//   See the User_Setup_Select.h file if you wish to be able to define multiple
//   setups and then easily select which setup file is used by the compiler.
//
//   If this file is edited correctly then all the library example sketches should
//   run without the need to make any more changes for a particular hardware setup!

// ##################################################################################
//
// Section 0. Call up the right driver file and any options for it
//
// ##################################################################################

// Display type -  only define if RPi display
//#define RPI_DISPLAY_TYPE

// Only define one driver
#define ST7796_DRIVER

//#define TFT_INVERSION_OFF //关闭反色
#define TFT_INVERSION_ON //打开反色
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

// ##################################################################################
//
// Section 1. Define the pins that are used to interface with the display here
//
// ##################################################################################

// >>>>> EDIT THE PIN NUMBERS IN THE LINES FOLLOWING TO SUIT YOUR ESP32 SETUP   <<<<<

// The ESP32 hardware SPI can be mapped to any pins, these are the recommended default
/*
#define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   15   // Chip select control pin
#define TFT_DC    2   // Data Command control pin
#define TFT_RST   4   // Reset pin (could connect to RST pin)
//#define TFT_RST  -1 // Set TFT_RST to -1 if display RESET is connected to ESP32 board RST

#define TOUCH_CS 22     // Chip select pin (T_CS) of touch screen
*/
// ##################################################################################
//
// Section 2. Not used for ESP32
//
// ##################################################################################


// ##################################################################################
//
// Section 3. Define the fonts that are to be used here
//
// ##################################################################################

// Comment out the #defines below with // to stop that font being loaded
// The ESP8366 and ESP32 have plenty of memory so commenting out fonts is not
// normally necessary. If all fonts are loaded the extra FLASH space required is
// about 17Kbytes. To save FLASH space only enable the fonts you need!

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
//#define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

// Comment out the #define below to stop the SPIFFS filing system and smooth font code being loaded
// this will save ~20kbytes of FLASH
#define SMOOTH_FONT

// ##################################################################################
//
// Section 4. Not used
//
// ##################################################################################


// ##################################################################################
//
// Section 5. Other options
//
// ##################################################################################

// Define the SPI clock frequency, this affects the graphics rendering speed. Too
// fast and the TFT driver will not keep up and display corruption appears.
// With an RPi ST7796 MH4.0 display 80MHz is OK for ESP32, 40MHz maximum for ESP8266

// #define SPI_FREQUENCY  20000000
// #define SPI_FREQUENCY  40000000
   #define SPI_FREQUENCY  80000000

// The ESP32 has 2 free SPI ports i.e. VSPI and HSPI, the VSPI is the default.
// If the VSPI port is in use and pins are not accessible (e.g. TTGO T-Beam)
// then uncomment the following line:
//#define USE_HSPI_PORT

// The XPT2046 requires a lower SPI clock rate of 2.5MHz so we define that here:
   #define SPI_TOUCH_FREQUENCY  2500000
