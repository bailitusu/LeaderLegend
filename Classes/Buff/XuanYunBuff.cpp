//
//  XuanYunBuff.cpp
//  OctLegend
//
//  Created by zc on 16/8/27.
//
//

#include "XuanYunBuff.h"
#include "Card.h"

bool XuanYunBuff::init() {
    this->huiHeNum = 1;
    this->buffName = "xuanyun";
    return true;
}

void XuanYunBuff::addBuff(Card *card,float value) {
    if (card->isHaveThisBuff("xuanyun")) {
        //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
       // card->isHaveThisBuff("xuanyun")->huiHeNum = 2;
        return;
    }
    
    card->buffArray.pushBack(this);
}

void XuanYunBuff::decreaseBuff(Card *card,float value) {
    if (card->isHaveThisBuff("xuanyun")) {
        //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
        card->isHaveThisBuff("xuanyun")->huiHeNum = 2;
        return;
    }
    
    card->buffArray.pushBack(this);
}