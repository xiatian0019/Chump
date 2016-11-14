//
//  BattleScene.hpp
//  Chump
//
//  Created by xiaoming on 16/6/1.
//
//

#ifndef BattleScene_hpp
#define BattleScene_hpp

#include <stdio.h>
#include "ObstacleLayer.hpp"
#include "Hero.hpp"
#include "Background.hpp"
#include "SettingPanel.hpp"


class BattleScene : public Layer , public SettingPanelDelegate
{
public:
    CREATE_FUNC(BattleScene);
    static Scene *createScene();
    bool init();
private:
    ObstacleLayer *stageLayer1;
    ObstacleLayer *stageLayer2;
    Hero *hero;
    
    void openTouchEvent();
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    //英雄移动与跳跃
    bool gameRunning;
    void onFrame(float dt);
    
    void heroMove(float dt);
    ObstacleLayer * getCurrentStageLayer();
    void heroGoNextStage();
    bool checkStageOver(ObstacleLayer *stageLayer);
    void updateStageLayer(ObstacleLayer *stageLayer1,ObstacleLayer *stageLayer2);
    void stageMove(float dt);
    
//    void layerMoveAction(ObstacleLayer *layer);
//    void layerMoveFinish(Ref *ref);
    
    float touchTime;
    bool touchLock;
    bool checkingHero();
    void gameOver();
    
    void resetGame();
    void gameStart();
    
    void addExplosionEffect(Vec2 point);
    
    Label *labelScore;
    Label *labelDead;
    int score;
    void updateLabelScore();
    
    int deadNum;
    void updateDeadLabel();
    void backClick(Ref *ref);
    
    int topScore;
    BackGround *backGround;
    
    void settingPanelClose();
    SettingPanel *mySettingPanel;
    MenuItemImage *btnSetting;
};

#endif /* BattleScene_hpp */
