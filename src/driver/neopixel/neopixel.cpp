#include "neopixel.h"



#define PIN             D0
#define NUMPIXELS       2


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


NeoPixel::NeoPixel()
{
    
}

NeoPixel::~NeoPixel()
{
    
}

bool NeoPixel::begin(void)
{
  bool ret = true;

  for (int i=0; i<3; i++)
  {
    left_pwm[i] = 0;
    right_pwm[i] = 0;
  }

  pixels.begin(); 
  pixels.setPixelColor(0, pixels.Color(0,0,0)); 
  pixels.show(); 
  pixels.setPixelColor(1, pixels.Color(0,0,0)); 
  pixels.show(); 

  return ret;
}

void NeoPixel::leftBright(uint8_t R, uint8_t G, uint8_t B)
{
  left_pwm[0] = G;
  left_pwm[1] = R;
  left_pwm[2] = B;
  
  pixels.setPixelColor(1, pixels.Color(left_pwm[0],  left_pwm[1],  left_pwm[2])); 
  pixels.show(); 
  pixels.setPixelColor(0, pixels.Color(right_pwm[0], right_pwm[1], right_pwm[2]));   
  pixels.show(); 
}

void NeoPixel::rightBright(uint8_t R, uint8_t G, uint8_t B)
{
  right_pwm[0] = G;
  right_pwm[1] = R;
  right_pwm[2] = B;

  pixels.setPixelColor(1, pixels.Color(left_pwm[0],  left_pwm[1],  left_pwm[2])); 
  pixels.show(); 
  pixels.setPixelColor(0, pixels.Color(right_pwm[0], right_pwm[1], right_pwm[2]));   
  pixels.show(); 
}

