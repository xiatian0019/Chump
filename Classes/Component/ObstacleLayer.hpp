//
//  ObstacleLayer.hpp
//  Chump
//
//  Created by xiaoming on 16/6/1.
//
//

#ifndef ObstacleLayer_hpp
#define ObstacleLayer_hpp

#include <stdio.h>
#include "ObstacleStage.hpp"

class ObstacleLayer : public Layer
{
public:
    CREATE_FUNC(ObstacleLayer);
    bool init();
    void setActive(bool value);
    bool getActive();
    void setStageNum(int value);
    int getStageNum();
    float getCurrStagePosY();
    void resetObstacleLayer();
    void setLayerMoving(bool value);
    bool getLayerMoving();
private:
    bool active;
    int stageNum;
    int stageNumMax;
    bool layerMoving;
};


#endif /* ObstacleLayer_hpp */
