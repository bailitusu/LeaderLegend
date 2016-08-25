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

void GeDangBuff::addBuff(Card *card) {
    if (card->isHaveThisBuff("gedang")) {
      //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
        card->isHaveThisBuff("gedang")->huiHeNum = 1;
        return;
    }
    this->defaultValue = card->geDang;
    card->geDang = card->geDang+0.5;
    card->buffArray.pushBack(this);
}

void GeDangBuff::decreaseBuff(Card *card) {
    
    if (card->isHaveThisBuff("gedang")) {
        //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
        card->isHaveThisBuff("gedang")->huiHeNum = 1;
        return;
    }
    this->defaultValue = card->geDang;
    card->geDang = card->geDang-0.5;
    card->buffArray.pushBack(this);
 
//    card->geDang = this->defaultGeDang;
//    card->buffArray.eraseObject(this);
  //  this->release();
  //  printf("%d---------%f/n",card->cellIndex,card->geDang);
}

