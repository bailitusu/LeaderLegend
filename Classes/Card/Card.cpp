//
//  Card.cpp
//  OctLegend
//
//  Created by zc on 16/8/12.
//
//

#include "Card.h"
#include "FightPlayer.h"
#include "CommonFunc.h"
#include "Setting.h"

bool Card::init() {
    return true;
}

void Card::didBeHit(Card* fromCard) {
    
    this->decreaseHP(this,fromCard->hitValue);
    if (this->HP <= 0) {
        this->cardDead();
        return;
    }
}

void Card::addHP(Card* card,float hpValue) {
    if (card != NULL) {
        card->HP = card->HP+hpValue;
        if (card->HP > card->MaxHP) {
            card->HP = card->MaxHP;
        }
        card->fPro->hpPro->setPercentage((1-(float)card->HP/card->MaxHP)*100);
    }

}

void Card::decreaseHP(Card* card,float hpValue) {
    if (card != NULL) {
        float percent = (1 - (card->HP-hpValue)/card->MaxHP) * 100;
        //  float aaa = this->fPro->hpPro->getPercentage();
        ProgressFromTo* ac = ProgressFromTo::create(1.0, card->fPro->hpPro->getPercentage(), percent);
        card->fPro->hpPro->runAction(ac);
        card->HP = card->HP - hpValue;
    }

}

void Card::addNuQi(Card* card,int num) {
    if (card != NULL) {
        if (card->fPro->nuqiPro->getPercentage() < 100) {
            switch (num) {
                case 1:
                    card->fPro->setNuQiProPrecent(34+card->fPro->nuqiPro->getPercentage());
                    break;
                case 2:
                    card->fPro->setNuQiProPrecent(66+card->fPro->nuqiPro->getPercentage());
                    break;
                case 3:
                    card->fPro->setNuQiProPrecent(100+card->fPro->nuqiPro->getPercentage());
                    break;
                default:
                    break;
            }
            
        }
    }

}

void Card::decreaseNuQi(Card* card,int num) {
    if (card != NULL) {
        if (card->fPro->nuqiPro->getPercentage() > 0) {
            switch (num) {
                case 1:
                    card->fPro->setNuQiProPrecent(card->fPro->nuqiPro->getPercentage()-34);
                    break;
                case 2:
                    card->fPro->setNuQiProPrecent(card->fPro->nuqiPro->getPercentage()-66);
                    break;
                case 3:
                    card->fPro->setNuQiProPrecent(card->fPro->nuqiPro->getPercentage()-100);
                    break;
                default:
                    break;
            }
            
        }
    }
}

void Card::willRun(FightPlayer* enemyTemp) {
    if (this->isHaveThisBuff("gedang")) {
        if(this->isHaveThisBuff("gedang")->thisBuffisEffect() == false) {
            
            this->isHaveThisBuff("gedang")->decrease(this);
            
        }
    }
}

void Card::running(FightPlayer* enemyTemp) {

}

void Card::endRun(FightPlayer* enemyTemp) {
    
}

void Card::runAnimation(FightPlayer* playerTemp) {
    
    this->willRun(playerTemp);
    this->running(playerTemp);

//    printf("run Animation error");
}

void Card::actionBlock() {
    this->fPro->hpPro->setVisible(true);
    this->fPro->hpProBg->setVisible(true);
    this->fPro->nuqiPro->setVisible(true);
    this->fPro->nuqiProBg->setVisible(true);
    
    
    this->endRun(this->forEnemy);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    if (playerName.compare("player") == 0) {
        EventCustom event = EventCustom("enemyPlayerNextRun");
        //event.setUserData((void*)123);
        dispatcher->dispatchEvent(&event);
    }else if (playerName.compare("enemyPlayer") == 0) {
        EventCustom event = EventCustom("playerNextRun");
        //event.setUserData((void*)123);
        dispatcher->dispatchEvent(&event);
    }

}

void Card::ultimateSkill() {
    printf("card ultimateSkill ");
}

void Card::cardDead() {
    this->forPlayer->fMap->mapCellArray.at(this->cellIndex)->obj = NULL;
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    this->cardSprite->removeFromParent();
}
void Card::initFightShuXing() {
    this->wuliHart = this->wuliHart*0.0075*this->wuLi+this->wuliHart;
    this->wuliMianShang = this->wuLi*0.0025*this->wuliMianShang + this->tongShuai*0.005*this->wuliMianShang + this->wuliMianShang;
    this->fashuHart = this->fashuHart*0.075*this->zhiLi+this->fashuHart;
    this->fashuMianShang = this->zhiLi*0.0025*this->wuliMianShang + this->tongShuai*0.005*this->wuliMianShang + this->fashuMianShang;
    this->mingZhong = this->mingZhong*0.0025*this->mingJie + this->mingZhong;
    this->baoJi = this->baoJi*0.005625*this->mingJie+this->baoJi;
    this->shanBi = this->shanBi*0.001875*this->yunQi + this->shanBi;
    this->mianBao = this->mianBao*0.00625*this->yunQi + this->mianBao;
    this->xianGong = this->mingJie*0.75+this->yunQi*0.25;
    
}

void Card::initCharacter() {
    
}

Buff* Card::isHaveThisBuff(std::string buffName) {
    for (int i = 0; i < this->buffArray.size(); i++) {
        if (this->buffArray.at(i)->buffName.compare("gedang") == 0) {
            return this->buffArray.at(i);
        }
    }
    return NULL;
}

void Card::suckBlood() {
    this->addHP(this, this->xiXue);
}

void Card::zaiShengBlood() {
    this->addHP(this, this->zhiLiao);
}

void Card::initCardSprite(std::string imageName) {
    this->cardSprite = Sprite::create(imageName);
    this->cardSprite->setAnchorPoint(Vec2(0.5, 0));
    // player->setFlippedX(true);
    CommonFunc::setSpriteSize(this->cardSprite, screenSize.width*0.075);
}