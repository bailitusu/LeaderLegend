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
    roundNum = 0;
    return true;
}

void FightField::playerNextRun() {
    if (playerIndex > (player->cardArray.size()-1)) {
        this->netxRound();
        
        return;
    }
    
    if (this->isHasCard(player) == true) {
        Card* tempCard = player->cardArray.at(playerIndex++);
        if (tempCard->HP <= 0) {
            this->playerNextRun();
        }else {
            tempCard->runAnimation(enemyPlayer);
        }
    }else {
        printf("enemy win");
    }

}


void FightField::enemyPlayerNextRun() {
    if (enemyIndex > (enemyPlayer->cardArray.size()-1)) {
        this->netxRound();
        return;
    }

    if(this->isHasCard(enemyPlayer) == true) {
        Card* tempCard = enemyPlayer->cardArray.at(enemyIndex++);
        if (tempCard->HP <= 0) {
            this->enemyPlayerNextRun();
        }else {
            tempCard->runAnimation(player);
        }
    }else {
        printf("player win");
    }

}

void FightField::startFight() {
  //  bool hasCard = false;
    if (player->xiangong > enemyPlayer->xiangong) {

//        for (int i = 0 ; i < this->enemyPlayer->cardArray.size(); i++) {
//            if (this->enemyPlayer->cardArray.at(i)->HP > 0) {
//                hasCard = true;
//                break;
//            }
//        }
        if (this->isHasCard(enemyPlayer) == true) {
            if (this->player->cardArray.at(0)->HP > 0) {
                this->player->cardArray.at(0)->runAnimation(this->enemyPlayer);
                playerIndex++;
            }else {
                this->playerNextRun();
            }
        }else {
            printf("player  win");
        }


    }else {

        if (this->isHasCard(player) == true) {
            if (this->enemyPlayer->cardArray.at(0)->HP > 0) {
                this->enemyPlayer->cardArray.at(0)->runAnimation(this->player);
                enemyIndex++;
            }else {
                this->enemyPlayerNextRun();
            }
        }else {
            printf("enemy  win");
        }
        
    }
}

void FightField::netxRound() {
    if (playerIndex > (player->cardArray.size()-1) && enemyIndex > (enemyPlayer->cardArray.size()-1)) {
        playerIndex = 0;
        enemyIndex = 0;
        roundNum++;
        this->startFight();
    }else if(playerIndex <= (player->cardArray.size()-1) ) {
        this->playerNextRun();
    }else if(enemyIndex <= (enemyPlayer->cardArray.size()-1)) {
        this->enemyPlayerNextRun();
    }
    
}

bool FightField::isHasCard(FightPlayer *tempPlayer) {
    for (int i = 0 ; i < tempPlayer->cardArray.size(); i++) {
        if (tempPlayer->cardArray.at(i)->HP > 0) {
            return true;
        }
    }
    return false;
}

