//
//  Treasure.cpp
//  OctLegend
//
//  Created by zc on 16/8/30.
//
//

#include "Treasure.h"
#include "Card.h"
#include "FightPlayer.h"
bool Treasure::init() {
    return true;
}

void Treasure::willRunAddNuQi(Card *card) {
    
}

float Treasure::specialMianShang(Card *card, float value) {
    return value;
}

void Treasure::initNuQi(Card *card) {
    
}

void Treasure::everyRoundAddHP(Card* card) {
    
}

void Treasure::bingFaHuiFuHp(FightPlayer *player) {

}

bool Treasure::spriteBrother(Card *card) {
    return false;
}

bool Treasure::mianYiCuoZhi() {
    return false;
}

float Treasure::fanTanWuLiHart(float hartValue) {
    return 0;
}

float Treasure::fanTanFaShuHart(float hartValue) {
    return 0;
}
