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

void Card::didBeHit(Card* fromCard, std::string hitKinds) {
    
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
        //float percent = (1 - (card->HP-hpValue)/card->MaxHP) * 100;
        //  float aaa = this->fPro->hpPro->getPercentage();
//        ProgressFromTo* ac = ProgressFromTo::create(1.0, card->fPro->hpPro->getPercentage(), percent);
//        card->fPro->hpPro->runAction(ac);
        
        card->HP = card->HP - hpValue;
        card->fPro->hpPro->setPercentage((1-(float)card->HP/card->MaxHP)*100);
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

void Card::decreaseNuQi(Card* card,int num, bool isDaZhao) {
    if (card != NULL) {
        if (card->fPro->nuqiPro->getPercentage() > 0) {
            bool hasZhenfen = false;
            for (int i = 0; i < card->buffArray.size(); i++) {
                if (card->buffArray.at(i)->buffName.compare("zhenfen") == 0) {
                    hasZhenfen = true;
                }
            }
            if (hasZhenfen == false || isDaZhao == true) {
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
}

void Card::willRun(FightPlayer* enemyTemp) {
    if (this->isHaveThisBuff("gedang")) {
        if(this->isHaveThisBuff("gedang")->thisBuffisEffect() == false) {
            this->geDang = this->isHaveThisBuff("gedang")->defaultValue;
            this->buffArray.eraseObject(this->isHaveThisBuff("gedang"));
            
        }
    }
}

void Card::running(FightPlayer* enemyTemp) {

}

void Card::endRun(FightPlayer* enemyTemp) {
    if (this->isHaveThisBuff("mingzhong")) {
        if(this->isHaveThisBuff("mingzhong")->thisBuffisEffect() == false) {
            this->mingZhong = this->isHaveThisBuff("mingzhong")->defaultValue;
            this->buffArray.eraseObject(this->isHaveThisBuff("mingzhong"));
            
        }
    }
    
    if (this->isHaveThisBuff("shanbi")) {
        if(this->isHaveThisBuff("shanbi")->thisBuffisEffect() == false) {
            this->shanBi = this->isHaveThisBuff("shanbi")->defaultValue;
            this->buffArray.eraseObject(this->isHaveThisBuff("shanbi"));
            
        }
    }
    
    if (this->isHaveThisBuff("mianbao")) {
        if(this->isHaveThisBuff("mianbao")->thisBuffisEffect() == false) {
            this->shanBi = this->isHaveThisBuff("mianbao")->defaultValue;
            this->buffArray.eraseObject(this->isHaveThisBuff("mianbao"));
            
        }
    }
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
    this->buffArray.clear();
    this->cardSprite->removeFromParent();
}

void Card::initFightShuXing() {
    this->wuliHart = this->wuLi*0.0075;
    this->wuliMianShang = this->wuLi*0.0025 + this->tongShuai*0.005;
    this->fashuHart = this->zhiLi*0.075;
    this->fashuMianShang = this->zhiLi*0.0025 + this->tongShuai*0.005;
    this->mingZhong = this->mingJie*0.0025;
    this->baoJi = this->mingJie*0.003125;
    this->shanBi = this->yunQi*0.001875;
    this->mianBao = this->yunQi*0.003125;
    this->xianGong = this->mingJie*0.75+this->yunQi*0.25;
    this->MaxHP = this->HP;
    this->initCharacter();
}

void Card::initCharacter() {
    
}

Buff* Card::isHaveThisBuff(std::string buffName) {
    for (int i = 0; i < this->buffArray.size(); i++) {
        if (this->buffArray.at(i)->buffName.compare(buffName) == 0) {
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