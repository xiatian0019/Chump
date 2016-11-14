//
//  Hero.cpp
//  Chump
//
//  Created by xiaoming on 16/6/1.
//
//

#include "Hero.hpp"
#include "GameSetting.h"
#include "GameController.hpp"


bool Hero::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setContentSize(Size(BOX_SIZE*GAME_SCALE, BOX_SIZE*GAME_SCALE));
    heroImage = ui::Scale9Sprite::create("stageGround.png");
    heroImage->setContentSize(this->getContentSize());
    //ground->setColor(Color3B(245, 222, 179));
    this->addChild(heroImage);
    heroImage->setPosition(Vec2(heroImage->getContentSize().width/2, heroImage->getContentSize().height/2));
    direction=1;
    speedX=GameController::getInstance()->getHorSpeed();
    speedY=0;
    gravity=GameController::getInstance()->getGravity();
    finalRotate=0;
    rotateOn=false;
    return true;
}

void Hero::heroJump(bool smallJump)
{
    int jumpStep=1;
    float jumpHeight=GameController::getInstance()->getJumpSpeedSmall();
    if (!smallJump) {
        jumpHeight=GameController::getInstance()->getJumpSpeedBig();
        jumpStep=2;
    }
    jumpCount=jumpCount+jumpStep;
    if (jumpCount>2) {
        return;
    }
    rotateOn=true;
    finalRotate = finalRotate+180*direction;
    speedY=jumpHeight;
}

void Hero::heroOnGround()
{
    speedY=0;
    jumpCount=0;
}


Vec2 Hero::getHeroPosNextSec(float dt)
{
    float posX=this->getPositionX()+speedX*dt*direction;
    float posY=this->getPositionY()+speedY*dt;
    return Vec2(posX, posY);
}

void Hero::heroFall(float dt)
{
    speedY=speedY-gravity*dt;
}

void Hero::heroRotate(float dt)
{
    if (!rotateOn) {
        return;
    }
    float rotateDif = GameController::getInstance()->getRotateSpeed()*dt;
    if (fabsf(heroImage->getRotation()-finalRotate)<1) {
        heroImage->setRotation(finalRotate);
        rotateOn=false;
    }
    else{
        if (heroImage->getRotation()<finalRotate) {
            heroImage->setRotation(heroImage->getRotation()+rotateDif);
        }
        else{
            heroImage->setRotation(heroImage->getRotation()-rotateDif);
        }
    }
}


void Hero::setJumpCount(int value)
{
    jumpCount=value;
}
int Hero::getJumpCount()
{
    return jumpCount;
}
void Hero::setDirection(int value)
{
    direction=value;
}
int Hero::getDirection()
{
    return direction;
}