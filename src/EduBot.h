/*
 * EduBot.h
 *
 *  Created on: May 16, 2018
 *      Author: Baram
 */

#ifndef OROCA_EDUBOT_H_
#define OROCA_EDUBOT_H_

#include <Arduino.h>

#include "./driver/driver.h"


#define EDUBOT_VER_STR            "EduBot V190201R2"

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
#ifdef EDUBOT_DRIVER_BLE
    BLE       ble;
#endif
    NeoPixel  led;
    VL53L0X   tof_L;
    VL53L0X   tof_R;
    Floor     floor_sensor;

    bool begin(int baud);
    bool update(void);

    void ledOn(void);
    void ledOff(void);
    void ledToggle(void);

    bool tofBegin(void);
    void tofEnd(void);

    bool buttonGetPressed(void);
    uint8_t batteryGetVoltage(void);

  private:
    bool printInitLog(const char *str_msg, bool ret);

    uint32_t pre_time[8];
};


#endif 
