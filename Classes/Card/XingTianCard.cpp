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
bool XingTianCard::init() {
    this->cellIndex = 0;
    this->HP = 20;
    this->MaxHP = 20;
    this->hitRuleNum = 1;
    this->cardName = "xingtian";
    
    this->wuLi = 20;
    this->tongShuai = 10;
    this->zhiLi = 10;
    this->mingJie = 20;
    this->yunQi = 20;
    
    this->wuliHart = 10;
    this->wuliMianShang = 10;
    this->fashuHart = 10;
    this->fashuMianShang = 10;
    this->shanBi = 20;
    this->mingZhong = 10;
    this->baoJi = 10;
    this->mianBao = 10;
    this->lianJi = 1;
    this->cardType = bingType.jinZhan;
    this->hitValue = 2;
    this->geDang = 10;
    return true;
}

void XingTianCard::didBeHit(Card* fromCard) {
    float hartValue = fromCard->hitValue;
    if (fromCard->cardType == bingType.gongJian) {
        hartValue = hartValue*0.2;
    }
   // printf("%d xingtian %f\n",this->cellIndex,this->geDang);
    this->decreaseHP(this, hartValue);
//    float percent = (1 - (this->HP-hartValue)/this->MaxHP) * 100;
//    //  float aaa = this->fPro->hpPro->getPercentage();
////    ProgressFromTo* ac = ProgressFromTo::create(1.0, this->fPro->hpPro->getPercentage(), percent);
////    this->fPro->hpPro->runAction(ac);
//    this->fPro->hpPro->setPercentage(percent);
//    this->HP = this->HP - hartValue;
    if (this->HP <= 0) {
        this->cardDead();
        return;
    }

}

void XingTianCard::running(FightPlayer *enemyTemp) {
    
    this->forEnemy = enemyTemp;
    
    
    auto defaultPosition = this->cardSprite->getPosition();
    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(cellNum)->position.x;
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(cellNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    auto moveTo = MoveTo::create(1.0, target);
    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
    
    auto hit = CallFunc::create(CC_CALLBACK_0(XingTianCard::hitAction,this));
    auto wait = ActionWait::create(0.1);
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
    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if (((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj) != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->didBeHit(this);
//        if (((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj) != NULL) {
//            if (((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->nuqiPro->getPercentage() < 100) {
//                ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->setNuQiProPrecent(34+((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->nuqiPro->getPercentage());
//            }
//        }
        this->addNuQi((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum)->obj), 1);

    }
    
    
    
    
}

//void XingTianCard::actionBlock() {
//    
//    
//    this->fPro->hpPro->setVisible(true);
//    this->fPro->hpProBg->setVisible(true);
//    this->fPro->nuqiPro->setVisible(true);
//    this->fPro->nuqiProBg->setVisible(true);
//    
//    
//    
//    auto dispatcher = Director::getInstance()->getEventDispatcher();
//    if (playerName.compare("player") == 0) {
//        EventCustom event = EventCustom("enemyPlayerNextRun");
//        //event.setUserData((void*)123);
//        dispatcher->dispatchEvent(&event);
//    }else if (playerName.compare("enemyPlayer") == 0) {
//        EventCustom event = EventCustom("playerNextRun");
//        //event.setUserData((void*)123);
//        dispatcher->dispatchEvent(&event);
//    }
//}

void XingTianCard::ultimateSkill() {
//    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    Vector<MapCell*> temp = this->forEnemy->fMap->hitNineCell(cellNum);
//    for (int i = 0; i < temp.size(); i++) {
//        
//        if (((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage() < 100) {
//            ((Card*)(temp.at(i))->obj)->fPro->setNuQiProPrecent(100/3+((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage());
//        }
//        ((Card*)(temp.at(i))->obj)->didBeHit(this);
//    }
    auto geDangBuff = GeDangBuff::create();
    geDangBuff->add(this);
  //  geDangBuff->retain();
//    this->buffArray
//    this->geDang = this->geDang*0.15 + this->geDang;
    this->fPro->setNuQiProPrecent(0);
}