//
//  ZaiShengLongHou.cpp
//  OctLegend
//
//  Created by zc on 16/8/30.
//
//

#include "ZaiShengLongHou.h"
#include "FightPlayer.h"
#include "Card.h"
bool ZaiShengLongHou::init() {
    this->skillLevel = 9;
    this->dargonName = "zaishenglonghou";
    this->dargonInfoName = "再生龙吼";
    this->zuheNum = 30;
    return true;
}

void ZaiShengLongHou::runSkill(FightPlayer* player, DragonData* data) {
    for (int i = 0 ; i < player->fMap->mapCellArray.size(); i++) {
        if (player->fMap->mapCellArray.at(i)->obj != NULL) {
       //     ((Card*)player->fMap->mapCellArray.at(i)->obj)->addHP(((Card*)player->fMap->mapCellArray.at(i)->obj), this->skillLevel*200);
        //    ((Card*)player->fMap->mapCellArray.at(i)->obj)->addNuQi(((Card*)player->fMap->mapCellArray.at(i)->obj), 1);
        }
    }
    
}
