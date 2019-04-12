
#include "face/FaceSmile.h"
#include "face/FaceLeft.h"
#include "face/FaceRight.h"
#include "face/FaceSpeak.h"
#include "face/FaceSleep.h"
#include "face/FaceSad.h"

typedef enum
{
	IDLE,
	SLEEP, 
	SMILE, 
	LEFT, 
	RIGHT,
	SPEAKER,
	SAD1,
	SAD2 
} face_t;

