//
//  FightProgress.cpp
//  OctLegend
//
//  Created by zc on 16/8/17.
//
//

#include "FightProgress.h"
#include "CommonFunc.h"
#include "Setting.h"
bool FightProgress::init() {
    hpPro = ProgressTimer::create(Sprite::create("xuetiaoBg.png"));
    hpPro->setType(ProgressTimer::Type::BAR);
    hpPro->setMidpoint(Vec2(1, 0));
    hpPro->setBarChangeRate(Vec2(1, 0));
    //hpPro->setPosition(Vec2(0, 0));
    hpPro->setAnchorPoint(Vec2(0.5, 0));
    hpPro->setPercentage(0);
    Rect spRect = hpPro->getBoundingBox();
   // hpPro->setScale(screenSize.width*0.06/spRect.size.width);
    hpPro->setScale(46/spRect.size.width, 4/spRect.size.height);
    
    
    hpProBg = Sprite::create("xuetiao.png");
   // hpProBg->addChild(hpPro,51);
    hpProBg->setAnchorPoint(Vec2(0.5, 0));
    CommonFunc::setShowAllSpriteSize(hpProBg, 40, 3);
   // CommonFunc::setSpriteSize(hpProBg, screenSize.width*0.06);
    return true;
}

void FightProgress::initNuQiPro(float precent) {
    nuqiPro = ProgressTimer::create(Sprite::create("qitiao.png"));
    nuqiPro->setType(ProgressTimer::Type::BAR);
    nuqiPro->setMidpoint(Vec2(0, 0));
    nuqiPro->setBarChangeRate(Vec2(1, 0));
    nuqiPro->setAnchorPoint(Vec2(0.5, 0));
    nuqiPro->setPercentage(precent);
    Rect spRect = nuqiPro->getBoundingBox();
   // nuqiPro->setScale(screenSize.width*0.06/spRect.size.width);
    nuqiPro->setScale(40/spRect.size.width, 3/spRect.size.height);
    
    nuqiProBg = Sprite::create("qitiaoBg.png");
    nuqiProBg->setAnchorPoint(Vec2(0.5, 0));
  //  CommonFunc::setSpriteSize(nuqiProBg, screenSize.width*0.06);
    CommonFunc::setShowAllSpriteSize(nuqiProBg, 43, 5);
}

void FightProgress::setNuQiProPrecent(float precent) {
    nuqiPro->setPercentage(precent);
}







