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


#define EDUBOT_VER_STR            "EduBot V19041R1"

#define EDUBOT_OK                 0
#define EDUBOT_ERR_INIT_IMU       1



#define MENU_MAX_NODE             32


typedef struct
{
  uint8_t index;
  char    str[16];
  uint8_t str_length;

  void (*setup_func)(void);
  void (*loop_func)(void);
} menu_node_t;


typedef struct 
{
  uint8_t run_count;  
  uint8_t count;
  uint8_t cursor;
  uint8_t first_rows;
  uint8_t view_rows;
  uint32_t pre_time;
  uint32_t pre_time_pressed;
  uint32_t press_count;
  bool     press_state;
  menu_node_t node[MENU_MAX_NODE];
} menu_t;



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
    Floor     floor_sensor;

    WifiEduBot wifi;

    bool begin(int baud);
    bool update(void);

    void ledOn(void);
    void ledOff(void);
    void ledToggle(void);

    bool tofBegin(void);
    void tofEnd(void);

    bool buttonGetPressed(void);
    uint8_t batteryGetVoltage(void);

    void menuAdd(const char *menu_str, void (*setup_func)(void) = NULL, void (*loop_func)(void) = NULL);
    void menuUpdate(void);

  private:
    bool printInitLog(const char *str_msg, bool ret);
    bool menuDraw(menu_t *p_menu);

    bool is_init;

    uint32_t pre_time[8];
    menu_t menu;
    menu_t *p_menu;
};

extern EduBot edubot;

#endif 
