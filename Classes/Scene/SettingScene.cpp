//
//  SettingScene.cpp
//  Chump
//
//  Created by xiaoming on 16/7/1.
//
//

#include "SettingScene.hpp"
#include "GameSetting.h"
#include "GameController.hpp"
#include "MainScene.hpp"
#include "GameTools.hpp"
Scene *SettingScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SettingScene::create();
    scene->addChild(layer);
    return scene;
}
bool SettingScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto colorBack = LayerColor::create(Color4B(238, 237, 236, 255), WIDTH, HEIGHT);
    this->addChild(colorBack);
    
    auto labelTitle = Label::createWithSystemFont("Setting", FONT_GEORGIA, 40);
    this->addChild(labelTitle);
    labelTitle->setPosition(Vec2(WIDTH/2, HEIGHT-100));
    labelTitle->setColor(Color3B(0, 0, 0));
    
    
    this->addEditList();
    
    
    auto resetLabel = Label::createWithSystemFont("RESET", FONT_HELVETICA, 40);
    resetLabel->setColor(Color3B(0, 0, 0));
    auto backLabel = Label::createWithSystemFont("BACK", FONT_HELVETICA, 40);
    backLabel->setColor(Color3B(0, 0, 0));
    auto itemReset = MenuItemLabel::create(resetLabel, CC_CALLBACK_1(SettingScene::resetClick, this));
    auto itemBack = MenuItemLabel::create(backLabel, CC_CALLBACK_1(SettingScene::backClick, this));
    auto menu = Menu::create(itemReset,itemBack, NULL);
    this->addChild(menu);
    itemBack->setPosition(Vec2(-WIDTH/2+70, -HEIGHT/2+70));
    itemReset->setPosition(Vec2(WIDTH/2-70, -HEIGHT/2+70));
    
    return true;
}

void SettingScene::clearEditList()
{
    if (editList.size()>0) {
        for (int i=0; i<editList.size(); i++) {
            editList.at(i)->removeFromParent();
        }
        editList.clear();
    }
}
void SettingScene::addEditList()
{
    if (editList.size()>0) {
        this->clearEditList();
    }
    auto gameC = GameController::getInstance();
    this->addInputNode("SmallJump", 1, Vec2(120, HEIGHT*4/5),gameC->getJumpSpeedSmall());
    this->addInputNode("BigJump", 2, Vec2(WIDTH-300, HEIGHT*4/5),gameC->getJumpSpeedBig());
    this->addInputNode("HorSpeed", 3, Vec2(120, HEIGHT*3/5),gameC->getHorSpeed());
    this->addInputNode("Gravity", 4, Vec2(WIDTH-300, HEIGHT*3/5),gameC->getGravity());
    this->addInputNode("StageSpeed", 5, Vec2(120, HEIGHT*2/5),gameC->getStageSpeed());
    this->addInputNode("SmallJumpTime", 6, Vec2(WIDTH-300, HEIGHT*2/5),gameC->getSmallJumpTime());
    this->addInputNode("RotateSpeed", 7, Vec2(120, HEIGHT*1/5),gameC->getRotateSpeed());
}
void SettingScene::onExit()
{
    this->clearEditList();
    Layer::onExit();
}


void SettingScene::addInputNode(std::string inputDesc,int inputTag,Vec2 pos,float defaultValue)
{
    auto node = Node::create();
    auto labelDesc = Label::createWithSystemFont(inputDesc, FONT_HELVETICA, 30);
    labelDesc->setColor(Color3B(0, 0, 0));
    node->addChild(labelDesc);
    labelDesc->setPosition(Vec2(0, 50));
    auto edit = ui::EditBox::create(Size(200, 50), "black.png");
    node->addChild(edit);
    edit->setDelegate(this);
    edit->setTag(inputTag);
    if (defaultValue<1) {
        edit->setText(Value(defaultValue).asString().c_str());
    }
    else{
        edit->setText(Value((int)defaultValue).asString().c_str());
    }
    editList.push_back(node);
    this->addChild(node);
    node->setPosition(pos);
}



void SettingScene::editBoxReturn(ui::EditBox* editBox)
{
    CCLOG("editBoxReturn:%d,%s",editBox->getTag(),editBox->getText());
    this->saveInputData(editBox->getTag(), atof(editBox->getText()));
}
void SettingScene::editBoxTextChanged(ui::EditBox* editBox, const std::string& text)
{
    CCLOG("editBoxTextChanged~~~:%d,%s",editBox->getTag(),editBox->getText());
}

void SettingScene::resetClick(Ref *ref)
{
    GameController::getInstance()->resetData();
    this->addEditList();
}
void SettingScene::backClick(Ref *ref)
{
    auto scene = MainScene::createScene();
    GameTools::changeToScene(scene, TRAN_FADE);
}


void SettingScene::saveInputData(int tag,float value)
{
    auto gameC = GameController::getInstance();
    switch (tag) {
        case 1:
            gameC->setJumpSpeedSmall(value);
            break;
        case 2:
            gameC->setJumpSpeedBig(value);
            break;
        case 3:
            gameC->setHorSpeed(value);
            break;
        case 4:
            gameC->setGravity(value);
            break;
        case 5:
            gameC->setStageSpeed(value);
            break;
        case 6:
            gameC->setSmallJumpTime(value);
            break;
        default:
            gameC->setRotateSpeed(value);
            break;
    }
}