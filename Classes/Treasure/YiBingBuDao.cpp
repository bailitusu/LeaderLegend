//
//  YiBingBuDao.cpp
//  OctLegend
//
//  Created by zc on 16/8/31.
//
//

#include "YiBingBuDao.h"
#include "Card.h"
#include "FightPlayer.h"
#include "ActionWait.h"
bool YiBingBuDao::init() {
    this->gongJi = 2700;
    this->fangYu = 2700;
    this->faLi = 3000;
    this->mingZhong = 0.2;
    this->shanBi = 0.2;
    this->baoJi = 0.2;
    this->mianBao = 0.05;
    this->level = 3;
    this->nuQiNum = 1;
    this->isBuDao = true;
    this->treasureName = "yibingbudao";
    return true;
}

void YiBingBuDao::initNuQi(Card *card) {
    card->addNuQi(card, this->nuQiNum);
}

bool YiBingBuDao::spriteBrother(Card *card) {
    if (this->isBuDao == true) {

        auto wait = ActionWait::create(1.0);
        auto block = CallFunc::create(CC_CALLBACK_0(YiBingBuDao::blockBuDao,this,card));
        card->cardSprite->runAction(Sequence::create(wait,block,NULL));
        
        this->isBuDao = false;
        return true;
    }
    return false;
}

void YiBingBuDao::blockBuDao(Card *card) {
    float temp;
    if (card->HP < 0) {
        temp = -(card->HP-1);
    }else if(card->HP == 0) {
        temp = 1;
    }
    card->addHP(card, temp);
}
