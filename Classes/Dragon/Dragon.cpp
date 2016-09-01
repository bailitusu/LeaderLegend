//
//  Dragon.cpp
//  OctLegend
//
//  Created by zc on 16/8/29.
//
//

#include "Dragon.h"
#include "FightPlayer.h"

bool Dragon::init() {
    this->currentIndex = 0;
    return true;
}

void Dragon::runNextDragonSkill(FightPlayer* player) {
    if (this->currentIndex >= this->dragonSkillArray.size()) {
        this->dragonSkillArray.clear();
        return;
    }
    this->dragonSkillArray.at(this->currentIndex)->runSkill(player);
    this->currentIndex++;
}

void Dragon::addDragonSkill(DragonSkill *skill,int index) {
    this->dragonSkillArray.insert(index, skill);
}
