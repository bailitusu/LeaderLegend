//
//  TaoWuCard.cpp
//  OctMountain
//
//  Created by zc on 16/12/2.
//
//

#include "TaoWuCard.h"
#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "OneRecord.h"
#include "RecordFight.h"
#include "ReadRecordFight.h"
#include "ActionWait.h"
#include "CommonFunc.h"
#include "FightProgress.h"
bool TaoWuCard::init() {
    this->cellIndex = 0;
    this->HP = 20000;
    //    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.jinZhan;
    this->cardName = "taowu";
    this->cardZhongWenName = "涛忤";
    this->cardSpriteImageName = "taowu_idle";
    this->xiaoZhaoInfo = "挫志攻击";
    this->daZhaoInfo = "大范围固定伤害";
    this->wuLi = 87;
    this->tongShuai = 81;
    this->zhiLi = 62;
    this->mingJie = 58;
    this->yunQi = 90;
    
    this->gongJi = 17000;
    this->faLi = 17000;
    this->fangYu = 20000;

    this->bingKinds = bingZhongType.jinZhan;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
    return true;
}

void TaoWuCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("panda_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pande_conjure.mp3");
}

void TaoWuCard::xiaoHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("panda_attack.mp3",false);
}

void TaoWuCard::xiaoSkll(OneRecord *info) {
    this->stopStandAnimation();
    auto defaultPosition = this->cardSprite->getPosition();
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-40;
    }else {
        tagetX = tagetX+40;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;

    Animate* gong = CommonFunc::creatAnimation("taowu_attackm_%d.png", 9, animationFactor*9, 1);
    
    auto move = CallFunc::create(CC_CALLBACK_0(TaoWuCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*6);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(TaoWuCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(TaoWuCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(TaoWuCard::hitBlock,this,info->affectRecordArray));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(TaoWuCard::nuQiManage, this,info));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(TaoWuCard::xiaoHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,wait,movaFanhui,moveWait,addNuqi,afterAction,appear,recordBlock,NULL));
    
    this->cardSprite->runAction(Sequence::create(moveWait,gongMusic,NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    
}

void TaoWuCard::daHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("panda_conjure.mp3",false);
}

void TaoWuCard::daSkill(OneRecord *info) {
    this->stopStandAnimation();
    
    auto defaultPosition = this->cardSprite->getPosition();
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-40;
    }else {
        tagetX = tagetX+40;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;

    Animate* dazhao = CommonFunc::creatAnimation("taowu_attackb_%d.png", 13, animationFactor*13, 1);
    auto move = CallFunc::create(CC_CALLBACK_0(TaoWuCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*6);
    auto dazhaoWait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(TaoWuCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(TaoWuCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(TaoWuCard::daHitBlock, this, info->affectRecordArray));

    auto myNuqi = CallFunc::create(CC_CALLBACK_0(TaoWuCard::nuQiManage, this,info));
    
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(TaoWuCard::daHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,dazhao,maxHit,dazhaoWait,movaFanhui,moveWait,myNuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,dazhaoMusic,NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void TaoWuCard::daHitBlock(Vector<OneRecord *> affectRecordArray) {
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
            
            //     this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange,affectRecordArray.at(i)->nuQiMax);
        }
    }
    // this->decreaseNuQi(this, 3,true);
    
}

void TaoWuCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("panda_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("pande_conjure.mp3");
}
void TaoWuCard::moveAnimation(Vec2 target) {

    Animate* animateActionWalk = CommonFunc::creatAnimation("taowu_move_%d.png", 6, animationFactor*6, 1);
    auto moveTo = MoveTo::create(animationFactor*6, target);
    this->cardSprite->runAction(moveTo);
    this->cardSprite->runAction(animateActionWalk);
}

void TaoWuCard::nuQiManage(OneRecord *info) {
    this->nuQiAppear(this, info->nuQiChange,info->nuQiMax);
}



void TaoWuCard::hitBlock(Vector<OneRecord *> affectRecordArray) {
    
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
            //    this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange,affectRecordArray.at(i)->nuQiMax);
        }
    }
    
    
    
}




void TaoWuCard::runZhanLiAnimation() {

    Animate* zhanli = CommonFunc::creatAnimation("taowu_idle_%d.png", 4, animationFactor*4, 1);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}
