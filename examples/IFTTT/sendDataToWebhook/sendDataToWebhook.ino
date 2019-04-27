//예제 사용법과 IFTTT 쪽 코드 만드는 법은 아래 링크에 있습니다. 두개 중복내용임 
//https://github.com/hyunoklee/OROCA-EduBot-Library/blob/develop/examples/IFTTT/sendDataToWebhook/사용법.md
//https://github.com/oroca/OROCA-EduBot-Library/blob/develop/examples/IFTTT/sendDataToWebhook/사용법.md
#include <EduBot.h>
#include <WiFi.h>

const char* ssid     = "U+123451315";  // 공유기의 이름 
const char* password = "123451315";  // 공유기의 비밀번호 
#define IFTTT_KEY   "123451315-123451315123451315123451315123451315123451315" // 자신의 WebHook Key 
char * MakerIFTTT_Event = "test";  //webhook에서 설정한 Event Name 과 동일해야 함 
const int hostPort = 80;
#define IFTTT_Host  "maker.ifttt.com"

int count = 0;

void setup() {

  //Serial.begin(115200);  
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
  
}

void loop() {    
  sendWebhook(0x19E60707) ; 
  delay(30000);
}
  
void sendWebhook(uint32_t value ) {

  WiFiClient client;
  if (!client.connect(IFTTT_Host, hostPort)) 
  {
    Serial.println("IFTTT Connection fail");
    edubot.lcd.clearDisplay();
    edubot.lcd.printf(0, 16, "IFTTT Connection      fail");
    edubot.lcd.display();
    return;
  }

  edubot.lcd.clearDisplay();
  edubot.lcd.printf(0, 16, "IFTTT Send Data          OK");
  edubot.lcd.display();
  
  String value1 = String(value, HEX) ;
  //String PostData = "{\"value1\" : \"ESP32 test!\" }";  
  String PostData = "{\"value1\" : \""+ value1 +"\" }";  
  Serial.println("connected to server… Getting name…");
  // send the HTTP PUT request:
  String request = "POST /trigger/";
  request += MakerIFTTT_Event;
  request += "/with/key/";
  request += IFTTT_KEY;
  request += " HTTP/1.1";
  
  Serial.println(request);
  client.println(request);  
  client.println("Host: " + String(IFTTT_Host));
  client.println("User-Agent: Energia/1.1");
  client.println("Connection: close");
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(PostData.length());
  client.println();
  client.println(PostData);
  client.println(); 

  while(client.connected())
  {
    if(client.available())
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    else 
    {
      delay(50);
    };
  }

  Serial.println();
  Serial.println("closing connection");
  client.stop();  
}
