//
//  ADCenter.cpp
//  ColorGate
//
//  Created by xiaoming on 16/6/20.
//
//

#include "ADCenter.hpp"
#import "RootViewController.h"
#import "AppController.h"
#include "GameTools.hpp"
#include "GameSetting.h"

static ADCenter *adCenter = NULL;


ADCenter * ADCenter::getInstance()
{
    if (adCenter==NULL) {
        adCenter = new ADCenter();
//        RootViewController * vc = (RootViewController*)[UIApplication sharedApplication].keyWindow.rootViewController;
//        [vc loadAdInstl];
        
    }
    return adCenter;
}
ADCenter::ADCenter()
{
    
}
ADCenter::~ADCenter()
{
    
}
void ADCenter::addFullScreen()
{
    if (this->addCanShow()) {
//        RootViewController * vc = (RootViewController*)[UIApplication sharedApplication].keyWindow.rootViewController;
//        [vc showAdInstl];
    }
}

void ADCenter::setBannerHide(bool hide)
{
    // hide banner
    
    
//    RootViewController * vc = (RootViewController*)[UIApplication sharedApplication].keyWindow.rootViewController;
//    [vc setBannerHide:hide];
}


bool ADCenter::addCanShow()
{
    return true;
}


int ADCenter::getAddShowNum()
{
    int currentTime=GameTools::getCurrentTime();
    int today=UserDefault::getInstance()->getIntegerForKey("Today", -1);
    if (currentTime!=today) {
        UserDefault::getInstance()->setIntegerForKey("Today", currentTime);
        UserDefault::getInstance()->setIntegerForKey("AddTime", 0);
    }
    int addTime = UserDefault::getInstance()->getIntegerForKey("AddTime", 0);
    UserDefault::getInstance()->flush();
    return addTime;
}




void ADCenter::userEvaluate()
{
    //用户评分
    
//    if (this->checkCanEvaluate()) {
//        AppController *appController= (AppController *)[UIApplication sharedApplication].delegate;
//        [appController showGradePanel];
//    }
}


bool ADCenter::checkCanEvaluate()
{
    bool userEvaluated=UserDefault::getInstance()->getBoolForKey("Evaluated", false);
    int refuseNum=UserDefault::getInstance()->getIntegerForKey("GradeRefuseNum", 0);
    UserDefault::getInstance()->flush();
    if (userEvaluated||refuseNum>=GRADE_REFUSE_NUM) {
        return false;
    }
    int evaluatedDay=UserDefault::getInstance()->getIntegerForKey("evaluatedDay", -1);
    int currentTime=GameTools::getCurrentTime();
    if (evaluatedDay>currentTime||evaluatedDay==-1) {
        evaluatedDay=currentTime;
        UserDefault::getInstance()->setIntegerForKey("evaluatedDay", currentTime);
        evaluatedDay=0;
    }
    else{
        evaluatedDay=currentTime-evaluatedDay;
    }
    int evaluatedOpen=UserDefault::getInstance()->getIntegerForKey("evaluatedOpen", 0);
    
    bool canEvaluate=false;
    if (evaluatedOpen>=10||evaluatedDay>=3) {
        UserDefault::getInstance()->setIntegerForKey("evaluatedDay", currentTime);
        UserDefault::getInstance()->setIntegerForKey("evaluatedOpen", 0);
        canEvaluate=true;
    }
    UserDefault::getInstance()->flush();
    return canEvaluate;
}

