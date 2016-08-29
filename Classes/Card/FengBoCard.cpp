//
//  FengBoCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#include "FengBoCard.h"

#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "ActionWait.h"
#include "Card.h"
#include "ShanBiBuff.h"
#include "MianBaoBuff.h"
bool FengBoCard::init() {
    this->cellIndex = 0;
    this->HP = 17000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.faShi;
    this->cardName = "fengbo";
    
    this->wuLi = 71;
    this->tongShuai = 84;
    this->zhiLi = 92;
    this->mingJie = 98;
    this->yunQi = 72;
    
    this->gongJi = 17000;
    this->faLi = 21000;
    this->fangYu = 17000;
//    this->wuliHart = 10;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 10;
//    this->baoJi = 10;
//    this->mianBao = 10;
//    this->lianJi = 1;
    this->bingKinds = bingZhongType.faShi;
//    this->hitValue = 2;
    this->hitLevel = 1.05;
    this->cardLevel = 60;

    return true;
}


void FengBoCard::running(FightPlayer *enemyTemp) {
    
    this->forEnemy = enemyTemp;
    
    
    auto defaultPosition = this->cardSprite->getPosition();
    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.x;
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    auto moveTo = MoveTo::create(1.0, target);
    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
    
    auto hit = CallFunc::create(CC_CALLBACK_0(FengBoCard::hitAction,this));
   // auto wait = ActionWait::create(0.1);
    auto maxHit = CallFunc::create(CC_CALLBACK_0(FengBoCard::ultimateSkill, this));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(FengBoCard::nuQiManage, this));
    auto block = CallFunc::create(CC_CALLBACK_0(FengBoCard::actionBlock,this));
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


void FengBoCard::nuQiManage() {
    this->addNuQi(this, 1);
}

void FengBoCard::hitAction() {
//    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    Vector<MapCell*> temp = this->forEnemy->fMap->hitHengPaiCell(this->targetNum);
    for (int i = 0; i < temp.size(); i++) {
        
 
        ((Card*)(temp.at(i))->obj)->didBeHit(this,"fashu");
        this->addNuQi((Card*)(temp.at(i))->obj, 1);
        
    }

}


void FengBoCard::ultimateSkill() {

    Vector<MapCell*> temp = this->forEnemy->fMap->hitAllCell();
    for (int i = 0; i < temp.size(); i++) {
        
        
        ((Card*)(temp.at(i))->obj)->didBeHit(this,"fashu");
        this->addNuQi((Card*)(temp.at(i))->obj, 1);
        if (((Card*)(temp.at(i))->obj) != NULL) {
            auto shanBiBuff = ShanBiBuff::create();
            shanBiBuff->decreaseBuff(((Card*)(temp.at(i))->obj));
            auto mianBaoBuff = MianBaoBuff::create();
            mianBaoBuff->decreaseBuff(((Card*)(temp.at(i))->obj));
        }
        
    }
    this->decreaseNuQi(this, 3,true);
}