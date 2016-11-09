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

bool HouYiCard::init() {
    this->cellIndex = 0;
    this->HP = 18000;
    
    this->hitRuleNum = hitRuleType.gongJian;
    this->cardName = "houyi";
    this->cardSpriteImageName = "xiaohei_stand";
    this->xiaoZhaoInfo = "连击";
    this->daZhaoInfo = "万箭齐发";
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

void HouYiCard::preAddCardAnimationResource() {
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        this->gong = CommonFunc::creatAnimation("xiaohei_attack_r%d.png", 12, animationFactor*12, 1);
//        this->dazhao = CommonFunc::creatAnimation("xiaohei_conjure_r%d.png", 16, animationFactor*16, 1);
//    }else {
//        this->gong = CommonFunc::creatAnimation("xiaohei_attack_l%d.png", 12, animationFactor*12, 1);
//        this->dazhao = CommonFunc::creatAnimation("xiaohei_conjure_l%d.png", 16, animationFactor*16, 1);
//    }
//    this->gong->retain();
//    this->dazhao->retain();
}
//void HouYiCard::running(FightPlayer *enemyTemp) {
//    this->forEnemy = enemyTemp;
//    
//  //  printf("%dhouyi%f\n",this->cellIndex,this->mingZhong);
//    auto defaultPosition = this->cardSprite->getPosition();
//    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    if (this->targetNum == 100) {
//        return;
//    }
//    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.x;
//    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
//    
//    this->cardSprite->stopActionByTag(10);
//    auto gong = CommonFunc::creatAnimation("xiaoheihit_%d.png", 22, 1.5f, 1);
//    auto dazhao = CommonFunc::creatAnimation("xiaoheidazhao_%d.png", 22, 2.0f, 1);
////    auto moveTo = MoveTo::create(1.0, target);
////    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
//    
//    //auto hit = CallFunc::create(CC_CALLBACK_0(HouYiCard::Hit,this));
//    auto wait = ActionWait::create(1.0);
//    auto maxHit = CallFunc::create(CC_CALLBACK_0(HouYiCard::ultimateSkill, this));
//    auto addNuqi = CallFunc::create(CC_CALLBACK_0(HouYiCard::nuQiManage, this));
//    auto block = CallFunc::create(CC_CALLBACK_0(HouYiCard::actionBlock,this));
//    if (this->fPro->nuqiPro->getPercentage() < 100) {
//        if (CommonFunc::isInPercent(0.5)) {
//   //         this->cardSprite->runAction(Sequence::create(gong,hit,wait,gong,hit,wait,addNuqi,block, NULL));
//      //      this->cardSprite->runAction(Sequence::create(moveTo,hit,wait,hit,movaFanhui,addNuqi,block,NULL));
//        } else {
//     //       this->cardSprite->runAction(Sequence::create(gong,hit,addNuqi,block, NULL));
//       //     this->cardSprite->runAction(Sequence::create(moveTo,hit,movaFanhui,addNuqi,block,NULL));
//        }
//    }else {
//        this->cardSprite->runAction(Sequence::create(dazhao,maxHit,block, NULL));
//       // this->cardSprite->runAction(Sequence::create(moveTo,maxHit,movaFanhui,block,NULL));
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

//void HouYiCard::beforeAnimation(OneRecord *info) {
//
//}

//void HouYiCard::afterAnimation(OneRecord *info) {
//    
//}

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

void HouYiCard::recordRuning(FightPlayer *enemyTemp) {
    this->forEnemy = enemyTemp;
    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    if (this->targetNum == 100) {
        return;
    }
    auto oneRecord = OneRecord::create();
    
    oneRecord->hitTarget = this->targetNum;
    oneRecord->cardName = this->cardName;
    oneRecord->playerName = this->playerName;
    oneRecord->standIndex = this->cellIndex;
  //  printf("%d-------%s\n", this->cellIndex, this->playerName.c_str());
//
//    auto hit = CallFunc::create(CC_CALLBACK_0(HouYiCard::recordHit,this));
//    auto maxHit = CallFunc::create(CC_CALLBACK_0(HouYiCard::ultimateSkill, this));
//    auto addNuqi = CallFunc::create(CC_CALLBACK_0(HouYiCard::nuQiManage, this));
//    auto block = CallFunc::create(CC_CALLBACK_0(HouYiCard::actionBlock,this));
    if (this->nuQiNum < this->nuQiNumMax) {
        oneRecord->isXiaoZhao = true;
        oneRecord->isDaZhao = false;
        if (CommonFunc::isInPercent(0.5)) {
            oneRecord->isLianJi = true;
        }else {
            oneRecord->isLianJi = false;
        }
        RecordFight::GetInstance()->addItemToRecord(oneRecord);
        if (oneRecord->isLianJi == true) {
            this->recordHit();
            this->recordHit();
            //this->nuQiManage();
            this->recordAddNuqi(this, 1);
            this->recordActionBlock();
           // this->cardSprite->runAction(Sequence::create(hit,hit,addNuqi,block, NULL));
        }else {
            this->recordHit();
           // this->nuQiManage();
            this->recordAddNuqi(this, 1);
            this->recordActionBlock();
        }
    }else {
        oneRecord->isXiaoZhao = false;
        oneRecord->isDaZhao = true;
        RecordFight::GetInstance()->addItemToRecord(oneRecord);
        this->recordUltimateSkill();
        this->recordActionBlock();
       // this->cardSprite->runAction(Sequence::create(maxHit,block, NULL));
    }
    
    
}
void HouYiCard::recordHit() {
    if ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj != NULL) {
        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->recordDidBeHit(this,"wuli");
        
//        auto oneRecord = OneRecord::create();
//        oneRecord->enemyNuQiChange = 1;
        //RecordFight::GetInstance()->addItemOfNuqiBuff(RecordFight::GetInstance()->currentRecordIndex, oneRecord);
        this->recordAddNuqi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);
    }
}


void HouYiCard::nuQiManage(OneRecord *info) {
//    if (this->fPro->nuqiPro->getPercentage() < 100) {
//        this->fPro->setNuQiProPrecent(34+this->fPro->nuqiPro->getPercentage());
//    }
    this->nuQiAppear(this, info->nuQiChange);
}

void HouYiCard::hitBlock( Vector<OneRecord*> affectRecordArray) {

//    if ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj != NULL) {
//        ((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum))->obj)->didBeHit(this,"wuli");
//
//        this->addNuQi((Card*)(this->forEnemy->fMap->mapCellArray.at(this->targetNum)->obj), 1);
//    }
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
            
            
            this->hpAppear(beHitCardRecord->card, beHitCardRecord->hitValue, beHitCardRecord->currentHP);
//            if (beHitCardRecord->card->HP < 0) {
//                this->cardSprite->stopActionByTag(1);
//                auto wait = ActionWait::create(1.0);
//                auto addNuqi = CallFunc::create(CC_CALLBACK_0(HouYiCard::nuQiManage, this));
//                auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
//                
//                this->cardSprite->runAction(Sequence::create(wait,addNuqi,recordBlock,NULL));
//            }
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
            this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange);
        }
    }
   // this->decreaseNuQi(this, 3, true);
}

void HouYiCard::recordUltimateSkill() {
    Vector<MapCell*> temp = this->forEnemy->fMap->hitNineCell(this->targetNum);
    for (int i = 0; i < temp.size(); i++) {
        this->recordAddNuqi((Card*)(temp.at(i))->obj, 1);
//        auto oneRecord = OneRecord::create();
//        oneRecord->enemyNuQiChange = 1;
       // RecordFight::GetInstance()->addItemOfNuqiBuff(RecordFight::GetInstance()->currentRecordIndex, oneRecord);
        ((Card*)(temp.at(i))->obj)->recordDidBeHit(this, "wuli");
    }
    this->recordDecreaseNuqi(this, 3, true);
   // this->decreaseNuQi(this, 3,true);
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
//void HouYiCard::ultimateSkill() {
////    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    Vector<MapCell*> temp = this->forEnemy->fMap->hitNineCell(this->targetNum);
//    for (int i = 0; i < temp.size(); i++) {
//        this->addNuQi((Card*)(temp.at(i))->obj, 1);
////        if (((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage() < 100) {
////            ((Card*)(temp.at(i))->obj)->fPro->setNuQiProPrecent(100/3+((Card*)(temp.at(i))->obj)->fPro->nuqiPro->getPercentage());
////        }
//        ((Card*)(temp.at(i))->obj)->didBeHit(this,"wuli");
//    }
//    this->decreaseNuQi(this, 3,true);
//    //this->fPro->setNuQiProPrecent(0);
//}
