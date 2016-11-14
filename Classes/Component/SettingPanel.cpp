//
//  SettingPanel.cpp
//  Chump
//
//  Created by xiaoming on 16/7/25.
//
//

#include "SettingPanel.hpp"
#include "GameSetting.h"
#include "SoundPlayer.hpp"

bool SettingPanel::init()
{
    if (!Layer::init()) {
        return false;
    }
    backSp = ui::Scale9Sprite::create("frame.png");
    backSp->setContentSize(Size(500, 800));
    this->addChild(backSp);
    backSp->setPosition(Vec2(WIDTH/2, HEIGHT/2));
    this->addLabel("SET UP", backSp, Vec2(backSp->getContentSize().width/2, 133*5));
    this->addLabel("MUSIC", backSp, Vec2(backSp->getContentSize().width/3, 133*4));
    this->addLabel("EFFECT", backSp, Vec2(backSp->getContentSize().width/3, 399));
    this->addLabel("LIST", backSp, Vec2(backSp->getContentSize().width/2, 266));
    this->addLabel("BACK BUY", backSp, Vec2(backSp->getContentSize().width/2, 133));
    myDelegate=NULL;
    this->openTouchEvent();
    
    
    btnSoundOn = this->addBtn(false, 1);
    btnSoundOff = this->addBtn(true, 2);
    btnEffectOn = this->addBtn(false, 3);
    btnEffectOff = this->addBtn(true,4);
    
    auto menu = Menu::create(btnSoundOn,btnSoundOff,btnEffectOn,btnEffectOff,NULL);
    backSp->addChild(menu);
    menu->setPosition(Vec2(0, 0));
    
    btnSoundOn->setPosition(Vec2(backSp->getContentSize().width*2/3, 133*4));
    btnSoundOff->setPosition(btnSoundOn->getPosition());
    btnEffectOn->setPosition(Vec2(backSp->getContentSize().width*2/3, 399));
    btnEffectOff->setPosition(btnEffectOn->getPosition());

    
    this->updateBtnState();
    
    
    return true;
}

void SettingPanel::setDelegate(SettingPanelDelegate *delegate)
{
    myDelegate = delegate;
}

void SettingPanel::addLabel(std::string txt,Node *pareNode,Vec2 pos)
{
    auto label = Label::createWithSystemFont(txt, FONT_GEORGIA, 28);
    pareNode->addChild(label);
    label->setPosition(pos);
    label->setColor(Color3B(0, 0, 0));
}


void SettingPanel::openTouchEvent()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(SettingPanel::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(SettingPanel::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
bool SettingPanel::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void SettingPanel::onTouchEnded(Touch* touch, Event* event)
{
    if (backSp->getBoundingBox().containsPoint(touch->getLocation())==false) {
        if (myDelegate) {
            myDelegate->settingPanelClose();
        }
    }
}


MenuItemImage *SettingPanel::addBtn(bool stateOn,int tag)
{
    std::string fileName = "stateNormal.png";
    if (stateOn) {
        fileName = "stateSelected.png";
    }
    auto itemImage = MenuItemImage::create(fileName, fileName, CC_CALLBACK_1(SettingPanel::btnClick, this));
    itemImage->setTag(tag);
    itemImage->setScale(0.7);
    return itemImage;
}
void SettingPanel::btnClick(Ref *ref)
{
    int tag = ((Node *)ref)->getTag();
    CCLOG("pressTag:%d",tag);
    switch (tag) {
        case 1:
            SoundPlayer::soundOn();
            break;
        case 2:
            SoundPlayer::soundOff();
            break;
        case 3:
            SoundPlayer::effectOn();
            break;
        case 4:
            SoundPlayer::effectOff();
            break;
        default:
            break;
    }
    this->updateBtnState();
}


void SettingPanel::updateBtnState()
{
    auto soundSwitch = SoundPlayer::getSoundSwitch();
    btnSoundOn->setVisible(!soundSwitch);
    btnSoundOff->setVisible(soundSwitch);
    
    auto effectSwitch = SoundPlayer::getEffectSwitch();
    btnEffectOn->setVisible(!effectSwitch);
    btnEffectOff->setVisible(effectSwitch);
}