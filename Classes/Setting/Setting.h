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

struct CardType {
    int jinZhan = 0;
    int gongJian = 1;
    int faShi = 2;
    int niao = 3;
};
static CardType bingType;
#endif /* Setting_hpp */
