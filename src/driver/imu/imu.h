#ifndef _IMU_H_
#define _IMU_H_

#include <Arduino.h>
#include "SparkFunMPU9250-DMP.h"





class ImuSensor 
{
  public:
    ImuSensor();
    ~ImuSensor();
    
    bool begin(void);
    bool isInit(void);
    bool update(void);


    float getRoll(void);
    float getPitch(void);
    float getYaw(void);

    float getAccX(void);
    float getAccY(void);
    float getAccZ(void);

    float getGyroX(void);
    float getGyroY(void);
    float getGyroZ(void);

  private:
    bool is_init;
    MPU9250_DMP m_imu;
};



#endif