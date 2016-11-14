//
//  ADCenter.hpp
//  ColorGate
//
//  Created by xiaoming on 16/6/20.
//
//

#ifndef ADCenter_hpp
#define ADCenter_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class ADCenter : public Ref
{
public:
    static ADCenter * getInstance();
    ADCenter();
    ~ADCenter();
    void addFullScreen();
    void setBannerHide(bool hide);
    void userEvaluate();
private:
    bool addCanShow();
    int getAddShowNum();
    bool checkCanEvaluate();
};

#endif /* ADCenter_hpp */
