#include "neopixel.h"
#include "./NeoPixelBus/NeoPixelBus.h"


#define PIN             D0
#define NUMPIXELS       2


NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> pixels(NUMPIXELS, PIN);

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

  pixels.Begin(); 
  pixels.Show(); 

  return ret;
}

void NeoPixel::leftBright(uint8_t R, uint8_t G, uint8_t B)
{
  left_pwm[0] = R;
  left_pwm[1] = G;
  left_pwm[2] = B;


  pixels.SetPixelColor(1, RgbColor(R, G, B));
  pixels.Show();
}

void NeoPixel::rightBright(uint8_t R, uint8_t G, uint8_t B)
{
  right_pwm[0] = R;
  right_pwm[1] = G;
  right_pwm[2] = B;


  pixels.SetPixelColor(0, RgbColor(R, G, B));
  pixels.Show();
}

