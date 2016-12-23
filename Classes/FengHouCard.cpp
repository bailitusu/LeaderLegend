//
//  FengHouCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#include "FengHouCard.h"
#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "ActionWait.h"
#include "Card.h"
#include "GeDangBuff.h"
#include "ZhenFenBuff.h"
#include "BaoJiBuff.h"

#include "CommonFunc.h"
#include "OneRecord.h"
#include "RecordFight.h"
#include "ReadRecordFight.h"
#include "FightProgress.h"
bool FengHouCard::init() {
    this->cellIndex = 0;
    this->HP = 19000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.jinZhan;
    this->cardName = "fenghou";
    this->cardZhongWenName = "风后";
    this->cardSpriteImageName = "fenghou_idle";
    this->xiaoZhaoInfo = "普通攻击后鼓舞身边队友";
    this->daZhaoInfo = "鼓舞全军附加振奋状态";
    this->wuLi = 72;
    this->tongShuai = 92;
    this->zhiLi = 88;
    this->mingJie = 82;
    this->yunQi = 92;
    
    this->gongJi = 18000;
    this->faLi = 18000;
    this->fangYu = 20000;
//    this->wuliHart = 10;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 10;
//    this->baoJi = 10;
//    this->mianBao = 10;
//    this->lianJi = 1;
    this->bingKinds = bingZhongType.guWu;
//    this->hitValue = 2;
//    this->geDang = 0;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
    return true;
}


void FengHouCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("gugong_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("gugong_conjure.mp3");
}




void FengHouCard::nuQiManage(OneRecord *info) {

    this->nuQiAppear(this, info->nuQiChange,info->nuQiMax);

}



void FengHouCard::xiaoHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("gugong_attack.mp3",false);
}
void FengHouCard::xiaoSkll(OneRecord *info) {
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
//        gong = CommonFunc::creatAnimation("gugong_attack_r%d.png", 12, animationFactor*12, 1);
//    }else {
//        gong = CommonFunc::creatAnimation("gugong_attack_l%d.png", 12, animationFactor*12, 1);
//    }
    gong = CommonFunc::creatAnimation("fenghou_attackm_%d.png", 12, animationFactor*12, 1);
    auto move = CallFunc::create(CC_CALLBACK_0(FengHouCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*7);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(FengHouCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(FengHouCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(FengHouCard::hitBlock,this,info->affectRecordArray));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(FengHouCard::nuQiManage, this,info));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(FengHouCard::xiaoHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,wait,movaFanhui,moveWait,addNuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,gongMusic, NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);

}

void FengHouCard::moveAnimation(Vec2 target) {
    Animate* animateActionWalk = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        animateActionWalk = CommonFunc::creatAnimation("gugong_move_r%d.png", 7, animationFactor*7, 1);
//    }else {
//        animateActionWalk = CommonFunc::creatAnimation("gugong_move_l%d.png", 7, animationFactor*7, 1);
//    }
    animateActionWalk = CommonFunc::creatAnimation("fenghou_move_%d.png", 7, animationFactor*7, 1);
    auto moveTo = MoveTo::create(animationFactor*7, target);

    this->cardSprite->runAction(moveTo);
    this->cardSprite->runAction(animateActionWalk);
}

void FengHouCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("gugong_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("gugong_conjure.mp3");
}

void FengHouCard::hitBlock(Vector<OneRecord *> affectRecordArray) {
    auto beHitCardRecord = affectRecordArray.at(0);
    if (beHitCardRecord->isShanBi == true) {
        
        beHitCardRecord->card->animationShanBi();
    }else {
        if (beHitCardRecord->card->HP > 0) {
            this->createTeXiao(beHitCardRecord->card);
            beHitCardRecord->card->MaxHP = beHitCardRecord->maxHP;
            
            if (beHitCardRecord->isBaoJi == true) {
                this->hpAppear(beHitCardRecord->card, beHitCardRecord->hitValue, beHitCardRecord->currentHP,"暴击");
            }else if(beHitCardRecord->isGeDang == true) {
                this->hpAppear(beHitCardRecord->card, beHitCardRecord->hitValue, beHitCardRecord->currentHP,"格挡");
            }else {
                this->hpAppear(beHitCardRecord->card, beHitCardRecord->hitValue, beHitCardRecord->currentHP,"");
            }
          //  this->hpAppear(beHitCardRecord->card, beHitCardRecord->hitValue, beHitCardRecord->currentHP);
            
            this->nuQiAppear(beHitCardRecord->card, beHitCardRecord->nuQiChange,beHitCardRecord->nuQiMax);
            
        }
    }
}

void FengHouCard::createTeXiao(Card *cardTexiao) {
    ParticleSystem *cps = ParticleSun::create();
    cps->setPosition(cardTexiao->cardSprite->getPosition());
    cps->setLife(0.05f);
    cps->setTotalParticles(100);
    cps->setDuration(0.7);
    //  cps->setGravity(Point(0,-480));
    cps->setEmissionRate(200);
    cps->setPosVar(Point(20,20));
    cardTexiao->forPlayer->fMap->addChild(cps,3000);
}

void FengHouCard::daHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("gugong_conjure.mp3",false);
}

void FengHouCard::daSkill(OneRecord *info) {
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
//        dazhao = CommonFunc::creatAnimation("gugong_conjure_r%d.png", 12, animationFactor*12, 1);
//    }else {
//        dazhao = CommonFunc::creatAnimation("gugong_conjure_l%d.png", 12, animationFactor*12, 1);
//    }
    dazhao = CommonFunc::creatAnimation("fenghou_attackb_%d.png", 12, animationFactor*12, 1);
    
    auto move = CallFunc::create(CC_CALLBACK_0(FengHouCard::moveAnimation, this, target));
    auto wait = ActionWait::create(1.0);
    auto moveWait = ActionWait::create(animationFactor*7);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(FengHouCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(FengHouCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(FengHouCard::daHitBlock, this, info->affectRecordArray));
    // auto addNuqi = CallFunc::create(CC_CALLBACK_0(TaoTieCard::nuQiManage, this));
    auto nuqi = CallFunc::create(CC_CALLBACK_0(FengHouCard::nuQiManage, this,info));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(FengHouCard::daHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,dazhao,maxHit,wait,movaFanhui,moveWait,nuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,dazhaoMusic, NULL));
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void FengHouCard::daHitBlock(Vector<OneRecord*> affectRecordArray) {
    for (int i = 0 ; i < affectRecordArray.size(); i++) {
        auto beHitCard = affectRecordArray.at(i)->card;
        if (affectRecordArray.at(i)->isShanBi == true) {
            beHitCard->animationShanBi();
        }else {
            beHitCard->MaxHP = affectRecordArray.at(i)->maxHP;
            this->createTeXiao(beHitCard);
            if (affectRecordArray.at(i)->isBaoJi == true) {
                this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"暴击");
            }else if(affectRecordArray.at(i)->isGeDang == true) {
                this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"格挡");
            }else {
                this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"");
            }
            

        }
    }
    

}

void FengHouCard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        zhanli = CommonFunc::creatAnimation("gugong_stand_r%d.png", 5, animationFactor*5, 1);
//    }else {
//        zhanli = CommonFunc::creatAnimation("gugong_stand_l%d.png", 5, animationFactor*5, 1);
//    }
    
    zhanli = CommonFunc::creatAnimation("fenghou_idle_%d.png", 5, animationFactor*5, 1);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}
