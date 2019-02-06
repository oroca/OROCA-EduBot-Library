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
  uint16_t value_raw;
} adc_pin_info_t;


adc_pin_info_t adc_pin_info[ADC_INFO_PIN_MAX] =
{
  {A0, false, 0, 0},
  {A1, false, 0, 0},
  {A2, false, 0, 0},
  {A3, false, 0, 0},
  {VBAT, true, 0, 0},
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
  uint16_t value;


  for (int i=0; i<ADC_INFO_PIN_MAX; i++)
  {
    if (adc_pin_info[i].enable == true)
    {
      adc_pin_info[i].value_raw = analogRead(adc_pin_info[i].pin_number);
      value = constrain(adc_pin_info[i].value_raw, 0, 3000);
      value = map(value, 0, 3000, 0, 255);
      adc_pin_info[i].value = value;      
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

uint16_t adcInfoReadRaw(uint16_t pin)
{
  uint16_t ret = 0;


  for (int i=0; i<ADC_INFO_PIN_MAX; i++)
  {
    if (adc_pin_info[i].pin_number == pin)
    {
      ret = adc_pin_info[i].value_raw;
    }
  }

  return ret;
}