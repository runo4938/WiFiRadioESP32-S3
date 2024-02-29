esp32-wroom-s3 n16r8
pcm5102

Audio audio;
#define I2S_DOUT 16 // 27 // 18 // DIN connection
#define I2S_BCLK 17 // // Bit clock
#define I2S_LRC 18  //  // Left Right Clock

st7789  User_Setup.h
#define ST7789_DRIVER
#define TFT_CS 10   // or 34 (FSPI CS0)
#define TFT_MOSI 11 // or 35 (FSPI D)
#define TFT_SCLK 12 // or 36 (FSPI CLK)
#define TFT_MISO 13 // or 37 (FSPI Q)
#define TFT_BL 5
// Use pins in range 0-31
#define TFT_DC 7
#define TFT_RST 6
#define SPI_FREQUENCY 40000000

KY-040 EM-407 5В
#define CLK 4 // 35 //
#define DT 3  //  //
#define SW 8  //  //

