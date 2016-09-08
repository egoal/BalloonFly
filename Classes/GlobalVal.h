#ifndef _GLOBAL_VAL_H_
#define _GLOBAL_VAL_H_
#include "SimpleAudioEngine.h"

#define HIGHEST_SCORE "HighestScore"
#define FIRST_TRY "FirstTry"

#define PLAY_MUSIC "PlayMusic"
#define PLAY_SOUND "PlaySound"
extern bool playMusic;
extern bool playSound;
#define MUSIC_THEME "ThemeMusic.mp3"
#define MUSIC_GAME "InGameMusic.mp3"
#define SOUND_BUTTON "ButtonPressed.wav"
#define SOUND_BALLOON_HURTED "BalloonHited.wav"
#define SOUND_BALLOON_FALLEN "BalloonFallen.mp3"
#define SOUND_SBIRD "SBirdHurted.wav"
#define SOUND_RBIRD "RBirdHurted.wav"
#define SOUND_TOOLGET "ToolGet.wav"

#define PLAY_BUTTONSOUND CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_BUTTON)

#endif