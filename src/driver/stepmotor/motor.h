/*
 * motor.h
 *
 *      Author: Baram
 */


#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <Arduino.h>





class Motor 
{
  public:
    Motor();
    ~Motor();
    
    bool begin(void);

    void setSpeed(int32_t left, int32_t right, uint32_t delay_ms = 0);
    void setLeftSpeed(int32_t left, uint32_t delay_ms = 0);
    void setRightSpeed(int32_t right, uint32_t delay_ms = 0);

    void setStep(int32_t left, int32_t right, int max_speed = 0);
    void setStepNoWait(int32_t left, int32_t right, int max_speed = 0);
    void setLeftSpeed(int32_t left);
    void setLeftStep(int32_t left, int max_speed = 0);
    void setLeftStepNoWait(int32_t left, int max_speed = 0);
    void setRightSpeed(int32_t right);
    void setRightStep(int32_t right, int max_speed = 0);
    void setRightStepNoWait(int32_t right, int max_speed = 0);

    void setDistance(int32_t left, int32_t right, int max_speed = 0) { setStep(distanceToStep(left), distanceToStep(right), max_speed); }
    void setLeftDistance(int32_t left, int max_speed = 0) { setStep(distanceToStep(left), max_speed); }
    void setRightDistance(int32_t right, int max_speed = 0) { setStep(distanceToStep(right), max_speed); }

    void setAcc(int32_t left, int32_t right);
    void setLeftAcc(int32_t left);
    void setRightAcc(int32_t right);

    void wait(void);
    void waitLeft(void);
    void waitRight(void);

    bool isBusy(void);
    bool isLeftBusy(void);
    bool isRightBusy(void);

    int32_t getLeftSpeed(void);
    int32_t getRightSpeed(void);
    int32_t getLeftStep(void);
    int32_t getRightStep(void);

    void setGearRatio(int32_t ratio);
    void setWheelDiameter(int32_t diameter);
    int32_t distanceToStep(int32_t distance);

  private:
    int32_t gear_ratio;
    int32_t wheel_diameter;
};



#endif