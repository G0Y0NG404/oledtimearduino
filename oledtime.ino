// How to connect the DS1302 and OLED.
// DS1302:           CE pin      -> Arduino Digital A0  :also called rst
//                   I/O pin     -> Arduino Digital A1  :also called dat
//                   SCLK pin    -> Arduino Digital A2  :also called clk
//                   GND pin     -> Arduino GND
// OLED:             SCL pin     -> Arduino SCL
//                   SDA pin     -> Arduino SDA
//                   VCC pin     -> Arduino 5V
//                   GND pin     -> Arduino GND

#include <DS1302.h>
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0); // I2C / TWI

// Init the DS1302
DS1302 rtc(A0, A1, A2);

void setup()
{
  Serial.begin(9600);
  
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

  // The following lines are initially needed to set the time but should be commented out
  // and reuploaded to use the values already stored in the DS1302
  rtc.setDOW(TUESDAY);      // Set Day-of-Week to FRIDAY
  rtc.setTime(15, 56, 0);   // Set the time to 12:00:00 (24hr format)
  rtc.setDate(12, 9, 2023); // Set the date to August 6th, 2019 
}

void loop()
{
  u8g.firstPage();
  do {
    draw();
  } while( u8g.nextPage() );

  // rebuild the picture after some delay
  delay(50);
}

void draw(void) {
  
  u8g.setFont(u8g_font_courB14r);  //change the font see notes
  u8g.setFontPosTop();  //reference position for a text
  u8g.drawStr( 0, 0, rtc.getTimeStr());//changing the two numbers adjusts the position of the words
  u8g.drawStr( 0, 22, rtc.getDOWStr());
  u8g.drawStr( 0, 44,rtc.getDateStr());
  
} 
