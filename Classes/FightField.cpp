//
//  FightField.cpp
//  OctLegend
//
//  Created by zc on 16/8/12.
//
//

#include "FightField.h"
#include "FightPlayer.h"
#include "Dragon/Dragon.h"
#include "Setting/ActionWait.h"
#include "Setting/OneRecord.h"
#include "Setting/RecordFight.h"
#include "ShiFangNeiCun.h"
#include "ReadRecordFight.h"
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
    
    if (this->isHasCard(player) == true) {
        
        if (playerIndex > (player->cardArray.size()-1)) {
            this->netxRound();
            return;
        }
    
    
        Card* tempCard = player->cardArray.at(playerIndex++);
        if (tempCard->HP <= 0) {
            this->playerNextRun();
        }else {
            tempCard->runAnimation(enemyPlayer);
        }
    } else {

        
        OneRecord* record = OneRecord::create();
        record->whoSuccess = "enemy win";
      //  printf("------%zd", this->roleData.size());
        
        RecordFight::GetInstance()->addFightResult(record, 1);
        ShiFangNeiCun::releaseMenmory(player, enemyPlayer);
       // this->release();
      //  printf("------%zd", this->roleData.size());
        ReadRecordFight* rf = ReadRecordFight::create();
        rf->player = this->player;
        rf->playerEnemy = this->enemyPlayer;
        rf->roleData = &this->roleData;
        rf->readRecordFormMenmory();
        rf->readNextFightRecord();
        rf->retain();
        printf("enemy win");
        
        
    }

}


void FightField::enemyPlayerNextRun() {
    
    if(this->isHasCard(enemyPlayer) == true) {
        
        if (enemyIndex > (enemyPlayer->cardArray.size()-1)) {
            this->netxRound();
            return;
        }
    
        Card* tempCard = enemyPlayer->cardArray.at(enemyIndex++);
        if (tempCard->HP <= 0) {
            this->enemyPlayerNextRun();
        }else {
            tempCard->runAnimation(player);
        }
    }else {

        OneRecord* record = OneRecord::create();
        record->whoSuccess = "player win";
      //  printf("------%zd", this->roleData.size());
        RecordFight::GetInstance()->addFightResult(record, 1);
        ShiFangNeiCun::releaseMenmory(player, enemyPlayer);
       // this->release();
       // printf("------%zd", this->roleData.size());
        ReadRecordFight* rf = ReadRecordFight::create();
        rf->roleData = &this->roleData;
        rf->player = this->player;
        rf->playerEnemy = this->enemyPlayer;
        rf->readRecordFormMenmory();
        rf->readNextFightRecord();
        rf->retain();
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
                playerIndex++;
                this->player->cardArray.at(0)->runAnimation(this->enemyPlayer);
                
            }else {
                this->playerNextRun();
            }
        }else {
            OneRecord* record = OneRecord::create();
            record->whoSuccess = "player win";
         //   printf("------%zd", this->roleData.size());
            RecordFight::GetInstance()->addFightResult(record, 1);
            ShiFangNeiCun::releaseMenmory(player, enemyPlayer);
          //  this->release();
         //   printf("------%zd", this->roleData.size());
            ReadRecordFight* rf = ReadRecordFight::create();
            rf->player = this->player;
            rf->playerEnemy = this->enemyPlayer;
            rf->roleData = &this->roleData;
            rf->readRecordFormMenmory();
            rf->readNextFightRecord();
            rf->retain();
            printf("player  win");

        }


    }else {

        if (this->isHasCard(player) == true) {
            if (this->enemyPlayer->cardArray.at(0)->HP > 0) {
                enemyIndex++;
                this->enemyPlayer->cardArray.at(0)->runAnimation(this->player);
                
            }else {
                this->enemyPlayerNextRun();
            }
        }else {
            OneRecord* record = OneRecord::create();
            record->whoSuccess = "enemy win";
          //  printf("------%zd", this->roleData.size());
            RecordFight::GetInstance()->addFightResult(record, 1);
            ShiFangNeiCun::releaseMenmory(player, enemyPlayer);
            //this->release();
          //  printf("------%zd", this->roleData.size());
            ReadRecordFight* rf = ReadRecordFight::create();
            rf->player = this->player;
            rf->playerEnemy = this->enemyPlayer;
            rf->roleData = &this->roleData;
            rf->readRecordFormMenmory();
            rf->readNextFightRecord();
            rf->retain();
            printf("enemy  win");
        }
        
    }
}

void FightField::netxRound() {
    
    if (playerIndex > (player->cardArray.size()-1) && enemyIndex > (enemyPlayer->cardArray.size()-1)) {
        
        /* zyh
        printf("----------------next round  ");
        int playerCount = 0;
        for (int i = 0 ; i < this->player->cardArray.size(); i++) {
            if (this->player->cardArray.at(i)->HP > 0) {
                playerCount++;
            }
        }
        printf("player count: %d ", playerCount);
        
        int enemyCount = 0;
        for (int i = 0 ; i < this->enemyPlayer->cardArray.size(); i++) {
            if (this->enemyPlayer->cardArray.at(i)->HP > 0) {
                enemyCount++;
            }
        }
        printf("enemy count: %d\n\n\n", enemyCount);
        */
        
        playerIndex = 0;
        enemyIndex = 0;
        roundNum++;
        if (this->player->xiangong > this->enemyPlayer->xiangong) {
            auto wait = ActionWait::create(1.0);
            auto apper = FadeTo::create(0.5, 255);
            auto disapper = FadeTo::create(0.5, 0);
            auto run = CallFunc::create(CC_CALLBACK_0(FightField::dragonRun,this,"player"));
            auto block = CallFunc::create(CC_CALLBACK_0(FightField::dragonBlock,this,"player"));
            this->player->fDragon->dragonSprite->runAction(Sequence::create(run,block, NULL));//
        }else {
            auto wait = ActionWait::create(1.0);
            auto apper = FadeTo::create(0.5, 255);
            auto disapper = FadeTo::create(0.5, 0);
            auto run = CallFunc::create(CC_CALLBACK_0(FightField::dragonRun,this,"enemy"));
            auto block = CallFunc::create(CC_CALLBACK_0(FightField::dragonBlock,this,"enemy"));
            this->enemyPlayer->fDragon->dragonSprite->runAction(Sequence::create(run,block, NULL));
        }
       // this->startFight();
    }else if(playerIndex <= (player->cardArray.size()-1) ) {
        this->playerNextRun();
    }else if(enemyIndex <= (enemyPlayer->cardArray.size()-1)) {
        this->enemyPlayerNextRun();
    }
    
    
    else {
        printf("❌ERROR");
    }
    
}

void FightField::dragonRun(std::string playerName) {
    if (playerName.compare("player") == 0) {
        this->player->fDragon->runNextDragonSkill(this->player);
    }else {
        this->enemyPlayer->fDragon->runNextDragonSkill(this->enemyPlayer);
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

void FightField::dragonBlock(std::string playerName) {
    if (playerName.compare("player") == 0) {
        auto wait = ActionWait::create(1.0);
        auto apper = FadeTo::create(0.5, 255);
        auto disapper = FadeTo::create(0.5, 0);
        auto run = CallFunc::create(CC_CALLBACK_0(FightField::dragonRun,this,"enemy"));
        auto block = CallFunc::create(CC_CALLBACK_0(FightField::startFight,this));
        this->enemyPlayer->fDragon->dragonSprite->runAction(Sequence::create(run,block, NULL));//apper,disapper,run,wait,
    }else if (playerName.compare("enemy") == 0) {
        auto wait = ActionWait::create(1.0);
        auto apper = FadeTo::create(0.5, 255);
        auto disapper = FadeTo::create(0.5, 0);
        auto run = CallFunc::create(CC_CALLBACK_0(FightField::dragonRun,this,"player"));
        auto block = CallFunc::create(CC_CALLBACK_0(FightField::startFight,this));
        this->player->fDragon->dragonSprite->runAction(Sequence::create(run,block, NULL));
    }
}
