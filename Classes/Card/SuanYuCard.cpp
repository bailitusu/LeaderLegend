//
//  SuanYuCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/25.
//
//

#include "SuanYuCard.h"

#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "ActionWait.h"
#include "Card.h"
#include "CommonFunc.h"
#include "XuanYunBuff.h"

#include "CommonFunc.h"
#include "OneRecord.h"
#include "RecordFight.h"
#include "ReadRecordFight.h"
bool SuanYuCard::init() {
    this->cellIndex = 0;
    this->HP = 18000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.niao;
    this->cardName = "suanyu";
    
    this->wuLi = 81;
    this->tongShuai = 78;
    this->zhiLi = 56;
    this->mingJie = 98;
    this->yunQi = 75;
    
    this->gongJi = 19000;
    this->faLi = 17000;
    this->fangYu = 18000;
    
//    this->wuliHart = 10;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 100;
//    this->baoJi = 10;
//    this->mianBao = 10;
//    this->lianJi = 1;
    this->bingKinds = bingZhongType.yuanCheng;
//    this->hitValue = 2;
//    this->geDang = 10;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
    return true;
}

//void SuanYuCard::didBeHit(Card* fromCard, std::string hitKinds) {
//    float hartValue = CommonFunc::reckonHitValue(fromCard, this, hitKinds);
//    if (CommonFunc::isInPercent(CommonFunc::reckonBaoJiPercent(fromCard, this))) {
//        if (hitKinds == "wuli") {
//            hartValue = hartValue*1.5;
//        }else if(hitKinds == "fashu") {
//            hartValue = hartValue*1.75;
//        }
//    }
//    if (CommonFunc::isInPercent(this->geDang)) {
//        hartValue = hartValue*0.4;
//    }
//    if (fromCard->bingKinds == bingZhongType.yuanCheng) {
//        hartValue = hartValue*2;
//    }
//    hartValue = this->magicGoods->specialMianShang(this, hartValue);
//    if (CommonFunc::isInPercent(CommonFunc::reckonShanBiPercent(fromCard, this, hitKinds)) != false) {
//        
//        
//        fromCard->xiXue = hartValue;
//        this->decreaseHP(this,hartValue);
//        
//        float tempHart = 0;
//        if (hitKinds == "wuli") {
//            tempHart = this->magicGoods->fanTanWuLiHart(hartValue);
//            if (tempHart != 0) {
//                fromCard->decreaseHP(fromCard, tempHart);
//            }
//        }else if(hitKinds == "fashu") {
//            tempHart = this->magicGoods->fanTanFaShuHart(hartValue);
//            if (tempHart != 0) {
//                fromCard->decreaseHP(fromCard, tempHart);
//            }
//        }
//
//    }else {
//        this->textLabel->setTextColor(Color4B(0, 0, 240, 255));
//        this->showLabelText(this->textLabel, 0, "ShanBi");
//    }
//
//    
//}

void SuanYuCard::initCharacter() {
    this->mingZhong = 3.0;
}

//void SuanYuCard::running(FightPlayer *enemyTemp) {
//    
//    this->forEnemy = enemyTemp;
//    
//    
//    auto defaultPosition = this->cardSprite->getPosition();
//    
//    if (this->fPro->nuqiPro->getPercentage() < 100){
//        this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    }else {
//        Vector<MapCell*> temp = AttackRule::NuQiMaxRule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//        bool breakFlag = false;
//        for (int j = 5; j >= 0; j--) {
//            for (int i = 0; i < temp.size(); i++) {
//                if (((Card*)temp.at(i)->obj)->nuQiNum == j) {
//                    
//                    this->targetNum = ((Card*)temp.at(i)->obj)->cellIndex;
//                    breakFlag = true;
//                    break;
//                }
//            }
//            if (breakFlag == true) {
//                break;
//            }
//        }
//    }
//    
//
//    
//    
//    
//    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.x;
//    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
//    
//    auto moveTo = MoveTo::create(1.0, target);
//    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
//    
//    auto hit = CallFunc::create(CC_CALLBACK_0(SuanYuCard::hitAction,this));
//    auto wait = ActionWait::create(0.5);
//    auto maxHit = CallFunc::create(CC_CALLBACK_0(SuanYuCard::ultimateSkill, this));
//    auto addNuqi = CallFunc::create(CC_CALLBACK_0(SuanYuCard::nuQiManage, this));
//    auto block = CallFunc::create(CC_CALLBACK_0(SuanYuCard::actionBlock,this));
//    if (this->fPro->nuqiPro->getPercentage() < 100) {
//        
//        this->cardSprite->runAction(Sequence::create(moveTo,hit,wait,movaFanhui,addNuqi,block,NULL));
//        
//    }else {
//        this->cardSprite->runAction(Sequence::create(moveTo,maxHit,wait,movaFanhui,block,NULL));
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

void SuanYuCard::recordRuning(FightPlayer *enemyTemp) {
    this->forEnemy = enemyTemp;
    
    auto oneRecord = OneRecord::create();
    
    if (this->nuQiNum < this->nuQiNumMax){
        this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    }else {
        Vector<MapCell*> temp = AttackRule::NuQiMaxRule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
        bool breakFlag = false;
        for (int j = 5; j >= 0; j--) {
            for (int i = 0; i < temp.size(); i++) {
                if (((Card*)temp.at(i)->obj)->nuQiNum == j) {

                    this->targetNum = ((Card*)temp.at(i)->obj)->cellIndex;
                    breakFlag = true;
                    break;
                }
            }
            if (breakFlag == true) {
                break;
            }
        }
    }

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

void SuanYuCard::nuQiManage() {
    this->addNuQi(this, 1);
}

void SuanYuCard::recordHit() {
  //  int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if (((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj) != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->recordDidBeHit(this,"wuli");

        this->recordAddNuqi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);
    }
   
}

void SuanYuCard::recordUltimateSkill() {
    Vector<MapCell*> temp = AttackRule::NuQiMaxRule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    for (int j = 5; j >= 0; j--) {
        for (int i = 0; i < temp.size(); i++) {
            if (((Card*)temp.at(i)->obj)->nuQiNum == j) {

                this->recordDecreaseNuqi((Card*)temp.at(i)->obj, 1, false);
                this->recordAddNuqi(this, 1);
                ((Card*)temp.at(i)->obj)->recordDidBeHit(this, "wuli");
                this->recordDecreaseNuqi(this, 3,true);

                if (((Card*)(temp.at(i))->obj) != NULL) {
                    auto xuanYunBuff = XuanYunBuff::create();
                    xuanYunBuff->addBuff(((Card*)(temp.at(i))->obj),0);
                }
                return;
            }
        }
    }
}

void SuanYuCard::xiaoSkll(OneRecord *info) {
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
        gong = CommonFunc::creatAnimation("fengxing_attack_r%d.png", 6, animationFactor*6, 1);
    }else {
        gong = CommonFunc::creatAnimation("fengxing_attack_l%d.png", 6, animationFactor*6, 1);
    }
    
  //  auto gong = CommonFunc::creatAnimation("fengxing_attack_%d.png", 6, 0.5f, 2);
    auto move = CallFunc::create(CC_CALLBACK_0(SuanYuCard::moveAnimation, this, target));
    auto wait = ActionWait::create(1.0);
    auto moveWait = ActionWait::create(animationFactor*3*2);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(SuanYuCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(SuanYuCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(SuanYuCard::hitBlock,this,info->affectRecordArray));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(SuanYuCard::nuQiManage, this));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,wait,movaFanhui,moveWait,addNuqi,appear,recordBlock,NULL));
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    
}

void SuanYuCard::moveAnimation(Vec2 target) {
    Animate* animateActionWalk = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        animateActionWalk = CommonFunc::creatAnimation("fengxing_move_r%d.png", 3, animationFactor*3, 2);
    }else {
        animateActionWalk = CommonFunc::creatAnimation("fengxing_move_l%d.png", 3, animationFactor*3, 2);
    }
    
    auto moveTo = MoveTo::create(animationFactor*3*2, target);
  //  auto animateActionWalk = CommonFunc::creatAnimation("fengxing_move_%d.png", 3, 0.25f, 4);
    this->cardSprite->runAction(moveTo);
    this->cardSprite->runAction(animateActionWalk);
}

void SuanYuCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
}

void SuanYuCard::hitBlock(Vector<OneRecord *> affectRecordArray) {
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

void SuanYuCard::daSkill(OneRecord *info) {
    this->stopStandAnimation();
    auto defaultPosition = this->cardSprite->getPosition();

    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-15;
    }else {
        tagetX = tagetX+15;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    Animate* dazhao = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        dazhao = CommonFunc::creatAnimation("fengxing_conjure_r%d.png", 6, animationFactor*6, 1);
    }else {
        dazhao = CommonFunc::creatAnimation("fengxing_conjure_l%d.png", 6, animationFactor*6, 1);
    }
    
    //auto dazhao = CommonFunc::creatAnimation("fengxing_conjure_%d.png", 6, 0.5f, 2);
    
    auto move = CallFunc::create(CC_CALLBACK_0(SuanYuCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*3*2);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(SuanYuCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(SuanYuCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(SuanYuCard::daHitBlock, this, info->affectRecordArray));
    // auto addNuqi = CallFunc::create(CC_CALLBACK_0(TaoTieCard::nuQiManage, this));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    
    this->cardSprite->runAction(Sequence::create(move,moveWait,dazhao,maxHit,wait,movaFanhui,moveWait,appear,recordBlock,NULL));
    
}

void SuanYuCard::daHitBlock(Vector<OneRecord*> affectRecordArray) {
    for (int i = 0 ; i < affectRecordArray.size(); i++) {
        auto beHitCard = affectRecordArray.at(i)->card;
        if (affectRecordArray.at(i)->isShanBi == true) {
            beHitCard->animationShanBi();
        }else {
            this->decreaseHP(beHitCard, affectRecordArray.at(i)->hitValue);
            if (beHitCard != NULL) {
                auto xuanYunBuff = XuanYunBuff::create();
                xuanYunBuff->addBuff(beHitCard,0);
            }
            this->decreaseNuQi(beHitCard, 1,false);
        }
    }
    

    this->decreaseNuQi(this, 3, true);
}

void SuanYuCard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        zhanli = CommonFunc::creatAnimation("fengxing_stand_r%d.png", 3, animationFactor*3, 1);
    }else {
        zhanli = CommonFunc::creatAnimation("fengxing_stand_l%d.png", 3, animationFactor*3, 1);
    }
   // auto zhanli = CommonFunc::creatAnimation("fengxing_stand_%d.png", 3, 0.25f, 4);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}
//void SuanYuCard::ultimateSkill() {
//    Vector<MapCell*> temp = AttackRule::NuQiMaxRule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    for (int j = 5; j >= 0; j--) {
//        for (int i = 0; i < temp.size(); i++) {
//            if (((Card*)temp.at(i)->obj)->nuQiNum == j) {
//                
//                this->decreaseNuQi((Card*)temp.at(i)->obj, 1, false);
//                this->addNuQi(this, 1);
//                ((Card*)temp.at(i)->obj)->didBeHit(this, "wuli");
//                this->decreaseNuQi(this, 3,true);
//                
//                if (((Card*)(temp.at(i))->obj) != NULL) {
//                    auto xuanYunBuff = XuanYunBuff::create();
//                    xuanYunBuff->addBuff(((Card*)(temp.at(i))->obj),0);
//                }
//                return;
//            }
//        }
//    }
//   
//}
