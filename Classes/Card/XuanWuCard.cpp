//
//  XuanWuCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#include "XuanWuCard.h"
#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "ActionWait.h"
#include "MingZhongBuff.h"
#include "Setting.h"

#include "CommonFunc.h"
#include "OneRecord.h"
#include "RecordFight.h"
#include "ReadRecordFight.h"
bool XuanWuCard::init() {
    this->cellIndex = 0;
    this->HP = 22000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.jinZhan;
    this->cardName = "xuanwu";
    this->cardSpriteImageName = "niutou_stand";
    this->xiaoZhaoInfo = "鸠抓";
    this->daZhaoInfo = "滚筒洗衣机";
    this->wuLi = 72;
    this->tongShuai = 97;
    this->zhiLi = 85;
    this->mingJie = 25;
    this->yunQi = 100;
    
    this->gongJi = 15000;
    this->faLi = 19000;
    this->fangYu = 22000;
//    this->wuliHart = 10;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 10;
//    this->baoJi = 10;
//    this->mianBao = 10;
//    this->lianJi = 1;
    this->bingKinds = bingZhongType.fangYu;
//    this->hitValue = 2;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
    return true;
}

void XuanWuCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("niutou_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("niutou_conjure.mp3");
}

void XuanWuCard::initCharacter() {
    this->zhiLiao = this->MaxHP*0.15;
    this->geDang = 0.2;
}

//void XuanWuCard::running(FightPlayer *enemyTemp) {
//    this->forEnemy = enemyTemp;
//
//    
//    auto defaultPosition = this->cardSprite->getPosition();
//    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    
//    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.x;
//    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
//    auto zaiSheng = CallFunc::create(CC_CALLBACK_0(XuanWuCard::zaiShengAction,this));
//    auto moveTo = MoveTo::create(1.0, target);
//    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
//    
//    auto hit = CallFunc::create(CC_CALLBACK_0(XuanWuCard::hitAction,this));
//    auto maxHit = CallFunc::create(CC_CALLBACK_0(XuanWuCard::ultimateSkill, this));
//    auto addNuqi = CallFunc::create(CC_CALLBACK_0(XuanWuCard::nuQiManage, this));
//    auto block = CallFunc::create(CC_CALLBACK_0(XuanWuCard::actionBlock,this));
//    if (this->fPro->nuqiPro->getPercentage() < 100) {
//
//        this->cardSprite->runAction(Sequence::create(zaiSheng,moveTo,hit,movaFanhui,addNuqi,block,NULL));
//        
//    }else {
//        this->cardSprite->runAction(Sequence::create(zaiSheng,moveTo,maxHit,movaFanhui, block,NULL));
//    }
//    
//    
//    
//    this->fPro->hpPro->setVisible(false);
//    this->fPro->hpProBg->setVisible(false);
//    this->fPro->nuqiPro->setVisible(false);
//    this->fPro->nuqiProBg->setVisible(false);
//    
//
//}

void XuanWuCard::recordRuning(FightPlayer *enemyTemp) {
    this->forEnemy = enemyTemp;

    this->forEnemy = enemyTemp;
    auto oneRecord = OneRecord::create();
    

    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    oneRecord->hitTarget = this->targetNum;
    oneRecord->cardName = this->cardName;
    oneRecord->playerName = this->playerName;
    oneRecord->standIndex = this->cellIndex;
    oneRecord->currentHP = this->HP;
    
    if (this->nuQiNum < this->nuQiNumMax) {
        oneRecord->isXiaoZhao = true;
        oneRecord->isDaZhao = false;
        RecordFight::GetInstance()->addItemToRecord(oneRecord);
        this->zaiShengAction(true);
        this->recordHit();
        
        this->recordAddNuqi(this, 1);
        this->recordActionBlock();
    }else {
        oneRecord->isXiaoZhao = false;
        oneRecord->isDaZhao = true;
        RecordFight::GetInstance()->addItemToRecord(oneRecord);
        this->zaiShengAction(true);
        this->recordUltimateSkill();
        this->recordActionBlock();
        // this->cardSprite->runAction(Sequence::create(maxHit,block, NULL));
    }
    
    

}

void XuanWuCard::zaiShengAction(bool isRecord) {
    //printf("%d %s xuanwu %d \n",this->cellIndex, this->playerName.c_str(), this->HP);
    this->zaiShengBlood(isRecord);
    //printf("%d %s xuanwu %d %f \n",this->cellIndex, this->playerName.c_str(), this->HP, this->fPro->hpPro->getPercentage());
    
}



void XuanWuCard::nuQiManage(OneRecord *info) {
    this->nuQiAppear(this, info->nuQiChange);
}



void XuanWuCard::recordHit() {
   // int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->recordDidBeHit(this,"wuli");
        
        this->recordAddNuqi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);

    }
  
}

void XuanWuCard::daHitBlock(Vector<OneRecord*> affectRecordArray) {
    for (int i = 0 ; i < affectRecordArray.size(); i++) {
        auto beHitCard = affectRecordArray.at(i)->card;
        if (affectRecordArray.at(i)->isShanBi == true) {
            beHitCard->animationShanBi();
        }else {
            this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
//            if (beHitCard != NULL) {
//                auto mingZhongBuff = MingZhongBuff::create();
//                mingZhongBuff->decreaseBuff(beHitCard,0.1);
//            }
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange);
        }
    }
   // this->decreaseNuQi(this, 3, true);
}

void XuanWuCard::xiaoHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("niutou_attack.mp3",false);
}

void XuanWuCard::xiaoSkll(OneRecord *info) {
    this->stopStandAnimation();
    auto defaultPosition = this->cardSprite->getPosition();

    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-40;
    }else {
        tagetX = tagetX+40;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
  //  this->zaiShengAction(false);

    
    Animate* gong = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        gong = CommonFunc::creatAnimation("niutou_attack_r%d.png", 20, animationFactor*20, 1);
    }else {
        gong = CommonFunc::creatAnimation("niutou_attack_l%d.png", 20, animationFactor*20, 1);
    }
    
   // auto gong = CommonFunc::creatAnimation("niutou_attack_%d.png", 20, 1.0f, 1);
    auto move = CallFunc::create(CC_CALLBACK_0(XuanWuCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*8);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(XuanWuCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(XuanWuCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(XuanWuCard::hitBlock,this,info->affectRecordArray));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(XuanWuCard::nuQiManage, this,info));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(XuanWuCard::xiaoHitMusic, this));
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,wait,movaFanhui,moveWait,addNuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,gongMusic, NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void XuanWuCard::hitBlock(Vector<OneRecord *> affectRecordArray) {
    
    for (int i = 0 ; i < affectRecordArray.size(); i++) {
        auto beHitCard = affectRecordArray.at(i)->card;
        if (affectRecordArray.at(i)->isShanBi == true) {
            beHitCard->animationShanBi();
        }else {
            beHitCard->HP = affectRecordArray.at(i)->currentHP;
            beHitCard->MaxHP = affectRecordArray.at(i)->maxHP;
            this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
            //            if (beHitCard != NULL) {
            //                auto mingZhongBuff = MingZhongBuff::create();
            //                mingZhongBuff->decreaseBuff(beHitCard,0.1);
            //            }
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange);
        }
    }
    
    
//    auto beHitCardRecord = affectRecordArray.at(0);
//    if (beHitCardRecord->isShanBi == true) {
//        
//        beHitCardRecord->card->animationShanBi();
//    }else {
//        if (beHitCardRecord->card->HP > 0) {
//            
//            
//            this->decreaseHP(beHitCardRecord->card, beHitCardRecord->hitValue);
//            
//            this->addNuQi(beHitCardRecord->card, 1);
//            
//        }
//    }
}

void XuanWuCard::daHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("niutou_conjure.mp3",false);
}

void XuanWuCard::daSkill(OneRecord *info) {
    this->stopStandAnimation();
    auto defaultPosition = this->cardSprite->getPosition();

  //  this->zaiShengAction(false);
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-40;
    }else {
        tagetX = tagetX+40;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    Animate* dazhao = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        dazhao = CommonFunc::creatAnimation("niutou_conjure_r%d.png", 20, animationFactor*20, 1);
    }else {
        dazhao = CommonFunc::creatAnimation("niutou_conjure_l%d.png", 20, animationFactor*20, 1);
    }
    
 //   auto dazhao = CommonFunc::creatAnimation("niutou_conjure_%d.png", 20, 1.0f, 1);
    
    auto move = CallFunc::create(CC_CALLBACK_0(XuanWuCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*8);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(XuanWuCard::moveAnimation, this, defaultPosition));
    auto nuqi = CallFunc::create(CC_CALLBACK_0(XuanWuCard::nuQiManage, this,info));
    auto appear = CallFunc::create(CC_CALLBACK_0(XuanWuCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(XuanWuCard::daHitBlock, this, info->affectRecordArray));
    // auto addNuqi = CallFunc::create(CC_CALLBACK_0(TaoTieCard::nuQiManage, this));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(XuanWuCard::daHitMusic, this));
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    
    this->cardSprite->runAction(Sequence::create(move,moveWait,dazhao,maxHit,wait,movaFanhui,moveWait,nuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,dazhaoMusic, NULL));
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void XuanWuCard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        zhanli = CommonFunc::creatAnimation("niutou_stand_r%d.png", 4, animationFactor*4*1.5, 1);
    }else {
        zhanli = CommonFunc::creatAnimation("niutou_stand_l%d.png", 4, animationFactor*4*1.5, 1);
    }
    
   // auto zhanli = CommonFunc::creatAnimation("niutou_stand_%d.png", 4, 0.5f, 2);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}

void XuanWuCard::moveAnimation(Vec2 target) {
    Animate* animateActionWalk = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        animateActionWalk = CommonFunc::creatAnimation("niutou_move_r%d.png", 8, animationFactor*8, 1);
    }else {
        animateActionWalk = CommonFunc::creatAnimation("niutou_move_l%d.png", 8, animationFactor*8, 1);
    }
    
    auto moveTo = MoveTo::create(animationFactor*8, target);
 //   auto animateActionWalk = CommonFunc::creatAnimation("niutou_move_%d.png", 8, 0.5f, 2);
    this->cardSprite->runAction(moveTo);
    this->cardSprite->runAction(animateActionWalk);
}

void XuanWuCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("niutou_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("niutou_conjure.mp3");
}

void XuanWuCard::recordUltimateSkill() {
    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    Vector<MapCell*> temp = this->forEnemy->fMap->hitHengPaiCell(cellNum);
    for (int i = 0; i < temp.size(); i++) {
        this->recordAddNuqi((Card*)(temp.at(i))->obj, 1);

        ((Card*)(temp.at(i))->obj)->recordDidBeHit(this,"fashu");
        if (((Card*)(temp.at(i))->obj) != NULL) {
            auto mingZhongBuff = MingZhongBuff::create();
            mingZhongBuff->decreaseBuff(((Card*)(temp.at(i))->obj),0.1);
        }

    }

    this->recordDecreaseNuqi(this, 3,true);
}

//void XuanWuCard::ultimateSkill() {
//    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    Vector<MapCell*> temp = this->forEnemy->fMap->hitHengPaiCell(cellNum);
//    for (int i = 0; i < temp.size(); i++) {
//        this->addNuQi((Card*)(temp.at(i))->obj, 1);
////        if (((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage() < 100) {
////            ((Card*)(temp.at(i))->obj)->fPro->setNuQiProPrecent(100/3+((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage());
////        }
//        ((Card*)(temp.at(i))->obj)->didBeHit(this,"fashu");
//        if (((Card*)(temp.at(i))->obj) != NULL) {
//            auto mingZhongBuff = MingZhongBuff::create();
//            mingZhongBuff->decreaseBuff(((Card*)(temp.at(i))->obj),0.1);
//        }
//
//    }
//
//    this->decreaseNuQi(this, 3,true);
//}
