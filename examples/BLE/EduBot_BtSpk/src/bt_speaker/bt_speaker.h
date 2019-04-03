/*
 * a2dp.h
 *
 *  Created on: 07.05.2017
 *      Author: michaelboeckling
 */

#ifndef _INCLUDE_BT_SPEAKER_H_
#define _INCLUDE_BT_SPEAKER_H_


#ifdef __cplusplus
 extern "C" {
#endif

#include "../audio_renderer/audio_renderer.h"

void bt_speaker_start(renderer_config_t *renderer_config);

#ifdef __cplusplus
 }
#endif

#endif /* _INCLUDE_BT_SPEAKER_H_ */
