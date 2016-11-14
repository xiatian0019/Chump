//
//  SettingScene.hpp
//  Chump
//
//  Created by xiaoming on 16/7/1.
//
//

#ifndef SettingScene_hpp
#define SettingScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class SettingScene : public Layer , public ui::EditBoxDelegate
{
public:
    CREATE_FUNC(SettingScene);
    static Scene *createScene();
    bool init();
private:
    void addInputNode(std::string inputDesc,int inputTag,Vec2 pos,float defaultValue);
    void editBoxReturn(ui::EditBox* editBox);
    void editBoxTextChanged(ui::EditBox* editBox, const std::string& text);
    
    void resetClick(Ref *ref);
    void backClick(Ref *ref);
    void saveInputData(int tag,float value);
    std::vector<Node *>editList;
    void onExit();
    void clearEditList();
    void addEditList();
};

#endif /* SettingScene_hpp */
