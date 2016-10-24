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

#include "CommonFunc.h"
#include "OneRecord.h"
#include "RecordFight.h"
#include "ReadRecordFight.h"
bool FengHouCard::init() {
    this->cellIndex = 0;
    this->HP = 19000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.jinZhan;
    this->cardName = "fenghou";
    this->cardSpriteImageName = "gugong_stand";
    this->xiaoZhaoInfo = "一即当前";
    this->daZhaoInfo = "统帅天下";
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


void FengHouCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("gugong_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("gugong_conjure.mp3");
}

void FengHouCard::recordRuning(FightPlayer *enemyTemp) {
    this->forEnemy = enemyTemp;

    auto oneRecord = OneRecord::create();
    
    
    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    oneRecord->hitTarget = this->targetNum;
    oneRecord->cardName = this->cardName;
    oneRecord->playerName = this->playerName;
    oneRecord->standIndex = this->cellIndex;
    
    
    if (this->nuQiNum < this->nuQiNumMax) {
        oneRecord->isXiaoZhao = true;
        oneRecord->isDaZhao = false;
        RecordFight::GetInstance()->addItemToRecord(oneRecord);
        this->recordHit();
        
        this->recordAddNuqi(this, 1);
        this->recordActionBlock();
    }else {
        oneRecord->isXiaoZhao = false;
        oneRecord->isDaZhao = true;
        RecordFight::GetInstance()->addItemToRecord(oneRecord);

        this->recordUltimateSkill();
        this->recordActionBlock();
        // this->cardSprite->runAction(Sequence::create(maxHit,block, NULL));
    }

}

//void FengHouCard::running(FightPlayer *enemyTemp) {
//    
//    this->forEnemy = enemyTemp;
//    
//    
//    auto defaultPosition = this->cardSprite->getPosition();
//    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    
//    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.x;
//    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
//    
//    auto moveTo = MoveTo::create(1.0, target);
//    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
//    
//    auto hit = CallFunc::create(CC_CALLBACK_0(FengHouCard::hitAction,this));
//    //auto wait = ActionWait::create(0.1);
//    auto maxHit = CallFunc::create(CC_CALLBACK_0(FengHouCard::ultimateSkill, this));
//    auto addNuqi = CallFunc::create(CC_CALLBACK_0(FengHouCard::nuQiManage, this));
//    auto block = CallFunc::create(CC_CALLBACK_0(FengHouCard::actionBlock,this));
//    if (this->fPro->nuqiPro->getPercentage() < 100) {
//        
//        this->cardSprite->runAction(Sequence::create(moveTo,hit,movaFanhui,addNuqi,block,NULL));
//        
//    }else {
//        this->cardSprite->runAction(Sequence::create(moveTo,maxHit,movaFanhui,block,NULL));
//    }
//    
//    
//    
//    this->fPro->hpPro->setVisible(false);
//    this->fPro->hpProBg->setVisible(false);
//    this->fPro->nuqiPro->setVisible(false);
//    this->fPro->nuqiProBg->setVisible(false);
//    
//}


void FengHouCard::nuQiManage() {
    this->addNuQi(this, 1);

    Vector<MapCell*> temp = this->forPlayer->fMap->hitNineCell(this->cellIndex);
    for (int i = 0; i < temp.size(); i++) {
        this->addNuQi((Card*)(temp.at(i))->obj, 1);
    }

}

void FengHouCard::recordHit() {
//    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if (((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj) != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->recordDidBeHit(this,"wuli");

        this->recordAddNuqi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);
        
    }
    Vector<MapCell*> temp = this->forPlayer->fMap->hitNineCell(this->cellIndex);
    for (int i = 0; i < temp.size(); i++) {
        this->recordAddNuqi((Card*)(temp.at(i))->obj, 1);
    }
}

void FengHouCard::recordUltimateSkill() {
    if (((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj) != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->recordDidBeHit(this,"wuli");

        this->recordAddNuqi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);

    }

    Vector<MapCell*> temp = this->forPlayer->fMap->hitAllCell();
    for (int i = 0; i < temp.size(); i++) {
        if (((Card*)(temp.at(i))->obj)->cellIndex != this->cellIndex) {
            this->recordAddNuqi((Card*)(temp.at(i))->obj, 1);
        }

        if (((Card*)(temp.at(i))->obj) != NULL) {
            auto zhenFen = ZhenFenBuff::create();
            zhenFen->addBuff(((Card*)(temp.at(i))->obj),0);
            auto baoJi = BaojiBuff::create();
            baoJi->addBuff(((Card*)(temp.at(i))->obj),0.2);

        }
    }
    
    this->recordDecreaseNuqi(this, 3, true);
}


void FengHouCard::xiaoHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("gugong_attack.mp3",false);
}
void FengHouCard::xiaoSkll(OneRecord *info) {
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
        gong = CommonFunc::creatAnimation("gugong_attack_r%d.png", 12, animationFactor*12, 1);
    }else {
        gong = CommonFunc::creatAnimation("gugong_attack_l%d.png", 12, animationFactor*12, 1);
    }
   // auto gong = CommonFunc::creatAnimation("gugong_attack_%d.png", 12, 1.0f, 1);
    auto move = CallFunc::create(CC_CALLBACK_0(FengHouCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*7);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(FengHouCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(FengHouCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(FengHouCard::hitBlock,this,info->affectRecordArray));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(FengHouCard::nuQiManage, this));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(FengHouCard::xiaoHitMusic, this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,wait,movaFanhui,moveWait,addNuqi,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,gongMusic, NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);

}

void FengHouCard::moveAnimation(Vec2 target) {
    Animate* animateActionWalk = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        animateActionWalk = CommonFunc::creatAnimation("gugong_move_r%d.png", 7, animationFactor*7, 1);
    }else {
        animateActionWalk = CommonFunc::creatAnimation("gugong_move_l%d.png", 7, animationFactor*7, 1);
    }
    
    auto moveTo = MoveTo::create(animationFactor*7, target);
   // auto animateActionWalk = CommonFunc::creatAnimation("gugong_move_%d.png", 7, 0.5f, 2);
    this->cardSprite->runAction(moveTo);
    this->cardSprite->runAction(animateActionWalk);
}

void FengHouCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("gugong_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("gugong_conjure.mp3");
}

void FengHouCard::hitBlock(Vector<OneRecord *> affectRecordArray) {
    auto beHitCardRecord = affectRecordArray.at(0);
    if (beHitCardRecord->isShanBi == true) {
        
        beHitCardRecord->card->animationShanBi();
    }else {
        if (beHitCardRecord->card->HP > 0) {
            
            
            this->decreaseHP(beHitCardRecord->card, beHitCardRecord->hitValue);
            
            this->addNuQi(beHitCardRecord->card,1);
            
        }
    }
}


void FengHouCard::daHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("gugong_conjure.mp3",false);
}

void FengHouCard::daSkill(OneRecord *info) {
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
        dazhao = CommonFunc::creatAnimation("gugong_conjure_r%d.png", 12, animationFactor*12, 1);
    }else {
        dazhao = CommonFunc::creatAnimation("gugong_conjure_l%d.png", 12, animationFactor*12, 1);
    }
   // auto dazhao = CommonFunc::creatAnimation("gugong_conjure_%d.png", 11, 1.0f, 1);
    
    auto move = CallFunc::create(CC_CALLBACK_0(FengHouCard::moveAnimation, this, target));
    auto wait = ActionWait::create(1.0);
    auto moveWait = ActionWait::create(animationFactor*7);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(FengHouCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(FengHouCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(FengHouCard::daHitBlock, this, info->affectRecordArray));
    // auto addNuqi = CallFunc::create(CC_CALLBACK_0(TaoTieCard::nuQiManage, this));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(FengHouCard::daHitMusic, this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,dazhao,maxHit,wait,movaFanhui,moveWait,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,dazhaoMusic, NULL));
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void FengHouCard::daHitBlock(Vector<OneRecord*> affectRecordArray) {
    for (int i = 0 ; i < affectRecordArray.size(); i++) {
        auto beHitCard = affectRecordArray.at(i)->card;
        if (affectRecordArray.at(i)->isShanBi == true) {
            beHitCard->animationShanBi();
        }else {
            this->decreaseHP(beHitCard, affectRecordArray.at(i)->hitValue);

            this->addNuQi(beHitCard, 1);
        }
    }
    
    Vector<MapCell*> temp = this->forPlayer->fMap->hitAllCell();
    for (int i = 0; i < temp.size(); i++) {
        if (((Card*)(temp.at(i))->obj)->cellIndex != this->cellIndex) {
            this->addNuQi((Card*)(temp.at(i))->obj, 1);
        }
        
        if (((Card*)(temp.at(i))->obj) != NULL) {
            auto zhenFen = ZhenFenBuff::create();
            zhenFen->addBuff(((Card*)(temp.at(i))->obj),0);
            auto baoJi = BaojiBuff::create();
            baoJi->addBuff(((Card*)(temp.at(i))->obj),0.2);
            
        }
    }
    this->decreaseNuQi(this, 3, true);
}

void FengHouCard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        zhanli = CommonFunc::creatAnimation("gugong_stand_r%d.png", 5, animationFactor*5, 1);
    }else {
        zhanli = CommonFunc::creatAnimation("gugong_stand_l%d.png", 5, animationFactor*5, 1);
    }
    
  //  auto zhanli = CommonFunc::creatAnimation("gugong_stand_%d.png", 5, 0.5f, 2);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}
//void FengHouCard::ultimateSkill() {
////    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    if (((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj) != NULL) {
//        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->didBeHit(this,"wuli");
//        
//        this->addNuQi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);
//        
//    }
//    
//    Vector<MapCell*> temp = this->forPlayer->fMap->hitAllCell();
//    for (int i = 0; i < temp.size(); i++) {
//        if (((Card*)(temp.at(i))->obj)->cellIndex != this->cellIndex) {
//            this->addNuQi((Card*)(temp.at(i))->obj, 1);
//        }
//        
//        if (((Card*)(temp.at(i))->obj) != NULL) {
//            auto zhenFen = ZhenFenBuff::create();
//            zhenFen->addBuff(((Card*)(temp.at(i))->obj),0);
//            auto baoJi = BaojiBuff::create();
//            baoJi->addBuff(((Card*)(temp.at(i))->obj),0.2);
//            
//        }
//    }
//    
//    this->decreaseNuQi(this, 3, true);
//}
