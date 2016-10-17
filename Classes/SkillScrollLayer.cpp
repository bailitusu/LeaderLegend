//
//  SkillScrollLayer.cpp
//  OctLegend
//
//  Created by zc on 16/10/13.
//
//

#include "SkillScrollLayer.h"
#include "CommonFunc.h"
#include "LingShoLayer.h"
bool SkillScrollLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    return true;
}


void SkillScrollLayer::initSkillScrollLayer() {
    Sprite* background = Sprite::create("allSkillBg.jpg");
   // CommonFunc::setSpriteSize(background, this->getBoundingBox().size.width);
    CommonFunc::setShowAllSpriteSize(background, this->getBoundingBox().size.width, this->getBoundingBox().size.height);
    background->setPosition(this->getBoundingBox().size.width/2,this->getBoundingBox().size.height/2);
    this->addChild(background,-100);
    
    continerLayer = Layer::create();
    continerLayer->setContentSize(Size(this->getBoundingBox().size.width-20, this->getBoundingBox().size.height*2));
    continerLayer->setPosition(8,-this->getBoundingBox().size.height-55);
    
    auto scrollView = extension::ScrollView::create();
    scrollView->setViewSize(Size(this->getBoundingBox().size.width-20,this->getBoundingBox().size.height-55));
    scrollView->setPosition(8,10);
    scrollView->setContainer(continerLayer);
    scrollView->setDirection(extension::ScrollView::Direction::VERTICAL);
    scrollView->setDelegate(this);
    scrollView->getTouchListener()->setSwallowTouches(false);
    this->addChild(scrollView,0);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto liston = EventListenerTouchOneByOne::create();
    liston->onTouchBegan = CC_CALLBACK_2(SkillScrollLayer::onTouchBegan, this);
    liston->onTouchMoved = CC_CALLBACK_2(SkillScrollLayer::onTouchMoved, this);
    liston->onTouchEnded = CC_CALLBACK_2(SkillScrollLayer::onTouchEnded, this);
  //  liston->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(liston, this);
}

bool SkillScrollLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
   // ((LingShoLayer*)this->getParent())->onTouchBegan(touch, unused_event);
    this->isMoved = false;
    return true;
}

void SkillScrollLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    this->isMoved = true;
}

void SkillScrollLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
}

void SkillScrollLayer::scrollViewDidScroll(extension::ScrollView *view) {
    return;
}

void SkillScrollLayer::scrollViewDidZoom(extension::ScrollView *view) {
    return;
}
