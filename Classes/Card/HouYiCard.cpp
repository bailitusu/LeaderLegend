//
//  HouYiCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/20.
//
//

#include "HouYiCard.h"
#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
bool HouYiCard::init() {
    this->cellIndex = 0;
    this->HP = 20;
    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.gongJian;
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
    this->bingKinds = bingZhongType.yuanCheng;
    this->hitValue = 2;
    return true;
}

//void HouYiCard::didBeHit(Card* fromCard) {
//
//    
//
////    if (this->fPro->nuqiPro->getPercentage() < 100 && this->HP > 0) {
////        this->fPro->setNuQiProPrecent(100/3+this->fPro->nuqiPro->getPercentage());
////    }else {
////        return;
////    }
////
//    // std::cout << "huangdi hart" << hitValue << std::endl;
//}
//
//void HouYiCard::cardDead() {
//    
//
//}

void HouYiCard::running(FightPlayer *enemyTemp) {
    this->forEnemy = enemyTemp;
    
  //  printf("%dhouyi%f\n",this->cellIndex,this->mingZhong);
    auto defaultPosition = this->cardSprite->getPosition();
    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(cellNum)->position.x;
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(cellNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    auto moveTo = MoveTo::create(1.0, target);
    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
    
    auto hit = CallFunc::create(CC_CALLBACK_0(HouYiCard::hitAction,this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(HouYiCard::ultimateSkill, this));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(HouYiCard::nuQiManage, this));
    auto block = CallFunc::create(CC_CALLBACK_0(HouYiCard::actionBlock,this));
    if (this->fPro->nuqiPro->getPercentage() < 100) {
        if (this->lianJi == 2) {
            this->cardSprite->runAction(Sequence::create(moveTo,hit,hit,movaFanhui,addNuqi,block,NULL));
        } else {
            this->cardSprite->runAction(Sequence::create(moveTo,hit,movaFanhui,addNuqi,block,NULL));
        }
    }else {
        this->cardSprite->runAction(Sequence::create(moveTo,maxHit,movaFanhui,block,NULL));
    }
    
    
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    

}

//void HouYiCard::runAnimation(FightPlayer* playerTemp) {
//    // AttackRule::Rule(1, 1, <#FightMap *map#>)
//    // this->cardSprite->runAction(Sequence::create(animateAction, CallFunc::create(CC_CALLBACK_0(HuangDiCard::actionBlock,this)), NULL));
//    
//    
//    
//}

void HouYiCard::nuQiManage() {
//    if (this->fPro->nuqiPro->getPercentage() < 100) {
//        this->fPro->setNuQiProPrecent(34+this->fPro->nuqiPro->getPercentage());
//    }
    this->addNuQi(this, 1);
}

void HouYiCard::hitAction() {
    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if (cellNum != 100) {
        if ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj != NULL) {
            ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->didBeHit(this,"wuli");
            //        if ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum)->obj) != NULL) {
            //            if (((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->nuqiPro->getPercentage() < 100) {
            //                ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->setNuQiProPrecent(34+((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->fPro->nuqiPro->getPercentage());
            //            }
            //        }
            this->addNuQi((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum)->obj), 1);
        }
    }
 
}



void HouYiCard::ultimateSkill() {
    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    Vector<MapCell*> temp = this->forEnemy->fMap->hitNineCell(cellNum);
    for (int i = 0; i < temp.size(); i++) {
        this->addNuQi((Card*)(temp.at(i))->obj, 1);
//        if (((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage() < 100) {
//            ((Card*)(temp.at(i))->obj)->fPro->setNuQiProPrecent(100/3+((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage());
//        }
        ((Card*)(temp.at(i))->obj)->didBeHit(this,"wuli");
    }
    this->decreaseNuQi(this, 3,true);
    //this->fPro->setNuQiProPrecent(0);
}