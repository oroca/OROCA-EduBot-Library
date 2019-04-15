#include <EduBot.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <esp_wifi.h>

extern "C"
{
#include "./src/audio_player/include/audio_player.h"
#include "./src/fifo/include/spiram_fifo.h"
}


char ssid[] = "your ssid"; 
char pass[] = "your ssid password"; 

int status = WL_IDLE_STATUS;
WiFiClient  client;

typedef struct
{
  char *host;
  char *path;
  int   port;
} station_tbl_t;

station_tbl_t station_tbl[] = 
{
  {"radiostreaming.ert.gr", "/ert-kosmos", 80},
  {"onair.radiogfm.kr", "/", 8003},
};


player_t player;


void connectStation(int station_no) 
{
  if (client.connect(station_tbl[station_no].host, station_tbl[station_no].port)) 
  {
    Serial.println("Connected now"); 
    edubot.lcd.println("Connected now");
    edubot.lcd.display(); 
  }
  client.print(String("GET ") + station_tbl[station_no].path + " HTTP/1.1\r\n" +
              "Host: " + station_tbl[station_no].host + "\r\n" + 
              "Connection: close\r\n\r\n");   
}

static renderer_config_t *create_renderer_config()
{
  renderer_config_t *renderer_config = (renderer_config_t *)calloc(1, sizeof(renderer_config_t));

  renderer_config->bit_depth = I2S_BITS_PER_SAMPLE_16BIT;
  renderer_config->i2s_num = I2S_NUM_0;
  renderer_config->sample_rate = 44100;
  renderer_config->sample_rate_modifier = 1.0;
  renderer_config->output_mode = I2S;
  return renderer_config;
}

void setup() {
  edubot.begin(115200);

  edubot.lcd.clearDisplay();  

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
    edubot.lcd.print(".");
    edubot.lcd.display(); 
  }
    
  Serial.println("WiFi connected");
  edubot.lcd.println("\r\nWiFi connected");
  edubot.lcd.display(); 
  


  connectStation(1);
  delay(2000);


  if (!spiRamFifoInit()) 
  {
    printf("\n\nSPI RAM chip fail!\n");
    while(1);
  }
  renderer_init(create_renderer_config());

  player.command = CMD_NONE;
  player.decoder_status = UNINITIALIZED;
  player.decoder_command = CMD_NONE;
  player.buffer_pref = BUF_PREF_SAFE;
  player.media_stream = (media_stream_t *)calloc(1, sizeof(media_stream_t));  
  player.media_stream->content_type =  AUDIO_MPEG;
  audio_player_init(&player);
  audio_player_start();  
}

uint8_t mp3buff[4096];
uint32_t pre_time;
bool playing = false;

void loop() {
  int length;
  int buf_len;


  if (millis()-pre_time > 100)
  {
    edubot.lcd.clearDisplay();  

    edubot.lcd.printf(16*0, (16*0), "   Web Radio");

    if (playing == true)
    {
      edubot.lcd.printf(16*0, (16*2), "   Playing");
    }
    else
    {
      edubot.lcd.printf(16*0, (16*2), "   Stoped");
    }
    edubot.lcd.display();  
  }

  if (edubot.buttonGetPressed())
  {
    while(edubot.buttonGetPressed());

    if (playing == false)
    {
      playing = true;
    }
    else
    {
      playing = false;
    }
  }


  length = client.available();
  buf_len = spiRamFifoFree();

  if (length > 2048)
  {
    length = 2048;
  }

  if (length > 0 && buf_len > 0)
  {
    
    if (length > buf_len)
    {
      length = buf_len;
    }
    uint32_t bytesread = client.read(mp3buff, length);

    if (playing == true)
    {
      audio_stream_consumer((const char *)mp3buff, bytesread, (void *)&player);
    }
  }  
}
