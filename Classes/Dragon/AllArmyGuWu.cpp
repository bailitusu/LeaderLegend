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
    this->dargonName = "allarmyguwu";
    this->dargonInfoName = "全军鼓舞";
    return true;
}

void AllArmyGuWu::runSkill(FightPlayer* player,DragonData* data) {
//    for (int i = 0 ; i < player->fMap->mapCellArray.size(); i++) {
//        if (player->fMap->mapCellArray.at(i)->obj != NULL) {
//            ((Card*)player->fMap->mapCellArray.at(i)->obj)->addNuQi(((Card*)player->fMap->mapCellArray.at(i)->obj), this->skillLevel);
//        }
//    }
    for (int i = 0; i < data->dragonAffectArray.size(); i++) {
        Card* affectCard;
        if (data->dragonAffectArray.at(i)->playerName.compare(player->fpName) == 0) {
            affectCard = ((Card*)player->fMap->mapCellArray.at(data->dragonAffectArray.at(i)->standIndex)->obj);
            //affectCard->MaxHP = data->dragonAffectArray.at(i)->maxHP;
            affectCard->nuQiAppear(affectCard, data->dragonAffectArray.at(i)->nuQiChange);
        }else {
            affectCard = ((Card*)player->enemy->fMap->mapCellArray.at(data->dragonAffectArray.at(i)->standIndex)->obj);
          //  affectCard->MaxHP = data->dragonAffectArray.at(i)->maxHP;
            affectCard->nuQiAppear(affectCard, data->dragonAffectArray.at(i)->nuQiChange);
        }
    }
}
