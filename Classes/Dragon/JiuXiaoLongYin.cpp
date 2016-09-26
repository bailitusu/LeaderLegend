//
//  JiuXiaoLongYin.cpp
//  OctLegend
//
//  Created by zc on 16/8/30.
//
//

#include "JiuXiaoLongYin.h"
#include "FightPlayer.h"
#include "Card.h"

bool JiuXiaoLongYin::init() {
    this->skillLevel = 9;
    this->dargonName = "jiuxiaolongyin";
    return true;
}

void JiuXiaoLongYin::runSkill(FightPlayer *player) {
    for (int i = 0 ; i < player->enemy->fMap->mapCellArray.size(); i++) {
        if (player->enemy->fMap->mapCellArray.at(i)->obj != NULL) {
            ((Card*)player->enemy->fMap->mapCellArray.at(i)->obj)->decreaseHP(((Card*)player->enemy->fMap->mapCellArray.at(i)->obj), this->skillLevel*200);
            ((Card*)player->enemy->fMap->mapCellArray.at(i)->obj)->decreaseNuQi(((Card*)player->enemy->fMap->mapCellArray.at(i)->obj), 1, false);
        }
    }
}