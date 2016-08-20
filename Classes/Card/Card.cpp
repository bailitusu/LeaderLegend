//
//  Card.cpp
//  OctLegend
//
//  Created by zc on 16/8/12.
//
//

#include "Card.h"
#include "FightPlayer.h"
bool Card::init() {
    return true;
}

void Card::didBeHit(float hitValue) {
    log("card~~~~~~~");
}

void Card::runAnimation(FightPlayer* playerTemp) {
    printf("run Animation error");
}

void Card::ultimateSkill() {
    printf("card ultimateSkill ");
}

void Card::cardDead() {
    
}