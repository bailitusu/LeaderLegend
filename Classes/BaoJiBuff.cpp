//
//  BaoJiBuff.cpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#include "BaoJiBuff.h"
#include "Card.h"
bool BaojiBuff::init() {
    this->huiHeNum = 2;
    this->buffName = "baoji";
    return true;
}

void BaojiBuff::addBuff(Card *card,float value) {
    if (card->isHaveThisBuff("baoji")) {
        //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
     //   card->isHaveThisBuff("baoji")->huiHeNum = 2;
        return;
    }
    this->defaultValue = card->baoJi;
    card->baoJi = card->baoJi+card->baoJi*value;
    card->buffArray.pushBack(this);
}

void BaojiBuff::decreaseBuff(Card *card,float value) {
    if (card->isHaveThisBuff("baoji")) {
        //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
        card->isHaveThisBuff("baoji")->huiHeNum = 2;
        return;
    }
    this->defaultValue = card->baoJi;
    card->baoJi = card->baoJi-card->baoJi*value;
    card->buffArray.pushBack(this);
}

