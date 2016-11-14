//
//  ObstacleStage.hpp
//  Chump
//
//  Created by xiaoming on 16/6/1.
//
//

#ifndef ObstacleStage_hpp
#define ObstacleStage_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ObstacleStage : public Node
{
public:
    ObstacleStage();
    ~ObstacleStage();
    std::vector<Node *>*getBoxList();
private:
    void addObstacle(int stageId);
    void addBox(Vec2 boxPoint);
    std::vector<Node *>boxList;
};


#endif /* ObstacleStage_hpp */
