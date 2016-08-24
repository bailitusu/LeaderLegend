//
//  ChangECard.cpp
//  OctLegend
//
//  Created by zc on 16/8/20.
//
//

#include "ChangECard.h"
#include "FightPlayer.h"
#include "AttackRule.h"
bool ChangECard::init() {
    this->cellIndex = 0;
    this->HP = 20;
    this->MaxHP = 20;
    this->hitRuleNum = 2;
    this->cardName = "change";
    
    this->wuLi = 20;
    this->tongShuai = 10;
    this->zhiLi = 10;
    this->mingJie = 20;
    this->yunQi = 20;
    this->zhiLiao = 2;
    this->wuliHart = 10;
    this->wuliMianShang = 10;
    this->fashuHart = 10;
    this->fashuMianShang = 10;
    this->shanBi = 20;
    this->mingZhong = 10;
    this->baoJi = 10;
    this->mianBao = 10;
    this->lianJi = 1;
    this->hitValue = 0;
    return true;
}

//void ChangECard::didBeHit(Card* fromCard) {
//    
//    
//    float percent = (1 - (this->HP - fromCard->hitValue)/this->MaxHP) * 100;
//    //  float aaa = this->fPro->hpPro->getPercentage();
//  //  ProgressFromTo* ac = ProgressFromTo::create(1.0, this->fPro->hpPro->getPercentage(), percent);
//    this->fPro->hpPro->setPercentage(percent);
//    //this->fPro->hpPro->runAction(ac);
//    this->HP = this->HP - fromCard->hitValue;
//    if (this->HP <= 0) {
//        this->cardDead();
//        return;
//    }
//    //    if (this->fPro->nuqiPro->getPercentage() < 100 && this->HP > 0) {
//    //        this->fPro->setNuQiProPrecent(100/3+this->fPro->nuqiPro->getPercentage());
//    //    }else {
//    //        return;
//    //    }
//    //
//    // std::cout << "huangdi hart" << hitValue << std::endl;
//}

void ChangECard::running(FightPlayer *enemyTemp) {
    this->forEnemy = enemyTemp;
    

    auto defalutScale = this->cardSprite->getScale();
    auto big = ScaleTo::create(1.0, 1.0);
    auto small = ScaleTo::create(1.0, defalutScale);
    auto hit = CallFunc::create(CC_CALLBACK_0(ChangECard::hitAction,this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(ChangECard::ultimateSkill, this));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(ChangECard::nuQiManage, this));
    auto block = CallFunc::create(CC_CALLBACK_0(ChangECard::actionBlock,this));
    if (this->fPro->nuqiPro->getPercentage() < 100) {
        
        this->cardSprite->runAction(Sequence::create(big,small,hit,addNuqi, block,NULL));
        
        //this->cardSprite->runAction(Sequence::create(hit,addNuqi,block,NULL));
        
    }else {
        this->cardSprite->runAction(Sequence::create(maxHit, block,NULL));
    }
    
    
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);

}


void ChangECard::nuQiManage() {
   this->addNuQi(this, 1);
}

void ChangECard::hitAction() {
    for (int i = 0; i < this->forPlayer->cardArray.size(); i++) {
        if (this->forPlayer->cardArray.at(i)->cellIndex != this->cellIndex && this->forPlayer->cardArray.at(i)->fPro->nuqiPro->getPercentage() < 100) {
           // this->forPlayer->cardArray.at(i)->fPro->setNuQiProPrecent(34+this->forPlayer->cardArray.at(i)->fPro->nuqiPro->getPercentage());
            this->addNuQi(this->forPlayer->cardArray.at(i), 1);
        }
    }

}

void ChangECard::ultimateSkill() {
    for (int i = 0; i < this->forPlayer->fMap->mapCellArray.size(); i++) {
        auto temp = (Card*)(this->forPlayer->fMap->mapCellArray.at(i))->obj;
        if (temp != NULL && temp->cellIndex != this->cellIndex) {
             this->addNuQi(temp, 1);
//            if (temp->fPro->nuqiPro->getPercentage() < 100) {
//                temp->fPro->setNuQiProPrecent(34+temp->fPro->nuqiPro->getPercentage());
//            }
//            temp->HP = temp->HP+this->zhiLiao;
//            if (temp->HP > temp->MaxHP) {
//                temp->HP = temp->MaxHP;
//            }
//            temp->fPro->hpPro->setPercentage((1-(float)temp->HP/temp->MaxHP)*100);
            this->addHP(temp, this->zhiLiao);
        }
    }
    
    this->decreaseNuQi(this, 3);
//    this->fPro->setNuQiProPrecent(0);
}