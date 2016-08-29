//
//  XingTianCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#include "XingTianCard.h"

#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "ActionWait.h"
#include "Card.h"
#include "GeDangBuff.h"
#include "CommonFunc.h"
#include "Setting.h"
bool XingTianCard::init() {
    this->cellIndex = 0;
    this->HP = 20000;
    
    this->hitRuleNum = hitRuleType.jinZhan;
    this->cardName = "xingtian";
    
    this->wuLi = 90;
    this->tongShuai = 88;
    this->zhiLi = 66;
    this->mingJie = 85;
    this->yunQi = 65;
    
    this->gongJi = 17000;

    this->faLi = 17000;
    this->fangYu = 20000;
    
//    this->wuliHart =1;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 10;
//    this->baoJi = 10;
//    this->mianBao = 10;
//    this->lianJi = 1;
    this->bingKinds = bingZhongType.fangYu;
   // this->hitValue = 2;
    this->hitLevel = 0.8;
    //this->geDang = 0.15;
    this->cardLevel = 60;
    return true;
}

void XingTianCard::didBeHit(Card* fromCard, std::string hitKinds) {
    
    float hartValue = CommonFunc::reckonHitValue(fromCard, this, hitKinds);
    if (CommonFunc::isInPercent(CommonFunc::reckonBaoJiPercent(fromCard, this))) {
        if (hitKinds == "wuli") {
            hartValue = hartValue*1.5;
        }else if(hitKinds == "fashu") {
            hartValue = hartValue*1.75;
        }
    }
    if (CommonFunc::isInPercent(this->geDang)) {
        hartValue = hartValue*0.4;
    }
    if (fromCard->bingKinds == bingZhongType.yuanCheng) {
        hartValue = hartValue*0.2;
    }
    if (CommonFunc::isInPercent(CommonFunc::reckonShanBiPercent(fromCard, this, hitKinds)) != false) {
        // printf("%d xingtian %f\n",this->cellIndex,this->geDang);
        this->decreaseHP(this, hartValue);
        
        fromCard->xiXue = hartValue;
        if (this->HP <= 0) {
            this->cardDead();
            return;
        }
    }else {
        this->textLabel->setTextColor(Color4B(0, 0, 240, 255));
        this->showLabelText(this->textLabel, 0, "ShanBi");
    }
}

void XingTianCard::initCharacter() {
    this->geDang = 0.15;
}

void XingTianCard::running(FightPlayer *enemyTemp) {
    
    this->forEnemy = enemyTemp;
    
    
    auto defaultPosition = this->cardSprite->getPosition();
    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.x;
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    auto moveTo = MoveTo::create(1.0, target);
    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
    
    auto hit = CallFunc::create(CC_CALLBACK_0(XingTianCard::hitAction,this));
    auto wait = ActionWait::create(1.0);
    auto maxHit = CallFunc::create(CC_CALLBACK_0(XingTianCard::ultimateSkill, this));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(XingTianCard::nuQiManage, this));
    auto block = CallFunc::create(CC_CALLBACK_0(XingTianCard::actionBlock,this));
    if (this->fPro->nuqiPro->getPercentage() < 100) {
        
        this->cardSprite->runAction(Sequence::create(moveTo,hit,movaFanhui,addNuqi,block,NULL));
        
    }else {
        this->cardSprite->runAction(Sequence::create(moveTo,hit,wait,hit,wait,hit,wait,maxHit,movaFanhui,block,NULL));
    }
    
    
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    
}


void XingTianCard::nuQiManage() {
    this->addNuQi(this, 1);
}

void XingTianCard::hitAction() {
  //  int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if (((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj) != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->didBeHit(this,"wuli");
//        if (((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj) != NULL) {
//            if (((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->nuqiPro->getPercentage() < 100) {
//                ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->setNuQiProPrecent(34+((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->nuqiPro->getPercentage());
//            }
//        }
        this->addNuQi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);

    }
    
    
    
    
}


void XingTianCard::ultimateSkill() {

    auto geDangBuff = GeDangBuff::create();
    geDangBuff->addBuff(this);
  //  geDangBuff->retain();
//    this->buffArray
//    this->geDang = this->geDang*0.15 + this->geDang;
    this->decreaseNuQi(this, 3,true);
}