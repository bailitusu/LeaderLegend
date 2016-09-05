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
#include "ActionWait.h"
#include "CommonFunc.h"
bool HouYiCard::init() {
    this->cellIndex = 0;
    this->HP = 18000;
    
    this->hitRuleNum = hitRuleType.gongJian;
    this->cardName = "houyi";
    
    this->wuLi = 92;
    this->tongShuai = 70;
    this->zhiLi = 65;
    this->mingJie = 95;
    this->yunQi = 78;
    
    this->gongJi = 20000;
    this->faLi = 17000;
    this->fangYu = 18000;
//    this->wuliHart = 10;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 10;
//    this->baoJi = 10;
//    this->mianBao = 10;
  //  this->lianJi = 2;
    this->bingKinds = bingZhongType.yuanCheng;
//    this->hitValue = 2;
    this->hitLevel = 1.25;
    //this->geDang = 0.15;
    this->cardLevel = 60;
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
    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if (this->targetNum == 100) {
        return;
    }
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.x;
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    this->cardSprite->stopActionByTag(10);
    auto gong = CommonFunc::creatAnimation("xiaoheihit_%d.png", 22, 1.5f, 1);
    auto dazhao = CommonFunc::creatAnimation("xiaoheidazhao_%d.png", 22, 2.0f, 1);
//    auto moveTo = MoveTo::create(1.0, target);
//    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
    
    auto hit = CallFunc::create(CC_CALLBACK_0(HouYiCard::hitAction,this));
    auto wait = ActionWait::create(1.0);
    auto maxHit = CallFunc::create(CC_CALLBACK_0(HouYiCard::ultimateSkill, this));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(HouYiCard::nuQiManage, this));
    auto block = CallFunc::create(CC_CALLBACK_0(HouYiCard::actionBlock,this));
    if (this->fPro->nuqiPro->getPercentage() < 100) {
        if (CommonFunc::isInPercent(0.5)) {
            this->cardSprite->runAction(Sequence::create(gong,hit,wait,gong,hit,wait,addNuqi,block, NULL));
      //      this->cardSprite->runAction(Sequence::create(moveTo,hit,wait,hit,movaFanhui,addNuqi,block,NULL));
        } else {
            this->cardSprite->runAction(Sequence::create(gong,hit,addNuqi,block, NULL));
       //     this->cardSprite->runAction(Sequence::create(moveTo,hit,movaFanhui,addNuqi,block,NULL));
        }
    }else {
        this->cardSprite->runAction(Sequence::create(dazhao,maxHit,block, NULL));
       // this->cardSprite->runAction(Sequence::create(moveTo,maxHit,movaFanhui,block,NULL));
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

    if ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->didBeHit(this,"wuli");

        this->addNuQi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);
    }
    
 
}



void HouYiCard::ultimateSkill() {
//    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    Vector<MapCell*> temp = this->forEnemy->fMap->hitNineCell(this->targetNum);
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