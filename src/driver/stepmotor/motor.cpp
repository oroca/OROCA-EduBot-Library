/*
 * motor.cpp
 *
 *      Author: Baram
 */


#include "motor.h"
#include "stepmotor.h"
#include <math.h>


#define ENCODER_RES       (20*50)                               // 1바퀴 회전시 엔코더 펄스 수 
#define TICK2RAD          (((360./ENCODER_RES) * M_PI) / 180.)  // 엔코더 1펄스일때 회전하는 각도(라디안) 

#define DEG2RAD(x)        (x * 0.01745329252)                   // *PI/180
#define RAD2DEG(x)        (x * 57.2957795131)                   // *180/PI



static xSemaphoreHandle lock;


#define MOTOR_MUTEX_LOCK()    do {} while (xSemaphoreTake(lock, portMAX_DELAY) != pdPASS)
#define MOTOR_MUTEX_UNLOCK()  xSemaphoreGive(lock)



StepMotor step_l(0);
StepMotor step_r(1);


Motor::Motor()
{
  is_init = false;
  gear_ratio = 50;      // 50:1
  wheel_distance = 57;  // 57mm
  wheel_diameter = 34;  // 34mm
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

  if(lock == NULL) 
  {
    lock = xSemaphoreCreateMutex();
    if(lock == NULL) 
    {
      return false;
    }
  }

  pre_step_cnt_l = step_l.getStepCount();
  pre_step_cnt_r = step_r.getStepCount();

  is_init = true;
  return true;
}

void Motor::setSpeed(int32_t left, int32_t right, uint32_t delay_ms)
{
  step_l.setSpeed(left);
  step_r.setSpeed(right);  

  if (delay_ms > 0)
  {
    delay(delay_ms);
    step_l.setSpeed(0);
    step_r.setSpeed(0);  
  }
}

void Motor::setLeftSpeed(int32_t left, uint32_t delay_ms)
{
  step_l.setSpeed(left);

  if (delay_ms > 0)
  {
    delay(delay_ms);
    step_l.setSpeed(0);
  }
}

void Motor::setRightSpeed(int32_t right, uint32_t delay_ms)
{
  step_r.setSpeed(right);  

  if (delay_ms > 0)
  {
    delay(delay_ms);
    step_r.setSpeed(0);  
  }
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

void Motor::setWheelDistance(int32_t distance)
{
  wheel_distance = distance;
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

int32_t Motor::distanceToStep(float distance)
{
  // 모터 스텝각          : 18도
  // 모터 1회전시 스텝 수  : 360/18 = 20;
  // 휠 1회전시 스텝 수    : 20 * 기어비
  float steps_per_rotate;
  int32_t steps_for_distance;


  steps_per_rotate = 20.0 * (float)gear_ratio;

  steps_for_distance = distance * steps_per_rotate / ((float)wheel_diameter * M_PI);


  return steps_for_distance;
}

int32_t Motor::angleToStep(float angle)
{
  float radius = (float)wheel_distance / 2.0;
  float radian = angle * M_PI / 180.;
  float length;

  length = 2.0 * M_PI * radius * angle / 360.;

  
  return distanceToStep(length);
}

float Motor::getX(void)
{
  return loc_x;
}

float Motor::getY(void)
{
  return loc_y;
}

float Motor::getAngle(void)
{
  return RAD2DEG(loc_rad);
}

float Motor::clearLocation(void)
{
  MOTOR_MUTEX_LOCK();
  loc_x = 0;
  loc_y = 0;
  loc_rad = 0;
  MOTOR_MUTEX_UNLOCK();
}

float Motor::setLocation(float x, float y, float angle)
{
  MOTOR_MUTEX_LOCK();
  loc_x = x;
  loc_y = y;
  loc_rad = DEG2RAD(angle);  
  MOTOR_MUTEX_UNLOCK();
}

void Motor::update(void)
{
  float cnt_l;
  float cnt_r;
  float wheel_l, wheel_r; 
  float wheel_radius;
  float delta_s, delta_theta;
  float wheel_separation;

  int32_t step_cnt_l;
  int32_t step_cnt_r;


  step_cnt_l = step_l.getStepCount();
  step_cnt_r = step_r.getStepCount();

  cnt_l = step_cnt_l - pre_step_cnt_l;
  cnt_r = step_cnt_r - pre_step_cnt_r;  

  pre_step_cnt_l = step_cnt_l;
  pre_step_cnt_r = step_cnt_r;

  wheel_radius = ((float)wheel_diameter / 2.0); 
  wheel_separation = (float)wheel_distance;

  wheel_l = TICK2RAD * cnt_l;
  wheel_r = TICK2RAD * cnt_r;
  
  delta_s     = wheel_radius * (wheel_l + wheel_r) / 2.0;
  delta_theta = wheel_radius * (wheel_l - wheel_r) / wheel_separation;
    

  MOTOR_MUTEX_LOCK();
  loc_y  += delta_s * cos(loc_rad + (delta_theta / 2.0));
  loc_x  += delta_s * sin(loc_rad + (delta_theta / 2.0));
  loc_rad += delta_theta;

  // loc_rad : -180 ~ 180
  if (loc_rad > PI)
  {
    loc_rad = loc_rad - 2.*PI;
  }
  if (loc_rad < -PI)
  {
    loc_rad = loc_rad + 2.*PI;
  }
  MOTOR_MUTEX_UNLOCK();
}

