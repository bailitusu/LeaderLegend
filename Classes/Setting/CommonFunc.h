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
USING_NS_CC;
class Card;
class CommonFunc {
    
public:
    static void setSpriteSize(cocos2d::Sprite* sp, float width);
    static bool isInPercent(float percent);
    static float reckonHitValue(Card* gongJiCard, Card* fangShouCard, std::string hitType);
    static float reckonShanBiPercent(Card* gongJiCard, Card* fangShouCard, std::string hitType);
    static float reckonBaoJiPercent(Card* gongJiCard, Card* fangShouCard);
    static float reckonZhiLiaoValue(Card* zhiLiaoCard, Card* beZhiLiaoCard);
   // static void  showHitValue(Label* hpLabel,int hitValue,std::string text);
    //static void setSpriteSizeHeight(cocos2d::Sprite* sp, float width);
};
#endif /* CommonFunc_h */
