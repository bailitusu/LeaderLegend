//
//  FengBoCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#include "FengBoCard.h"

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
bool FengBoCard::init() {
    this->cellIndex = 0;
    this->HP = 17000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.faShi;
    this->cardName = "fengbo";
    this->cardZhongWenName = "风伯";
    this->cardSpriteImageName = "fengbo_idle";
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
//    this->wuliHart = 10;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 10;
//    this->baoJi = 10;
//    this->mianBao = 10;
//    this->lianJi = 1;
    this->bingKinds = bingZhongType.faShi;
//    this->hitValue = 2;
    this->hitLevel = 0.6;
    this->cardLevel = 60;

    return true;
}

void FengBoCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("zhousi_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("zhousi_conjure.mp3");
}





void FengBoCard::nuQiManage(OneRecord *info) {
    this->nuQiAppear(this, info->nuQiChange,info->nuQiMax);
}


void FengBoCard::xiaoHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("zhousi_attack.mp3",false);
}

void FengBoCard::xiaoSkll(OneRecord *info) {
    this->stopStandAnimation();
    auto defaultPosition = this->cardSprite->getPosition();
    
    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-40;
    }else {
        tagetX = tagetX+40;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    Animate* gong = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        gong = CommonFunc::creatAnimation("zhousi_attack_r%d.png", 16, animationFactor*16, 1);
//    }else {
//        gong = CommonFunc::creatAnimation("zhousi_attack_l%d.png", 16, animationFactor*16, 1);
//    }
    gong = CommonFunc::creatAnimation("fengbo_attackm_%d.png", 16, animationFactor*16, 1);
    auto move = CallFunc::create(CC_CALLBACK_0(FengBoCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*8);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(FengBoCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(FengBoCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(FengBoCard::hitBlock,this,info->affectRecordArray));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(FengBoCard::nuQiManage, this,info));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(FengBoCard::xiaoHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,wait,movaFanhui,moveWait,addNuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,gongMusic,NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);

}

void FengBoCard::moveAnimation(Vec2 target) {
    
    Animate* animateActionWalk = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        animateActionWalk = CommonFunc::creatAnimation("zhousi_move_r%d.png", 8, animationFactor*8, 1);
//    }else {
//        animateActionWalk = CommonFunc::creatAnimation("zhousi_move_l%d.png", 8, animationFactor*8, 1);
//    }
    animateActionWalk = CommonFunc::creatAnimation("fengbo_move_%d.png", 8, animationFactor*8, 1);
    auto moveTo = MoveTo::create(animationFactor*8, target);
    this->cardSprite->runAction(moveTo);
    this->cardSprite->runAction(animateActionWalk);
}

void FengBoCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("zhousi_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("zhousi_conjure.mp3");
}

void FengBoCard::hitBlock(Vector<OneRecord *> affectRecordArray) {
    for (int i = 0 ; i < affectRecordArray.size(); i++) {
        auto beHitCard = affectRecordArray.at(i)->card;
        if (affectRecordArray.at(i)->isShanBi == true) {
            beHitCard->animationShanBi();
        }else {
            this->createTeXiao(beHitCard);
            if (affectRecordArray.at(i)->isBaoJi == true) {
                this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"暴击");
            }else if(affectRecordArray.at(i)->isGeDang == true) {
                this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"格挡");
            }else {
                this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"");
            }
            
          //  this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
            
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange,affectRecordArray.at(i)->nuQiMax);
        }
    }
}

void FengBoCard::createTeXiao(Card *cardTexiao) {
    ParticleSystem *cps = ParticleFire::create();
    cps->setPosition(cardTexiao->cardSprite->getPosition());
    cps->setLife(0.05f);
    cps->setTotalParticles(100);
    cps->setDuration(0.7);
    //  cps->setGravity(Point(0,-480));
    cps->setEmissionRate(200);
    cps->setPosVar(Point(20,20));
    cardTexiao->forPlayer->fMap->addChild(cps,3000);
}

void FengBoCard::daHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("zhousi_conjure.mp3",false);
}

void FengBoCard::daSkill(OneRecord *info) {
    this->stopStandAnimation();
    auto defaultPosition = this->cardSprite->getPosition();

    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-40;
    }else {
        tagetX = tagetX+40;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    Animate* dazhao = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        dazhao = CommonFunc::creatAnimation("zhousi_conjure_r%d.png", 16, animationFactor*16, 1);
//    }else {
//        dazhao = CommonFunc::creatAnimation("zhousi_conjure_l%d.png", 16, animationFactor*16, 1);
//    }
    dazhao = CommonFunc::creatAnimation("fengbo_attackb_%d.png", 16, animationFactor*16, 1);
    
    auto move = CallFunc::create(CC_CALLBACK_0(FengBoCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*8);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(FengBoCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(FengBoCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(FengBoCard::daHitBlock, this, info->affectRecordArray));
    
    auto nuqi = CallFunc::create(CC_CALLBACK_0(FengBoCard::nuQiManage, this,info));
    
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(FengBoCard::daHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,dazhao,maxHit,wait,movaFanhui,moveWait,nuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,dazhaoMusic, NULL));
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void FengBoCard::daHitBlock(Vector<OneRecord*> affectRecordArray) {
    for (int i = 0 ; i < affectRecordArray.size(); i++) {
        auto beHitCard = affectRecordArray.at(i)->card;
        if (affectRecordArray.at(i)->isShanBi == true) {
            beHitCard->animationShanBi();
        }else {
            this->createTeXiao(beHitCard);
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

void FengBoCard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        zhanli = CommonFunc::creatAnimation("zhousi_stand_r%d.png", 8, animationFactor*8*1.5, 1);
//    }else {
//        zhanli = CommonFunc::creatAnimation("zhousi_stand_l%d.png", 8, animationFactor*8*1.5, 1);
//    }
    zhanli = CommonFunc::creatAnimation("fengbo_idle_%d.png", 8, animationFactor*8*1.5, 1);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);;
}
