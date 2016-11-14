//
//  SettingPanel.hpp
//  Chump
//
//  Created by xiaoming on 16/7/25.
//
//

#ifndef SettingPanel_hpp
#define SettingPanel_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
#include "cocos-ext.h"
USING_NS_CC_EXT;

class SettingPanelDelegate
{
public:
    virtual void settingPanelClose()=0;
};


class SettingPanel : public Layer
{
public:
    CREATE_FUNC(SettingPanel);
    bool init();
    void setDelegate(SettingPanelDelegate *delegate);
private:
    void addLabel(std::string txt,Node *pareNode,Vec2 pos);
    void openTouchEvent();
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    ui::Scale9Sprite *backSp;
    SettingPanelDelegate *myDelegate;
    
    MenuItemImage *btnSoundOn;
    MenuItemImage *btnSoundOff;
    MenuItemImage *btnEffectOn;
    MenuItemImage *btnEffectOff;
    
    MenuItemImage *addBtn(bool stateOn,int tag);
    void btnClick(Ref *ref);
    void updateBtnState();
    
};

#endif /* SettingPanel_hpp */
