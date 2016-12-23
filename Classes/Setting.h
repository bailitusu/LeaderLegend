//
//  Setting.hpp
//  OctLegend
//
//  Created by zc on 16/8/8.
//
//

#ifndef Setting_h
#define Setting_h

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#define screenSize Director::getInstance()->getVisibleSize()
#define origin Director::getInstance()->getVisibleOrigin()
#define winSize Director::getInstance()->getWinSize()
#define animationFactor 0.05

//114 220 244 淡蓝
#define dragonFontColor Color4B(225, 225, 225, 255)
#define dragonSkillInfoColor Color4B(137, 87, 39, 255)
#define tuJianInfoColor Color4B(25, 25, 25, 255)
#define tuJianTextColor Color4B(114,68,37,255)
#define zhuceTitle Color4B(241,117,60,255)
#define ziSe Color4B(75,23,162,255)
#define hongse Color4B(213,60,28,255)
#define lvse Color4B(45,163,36,255)

extern std::string myKey;
extern std::string myPassWord;
struct CardRuleType {
    int jinZhan = 1;
    int gongJian = 2;
    int faShi = 2;
    int niao = 3;
};
static CardRuleType hitRuleType;

struct CardBingType {
    int jinZhan = 0;
    int fangYu = 1;
    int yuanCheng = 2;
    int guWu = 3;
    int zhiLiao = 4;
    int faShi = 5;
};

static CardBingType bingZhongType;
#endif /* Setting_hpp */
