//
//  Hero.hpp
//  Chump
//
//  Created by xiaoming on 16/6/1.
//
//

#ifndef Hero_hpp
#define Hero_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class Hero : public Node
{
public:
    CREATE_FUNC(Hero);
    bool init();
    void setJumpCount(int value);
    int getJumpCount();
    Vec2 getHeroPosNextSec(float dt);
    void heroFall(float dt);
    void heroRotate(float dt);
    void setDirection(int value);
    int getDirection();
    void heroJump(bool smallJump);
    void heroOnGround();
private:
    int jumpCount;
    float gravity;
    float speedX;
    float speedY;
    int direction;
    float finalRotate;
    bool rotateOn;
    ui::Scale9Sprite *heroImage;
};

#endif /* Hero_hpp */
