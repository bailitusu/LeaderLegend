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




