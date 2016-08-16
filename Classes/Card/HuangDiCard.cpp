//
//  HuangDiCard.cpp
//  OctLegend
//
//  Created by zc on 16/8/12.
//
//

#include "HuangDiCard.h"
#include "CommonFunc.h"
#include "Setting.h"
#include <iostream>
#include <stdlib.h>
#include "string.h"
bool HuangDiCard::init() {
    HP = 15;
    return true;
}

void HuangDiCard::initCardSprite(std::string imageName) {
    cardSprite = Sprite::create(imageName);
    cardSprite->setAnchorPoint(Vec2(0.5, 0));
    // player->setFlippedX(true);
    CommonFunc::setSpriteSize(cardSprite, screenSize.width*0.075);
}

void HuangDiCard::didBeHit(int hitValue) {
  //  log("huangdi hart %d",hitValue);
    std::cout << "huangdi hart" << hitValue << std::endl;
}



void HuangDiCard::runAnimation() {
    

    
    auto animation = Animation::create();
    for (int i = 0; i < 14; i++) {
        std::ostringstream stringFarmat;
        stringFarmat << "huangdi_walk_up" << i << ".png";
        std::string szName = stringFarmat.str();
//        szName.initWithFormat("huangdi_walk_up%d.png", i);
       // sprintf(szName, "huangdi_walk_up%d.png", i);
        animation->addSpriteFrameWithFile(szName);
    }
    animation->setDelayPerUnit(2.0f/13);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(1);
    auto animateAction = Animate::create(animation);
    
    
    
    this->cardSprite->runAction(Sequence::create(animateAction, CallFunc::create(CC_CALLBACK_0(HuangDiCard::actionBlock,this)), NULL));

    

}

void HuangDiCard::actionBlock() {
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    if (playerName.compare("player") == 0) {
        EventCustom event = EventCustom("enemyPlayerNextRun");
        //event.setUserData((void*)123);
        dispatcher->dispatchEvent(&event);
    }else if (playerName.compare("enemyPlayer") == 0) {
        EventCustom event = EventCustom("playerNextRun");
        //event.setUserData((void*)123);
        dispatcher->dispatchEvent(&event);
    }
}

void HuangDiCard::getMsg(Ref* sender) {
    
}



