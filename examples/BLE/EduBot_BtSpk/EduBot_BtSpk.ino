#include <EduBot.h>
#include "EduBotSpeaker.h"


uint32_t progress_time_ms = 0;
uint32_t pre_time;

EduBotSpeaker BtSpk;


void setup() {
  edubot.begin(115200);
  BtSpk.begin("EduBot Speaker");  
}

void loop() {

  edubot.lcd.clearDisplay();  

  edubot.lcd.printf(16*0, (16*0), "   BtSpeaker");

  if (BtSpk.isConnected())
  {
    edubot.lcd.printf(16*0, 16*1, "연결완료");
  }
  else
  {
    edubot.lcd.printf(16*0, 16*1, "연결대기");
  }

  if (BtSpk.isPlaying())
  {
    edubot.lcd.printf(16*0, 16*2, "Playing");   
    progress_time_ms += (millis()-pre_time);
    pre_time = millis();
    edubot.lcd.printf(16*0, 16*3, "%dm %ds", (progress_time_ms/1000)/60, progress_time_ms/1000);    
  }
  else
  {
    edubot.lcd.printf(16*0, 16*2 , "Stoped");
    progress_time_ms = 0;
    pre_time = millis();
  }
  edubot.lcd.display();  
}
