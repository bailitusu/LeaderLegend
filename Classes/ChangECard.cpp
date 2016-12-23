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
#include "FightProgress.h"
bool ChangECard::init() {
    this->cellIndex = 0;
    this->HP = 16000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.faShi;
    this->cardName = "change";
    this->cardZhongWenName = "嫦娥";
    this->cardSpriteImageName = "change_idle";
    this->xiaoZhaoInfo = "鼓舞友军";
    this->daZhaoInfo = "鼓舞友军并恢复少量气血";
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




void ChangECard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bingnv_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bingnv_conjure.mp3");
}

//void ChangECard::recordRuning(FightPlayer *enemyTemp) {
//    this->forEnemy = enemyTemp;
//    
//    auto oneRecord = OneRecord::create();
//    oneRecord->cardName = this->cardName;
//    oneRecord->playerName = this->playerName;
//    oneRecord->standIndex = this->cellIndex;
//    
//    if (this->nuQiNum < this->nuQiNumMax) {
//        oneRecord->isXiaoZhao = true;
//        oneRecord->isDaZhao = false;
//        oneRecord->nuQiChange = 1;
//        RecordFight::GetInstance()->addItemToRecord(oneRecord);
// 
//        this->recordHit();
//        
//        this->recordAddNuqi(this, 1);
//        this->recordActionBlock();
//        
//    }else {
//        oneRecord->isXiaoZhao = false;
//        oneRecord->isDaZhao = true;
//        RecordFight::GetInstance()->addItemToRecord(oneRecord);
//        this->recordUltimateSkill();
//        this->recordActionBlock();
//        // this->cardSprite->runAction(Sequence::create(maxHit,block, NULL));
//    }
//
//}

void ChangECard::xiaoSkll(OneRecord *info) {
    this->stopStandAnimation();
    Animate* gong = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        gong = CommonFunc::creatAnimation("bingnv_attack_r%d.png", 12, animationFactor*12, 1);
//    }else {
//        gong = CommonFunc::creatAnimation("bingnv_attack_l%d.png", 12, animationFactor*12, 1);
//    }
    gong = CommonFunc::creatAnimation("change_attackm_%d.png", 12, animationFactor*12, 1);
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



void ChangECard::daSkill(OneRecord *info) {
    this->stopStandAnimation();
    Animate* dazhao = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        dazhao = CommonFunc::creatAnimation("bingnv_conjure_r%d.png", 16, animationFactor*16, 1);
//    }else {
//        dazhao = CommonFunc::creatAnimation("bingnv_conjure_l%d.png", 16, animationFactor*16, 1);
//    }
    //auto dazhao = CommonFunc::creatAnimation("bingnv_conjure_%d.png", 16, 1.0f, 1);
    dazhao = CommonFunc::creatAnimation("change_attackb_%d.png", 16, animationFactor*16, 1);
    auto wait = ActionWait::create(1.4);
    auto nuqi = CallFunc::create(CC_CALLBACK_0(ChangECard::nuQiManage, this,info));
    auto appear = CallFunc::create(CC_CALLBACK_0(ChangECard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(ChangECard::daHitBlock, this, info->affectRecordArray));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    
    this->cardSprite->runAction(Sequence::create(dazhao,maxHit,wait,nuqi,afterAction,appear,recordBlock,NULL));
    this->createTeXiao();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bingnv_conjure.mp3",false);
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void ChangECard::createTeXiao() {
    ParticleSystem *cps = ParticleSnow::create();
    cps->setPosition(this->forPlayer->fMap->getPosition().x+this->forPlayer->fMap->getBoundingBox().size.width/2,this->forPlayer->fMap->getPosition().y+this->forPlayer->fMap->getBoundingBox().size.height/2);
    cps->setLife(0.001f);
    cps->setTotalParticles(100);
    cps->setDuration(0.7);
  //  cps->setGravity(Point(0,-480));
    cps->setEmissionRate(100);
    cps->setPosVar(Point(this->forPlayer->fMap->getBoundingBox().size.width/2,this->forPlayer->fMap->getBoundingBox().size.height/2));
    this->forPlayer->fMap->getParent()->getParent()->addChild(cps,3000);
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
   this->nuQiAppear(this, info->nuQiChange,info->nuQiMax);
}

void ChangECard::hitBlock(Vector<OneRecord *> affectRecordArray) {
    
    for(int i = 0; i < affectRecordArray.size(); i++) {
        auto affectCard = affectRecordArray.at(i)->card;
    //    this->hpAppear(affectCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
        this->nuQiAppear(affectCard, affectRecordArray.at(i)->nuQiChange,affectRecordArray.at(i)->nuQiMax);
    }

}

void ChangECard::daHitBlock(Vector<OneRecord *> affectRecordArray) {
    for (int i = 0 ; i < affectRecordArray.size(); i++) {
        auto beHitCard = affectRecordArray.at(i)->card;
        
        if (affectRecordArray.at(i)->isBaoJi == true) {
            this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"暴击");
        }else {
            this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"");
        }

        this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange,affectRecordArray.at(i)->nuQiMax);
        
    }
  //  this->decreaseNuQi(this, 3, true);
}


void ChangECard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        zhanli = CommonFunc::creatAnimation("bingnv_stand_r%d.png", 4, animationFactor*4, 1);
//    }else {
//        zhanli = CommonFunc::creatAnimation("bingnv_stand_l%d.png", 4, animationFactor*4, 1);
//    }
    zhanli = CommonFunc::creatAnimation("change_idle_%d.png", 4, animationFactor*4, 1);
    //zhanli->setTag(10);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}
