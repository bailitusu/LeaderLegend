//
//  ShiFangNeiCun.cpp
//  OctLegend
//
//  Created by zc on 16/9/8.
//
//

#include "ShiFangNeiCun.h"
#include "FightPlayer.h"
#include "Dragon.h"
bool ShiFangNeiCun::init() {

    return true;

}

void ShiFangNeiCun::releaseMenmory(FightPlayer *player, FightPlayer *enemy) {
    for (int i = 0; i < player->cardArray.size(); i++) {
//        player->cardArray.at(i)->magicGoods->release();
      //  player->fDragon->release();
        player->cardArray.at(i)->release();
    }
    
    for (int i = 0; i < enemy->cardArray.size(); i++) {
//        enemy->cardArray.at(i)->magicGoods->release();
       // enemy->fDragon->release();
        enemy->cardArray.at(i)->release();
    }
    
    for (int i = 0; i < player->fMap->mapCellArray.size(); i++) {
        player->fMap->mapCellArray.at(i)->obj = NULL;
    }
    for (int i = 0; i < enemy->fMap->mapCellArray.size(); i++) {
        enemy->fMap->mapCellArray.at(i)->obj = NULL;
    }
    player->cardArray.clear();
    enemy->cardArray.clear();
}