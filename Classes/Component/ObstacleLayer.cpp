//
//  ObstacleLayer.cpp
//  Chump
//
//  Created by xiaoming on 16/6/1.
//
//

#include "ObstacleLayer.hpp"
#include "GameSetting.h"

bool ObstacleLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    float stageMax = HEIGHT/(STAGE_HEIGHT*GAME_SCALE);
    stageNumMax = (int)stageMax+1;
    this->setContentSize(Size(WIDTH, STAGE_HEIGHT*stageNumMax*GAME_SCALE));
    this->resetObstacleLayer();
    layerMoving=false;
    return true;
}

void ObstacleLayer::resetObstacleLayer()
{
    this->removeAllChildren();
    int stageNumber = stageNumMax;
    for (int i=0; i<stageNumber; i++) {
        auto stage = new ObstacleStage();
        this->addChild(stage);
        stage->setPosition(Vec2(0, i*STAGE_HEIGHT*GAME_SCALE));
        stage->setTag(i);
    }
    stageNum=stageNumber-1;
    active=false;
}

void ObstacleLayer::setActive(bool value)
{
    active=value;
}
bool ObstacleLayer::getActive()
{
    return active;
}

void ObstacleLayer::setStageNum(int value)
{
    stageNum=value;
}
int ObstacleLayer::getStageNum()
{
    return stageNum;
}

float ObstacleLayer::getCurrStagePosY()
{
    Vec2 worldPoint = this->convertToWorldSpace(Vec2(0, stageNum*STAGE_HEIGHT*GAME_SCALE));
    return worldPoint.y+STAGE_GROUND_HEIGHT*GAME_SCALE;
}

void ObstacleLayer::setLayerMoving(bool value)
{
    layerMoving=value;
}
bool ObstacleLayer::getLayerMoving()
{
    return layerMoving;
}