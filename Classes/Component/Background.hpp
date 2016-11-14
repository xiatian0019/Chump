//
//  Background.hpp
//  Chump
//
//  Created by xiaoming on 16/7/18.
//
//

#ifndef Background_hpp
#define Background_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class BackGround : public Layer
{
public:
    CREATE_FUNC(BackGround);
    bool init();
    void groundMove(float moveDif);
private:
    std::vector<Sprite *>imageList;
    void updateImage();
    Sprite *getTargetSprite(int index);
};

#endif /* Background_hpp */
