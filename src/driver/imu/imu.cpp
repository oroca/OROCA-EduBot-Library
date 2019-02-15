#include "imu.h"


static xSemaphoreHandle lock;


#define IMU_MUTEX_LOCK()    do {} while (xSemaphoreTake(lock, portMAX_DELAY) != pdPASS)
#define IMU_MUTEX_UNLOCK()  xSemaphoreGive(lock)


ImuSensor::ImuSensor(void)
{
  is_init = false;
}

ImuSensor::~ImuSensor()
{
	
}

bool ImuSensor::isInit(void)
{
  return is_init;
}

bool ImuSensor::begin(void)
{
  inv_error_t inv_error;

  if(lock == NULL) 
  {
    lock = xSemaphoreCreateMutex();
    if(lock == NULL) 
    {
      return false;
    }
  }

  // Call imu.begin() to verify communication and initialize
  if (m_imu.begin() != INV_SUCCESS)
  {
    while (1)
    {
      Serial.println("Unable to communicate with MPU-9250");
      Serial.println("Check connections, and try again.");
      Serial.println();
      delay(5000);
    }
    return false;
  }
  
  inv_error = m_imu.dmpBegin(DMP_FEATURE_6X_LP_QUAT |      // Enable 6-axis quat
                             DMP_FEATURE_SEND_RAW_ACCEL |
                             DMP_FEATURE_SEND_CAL_GYRO  |
                             DMP_FEATURE_GYRO_CAL ,        // Use gyro calibration
                             100);                         // Set DMP FIFO rate to 10 Hz

  if (inv_error != INV_SUCCESS)
  {
    Serial.print("dmpBegin err : ");
    Serial.println(inv_error);
    return false;
  }

  is_init = true;
  return true;
}

bool ImuSensor::update(void)
{
  bool ret = false;


  // Check for new data in the FIFO
  if ( m_imu.fifoAvailable() )
  {
    IMU_MUTEX_LOCK();
    // Use dmpUpdateFifo to update the ax, gx, mx, etc. values
    if ( m_imu.dmpUpdateFifo() == INV_SUCCESS)
    {
      // computeEulerAngles can be used -- after updating the
      // quaternion values -- to estimate roll, pitch, and yaw
      m_imu.computeEulerAngles();
      ret = true;
    }
    IMU_MUTEX_UNLOCK();
  }  

  return ret;
}

float ImuSensor::getRoll(void) 
{
  float ret = 0.0;

  IMU_MUTEX_LOCK();
  ret = m_imu.roll;
  IMU_MUTEX_UNLOCK();

  return ret;; 
}

float ImuSensor::getPitch(void) 
{
  float ret = 0.0;

  IMU_MUTEX_LOCK();
  ret = m_imu.pitch;
  IMU_MUTEX_UNLOCK();

  return ret; 
}

float ImuSensor::getYaw(void) 
{ 
  float ret = 0.0;

  IMU_MUTEX_LOCK();
  ret = m_imu.yaw;
  IMU_MUTEX_UNLOCK();

  return ret; 
}    

float ImuSensor::getAccX(void) 
{
  float ret = 0.0;

  IMU_MUTEX_LOCK();
  ret = m_imu.calcAccel(m_imu.ax);
  IMU_MUTEX_UNLOCK();

  return ret; 
};

float ImuSensor::getAccY(void) 
{
  float ret = 0.0;

  IMU_MUTEX_LOCK();
  ret = m_imu.calcAccel(m_imu.ay);
  IMU_MUTEX_UNLOCK();

  return ret; 
};

float ImuSensor::getAccZ(void) 
{ 
  float ret = 0.0;

  IMU_MUTEX_LOCK();
  ret = m_imu.calcAccel(m_imu.az);
  IMU_MUTEX_UNLOCK();

  return ret; 
};

float ImuSensor::getGyroX(void) 
{ 
  float ret = 0.0;

  IMU_MUTEX_LOCK();
  ret = m_imu.calcGyro(m_imu.gx);
  IMU_MUTEX_UNLOCK();

  return ret; 
};

float ImuSensor::getGyroY(void) 
{ 
  float ret = 0.0;

  IMU_MUTEX_LOCK();
  ret = m_imu.calcGyro(m_imu.gy);
  IMU_MUTEX_UNLOCK();

  return ret;   
};

float ImuSensor::getGyroZ(void) 
{ 
  float ret = 0.0;

  IMU_MUTEX_LOCK();
  ret = m_imu.calcGyro(m_imu.gz);
  IMU_MUTEX_UNLOCK();

  return ret;   
};