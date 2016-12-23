//
//  AllArmyGuWu.hpp
//  OctLegend
//
//  Created by zc on 16/8/29.
//
//

#ifndef AllArmyGuWu_h
#define AllArmyGuWu_h

#include "cocos2d.h"
#include "DragonSkill.h"
class AllArmyGuWu : public DragonSkill{
    
public:
    CREATE_FUNC(AllArmyGuWu);
    virtual bool init();
    virtual void runSkill(FightPlayer* player, DragonData* data);
    
};

#endif /* AllArmyGuWu_h */
