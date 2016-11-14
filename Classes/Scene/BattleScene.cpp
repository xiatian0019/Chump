//
//  BattleScene.cpp
//  Chump
//
//  Created by xiaoming on 16/6/1.
//
//

#include "BattleScene.hpp"
#include "GameSetting.h"
#include "GameTools.hpp"
#include "GameController.hpp"
#include "MainScene.hpp"
#include "ADCenter.hpp"
#include "SettingPanel.hpp"

Scene *BattleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = BattleScene::create();
    scene->addChild(layer);
    return scene;
}
bool BattleScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    backGround = BackGround::create();
    this->addChild(backGround);
    
    stageLayer1=NULL;
    stageLayer2=NULL;
    hero=NULL;
    
    labelScore = Label::createWithSystemFont("SCORE:0", FONT_VERDANA, 40);
    labelScore->setAnchorPoint(Vec2(0.5, 1));
    this->addChild(labelScore);
    labelScore->setPosition(Vec2(WIDTH/2, HEIGHT-50));
    
    
    deadNum = GameTools::getDeadNum();
    labelDead = Label::createWithSystemFont("DEAD:0", FONT_VERDANA, 40);
    labelDead->setAnchorPoint(Vec2(0, 1));
    this->addChild(labelDead);
    labelDead->setPosition(Vec2(35, HEIGHT-35));
    labelDead->setVisible(false);

    mySettingPanel=NULL;
    topScore = GameController::getInstance()->getTopScore();
    
    
    btnSetting = MenuItemImage::create("btnRankNormal.png", "btnRankNormal.png", CC_CALLBACK_1(BattleScene::backClick, this));
    auto menu = Menu::create(btnSetting, NULL);
    this->addChild(menu);
    btnSetting->setPosition(Vec2(30-WIDTH/2, HEIGHT/2-30));
    
    
    this->resetGame();
    this->openTouchEvent();
    this->schedule(schedule_selector(BattleScene::onFrame));
    return true;
}


void BattleScene::backClick(Ref *ref)
{
//    auto scene = MainScene::createScene();
//    GameTools::changeToScene(scene, TRAN_FADE);
    if (mySettingPanel==NULL) {
        mySettingPanel = SettingPanel::create();
        this->addChild(mySettingPanel);
        mySettingPanel->setDelegate(this);
    }
}


void BattleScene::settingPanelClose()
{
    if (mySettingPanel) {
        mySettingPanel->removeFromParent();
        mySettingPanel=NULL;
    }
}

void BattleScene::resetGame()
{
    if (stageLayer1) {
        stageLayer1->removeFromParent();
        stageLayer2->removeFromParent();
    }
    stageLayer1 = ObstacleLayer::create();
    stageLayer2 = ObstacleLayer::create();
    this->addChild(stageLayer1);
    this->addChild(stageLayer2);
    float initialDif = HEIGHT-((int)(HEIGHT/(STAGE_HEIGHT*GAME_SCALE)))*(STAGE_HEIGHT*GAME_SCALE);
    stageLayer1->setPositionY(-(stageLayer1->getContentSize().height-HEIGHT+initialDif));
    stageLayer1->setActive(true);
    stageLayer2->setPositionY(stageLayer1->getPositionY()-stageLayer2->getContentSize().height);
    hero=Hero::create();
    this->addChild(hero);
    
    auto activeLayer = this->getCurrentStageLayer();
    float stagePosY = activeLayer->getCurrStagePosY();
    
    hero->setPosition(Vec2(0, stagePosY));
    touchTime=0;
    touchLock=false;
    gameRunning=false;
    score=0;
    this->updateLabelScore();
    this->updateDeadLabel();
}
void BattleScene::gameStart()
{
    btnSetting->setVisible(false);
    gameRunning=true;
    this->updateLabelScore();
}

void BattleScene::updateLabelScore()
{
    if (gameRunning) {
        labelScore->setString("SCORE:"+Value(score).asString());
    }
    else{
        labelScore->setString("TopScore:"+Value(topScore).asString());
    }
    
}

void BattleScene::updateDeadLabel()
{
    labelDead->setString("DEAD:"+Value(deadNum).asString());
}

void BattleScene::onFrame(float dt)
{
    if (!gameRunning) {
        return;
    }
    if (!this->checkingHero()) {
        this->gameOver();
        return;
    }
    if (touchLock) {
        touchTime=touchTime+dt;
        if (touchTime>GameController::getInstance()->getSmallJumpTime()) {
            hero->heroJump(false);
            touchLock=false;
        }
    }
    this->heroMove(dt);
}

void BattleScene::gameOver()
{
    gameRunning=false;
    this->addExplosionEffect(hero->getPosition());
    hero->removeFromParent();
    hero=NULL;
    deadNum++;
    this->updateDeadLabel();
    GameTools::setDeadNum(deadNum);
    btnSetting->setVisible(true);
    
    if (topScore<score) {  //破纪录
        topScore = score;
        GameController::getInstance()->setTopScore(topScore);
    }
    this->updateLabelScore();
    
    ADCenter::getInstance()->addFullScreen();
}

bool BattleScene::checkingHero()
{
    bool heroAlive=true;
    auto activeLayer = this->getCurrentStageLayer();
    auto stage = (ObstacleStage *)activeLayer->getChildByTag(activeLayer->getStageNum());
    auto boxList = stage->getBoxList();
    for (int i=0; i<boxList->size(); i++) {
        auto box = boxList->at(i);
        Vec2 worldPoint = (box->getParent())->convertToWorldSpace(box->getPosition());
        auto boxRect = Rect(worldPoint.x, worldPoint.y, BOX_SIZE*GAME_SCALE, BOX_SIZE*GAME_SCALE);
        if (boxRect.intersectsRect(hero->getBoundingBox())) {
            heroAlive=false;
            break;
        }
    }
    return heroAlive;
}

void BattleScene::heroMove(float dt)
{
    if (!hero) {
        return;
    }
    auto activeLayer = this->getCurrentStageLayer();
    float stagePosY = activeLayer->getCurrStagePosY();
    Vec2 nextPos = hero->getHeroPosNextSec(dt);
    if (nextPos.y<=stagePosY) {
        nextPos.y=stagePosY;
        hero->heroOnGround();
    }
    else{
        hero->heroFall(dt);
    }
    hero->heroRotate(dt);
    hero->setPosition(nextPos);
    if (hero->getPositionX()<-1 || hero->getPositionX()>WIDTH+1) {
        this->heroGoNextStage();
    }
    this->stageMove(dt);
}

void BattleScene::stageMove(float dt)
{
    float moveDif = GameController::getInstance()->getStageSpeed()*dt;
    
    auto activeLayer = this->getCurrentStageLayer();
    float stagePosY = activeLayer->getCurrStagePosY();
    
    if (stagePosY<HEIGHT/2) {
        
        hero->setPositionY(hero->getPositionY()+moveDif);
        stageLayer1->setPositionY(stageLayer1->getPositionY()+moveDif);
        stageLayer2->setPositionY(stageLayer2->getPositionY()+moveDif);
        this->updateStageLayer(stageLayer1, stageLayer2);
        this->updateStageLayer(stageLayer2, stageLayer1);
        
        backGround->groundMove(moveDif);
    }
    
    
    
//    if (hero->getPositionY()<HEIGHT/2) {
//        if (hero->getPositionY()+moveDif>HEIGHT/2) {
//            moveDif=HEIGHT/2-hero->getPositionY();
//        }
//        hero->setPositionY(hero->getPositionY()+moveDif);
//        stageLayer1->setPositionY(stageLayer1->getPositionY()+moveDif);
//        stageLayer2->setPositionY(stageLayer2->getPositionY()+moveDif);
//        this->updateStageLayer(stageLayer1, stageLayer2);
//        this->updateStageLayer(stageLayer2, stageLayer1);
//    }
}

void BattleScene::updateStageLayer(ObstacleLayer *stageLayer1,ObstacleLayer *stageLayer2)
{
    if (stageLayer1->getPositionY()>HEIGHT) {
        stageLayer1->resetObstacleLayer();
        stageLayer1->setPositionY(stageLayer2->getPositionY()-stageLayer1->getContentSize().height);
    }
}

void BattleScene::heroGoNextStage()
{
    score++;
    this->updateLabelScore();
    if (this->checkStageOver(stageLayer1)) {
        stageLayer2->setActive(true);
    }
    else if (this->checkStageOver(stageLayer2)) {
        stageLayer1->setActive(true);
    }
    auto activeLayer = this->getCurrentStageLayer();
    CCLOG("currentStage:%d",activeLayer->getStageNum());
    float stagePosY = activeLayer->getCurrStagePosY();
    float posX=-1;
    if (hero->getDirection()==1) {
        posX=WIDTH+1;
    }
    hero->setDirection(hero->getDirection()*-1);
    //direction=direction*-1;
    hero->setPosition(Vec2(posX, stagePosY));
}

bool BattleScene::checkStageOver(ObstacleLayer *stageLayer)
{
    if (!stageLayer->getActive()) {
        return false;
    }
    if (stageLayer->getStageNum()==0) {
        stageLayer->setActive(false);
        return true;
    }
    stageLayer->setStageNum(stageLayer->getStageNum()-1);
    return false;
}


ObstacleLayer * BattleScene::getCurrentStageLayer()
{
    auto stageLayer = stageLayer1;
    if (!stageLayer->getActive()) {
        stageLayer = stageLayer2;
    }
    return stageLayer;
}


void BattleScene::openTouchEvent()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(BattleScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(BattleScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
bool BattleScene::onTouchBegan(Touch* touch, Event* event)
{
    if (touchLock) {
        return false;
    }
    touchLock=true;
    touchTime=0;
    return true;;
}
void BattleScene::onTouchEnded(Touch* touch, Event* event)
{
    if (!gameRunning) {
        if (hero==NULL) {
            this->resetGame();
        }
        this->gameStart();
    }
    else{
        if (touchTime>MAX_JUMP_TIME) {
            touchLock=false;
            return;
        }
        if (touchTime<GameController::getInstance()->getSmallJumpTime()) {
            hero->heroJump(true);
        }
        touchLock=false;
    }
    
    
}


void BattleScene::addExplosionEffect(Vec2 point)
{
    std::string fileName="boxBreak.plist";
    ParticleSystemQuad *effect = ParticleSystemQuad::create(fileName);
    auto scene =Director::getInstance()->getRunningScene();
    if (scene) {
        scene->addChild(effect,1000);
    }
    effect->setAutoRemoveOnFinish(true);
    effect->setPosition(point);
}
