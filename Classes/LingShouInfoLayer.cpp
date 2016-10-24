//
//  LingShouInfoLayer.cpp
//  OctLegend
//
//  Created by zc on 16/10/21.
//
//

#include "LingShouInfoLayer.h"
#include "CommonFunc.h"
#include "Setting.h"
#include "DragonSkill.h"
bool LingShouInfoLayer::init() {
    return true;
}

void LingShouInfoLayer::initLingShouInfoLayer() {
    Sprite* background = Sprite::create("lingshouinfo.jpg");
    CommonFunc::setShowAllSpriteSize(background, this->getBoundingBox().size.width, this->getBoundingBox().size.height);
    this->addChild(background, -100);
    
    this->dragonNameLabel = CommonFunc::createLabel(this->dSkill->dargonName, Vec2(0, 0));//该layer的猫点在0.5，0.5
    this->dragonNameLabel->setTextColor(Color4B(255, 255, 255, 255));
    this->addChild(this->dragonNameLabel,100);
}
