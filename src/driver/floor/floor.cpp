/*
 * floor.h
 *
 *      Author: Baram
 */

#include "floor.h"
#include "../adc_info/adc_info.h"


#define ADC_LEFT_IN       A2
#define ADC_LEFT_OUT      A3
#define ADC_RIGHT_IN      A1
#define ADC_RIGHT_OUT     A0


Floor::Floor()
{
    
}

Floor::~Floor()
{
    
}

bool Floor::begin(void)
{
  adcInfoEnable(A0);
  adcInfoEnable(A1);
  adcInfoEnable(A2);
  adcInfoEnable(A3);
  return true;
}

void Floor::update(void)
{

}
   
uint16_t Floor::getLeftIn(void)
{
  return adcInfoRead(ADC_LEFT_IN);
}

uint16_t Floor::getLeftOut(void)
{
  return adcInfoRead(ADC_LEFT_OUT);
}

uint16_t Floor::getRightIn(void)
{
  return adcInfoRead(ADC_RIGHT_IN);
}

uint16_t Floor::getRightOut(void)
{
  return adcInfoRead(ADC_RIGHT_OUT);
}
