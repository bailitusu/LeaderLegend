//
//  FanTanWuLiTreasure.cpp
//  OctLegend
//
//  Created by zc on 16/8/31.
//
//

#include "FanTanWuLiTreasure.h"
#include "Card.h"
bool FanTanWuLiTreasure::init() {
    this->gongJi = 2700;
    this->fangYu = 2700;
    this->faLi = 2700;
    this->mingZhong = 0.2;
    this->shanBi = 0.2;
    this->baoJi = 0.2;
    this->mianBao = 0.05;
    this->level = 3;
    this->nuQiNum = 2;
    this->treasureName = "fantanwuli";
    return true;
}

void FanTanWuLiTreasure::initNuQi(Card *card) {
    card->addNuQi(card, this->nuQiNum);
}

float FanTanWuLiTreasure::fanTanWuLiHart(float hartValue) {
    return hartValue*0.2;
}