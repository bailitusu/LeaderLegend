//
//  LoadingLayer.cpp
//  OctMountain
//
//  Created by zc on 16/11/21.
//
//

#include "LoadingLayer.h"
#include "Setting.h"
#include "CommonFunc.h"
#include "ActionWait.h"
LoadingLayer* LoadingLayer::loadingLayer = NULL;

LoadingLayer* LoadingLayer::GetInstance() {
    if (loadingLayer == NULL) {
        loadingLayer = LoadingLayer::create();
        loadingLayer->retain();
        return loadingLayer;
    }
    return loadingLayer;
}

bool LoadingLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    this->haveLoadNum = 0;
    this->totalNum = 10;
    return true;
}

void LoadingLayer::initLoadLayer() {
    this->nextScene->retain();
    this->loadSpBg = Sprite::create("loading_bar_bg.png");
    this->loadSpBg->setScale(2);
    this->loadSpBg->setPosition(screenSize.width/2,20);
    this->addChild(this->loadSpBg,100);
    
    this->loadBar = ProgressTimer::create(Sprite::create("loading_bar.png"));
    this->loadBar->setScale(2);
    this->loadBar->setPosition(this->loadSpBg->getPosition());
    this->loadBar->setPercentage(0);
    this->loadBar->setType(ProgressTimer::Type::BAR);
    this->loadBar->setBarChangeRate(Vec2(1,0));
    this->loadBar->setMidpoint(Vec2(0, 0));
    this->addChild(this->loadBar,150);
    
    Sprite* background = Sprite::create("guochangBg.jpg");//loadlayerBg.jpg
   // CommonFunc::setShowAllSpriteSize(background, screenSize.width, screenSize.height);
     CommonFunc::setSpriteSize(background, screenSize.width);
    background->setPosition(screenSize.width/2,screenSize.height/2);
    this->addChild(background,-100);
    
    auto wait = ActionWait::create(0.5);
    auto block = CallFunc::create(CC_CALLBACK_0(LoadingLayer::progressBlock, this,this->pushType));
    this->loadBar->runAction(Sequence::create(ProgressTo::create(0.5, 70),wait,ProgressTo::create(1, 100),block,NULL));
   
}

Scene* LoadingLayer::CreateScene() {
    Scene* scene = Scene::create();
    return scene;
}

void LoadingLayer::progressBlock(std::string type) {
    
    if (type.compare("push") == 0) {
        Director::getInstance()->pushScene(this->nextScene);
    }else if(type.compare("replace") == 0) {
        Director::getInstance()->replaceScene(this->nextScene);
    }
    this->nextScene->release();
    this->loadBar->setPercentage(0);
}

void LoadingLayer::loading(std::string imageName) {
   // Director::getInstance()->getTextureCache()->addImageAsync(imageName, CC_CALLBACK_1(LoadingLayer::loadedCallBack, this));
    this->haveLoadNum++;
    
}

void LoadingLayer::loadedCallBack(cocos2d::Texture2D *texture) {
    float temp = ((float)this->haveLoadNum / this->totalNum)*100;
    this->loadBar->setPercentage(temp);
    if (this->haveLoadNum >= 10) {
        
    }
}
