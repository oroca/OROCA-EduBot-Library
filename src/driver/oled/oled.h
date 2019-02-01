#ifndef _OLED_H_
#define _OLED_H_

#include <Arduino.h>
#include "../gfx/Adafruit_GFX_Library/Adafruit_GFX.h"
#include "../gfx/Adafruit_SSD1306/Adafruit_SSD1306.h"
#include "../hangul/PHan_Lib.h"


class OLed : public Adafruit_SSD1306
{
  public:
    OLed(): Adafruit_SSD1306(128, 64, &Wire1, -1, 800000UL, 100000UL) { is_init = false; }
    ~OLed();
    
    boolean begin(void);
    void printf(int x, int y,  const char *fmt, ...);
    void disHanFont(int x, int y, PHAN_FONT_OBJ *FontPtr);
    bool isInit() { return is_init; };
  private:
    bool is_init;
};



#endif