//
//  ChangECard.cpp
//  OctLegend
//
//  Created by zc on 16/8/20.
//
//

#include "ChangECard.h"
#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "CommonFunc.h"
#include "ActionWait.h"
#include "OneRecord.h"
#include "RecordFight.h"
#include "ReadRecordFight.h"
bool ChangECard::init() {
    this->cellIndex = 0;
    this->HP = 16000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.faShi;
    this->cardName = "change";
    this->cardSpriteImageName = "bingnv_stand";
    this->xiaoZhaoInfo = "加怒";
    this->daZhaoInfo = "苦尽甘来";
    this->wuLi = 60;
    this->tongShuai = 72;
    this->zhiLi = 78;
    this->mingJie = 90;
    this->yunQi = 95;
    
    this->gongJi = 17000;
    this->faLi = 20000;
    this->fangYu = 17000;
  //  this->zhiLiao = 2;
//    this->wuliHart = 10;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 10;
//    this->baoJi = 10;
//    this->mianBao = 10;

//    this->hitValue = 0;
    this->bingKinds = bingZhongType.guWu;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
    return true;
}



//void ChangECard::running(FightPlayer *enemyTemp) {
//    this->forEnemy = enemyTemp;
//    
//
//    auto defalutScale = this->cardSprite->getScale();
//    auto big = ScaleTo::create(1.0, 1.0);
//    auto small = ScaleTo::create(1.0, defalutScale);
//    auto tooSmall = ScaleTo::create(1.0, 0.3);
//    auto hit = CallFunc::create(CC_CALLBACK_0(ChangECard::hitAction,this));
//    auto wait = ActionWait::create(1.0);
//    auto maxHit = CallFunc::create(CC_CALLBACK_0(ChangECard::ultimateSkill, this));
//    auto addNuqi = CallFunc::create(CC_CALLBACK_0(ChangECard::nuQiManage, this));
//    auto block = CallFunc::create(CC_CALLBACK_0(ChangECard::actionBlock,this));
//    if (this->fPro->nuqiPro->getPercentage() < 100) {
//        
//        this->cardSprite->runAction(Sequence::create(big,small,hit,addNuqi, block,NULL));
//        
//        //this->cardSprite->runAction(Sequence::create(hit,addNuqi,block,NULL));
//        
//    }else {
//        this->cardSprite->runAction(Sequence::create(tooSmall,small,maxHit, wait,block,NULL));
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

void ChangECard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bingnv_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bingnv_conjure.mp3");
}

void ChangECard::recordRuning(FightPlayer *enemyTemp) {
    this->forEnemy = enemyTemp;
    
    auto oneRecord = OneRecord::create();
    oneRecord->cardName = this->cardName;
    oneRecord->playerName = this->playerName;
    oneRecord->standIndex = this->cellIndex;
    
    if (this->nuQiNum < this->nuQiNumMax) {
        oneRecord->isXiaoZhao = true;
        oneRecord->isDaZhao = false;
        oneRecord->nuQiChange = 1;
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

void ChangECard::xiaoSkll(OneRecord *info) {
    this->stopStandAnimation();
    Animate* gong = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        gong = CommonFunc::creatAnimation("bingnv_attack_r%d.png", 12, animationFactor*12, 1);
    }else {
        gong = CommonFunc::creatAnimation("bingnv_attack_l%d.png", 12, animationFactor*12, 1);
    }
   // auto gong = CommonFunc::creatAnimation("bingnv_attack_%d.png", 11, 0.5f, 2);
    auto wait = ActionWait::create(1.0);
    
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(ChangECard::nuQiManage, this,info));
    auto hit = CallFunc::create(CC_CALLBACK_0(ChangECard::hitBlock,this,info->affectRecordArray));
    auto appear = CallFunc::create(CC_CALLBACK_0(ChangECard::appearUI, this));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));

    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->cardSprite->runAction(Sequence::create(gong,hit,wait,addNuqi,afterAction,appear,recordBlock,NULL));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bingnv_attack.mp3",false);
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    
}

//void ChangECard::xiaoHitMusic() {
//    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bingnv_attack.mp3",false);
//}

void ChangECard::daSkill(OneRecord *info) {
    this->stopStandAnimation();
    Animate* dazhao = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        dazhao = CommonFunc::creatAnimation("bingnv_conjure_r%d.png", 16, animationFactor*16, 1);
    }else {
        dazhao = CommonFunc::creatAnimation("bingnv_conjure_l%d.png", 16, animationFactor*16, 1);
    }
    //auto dazhao = CommonFunc::creatAnimation("bingnv_conjure_%d.png", 16, 1.0f, 1);
    auto wait = ActionWait::create(1.4);
    auto nuqi = CallFunc::create(CC_CALLBACK_0(ChangECard::nuQiManage, this,info));
    auto appear = CallFunc::create(CC_CALLBACK_0(ChangECard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(ChangECard::daHitBlock, this, info->affectRecordArray));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    
    this->cardSprite->runAction(Sequence::create(dazhao,maxHit,wait,nuqi,afterAction,appear,recordBlock,NULL));
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bingnv_conjure.mp3",false);
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void ChangECard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("bingnv_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("bingnv_conjure.mp3");
}

void ChangECard::nuQiManage(OneRecord *info) {
   this->nuQiAppear(this, info->nuQiChange);
}

void ChangECard::hitBlock(Vector<OneRecord *> affectRecordArray) {
    
    for(int i = 0; i < affectRecordArray.size(); i++) {
        auto affectCard = affectRecordArray.at(i)->card;
    //    this->hpAppear(affectCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
        this->nuQiAppear(affectCard, affectRecordArray.at(i)->nuQiChange);
    }
//    for (int i = 0; i < this->forPlayer->cardArray.size(); i++) {
//        if (this->forPlayer->cardArray.at(i)->cellIndex != this->cellIndex && this->forPlayer->cardArray.at(i)->nuQiNum < this->forPlayer->cardArray.at(i)->nuQiNumMax) {
//            
//            this->addNuQi(this->forPlayer->cardArray.at(i), 1);
//        }
//    }
}

void ChangECard::daHitBlock(Vector<OneRecord *> affectRecordArray) {
    for (int i = 0 ; i < affectRecordArray.size(); i++) {
        auto beHitCard = affectRecordArray.at(i)->card;

        this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
        this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange);
        
    }
  //  this->decreaseNuQi(this, 3, true);
}

void ChangECard::recordHit() {
    for (int i = 0; i < this->forPlayer->cardArray.size(); i++) {
        if (this->forPlayer->cardArray.at(i)->cellIndex != this->cellIndex && this->forPlayer->cardArray.at(i)->nuQiNum < this->forPlayer->cardArray.at(i)->nuQiNumMax) {

            this->recordAddNuqi(this->forPlayer->cardArray.at(i), 1);
        }
    }

}

void ChangECard::recordUltimateSkill() {
    for (int i = 0; i < this->forPlayer->fMap->mapCellArray.size(); i++) {
        auto temp = (Card*)(this->forPlayer->fMap->mapCellArray.at(i))->obj;
        if (temp != NULL) {
            if (temp->cellIndex != this->cellIndex) {
                this->recordAddNuqi(temp, 1);
            }
            OneRecord* oneRecord = OneRecord::create();
            oneRecord->zhiLiao = CommonFunc::reckonZhiLiaoValue(this, temp);
            oneRecord->playerName = temp->playerName;
            oneRecord->cardName = temp->cardName;
            oneRecord->standIndex = temp->cellIndex;
            RecordFight::GetInstance()->addAffectCardArray(RecordFight::GetInstance()->currentRecordIndex, oneRecord);
            this->recordAddHP(temp, CommonFunc::reckonZhiLiaoValue(this, temp));
        }
    }
    
    this->recordDecreaseNuqi(this, 3,true);
}

void ChangECard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        zhanli = CommonFunc::creatAnimation("bingnv_stand_r%d.png", 4, animationFactor*4, 1);
    }else {
        zhanli = CommonFunc::creatAnimation("bingnv_stand_l%d.png", 4, animationFactor*4, 1);
    }
   // auto zhanli = CommonFunc::creatAnimation("bingnv_stand_%d.png", 4, 0.5f, 1);
    //zhanli->setTag(10);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}
//void ChangECard::ultimateSkill() {
//   // printf("%s   fang da %d \n",this->playerName.c_str(),this->cellIndex);
//    for (int i = 0; i < this->forPlayer->fMap->mapCellArray.size(); i++) {
//        auto temp = (Card*)(this->forPlayer->fMap->mapCellArray.at(i))->obj;
//        if (temp != NULL) {
//            if (temp->cellIndex != this->cellIndex) {
//                this->addNuQi(temp, 1);
//            }
//            
////            if (temp->fPro->nuqiPro->getPercentage() < 100) {
////                temp->fPro->setNuQiProPrecent(34+temp->fPro->nuqiPro->getPercentage());
////            }
////            temp->HP = temp->HP+this->zhiLiao;
////            if (temp->HP > temp->MaxHP) {
////                temp->HP = temp->MaxHP;
////            }
////            temp->fPro->hpPro->setPercentage((1-(float)temp->HP/temp->MaxHP)*100);
//           // CommonFunc::reckonZhiLiaoValue(this, temp);
//            this->addHP(temp, CommonFunc::reckonZhiLiaoValue(this, temp));
//        }
//    }
//    
//    this->decreaseNuQi(this, 3,true);
////    this->fPro->setNuQiProPrecent(0);
//}
