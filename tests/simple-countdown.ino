#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// TODO: later add stop button -> clicked twice resets counter (quits)
// int button_state = HIGH;
// const int PIN_BUTTON_STOP = 2;

// vars to store one session time (without the break)
byte minutes = 1; // 35 - 40
byte seconds = 15; // 00
char time_string[9];

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(void) 
{
  u8g2.setFont(u8g2_font_maniac_tf);
  u8g2.begin();
}

bool time_left = true;
void loop(void) 
{
  if (time_left)
  {
    if (seconds == 0)
    {
      if (minutes > 0)
      { 
        minutes--; 
        seconds = 59;
      }
      else 
      {
        seconds = 0;
      }
    }
    if (minutes == 0 && seconds == 0)
    {
      time_left = false;
    }

    u8g2.firstPage();
    do 
    {
      sprintf_P(time_string, PSTR("%02d:%02d"), minutes, seconds);
      // draw the time_string in minutes-seconds format
      u8g2.drawStr(25, 45, time_string);
    } while (u8g2.nextPage());
    delay(1000);
    seconds--;
  }

  else
  {
    u8g2.firstPage();
    do 
    {
      u8g2.drawStr(20, 45, "BREAK");
    } 
    while (u8g2.nextPage());
  }  
}
