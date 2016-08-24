//
//  HuangDiCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/12.
//
//

#include "HuangDiCard.h"
#include "CommonFunc.h"
#include "Setting.h"
#include <iostream>
#include <stdlib.h>
#include "string.h"
#include "AttackRule.h"
#include "FightPlayer.h"
#include "MapCell.h"
bool HuangDiCard::init() {
    cellIndex = 0;
    HP = 20;
    this->cardName = "huangdi";
    this->hitValue = 2;
    this->MaxHP = 20;
    return true;
}

//void HuangDiCard::initCardSprite(std::string imageName) {
//    cardSprite = Sprite::create(imageName);
//    cardSprite->setAnchorPoint(Vec2(0.5, 0));
//    // player->setFlippedX(true);
//    CommonFunc::setSpriteSize(cardSprite, screenSize.width*0.075);
//}

void HuangDiCard::didBeHit(Card* fromCard) {
  //  log("huangdi hart %d",hitValue);

    float percent = (1 - (HP-fromCard->hitValue)/this->MaxHP) * 100;
  //  float aaa = this->fPro->hpPro->getPercentage();
    ProgressFromTo* ac = ProgressFromTo::create(1.0, this->fPro->hpPro->getPercentage(), percent);
    this->fPro->hpPro->runAction(ac);
    HP = HP - fromCard->hitValue;
    if (HP <= 0) {
        this->cardDead();
        return;
    }
    if (this->fPro->nuqiPro->getPercentage() < 100 && HP > 0) {
        this->fPro->setNuQiProPrecent(100/3+this->fPro->nuqiPro->getPercentage());
    }else {
        return;
    }

   // std::cout << "huangdi hart" << hitValue << std::endl;
}

void HuangDiCard::cardDead() {
    
    this->forPlayer->fMap->mapCellArray.at(this->cellIndex)->obj = NULL;
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    this->cardSprite->removeFromParent();
}

void HuangDiCard::runAnimation(FightPlayer* playerTemp) {
   // AttackRule::Rule(1, 1, <#FightMap *map#>)
    this->forEnemy = playerTemp;
    

    auto defaultPosition = this->cardSprite->getPosition();
    int cellNum = AttackRule::Rule(this->cellIndex, 1, this->forEnemy->fMap);
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(cellNum)->position.x;
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(cellNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
   // Vec2 target = this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    auto moveTo = MoveTo::create(1.0, target);
    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
   // auto aaa = moveTo->reverse();
    
    
//    auto animation = Animation::create();
//    for (int i = 0; i < 14; i++) {
//        std::ostringstream stringFarmat;
//        stringFarmat << "huangdi_walk_up" << i << ".png";
//        std::string szName = stringFarmat.str();
////        szName.initWithFormat("huangdi_walk_up%d.png", i);
//       // sprintf(szName, "huangdi_walk_up%d.png", i);
//        animation->addSpriteFrameWithFile(szName);
//    }
//    animation->setDelayPerUnit(1.0f/13);
//    animation->setRestoreOriginalFrame(true);
//    animation->setLoops(1);
//    auto animateAction = Animate::create(animation);
    
    this->cardSprite->runAction(Sequence::create(moveTo,movaFanhui, CallFunc::create(CC_CALLBACK_0(HuangDiCard::actionBlock,this)),NULL));
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    
   // this->cardSprite->runAction(Sequence::create(animateAction, CallFunc::create(CC_CALLBACK_0(HuangDiCard::actionBlock,this)), NULL));
    
    

}

void HuangDiCard::actionBlock() {
    if (this->fPro->nuqiPro->getPercentage() < 100) {
        this->fPro->setNuQiProPrecent(34+this->fPro->nuqiPro->getPercentage());
    }else {
        this->ultimateSkill();
    }
    
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    int cellNum = AttackRule::Rule(this->cellIndex, 1, this->forEnemy->fMap);
    ((Card*)(this->forEnemy->fMap->mapCellArray.at(cellNum))->obj)->didBeHit(this);
    
    
    
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

void HuangDiCard::ultimateSkill() {
    this->fPro->setNuQiProPrecent(0);
}


