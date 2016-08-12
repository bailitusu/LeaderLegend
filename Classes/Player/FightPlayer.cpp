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

bool FightPlayer::init() {
//    HuangDiCard* aaa = HuangDiCard::create();
//    cardArray.pushBack(aaa);
    std::cout << cardArray.size() << std::endl;
    return true;
}

void FightPlayer::initMap(std::string imageName,std::string direction) {
    fMap = FightMap::create();
    fMap->init(imageName, direction);
    fMap->map->setPosition(0,0);
    fightLayer->addChild(fMap);
}