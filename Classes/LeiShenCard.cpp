//
//  LeiShenCard.cpp
//  OctMountain
//
//  Created by zc on 16/12/2.
//
//

#include "LeiShenCard.h"

#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "ActionWait.h"
#include "Card.h"
#include "ShanBiBuff.h"
#include "MianBaoBuff.h"

#include "CommonFunc.h"
#include "OneRecord.h"
#include "RecordFight.h"
#include "FightProgress.h"
#include "ReadRecordFight.h"
bool LeiShenCard::init() {
    this->cellIndex = 0;
    this->HP = 17000;
    //    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.faShi;
    this->cardName = "leishen";
    this->cardZhongWenName = "雷神";
    this->cardSpriteImageName = "leishen_idle";
    this->xiaoZhaoInfo = "横排中量法术伤害";
    this->daZhaoInfo = "对敌方全体造成法术伤害";
    this->wuLi = 71;
    this->tongShuai = 84;
    this->zhiLi = 92;
    this->mingJie = 98;
    this->yunQi = 72;
    
    this->gongJi = 17000;
    this->faLi = 21000;
    this->fangYu = 17000;

    this->bingKinds = bingZhongType.faShi;
    //    this->hitValue = 2;
    this->hitLevel = 0.6;
    this->cardLevel = 60;
    
    return true;
}

void LeiShenCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("zhousi_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("zhousi_conjure.mp3");
}





void LeiShenCard::nuQiManage(OneRecord *info) {
    this->nuQiAppear(this, info->nuQiChange,info->nuQiMax);
}


void LeiShenCard::xiaoHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("zhousi_attack.mp3",false);
}

void LeiShenCard::xiaoSkll(OneRecord *info) {
    this->stopStandAnimation();
    auto defaultPosition = this->cardSprite->getPosition();
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-40;
    }else {
        tagetX = tagetX+40;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;

    Animate* gong = CommonFunc::creatAnimation("leishen_attackm_%d.png", 7, animationFactor*7, 1);
    auto move = CallFunc::create(CC_CALLBACK_0(LeiShenCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*6);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(LeiShenCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(LeiShenCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(LeiShenCard::hitBlock,this,info->affectRecordArray));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(LeiShenCard::nuQiManage, this,info));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(LeiShenCard::xiaoHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,wait,movaFanhui,moveWait,addNuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,gongMusic,NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    
}

void LeiShenCard::moveAnimation(Vec2 target) {

    Animate* animateActionWalk = CommonFunc::creatAnimation("leishen_move_%d.png", 6, animationFactor*6, 1);
    auto moveTo = MoveTo::create(animationFactor*6, target);
    this->cardSprite->runAction(moveTo);
    this->cardSprite->runAction(animateActionWalk);
}

void LeiShenCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("zhousi_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("zhousi_conjure.mp3");
}

void LeiShenCard::hitBlock(Vector<OneRecord *> affectRecordArray) {
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
            
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange,affectRecordArray.at(i)->nuQiMax);
        }
    }
}

void LeiShenCard::daHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("zhousi_conjure.mp3",false);
}

void LeiShenCard::daSkill(OneRecord *info) {
    this->stopStandAnimation();
    auto defaultPosition = this->cardSprite->getPosition();
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-40;
    }else {
        tagetX = tagetX+40;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;

    Animate* dazhao = CommonFunc::creatAnimation("leishen_attackb_%d.png", 9, animationFactor*9, 1);
    
    auto move = CallFunc::create(CC_CALLBACK_0(LeiShenCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*6);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(LeiShenCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(LeiShenCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(LeiShenCard::daHitBlock, this, info->affectRecordArray));
    
    auto nuqi = CallFunc::create(CC_CALLBACK_0(LeiShenCard::nuQiManage, this,info));
    
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(LeiShenCard::daHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,dazhao,maxHit,wait,movaFanhui,moveWait,nuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,dazhaoMusic, NULL));
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void LeiShenCard::daHitBlock(Vector<OneRecord*> affectRecordArray) {
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
            
            
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange,affectRecordArray.at(i)->nuQiMax);
        }
    }
    
    //  this->decreaseNuQi(this, 3, true);
}

void LeiShenCard::runZhanLiAnimation() {

    Animate* zhanli = CommonFunc::creatAnimation("leishen_idle_%d.png", 4, animationFactor*4*1.5, 1);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);;
}
