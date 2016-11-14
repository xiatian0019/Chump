//
//  SoundPlayer.cpp
//  MagicSnake
//
//  Created by xiaoming on 16/1/15.
//
//

#include "SoundPlayer.hpp"
#include "cocos2d.h"
USING_NS_CC;
#include <SimpleAudioEngine.h>

static bool mainBgm = false;
static bool firstPlay = true;

void SoundPlayer::playEffect(std::string fileName)
{
    std::string soundName = fileName+".mp3";
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
}

void SoundPlayer::btnPress()
{
    if (!SoundPlayer::getSoundSwitch()) {
        return;
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pressed.wav");
}

void SoundPlayer::playMainBgm()
{
    if (mainBgm) {
        return;
    }
    mainBgm=true;
    if (!SoundPlayer::getSoundSwitch()) {
        return;
    }
    if (firstPlay) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        firstPlay=false;
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.8);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("mainBgm.mp3",true);
}
void SoundPlayer::playBattleBgm()
{
    if (!mainBgm) {
        return;
    }
    mainBgm=false;
    if (!SoundPlayer::getSoundSwitch()) {
        return;
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("battleBgm.mp3",true);
}


void SoundPlayer::soundOn()
{
    if (SoundPlayer::getSoundSwitch()) {
        return;
    }
    UserDefault::getInstance()->setBoolForKey("SoundSwitch", true);
    UserDefault::getInstance()->flush();
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    
}
void SoundPlayer::soundOff()
{
    if (!SoundPlayer::getSoundSwitch()) {
        return;
    }
    UserDefault::getInstance()->setBoolForKey("SoundSwitch", false);
    UserDefault::getInstance()->flush();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundPlayer::effectOn()
{
    if (SoundPlayer::getEffectSwitch()) {
        return;
    }
    UserDefault::getInstance()->setBoolForKey("EffectSwitch", true);
    UserDefault::getInstance()->flush();
}
void SoundPlayer::effectOff()
{
    if (!SoundPlayer::getEffectSwitch()) {
        return;
    }
    UserDefault::getInstance()->setBoolForKey("EffectSwitch", false);
    UserDefault::getInstance()->flush();
}

bool SoundPlayer::getSoundSwitch()
{
    bool soundSwitch = UserDefault::getInstance()->getBoolForKey("SoundSwitch", true);
    UserDefault::getInstance()->flush();
    return soundSwitch;
}

bool SoundPlayer::getEffectSwitch()
{
    bool effectSwitch = UserDefault::getInstance()->getBoolForKey("EffectSwitch", true);
    UserDefault::getInstance()->flush();
    return effectSwitch;
}

