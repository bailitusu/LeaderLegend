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
#include "FightProgress.h"
bool XingTianCard::init() {
    this->cellIndex = 0;
    this->HP = 20000;
    
    this->hitRuleNum = hitRuleType.jinZhan;
    this->cardName = "xingtian";
    this->cardSpriteImageName = "jiansheng_stand";
    this->xiaoZhaoInfo = "近战物理伤害";
    this->daZhaoInfo = "对单个目标造成3次物理伤害";
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


void XingTianCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("jiansheng_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("jiansheng_conjure.mp3");
}

void XingTianCard::initCharacter() {
    this->geDang = 0.15;
}

//
//void XingTianCard::recordRuning(FightPlayer *enemyTemp) {
//    this->forEnemy = enemyTemp;
//    auto oneRecord = OneRecord::create();
//    
//
//    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    oneRecord->hitTarget = this->targetNum;
//    oneRecord->cardName = this->cardName;
//    oneRecord->playerName = this->playerName;
//    oneRecord->standIndex = this->cellIndex;
//    
//    
//    if (this->nuQiNum < this->nuQiNumMax) {
//        oneRecord->isXiaoZhao = true;
//        oneRecord->isDaZhao = false;
//        RecordFight::GetInstance()->addItemToRecord(oneRecord);
//        
//        this->recordHit();
//        this->recordAddNuqi(this, 1);
//        this->recordActionBlock();
//    }else {
//        oneRecord->isXiaoZhao = false;
//        oneRecord->isDaZhao = true;
//        RecordFight::GetInstance()->addItemToRecord(oneRecord);
//        this->recordHit();
//        this->recordHit();
//        this->recordHit();
//        this->recordUltimateSkill();
//        this->recordActionBlock();
//        // this->cardSprite->runAction(Sequence::create(maxHit,block, NULL));
//    }
//
//    
//    
//}

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
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(XingTianCard::nuQiManage, this,info));
    auto appear = CallFunc::create(CC_CALLBACK_0(XingTianCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(XingTianCard::hitBlock,this,info->affectRecordArray));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(XingTianCard::xiaoHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    
    this->hitTimes = 0;
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,gongWait,movaFanhui,moveWait,addNuqi,afterAction,appear,recordBlock,NULL));
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
    
    auto nuqi = CallFunc::create(CC_CALLBACK_0(XingTianCard::nuQiManage, this,info));
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(XingTianCard::daHitMusic, this));
    
    auto dazhaoMusicWait = ActionWait::create(2.5);
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->hitTimes = 0;
    switch (info->affectRecordArray.size()) {
        case 1:
            this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,gongWait,movaFanhui,moveWait,nuqi,afterAction,appear,recordBlock,NULL));
            break;
        case 2:
            this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,gongWait,gong,hit,gongWait,movaFanhui,moveWait,nuqi,afterAction,appear,recordBlock,NULL));
            break;
        case 3:
            this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,gongWait,gong,hit,gongWait,gong,hit,gongWait,movaFanhui,moveWait,nuqi,afterAction,appear,recordBlock,NULL));
            break;

    }
 //   this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,gongWait,gong,hit,gongWait,gong,hit,gongWait,movaFanhui,moveWait,maxHit,nuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,dazhaoMusic,dazhaoMusicWait,dazhaoMusic,dazhaoMusicWait,dazhaoMusic,dazhaoMusicWait,NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void XingTianCard::hitBlock(Vector<OneRecord *> affectRecordArray) {
//    if (affectRecordArray.size() >= 2) {
//        if (this->hitTimes > 2 ) {
//            this->hitTimes = 0;
//        }
//    }else {
//        this->hitTimes = 0;
//    }
    
    auto beHitCardRecord = affectRecordArray.at(this->hitTimes);
    if (beHitCardRecord->isShanBi == true) {
        
        beHitCardRecord->card->animationShanBi();
    }else {
     //   if (beHitCardRecord->card->HP > 0) {
            
        beHitCardRecord->card->MaxHP = beHitCardRecord->maxHP;
        beHitCardRecord->card->HP = beHitCardRecord->currentHP;
        
        if (beHitCardRecord->isBaoJi == true) {
            this->hpAppear(beHitCardRecord->card, beHitCardRecord->hitValue, beHitCardRecord->currentHP,"暴击");
        }else if(beHitCardRecord->isGeDang == true) {
            this->hpAppear(beHitCardRecord->card, beHitCardRecord->hitValue, beHitCardRecord->currentHP,"格挡");
        }else {
            this->hpAppear(beHitCardRecord->card, beHitCardRecord->hitValue, beHitCardRecord->currentHP,"");
        }
      //  this->hpAppear(beHitCardRecord->card, beHitCardRecord->hitValue, beHitCardRecord->currentHP);

        this->nuQiAppear(beHitCardRecord->card, beHitCardRecord->nuQiChange);
            
       // }
    }
    this->hitTimes++;
}

void XingTianCard::daHitBlock(Vector<OneRecord *> affectRecordArray) {
//        auto geDangBuff = GeDangBuff::create();
//        geDangBuff->addBuff(this,0.5);
//
//        this->decreaseNuQi(this, 3,true);
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

void XingTianCard::nuQiManage(OneRecord *info) {
    this->nuQiAppear(this, info->nuQiChange);
}

//void XingTianCard::recordHit() {
//    
//    
//  //  int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    if (((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj) != NULL) {
//        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->recordDidBeHit(this,"wuli");
//
//        this->recordAddNuqi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);
//
//    }
//    
//    
//    
//}
//void XingTianCard::recordUltimateSkill() {
//        auto geDangBuff = GeDangBuff::create();
//        geDangBuff->addBuff(this,0.5);
//      //  geDangBuff->retain();
//    //    this->buffArray
//    //    this->geDang = this->geDang*0.15 + this->geDang;
//        this->recordDecreaseNuqi(this, 3,true);
//}

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

