//
//  GongGaoLayer.cpp
//  OctMountain
//
//  Created by zc on 16/11/22.
//
//

#include "GongGaoLayer.h"
#include "Setting.h"
#include "CommonFunc.h"
#include "RegisterLayer.h"
bool GongGaoLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    Sprite* background = Sprite::create("gonggaoBg.png");
    CommonFunc::setShowAllSpriteSize(background, screenSize.width, screenSize.height);
    background->setPosition(screenSize.width/2,screenSize.height/2);
    this->addChild(background,-100);
    scheduleOnce(schedule_selector(GongGaoLayer::enterNextScene), 1.5);
    return true;
}

Scene* GongGaoLayer::createScene() {
    Scene* scene = Scene::create();
    GongGaoLayer* layer = GongGaoLayer::create();
    scene->addChild(layer);
    
    return scene;
}

void GongGaoLayer::enterNextScene(float dur) {
    Scene* scene = RegisterLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
}
