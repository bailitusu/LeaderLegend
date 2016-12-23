//
//  BaiZeCard.cpp
//  OctMountain
//
//  Created by zc on 16/12/2.
//
//

#include "BaiZeCard.h"
#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "CommonFunc.h"
#include "ActionWait.h"
#include "OneRecord.h"
#include "RecordFight.h"
#include "ReadRecordFight.h"
#include "FightProgress.h"
bool BaiZeCard::init() {
    this->cellIndex = 0;
    this->HP = 16000;
    this->hitRuleNum = hitRuleType.faShi;
    this->cardName = "baize";
    this->cardZhongWenName = "白泽";
    this->cardSpriteImageName = "baize_idle";
    this->xiaoZhaoInfo = "友军回血";
    this->daZhaoInfo = "治疗移除有害状态";
    this->wuLi = 60;
    this->tongShuai = 72;
    this->zhiLi = 78;
    this->mingJie = 90;
    this->yunQi = 95;
    
    this->gongJi = 17000;
    this->faLi = 20000;
    this->fangYu = 17000;

    this->bingKinds = bingZhongType.guWu;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
    return true;
}



void BaiZeCard::xiaoSkll(OneRecord *info) {
    this->stopStandAnimation();
    Animate* gong = CommonFunc::creatAnimation("baize_attackm_%d.png", 8, animationFactor*8, 1);;

    
    auto wait = ActionWait::create(1.0);
    
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(BaiZeCard::nuQiManage, this,info));
    auto hit = CallFunc::create(CC_CALLBACK_0(BaiZeCard::hitBlock,this,info->affectRecordArray));
    auto appear = CallFunc::create(CC_CALLBACK_0(BaiZeCard::appearUI, this));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->cardSprite->runAction(Sequence::create(gong,hit,wait,addNuqi,afterAction,appear,recordBlock,NULL));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bingnv_attack.mp3",false);
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    
}



void BaiZeCard::daSkill(OneRecord *info) {
    this->stopStandAnimation();
    Animate* dazhao = NULL;

    dazhao = CommonFunc::creatAnimation("baize_attackb_%d.png", 10, animationFactor*10, 1);
    //auto dazhao = CommonFunc::creatAnimation("bingnv_conjure_%d.png", 16, 1.0f, 1);
    auto wait = ActionWait::create(1.4);
    auto nuqi = CallFunc::create(CC_CALLBACK_0(BaiZeCard::nuQiManage, this,info));
    auto appear = CallFunc::create(CC_CALLBACK_0(BaiZeCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(BaiZeCard::daHitBlock, this, info->affectRecordArray));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    
    this->cardSprite->runAction(Sequence::create(dazhao,maxHit,wait,nuqi,afterAction,appear,recordBlock,NULL));
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bingnv_conjure.mp3",false);
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void BaiZeCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("bingnv_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("bingnv_conjure.mp3");
}

void BaiZeCard::nuQiManage(OneRecord *info) {
    this->nuQiAppear(this, info->nuQiChange,info->nuQiMax);
}

void BaiZeCard::hitBlock(Vector<OneRecord *> affectRecordArray) {
    
    for(int i = 0; i < affectRecordArray.size(); i++) {
        auto affectCard = affectRecordArray.at(i)->card;
        if (affectRecordArray.at(i)->isBaoJi == true) {
            this->hpAppear(affectCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"暴击");
        }else {
            this->hpAppear(affectCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"");
        }
        //this->nuQiAppear(affectCard, affectRecordArray.at(i)->nuQiChange);
    }
    
}

void BaiZeCard::daHitBlock(Vector<OneRecord *> affectRecordArray) {
    for (int i = 0 ; i < affectRecordArray.size(); i++) {
        auto beHitCard = affectRecordArray.at(i)->card;
        
        if (affectRecordArray.at(i)->isBaoJi == true) {
            this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"暴击");
        }else {
            this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"");
        }
        
       // this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange);
        
    }
    //  this->decreaseNuQi(this, 3, true);
}


void BaiZeCard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        zhanli = CommonFunc::creatAnimation("bingnv_stand_r%d.png", 4, animationFactor*4, 1);
//    }else {
//        zhanli = CommonFunc::creatAnimation("bingnv_stand_l%d.png", 4, animationFactor*4, 1);
//    }
    
    zhanli = CommonFunc::creatAnimation("baize_idle_%d.png", 4, animationFactor*4, 1);
    //zhanli->setTag(10);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}
