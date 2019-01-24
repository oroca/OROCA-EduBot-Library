#include <EduBot.h>


EduBot edubot;


void setup() {
  // put your setup code here, to run once:
  
  edubot.begin(115200);                                   
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
  }
}