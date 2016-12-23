//
//  QiongQiCard.cpp
//  OctMountain
//
//  Created by zc on 16/12/2.
//
//

#include "QiongQiCard.h"

#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "ActionWait.h"
#include "Card.h"
#include "CommonFunc.h"
#include "XuanYunBuff.h"

#include "CommonFunc.h"
#include "OneRecord.h"
#include "RecordFight.h"
#include "ReadRecordFight.h"
#include "FightProgress.h"
bool QiongQiCard::init() {
    this->cellIndex = 0;
    this->HP = 18000;
    //    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.niao;
    this->cardName = "qiongqi";
    this->cardZhongWenName = "穷奇";
    this->cardSpriteImageName = "qiongqi_idle";
    this->xiaoZhaoInfo = "攻击敌方后排部队";
    this->daZhaoInfo = "吸取敌方后排部队怒气并眩晕";
    this->wuLi = 81;
    this->tongShuai = 78;
    this->zhiLi = 56;
    this->mingJie = 98;
    this->yunQi = 75;
    
    this->gongJi = 19000;
    this->faLi = 17000;
    this->fangYu = 18000;
    
    
    this->bingKinds = bingZhongType.yuanCheng;
    //    this->hitValue = 2;
    //    this->geDang = 10;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
    return true;
}


void QiongQiCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("fengxing_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("fengxing_conjure.mp3");
}

void QiongQiCard::nuQiManage(OneRecord *info) {
    this->nuQiAppear(this, info->nuQiChange,info->nuQiMax);
}



void QiongQiCard::xiaoHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fengxing_attack.mp3",false);
}

void QiongQiCard::xiaoSkll(OneRecord *info) {
    this->stopStandAnimation();
    auto defaultPosition = this->cardSprite->getPosition();
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-40;
    }else {
        tagetX = tagetX+40;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;

    Animate* gong = CommonFunc::creatAnimation("qiongqi_attackm_%d.png", 18, animationFactor*18, 1);

    auto move = CallFunc::create(CC_CALLBACK_0(QiongQiCard::moveAnimation, this, target));
    auto wait = ActionWait::create(1.0);
    auto moveWait = ActionWait::create(animationFactor*12);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(QiongQiCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(QiongQiCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(QiongQiCard::hitBlock,this,info->affectRecordArray));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(QiongQiCard::nuQiManage, this,info));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(QiongQiCard::xiaoHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,wait,movaFanhui,moveWait,addNuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,gongMusic, NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    
}

void QiongQiCard::moveAnimation(Vec2 target) {

     Animate* animateActionWalk = CommonFunc::creatAnimation("qiongqi_move_%d.png", 12, animationFactor*12, 1);
    auto moveTo = MoveTo::create(animationFactor*12, target);
    this->cardSprite->runAction(moveTo);
    this->cardSprite->runAction(animateActionWalk);
}

void QiongQiCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("fengxing_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("fengxing_conjure.mp3");
}

void QiongQiCard::hitBlock(Vector<OneRecord *> affectRecordArray) {
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
            //    this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
            
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange,affectRecordArray.at(i)->nuQiMax);
        }
    }
    
}

void QiongQiCard::daHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fengxing_conjure.mp3",false);
}

void QiongQiCard::daSkill(OneRecord *info) {
    this->stopStandAnimation();
    auto defaultPosition = this->cardSprite->getPosition();
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-15;
    }else {
        tagetX = tagetX+15;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;

    Animate* dazhao = CommonFunc::creatAnimation("qiongqi_attackb_%d.png", 27, animationFactor*27, 1);
    
    
    auto move = CallFunc::create(CC_CALLBACK_0(QiongQiCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*12);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(QiongQiCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(QiongQiCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(QiongQiCard::daHitBlock, this, info->affectRecordArray));
    auto nuqi = CallFunc::create(CC_CALLBACK_0(QiongQiCard::nuQiManage, this,info));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(QiongQiCard::daHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,dazhao,maxHit,wait,movaFanhui,moveWait,nuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,dazhaoMusic,NULL));
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void QiongQiCard::daHitBlock(Vector<OneRecord*> affectRecordArray) {
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

            if (beHitCard != NULL) {
                if (affectRecordArray.at(i)->addbuffName.compare("xuanyun") == 0) {
                    auto xuanYunBuff = XuanYunBuff::create();
                    xuanYunBuff->addBuff(beHitCard,0);
                }
                
            }
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange,affectRecordArray.at(i)->nuQiMax);
        }
    }
    
    
    //  this->decreaseNuQi(this, 3, true);
}

void QiongQiCard::runZhanLiAnimation() {

    Animate* zhanli = CommonFunc::creatAnimation("qiongqi_idle_%d.png", 8, animationFactor*8, 1);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}
