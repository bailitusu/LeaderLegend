//
//  AllArmyGuWu.cpp
//  OctLegend
//
//  Created by zc on 16/8/29.
//
//

#include "AllArmyGuWu.h"
#include "FightPlayer.h"
#include "Card.h"
bool AllArmyGuWu::init() {
    this->skillLevel = 1;
    return true;
}

void AllArmyGuWu::runSkill(FightPlayer* player) {
    for (int i = 0 ; i < player->fMap->mapCellArray.size(); i++) {
        if (player->fMap->mapCellArray.at(i)->obj != NULL) {
            ((Card*)player->fMap->mapCellArray.at(i)->obj)->addNuQi(((Card*)player->fMap->mapCellArray.at(i)->obj), this->skillLevel);
        }
    }
    
}