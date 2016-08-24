//
//  XuanWuCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#include "XuanWuCard.h"
#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "ActionWait.h"
bool XuanWuCard::init() {
    this->cellIndex = 0;
    this->HP = 20;
    this->MaxHP = 20;
    this->hitRuleNum = 2;
    this->cardName = "houyi";
    
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
    this->zhiLiao = 2;
    return true;
}

void XuanWuCard::didBeHit(Card* fromCard) {
    
    
    float percent = (1 - (this->HP-fromCard->hitValue)/this->MaxHP) * 100;
    //  float aaa = this->fPro->hpPro->getPercentage();
    ProgressFromTo* ac = ProgressFromTo::create(1.0, this->fPro->hpPro->getPercentage(), percent);
    this->fPro->hpPro->runAction(ac);
    this->HP = this->HP - fromCard->hitValue;
    if (this->HP <= 0) {
        this->cardDead();
        return;
    }
    //    if (this->fPro->nuqiPro->getPercentage() < 100 && this->HP > 0) {
    //        this->fPro->setNuQiProPrecent(100/3+this->fPro->nuqiPro->getPercentage());
    //    }else {
    //        return;
    //    }
    //
    // std::cout << "huangdi hart" << hitValue << std::endl;
}

void XuanWuCard::cardDead() {
    
    this->forPlayer->fMap->mapCellArray.at(this->cellIndex)->obj = NULL;
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    this->cardSprite->removeFromParent();
}

void XuanWuCard::runAnimation(FightPlayer* playerTemp) {
    // AttackRule::Rule(1, 1, <#FightMap *map#>)
    this->forEnemy = playerTemp;
    
    
    auto defaultPosition = this->cardSprite->getPosition();
    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(cellNum)->position.x;
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(cellNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    auto moveTo = MoveTo::create(1.0, target);
    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
    
    auto hit = CallFunc::create(CC_CALLBACK_0(XuanWuCard::hitAction,this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(XuanWuCard::ultimateSkill, this));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(XuanWuCard::addNuqi, this));
    auto block = CallFunc::create(CC_CALLBACK_0(XuanWuCard::actionBlock,this));
    if (this->fPro->nuqiPro->getPercentage() < 100) {
        if (this->lianJi == 2) {
            this->cardSprite->runAction(Sequence::create(moveTo,hit,hit,movaFanhui,addNuqi, block,NULL));
        } else {
            this->cardSprite->runAction(Sequence::create(moveTo,hit,movaFanhui,addNuqi,block,NULL));
        }
    }else {
        this->cardSprite->runAction(Sequence::create(moveTo,maxHit,movaFanhui, block,NULL));
    }
    
    
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    
    // this->cardSprite->runAction(Sequence::create(animateAction, CallFunc::create(CC_CALLBACK_0(HuangDiCard::actionBlock,this)), NULL));
    
    
    
}

void XuanWuCard::addNuqi() {
    if (this->fPro->nuqiPro->getPercentage() < 100) {
        this->fPro->setNuQiProPrecent(34+this->fPro->nuqiPro->getPercentage());
    }
}

void XuanWuCard::hitAction() {
    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->didBeHit(this);
        if (((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->nuqiPro->getPercentage() < 100) {
            ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->setNuQiProPrecent(34+((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->nuqiPro->getPercentage());
        }
    }
    
    
    
    
}

void XuanWuCard::actionBlock() {
    
    
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    if (playerName.compare("player") == 0) {
        EventCustom event = EventCustom("enemyPlayerNextRun");
        //event.setUserData((void*)123);
        dispatcher->dispatchEvent(&event);
    }else if (playerName.compare("enemyPlayer") == 0) {
        EventCustom event = EventCustom("playerNextRun");
        //event.setUserData((void*)123);
        dispatcher->dispatchEvent(&event);
    }
}

void XuanWuCard::ultimateSkill() {
    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    Vector<MapCell*> temp = this->forEnemy->fMap->hitNineCell(cellNum);
    for (int i = 0; i < temp.size(); i++) {
        
        if (((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage() < 100) {
            ((Card*)(temp.at(i))->obj)->fPro->setNuQiProPrecent(100/3+((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage());
        }
        ((Card*)(temp.at(i))->obj)->didBeHit(this);
    }
    this->fPro->setNuQiProPrecent(0);
}