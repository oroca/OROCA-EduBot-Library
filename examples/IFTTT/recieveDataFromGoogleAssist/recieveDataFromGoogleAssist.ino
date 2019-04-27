//이예제를 실행하기 위해서는 adafruit mqtt library를 설치 해야 합니다. 
//Arduino 프로그램에서 Sketch Tap 클릭 -> Include Library -> Manage Libraries 에서 adafruit mqtt library 찾아서 설치
//예제 사용법과 IFTTT 쪽 코드 만드는 법은 아래 링크에 있습니다. 두개 중복내용임 
//https://github.com/hyunoklee/OROCA-EduBot-Library/blob/develop/examples/IFTTT/recieveDataFromGoogleAssist/사용법.md
//https://github.com/oroca/OROCA-EduBot-Library/blob/develop/examples/IFTTT/recieveDataFromGoogleAssist/사용법.md

#include <WiFi.h>
#include <EduBot.h>

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
const char* ssid     = "U+123451315";  // 공유기의 이름 
const char* password = "123451315";  // 공유기의 비밀번호 
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "boo"  // https://io.adafruit.com  사이트 IO USER NAME
#define AIO_KEY         "123451315123451315121234513153451315123451315" //https://io.adafruit.com  사이트 IO KEY

WiFiClient client;     // Create an ESP8266 WiFiClient class to connect to the MQTT server.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);        // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Subscribe Edubot_Control = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Edubot_Control");

void MQTT_connect();
int step_len = 500;
uint32_t x=0;

void setup() {

  edubot.begin(115200);  
  delay(10);

  WiFi.begin(ssid, password);

  edubot.lcd.clearDisplay();
  edubot.lcd.printf(0, 16, "Wait wifi connection");
  edubot.lcd.display();

  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  

  edubot.lcd.clearDisplay();
  edubot.lcd.printf(0, 16, "wifi connection ok");
  edubot.lcd.display();  
  
  mqtt.subscribe(&Edubot_Control);

}

void loop() {

   MQTT_connect();
   Adafruit_MQTT_Subscribe *subscription;
   while ((subscription = mqtt.readSubscription(5000))) {

    if (subscription == &Edubot_Control) {
  
      Serial.print(F("Got: "));
      Serial.println((char *)Edubot_Control.lastread);
      edubot.lcd.clearDisplay();
      edubot.lcd.printf(0, 0, "Got Data :");
      //String test888 = (char*) Edubot_Control.lastread ;
      //String test888 = "1234578900" ;
      //edubot.lcd.printf(0, 16, "%s",(char*) Edubot_Control.lastread);
      const char *s = (char*) Edubot_Control.lastread ;
      edubot.lcd.printf(0, 16, s );
      edubot.lcd.display();      

      /*
      if (stristr((char*) Edubot_Control.lastread, "left")!=NULL)
      {
        Serial.println("action is left");
        edubot.motor.setStep(step_len, 0);
        delay(1000);
      }*/
    }
  }
}

char *stristr(const char *string,const char *strSearch)
{
     const char *s,*sub;
     for (;*string;string++) {
          for (sub=strSearch,s=string;*sub && *s && tolower(*s) == tolower(*sub);sub++,s++) {;}
          if (*sub == 0) return (char *)string;
     }
     return NULL;
}

void MQTT_connect() {

  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
 Serial.print("Connecting to MQTT... ");

 uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }

  edubot.lcd.clearDisplay();
  edubot.lcd.printf(0, 16, "MQTT Connected!");
  edubot.lcd.display(); 
  Serial.println("MQTT Connected!");   
      
}
