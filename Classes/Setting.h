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
#define animationFactor 0.1

//114 220 244 淡蓝
#define dragonFontColor Color4B(225, 225, 225, 255)
#define dragonSkillInfoColor Color4B(137, 87, 39, 255)
#define tuJianInfoColor Color4B(25, 25, 25, 255)
#define tuJianTextColor Color4B(114,68,37,255)

static std::string myKey = "yzq";
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
