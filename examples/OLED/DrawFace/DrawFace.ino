#include <EduBot.h>
#include <image/EduBotFace.h>

bool buttonGetPressed(void);
bool cur_press_state = false;
bool prev_press_state = false;
int count = 0 ;
unsigned char face1 [1024] ;
unsigned char face2 [1024] ;

void setup() {
  // put your setup code here, to run once:
  edubot.begin(115200);    
  Serial.begin(115200);  
  // for Unser Button
  pinMode(0, INPUT_PULLUP);  
  count = 0 ;
  
  copy_arr(face1, face_smile, 1024);
  copy_arr(face2, face_sleep, 1024);

  edubot.lcd.drawBitmap(0, 0, face1, 128, 64, 0, 1);
  edubot.lcd.display();
  delay(500);
  edubot.lcd.drawBitmap(0, 0, face2, 128, 64, 0, 1);
  edubot.lcd.display();
  delay(500);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  edubot.lcd.drawBitmap(0, 0, face1, 128, 64, 0, 1);
  edubot.lcd.display();
  delay(500);
  edubot.lcd.drawBitmap(0, 0, face2, 128, 64, 0, 1);
  edubot.lcd.display();
  delay(500);

  cur_press_state = buttonGetPressed() ;

  if( cur_press_state && !prev_press_state ){
    count = count + 1 ;  
  }

  prev_press_state = cur_press_state ;

    if (( count % 6 )== 0 ){
      copy_arr(face1, face_smile, 1024);
      copy_arr(face2, face_sleep, 1024); 
    }else if ( ( count % 6 ) == 1 ){
      copy_arr(face1, face_smile, 1024);
      copy_arr(face2, face_left, 1024);      
    }else if ( ( count % 6 ) == 2 ){
      copy_arr(face1, face_smile, 1024);
      copy_arr(face2, face_right, 1024); 
    }else if ( ( count % 6 ) == 3 ){
      copy_arr(face1, face_smile, 1024);
      copy_arr(face2, face_speak, 1024); 
    }else if ( ( count % 6 ) == 4 ){
      copy_arr(face1, face_smile, 1024);
      copy_arr(face2, face_sleep, 1024); 
    }else if ( ( count % 6 ) == 5 ){
      copy_arr(face1, face_sad1, 1024);
      copy_arr(face2, face_sad2, 1024);    
    } 
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

void copy_arr(unsigned char * tar, const unsigned char * sour, int lo)
{
    int count;
    for (count = 0; count < lo; count++)
        tar[count] = sour[count];
    
    return;
}
 
