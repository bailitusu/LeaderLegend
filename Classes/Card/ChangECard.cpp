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
#include "Setting.h"
#include "CommonFunc.h"
#include "ActionWait.h"
bool ChangECard::init() {
    this->cellIndex = 0;
    this->HP = 16000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.faShi;
    this->cardName = "change";
    
    this->wuLi = 60;
    this->tongShuai = 72;
    this->zhiLi = 78;
    this->mingJie = 90;
    this->yunQi = 95;
    
    this->gongJi = 17000;
    this->faLi = 20000;
    this->fangYu = 17000;
  //  this->zhiLiao = 2;
//    this->wuliHart = 10;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 10;
//    this->baoJi = 10;
//    this->mianBao = 10;

//    this->hitValue = 0;
    this->bingKinds = bingZhongType.guWu;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
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
    auto tooSmall = ScaleTo::create(1.0, 0.3);
    auto hit = CallFunc::create(CC_CALLBACK_0(ChangECard::hitAction,this));
    auto wait = ActionWait::create(1.0);
    auto maxHit = CallFunc::create(CC_CALLBACK_0(ChangECard::ultimateSkill, this));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(ChangECard::nuQiManage, this));
    auto block = CallFunc::create(CC_CALLBACK_0(ChangECard::actionBlock,this));
    if (this->fPro->nuqiPro->getPercentage() < 100) {
        
        this->cardSprite->runAction(Sequence::create(big,small,hit,addNuqi, block,NULL));
        
        //this->cardSprite->runAction(Sequence::create(hit,addNuqi,block,NULL));
        
    }else {
        this->cardSprite->runAction(Sequence::create(tooSmall,small,maxHit, wait,block,NULL));
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
   // printf("%s   fang da %d \n",this->playerName.c_str(),this->cellIndex);
    for (int i = 0; i < this->forPlayer->fMap->mapCellArray.size(); i++) {
        auto temp = (Card*)(this->forPlayer->fMap->mapCellArray.at(i))->obj;
        if (temp != NULL) {
            if (temp->cellIndex != this->cellIndex) {
                this->addNuQi(temp, 1);
            }
            
//            if (temp->fPro->nuqiPro->getPercentage() < 100) {
//                temp->fPro->setNuQiProPrecent(34+temp->fPro->nuqiPro->getPercentage());
//            }
//            temp->HP = temp->HP+this->zhiLiao;
//            if (temp->HP > temp->MaxHP) {
//                temp->HP = temp->MaxHP;
//            }
//            temp->fPro->hpPro->setPercentage((1-(float)temp->HP/temp->MaxHP)*100);
           // CommonFunc::reckonZhiLiaoValue(this, temp);
            this->addHP(temp, CommonFunc::reckonZhiLiaoValue(this, temp));
        }
    }
    
    this->decreaseNuQi(this, 3,true);
//    this->fPro->setNuQiProPrecent(0);
}