#include <EduBot.h>


namespace AppPlayRadio
{

void setup() {
  // put your setup code here, to run once:
  bool ret;
  
  edubot.begin(115200);                                   
  
  ret = edubot.wifi.begin();

  if (ret == true)
  {
    edubot.lcd.printf(0, 0, "WiFi OK");  
    edubot.lcd.display();    
  }
  else
  {
    edubot.lcd.printf(0, 0, "WiFi Fail");  
    edubot.lcd.display();        
  }

  edubot.audio.setVolume(50);
  edubot.audio.playURL("onair.radiogfm.kr:8003");
}

void loop() {
  // put your main code here, to run repeatedly
  uint32_t pre_time;


  pre_time = micros();
  edubot.lcd.clearDisplay();
  edubot.lcd.printf(0, 0, "Radio");
  edubot.lcd.printf(0, 16, "%d", millis());

  if (edubot.audio.isBusy())
  {
    edubot.lcd.printf(0, 32, "Playing");
  }
  else
  {
    edubot.lcd.printf(0, 32, "Stop");
  }
  
  edubot.lcd.display();
  delay(50);

  if (edubot.buttonGetPressed())
  {
    while(edubot.buttonGetPressed());

    if (edubot.audio.isBusy())
    {
      edubot.audio.playStop();
    }
    else
    {
      edubot.audio.playURL("onair.radiogfm.kr:8003");
    }
  }  
}

}