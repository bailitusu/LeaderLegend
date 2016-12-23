//
//  SuanYuCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/25.
//
//

#include "SuanYuCard.h"

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
bool SuanYuCard::init() {
    this->cellIndex = 0;
    this->HP = 18000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.niao;
    this->cardName = "suanyu";
    this->cardZhongWenName = "酸与";
    this->cardSpriteImageName = "suanyu_idle";
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


void SuanYuCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("fengxing_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("fengxing_conjure.mp3");
}

void SuanYuCard::initCharacter() {
    this->mingZhong = 3.0;
}




void SuanYuCard::nuQiManage(OneRecord *info) {
    this->nuQiAppear(this, info->nuQiChange,info->nuQiMax);
}



void SuanYuCard::xiaoHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fengxing_attack.mp3",false);
}

void SuanYuCard::xiaoSkll(OneRecord *info) {
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
//        gong = CommonFunc::creatAnimation("fengxing_attack_r%d.png", 6, animationFactor*6, 1);
//    }else {
//        gong = CommonFunc::creatAnimation("fengxing_attack_l%d.png", 6, animationFactor*6, 1);
//    }
     gong = CommonFunc::creatAnimation("suanyu_attackm_%d.png", 6, animationFactor*6, 1);
  //  auto gong = CommonFunc::creatAnimation("fengxing_attack_%d.png", 6, 0.5f, 2);
    auto move = CallFunc::create(CC_CALLBACK_0(SuanYuCard::moveAnimation, this, target));
    auto wait = ActionWait::create(1.0);
    auto moveWait = ActionWait::create(animationFactor*3*2);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(SuanYuCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(SuanYuCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(SuanYuCard::hitBlock,this,info->affectRecordArray));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(SuanYuCard::nuQiManage, this,info));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(SuanYuCard::xiaoHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,wait,movaFanhui,moveWait,addNuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,gongMusic, NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    
}

void SuanYuCard::moveAnimation(Vec2 target) {
    Animate* animateActionWalk = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        animateActionWalk = CommonFunc::creatAnimation("fengxing_move_r%d.png", 3, animationFactor*3, 2);
//    }else {
//        animateActionWalk = CommonFunc::creatAnimation("fengxing_move_l%d.png", 3, animationFactor*3, 2);
//    }
    animateActionWalk = CommonFunc::creatAnimation("suanyu_move_%d.png", 3, animationFactor*3, 2);
    auto moveTo = MoveTo::create(animationFactor*3*2, target);
  //  auto animateActionWalk = CommonFunc::creatAnimation("fengxing_move_%d.png", 3, 0.25f, 4);
    this->cardSprite->runAction(moveTo);
    this->cardSprite->runAction(animateActionWalk);
}

void SuanYuCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("fengxing_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("fengxing_conjure.mp3");
}

void SuanYuCard::hitBlock(Vector<OneRecord *> affectRecordArray) {
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
        //    this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
            
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange,affectRecordArray.at(i)->nuQiMax);
        }
    }

}

void SuanYuCard::createTeXiao(Card *cardTexiao) {
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

void SuanYuCard::daHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fengxing_conjure.mp3",false);
}

void SuanYuCard::daSkill(OneRecord *info) {
    this->stopStandAnimation();
    auto defaultPosition = this->cardSprite->getPosition();

    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.x;
    if (tagetX > 0) {
        tagetX = tagetX-15;
    }else {
        tagetX = tagetX+15;
    }
    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(info->hitTarget)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
    
    Animate* dazhao = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        dazhao = CommonFunc::creatAnimation("fengxing_conjure_r%d.png", 6, animationFactor*6*2, 1);
//    }else {
//        dazhao = CommonFunc::creatAnimation("fengxing_conjure_l%d.png", 6, animationFactor*6*2, 1);
//    }
    dazhao = CommonFunc::creatAnimation("suanyu_attackb_%d.png", 6, animationFactor*6*2, 1);

    
    auto move = CallFunc::create(CC_CALLBACK_0(SuanYuCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*3*2);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(SuanYuCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(SuanYuCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(SuanYuCard::daHitBlock, this, info->affectRecordArray));
    auto nuqi = CallFunc::create(CC_CALLBACK_0(SuanYuCard::nuQiManage, this,info));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(SuanYuCard::daHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,dazhao,maxHit,wait,movaFanhui,moveWait,nuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,dazhaoMusic,NULL));
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void SuanYuCard::daHitBlock(Vector<OneRecord*> affectRecordArray) {
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
            
      //      this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
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

void SuanYuCard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        zhanli = CommonFunc::creatAnimation("fengxing_stand_r%d.png", 3, animationFactor*3, 1);
//    }else {
//        zhanli = CommonFunc::creatAnimation("fengxing_stand_l%d.png", 3, animationFactor*3, 1);
//    }
    zhanli = CommonFunc::creatAnimation("suanyu_idle_%d.png", 3, animationFactor*3, 1);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}
