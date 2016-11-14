//
//  GameController.cpp
//  Chump
//
//  Created by xiaoming on 16/7/1.
//
//
#include "GameController.hpp"
#include "GameSetting.h"

#define HERO_JUMP_SPEED_SMALL    550   //小跳跃高度
#define HERO_JUMP_SPEED_BIG      600  //大跳跃高度
#define HORIZONTAL_SPEED   300         //每秒水平移动像素
#define GRAVITY     2000               //重力，每秒垂直速度降低
#define STAGE_MOVE_SPEED   300         //障碍物上移速度（保持主角在屏幕中央）
#define SMALL_JUMP_TIME     0.15       //点击多少秒后开始大跳
#define HERO_ROTATE_SPEED   500



static GameController *gameController=NULL;

GameController *GameController::getInstance()
{
    if (gameController==NULL) {
        gameController = new GameController();
    }
    return gameController;
}
GameController::GameController()
{
    jumpSpeedSmall = this->getDataByKey("jumpSpeedSmall", HERO_JUMP_SPEED_SMALL);
    jumpSpeedBig = this->getDataByKey("jumpSpeedBig", HERO_JUMP_SPEED_BIG);
    horSpeed = this->getDataByKey("horSpeed", HORIZONTAL_SPEED);
    gravity = this->getDataByKey("gravity", GRAVITY);
    stageSpeed = this->getDataByKey("stageSpeed", STAGE_MOVE_SPEED);
    smallJumpTime = this->getDataByKey("smallJumpTime", SMALL_JUMP_TIME);
    rotateSpeed = this->getDataByKey("rotateSpeed", HERO_ROTATE_SPEED);
    topScore =(int)this->getDataByKey("TopScore", 0);
    
    
}
GameController::~GameController()
{
    
}

void GameController::resetData()
{
    jumpSpeedSmall = HERO_JUMP_SPEED_SMALL;
    jumpSpeedBig = HERO_JUMP_SPEED_BIG;
    horSpeed = HORIZONTAL_SPEED;
    gravity = GRAVITY;
    stageSpeed = STAGE_MOVE_SPEED;
    smallJumpTime = SMALL_JUMP_TIME;
    rotateSpeed = HERO_ROTATE_SPEED;
    this->saveData();
}

void GameController::saveData()
{
    this->setDataByKey("jumpSpeedSmall", jumpSpeedSmall);
    this->setDataByKey("jumpSpeedBig", jumpSpeedBig);
    this->setDataByKey("horSpeed", horSpeed);
    this->setDataByKey("gravity", gravity);
    this->setDataByKey("stageSpeed", stageSpeed);
    this->setDataByKey("smallJumpTime", smallJumpTime);
    this->setDataByKey("rotateSpeed", rotateSpeed);

}

float GameController::getDataByKey(std::string key,float defaultValue)
{
    float value = UserDefault::getInstance()->getFloatForKey(key.c_str(), defaultValue);
    UserDefault::getInstance()->flush();
    return value;
}
void GameController::setDataByKey(std::string key,float value)
{
    UserDefault::getInstance()->setFloatForKey(key.c_str(), value);
    UserDefault::getInstance()->flush();
}


void GameController::setJumpSpeedSmall(float value)
{
    jumpSpeedSmall = value;
    this->saveData();
}
void GameController::setJumpSpeedBig(float value)
{
    jumpSpeedBig = value;
    this->saveData();
}
void GameController::setHorSpeed(float value)
{
    horSpeed = value;
    this->saveData();
}
void GameController::setGravity(float value)
{
    gravity = value;
    this->saveData();
}
void GameController::setStageSpeed(float value)
{
    stageSpeed = value;
    this->saveData();
}
void GameController::setSmallJumpTime(float value)
{
    smallJumpTime = value;
    this->saveData();
}
void GameController::setRotateSpeed(float value)
{
    rotateSpeed = value;
    this->saveData();
}

float GameController::getJumpSpeedSmall()
{
    return jumpSpeedSmall;
}
float GameController::getJumpSpeedBig()
{
    return jumpSpeedBig;
}
float GameController::getHorSpeed()
{
    return horSpeed;
}
float GameController::getGravity()
{
    return gravity;
}
float GameController::getStageSpeed()
{
    return stageSpeed;
}
float GameController::getSmallJumpTime()
{
    return smallJumpTime;
}
float GameController::getRotateSpeed()
{
    return rotateSpeed;
}


int GameController::getTopScore()
{
    return topScore;
}
void GameController::setTopScore(int value)
{
    if (value>topScore) {
        topScore = value;
        this->setDataByKey("TopScore", (float)topScore);
    }
}