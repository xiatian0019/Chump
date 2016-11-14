//
//  Background.cpp
//  Chump
//
//  Created by xiaoming on 16/7/18.
//
//

#include "Background.hpp"
#include "GameSetting.h"

bool BackGround::init()
{
    if (!Layer::init()) {
        return false;
    }
    for (int i=0; i<4; i++) {
        std::string fileName = "battleBack"+Value(i+1).asString()+".png";
        auto sp = Sprite::create(fileName);
        this->addChild(sp);
        sp->setAnchorPoint(Vec2(0, 0));
        sp->setPosition(Vec2(0, -i*sp->getContentSize().height));
        sp->setTag(i);
        imageList.push_back(sp);
    }
    return true;
}

void BackGround::groundMove(float moveDif)
{
    for (int i=0; i<imageList.size(); i++) {
        auto sp = imageList.at(i);
        sp->setPositionY(sp->getPositionY()+moveDif);
    }
    this->updateImage();
}


void BackGround::updateImage()
{
    for (int i=0; i<imageList.size(); i++) {
        auto sp = imageList.at(i);
        if (sp->getPositionY()>HEIGHT+200) {
            auto target = this->getTargetSprite(i);
            sp->setPositionY(target->getPositionY()-sp->getContentSize().height);
            break;
        }
    }
}

Sprite *BackGround::getTargetSprite(int index)
{
    int finalIndex = (index+1)%((int)imageList.size());
    return imageList.at(finalIndex);
}