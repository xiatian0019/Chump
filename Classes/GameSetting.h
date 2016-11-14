//
//  GameSetting.h
//  Chump
//
//  Created by xiaoming on 16/6/1.
//
//

#ifndef GameSetting_h
#define GameSetting_h

#define WIDTH   Director::getInstance()->getWinSize().width
#define HEIGHT  Director::getInstance()->getWinSize().height

#define GAME_SCALE   1

#define HERO_SIZE    64            //主角大小
#define BOX_SIZE     20            //格子大小
#define STAGE_GROUND_HEIGHT   20   //地板高度
#define STAGE_HEIGHT     200       //关卡高度


#define MAX_JUMP_TIME       1.5        //



#define GRADE_REFUSE_NUM    5    //用户拒绝N次后，不再弹出评分窗口



#define FONT_VERDANA              "Verdana-Bold"
#define FONT_HELVETICA_BOLD       "Helvetica-Bold"
#define FONT_GEORGIA              "Georgia-Bold"
#define FONT_HELVETICA            "Helvetica"








#endif /* GameSetting_h */
