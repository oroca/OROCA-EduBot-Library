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

    void setSpeed(int32_t left, int32_t right);
    void setStep(int32_t left, int32_t right, int max_speed = 0);
    void setLeftSpeed(int32_t left);
    void setLeftStep(int32_t left, int max_speed = 0);
    void setRightSpeed(int32_t right);
    void setRightStep(int32_t right, int max_speed = 0);
    void wait(void);

    int32_t getLeftSpeed(void);
    int32_t getRightSpeed(void);
    int32_t getLeftStep(void);
    int32_t getRightStep(void);

  private:

};



#endif