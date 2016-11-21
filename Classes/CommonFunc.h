//
//  CommonFunc.hpp
//  OctLegend
//
//  Created by zc on 16/8/10.
//
//

#ifndef CommonFunc_h
#define CommonFunc_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class Card;
class CommonFunc {
    
public:
    static void setSpriteSize(cocos2d::Sprite* sp, float width);
    static void setShowAllSpriteSize(cocos2d::Sprite* sp, float width,float height);
    static bool isInPercent(float percent);
    static float reckonHitValue(Card* gongJiCard, Card* fangShouCard, std::string hitType);
    static float reckonShanBiPercent(Card* gongJiCard, Card* fangShouCard, std::string hitType);
    static float reckonBaoJiPercent(Card* gongJiCard, Card* fangShouCard);
    static float reckonZhiLiaoValue(Card* zhiLiaoCard, Card* beZhiLiaoCard);
    static Animate* creatAnimation(std::string onePic, int picSumNum, float time, int loopTimes);
    static Animate* removeAnimation();
    static ui::Button* initButton(ui::Button*btn,const cocos2d::ui::AbstractCheckButton::ccWidgetTouchCallback& callback,float width,Vec2 positon);
   // static void  showHitValue(Label* hpLabel,int hitValue,std::string text);
    //static void setSpriteSizeHeight(cocos2d::Sprite* sp, float width);
    static Label* createLabel(std::string text, Vec2 position);
    static Label* createTextInfoLabel(std::string text, Vec2 position);
};
#endif /* CommonFunc_h */
