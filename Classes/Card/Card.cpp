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
#include "CommonFunc.h"
bool Card::init() {
    return true;
}

void Card::didBeHit(Card* fromCard, std::string hitKinds) {
    float hartValue = CommonFunc::reckonHitValue(fromCard, this, hitKinds);
    if (CommonFunc::isInPercent(CommonFunc::reckonBaoJiPercent(fromCard, this))) {
        if (hitKinds == "wuli") {
            hartValue = hartValue*1.5;
        }else if(hitKinds == "fashu") {
            hartValue = hartValue*1.75;
        }
    }
    if (CommonFunc::isInPercent(this->geDang)) {
        hartValue = hartValue*0.4;
    }
    hartValue = this->magicGoods->specialMianShang(this, hartValue);
    if (CommonFunc::isInPercent(CommonFunc::reckonShanBiPercent(fromCard, this, hitKinds)) != false) {
        
        
        fromCard->xiXue = hartValue;
        this->decreaseHP(this,hartValue);
        float tempHart = 0;
        if (hitKinds == "wuli") {
            tempHart = this->magicGoods->fanTanWuLiHart(hartValue);
            if (tempHart != 0) {
                fromCard->decreaseHP(fromCard, tempHart);
            }
        }else if(hitKinds == "fashu") {
            tempHart = this->magicGoods->fanTanFaShuHart(hartValue);
            if (tempHart != 0) {
                fromCard->decreaseHP(fromCard, tempHart);
            }
        }

//        if (this->HP <= 0) {
//            if (this->magicGoods->spriteBrother(this) == true) {
//                return;
//            }
//            this->cardDead();
//            return;
//        }

    }else {
        this->textLabel->setTextColor(Color4B(0, 0, 240, 255));
        this->showLabelText(this->textLabel, 0, "ShanBi");
    }

}

void Card::initHpLabel() {
    this->textLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 16);
    this->textLabel->setTextColor(Color4B(240, 0, 0, 255));
    this->textLabel->setOpacity(0);
    this->textLabel->setPosition(this->cardSprite->getPosition().x,this->cardSprite->getPosition().y+this->cardSprite->getBoundingBox().size.height+20);
    this->cardSprite->getParent()->addChild(this->textLabel,200);
}


void Card::addHP(Card* card,float hpValue) {
    if (card != NULL) {
        card->textLabel->setTextColor(Color4B(0, 240, 0, 255));
       // CommonFunc::showHitValue(card->hpLabel, (int)hpValue);
        card->showLabelText(card->textLabel, (int)hpValue, "");
//        auto appear = FadeTo::create(0.5, 255);
//        auto disappear = FadeTo::create(0.5, 0);
//        auto block = CallFunc::create(CC_CALLBACK_0(Card::textLabelDisappearBlock,this));
//        card->textLabel->runAction(Sequence::create(appear,disappear,block, NULL));
        
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
        card->textLabel->setTextColor(Color4B(240, 0, 0, 255));
      //  CommonFunc::showHitValue(card->textLabel, (int)hpValue);
        card->showLabelText(card->textLabel, (int)hpValue, "");
//        auto appear = FadeTo::create(0.5, 255);
//        auto disappear = FadeTo::create(0.5, 0);
//        //auto block = CallFunc::create(CC_CALLBACK_0(Card::hpFontDisappearBlock,this));
//        this->hpLabel->runAction(Sequence::create(appear,disappear, NULL));
        card->HP = card->HP - hpValue;
        card->fPro->hpPro->setPercentage((1-(float)card->HP/card->MaxHP)*100);
        
        if (card->HP <= 0) {
            if (card->magicGoods->spriteBrother(card) == true) {
                return;
            }
            card->cardDead();
        }
    }

}

void Card::showLabelText(cocos2d::Label *label, int hpValue, std::string text) {
    
    if (text.compare("") != 0) {
        //printf("%s",text.c_str());
        label->setString(text.c_str());
    }else {
        std::stringstream ss;
        ss << hpValue;
        label->setString(ss.str());
    }

    
    auto appear = FadeTo::create(0.5, 255);
    auto disappear = FadeTo::create(0.5, 0);
    auto block = CallFunc::create(CC_CALLBACK_0(Card::textLabelDisappearBlock,this));
    label->runAction(Sequence::create(appear,disappear,block, NULL));
}

void Card::textLabelDisappearBlock() {
    //this->hpLabel->removeFromParent();
    this->textLabel->setTextColor(Color4B(240, 0, 0, 255));
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
            card->nuQiNum = card->nuQiNum+num;
            if (card->nuQiNum >= card->nuQiNumMax) {
                card->nuQiNum = card->nuQiNumMax;
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

            if (hasZhenfen == false || isDaZhao == true || card->magicGoods->mianYiCuoZhi() == false) {
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
                card->nuQiNum = card->nuQiNum-num;
                if (card->nuQiNum <= 0) {
                    card->nuQiNum = 0;
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
    this->magicGoods->everyRoundAddHP(this);
    this->magicGoods->willRunAddNuQi(this);
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
    
    if (this->isHaveThisBuff("zhenfen")) {
        if(this->isHaveThisBuff("zhenfen")->thisBuffisEffect() == false) {
          //  this->shanBi = this->isHaveThisBuff("zhenfen")->defaultValue;
            this->buffArray.eraseObject(this->isHaveThisBuff("zhenfen"));
            
        }
    }
}

void Card::runAnimation(FightPlayer* playerTemp) {
    
    this->willRun(playerTemp);
    
    if (this->isHaveThisBuff("xuanyun")) {
        if(this->isHaveThisBuff("xuanyun")->thisBuffisEffect() == false) {
   
            this->buffArray.eraseObject(this->isHaveThisBuff("xuanyun"));
            this->running(playerTemp);
        }else {
            this->forEnemy = playerTemp;
            this->actionBlock();
        }
    }else {
        this->running(playerTemp);
    }
    
    

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
    
    this->magicGoods->bingFaHuiFuHp(this->forPlayer);
    
    this->fPro->hpPro->setVisible(false);
    this->fPro->hpProBg->setVisible(false);
    this->fPro->nuqiPro->setVisible(false);
    this->fPro->nuqiProBg->setVisible(false);
    this->buffArray.clear();
    this->cardSprite->removeFromParent();
}

void Card::initFightShuXing() {
    this->nuQiNum = 0;
    this->nuQiNumMax = 3;
    this->wuliHart = this->wuLi*0.0075;
    this->wuliMianShang = this->wuLi*0.0025 + this->tongShuai*0.005;
    this->fashuHart = this->zhiLi*0.0075;
    this->fashuMianShang = this->zhiLi*0.0025 + this->tongShuai*0.005;
    this->mingZhong = this->mingJie*0.0025;
    this->baoJi = this->mingJie*0.003125;
    this->shanBi = this->yunQi*0.001875;
    this->mianBao = this->yunQi*0.003125;
    this->xianGong = this->mingJie*0.75+this->yunQi*0.25;
    this->MaxHP = this->HP;
    this->initCharacter();
    this->initHpLabel();

    this->gongJi = this->magicGoods->gongJi+this->gongJi;
    this->fangYu = this->fangYu+this->magicGoods->fangYu;
    this->faLi = this->faLi+this->magicGoods->faLi;
    this->mingZhong = this->mingZhong + this->magicGoods->mingZhong;
    this->shanBi = this->shanBi + this->magicGoods->shanBi;
    this->baoJi = this->baoJi + this->magicGoods->baoJi;
    this->mianBao = this->mianBao + this->magicGoods->mianBao;
    this->magicGoods->initNuQi(this);
}

void Card::initCharacter() {
    
}

Buff* Card::isHaveThisBuff(std::string buffName) {
    for (int i = 0; i < this->buffArray.size(); i++) {
        //printf("%s\n",buffName.c_str());
        if (this->buffArray.at(i)->buffName.compare(buffName) == 0) {
            return this->buffArray.at(i);
        }
    }
    return NULL;
}

void Card::suckBlood(Card* fangYuCard) {
    this->addHP(this, this->xiXue*0.5);
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