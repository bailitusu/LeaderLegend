//
//  FightField.cpp
//  OctLegend
//
//  Created by zc on 16/8/12.
//
//

#include "FightField.h"
#include "FightPlayer.h"
bool  FightField::init() {
    playerIndex = 0;
    enemyIndex = 0;
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto playerListener = EventListenerCustom::create("playerNextRun", CC_CALLBACK_0(FightField::playerNextRun, this));
    
    auto enemyListener = EventListenerCustom::create("enemyPlayerNextRun", CC_CALLBACK_0(FightField::enemyPlayerNextRun, this));
    dispatcher->addEventListenerWithFixedPriority(playerListener, 1);
    dispatcher->addEventListenerWithFixedPriority(enemyListener, 1);
    
    return true;
}

void FightField::playerNextRun() {
    if (playerIndex > 7) {
        this->netxRound();
        
        return;
    }
    Card* tempCard = player->cardArray.at(playerIndex++);
    if (tempCard->HP <= 0) {
        this->playerNextRun();
    }else {
        tempCard->runAnimation(enemyPlayer);
    }
}


void FightField::enemyPlayerNextRun() {
    if (enemyIndex > 7) {
        this->netxRound();
        return;
    }
    Card* tempCard = enemyPlayer->cardArray.at(enemyIndex++);
    if (tempCard->HP <= 0) {
        this->enemyPlayerNextRun();
    }else {
        tempCard->runAnimation(player);
    }
}

void FightField::startFight() {
    if (player->xiangong > enemyPlayer->xiangong) {
        if (this->player->cardArray.at(0)->HP > 0) {
            this->player->cardArray.at(0)->runAnimation(this->enemyPlayer);
            playerIndex++;
        }else {
            this->playerNextRun();
        }

    }else {
        if (this->enemyPlayer->cardArray.at(0)->HP > 0) {
            this->enemyPlayer->cardArray.at(0)->runAnimation(this->player);
            enemyIndex++;
        }else {
            this->enemyPlayerNextRun();
        }
    }
}

void FightField::netxRound() {
    if (playerIndex > 7 && enemyIndex > 7) {
        playerIndex = 0;
        enemyIndex = 0;
        this->startFight();
    }
    
}


