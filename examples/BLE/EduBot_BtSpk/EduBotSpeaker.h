#ifndef _EDUBOTSPEAKER_H_
#define _EDUBOTSPEAKER_H_


#include "Arduino.h"


#include "./src/bt_speaker/bt_speaker.h"


class EduBotSpeaker
{
  public:
    EduBotSpeaker();
    ~EduBotSpeaker();    

    void begin(char *speaker_name);
    bool isConnected(void);
    bool isPlaying(void);

  private:    
    renderer_config_t *renderer_config;
};


#endif

