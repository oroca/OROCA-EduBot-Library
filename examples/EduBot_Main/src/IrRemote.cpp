#include <EduBot.h>


namespace AppIrRemote
{

void setup() {
  // put your setup code here, to run once:
  
  edubot.begin(115200);   
  edubot.tofEnd();                                
}

void loop() {
  // put your main code here, to run repeatedly

  if (edubot.ir_remote.available() > 0)
  {
    uint32_t key_code;

    key_code = edubot.ir_remote.read();

    Serial.print("Key : 0x");
    Serial.print(key_code, HEX);
    Serial.print(" ");
    Serial.println(edubot.ir_remote.getTime());
    edubot.lcd.clearDisplay();
    edubot.lcd.printf(0, 0, "KeyCode");
    edubot.lcd.printf(0, 16,"0x%X", key_code);
    edubot.lcd.display();
  }
}

}