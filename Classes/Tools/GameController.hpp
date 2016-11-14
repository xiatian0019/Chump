//
//  GameController.hpp
//  Chump
//
//  Created by xiaoming on 16/7/1.
//
//

#ifndef GameController_hpp
#define GameController_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;





class GameController : public Ref
{
public:
    static GameController *getInstance();
    GameController();
    ~GameController();
    void setJumpSpeedSmall(float value);
    void setJumpSpeedBig(float value);
    void setHorSpeed(float value);
    void setGravity(float value);
    void setStageSpeed(float value);
    void setSmallJumpTime(float value);
    void setRotateSpeed(float value);
    
    float getJumpSpeedSmall();
    float getJumpSpeedBig();
    float getHorSpeed();
    float getGravity();
    float getStageSpeed();
    float getSmallJumpTime();
    float getRotateSpeed();
    void resetData();
    int getTopScore();
    void setTopScore(int value);
private:
    float jumpSpeedSmall;
    float jumpSpeedBig;
    float horSpeed;
    float gravity;
    float stageSpeed;
    float smallJumpTime;
    float rotateSpeed;
    
    float getDataByKey(std::string key,float defaultValue);
    void setDataByKey(std::string key,float value);
    
    void saveData();
    
    int topScore;
    
    
};

#endif /* GameController_hpp */
