//
//  ZheZhaoLayer.cpp
//  OctMountain
//
//  Created by zc on 16/12/22.
//
//

#include "ZheZhaoLayer.h"
#include "Setting.h"
#include "CommonFunc.h"
Scene* ZheZhaoLayer::createScene() {
    Scene* scene = Scene::create();
    //    FuBenLayer* layer = FuBenLayer::create();
    //    scene->addChild(layer);
    return scene;
}

bool ZheZhaoLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

void ZheZhaoLayer::initThisLayer() {
//    Sprite* ba = Sprite::create("mengheiBg.png");
//    CommonFunc::setShowAllSpriteSize(ba, screenSize.width, screenSize.height);
//    ba->setPosition(screenSize.width/2,screenSize.height/2);
//    this->addChild(ba,100);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto liston = EventListenerTouchOneByOne::create();
    liston->onTouchBegan = CC_CALLBACK_2(ZheZhaoLayer::onTouchBegan, this);
    liston->onTouchMoved = CC_CALLBACK_2(ZheZhaoLayer::onTouchMoved, this);
    liston->onTouchEnded = CC_CALLBACK_2(ZheZhaoLayer::onTouchEnded, this);
     liston->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(liston, this);
}

bool ZheZhaoLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
    return true;
}

void ZheZhaoLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {

    
}

void ZheZhaoLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
}
