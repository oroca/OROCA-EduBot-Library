/*
 * EduBot.h
 *
 *  Created on: May 16, 2018
 *      Author: Baram
 */

#ifndef OROCA_EDUBOT_H_
#define OROCA_EDUBOT_H_

#include <Arduino.h>



#include "./driver/imu/imu.h"
#include "./driver/stepmotor/motor.h"
#include "./driver/stepmotor/stepmotor.h"
#include "./driver/audio/audio.h"
#include "./driver/oled/oled.h"
#include "./driver/oled/oled.h"
#include "./driver/hangul/PHan_Lib.h"
#include "./driver/vl53l0x/VL53L0X.h"
#include "./driver/ir_remote/ir_remote.h"
#include "./driver/neopixel/neopixel.h"


#define EDUBOT_VER_STR            "EduBot V190201R1"

#define EDUBOT_OK                 0
#define EDUBOT_ERR_INIT_IMU       1



class EduBot
{
  public:
    EduBot();
    ~EduBot();
    
    
    ImuSensor imu;
    Audio     audio;
    Motor     motor;

    // for Extention Board
    IrRemote  ir_remote;
    OLed      lcd;
    NeoPixel  led;
    VL53L0X   tof_L;
    VL53L0X   tof_R;

    bool begin(int baud);
    bool update(void);

    void ledOn(void);
    void ledOff(void);
    void ledToggle(void);
  private:
    bool printInitLog(const char *str_msg, bool ret);

    uint32_t pre_time[8];
};


#endif 
