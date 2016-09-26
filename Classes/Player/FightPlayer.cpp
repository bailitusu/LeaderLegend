//
//  FightPlayer.cpp
//  OctLegend
//
//  Created by zc on 16/8/12.
//
//

#include "FightPlayer.h"
#include <iostream>
#include "HuangDiCard.h"
#include "MapCell.h"
#include "FightLayer.h"
#include "Dragon.h"
#include "AllArmyGuWu.h"
#include "HuiMieBoDong.h"
#include "CommonFunc.h"
#include "JiuXiaoLongYin.h"
#include "ZaiShengLongHou.h"
#include "ZhanYiGaoAng.h"

#include "SetRoleFormatLayer.h"
bool FightPlayer::init() {

    xiangong = 0;
    std::cout << cardArray.size() << std::endl;

    return true;
}

void FightPlayer::initMap(std::string imageName,std::string direction) {
    fMap = FightMap::create();
    fMap->init(imageName, direction);
    fMap->map->setPosition(0,0);
    fightLayer->addChild(fMap,-10);

}

void FightPlayer::setCardsPositon(Card *card, int index, int zPoint) {
    card->cardSprite->setPosition((fMap->mapCellArray.at(index))->position);
    (fMap->mapCellArray.at(index))->obj = card;
    card->cellIndex = index;
    fMap->addChild(card->cardSprite,zPoint);
    
}

void FightPlayer::initCardStandArray() {
    for (int i = 0; i < fMap->mapCellArray.size(); i++) {
        if ((fMap->mapCellArray.at(i))->obj != NULL) {
            this->cardArray.pushBack((Card*)(((MapCell*)fMap->mapCellArray.at(i))->obj));
        }
    }
}

void FightPlayer::initRecordTackCard(Card *card, int standIndex, std::string playerName, Treasure *treasure) {
    card->playerName = playerName;
    (fMap->mapCellArray.at(standIndex))->obj = card;
    card->cellIndex = standIndex;
    card->forPlayer = this;
   
    card->magicGoods = treasure;
    if (playerName.compare("enemyPlayer")==0) {
        card->magicGoods->retain();
    }
   // card->magicGoods->retain();
    card->initFightShuXing();
    card->retain();
    card->magicGoods->initRecordNuqi(card);
    
}



void FightPlayer::initTackCard(Card* card, std::string imageName, int standIndex, std::string playerName,Treasure* treasure) {
    card->initCardSprite(imageName);
    card->playerName = playerName;
   // printf("%d", this->xiangong);
    this->setCardsPositon(card, standIndex,standIndex*10+5);
    card->forPlayer = this;
    card->fPro = FightProgress::create();
    card->fPro->hpProBg->setPosition(card->cardSprite->getPosition().x,card->cardSprite->getPosition().y+40);
    this->fMap->addChild(card->fPro->hpProBg,standIndex*10+10);
    
    card->fPro->hpPro->setPosition(card->fPro->hpProBg->getPosition());
    this->fMap->addChild(card->fPro->hpPro,standIndex*10+20);
    

    
    card->fPro->initNuQiPro(0);
    card->fPro->nuqiProBg->setPosition(card->cardSprite->getPosition().x,card->cardSprite->getPosition().y+35);
    this->fMap->addChild(card->fPro->nuqiProBg, standIndex*10+10);
    
    card->fPro->nuqiPro->setPosition(card->fPro->nuqiProBg->getPosition());
    this->fMap->addChild(card->fPro->nuqiPro,standIndex*10+20);
    
    card->magicGoods = treasure;
    if (playerName.compare("enemyPlayer") == 0) {
        card->magicGoods->retain();
    }
    
    
    card->initFightShuXing();
    card->fPro->retain();
    card->retain();
       card->initHpLabel();
    
    auto aa = card->magicGoods;
    aa->initNuQi(card);
//    card->magicGoods->initNuQi(card);
    card->runZhanLiAnimation();
}

void FightPlayer::initDragon(std::string imageName) {
    this->fDragon = Dragon::create();
    this->fDragon->dragonSprite = Sprite::create(imageName);
    CommonFunc::setSpriteSize(this->fDragon->dragonSprite, 100);
    this->fDragon->dragonSprite->setAnchorPoint(Vec2(0.5, 1));
    this->fightLayer->addChild(this->fDragon->dragonSprite,200);
    this->fDragon->dragonSprite->setOpacity(0);
    this->fDragon->retain();
    
//    this->fDragon->addDragonSkill(JiuXiaoLongYin::create(), 0);
//    this->fDragon->addDragonSkill(HuiMieBoDong::create(), 1);
//    this->fDragon->addDragonSkill(ZaiShengLongHou::create(), 2);
//    this->fDragon->addDragonSkill(AllArmyGuWu::create(), 3);
//    this->fDragon->addDragonSkill(ZhanYiGaoAng::create(), 4);
}
