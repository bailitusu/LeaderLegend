//
//  MingZhongBuff.cpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#include "MingZhongBuff.h"
#include "Card.h"

bool MingZhongBuff::init() {
    this->huiHeNum = 2;
    this->buffName = "mingzhong";
    return true;
}

void MingZhongBuff::addBuff(Card *card) {
    if (card->isHaveThisBuff("mingzhong")) {
        //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
        card->isHaveThisBuff("mingzhong")->huiHeNum = 2;
        return;
    }
    this->defaultValue = card->mingZhong;
    card->mingZhong = card->mingZhong+card->mingZhong*0.1;
    card->buffArray.pushBack(this);
}

void MingZhongBuff::decreaseBuff(Card *card) {
    if (card->isHaveThisBuff("mingzhong")) {
        //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
        card->isHaveThisBuff("mingzhong")->huiHeNum = 2;
        return;
    }
    this->defaultValue = card->mingZhong;
    card->mingZhong = card->mingZhong-card->mingZhong*0.1;
    card->buffArray.pushBack(this);
}