//
//  Obstacle.hpp
//  Chump
//
//  Created by xiaoming on 16/6/3.
//
//

#ifndef Obstacle_hpp
#define Obstacle_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class Obstacle : public Ref
{
public:
    static std::vector<int> getObstacle(int obstacleId=-1);
private:
    static std::string getObstacleData(int index);
};

#endif /* Obstacle_hpp */
