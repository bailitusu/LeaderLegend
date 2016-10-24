//
//  DragonSkill.hpp
//  OctLegend
//
//  Created by zc on 16/8/29.
//
//

#ifndef DragonSkill_h
#define DragonSkill_h

#include "cocos2d.h"
class FightPlayer;
USING_NS_CC;
class DragonSkill : public Ref {
    
public:
    CREATE_FUNC(DragonSkill);
    virtual bool init();
    virtual void runSkill(FightPlayer* player);
    Sprite* dragonSkillSp;
    std::string imageName;
    int skillLevel;
    std::string dargonName;
    bool noHave;
};

#endif /* DragonSkill_h */
