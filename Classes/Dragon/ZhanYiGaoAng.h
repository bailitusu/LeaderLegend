//
//  ZhanYiGaoAng.hpp
//  OctLegend
//
//  Created by zc on 16/8/30.
//
//

#ifndef ZhanYiGaoAng_h
#define ZhanYiGaoAng_h

#include "cocos2d.h"
#include "DragonSkill.h"
class ZhanYiGaoAng : public DragonSkill {
    
public:
    CREATE_FUNC(ZhanYiGaoAng);
    virtual bool init();
    virtual void runSkill(FightPlayer* player);
};

#endif /* ZhanYiGaoAng_h */
