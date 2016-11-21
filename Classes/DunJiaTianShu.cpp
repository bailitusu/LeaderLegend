//
//  DunJiaTianShu.cpp
//  OctLegend
//
//  Created by zc on 16/8/30.
//
//

#include "DunJiaTianShu.h"
#include "Card.h"

bool DunJiaTianShu::init() {
    this->gongJi = 1400;
    this->fangYu = 1400;
    this->faLi = 2800;
    this->mingZhong = 0.15;
    this->shanBi = 0.15;
    this->baoJi = 0.15;
   // this->mianBao = 0.05;
    this->level = 3;
    this->nuQiNum = 1;
    this->treasureName = "dunjiatianshu";
    return true;
}

void DunJiaTianShu::initNuQi(Card *card) {
 //   card->addNuQi(card, this->nuQiNum);
}

void DunJiaTianShu::initRecordNuqi(Card *card) {
   // card->recordAddNuqi(card, this->nuQiNum);
}




