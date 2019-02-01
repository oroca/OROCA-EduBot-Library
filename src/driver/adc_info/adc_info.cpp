/*
 * adc_info.h
 *
 *      Author: Baram
 */

#include "adc_info.h"


#define ADC_INFO_PIN_MAX      5


typedef struct
{
  int pin_number;
  bool enable;
  uint16_t value;
} adc_pin_info_t;


adc_pin_info_t adc_pin_info[ADC_INFO_PIN_MAX] =
{
  {A0, false, 0},
  {A1, false, 0},
  {A2, false, 0},
  {A3, false, 0},
  {VBAT, true, 0},
};

void adcInfoInit(void)
{
}

void adcInfoEnable(uint16_t pin)
{
  for (int i=0; i<ADC_INFO_PIN_MAX; i++)
  {
    if (adc_pin_info[i].pin_number == pin)
    {
      adc_pin_info[i].enable = true;
    }
  }
}

void adcInfoDisable(uint16_t pin)
{
  for (int i=0; i<ADC_INFO_PIN_MAX; i++)
  {
    if (adc_pin_info[i].pin_number == pin)
    {
      adc_pin_info[i].enable = false;
    }
  }
}

void adcInfoUpdate(void)
{
  for (int i=0; i<ADC_INFO_PIN_MAX; i++)
  {
    if (adc_pin_info[i].enable == true)
    {
      adc_pin_info[i].value = analogRead(adc_pin_info[i].pin_number);      
    }
  }  
}

uint16_t adcInfoRead(uint16_t pin)
{
  uint16_t ret = 0;


  for (int i=0; i<ADC_INFO_PIN_MAX; i++)
  {
    if (adc_pin_info[i].pin_number == pin)
    {
      ret = adc_pin_info[i].value;
    }
  }

  return ret;
}