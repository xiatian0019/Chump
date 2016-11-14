//
//  SoundPlayer.hpp
//  MagicSnake
//
//  Created by xiaoming on 16/1/15.
//
//

#ifndef SoundPlayer_hpp
#define SoundPlayer_hpp

#include <stdio.h>

class SoundPlayer
{
public:
    static void playEffect(std::string fileName);
    static void btnPress();
    static void playMainBgm();
    static void playBattleBgm();
    static void soundOn();
    static void soundOff();
    static void effectOn();
    static void effectOff();
    static bool getSoundSwitch();
    static bool getEffectSwitch();
};

#endif /* SoundPlayer_hpp */
