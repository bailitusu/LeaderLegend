//
//  ShanBiBuff.cpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#include "ShanBiBuff.h"
#include "Card.h"

bool ShanBiBuff::init() {
    this->huiHeNum = 2;
    this->buffName = "shanbi";
    return true;
}

void ShanBiBuff::addBuff(Card *card,float value) {
    if (card->isHaveThisBuff("shanbi")) {
        //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
      //  card->isHaveThisBuff("shanbi")->huiHeNum = 2;
        return;
    }
    this->defaultValue = card->shanBi;
    card->shanBi = card->shanBi+card->shanBi*value;
    card->buffArray.pushBack(this);
}

void ShanBiBuff::decreaseBuff(Card *card,float value) {
    if (card->isHaveThisBuff("shanbi")) {
        //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
        card->isHaveThisBuff("shanbi")->huiHeNum = 2;
        return;
    }
    this->defaultValue = card->shanBi;
    card->shanBi = card->shanBi-card->shanBi*value;
    card->buffArray.pushBack(this);
}
