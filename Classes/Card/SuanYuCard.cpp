//
//  SuanYuCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/25.
//
//

#include "SuanYuCard.h"

#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "ActionWait.h"
#include "Card.h"
#include "CommonFunc.h"
#include "XuanYunBuff.h"
bool SuanYuCard::init() {
    this->cellIndex = 0;
    this->HP = 18000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.niao;
    this->cardName = "suanyu";
    
    this->wuLi = 81;
    this->tongShuai = 78;
    this->zhiLi = 56;
    this->mingJie = 98;
    this->yunQi = 75;
    
    this->gongJi = 19000;
    this->faLi = 17000;
    this->fangYu = 18000;
    
//    this->wuliHart = 10;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 100;
//    this->baoJi = 10;
//    this->mianBao = 10;
//    this->lianJi = 1;
    this->bingKinds = bingZhongType.yuanCheng;
//    this->hitValue = 2;
//    this->geDang = 10;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
    return true;
}

void SuanYuCard::didBeHit(Card* fromCard, std::string hitKinds) {
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
        hartValue = hartValue*2;
    }
    hartValue = this->magicGoods->specialMianShang(this, hartValue);
    if (CommonFunc::isInPercent(CommonFunc::reckonShanBiPercent(fromCard, this, hitKinds)) != false) {
        
        
        fromCard->xiXue = hartValue;
        this->decreaseHP(this,hartValue);
        
        float tempHart = 0;
        if (hitKinds == "wuli") {
            tempHart = this->magicGoods->fanTanWuLiHart(hartValue);
            if (tempHart != 0) {
                fromCard->decreaseHP(fromCard, tempHart);
            }
        }else if(hitKinds == "fashu") {
            tempHart = this->magicGoods->fanTanFaShuHart(hartValue);
            if (tempHart != 0) {
                fromCard->decreaseHP(fromCard, tempHart);
            }
        }

    }else {
        this->textLabel->setTextColor(Color4B(0, 0, 240, 255));
        this->showLabelText(this->textLabel, 0, "ShanBi");
    }

    
}

void SuanYuCard::initCharacter() {
    this->mingZhong = 3.0;
}

void SuanYuCard::running(FightPlayer *enemyTemp) {
    
    this->forEnemy = enemyTemp;
    
    
    auto defaultPosition = this->cardSprite->getPosition();
    
    if (this->fPro->nuqiPro->getPercentage() < 100){
        this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    }else {
        Vector<MapCell*> temp = AttackRule::NuQiMaxRule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
        bool breakFlag = false;
        for (int j = 5; j >= 0; j--) {
            for (int i = 0; i < temp.size(); i++) {
                if (((Card*)temp.at(i)->obj)->nuQiNum == j) {
                    
                    this->targetNum = ((Card*)temp.at(i)->obj)->cellIndex;
                    breakFlag = true;
                    break;
                }
            }
            if (breakFlag == true) {
                break;
            }
        }
    }
    

    
    
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.x;
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    auto moveTo = MoveTo::create(1.0, target);
    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
    
    auto hit = CallFunc::create(CC_CALLBACK_0(SuanYuCard::hitAction,this));
    auto wait = ActionWait::create(0.5);
    auto maxHit = CallFunc::create(CC_CALLBACK_0(SuanYuCard::ultimateSkill, this));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(SuanYuCard::nuQiManage, this));
    auto block = CallFunc::create(CC_CALLBACK_0(SuanYuCard::actionBlock,this));
    if (this->fPro->nuqiPro->getPercentage() < 100) {
        
        this->cardSprite->runAction(Sequence::create(moveTo,hit,wait,movaFanhui,addNuqi,block,NULL));
        
    }else {
        this->cardSprite->runAction(Sequence::create(moveTo,maxHit,wait,movaFanhui,block,NULL));
    }
    
    
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    
}


void SuanYuCard::nuQiManage() {
    this->addNuQi(this, 1);
}

void SuanYuCard::hitAction() {
  //  int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if (((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj) != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->didBeHit(this,"wuli");

        this->addNuQi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);
        
    }
   
}


void SuanYuCard::ultimateSkill() {
    Vector<MapCell*> temp = AttackRule::NuQiMaxRule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    for (int j = 5; j >= 0; j--) {
        for (int i = 0; i < temp.size(); i++) {
            if (((Card*)temp.at(i)->obj)->nuQiNum == j) {
                
                this->decreaseNuQi((Card*)temp.at(i)->obj, 1, false);
                this->addNuQi(this, 1);
                ((Card*)temp.at(i)->obj)->didBeHit(this, "wuli");
                this->decreaseNuQi(this, 3,true);
                
                if (((Card*)(temp.at(i))->obj) != NULL) {
                    auto xuanYunBuff = XuanYunBuff::create();
                    xuanYunBuff->addBuff(((Card*)(temp.at(i))->obj),0);
                }
                return;
            }
        }
    }
   
}
