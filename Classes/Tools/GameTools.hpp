//
//  GameTools.hpp
//  MagicSnake
//
//  Created by xiaoming on 15/12/9.
//
//

#ifndef GameTools_hpp
#define GameTools_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

enum SceneAnime
{
    TRAN_FADE,
    TRAN_WHITE,
    TRAN_ZOOM,
    TRAN_SHRINK,
};


class GameTools
{
public:
    static int getRandomNum(int min,int max);
    static std::string enCodeData(int value);
    static int deCodeData(std::string value);
    static void changeToScene(Scene *scene,SceneAnime anime);
    static int getCurrentTime();
    static std::string getFinalName(std::string nameData,int length);
    static std::string getStringByLength(std::string stringData,int length);
    static int getDeadNum();
    static void setDeadNum(int value);
};

#endif /* GameTools_hpp */
