//
//  MianYiCuoZhiTreasure.cpp
//  OctLegend
//
//  Created by zc on 16/8/31.
//
//

#include "MianYiCuoZhiTreasure.h"
#include "Card.h"
bool MianYiCuoZhiTreasure::init() {
    this->gongJi = 2700;
    this->fangYu = 2700;
    this->faLi = 2700;
    this->mingZhong = 0.2;
    this->shanBi = 0.2;
    this->baoJi = 0.2;
    this->mianBao = 0.05;
    this->level = 3;
    this->nuQiNum = 2;
    this->treasureName = "mianyicuozhi";
    return true;
}

void MianYiCuoZhiTreasure::initNuQi(Card *card) {
  //  card->addNuQi(card, this->nuQiNum);
}

bool MianYiCuoZhiTreasure::mianYiCuoZhi() {
    return true;
}

void MianYiCuoZhiTreasure::everyRoundAddHP(Card *card) {
  //  card->addHP(card, (float)card->MaxHP*0.15);
}
