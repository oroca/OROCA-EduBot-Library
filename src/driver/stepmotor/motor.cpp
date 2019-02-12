/*
 * motor.cpp
 *
 *      Author: Baram
 */


#include "motor.h"
#include "stepmotor.h"



StepMotor step_l(0);
StepMotor step_r(1);


Motor::Motor()
{
  gear_ratio = 50;
  wheel_diameter = 32;
}

Motor::~Motor()
{
	
}

bool Motor::begin(void)
{		
  step_l.begin(27, 14, 32,  1);  // enable_pin, step_pin, dir_pin, dir
  step_l.setAcc(1);
  step_l.setSpeed(0);

  step_r.begin(12, 15,  2, -1);   // enable_pin, step_pin, dir_pin, dir
  step_r.setAcc(1);
  step_r.setSpeed(0);  


  return true;
}

void Motor::setSpeed(int32_t left, int32_t right)
{
  step_l.setSpeed(left);
  step_r.setSpeed(right);  
}

void Motor::setStep(int32_t left, int32_t right, int max_speed)
{
  step_l.setStep(left, max_speed);
  step_r.setStep(right, max_speed);  
  wait();
}

void Motor::setStepNoWait(int32_t left, int32_t right, int max_speed)
{
  step_l.setStep(left, max_speed);
  step_r.setStep(right, max_speed);    
}

void Motor::wait(void)
{
  while(step_l.isBusy());
  while(step_r.isBusy());
}

void Motor::waitLeft(void)
{
  while(step_l.isBusy());
}

void Motor::waitRight(void)
{
  while(step_r.isBusy());
}

bool Motor::isBusy(void)
{
  return (step_l.isBusy() | step_r.isBusy());
}

bool Motor::isLeftBusy(void)
{
  return step_l.isBusy();
}

bool Motor::isRightBusy(void)
{
  return step_r.isBusy();
}

void Motor::setLeftSpeed(int32_t left)
{
  step_l.setSpeed(left);
}

void Motor::setLeftStep(int32_t left, int max_speed)
{
  step_l.setStep(left, max_speed);
  waitLeft();
}

void Motor::setLeftStepNoWait(int32_t left, int max_speed)
{
  step_l.setStep(left, max_speed);
}

void Motor::setRightSpeed(int32_t right)
{
  step_r.setSpeed(right);
}

void Motor::setRightStep(int32_t right, int max_speed)
{
  step_r.setStep(right, max_speed);
  waitRight();
}

void Motor::setRightStepNoWait(int32_t right, int max_speed)
{
  setRightStep(right, max_speed);  
}

int32_t Motor::getLeftSpeed(void)
{
  return step_l.cur_speed;
}

int32_t Motor::getRightSpeed(void)
{
  return step_r.cur_speed;
}

int32_t Motor::getLeftStep(void)
{
  return step_l.step_count;
}

int32_t Motor::getRightStep(void)
{
  return step_r.step_count;
}

void Motor::setAcc(int32_t left, int32_t right)
{
  step_l.setAcc(left);
  step_r.setAcc(right);
}

void Motor::setLeftAcc(int32_t left)
{
  step_l.setAcc(left);
}

void Motor::setRightAcc(int32_t right)
{
  step_r.setAcc(right);
}

void Motor::setGearRatio(int32_t ratio)
{
  gear_ratio = ratio;
}

void Motor::setWheelDiameter(int32_t diameter)
{
  wheel_diameter = diameter;
}

int32_t Motor::distanceToStep(int32_t distance)
{
  // 모터 스텝각          : 18도
  // 모터 1회전시 스텝 수  : 360/18 = 20;
  // 휠 1회전시 스텝 수    : 20 * 기어비
  int32_t steps_per_rotate;
  int32_t steps_for_distance;


  steps_per_rotate = 20 * gear_ratio;

  steps_for_distance = distance * steps_per_rotate / ((float)wheel_diameter * M_PI);


  return steps_for_distance;
}