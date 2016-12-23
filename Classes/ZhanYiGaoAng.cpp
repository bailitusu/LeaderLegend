//
//  ZhanYiGaoAng.cpp
//  OctLegend
//
//  Created by zc on 16/8/30.
//
//

#include "ZhanYiGaoAng.h"
#include "FightPlayer.h"
#include "Card.h"
#include "ZhenFenBuff.h"
#include "MingZhongBuff.h"
bool ZhanYiGaoAng::init() {
    this->skillLevel = 9;
    this->dargonName = "zhanyigaoang";
    this->dargonInfoName = "战役高昂";
    this->zuheNum = 3;
    return true;
}

void ZhanYiGaoAng::runSkill(FightPlayer* player, DragonData* data) {
    for (int i = 0 ; i < player->fMap->mapCellArray.size(); i++) {
        if (player->fMap->mapCellArray.at(i)->obj != NULL) {
            auto zhenFenBuff = ZhenFenBuff::create();
            zhenFenBuff->addBuff(((Card*)player->fMap->mapCellArray.at(i)->obj), 0);
            auto mingZhongBuff = MingZhongBuff::create();
            mingZhongBuff->addBuff(((Card*)player->fMap->mapCellArray.at(i)->obj), 0.1);
        }
    }
    
}
