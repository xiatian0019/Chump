//
//  MainScene.hpp
//  Chump
//
//  Created by xiaoming on 16/6/6.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class MainScene : public Layer
{
public:
    CREATE_FUNC(MainScene);
    static Scene *createScene();
    bool init();
private:
    void onStartClick(Ref *ref);
    void onHelpClick(Ref *ref);
    void onAboutClick(Ref *ref);
    void onRankClick(Ref *ref);
    MenuItemImage *soundOn;
    MenuItemImage *soundOff;
    void soundOnClick(Ref *ref);
    void soundOffClick(Ref *ref);
    void updateSoundSwitch(bool soundOn);
    void setMainScene();
};


#endif /* MainScene_hpp */
