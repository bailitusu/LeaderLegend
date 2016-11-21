//
//  MianBaoBuff.cpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#include "MianBaoBuff.h"
#include "Card.h"

bool MianBaoBuff::init() {
    this->huiHeNum = 2;
    this->buffName = "mianbao";
    return true;
}

void MianBaoBuff::addBuff(Card *card,float value) {
    if (card->isHaveThisBuff("mianbao")) {
        //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
        card->isHaveThisBuff("mianbao")->huiHeNum = 2;
        return;
    }
    this->defaultValue = card->mianBao;
    card->mianBao = card->mianBao+card->mianBao*0.1;
    card->buffArray.pushBack(this);
}

void MianBaoBuff::decreaseBuff(Card *card,float value) {
    if (card->isHaveThisBuff("mianbao")) {
        //  printf("-------------%d--------------",card->isHaveThisBuff("gedang")->huiHeNum);
        card->isHaveThisBuff("mianbao")->huiHeNum = 2;
        return;
    }
    this->defaultValue = card->mianBao;
    card->mianBao = card->mianBao-card->mianBao*0.1;
    card->buffArray.pushBack(this);
}
