//
//  HuiMieBoDong.cpp
//  OctLegend
//
//  Created by zc on 16/8/29.
//
//

#include "HuiMieBoDong.h"
#include "FightPlayer.h"
#include "Card.h"
#include "CommonFunc.h"
#include "Setting.h"
bool HuiMieBoDong::init() {
    this->skillLevel = 9;
    this->dargonName = "huimiebodong";
    this->dargonInfoName = "毁灭波动";
    return true;
}

void HuiMieBoDong::runSkill(FightPlayer* player, DragonData* data) {
//    for (int i = 0 ; i < player->enemy->fMap->mapCellArray.size(); i++) {
//        if (player->enemy->fMap->mapCellArray.at(i)->obj != NULL) {
//            ((Card*)player->enemy->fMap->mapCellArray.at(i)->obj)->decreaseHP(((Card*)player->enemy->fMap->mapCellArray.at(i)->obj), this->skillLevel*200);
//        }
//    }
    for (int i = 0; i < data->dragonAffectArray.size(); i++) {
        Card* affectCard;
        if (data->dragonAffectArray.at(i)->playerName.compare(player->fpName) == 0) {
            affectCard = ((Card*)player->fMap->mapCellArray.at(data->dragonAffectArray.at(i)->standIndex)->obj);
            affectCard->MaxHP = data->dragonAffectArray.at(i)->maxHP;
            affectCard->hpAppear(affectCard, data->dragonAffectArray.at(i)->hitValue, data->dragonAffectArray.at(i)->currentHP);
        }else {
            affectCard = ((Card*)player->enemy->fMap->mapCellArray.at(data->dragonAffectArray.at(i)->standIndex)->obj);
            affectCard->MaxHP = data->dragonAffectArray.at(i)->maxHP;
            affectCard->hpAppear(affectCard, data->dragonAffectArray.at(i)->hitValue, data->dragonAffectArray.at(i)->currentHP);
        }
    }
    this->release();
    
}

void HuiMieBoDong::runSkillAnimation(cocos2d::Sprite *sprite,FightPlayer* player, DragonData* data) {
    
    
    Sprite* huimieSp = Sprite::create("huimiebodong_0.png");
    CommonFunc::setSpriteSize(huimieSp, 200);
    // huimieSp->setAnchorPoint(Vec2(1, 0));
    auto positon = Vec2(player->enemy->fMap->getPosition().x+player->enemy->fMap->getBoundingBox().size.width/2, player->enemy->fMap->getPosition().y+player->fMap->getBoundingBox().size.height/2);
    auto moveTo = MoveTo::create(1.0, positon);
    auto huimiebodong = CommonFunc::creatAnimation("huimiebodong_%d.png", 18, 1, 0);
    auto overBlock = CallFunc::create(CC_CALLBACK_0(HuiMieBoDong::animationOver, this,huimieSp,player,data));
    huimieSp->setPosition(screenSize.width/2, 300);
    sprite->getParent()->addChild(huimieSp,300);
    
    huimieSp->runAction(Sequence::create(Spawn::create(moveTo,huimiebodong,NULL),overBlock, NULL) );
}


void HuiMieBoDong::animationOver(cocos2d::Sprite *sprite, FightPlayer *player, DragonData *data) {
    sprite->removeFromParentAndCleanup(true);
    CommonFunc::removeAnimation();
    this->runSkill(player, data);
}
