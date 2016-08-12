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
bool HuangDiCard::init() {
    cardSprite = Sprite::create("long.png");
    cardSprite->setAnchorPoint(Vec2(0.5, 0));
    // player->setFlippedX(true);
    CommonFunc::setSpriteSize(cardSprite, screenSize.width*0.075);
    return true;
}

void HuangDiCard::didBeHit(int hitValue) {
  //  log("huangdi hart %d",hitValue);
    std::cout << "huangdi hart" << hitValue << std::endl;
}