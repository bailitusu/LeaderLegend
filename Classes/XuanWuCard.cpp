//
//  XuanWuCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#include "XuanWuCard.h"
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
bool XuanWuCard::init() {
    this->cellIndex = 0;
    this->HP = 22000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.jinZhan;
    this->cardName = "xuanwu";
    this->cardZhongWenName = "玄武";
    this->cardSpriteImageName = "xuanwu_idle";
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
//    this->wuliHart = 10;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 10;
//    this->baoJi = 10;
//    this->mianBao = 10;
//    this->lianJi = 1;
    this->bingKinds = bingZhongType.fangYu;
//    this->hitValue = 2;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
    return true;
}

void XuanWuCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("niutou_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("niutou_conjure.mp3");
}

void XuanWuCard::initCharacter() {
    this->zhiLiao = this->MaxHP*0.15;
    this->geDang = 0.2;
}


//void XuanWuCard::recordRuning(FightPlayer *enemyTemp) {
//    this->forEnemy = enemyTemp;
//
//    this->forEnemy = enemyTemp;
//    auto oneRecord = OneRecord::create();
//    
//
//    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    oneRecord->hitTarget = this->targetNum;
//    oneRecord->cardName = this->cardName;
//    oneRecord->playerName = this->playerName;
//    oneRecord->standIndex = this->cellIndex;
//    oneRecord->currentHP = this->HP;
//    
//    if (this->nuQiNum < this->nuQiNumMax) {
//        oneRecord->isXiaoZhao = true;
//        oneRecord->isDaZhao = false;
//        RecordFight::GetInstance()->addItemToRecord(oneRecord);
//        this->zaiShengAction(true);
//        this->recordHit();
//        
//        this->recordAddNuqi(this, 1);
//        this->recordActionBlock();
//    }else {
//        oneRecord->isXiaoZhao = false;
//        oneRecord->isDaZhao = true;
//        RecordFight::GetInstance()->addItemToRecord(oneRecord);
//        this->zaiShengAction(true);
//        this->recordUltimateSkill();
//        this->recordActionBlock();
//        // this->cardSprite->runAction(Sequence::create(maxHit,block, NULL));
//    }
//    
//    
//
//}

void XuanWuCard::zaiShengAction(bool isRecord) {
    //printf("%d %s xuanwu %d \n",this->cellIndex, this->playerName.c_str(), this->HP);
    this->zaiShengBlood(isRecord);
    //printf("%d %s xuanwu %d %f \n",this->cellIndex, this->playerName.c_str(), this->HP, this->fPro->hpPro->getPercentage());
    
}



void XuanWuCard::nuQiManage(OneRecord *info) {
    this->nuQiAppear(this, info->nuQiChange,info->nuQiMax);
}




void XuanWuCard::daHitBlock(Vector<OneRecord*> affectRecordArray) {
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
//            if (beHitCard != NULL) {
//                auto mingZhongBuff = MingZhongBuff::create();
//                mingZhongBuff->decreaseBuff(beHitCard,0.1);
//            }
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange,affectRecordArray.at(i)->nuQiMax);
        }
    }
   // this->decreaseNuQi(this, 3, true);
}

void XuanWuCard::xiaoHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("niutou_attack.mp3",false);
}

void XuanWuCard::xiaoSkll(OneRecord *info) {
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
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        gong = CommonFunc::creatAnimation("niutou_attack_l%d.png", 20, animationFactor*20, 1);
//    }else {
//        gong = CommonFunc::creatAnimation("niutou_attack_l%d.png", 20, animationFactor*20, 1);
//    }
    gong = CommonFunc::creatAnimation("xuanwu_attackm_%d.png", 20, animationFactor*20, 1);
    auto move = CallFunc::create(CC_CALLBACK_0(XuanWuCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*8);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(XuanWuCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(XuanWuCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(XuanWuCard::hitBlock,this,info->affectRecordArray));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(XuanWuCard::nuQiManage, this,info));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(XuanWuCard::xiaoHitMusic, this));
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,wait,movaFanhui,moveWait,addNuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,gongMusic, NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void XuanWuCard::hitBlock(Vector<OneRecord *> affectRecordArray) {
    
    for (int i = 0 ; i < affectRecordArray.size(); i++) {
        auto beHitCard = affectRecordArray.at(i)->card;
        if (affectRecordArray.at(i)->isShanBi == true) {
            beHitCard->animationShanBi();
        }else {
            beHitCard->HP = affectRecordArray.at(i)->currentHP;
            beHitCard->MaxHP = affectRecordArray.at(i)->maxHP;
            this->createTeXiao(beHitCard);
            if (affectRecordArray.at(i)->isBaoJi == true) {
                this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"暴击");
            }else if(affectRecordArray.at(i)->isGeDang == true) {
                this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"格挡");
            }else {
                this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP,"");
            }
            
      //      this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
            //            if (beHitCard != NULL) {
            //                auto mingZhongBuff = MingZhongBuff::create();
            //                mingZhongBuff->decreaseBuff(beHitCard,0.1);
            //            }
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange,affectRecordArray.at(i)->nuQiMax);
        }
    }
    
    

}

void XuanWuCard::createTeXiao(Card *cardTexiao) {
    ParticleSystem *cps = ParticleSmoke::create();
    cps->setPosition(cardTexiao->cardSprite->getPosition());
    cps->setLife(0.05f);
    cps->setTotalParticles(100);
    cps->setDuration(0.7);
    //  cps->setGravity(Point(0,-480));
    cps->setEmissionRate(50);
    cps->setPosVar(Point(10,10));
    cardTexiao->forPlayer->fMap->addChild(cps,3000);
}

void XuanWuCard::daHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("niutou_conjure.mp3",false);
}

void XuanWuCard::daSkill(OneRecord *info) {
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
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        dazhao = CommonFunc::creatAnimation("niutou_conjure_l%d.png", 20, animationFactor*20, 1);
//    }else {
//        dazhao = CommonFunc::creatAnimation("niutou_conjure_l%d.png", 20, animationFactor*20, 1);
//    }

    dazhao = CommonFunc::creatAnimation("xuanwu_attackb_%d.png", 20, animationFactor*20, 1);
    auto move = CallFunc::create(CC_CALLBACK_0(XuanWuCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*8);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(XuanWuCard::moveAnimation, this, defaultPosition));
    auto nuqi = CallFunc::create(CC_CALLBACK_0(XuanWuCard::nuQiManage, this,info));
    auto appear = CallFunc::create(CC_CALLBACK_0(XuanWuCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(XuanWuCard::daHitBlock, this, info->affectRecordArray));
    // auto addNuqi = CallFunc::create(CC_CALLBACK_0(TaoTieCard::nuQiManage, this));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(XuanWuCard::daHitMusic, this));
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    
    this->cardSprite->runAction(Sequence::create(move,moveWait,dazhao,maxHit,wait,movaFanhui,moveWait,nuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,dazhaoMusic, NULL));
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void XuanWuCard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        zhanli = CommonFunc::creatAnimation("niutou_stand_l%d.png", 4, animationFactor*4*1.5, 1);
//    }else {
//        zhanli = CommonFunc::creatAnimation("niutou_stand_l%d.png", 4, animationFactor*4*1.5, 1);
//    }
    zhanli = CommonFunc::creatAnimation("xuanwu_idle_%d.png", 4, animationFactor*4*1.5, 1);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}

void XuanWuCard::moveAnimation(Vec2 target) {
    Animate* animateActionWalk = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        animateActionWalk = CommonFunc::creatAnimation("niutou_move_l%d.png", 8, animationFactor*8, 1);
//    }else {
//        animateActionWalk = CommonFunc::creatAnimation("niutou_move_l%d.png", 8, animationFactor*8, 1);
//    }
    animateActionWalk = CommonFunc::creatAnimation("xuanwu_move_%d.png", 8, animationFactor*8, 1);
    auto moveTo = MoveTo::create(animationFactor*8, target);
 //   auto animateActionWalk = CommonFunc::creatAnimation("niutou_move_%d.png", 8, 0.5f, 2);
    this->cardSprite->runAction(moveTo);
    this->cardSprite->runAction(animateActionWalk);
}

void XuanWuCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("niutou_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("niutou_conjure.mp3");
}


