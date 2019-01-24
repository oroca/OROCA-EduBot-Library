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


    float getRoll(void) { return m_imu.roll; }
    float getPitch(void) { return m_imu.pitch; }
    float getYaw(void) { return m_imu.yaw; }    

    float getAccX(void) { return m_imu.calcAccel(m_imu.ax); };
    float getAccY(void) { return m_imu.calcAccel(m_imu.ay); };
    float getAccZ(void) { return m_imu.calcAccel(m_imu.az); };

    float getGyroX(void) { return m_imu.calcGyro(m_imu.gx); };
    float getGyroY(void) { return m_imu.calcGyro(m_imu.gy); };
    float getGyroZ(void) { return m_imu.calcGyro(m_imu.gz); };

  private:
    bool is_init;
    MPU9250_DMP m_imu;
};



#endif