//
//  MainScene.cpp
//  Chump
//
//  Created by xiaoming on 16/6/6.
//
//

#include "MainScene.hpp"
#include "GameSetting.h"
#include "GameTools.hpp"
#include "SoundPlayer.hpp"
#include "BattleScene.hpp"
#include "SettingScene.hpp"
Scene *MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}
bool MainScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    this->setMainScene();
    return true;
}


void MainScene::setMainScene()
{
    auto title = Label::createWithSystemFont("RUNNING BRICK", FONT_VERDANA, 60);
    this->addChild(title);
    title->setPosition(Vec2(WIDTH/2, HEIGHT-170));
    
    
    auto itemStart = MenuItemLabel::create(Label::createWithSystemFont("START", FONT_VERDANA, 52), CC_CALLBACK_1(MainScene::onStartClick, this));
    auto itemHelp = MenuItemLabel::create(Label::createWithSystemFont("HELP", FONT_VERDANA, 52), CC_CALLBACK_1(MainScene::onHelpClick, this));
    auto itemAbout = MenuItemLabel::create(Label::createWithSystemFont("ABOUT", FONT_VERDANA, 52), CC_CALLBACK_1(MainScene::onAboutClick, this));
    
    itemStart->setPosition(Vec2(0, -HEIGHT/8));
    itemHelp->setPosition(Vec2(0, 2*-HEIGHT/8));
    itemAbout->setPosition(Vec2(0, 3*-HEIGHT/8));
    
    //RANK BUTTON
    auto itemRank=MenuItemImage::create("btnRankNormal.png", "btnRankPressed.png", CC_CALLBACK_1(MainScene::onRankClick, this));
    itemRank->setPosition(Vec2(-WIDTH/2+45, -HEIGHT/2+45));
    soundOn=MenuItemImage::create("btnSoundOn.png", "btnSoundOnPressed.png", CC_CALLBACK_1(MainScene::soundOffClick, this));
    soundOff=MenuItemImage::create("btnSoundOff.png", "btnSoundOffPressed.png", CC_CALLBACK_1(MainScene::soundOnClick, this));
    soundOn->setPosition(Vec2(WIDTH/2-45, -HEIGHT/2+45));
    soundOff->setPosition(Vec2(WIDTH/2-45, -HEIGHT/2+45));
    this->updateSoundSwitch(SoundPlayer::getSoundSwitch());
    
    Menu *menu = Menu::create(itemStart,itemHelp,itemAbout,soundOn,soundOff,itemRank,NULL);
    this->addChild(menu);
    
    
}

void MainScene::onStartClick(Ref *ref)
{
    SoundPlayer::btnPress();
    auto scene = BattleScene::createScene();
    GameTools::changeToScene(scene, TRAN_FADE);
}
void MainScene::onHelpClick(Ref *ref)
{
    SoundPlayer::btnPress();
//    auto scene = HelpScene::createScene();
//    GameTools::changeToScene(scene, TRAN_FADE);
}
void MainScene::onAboutClick(Ref *ref)
{
    SoundPlayer::btnPress();
    auto scene = SettingScene::createScene();
    GameTools::changeToScene(scene, TRAN_FADE);
}

void MainScene::onRankClick(Ref *ref)
{
    //ADCenter::getInstance()->showGameRank();
}

void MainScene::soundOnClick(Ref *ref)
{
    SoundPlayer::soundOn();
    SoundPlayer::btnPress();
    this->updateSoundSwitch(true);
}
void MainScene::soundOffClick(Ref *ref)
{
    SoundPlayer::soundOff();
    this->updateSoundSwitch(false);
}

void MainScene::updateSoundSwitch(bool soundOn)
{
    this->soundOn->setVisible(soundOn);
    this->soundOff->setVisible(!soundOn);
}