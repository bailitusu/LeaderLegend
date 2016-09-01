//
//  ZaiShengLongHou.hpp
//  OctLegend
//
//  Created by zc on 16/8/30.
//
//

#ifndef ZaiShengLongHou_h
#define ZaiShengLongHou_h

#include "cocos2d.h"
#include "DragonSkill.h"
class ZaiShengLongHou : public DragonSkill {
    
public:
    CREATE_FUNC(ZaiShengLongHou);
    virtual bool init();
    virtual void runSkill(FightPlayer* player);
};

#endif /* ZaiShengLongHou_h */
