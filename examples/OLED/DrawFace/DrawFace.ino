#include <EduBot.h>
#include "animation.h"

static int anim_num = 9;
static bool buttonGetPressed(void);
static bool cur_press_state = false;
static bool prev_press_state = false;
static int count = 0 ;
static Animation anim ;

void setup() {
  // put your setup code here, to run once:
  edubot.begin(115200); 
  delay(100);
  // for Unser Button
  pinMode(0, INPUT_PULLUP);  
  // for anim
  count = 5 ;
  anim.begin(); 
  anim.set(IMG_FACE_Rabbit_SLEEP_INV,100,IMG_FACE_Rabbit_IDLE1_INV,3000);   
}

void loop() {  
  anim.play(); 

  cur_press_state = buttonGetPressed() ;
  if( cur_press_state && !prev_press_state ){ 
    count = count + 1 ;        
    if (( count % anim_num )== 0 ){
      anim.set(IMG_FACE_SMILE_INV, 1000 , IMG_FACE_SLEEP_INV, 500 );
    }else if ( ( count % anim_num ) == 1 ){
      anim.set(IMG_FACE_SMILE_INV, 1000 , IMG_FACE_LEFT_INV, 500 );     
    }else if ( ( count % anim_num ) == 2 ){
      anim.set(IMG_FACE_SMILE_INV, 1000 , IMG_FACE_RIGHT_INV, 500 );
    }else if ( ( count % anim_num ) == 3 ){
      anim.set(IMG_FACE_SMILE_INV, 1000 , IMG_FACE_SPEAK_INV, 500 ); 
    }else if ( ( count % anim_num ) == 4 ){
      anim.set(IMG_FACE_SAD_1_INV, 1000 , IMG_FACE_SAD_2_INV, 500 );  
    }else if ( ( count % anim_num ) == 5 ){
      anim.set(IMG_FACE_Rabbit_IDLE1_INV, 100 , IMG_FACE_Rabbit_SLEEP_INV, 3000 );  
    }else if ( ( count % anim_num ) == 6 ){
      anim.set(IMG_FACE_Rabbit_IDLE1_INV, 1000 , IMG_FACE_Rabbit_IDLE2_INV, 500 );  
    }else if ( ( count % anim_num ) == 7 ){
      anim.set(IMG_FACE_Rabbit_IDLE1_INV, 1000 , IMG_FACE_Rabbit_LAUGH1_INV, 500 );  
    }else if ( ( count % anim_num ) == 8 ){
      anim.set(IMG_FACE_Rabbit_LAUGH1_INV, 1000 , IMG_FACE_Rabbit_LAUGH2_INV, 500 );  
    }             
    
  }
  prev_press_state = cur_press_state ;
  delay(10);  
}

bool buttonGetPressed(void)
{
  if (digitalRead(0) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }  
}
