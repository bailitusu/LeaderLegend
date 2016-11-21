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
#include "OneRecord.h"
#include "RecordFight.h"
#include "ReadRecordFight.h"
#include "FightProgress.h"
bool HouYiCard::init() {
    this->cellIndex = 0;
    this->HP = 18000;
    
    this->hitRuleNum = hitRuleType.gongJian;
    this->cardName = "houyi";
    this->cardSpriteImageName = "xiaohei_stand";
    this->xiaoZhaoInfo = "远程物理攻击并50%几率触发连击";
    this->daZhaoInfo = "远程物理攻击9格范围敌军";
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
    this->hitTimes = 0;
    return true;
}

void HouYiCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("xiaohei_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("xiaohei_conjure.mp3");
}


void HouYiCard::xiaoSkll(OneRecord *info) {
    this->stopStandAnimation();
    
    Animate* gong = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        gong = CommonFunc::creatAnimation("xiaohei_attack_r%d.png", 12, animationFactor*12, 0);
    }else {
        gong = CommonFunc::creatAnimation("xiaohei_attack_l%d.png", 12, animationFactor*12, 0);
    }
    
    auto wait = ActionWait::create(1.0);
    
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(HouYiCard::nuQiManage, this,info));
    auto appear = CallFunc::create(CC_CALLBACK_0(HouYiCard::appearUI, this, gong));
    auto hit = CallFunc::create(CC_CALLBACK_0(HouYiCard::hitBlock,this,info->affectRecordArray));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(HouYiCard::xiaoHitMusic, this));
    auto waitMusic = ActionWait::create(1.2);
    if (info->isLianJi == true) {
        Sequence* sequence;
        if (info->affectRecordArray.size() == 2) {
           sequence = Sequence::create(gong,hit,wait,gong,hit,wait,addNuqi,afterAction,appear,recordBlock,NULL);
        }else {
           sequence = Sequence::create(gong,hit,wait,addNuqi,afterAction,appear,recordBlock,NULL);
        }
        
        sequence->setTag(1);
        this->cardSprite->runAction(sequence);
        auto sequeceMusic = Sequence::create(gongMusic,waitMusic,gongMusic,NULL);
        this->cardSprite->runAction(sequeceMusic);
    }else {
    
        this->cardSprite->runAction(Sequence::create(gong,hit,wait,addNuqi,afterAction,appear,recordBlock,NULL));
        this->cardSprite->runAction(gongMusic);
    }
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void HouYiCard::xiaoHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("xiaohei_attack.mp3",false);
}

void HouYiCard::appearUI(Animate* tempAnimate) {
 //   this->runZhanLiAnimation();

    
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();

    
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);

    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("xiaohei_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("xiaohei_conjure.mp3");
    
}

void HouYiCard::daSkill(OneRecord *info) {
    this->stopStandAnimation();
    Animate* dazhao = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        dazhao = CommonFunc::creatAnimation("xiaohei_conjure_r%d.png", 16, animationFactor*16, 0);
    }else {
        dazhao = CommonFunc::creatAnimation("xiaohei_conjure_l%d.png", 16, animationFactor*16, 0);
    }
  //  auto dazhao = CommonFunc::creatAnimation("xiaohei_conjure_%d.png", 22, 2.0f, 1);
    auto wait = ActionWait::create(1.0);
    auto appear = CallFunc::create(CC_CALLBACK_0(HouYiCard::appearUI, this, dazhao));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(HouYiCard::daHitBlock, this, info->affectRecordArray));
    auto nuqi = CallFunc::create(CC_CALLBACK_0(HouYiCard::nuQiManage, this,info));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    
    this->cardSprite->runAction(Sequence::create(dazhao,maxHit,wait,nuqi,afterAction,wait,appear,recordBlock,NULL));
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("xiaohei_conjure.mp3");
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

//void HouYiCard::recordRuning(FightPlayer *enemyTemp) {
//    this->forEnemy = enemyTemp;
//    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    if (this->targetNum == 100) {
//        return;
//    }
//    auto oneRecord = OneRecord::create();
//    
//    oneRecord->hitTarget = this->targetNum;
//    oneRecord->cardName = this->cardName;
//    oneRecord->playerName = this->playerName;
//    oneRecord->standIndex = this->cellIndex;
//  //  printf("%d-------%s\n", this->cellIndex, this->playerName.c_str());
////
////    auto hit = CallFunc::create(CC_CALLBACK_0(HouYiCard::recordHit,this));
////    auto maxHit = CallFunc::create(CC_CALLBACK_0(HouYiCard::ultimateSkill, this));
////    auto addNuqi = CallFunc::create(CC_CALLBACK_0(HouYiCard::nuQiManage, this));
////    auto block = CallFunc::create(CC_CALLBACK_0(HouYiCard::actionBlock,this));
//    if (this->nuQiNum < this->nuQiNumMax) {
//        oneRecord->isXiaoZhao = true;
//        oneRecord->isDaZhao = false;
//        if (CommonFunc::isInPercent(0.5)) {
//            oneRecord->isLianJi = true;
//        }else {
//            oneRecord->isLianJi = false;
//        }
//        RecordFight::GetInstance()->addItemToRecord(oneRecord);
//        if (oneRecord->isLianJi == true) {
//            this->recordHit();
//            this->recordHit();
//            //this->nuQiManage();
//            this->recordAddNuqi(this, 1);
//            this->recordActionBlock();
//           // this->cardSprite->runAction(Sequence::create(hit,hit,addNuqi,block, NULL));
//        }else {
//            this->recordHit();
//           // this->nuQiManage();
//            this->recordAddNuqi(this, 1);
//            this->recordActionBlock();
//        }
//    }else {
//        oneRecord->isXiaoZhao = false;
//        oneRecord->isDaZhao = true;
//        RecordFight::GetInstance()->addItemToRecord(oneRecord);
//        this->recordUltimateSkill();
//        this->recordActionBlock();
//       // this->cardSprite->runAction(Sequence::create(maxHit,block, NULL));
//    }
//    
//    
//}

void HouYiCard::nuQiManage(OneRecord *info) {

    this->nuQiAppear(this, info->nuQiChange);
}

void HouYiCard::hitBlock( Vector<OneRecord*> affectRecordArray) {


    if (affectRecordArray.size() == 2) {
        if (this->hitTimes > 1 ) {
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
            
            if (beHitCardRecord->isBaoJi == true) {
                this->hpAppear(beHitCardRecord->card, beHitCardRecord->hitValue, beHitCardRecord->currentHP,"暴击");
            }else if(beHitCardRecord->isGeDang == true) {
                this->hpAppear(beHitCardRecord->card, beHitCardRecord->hitValue, beHitCardRecord->currentHP,"格挡");
            }else {
                this->hpAppear(beHitCardRecord->card, beHitCardRecord->hitValue, beHitCardRecord->currentHP,"");
            }
           

            this->nuQiAppear(beHitCardRecord->card, beHitCardRecord->nuQiChange);
            
            
        }
    }
    this->hitTimes++;
    
 
}

void HouYiCard::daHitBlock(Vector<OneRecord*> affectRecordArray) {
    for (int i = 0 ; i < affectRecordArray.size(); i++) {
        auto beHitCard = affectRecordArray.at(i)->card;
        if (affectRecordArray.at(i)->isShanBi == true) {
            beHitCard->animationShanBi();
        }else {
            
            if (affectRecordArray.at(i)->isBaoJi == true) {
                this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"暴击");
            }else if(affectRecordArray.at(i)->isGeDang == true) {
                this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"格挡");
            }else {
                this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"");
            }
            
         //   this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange);
        }
    }
   // this->decreaseNuQi(this, 3, true);
}



void HouYiCard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        zhanli = CommonFunc::creatAnimation("xiaohei_stand_r%d.png", 5, animationFactor*5, 1);
    }else {
        zhanli = CommonFunc::creatAnimation("xiaohei_stand_l%d.png", 5, animationFactor*5, 1);
    }
   // auto zhanli = CommonFunc::creatAnimation("xiaohei_stand_%d.png", 5, 0.5f, 1);
    //zhanli->setTag(10);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}

