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



#define EDUBOT_OK                 0
#define EDUBOT_ERR_INIT_IMU       1



class EduBot
{
  public:
    EduBot();
    ~EduBot();
    
    IrRemote  ir_remote;
    ImuSensor imu;
    Audio     audio;
    Motor     motor;
    OLed      lcd;

    bool begin(int baud);
    bool update(void);

  private:
    bool printInitLog(const char *str_msg, bool ret);

};


#endif 
