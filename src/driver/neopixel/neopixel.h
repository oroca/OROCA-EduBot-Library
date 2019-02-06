#ifndef _NEOPIXEL_H_
#define _NEOPIXEL_H_

#include <Arduino.h>




class NeoPixel 
{
  public:
    NeoPixel();
    ~NeoPixel();
    
    bool begin(void);
    void leftBright(uint8_t R, uint8_t G, uint8_t B);
    void rightBright(uint8_t R, uint8_t G, uint8_t B);

  private:
    uint8_t left_pwm[3];
    uint8_t right_pwm[3];
};



#endif