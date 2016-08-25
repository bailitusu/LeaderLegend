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

#define screenSize Director::getInstance()->getVisibleSize()
#define origin Director::getInstance()->getVisibleOrigin()

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
