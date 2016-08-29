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
#include "MingZhongBuff.h"
#include "Setting.h"
bool XuanWuCard::init() {
    this->cellIndex = 0;
    this->HP = 22000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.jinZhan;
    this->cardName = "xuanwu";
    
    this->wuLi = 72;
    this->tongShuai = 97;
    this->zhiLi = 85;
    this->mingJie = 25;
    this->yunQi = 100;
    
    this->gongJi = 15000;
    this->faLi = 19000;
    this->fangYu = 22000;
//    this->wuliHart = 10;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 10;
//    this->baoJi = 10;
//    this->mianBao = 10;
//    this->lianJi = 1;
    this->bingKinds = bingZhongType.fangYu;
//    this->hitValue = 2;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
    return true;
}

//void XuanWuCard::didBeHit(Card* fromCard) {
//    
//    
//    float percent = (1 - (this->HP-fromCard->hitValue)/this->MaxHP) * 100;
//    //  float aaa = this->fPro->hpPro->getPercentage();
//    ProgressFromTo* ac = ProgressFromTo::create(1.0, this->fPro->hpPro->getPercentage(), percent);
//    this->fPro->hpPro->runAction(ac);
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

void XuanWuCard::initCharacter() {
    this->zhiLiao = this->MaxHP*0.15;
    this->geDang = 0.2;
}

void XuanWuCard::running(FightPlayer *enemyTemp) {
    this->forEnemy = enemyTemp;

    
    auto defaultPosition = this->cardSprite->getPosition();
    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.x;
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    auto zaiSheng = CallFunc::create(CC_CALLBACK_0(XuanWuCard::zaiShengAction,this));
    auto moveTo = MoveTo::create(1.0, target);
    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
    
    auto hit = CallFunc::create(CC_CALLBACK_0(XuanWuCard::hitAction,this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(XuanWuCard::ultimateSkill, this));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(XuanWuCard::nuQiManage, this));
    auto block = CallFunc::create(CC_CALLBACK_0(XuanWuCard::actionBlock,this));
    if (this->fPro->nuqiPro->getPercentage() < 100) {

        this->cardSprite->runAction(Sequence::create(zaiSheng,moveTo,hit,movaFanhui,addNuqi,block,NULL));
        
    }else {
        this->cardSprite->runAction(Sequence::create(zaiSheng,moveTo,maxHit,movaFanhui, block,NULL));
    }
    
    
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    

}

void XuanWuCard::zaiShengAction() {
    //printf("%d %s xuanwu %d \n",this->cellIndex, this->playerName.c_str(), this->HP);
    this->zaiShengBlood();
    //printf("%d %s xuanwu %d %f \n",this->cellIndex, this->playerName.c_str(), this->HP, this->fPro->hpPro->getPercentage());
    
}

void XuanWuCard::nuQiManage() {
    this->addNuQi(this, 1);
}

void XuanWuCard::hitAction() {
   // int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->didBeHit(this,"wuli");
        
        this->addNuQi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);
//        if (((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->nuqiPro->getPercentage() < 100) {
//            ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->setNuQiProPrecent(34+((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->nuqiPro->getPercentage());
//        }
    }
    
    
    
    
}


void XuanWuCard::ultimateSkill() {
    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    Vector<MapCell*> temp = this->forEnemy->fMap->hitHengPaiCell(cellNum);
    for (int i = 0; i < temp.size(); i++) {
        this->addNuQi((Card*)(temp.at(i))->obj, 1);
//        if (((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage() < 100) {
//            ((Card*)(temp.at(i))->obj)->fPro->setNuQiProPrecent(100/3+((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage());
//        }
        ((Card*)(temp.at(i))->obj)->didBeHit(this,"fashu");
        if (((Card*)(temp.at(i))->obj) != NULL) {
            auto mingZhongBuff = MingZhongBuff::create();
            mingZhongBuff->decreaseBuff(((Card*)(temp.at(i))->obj));
        }

    }

    this->decreaseNuQi(this, 3,true);
}