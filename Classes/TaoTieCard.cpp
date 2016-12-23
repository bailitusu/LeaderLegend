//
//  TaoTieCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/20.
//
//

#include "TaoTieCard.h"
#include "FightPlayer.h"
#include "AttackRule.h"
#include "Setting.h"
#include "OneRecord.h"
#include "RecordFight.h"
#include "ReadRecordFight.h"
#include "ActionWait.h"
#include "CommonFunc.h"
#include "FightProgress.h"
bool TaoTieCard::init() {
    this->cellIndex = 0;
    this->HP = 20000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.jinZhan;
    this->cardName = "taotie";
    this->cardZhongWenName = "饕餮";
    this->cardSpriteImageName = "taotie_idle";
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
//    this->wuliHart = 10;
//    this->wuliMianShang = 10;
//    this->fashuHart = 10;
//    this->fashuMianShang = 10;
//    this->shanBi = 20;
//    this->mingZhong = 10;
//    this->baoJi = 10;
//    this->mianBao = 10;
//    this->lianJi = 1;
//    this->hitValue = 2;
//    this->xiXue = 2;
    this->bingKinds = bingZhongType.jinZhan;
    this->hitLevel = 1.05;
    this->cardLevel = 60;
    return true;
}

void TaoTieCard::preCardAudio() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("panda_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pande_conjure.mp3");
}

//void TaoTieCard::recordRuning(FightPlayer *enemyTemp) {
//    this->forEnemy = enemyTemp;
//    auto oneRecord = OneRecord::create();
//    
//    if (this->nuQiNum >= this->nuQiNumMax) {
//        oneRecord->isXiaoZhao = false;
//        oneRecord->isDaZhao = true;
//        this->targetNum = AttackRule::Rule(this->cellIndex, 2, this->forEnemy->fMap);
//    }else {
//        oneRecord->isXiaoZhao = true;
//        oneRecord->isDaZhao = false;
//       this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    }
//
//    oneRecord->hitTarget = this->targetNum;
//    oneRecord->cardName = this->cardName;
//    oneRecord->playerName = this->playerName;
//    oneRecord->standIndex = this->cellIndex;
//
//
//    if (this->nuQiNum < this->nuQiNumMax) {
//
//        RecordFight::GetInstance()->addItemToRecord(oneRecord);
//        
//        this->recordHit();
//        this->recordAddNuqi(this, 1);
//        this->recordActionBlock();
//    }else {
//
//        RecordFight::GetInstance()->addItemToRecord(oneRecord);
//        this->recordUltimateSkill();
//        this->recordActionBlock();
//        // this->cardSprite->runAction(Sequence::create(maxHit,block, NULL));
//    }
//
//
//}
//
void TaoTieCard::xiaoHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("panda_attack.mp3",false);
}

void TaoTieCard::xiaoSkll(OneRecord *info) {
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
//        gong = CommonFunc::creatAnimation("panda_attack_r%d.png", 8, animationFactor*8, 1);
//    }else {
//        gong = CommonFunc::creatAnimation("panda_attack_l%d.png", 8, animationFactor*8, 1);
//    }
    gong = CommonFunc::creatAnimation("taotie_attackm_%d.png", 8, animationFactor*8, 1);
   
    auto move = CallFunc::create(CC_CALLBACK_0(TaoTieCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*8);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(TaoTieCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(TaoTieCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(TaoTieCard::hitBlock,this,info->affectRecordArray));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(TaoTieCard::nuQiManage, this,info));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(TaoTieCard::xiaoHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,wait,movaFanhui,moveWait,addNuqi,afterAction,appear,recordBlock,NULL));
    
    this->cardSprite->runAction(Sequence::create(moveWait,gongMusic,NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);

}

void TaoTieCard::daHitMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("panda_conjure.mp3",false);
}

void TaoTieCard::daSkill(OneRecord *info) {
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
//        dazhao = CommonFunc::creatAnimation("panda_conjure_r%d.png", 20, animationFactor*20, 1);
//    }else {
//        dazhao = CommonFunc::creatAnimation("panda_conjure_l%d.png", 20, animationFactor*20, 1);
//    }
    dazhao = CommonFunc::creatAnimation("taotie_attackb_%d.png", 20, animationFactor*20, 1);
    auto move = CallFunc::create(CC_CALLBACK_0(TaoTieCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*8);
    auto dazhaoWait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(TaoTieCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(TaoTieCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(TaoTieCard::daHitBlock, this, info->affectRecordArray));
   // auto addNuqi = CallFunc::create(CC_CALLBACK_0(TaoTieCard::nuQiManage, this));
    auto myNuqi = CallFunc::create(CC_CALLBACK_0(TaoTieCard::nuQiManage, this,info));
    
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(TaoTieCard::daHitMusic, this));
    
    auto afterAction = CallFunc::create(CC_CALLBACK_0(Card::afterAnimation,this,info,this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,dazhao,maxHit,dazhaoWait,movaFanhui,moveWait,myNuqi,afterAction,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,dazhaoMusic,NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
}

void TaoTieCard::daHitBlock(Vector<OneRecord *> affectRecordArray) {
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
            
       //     this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange,affectRecordArray.at(i)->nuQiMax);
        }
    }
       // this->decreaseNuQi(this, 3,true);
    
}

void TaoTieCard::appearUI() {
    this->cardSprite->runAction(this->standAction);
    CommonFunc::removeAnimation();
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("panda_attack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("pande_conjure.mp3");
}
void TaoTieCard::moveAnimation(Vec2 target) {
    Animate* animateActionWalk = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        animateActionWalk = CommonFunc::creatAnimation("panda_move_r%d.png", 8, animationFactor*8, 1);
//    }else {
//        animateActionWalk = CommonFunc::creatAnimation("panda_move_l%d.png", 8, animationFactor*8, 1);
//    }
    animateActionWalk = CommonFunc::creatAnimation("taotie_move_%d.png", 8, animationFactor*8, 1);
    auto moveTo = MoveTo::create(animationFactor*8, target);
    this->cardSprite->runAction(moveTo);
    this->cardSprite->runAction(animateActionWalk);
}

void TaoTieCard::nuQiManage(OneRecord *info) {
    this->nuQiAppear(this, info->nuQiChange,info->nuQiMax);
}


void TaoTieCard::createTeXiao(Card *cardTexiao) {
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

void TaoTieCard::hitBlock(Vector<OneRecord *> affectRecordArray) {

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
            
        //    this->hpAppear(beHitCard, affectRecordArray.at(i)->hitValue, affectRecordArray.at(i)->currentHP);
            this->nuQiAppear(beHitCard, affectRecordArray.at(i)->nuQiChange,affectRecordArray.at(i)->nuQiMax);
        }
    }
    


}




void TaoTieCard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
//    if (this->playerName.compare("enemyPlayer") == 0) {
//        zhanli = CommonFunc::creatAnimation("panda_stand_r%d.png", 4, animationFactor*4, 1);
//    }else {
//        zhanli = CommonFunc::creatAnimation("panda_stand_l%d.png", 4, animationFactor*4, 1);
//    }
    zhanli = CommonFunc::creatAnimation("taotie_idle_%d.png", 4, animationFactor*4, 1);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);
}
