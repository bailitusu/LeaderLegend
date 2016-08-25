//
//  ZhenFenBuff.cpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#include "ZhenFenBuff.h"
#include "Card.h"

bool ZhenFenBuff::init() {
    this->huiHeNum = 2;
    this->buffName = "zhenfen";
    return true;
}

void ZhenFenBuff::addBuff(Card *card) {
    if (card->isHaveThisBuff("zhenfen")) {
        //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
        card->isHaveThisBuff("zhenfen")->huiHeNum = 2;
        return;
    }

    card->buffArray.pushBack(this);
}

void ZhenFenBuff::decreaseBuff(Card *card) {
    if (card->isHaveThisBuff("zhenfen")) {
        //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
        card->isHaveThisBuff("zhenfen")->huiHeNum = 2;
        return;
    }

    card->buffArray.pushBack(this);
}