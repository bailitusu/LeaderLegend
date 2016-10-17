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
#include "OneRecord.h"
#include "RecordFight.h"
#include "ReadRecordFight.h"
#include "ActionWait.h"
#include "CommonFunc.h"
bool TaoTieCard::init() {
    this->cellIndex = 0;
    this->HP = 20000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.jinZhan;
    this->cardName = "taotie";
    
    this->wuLi = 87;
    this->tongShuai = 81;
    this->zhiLi = 62;
    this->mingJie = 58;
    this->yunQi = 90;
    
    this->gongJi = 17000;
    this->faLi = 17000;
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
//    this->hitValue = 2;
//    this->xiXue = 2;
    this->bingKinds = bingZhongType.jinZhan;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
    return true;
}

void TaoTieCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("panda_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pande_conjure.mp3");
}

void TaoTieCard::recordRuning(FightPlayer *enemyTemp) {
    this->forEnemy = enemyTemp;
    auto oneRecord = OneRecord::create();
    
    if (this->nuQiNum >= this->nuQiNumMax) {
        oneRecord->isXiaoZhao = false;
        oneRecord->isDaZhao = true;
        this->targetNum = AttackRule::Rule(this->cellIndex, 2, this->forEnemy->fMap);
    }else {
        oneRecord->isXiaoZhao = true;
        oneRecord->isDaZhao = false;
       this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    }

    oneRecord->hitTarget = this->targetNum;
    oneRecord->cardName = this->cardName;
    oneRecord->playerName = this->playerName;
    oneRecord->standIndex = this->cellIndex;


    if (this->nuQiNum < this->nuQiNumMax) {

        RecordFight::GetInstance()->addItemToRecord(oneRecord);
        
        this->recordHit();
        this->recordAddNuqi(this, 1);
        this->recordActionBlock();
    }else {

        RecordFight::GetInstance()->addItemToRecord(oneRecord);
        this->recordUltimateSkill();
        this->recordActionBlock();
        // this->cardSprite->runAction(Sequence::create(maxHit,block, NULL));
    }


}

//void TaoTieCard::running(FightPlayer *enemyTemp) {
//    this->forEnemy = enemyTemp;
//    
//    
//    auto defaultPosition = this->cardSprite->getPosition();
//    if (this->fPro->nuqiPro->getPercentage() >= 100) {
//        this->targetNum = AttackRule::Rule(this->cellIndex, 2, this->forEnemy->fMap);
//    }else {
//       this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap); 
//    }
//    
//    
//    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.x;
//    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
//    
//    auto moveTo = MoveTo::create(1.0, target);
//    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
//    
//    auto hit = CallFunc::create(CC_CALLBACK_0(TaoTieCard::hitAction,this));
//    auto maxHit = CallFunc::create(CC_CALLBACK_0(TaoTieCard::ultimateSkill, this));
//    auto addNuqi = CallFunc::create(CC_CALLBACK_0(TaoTieCard::nuQiManage, this));
//    auto block = CallFunc::create(CC_CALLBACK_0(TaoTieCard::actionBlock,this));
//    if (this->fPro->nuqiPro->getPercentage() < 100) {
//        
//        this->cardSprite->runAction(Sequence::create(moveTo,hit,movaFanhui,addNuqi,block,NULL));
//        
//    }else {
//        this->cardSprite->runAction(Sequence::create(moveTo,maxHit,movaFanhui, block,NULL));
//    }
//    
//    
//    
//    this->fPro->hpPro->setVisible(false);
//    this->fPro->hpProBg->setVisible(false);
//    this->fPro->nuqiPro->setVisible(false);
//    this->fPro->nuqiProBg->setVisible(false);
//    
//    // this->cardSprite->runAction(Sequence::create(animateAction, CallFunc::create(CC_CALLBACK_0(HuangDiCard::actionBlock,this)), NULL));
//    
//
//}
void TaoTieCard::xiaoHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("panda_attack.mp3",false);
}

void TaoTieCard::xiaoSkll(OneRecord *info) {
    this->stopStandAnimation();
    auto defaultPosition = this->cardSprite->getPosition();

    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-40;
    }else {
        tagetX = tagetX+40;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    Animate* gong = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        gong = CommonFunc::creatAnimation("panda_attack_r%d.png", 8, animationFactor*8, 1);
    }else {
        gong = CommonFunc::creatAnimation("panda_attack_l%d.png", 8, animationFactor*8, 1);
    }
    
   // auto gong = CommonFunc::creatAnimation("panda_attack_%d.png", 8, 1.0f, 1);
    auto move = CallFunc::create(CC_CALLBACK_0(TaoTieCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*8);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(TaoTieCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(TaoTieCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(TaoTieCard::hitBlock,this,info->affectRecordArray));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(TaoTieCard::nuQiManage, this));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(TaoTieCard::xiaoHitMusic, this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,wait,movaFanhui,moveWait,addNuqi,appear,recordBlock,NULL));
    
    this->cardSprite->runAction(Sequence::create(moveWait,gongMusic,NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);

}

void TaoTieCard::daHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("panda_conjure.mp3",false);
}

void TaoTieCard::daSkill(OneRecord *info) {
    this->stopStandAnimation();
    
    auto defaultPosition = this->cardSprite->getPosition();
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-40;
    }else {
        tagetX = tagetX+40;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    Animate* dazhao = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        dazhao = CommonFunc::creatAnimation("panda_conjure_r%d.png", 20, animationFactor*20, 1);
    }else {
        dazhao = CommonFunc::creatAnimation("panda_conjure_l%d.png", 20, animationFactor*20, 1);
    }
    
   // auto dazhao = CommonFunc::creatAnimation("panda_conjure_%d.png", 20, 1.0f, 1);
    
    auto move = CallFunc::create(CC_CALLBACK_0(TaoTieCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*8);
    auto dazhaoWait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(TaoTieCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(TaoTieCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(TaoTieCard::daHitBlock, this, info->affectRecordArray));
   // auto addNuqi = CallFunc::create(CC_CALLBACK_0(TaoTieCard::nuQiManage, this));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(TaoTieCard::daHitMusic, this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,dazhao,maxHit,dazhaoWait,movaFanhui,moveWait,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,dazhaoMusic,NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void TaoTieCard::daHitBlock(Vector<OneRecord *> affectRecordArray) {
    for (int i = 0 ; i < affectRecordArray.size(); i++) {
        auto beHitCard = affectRecordArray.at(i)->card;
        if (affectRecordArray.at(i)->isShanBi == true) {
            beHitCard->animationShanBi();
        }else {
            this->decreaseHP(beHitCard, affectRecordArray.at(i)->hitValue);
            this->decreaseNuQi(beHitCard, 1,false);
        }
    }
        this->decreaseNuQi(this, 3,true);
    
}

void TaoTieCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("panda_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("pande_conjure.mp3");
}
void TaoTieCard::moveAnimation(Vec2 target) {
    Animate* animateActionWalk = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        animateActionWalk = CommonFunc::creatAnimation("panda_move_r%d.png", 8, animationFactor*8, 1);
    }else {
        animateActionWalk = CommonFunc::creatAnimation("panda_move_l%d.png", 8, animationFactor*8, 1);
    }
    auto moveTo = MoveTo::create(animationFactor*8, target);
  //  auto animateActionWalk = CommonFunc::creatAnimation("panda_move_%d.png", 8, 0.5f, 2);
    this->cardSprite->runAction(moveTo);
    this->cardSprite->runAction(animateActionWalk);
}

void TaoTieCard::nuQiManage() {
    this->addNuQi(this, 1);
}

//void TaoTieCard::hitAction() {
////    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
////    if (cellNum != 100) {
//    if ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj != NULL) {
//        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->didBeHit(this,"wuli");
//
//        this->decreaseNuQi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1,false);
//        this->suckBlood((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj));
//        
//    }
//  
//    
//}

void TaoTieCard::recordHit() {
    if ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->recordDidBeHit(this,"wuli");
        
        this->recordDecreaseNuqi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1,false);
        //this->addHP(this, this->xiXue*0.5);
        this->recordAddHP(this, this->xiXue*0.5);
        
    }
}
void TaoTieCard::hitBlock(Vector<OneRecord *> affectRecordArray) {

    
    auto beHitCardRecord = affectRecordArray.at(0);
    if (beHitCardRecord->isShanBi == true) {
        
        beHitCardRecord->card->animationShanBi();
    }else {
        if (beHitCardRecord->card->HP > 0) {
            
            
            this->decreaseHP(beHitCardRecord->card, beHitCardRecord->hitValue);

            this->decreaseNuQi(beHitCardRecord->card, 1,false);
            this->xiXue = beHitCardRecord->hitValue;
            this->suckBlood(this);
            
        }
    }

}


void TaoTieCard::recordUltimateSkill() {
    int cellNum = AttackRule::Rule(this->cellIndex, 2, this->forEnemy->fMap);
    Vector<MapCell*> temp = this->forEnemy->fMap->hitNineCell(cellNum);
    for (int i = 0; i < temp.size(); i++) {
        this->recordDecreaseNuqi((Card*)(temp.at(i))->obj, 1,false);

        
        ((Card*)(temp.at(i))->obj)->recordDidBeHit(this,"fashu");
    }
    this->recordDecreaseNuqi(this, 3,true);
}

void TaoTieCard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        zhanli = CommonFunc::creatAnimation("panda_stand_r%d.png", 4, animationFactor*4, 1);
    }else {
        zhanli = CommonFunc::creatAnimation("panda_stand_l%d.png", 4, animationFactor*4, 1);
    }
    
 //   auto zhanli = CommonFunc::creatAnimation("panda_stand_%d.png", 4, 0.5f, 1);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}
//void TaoTieCard::ultimateSkill() {
//    int cellNum = AttackRule::Rule(this->cellIndex, 2, this->forEnemy->fMap);
//    Vector<MapCell*> temp = this->forEnemy->fMap->hitNineCell(cellNum);
//    for (int i = 0; i < temp.size(); i++) {
//        this->decreaseNuQi((Card*)(temp.at(i))->obj, 1,false);
////        if (((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage() < 100) {
////            ((Card*)(temp.at(i))->obj)->fPro->setNuQiProPrecent(((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage()- 100/3);
////        }
//        
//        ((Card*)(temp.at(i))->obj)->didBeHit(this,"fashu");
//    }
//    this->decreaseNuQi(this, 3,true);
//   // this->fPro->setNuQiProPrecent(0);
//}
