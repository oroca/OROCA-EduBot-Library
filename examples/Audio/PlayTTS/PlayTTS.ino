#include <EduBot.h>


void playTTS(void)
{
  edubot.audio.playTTS("안녕하세요. 저의 이름은 에듀봇이에요. 나이는 1살이에요. 이것은 구글 TTS를 이용해서 음성을 출력해 본것이에요. 조금은 느리지만 동작은 되네요. ", "ko", false);  
}

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
  playTTS();
}

void loop() {
  // put your main code here, to run repeatedly
  uint32_t pre_time;


  pre_time = micros();
  edubot.lcd.clearDisplay();
  edubot.lcd.printf(0, 0, "TTS");
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
      playTTS();
    }
  }  
}

