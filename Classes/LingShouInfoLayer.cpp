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
    Sprite* background = Sprite::create("dragonSkillInfoBg.jpg");
    CommonFunc::setShowAllSpriteSize(background, this->getBoundingBox().size.width, this->getBoundingBox().size.height);
    background->setOpacity(220);
    this->addChild(background, -100);
    
    this->dragonNameLabel = CommonFunc::createLabel(this->dSkill->dargonInfoName, Vec2(-30, 20));//该layer的猫点在0.5，0.5
    this->dragonNameLabel->setTextColor(dragonSkillInfoColor);
    this->addChild(this->dragonNameLabel,100);
    
    this->skillSp = Sprite::create(this->skillImageName);
    CommonFunc::setShowAllSpriteSize(this->skillSp, this->getBoundingBox().size.width/5, this->getBoundingBox().size.width/5);
    this->skillSp->setPosition(Vec2(-this->getBoundingBox().size.width/2+this->skillSp->getBoundingBox().size.width/2+15, 2));
    this->addChild(this->skillSp,100);
    
    
}
