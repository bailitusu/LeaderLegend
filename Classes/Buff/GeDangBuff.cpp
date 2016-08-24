//
//  GeDangBuff.cpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#include "GeDangBuff.h"
#include "Card.h"

bool GeDangBuff::init() {
    this->huiHeNum = 1;
    this->buffName = "gedang";
    return true;
}

void GeDangBuff::add(Card *card) {
    if (card->isHaveThisBuff("gedang")) {
      //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
        card->isHaveThisBuff("gedang")->huiHeNum = 1;
        return;
    }
    this->defaultGeDang = card->geDang;
    card->geDang = card->geDang*0.5+card->geDang;
    card->buffArray.pushBack(this);
}

void GeDangBuff::decrease(Card *card) {
 
    card->geDang = this->defaultGeDang;
    card->buffArray.eraseObject(this);
  //  this->release();
  //  printf("%d---------%f/n",card->cellIndex,card->geDang);
}

