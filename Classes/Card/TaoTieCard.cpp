//
//  TaoTieCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/20.
//
//

#include "TaoTieCard.h"
#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
bool TaoTieCard::init() {
    this->cellIndex = 0;
    this->HP = 20;
    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.jinZhan;
    this->cardName = "taotie";
    
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
    this->hitValue = 2;
    this->xiXue = 2;
    this->bingKinds = bingZhongType.jinZhan;
    return true;
}

//void TaoTieCard::didBeHit(Card* fromCard) {
//    
//    
//    float percent = (1 - (this->HP- fromCard->hitValue)/this->MaxHP) * 100;
//
//    this->fPro->hpPro->setPercentage(percent);
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

//void TaoTieCard::cardDead() {
//    
//    this->forPlayer->fMap->mapCellArray.at(this->cellIndex)->obj = NULL;
//    this->fPro->hpPro->setVisible(false);
//    this->fPro->hpProBg->setVisible(false);
//    this->fPro->nuqiPro->setVisible(false);
//    this->fPro->nuqiProBg->setVisible(false);
//    this->cardSprite->removeFromParent();
//}

void TaoTieCard::running(FightPlayer *enemyTemp) {
    this->forEnemy = enemyTemp;
    
    
    auto defaultPosition = this->cardSprite->getPosition();
    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(cellNum)->position.x;
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(cellNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    auto moveTo = MoveTo::create(1.0, target);
    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
    
    auto hit = CallFunc::create(CC_CALLBACK_0(TaoTieCard::hitAction,this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(TaoTieCard::ultimateSkill, this));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(TaoTieCard::nuQiManage, this));
    auto block = CallFunc::create(CC_CALLBACK_0(TaoTieCard::actionBlock,this));
    if (this->fPro->nuqiPro->getPercentage() < 100) {
        
        this->cardSprite->runAction(Sequence::create(moveTo,hit,movaFanhui,addNuqi,block,NULL));
        
    }else {
        this->cardSprite->runAction(Sequence::create(moveTo,maxHit,movaFanhui, block,NULL));
    }
    
    
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    
    // this->cardSprite->runAction(Sequence::create(animateAction, CallFunc::create(CC_CALLBACK_0(HuangDiCard::actionBlock,this)), NULL));
    

}

void TaoTieCard::nuQiManage() {
    this->addNuQi(this, 1);
}

void TaoTieCard::hitAction() {
    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if (cellNum != 100) {
        if ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj != NULL) {
            ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->didBeHit(this,"wuli");
//            if (((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->nuqiPro->getPercentage() < 100) {
//                ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->setNuQiProPrecent(((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->nuqiPro->getPercentage()-34);
//            }
//            this->HP = this->HP + 2;
//            if (this->HP > this->MaxHP) {
//                this->HP = this->MaxHP;
//            }
//            this->fPro->hpPro->setPercentage((1-(float)this->HP/this->MaxHP)*100);
            this->decreaseNuQi((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum)->obj), 1,false);
            this->suckBlood();
            
        }
    }

    
    
    
    
}


void TaoTieCard::ultimateSkill() {
    int cellNum = AttackRule::Rule(this->cellIndex, 2, this->forEnemy->fMap);
    Vector<MapCell*> temp = this->forEnemy->fMap->hitNineCell(cellNum);
    for (int i = 0; i < temp.size(); i++) {
        this->decreaseNuQi((Card*)(temp.at(i))->obj, 1,false);
//        if (((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage() < 100) {
//            ((Card*)(temp.at(i))->obj)->fPro->setNuQiProPrecent(((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage()- 100/3);
//        }
        
        ((Card*)(temp.at(i))->obj)->didBeHit(this,"fashu");
    }
    this->decreaseNuQi(this, 3,true);
   // this->fPro->setNuQiProPrecent(0);
}