//
//  HuFuTreasure.cpp
//  OctLegend
//
//  Created by zc on 16/8/30.
//
//

#include "HuFuTreasure.h"
#include "Card.h"

bool HuFuTreasure::init() {
    this->gongJi = 2700;
    this->fangYu = 2700;
    this->faLi = 2700;
    this->mingZhong = 0.2;
    this->shanBi = 0.2;
    this->baoJi = 0.2;
    this->mianBao = 0.05;
    this->level = 3;
    this->nuQiNum = 0;
    this->treasureName = "hufu";
    return true;
}

void HuFuTreasure::initNuQi(Card *card) {
    card->addNuQi(card, this->nuQiNum);
}

void HuFuTreasure::willRunAddNuQi(Card *card) {
    card->addNuQi(card, 1);
}

float HuFuTreasure::specialMianShang(Card *card, float value) {
    float temp = (float)(card->MaxHP-card->HP)/card->MaxHP;
    temp = temp/5;
    value = value*(1-temp);
    return value;
}