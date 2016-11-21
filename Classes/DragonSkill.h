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
#include "ReadRecordFight.h"

#include "OneRecord.h"
class FightPlayer;

USING_NS_CC;
class DragonSkill : public Ref {
    
public:
    CREATE_FUNC(DragonSkill);
    virtual bool init();
    virtual void runSkill(FightPlayer* player, DragonData* data);
    virtual void runSkillAnimation(Sprite* sprite,FightPlayer* player, DragonData* data);
    Sprite* dragonSkillSp;
    std::string imageName;
    int skillLevel;
    std::string dargonName;
    bool noHave;
    std::string dargonInfoName;
};

#endif /* DragonSkill_h */
