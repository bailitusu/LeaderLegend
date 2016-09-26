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
#include "RecordFight.h"


bool Card::init() {
    return true;
}
void Card::recordDidBeHit(Card *fromCard, std::string hitKinds) {
    float hartValue = CommonFunc::reckonHitValue(fromCard, this, hitKinds);
    OneRecord* oneRecord = OneRecord::create();
    oneRecord->isBaoJi = false;
    oneRecord->isGeDang = false;
    oneRecord->isShanBi = false;
    if (CommonFunc::isInPercent(CommonFunc::reckonBaoJiPercent(fromCard, this))) {
        if (hitKinds == "wuli") {
            hartValue = hartValue*1.5;
        }else if(hitKinds == "fashu") {
            hartValue = hartValue*1.75;
        }
        oneRecord->isBaoJi = true;
    }
    if (CommonFunc::isInPercent(this->geDang)) {
        hartValue = hartValue*0.4;
        oneRecord->isGeDang = true;
    }
    if (this->cardName.compare("xingtian") == 0) {
        if (fromCard->bingKinds == bingZhongType.yuanCheng) {
            hartValue = hartValue*0.2;
        }
    }
    if (this->cardName.compare("suanyu") == 0) {
        if (fromCard->bingKinds == bingZhongType.yuanCheng) {
            hartValue = hartValue*2;
        }
    }
    hartValue = this->magicGoods->specialMianShang(this, hartValue);
    if (CommonFunc::isInPercent(CommonFunc::reckonShanBiPercent(fromCard, this, hitKinds)) != false) {
        
        oneRecord->isShanBi = false;
        oneRecord->hitValue = hartValue;
        fromCard->xiXue = hartValue;
        this->recordDecreaseHP(this,hartValue);
        float tempHart = 0;
        if (hitKinds == "wuli") {
            tempHart = this->magicGoods->fanTanWuLiHart(hartValue);
            if (tempHart != 0) {
                oneRecord->fanTanWuLiHartValue = tempHart;
                fromCard->recordDecreaseHP(fromCard, tempHart);
            }
        }else if(hitKinds == "fashu") {
            tempHart = this->magicGoods->fanTanFaShuHart(hartValue);
            if (tempHart != 0) {
                oneRecord->fanTanFaShuHartValue = tempHart;
                fromCard->recordDecreaseHP(fromCard, tempHart);
            }
        }

        
    }else {
        oneRecord->isShanBi = true;
    }
    oneRecord->playerName = this->playerName;
    oneRecord->cardName = this->cardName;
    oneRecord->standIndex = this->cellIndex;
    RecordFight::GetInstance()->addAffectCardArray(RecordFight::GetInstance()->currentRecordIndex, oneRecord);

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

void Card::xiaoSkll(OneRecord *info) {
    
}

void Card::daSkill(OneRecord *info) {
    
}

void Card::animationShanBi() {
    this->textLabel->setTextColor(Color4B(0, 0, 240, 255));
    this->showLabelText(this->textLabel, 0, "ShanBi");
}

void Card::initHpLabel() {
    this->textLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 16);
    this->textLabel->setTextColor(Color4B(240, 0, 0, 255));
    this->textLabel->setOpacity(0);
    this->textLabel->setPosition(this->cardSprite->getPosition().x,this->cardSprite->getPosition().y+50);
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
void Card::recordAddHP(Card *card, float hpValue) {
    if (card != NULL) {
        card->HP = card->HP+hpValue;
        if (card->HP > card->MaxHP) {
            card->HP = card->MaxHP;
        }
    }
}
void Card::recordDecreaseHP(Card *card, float hpValue) {
    if (card != NULL) {

        card->HP = card->HP - hpValue;
       // card->fPro->hpPro->setPercentage((1-(float)card->HP/card->MaxHP)*100);
        
        if (card->HP <= 0) {
            if (card->magicGoods->spriteBrother(card) == true) {
                return;
            }
            card->recordCardDead();
        }
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

void Card::recordAddNuqi(Card *card, int num) {
    if (card != NULL) {
        if (card->nuQiNum < card->nuQiNumMax) {
     
            card->nuQiNum = card->nuQiNum+num;
            if (card->nuQiNum >= card->nuQiNumMax) {
                card->nuQiNum = card->nuQiNumMax;
            }
        }
    }

}

void Card::recordDecreaseNuqi(Card *card, int num,bool isDaZhao) {
    if (card != NULL) {
        if (card->nuQiNum > 0) {
            bool hasZhenfen = false;
            for (int i = 0; i < card->buffArray.size(); i++) {
                if (card->buffArray.at(i)->buffName.compare("zhenfen") == 0) {
                    hasZhenfen = true;
                }
            }
            
            if (hasZhenfen == false || isDaZhao == true || card->magicGoods->mianYiCuoZhi() == false) {

                card->nuQiNum = card->nuQiNum-num;
                if (card->nuQiNum <= 0) {
                    card->nuQiNum = 0;
                }
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
    this->forEnemy = enemyTemp;
    if (this->isHaveThisBuff("gedang")) {
        if(this->isHaveThisBuff("gedang")->thisBuffisEffect() == false) {
            this->geDang = this->isHaveThisBuff("gedang")->defaultValue;
            this->buffArray.eraseObject(this->isHaveThisBuff("gedang"));
            
        }
    }
    this->magicGoods->everyRoundAddHP(this);
    this->magicGoods->willRunAddNuQi(this);
    this->forPlayer->fMap->setLocalZOrder(1000);
}

void Card::running(FightPlayer* enemyTemp) {

}

void Card::recordRuning(FightPlayer *enemyTemp) {
    
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
    this->forPlayer->fMap->setLocalZOrder(-10);
}

void Card::runAnimation(FightPlayer* playerTemp) {
    
    this->willRun(playerTemp);
    
    if (this->isHaveThisBuff("xuanyun")) {
        if(this->isHaveThisBuff("xuanyun")->thisBuffisEffect() == false) {
   
            this->buffArray.eraseObject(this->isHaveThisBuff("xuanyun"));
           // this->running(playerTemp);
            this->recordRuning(playerTemp);
        }else {
            this->forEnemy = playerTemp;
            this->actionBlock();
        }
    }else {
        //this->running(playerTemp);
        this->recordRuning(playerTemp);
    }
    
    

//    printf("run Animation error");
}

void Card::recordActionBlock() {
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
void Card::runZhanLiAnimation() {

}
void Card::actionBlock() {
//    this->fPro->hpPro->setVisible(true);
//    this->fPro->hpProBg->setVisible(true);
//    this->fPro->nuqiPro->setVisible(true);
//    this->fPro->nuqiProBg->setVisible(true);
    
    this->forPlayer->fMap->setLocalZOrder(-10);
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

void Card::recordCardDead() {
    this->forPlayer->fMap->mapCellArray.at(this->cellIndex)->obj = NULL;
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
 

    this->gongJi = this->magicGoods->gongJi+this->gongJi;
    this->fangYu = this->fangYu+this->magicGoods->fangYu;
    this->faLi = this->faLi+this->magicGoods->faLi;
    this->mingZhong = this->mingZhong + this->magicGoods->mingZhong;
    this->shanBi = this->shanBi + this->magicGoods->shanBi;
    this->baoJi = this->baoJi + this->magicGoods->baoJi;
    this->mianBao = this->mianBao + this->magicGoods->mianBao;
    
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

void Card::zaiShengBlood(bool isRecord) {
    if (isRecord == true) {
        this->recordAddHP(this, this->zhiLiao);
    }else {
        this->addHP(this, this->zhiLiao);
    }
   
}

void Card::stopStandAnimation() {
    this->cardSprite->stopActionByTag(10);
}

void Card::initCardSprite(std::string imageName) {
    this->cardSprite = Sprite::create(imageName);
    this->cardSprite->setAnchorPoint(Vec2(0.5, 0.5));
    // player->setFlippedX(true);
    CommonFunc::setSpriteSize(this->cardSprite, screenSize.width*0.25);
}
