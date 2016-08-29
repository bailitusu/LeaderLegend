//
//  FengHouCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#include "FengHouCard.h"
#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "ActionWait.h"
#include "Card.h"
#include "GeDangBuff.h"
#include "ZhenFenBuff.h"
#include "BaoJiBuff.h"
bool FengHouCard::init() {
    this->cellIndex = 0;
    this->HP = 19000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.jinZhan;
    this->cardName = "fenghou";
    
    this->wuLi = 72;
    this->tongShuai = 92;
    this->zhiLi = 88;
    this->mingJie = 82;
    this->yunQi = 92;
    
    this->gongJi = 18000;
    this->faLi = 18000;
    this->fangYu = 20000;
//    this->wuliHart = 10;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 10;
//    this->baoJi = 10;
//    this->mianBao = 10;
//    this->lianJi = 1;
    this->bingKinds = bingZhongType.guWu;
//    this->hitValue = 2;
//    this->geDang = 0;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
    return true;
}




void FengHouCard::running(FightPlayer *enemyTemp) {
    
    this->forEnemy = enemyTemp;
    
    
    auto defaultPosition = this->cardSprite->getPosition();
    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.x;
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    auto moveTo = MoveTo::create(1.0, target);
    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
    
    auto hit = CallFunc::create(CC_CALLBACK_0(FengHouCard::hitAction,this));
    //auto wait = ActionWait::create(0.1);
    auto maxHit = CallFunc::create(CC_CALLBACK_0(FengHouCard::ultimateSkill, this));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(FengHouCard::nuQiManage, this));
    auto block = CallFunc::create(CC_CALLBACK_0(FengHouCard::actionBlock,this));
    if (this->fPro->nuqiPro->getPercentage() < 100) {
        
        this->cardSprite->runAction(Sequence::create(moveTo,hit,movaFanhui,addNuqi,block,NULL));
        
    }else {
        this->cardSprite->runAction(Sequence::create(moveTo,maxHit,movaFanhui,block,NULL));
    }
    
    
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    
}


void FengHouCard::nuQiManage() {
    this->addNuQi(this, 1);

    Vector<MapCell*> temp = this->forPlayer->fMap->hitNineCell(this->cellIndex);
    for (int i = 0; i < temp.size(); i++) {
        this->addNuQi((Card*)(temp.at(i))->obj, 1);
    }

}

void FengHouCard::hitAction() {
//    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if (((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj) != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->didBeHit(this,"wuli");

        this->addNuQi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);
        
    }
}



void FengHouCard::ultimateSkill() {
//    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if (((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj) != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->didBeHit(this,"wuli");
        
        this->addNuQi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);
        
    }
    
    Vector<MapCell*> temp = this->forPlayer->fMap->hitAllCell();
    for (int i = 0; i < temp.size(); i++) {
        if (((Card*)(temp.at(i))->obj)->cellIndex != this->cellIndex) {
            this->addNuQi((Card*)(temp.at(i))->obj, 1);
        }
        
        if (((Card*)(temp.at(i))->obj) != NULL) {
            auto zhenFen = ZhenFenBuff::create();
            zhenFen->addBuff(((Card*)(temp.at(i))->obj));
            auto baoJi = BaojiBuff::create();
            baoJi->addBuff(((Card*)(temp.at(i))->obj));

        }
    }
    
    this->decreaseNuQi(this, 3, true);
}