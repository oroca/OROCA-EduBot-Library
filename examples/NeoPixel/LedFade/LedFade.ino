#include <EduBot.h>


EduBot edubot;



void setup() {
  // put your setup code here, to run once:
  
  edubot.begin(115200);                                     

}

void loop() {
  // put your main code here, to run repeatedly
  static uint8_t led_bright = 0;
  static int led_dir = 1;
  static int led_index = 0;   


  if (led_index == 0)
  {
    edubot.led.leftBright(led_bright, 0, 0);
    edubot.led.rightBright(led_bright, 0, 0);
  }
  else if(led_index == 1)
  {
    edubot.led.leftBright(0, led_bright, 0);
    edubot.led.rightBright(0, led_bright, 0);    
  }
  else
  {
    edubot.led.leftBright(0, 0, led_bright);
    edubot.led.rightBright(0, 0, led_bright);    
  }

  
      
  led_bright += led_dir;  

  if (led_bright == 255)
  {
    led_dir = -1;
  }
  if (led_bright == 0)
  {
    led_dir = 1;
    led_index++;
    led_index %= 3;
  }  
  delay(2);
}