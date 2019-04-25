#include <EduBot.h>
#include "animation.h"

Animation EdubotAnimation ;

typedef struct
{
  bool is_init;  
  bool drawbythread;  
  uint8_t faceAnim1;
  uint8_t faceAnim2;
  uint8_t faceAnimState;
  uint32_t pre_ani_time;
  uint32_t ani_dur_time ;
  uint32_t ani1_dur_time ;
  uint32_t ani2_dur_time ;
  int count ;
} animation_node_t;


animation_node_t ani_play;

volatile SemaphoreHandle_t animation_semaphore = NULL;
volatile TaskHandle_t _animation_task_handle = NULL;
volatile SemaphoreHandle_t myMutex;

void animationThread(void *arg)
{
  Animation *p_animation = (Animation *)arg;
  while(1)
  { 
    //Serial.println("animationThread");  
    xSemaphoreTake(myMutex,portMAX_DELAY);
    edubot.lcd.drawBitmap(0, 0, face_smile, 128, 64, 0, 1);
    edubot.lcd.display();
    edubot.lcd.display();
    xSemaphoreGive(myMutex);
    delay(100);
  }

}


Animation::Animation(void)
{
  ani_play.is_init = false;
  ani_play.drawbythread = false;
  ani_play.faceAnim1 = IMG_FACE_Rabbit_IDLE1_INV;
  ani_play.faceAnim2 = IMG_FACE_Rabbit_SLEEP_INV;
  ani_play.faceAnimState = FACE_ANIM2;
  ani_play.pre_ani_time = 0;
  ani_play.ani_dur_time = 1000;
  ani_play.ani1_dur_time = 1000;
  ani_play.ani2_dur_time = 1000;

}

Animation::~Animation()
{
	
}

bool Animation::isInit(void)
{
  return ani_play.is_init;
}

bool Animation::begin(void)
{ 
  //Serial.print("Animation begin");  
  if (ani_play.is_init == false)
  {
    //speaker.begin();

    if (animation_semaphore == NULL)
    {
      animation_semaphore = xSemaphoreCreateBinary();
      myMutex = xSemaphoreCreateMutex();
    }
  
    if ( ani_play.drawbythread ){
      //xTaskCreate(animationThread, "animationThread", 4096, this, 1, (TaskHandle_t*)&_animation_task_handle); 
      xTaskCreate(animationThread, "animationThread", 10000, this, 0, (TaskHandle_t*)&_animation_task_handle);  
    } 
    

    if (!_animation_task_handle)
    {
      ani_play.is_init = false;
    }
    else
    {
      ani_play.is_init = true;
    }    
    
  }


  //playAnimationByTimer();
  drawLcdImage( IMG_FACE_Rabbit_SLEEP_INV );
  
  //edubot.lcd.drawBitmap(0, 0, face_smile, 128, 64, 0, 1);
  edubot.lcd.display();
  

  return ani_play.is_init;
}

void Animation::set(uint8_t image1, uint32_t time1, uint8_t image2, uint32_t time2)
{

  ani_play.faceAnim1 =  image1;
  ani_play.ani1_dur_time = time1 ;
  ani_play.faceAnim2 =  image2;
  ani_play.ani2_dur_time = time2 ; 
  
  drawLcdImage( image1 );
  ani_play.faceAnimState = FACE_ANIM1;

}

void Animation::play(void)
{
  //Serial.println("faceAnimation");
  if ( millis()- ani_play.pre_ani_time >= ani_play.ani_dur_time )
  {
      if( ani_play.faceAnimState == FACE_ANIM1 ){
        drawLcdImage( ani_play.faceAnim2 );
        edubot.lcd.display();
        ani_play.faceAnimState = FACE_ANIM2;
        ani_play.ani_dur_time =  ani_play.ani2_dur_time;  
        //Serial.println("faceAnimation....1");  
                
      }else if( ani_play.faceAnimState == FACE_ANIM2 ){
        drawLcdImage( ani_play.faceAnim1 );
        edubot.lcd.display();
        ani_play.faceAnimState = FACE_ANIM1;
        ani_play.ani_dur_time =  ani_play.ani1_dur_time; 
        //Serial.println("faceAnimation....2");  
      }
      ani_play.pre_ani_time = millis();
  }   
   
}

void Animation::playAnimationByThread(void)
{
   xSemaphoreGive(animation_semaphore);
}

void Animation::stop(void)
{
}

void Animation::drawLcdImage(uint16_t index)
{
  ani_img_tbl_t *p_img = (ani_img_tbl_t *)&ani_img_tbl[index];

  if (index >= IMG_EDUBOT_MAX)
  {
    return;
  }

  edubot.lcd.drawBitmap(p_img->x, p_img->y, p_img->p_data, p_img->width, p_img->height, p_img->color, !p_img->color);
}
