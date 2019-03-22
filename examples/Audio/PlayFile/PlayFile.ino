#include <EduBot.h>
/*
  이예제를 실행하기 위해서는 아래 링크의 방법을 이용해서 오디오 파일을 업로드 해야 합니다. 
  https://blog.naver.com/chcbaram/221416603068
*/



void setup() {
  // put your setup code here, to run once:
  
  edubot.begin(115200);     

  edubot.audio.playFile("/a.wav", false);
}

void loop() {
  // put your main code here, to run repeatedly
}

