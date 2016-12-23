//
//  DangKangCard.cpp
//  OctMountain
//
//  Created by zc on 16/12/2.
//
//

#include "DangKangCard.h"
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
#include "FightProgress.h"
bool DangKangCard::init() {
    this->cellIndex = 0;
    this->HP = 22000;
    //    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.jinZhan;
    this->cardName = "dangkang";
    this->cardZhongWenName = "当康";
    this->cardSpriteImageName = "dangkang_idle";
    this->xiaoZhaoInfo = "每回合攻击前恢复一定气血";
    this->daZhaoInfo = "横排大量法术伤害";
    this->wuLi = 72;
    this->tongShuai = 97;
    this->zhiLi = 85;
    this->mingJie = 25;
    this->yunQi = 100;
    
    this->gongJi = 15000;
    this->faLi = 19000;
    this->fangYu = 22000;

    this->bingKinds = bingZhongType.fangYu;
    //    this->hitValue = 2;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
    return true;
}

void DangKangCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("niutou_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("niutou_conjure.mp3");
}


void DangKangCard::nuQiManage(OneRecord *info) {
    this->nuQiAppear(this, info->nuQiChange,info->nuQiMax);
}

void DangKangCard::daHitBlock(Vector<OneRecord*> affectRecordArray) {
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

void DangKangCard::xiaoHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("niutou_attack.mp3",false);
}

void DangKangCard::xiaoSkll(OneRecord *info) {
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

    gong = CommonFunc::creatAnimation("dangkang_attackm_%d.png", 8, animationFactor*8, 1);
    auto move = CallFunc::create(CC_CALLBACK_0(DangKangCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*8);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(DangKangCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(DangKangCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(DangKangCard::hitBlock,this,info->affectRecordArray));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(DangKangCard::nuQiManage, this,info));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(DangKangCard::xiaoHitMusic, this));
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,wait,movaFanhui,moveWait,addNuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,gongMusic, NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void DangKangCard::hitBlock(Vector<OneRecord *> affectRecordArray) {
    
    for (int i = 0 ; i < affectRecordArray.size(); i++) {
        auto beHitCard = affectRecordArray.at(i)->card;
        if (affectRecordArray.at(i)->isShanBi == true) {
            beHitCard->animationShanBi();
        }else {
            beHitCard->HP = affectRecordArray.at(i)->currentHP;
            beHitCard->MaxHP = affectRecordArray.at(i)->maxHP;
            
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

void DangKangCard::daHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("niutou_conjure.mp3",false);
}

void DangKangCard::daSkill(OneRecord *info) {
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
    
    dazhao = CommonFunc::creatAnimation("dangkang_attackb_%d.png", 11, animationFactor*11, 1);
    auto move = CallFunc::create(CC_CALLBACK_0(DangKangCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*8);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(DangKangCard::moveAnimation, this, defaultPosition));
    auto nuqi = CallFunc::create(CC_CALLBACK_0(DangKangCard::nuQiManage, this,info));
    auto appear = CallFunc::create(CC_CALLBACK_0(DangKangCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(DangKangCard::daHitBlock, this, info->affectRecordArray));

    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(DangKangCard::daHitMusic, this));
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    
    this->cardSprite->runAction(Sequence::create(move,moveWait,dazhao,maxHit,wait,movaFanhui,moveWait,nuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,dazhaoMusic, NULL));
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void DangKangCard::runZhanLiAnimation() {
    Animate* zhanli = NULL;

    zhanli = CommonFunc::creatAnimation("dangkang_idle_%d.png", 8, animationFactor*8, 1);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}

void DangKangCard::moveAnimation(Vec2 target) {
    Animate* animateActionWalk = NULL;

    animateActionWalk = CommonFunc::creatAnimation("dangkang_move_%d.png", 8, animationFactor*8, 1);
    auto moveTo = MoveTo::create(animationFactor*8, target);
    //   auto animateActionWalk = CommonFunc::creatAnimation("niutou_move_%d.png", 8, 0.5f, 2);
    this->cardSprite->runAction(moveTo);
    this->cardSprite->runAction(animateActionWalk);
}

void DangKangCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("niutou_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("niutou_conjure.mp3");
}
