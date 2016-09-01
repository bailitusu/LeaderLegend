//
//  HuiMieBoDong.cpp
//  OctLegend
//
//  Created by zc on 16/8/29.
//
//

#include "HuiMieBoDong.h"
#include "FightPlayer.h"
#include "Card.h"
bool HuiMieBoDong::init() {
    this->skillLevel = 9;
    return true;
}

void HuiMieBoDong::runSkill(FightPlayer* player) {
    for (int i = 0 ; i < player->enemy->fMap->mapCellArray.size(); i++) {
        if (player->enemy->fMap->mapCellArray.at(i)->obj != NULL) {
            ((Card*)player->enemy->fMap->mapCellArray.at(i)->obj)->decreaseHP(((Card*)player->enemy->fMap->mapCellArray.at(i)->obj), this->skillLevel*200);
        }
    }
    
}