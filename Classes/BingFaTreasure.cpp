//
//  BingFaTreasure.cpp
//  OctLegend
//
//  Created by zc on 16/8/30.
//
//

#include "BingFaTreasure.h"
#include "Card.h"
#include "FightPlayer.h"
bool BingFaTreasure::init() {
    this->gongJi = 2700;
    this->fangYu = 2700;
    this->faLi = 3000;
    this->mingZhong = 0.2;
    this->shanBi = 0.2;
    this->baoJi = 0.2;
    this->mianBao = 0.05;
    this->level = 3;
    this->nuQiNum = 1;
    this->treasureName = "bingfa";
    return true;
}

void BingFaTreasure::initNuQi(Card *card) {
   // card->addNuQi(card, this->nuQiNum);
}

void BingFaTreasure::bingFaHuiFuHp(FightPlayer *player) {
    for (int i = 0; i < player->fMap->mapCellArray.size(); i++) {
        if (player->fMap->mapCellArray.at(i)->obj != NULL) {
           // ((Card*)player->fMap->mapCellArray.at(i)->obj)->addHP(((Card*)player->fMap->mapCellArray.at(i)->obj), ((Card*)player->fMap->mapCellArray.at(i)->obj)->MaxHP*0.45);
        }
    }
}
