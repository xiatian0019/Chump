//
//  ObstacleStage.cpp
//  Chump
//
//  Created by xiaoming on 16/6/1.
//
//

#include "ObstacleStage.hpp"

#include "GameSetting.h"
#include "Obstacle.hpp"
#include "GameTools.hpp"
ObstacleStage::ObstacleStage()
{
    Node::init();
    this->setContentSize(Size(WIDTH, STAGE_HEIGHT*GAME_SCALE));
    auto ground = ui::Scale9Sprite::create("stageGround.png");
    ground->setContentSize(Size(WIDTH, STAGE_GROUND_HEIGHT*GAME_SCALE));
    ground->setAnchorPoint(Vec2(0, 0));
    ground->setColor(Color3B(245, 222, 179));
    this->addChild(ground);
//    for (int i=0; i<4; i++) {
//        this->addObstacle(i);
//    }
    

    //int obstaclePos = GameTools::getRandomNum(1, 1000);
    
    this->addObstacle(0);
    
//    if (obstaclePos%2==0) {
//        this->addObstacle(1);
//        this->addObstacle(3);
//    }
//    else{
//        this->addObstacle(0);
//        this->addObstacle(2);
//    }
    this->autorelease();
}
ObstacleStage::~ObstacleStage()
{
    
}


void ObstacleStage::addObstacle(int stageId)
{
    auto boxList = Obstacle::getObstacle();
    int boxSize = (int)boxList.size();
    for (int i=0; i<boxSize; i++) {
        int boxNum = boxList.at(i);
        if (boxNum==0) {
            continue;
        }
        if (boxNum>0) {
            for (int j=0; j<boxNum; j++) {
                this->addBox(Vec2((stageId*boxSize+i)*BOX_SIZE*GAME_SCALE, j*BOX_SIZE*GAME_SCALE+STAGE_GROUND_HEIGHT*GAME_SCALE));
            }
        }
        else{
            for (int j=0; j>boxNum; j--) {
                this->addBox(Vec2((stageId*boxSize+i)*BOX_SIZE*GAME_SCALE, (9+j)*BOX_SIZE*GAME_SCALE+STAGE_GROUND_HEIGHT*GAME_SCALE));
            }
        }
    }
}

void ObstacleStage::addBox(Vec2 boxPoint)
{
    auto box = ui::Scale9Sprite::create("stageGround.png");
    box->setContentSize(Size(BOX_SIZE*GAME_SCALE, BOX_SIZE*GAME_SCALE));
    box->setAnchorPoint(Vec2(0, 0));
    box->setColor(Color3B(245, 222, 179));
    this->addChild(box);
    box->setPosition(boxPoint);
    boxList.push_back(box);
}
std::vector<Node *>*ObstacleStage::getBoxList()
{
    return &boxList;
}