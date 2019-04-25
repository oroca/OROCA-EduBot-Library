#ifndef _Animation_H_
#define _Animation_H_

#include <Arduino.h>
#include <image/EduBoy.h>
#include <image/EduBotFace.h>

enum 
{
  FACE_ANIM1 = 0,   // 0
  FACE_ANIM2,       // 1
} ANIM_State;

enum 
{
  IMG_OROCA_LOGO_1 = 0,   // 0
  IMG_OROCA_LOGO_2,       // 1
  IMG_OROCA_LOGO_3,       // 2
  IMG_OROCA_LOGO_4,       // 3
  IMG_FACE_LEFT,          // 4
  IMG_FACE_RIGHT,         // 5
  IMG_FACE_SAD_1,         // 6
  IMG_FACE_SAD_2,         // 7
  IMG_FACE_SLEEP,         // 8
  IMG_FACE_SMILE,         // 9
  IMG_FACE_SPEAK,         // 10
  IMG_FACE_Rabbit_SLEEP,         // 11
  IMG_FACE_Rabbit_IDLE1,         // 12
  IMG_FACE_Rabbit_IDLE2,         // 13
  IMG_FACE_Rabbit_IDLE3,         // 14
  IMG_FACE_Rabbit_LAUGH1,         // 15
  IMG_FACE_Rabbit_LAUGH2,         // 16
  
  IMG_FACE_LEFT_INV,      // 11
  IMG_FACE_RIGHT_INV,     // 12
  IMG_FACE_SAD_1_INV,     // 13
  IMG_FACE_SAD_2_INV,     // 14
  IMG_FACE_SLEEP_INV,     // 15
  IMG_FACE_SMILE_INV,     // 16
  IMG_FACE_SPEAK_INV,     // 17
  IMG_FACE_Rabbit_SLEEP_INV,         // 18
  IMG_FACE_Rabbit_IDLE1_INV,         // 19
  IMG_FACE_Rabbit_IDLE2_INV,         // 20
  IMG_FACE_Rabbit_IDLE3_INV,         // 21
  IMG_FACE_Rabbit_LAUGH1_INV,         // 22
  IMG_FACE_Rabbit_LAUGH2_INV,         // 23

  IMG_EDUBOT_MAX
} AnimationImage;

typedef struct 
{
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  uint8_t *p_data;
  uint8_t  color;
} ani_img_tbl_t;


static const ani_img_tbl_t ani_img_tbl[IMG_EDUBOT_MAX] = 
{
  {(128-48)/2, (64-48)/2, 48, 48, (uint8_t *)&edubot_logo[0*48*48/8], 1},
  {(128-48)/2, (64-48)/2, 48, 48, (uint8_t *)&edubot_logo[1*48*48/8], 1},
  {(128-48)/2, (64-48)/2, 48, 48, (uint8_t *)&edubot_logo[2*48*48/8], 1},
  {(128-48)/2, (64-48)/2, 48, 48, (uint8_t *)&edubot_logo[3*48*48/8], 1},

  {0, 0, 128, 64, (uint8_t *)&face_left[0], 1},
  {0, 0, 128, 64, (uint8_t *)&face_right[0], 1},
  {0, 0, 128, 64, (uint8_t *)&face_sad1[0], 1},
  {0, 0, 128, 64, (uint8_t *)&face_sad2[0], 1},
  {0, 0, 128, 64, (uint8_t *)&face_sleep[0], 1},
  {0, 0, 128, 64, (uint8_t *)&face_smile[0], 1},
  {0, 0, 128, 64, (uint8_t *)&face_speak[0], 1},
  {0, 0, 128, 64, (uint8_t *)&face_rabbit_sleep[0], 1},
  {0, 0, 128, 64, (uint8_t *)&face_rabbit_idle1[0], 1},
  {0, 0, 128, 64, (uint8_t *)&face_rabbit_idle2[0], 1},
  {0, 0, 128, 64, (uint8_t *)&face_rabbit_idle3[0], 1},
  {0, 0, 128, 64, (uint8_t *)&face_rabbit_laugh1[0], 1},
  {0, 0, 128, 64, (uint8_t *)&face_rabbit_laugh2[0], 1},

  {0, 0, 128, 64, (uint8_t *)&face_left[0], 0},
  {0, 0, 128, 64, (uint8_t *)&face_right[0], 0},
  {0, 0, 128, 64, (uint8_t *)&face_sad1[0], 0},
  {0, 0, 128, 64, (uint8_t *)&face_sad2[0], 0},
  {0, 0, 128, 64, (uint8_t *)&face_sleep[0], 0},
  {0, 0, 128, 64, (uint8_t *)&face_smile[0], 0},
  {0, 0, 128, 64, (uint8_t *)&face_speak[0], 0},
  {0, 0, 128, 64, (uint8_t *)&face_rabbit_sleep[0], 0},
  {0, 0, 128, 64, (uint8_t *)&face_rabbit_idle1[0], 0},
  {0, 0, 128, 64, (uint8_t *)&face_rabbit_idle2[0], 0},
  {0, 0, 128, 64, (uint8_t *)&face_rabbit_idle3[0], 0},
  {0, 0, 128, 64, (uint8_t *)&face_rabbit_laugh1[0], 0},
  {0, 0, 128, 64, (uint8_t *)&face_rabbit_laugh2[0], 0},
};

class Animation
{
  public:
    Animation();
    ~Animation();

    bool begin(void);
    bool isInit(void);    

    void set(uint8_t image1, uint32_t time1, uint8_t image2, uint32_t time2);
    void play(void);
    void playAnimationByThread(void);
    void stop(void);
    void drawLcdImage(uint16_t index) ;  
};


#endif
