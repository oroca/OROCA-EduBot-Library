#include "audio.h"
#include "MAX98357.h"


#define PLAY_FILE     0
#define PLAY_BUFF     1
#define PLAY_TTS      2
#define PLAY_URL      3

static pcm_format_t bt_buffer_fmt = {
    .sample_rate   = 8000, // 44100
    .bit_depth     = I2S_BITS_PER_SAMPLE_16BIT,
    .num_channels  = 2,
    .buffer_format = PCM_INTERLEAVED
};


#define AUDIO_BUF_MAX     1024

typedef struct
{
  bool is_init;  
  bool is_busy;
  bool is_stop;
  bool is_opened;

  uint8_t play_mode;
  char file_name[128];  
  pcm_format_t buffer_fmt;
  uint8_t spk_buf[2][AUDIO_BUF_MAX];  
  
  uint8_t *play_buff;
  uint32_t play_buff_length;

  String url;
  String lang;  
} audio_node_t;


audio_node_t audio_play;
wav_header_t wav_header;
MAX98357 speaker;


volatile SemaphoreHandle_t play_semaphore = NULL;
volatile TaskHandle_t _play_task_handle = NULL;


bool wavplayStartFile(char *p_name);
bool wavplayStartBuff(uint8_t *p_buff, uint32_t length);


void audioThread(void *arg)
{
  Audio *p_audio = (Audio *)arg;

  while(1)
  {
    if (xSemaphoreTake(play_semaphore, 10) == pdTRUE)
    {
      audio_play.is_busy = true;
      if (audio_play.play_mode == PLAY_FILE)
      {
        wavplayStartFile(audio_play.file_name);
      }
      if (audio_play.play_mode == PLAY_BUFF)
      {
        wavplayStartBuff(audio_play.play_buff, audio_play.play_buff_length);
      }
      if (audio_play.play_mode == PLAY_TTS)
      {
        p_audio->mp3.connecttospeech(audio_play.url, audio_play.lang);
      }
      if (audio_play.play_mode == PLAY_URL)
      {
        p_audio->mp3.connecttohost(audio_play.url);

        while(p_audio->mp3.m_f_running)
        {
          p_audio->mp3.loop();
        }
      }

      

      audio_play.is_busy = false;
    }      
    delay(1);
  }
}


Audio::Audio(void)
{
  audio_play.is_init = false;
  audio_play.is_opened = false;
  audio_play.is_stop = false;

  audio_play.buffer_fmt.sample_rate = 8000;
  audio_play.buffer_fmt.bit_depth = I2S_BITS_PER_SAMPLE_16BIT;
  audio_play.buffer_fmt.num_channels = 2;
  audio_play.buffer_fmt.buffer_format = PCM_INTERLEAVED;
}

Audio::~Audio()
{
	
}

bool Audio::isInit(void)
{
  return audio_play.is_init;
}

bool Audio::begin(void)
{  
  if (audio_play.is_init == false)
  {
    speaker.begin();

    if (play_semaphore == NULL)
    {
      play_semaphore = xSemaphoreCreateBinary();
    }
    xTaskCreate(audioThread, "audioThread", 4096, this, 1, (TaskHandle_t*)&_play_task_handle);    
    

    if (!_play_task_handle)
    {
      audio_play.is_init = false;
    }
    else
    {
      audio_play.is_init = true;
    }    
    
    if(!SPIFFS.begin(true))
    {
      audio_play.is_init = false;    
      return false;
    }  

    mp3.setVolume(90);
  }
  

  return audio_play.is_init;
}

bool Audio::playFile(char *p_name, bool wait)
{
  if (audio_play.is_init == false)
  {
    return false;
  }

  audio_play.play_mode = PLAY_FILE;
  audio_play.is_stop = true;
  while(audio_play.is_busy)
  {
    delay(1);
  }
  audio_play.is_stop = false;


  strcpy(audio_play.file_name, p_name);
  
  xSemaphoreGive(play_semaphore);

  if (wait == true)
  {
    audio_play.is_busy = true;
    while(audio_play.is_busy)
    {
      delay(1);
    }
  }
  else
  {
    audio_play.is_busy = true;
  }
  return true;
}

bool Audio::playBuff(uint8_t *p_buff, uint32_t length, bool wait)
{
  if (audio_play.is_init == false)
  {
    return false;
  }

  audio_play.play_mode = PLAY_BUFF;
  audio_play.is_stop = true;
  while(audio_play.is_busy)
  {
    delay(1);
  }
  audio_play.is_stop = false;


  
  audio_play.play_buff = p_buff;
  audio_play.play_buff_length = length;

  xSemaphoreGive(play_semaphore);

  if (wait == true)
  {
    audio_play.is_busy = true;
    while(audio_play.is_busy)
    {
      delay(1);
    }
  }
  else
  {
    audio_play.is_busy = true;
  }
  return true;
}

bool Audio::playTTS(String tts, String lang, bool wait)
{
  if (audio_play.is_init == false)
  {
    return false;
  }

  audio_play.play_mode = PLAY_TTS;
  audio_play.is_stop = true;
  while(audio_play.is_busy)
  {
    delay(1);
  }
  audio_play.is_stop = false;


  
  audio_play.url = tts;
  audio_play.lang = lang;

  xSemaphoreGive(play_semaphore);

  if (wait == true)
  {
    audio_play.is_busy = true;
    while(audio_play.is_busy)
    {
      delay(1);
    }
  }
  else
  {
    audio_play.is_busy = true;
  }
  return true;
}

bool Audio::playURL(String url)
{
  if (audio_play.is_init == false)
  {
    return false;
  }

  audio_play.play_mode = PLAY_URL;
  audio_play.is_stop = true;
  while(audio_play.is_busy)
  {
    delay(1);
  }
  audio_play.is_stop = false;


  
  audio_play.url = url;

  xSemaphoreGive(play_semaphore);

  audio_play.is_busy = true;
  return true;
}

void Audio::playStop(void)
{
  mp3.stopSong();

  audio_play.is_stop = true;
  while(audio_play.is_busy)
  {
    delay(1);
  }
  audio_play.is_stop = false;
}

void Audio::waitStop(void)
{
  while(audio_play.is_busy)
  {
    delay(1);
  }
}

bool Audio::isBusy(void)
{
  return audio_play.is_busy;  
}

void Audio::setVolume(uint8_t vol)
{
  mp3.setVolume(vol);
}

bool wavplayStartFile(char *p_name)
{  
  bool started;
  uint8_t buf_i;

  File file = SPIFFS.open(p_name);
  if(!file)
  {
    Serial.println("Failed to open file for reading");
    return false;
  }


  file.read((uint8_t *)&wav_header, 44);


  audio_play.buffer_fmt.num_channels = wav_header.Fmt.NumChannels;
  audio_play.buffer_fmt.sample_rate = wav_header.Fmt.SampleRate;

  /*
  Serial.print("AudioFormat : ");          
  Serial.println(wav_header.Fmt.AudioFormat);          

  Serial.print("NumChannels : ");          
  Serial.println(wav_header.Fmt.NumChannels);          

  Serial.print("SampleRate : ");          
  Serial.println(wav_header.Fmt.SampleRate);          

  Serial.print("AvgByteRate : ");          
  Serial.println(wav_header.Fmt.AvgByteRate);          

  Serial.print("BlockAlign : ");          
  Serial.println(wav_header.Fmt.BlockAlign);          

  Serial.print("BitPerSample : ");          
  Serial.println(wav_header.Fmt.BitPerSample); 
  */

  file.read(audio_play.spk_buf[1], 512);

  memset(audio_play.spk_buf[1], 0 ,AUDIO_BUF_MAX);  
  speaker.start();
  speaker.write((char *)audio_play.spk_buf[1], AUDIO_BUF_MAX, &audio_play.buffer_fmt);     

  buf_i = 0;
  started = false;  
  while(1)
  {
    int length = file.available();

    if (length > AUDIO_BUF_MAX*1) length = AUDIO_BUF_MAX*1;
    if (length <= 0) break;

    file.read(audio_play.spk_buf[buf_i], length);

    if (started == false)
    {

      started = true;
    }
    speaker.write((char *)audio_play.spk_buf[buf_i], length, &bt_buffer_fmt);    
    delay(1);

    buf_i ^= 1;
    if (audio_play.is_stop == true)
    {
      speaker.stop();
      break;
    }
  }

  delay(100);
  speaker.stop();  

  file.close();  

  return true;
}

bool wavplayStartBuff(uint8_t *p_buff, uint32_t length_in)
{  
  bool started;
  uint8_t buf_i;
  int32_t index;


  audio_play.buffer_fmt.sample_rate = 8000;
  audio_play.buffer_fmt.bit_depth = I2S_BITS_PER_SAMPLE_16BIT;
  audio_play.buffer_fmt.num_channels = 1;

  buf_i = 0;
  started = false;  
  index = 0;
  while(1)
  {
    int length = length_in - index;

    if (length > AUDIO_BUF_MAX/2) length = AUDIO_BUF_MAX/2;
    if (length <= 0) break;

    for (int i=0; i<length*2; i+=4)
    {
      audio_play.spk_buf[buf_i][i + 0] = p_buff[index];
      audio_play.spk_buf[buf_i][i + 2] = p_buff[index];
      index++;
      audio_play.spk_buf[buf_i][i + 1] = p_buff[index];
      audio_play.spk_buf[buf_i][i + 3] = p_buff[index];
      index++;
    }

    if (started == false)
    {

      started = true;
    }
    speaker.write((char *)audio_play.spk_buf[buf_i], length*2, &bt_buffer_fmt);    
    delay(1);

    buf_i ^= 1;
    if (audio_play.is_stop == true)
    {
      speaker.stop();
      break;
    }
  }

  for (int i=0; i<AUDIO_BUF_MAX; i++)
  {
    audio_play.spk_buf[buf_i][i] = 0;
  }
  for (int i=0; i<4096/AUDIO_BUF_MAX; i++)
  {
    speaker.write((char *)audio_play.spk_buf[buf_i], AUDIO_BUF_MAX, &bt_buffer_fmt); 
    speaker.write((char *)audio_play.spk_buf[buf_i], AUDIO_BUF_MAX, &bt_buffer_fmt);   
  }

  return true;
}
