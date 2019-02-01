/*
 * adc_info.h
 *
 *      Author: Baram
 */

#ifndef _ADCINFO_H_
#define _ADCINFO_H_

#include <Arduino.h>




void adcInfoInit(void);
void adcInfoEnable(uint16_t pin);
void adcInfoDisable(uint16_t pin);
void adcInfoUpdate(void);
uint16_t adcInfoRead(uint16_t pin);

#endif