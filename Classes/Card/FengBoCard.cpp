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
#include "ReadRecordFight.h"
bool FengBoCard::init() {
    this->cellIndex = 0;
    this->HP = 17000;
//    this->MaxHP = 20;
    this->hitRuleNum = hitRuleType.faShi;
    this->cardName = "fengbo";
    
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


void FengBoCard::recordRuning(FightPlayer *enemyTemp) {
    this->forEnemy = enemyTemp;
    
    auto oneRecord = OneRecord::create();
    
    
    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    oneRecord->hitTarget = this->targetNum;
    oneRecord->cardName = this->cardName;
    oneRecord->playerName = this->playerName;
    oneRecord->standIndex = this->cellIndex;
    
    
    if (this->nuQiNum < this->nuQiNumMax) {
        oneRecord->isXiaoZhao = true;
        oneRecord->isDaZhao = false;
        RecordFight::GetInstance()->addItemToRecord(oneRecord);
        this->recordHit();
        
        this->recordAddNuqi(this, 1);
        this->recordActionBlock();
    }else {
        oneRecord->isXiaoZhao = false;
        oneRecord->isDaZhao = true;
        RecordFight::GetInstance()->addItemToRecord(oneRecord);
        
        this->recordUltimateSkill();
        this->recordActionBlock();
        // this->cardSprite->runAction(Sequence::create(maxHit,block, NULL));
    }

}

//void FengBoCard::running(FightPlayer *enemyTemp) {
//    
//    this->forEnemy = enemyTemp;
//    
//    
//    auto defaultPosition = this->cardSprite->getPosition();
//    this->targetNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
//    
//    float tagetX = this->forEnemy->fMap->getPosition().x-this->forEnemy->enemy->fMap->getPosition().x+this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.x;
//    Vec2 target = Vec2(tagetX, this->forEnemy->fMap->mapCellArray.at(this->targetNum)->position.y); //this->playerTemp->fMap->mapCellArray.at(cellNum)->position;
//    
//    auto moveTo = MoveTo::create(1.0, target);
//    auto movaFanhui = MoveTo::create(1.0, defaultPosition);
//    
//    auto hit = CallFunc::create(CC_CALLBACK_0(FengBoCard::hitAction,this));
//   // auto wait = ActionWait::create(0.1);
//    auto maxHit = CallFunc::create(CC_CALLBACK_0(FengBoCard::ultimateSkill, this));
//    auto addNuqi = CallFunc::create(CC_CALLBACK_0(FengBoCard::nuQiManage, this));
//    auto block = CallFunc::create(CC_CALLBACK_0(FengBoCard::actionBlock,this));
//    if (this->fPro->nuqiPro->getPercentage() < 100) {
//        
//        this->cardSprite->runAction(Sequence::create(moveTo,hit,movaFanhui,addNuqi,block,NULL));
//        
//    }else {
//        this->cardSprite->runAction(Sequence::create(moveTo,maxHit,movaFanhui,block,NULL));
//    }
//    
//    
//    
//    this->fPro->hpPro->setVisible(false);
//    this->fPro->hpProBg->setVisible(false);
//    this->fPro->nuqiPro->setVisible(false);
//    this->fPro->nuqiProBg->setVisible(false);
//    
//}


void FengBoCard::nuQiManage() {
    this->addNuQi(this, 1);
}

void FengBoCard::recordHit() {
//    int cellNum = AttackRule::Rule(this->cellIndex, this->hitRuleNum, this->forEnemy->fMap);
    Vector<MapCell*> temp = this->forEnemy->fMap->hitHengPaiCell(this->targetNum);
    for (int i = 0; i < temp.size(); i++) {
        
 
        ((Card*)(temp.at(i))->obj)->recordDidBeHit(this,"fashu");
        this->recordAddNuqi((Card*)(temp.at(i))->obj, 1);
        
    }

}

void FengBoCard::recordUltimateSkill() {
    Vector<MapCell*> temp = this->forEnemy->fMap->hitAllCell();
    for (int i = 0; i < temp.size(); i++) {
        
        
        ((Card*)(temp.at(i))->obj)->recordDidBeHit(this,"fashu");
        this->recordAddNuqi((Card*)(temp.at(i))->obj, 1);
        if (((Card*)(temp.at(i))->obj) != NULL) {
            auto shanBiBuff = ShanBiBuff::create();
            shanBiBuff->decreaseBuff(((Card*)(temp.at(i))->obj),0.05);
            auto mianBaoBuff = MianBaoBuff::create();
            mianBaoBuff->decreaseBuff(((Card*)(temp.at(i))->obj),0.05);
        }
        
    }
    this->recordDecreaseNuqi(this, 3,true);

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
    if (this->playerName.compare("enemyPlayer") == 0) {
        gong = CommonFunc::creatAnimation("zhousi_attack_r%d.png", 16, animationFactor*16, 1);
    }else {
        gong = CommonFunc::creatAnimation("zhousi_attack_l%d.png", 16, animationFactor*16, 1);
    }
    
   // auto gong = CommonFunc::creatAnimation("zhousi_attack_%d.png", 16, 1.0f, 1);
    auto move = CallFunc::create(CC_CALLBACK_0(FengBoCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*8);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(FengBoCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(FengBoCard::appearUI, this));
    auto hit = CallFunc::create(CC_CALLBACK_0(FengBoCard::hitBlock,this,info->affectRecordArray));
    auto addNuqi = CallFunc::create(CC_CALLBACK_0(FengBoCard::nuQiManage, this));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto gongMusic = CallFunc::create(CC_CALLBACK_0(FengBoCard::xiaoHitMusic, this));
    
    this->cardSprite->runAction(Sequence::create(move,moveWait,gong,hit,wait,movaFanhui,moveWait,addNuqi,appear,recordBlock,NULL));
    this->cardSprite->runAction(Sequence::create(moveWait,gongMusic,NULL));
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);

}

void FengBoCard::moveAnimation(Vec2 target) {
    
    Animate* animateActionWalk = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        animateActionWalk = CommonFunc::creatAnimation("zhousi_move_r%d.png", 8, animationFactor*8, 1);
    }else {
        animateActionWalk = CommonFunc::creatAnimation("zhousi_move_l%d.png", 8, animationFactor*8, 1);
    }
    auto moveTo = MoveTo::create(animationFactor*8, target);
   // auto animateActionWalk = CommonFunc::creatAnimation("zhousi_move_%d.png", 8, 0.5f, 2);
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
            this->decreaseHP(beHitCard, affectRecordArray.at(i)->hitValue);
            
            this->addNuQi(beHitCard, 1);
        }
    }
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
    if (this->playerName.compare("enemyPlayer") == 0) {
        dazhao = CommonFunc::creatAnimation("zhousi_conjure_r%d.png", 16, animationFactor*16, 1);
    }else {
        dazhao = CommonFunc::creatAnimation("zhousi_conjure_l%d.png", 16, animationFactor*16, 1);
    }
    
   // auto dazhao = CommonFunc::creatAnimation("zhousi_conjure_%d.png", 16, 1.0f, 1);
    
    auto move = CallFunc::create(CC_CALLBACK_0(FengBoCard::moveAnimation, this, target));
    auto moveWait = ActionWait::create(animationFactor*8);
    auto wait = ActionWait::create(1.0);
    auto movaFanhui = CallFunc::create(CC_CALLBACK_0(FengBoCard::moveAnimation, this, defaultPosition));
    auto appear = CallFunc::create(CC_CALLBACK_0(FengBoCard::appearUI, this));
    auto maxHit = CallFunc::create(CC_CALLBACK_0(FengBoCard::daHitBlock, this, info->affectRecordArray));
    // auto addNuqi = CallFunc::create(CC_CALLBACK_0(TaoTieCard::nuQiManage, this));
    auto recordBlock = CallFunc::create(CC_CALLBACK_0(ReadRecordFight::readNextFightRecord, this->readRecordFight));
    auto dazhaoMusic = CallFunc::create(CC_CALLBACK_0(FengBoCard::daHitMusic, this));
    this->cardSprite->runAction(Sequence::create(move,moveWait,dazhao,maxHit,wait,movaFanhui,moveWait,appear,recordBlock,NULL));
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
            this->decreaseHP(beHitCard, affectRecordArray.at(i)->hitValue);
            if (beHitCard != NULL) {
                auto shanBiBuff = ShanBiBuff::create();
                shanBiBuff->decreaseBuff(beHitCard,0.05);
                auto mianBaoBuff = MianBaoBuff::create();
                mianBaoBuff->decreaseBuff(beHitCard,0.05);
            }
            
            this->addNuQi(beHitCard, 1);
        }
    }
    
    this->decreaseNuQi(this, 3, true);
}

void FengBoCard::runZhanLiAnimation() {
    Animate* zhanli = NULL;
    if (this->playerName.compare("enemyPlayer") == 0) {
        zhanli = CommonFunc::creatAnimation("zhousi_stand_r%d.png", 8, animationFactor*8*1.5, 1);
    }else {
        zhanli = CommonFunc::creatAnimation("zhousi_stand_l%d.png", 8, animationFactor*8*1.5, 1);
    }
   // auto zhanli = CommonFunc::creatAnimation("zhousi_stand_%d.png", 8, 0.5f, 2);
    this->standAction = RepeatForever::create(zhanli);
    this->standAction->retain();
    this->standAction->setTag(10);
    this->cardSprite->runAction(this->standAction);;
}
//
//void FengBoCard::ultimateSkill() {
//
//    Vector<MapCell*> temp = this->forEnemy->fMap->hitAllCell();
//    for (int i = 0; i < temp.size(); i++) {
//        
//        
//        ((Card*)(temp.at(i))->obj)->didBeHit(this,"fashu");
//        this->addNuQi((Card*)(temp.at(i))->obj, 1);
//        if (((Card*)(temp.at(i))->obj) != NULL) {
//            auto shanBiBuff = ShanBiBuff::create();
//            shanBiBuff->decreaseBuff(((Card*)(temp.at(i))->obj),0.05);
//            auto mianBaoBuff = MianBaoBuff::create();
//            mianBaoBuff->decreaseBuff(((Card*)(temp.at(i))->obj),0.05);
//        }
//        
//    }
//    this->decreaseNuQi(this, 3,true);
//}
