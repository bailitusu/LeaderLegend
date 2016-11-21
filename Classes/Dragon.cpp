//
//  Dragon.cpp
//  OctLegend
//
//  Created by zc on 16/8/29.
//
//

#include "Dragon.h"
#include "FightPlayer.h"
#include "RecordFight.h"
#include "ReadRecordFight.h"
#include "HuiMieBoDong.h"
#include "ActionWait.h"
#include "AllArmyGuWu.h"
#include "CommonFunc.h"
#include "Setting.h"
bool Dragon::init() {
    this->currentIndex = 0;
    return true;
}

void Dragon::runNextDragonSkill(FightPlayer* player) {
    if (this->currentIndex >= this->dragonSkillArray.size()) {
        this->dragonSkillArray.clear();
        return;
    }
    auto record = OneRecord::create();
    record->dragonSkillName = this->dragonSkillArray.at(this->currentIndex)->dargonName;
    record->playerName = player->fpName;
    RecordFight::GetInstance()->addDragonItemToRecord(record);
    RecordFight::GetInstance()->currentRecordIndex++;
  //  this->dragonSkillArray.at(this->currentIndex)->runSkill(player);
    this->currentIndex++;
}

void Dragon::addDragonSkill(DragonSkill *skill,int index) {
    this->dragonSkillArray.insert(index, skill);
}

void Dragon::runDragonAnimation(DragonData* dragonData,FightPlayer* player) {
    

    auto wait = ActionWait::create(1.0);
    auto apper = FadeTo::create(0.5, 255);
    auto disapper = FadeTo::create(0.5, 0);
    auto run = CallFunc::create(CC_CALLBACK_0(Dragon::dragonAnimationBlock, this,dragonData,player));


    auto block = CallFunc::create(CC_CALLBACK_0(Dragon::runBlock, this,dragonData));
    this->dragonSprite->runAction(Sequence::create(apper,disapper,run,wait,block,NULL));
}

void Dragon::runBlock(DragonData* dragonData) {
    dragonData->release();
    this->readRecordFight->readNextDragon();
}

void Dragon::dragonAnimationBlock(DragonData* dragonData, FightPlayer *player) {
    std::string dragonSkillName = dragonData->dragonSkillName;
    if (dragonSkillName.compare("huimiebodong") == 0) {
        HuiMieBoDong* huimie = HuiMieBoDong::create();
        huimie->runSkillAnimation(this->dragonSprite,player,dragonData);
        huimie->retain();
       // huimie->runSkill(player,dragonData);

    }else if(dragonSkillName.compare("quanjunguwu") == 0) {
        AllArmyGuWu* allGuWu = AllArmyGuWu::create();
        allGuWu->runSkill(player, dragonData);
    }
}

void Dragon::initDragonShuXing() {
    this->bingLi = 89;
//    this->mianBao = 10;
//    this->baoJi = 10;
    this->minJie = 27;
    this->fangYu = 50;
    this->gongJi = 88;
    this->faLI = 86;
}
