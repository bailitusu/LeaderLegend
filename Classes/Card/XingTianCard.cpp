//
//  XingTianCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#include "XingTianCard.h"

#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "ActionWait.h"
#include "Card.h"
#include "GeDangBuff.h"
#include "CommonFunc.h"
#include "Setting.h"

#include "OneRecord.h"
#include "RecordFight.h"
#include "ReadRecordFight.h"
bool XingTianCard::init() {
    this->cellIndex = 0;
    this->HP = 20000;
    
    this->hitRuleNum = hitRuleType.jinZhan;
    this->cardName = "xingtian";
    this->cardSpriteImageName = "jiansheng_stand";
    this->xiaoZhaoInfo = "盾击";
    this->daZhaoInfo = "无双乱舞";
    this->wuLi = 90;
    this->tongShuai = 88;
    this->zhiLi = 66;
    this->mingJie = 85;
    this->yunQi = 65;
    
    this->gongJi = 17000;

    this->faLi = 17000;
    this->fangYu = 20000;
    
//    this->wuliHart =1;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 10;
//    this->baoJi = 10;
//    this->mianBao = 10;
//    this->lianJi = 1;
    this->bingKinds = bingZhongType.fangYu;
   // this->hitValue = 2;
    this->hitLevel = 0.8;
    //this->geDang = 0.15;
    this->cardLevel = 60;
    return true;
}

//void XingTianCard::didBeHit(Card* fromCard, std::string hitKinds) {
//    
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
//        hartValue = hartValue*0.2;
//    }
//    hartValue = this->magicGoods->specialMianShang(this, hartValue);
//    if (CommonFunc::isInPercent(CommonFunc::reckonShanBiPercent(fromCard, this, hitKinds)) != false) {
//        // printf("%d xingtian %f\n",this->cellIndex,this->geDang);
//        
//        
//        fromCard->xiXue = hartValue;
//        this->decreaseHP(this, hartValue);
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
////        if (this->HP <= 0) {
////            this->cardDead();
////            return;
////        }
//    }else {
//        this->textLabel->setTextColor(Color4B(0, 0, 240, 255));
//        this->showLabelText(this->textLabel, 0, "ShanBi");
//    }
//}

void XingTianCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("jiansheng_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("jiansheng_conjure.mp3");
}

void XingTianCard::initCharacter() {
    this->geDang = 0.15;
}

//void XingTianCard::running(FightPlayer *enemyTemp) {
//    
//    this->forEnemy = enemyTemp;
//    
//    
//    auto defaultPosition = this->cardSprite->getPosition();
//    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    
//    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.x;
//    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
//   // this->cardSprite->setLocalZOrder(1000);
//   
//    
////    auto animationHit = Animation::create();
////    for (int i = 0; i < 15; i++) {
////        char tempName[50] = {0};
////        sprintf(tempName, "jianshenghit_%d.png",i);
////        animationHit->addSpriteFrameWithFile(tempName);
////    }
////    animationHit->setDelayPerUnit(1.0f/15);
////    animationHit->setRestoreOriginalFrame(true);
////    animationHit->setLoops(1);
////    auto animateActionHit= Animate::create(animationHit);
//   // this->cardSprite->runAction(animateActionHit);
//    auto animateActionHit = CommonFunc::creatAnimation("jianshenghit_%d.png", 15, 1.0f, 1);
//    auto moveTo = MoveTo::create(2.0, target);
//    
//    auto movaFanhui = MoveTo::create(2.0, defaultPosition);
//    
//    auto hit = CallFunc::create(CC_CALLBACK_0(XingTianCard::hitAction,this));
//    auto wait = ActionWait::create(1.0);
//    auto maxHit = CallFunc::create(CC_CALLBACK_0(XingTianCard::ultimateSkill, this));
//    auto addNuqi = CallFunc::create(CC_CALLBACK_0(XingTianCard::nuQiManage, this));
//    auto block = CallFunc::create(CC_CALLBACK_0(XingTianCard::actionBlock,this));
//    if (this->fPro->nuqiPro->getPercentage() < 100) {
//        
//        this->cardSprite->runAction(Sequence::create(moveTo,animateActionHit,hit,movaFanhui,addNuqi,block,NULL));
//        
//    }else {
//        this->cardSprite->runAction(Sequence::create(moveTo,hit,wait,hit,wait,hit,wait,maxHit,movaFanhui,block,NULL));
//    }
//    
////    auto animationWalk = Animation::create();
////        for (int i = 0; i < 17; i++) {
////            char tempName[50] = {0};
////            sprintf(tempName, "jianshengwalk_%d.png",i);
////            animationWalk->addSpriteFrameWithFile(tempName);
////        }
////    animationWalk->setDelayPerUnit(2.0f/16);
////    animationWalk->setRestoreOriginalFrame(true);
////    animationWalk->setLoops(1);
//    auto animateActionWalk = CommonFunc::creatAnimation("jianshengwalk_%d.png", 17, 2.0f, 1);
//
//    this->cardSprite->runAction(animateActionWalk);
//    
//    this->fPro->hpPro->setVisible(false);
//    this->fPro->hpProBg->setVisible(false);
//    this->fPro->nuqiPro->setVisible(false);
//    this->fPro->nuqiProBg->setVisible(false);
//    
//}
void XingTianCard::recordRuning(FightPlayer *enemyTemp) {
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
        this->recordHit();
        this->recordHit();
        this->recordHit();
        this->recordUltimateSkill();
        this->recordActionBlock();
        // this->cardSprite->runAction(Sequence::create(maxHit,block, NULL));
    }

    
    
}

void XingTianCard::xiaoHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jiansheng_attack.mp3",false);
}

void XingTianCard::xiaoSkll(OneRecord *info) {
    this->stopStandAnimation();
    auto defaultPosition = this->cardSprite->getPosition();

    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-40;
    }else {
        tagetX = tagetX+40;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    auto move = CallFunc::create(CC_CALLBACK_0(XingTianCard::moveAnimation, this, target));

    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(XingTianCard::moveAnimation, this, defaultPosition));
    
    Animate* gong = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        gong = CommonFunc::creatAnimation("jiansheng_attack_r%d.png", 15, animationFactor*15, 1);
    }else {
        gong = CommonFunc::creatAnimation("jiansheng_attack_l%d.png", 15, animationFactor*15, 1);
    }
    
   // auto gong = CommonFunc::creatAnimation("jiansheng_attack_%d.png", 15, 1.0f, 1);
    auto gongWait = ActionWait::create(1.0);
    auto moveWait = ActionWait::create(animationFactor*14);
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(XingTianCard::nuQiManage, this));
    auto appear = CallFunc::create(CC_CALLBACK_0(XingTianCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(XingTianCard::hitBlock,this,info->affectRecordArray));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(XingTianCard::xiaoHitMusic, this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,gongWait,movaFanhui,moveWait,addNuqi,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,gongMusic, NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void XingTianCard::daHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jiansheng_conjure.mp3",false);
}

void XingTianCard::daSkill(OneRecord *info) {
    this->stopStandAnimation();
    auto defaultPosition = this->cardSprite->getPosition();

    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-40;
    }else {
        tagetX = tagetX+40;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    auto move = CallFunc::create(CC_CALLBACK_0(XingTianCard::moveAnimation, this, target));
    
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(XingTianCard::moveAnimation, this, defaultPosition));
    
    Animate* gong = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        gong = CommonFunc::creatAnimation("jiansheng_attack_r%d.png", 15, animationFactor*15, 1);
    }else {
        gong = CommonFunc::creatAnimation("jiansheng_attack_l%d.png", 15, animationFactor*15, 1);
    }
    
   // auto gong = CommonFunc::creatAnimation("jiansheng_attack_%d.png", 15, 1.0f, 1);
    auto hit = CallFunc::create(CC_CALLBACK_0(XingTianCard::hitBlock,this,info->affectRecordArray));

    auto gongWait = ActionWait::create(1.0);
    auto moveWait = ActionWait::create(animationFactor*14);
    auto appear = CallFunc::create(CC_CALLBACK_0(XingTianCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(XingTianCard::daHitBlock, this, info->affectRecordArray));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(XingTianCard::daHitMusic, this));
    auto dazhaoMusicWait = ActionWait::create(2.5);
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,gongWait,gong,hit,gongWait,gong,hit,gongWait,movaFanhui,moveWait,maxHit,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,dazhaoMusic,dazhaoMusicWait,dazhaoMusic,dazhaoMusicWait,dazhaoMusic,dazhaoMusicWait,NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void XingTianCard::hitBlock(Vector<OneRecord *> affectRecordArray) {
    if (affectRecordArray.size() == 3) {
        if (this->hitTimes > 2 ) {
            this->hitTimes = 0;
        }
    }else {
        this->hitTimes = 0;
    }
    
    auto beHitCardRecord = affectRecordArray.at(this->hitTimes);
    if (beHitCardRecord->isShanBi == true) {
        
        beHitCardRecord->card->animationShanBi();
    }else {
        if (beHitCardRecord->card->HP > 0) {
            
            
            this->decreaseHP(beHitCardRecord->card, beHitCardRecord->hitValue);

            this->addNuQi(beHitCardRecord->card, 1);
            
        }
    }
    this->hitTimes++;
}

void XingTianCard::daHitBlock(Vector<OneRecord *> affectRecordArray) {
        auto geDangBuff = GeDangBuff::create();
        geDangBuff->addBuff(this,0.5);

        this->decreaseNuQi(this, 3,true);
}

void XingTianCard::moveAnimation(Vec2 target) {
    Animate* animateActionWalk = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        animateActionWalk = CommonFunc::creatAnimation("jiansheng_move_r%d.png", 14, animationFactor*14, 1);
    }else {
        animateActionWalk = CommonFunc::creatAnimation("jiansheng_move_l%d.png", 14, animationFactor*14, 1);
    }
    
    auto moveTo = MoveTo::create(animationFactor*14, target);
   // auto animateActionWalk = CommonFunc::creatAnimation("jiansheng_move_%d.png", 14, 0.5f, 2);
    this->cardSprite->runAction(moveTo);
    this->cardSprite->runAction(animateActionWalk);
}

void XingTianCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("jiansheng_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("jiansheng_conjure.mp3");
}

void XingTianCard::nuQiManage() {
    this->addNuQi(this, 1);
}

void XingTianCard::recordHit() {
    
    
  //  int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if (((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj) != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->recordDidBeHit(this,"wuli");

        this->recordAddNuqi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);

    }
    
    
    
}
void XingTianCard::recordUltimateSkill() {
        auto geDangBuff = GeDangBuff::create();
        geDangBuff->addBuff(this,0.5);
      //  geDangBuff->retain();
    //    this->buffArray
    //    this->geDang = this->geDang*0.15 + this->geDang;
        this->recordDecreaseNuqi(this, 3,true);
}

void XingTianCard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        zhanli = CommonFunc::creatAnimation("jiansheng_stand_r%d.png", 3, animationFactor*3*1.5, 1);
    }else {
        zhanli = CommonFunc::creatAnimation("jiansheng_stand_l%d.png", 3, animationFactor*3*1.5, 1);
    }
    
  //  auto zhanli = CommonFunc::creatAnimation("jiansheng_stand_%d.png", 3, 0.5f, 2);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}
//
//void XingTianCard::ultimateSkill() {
//
//    auto geDangBuff = GeDangBuff::create();
//    geDangBuff->addBuff(this,0.5);
//  //  geDangBuff->retain();
////    this->buffArray
////    this->geDang = this->geDang*0.15 + this->geDang;
//    this->decreaseNuQi(this, 3,true);
//}
