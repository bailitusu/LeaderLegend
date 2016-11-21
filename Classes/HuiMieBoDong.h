//
//  HuiMieBoDong.hpp
//  OctLegend
//
//  Created by zc on 16/8/29.
//
//

#ifndef HuiMieBoDong_h
#define HuiMieBoDong_h

#include "cocos2d.h"
#include "DragonSkill.h"
class HuiMieBoDong : public DragonSkill{
    
public:
    CREATE_FUNC(HuiMieBoDong);
    virtual bool init();
    virtual void runSkill(FightPlayer* player, DragonData* data);
    virtual void runSkillAnimation(Sprite* sprite,FightPlayer* player, DragonData* data);
    void animationOver(Sprite* sprite,FightPlayer* player, DragonData* data);
};


#endif /* HuiMieBoDong_h */
