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
bool FightPlayer::init() {

    xiangong = 0;
    std::cout << cardArray.size() << std::endl;

    return true;
}

void FightPlayer::initMap(std::string imageName,std::string direction) {
    fMap = FightMap::create();
    fMap->init(imageName, direction);
    fMap->map->setPosition(0,0);
    fightLayer->addChild(fMap);
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

void FightPlayer::initTackCard(Card* card, std::string imageName, int standIndex, std::string playerName) {
    card->initCardSprite(imageName);
    card->playerName = playerName;
    
    this->setCardsPositon(card, standIndex,standIndex*10);
    card->forPlayer = this;
    card->fPro = FightProgress::create();
    card->fPro->hpProBg->setPosition(card->cardSprite->getPosition().x,card->cardSprite->getPosition().y+card->cardSprite->getBoundingBox().size.height+10);
    this->fMap->addChild(card->fPro->hpProBg,standIndex*10+10);
    
    card->fPro->hpPro->setPosition(card->fPro->hpProBg->getPosition());
    this->fMap->addChild(card->fPro->hpPro,standIndex*10+20);
    
    
    card->fPro->initNuQiPro(0);
    card->fPro->nuqiProBg->setPosition(card->cardSprite->getPosition().x,card->cardSprite->getPosition().y+card->cardSprite->getBoundingBox().size.height+5);
    this->fMap->addChild(card->fPro->nuqiProBg, standIndex*10+10);
    
    card->fPro->nuqiPro->setPosition(card->fPro->nuqiProBg->getPosition());
    this->fMap->addChild(card->fPro->nuqiPro,standIndex*10+20);
   // card->initFightShuXing();
    card->fPro->retain();
    card->retain();

}


