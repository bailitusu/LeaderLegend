//
//  PveGuaiWuInfoLayer.cpp
//  OctLegend
//
//  Created by zc on 16/11/8.
//
//

#include "PveGuaiWuInfoLayer.h"
#include "Setting.h"
#include "CommonFunc.h"
#include "PveGuaiWu.h"
#include "PveFightLayer.h"
bool PveGuaiWuInfoLayer::init() {
//    if (!LayerColor::initWithColor(Color4B(25, 25, 25, 255)) ) {
//        return false;
//    }
    return true;
}

void PveGuaiWuInfoLayer::initPveGuaiWuLayer() {
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto liston = EventListenerTouchOneByOne::create();
    liston->onTouchBegan = CC_CALLBACK_2(PveGuaiWuInfoLayer::onTouchBegan, this);
    liston->onTouchMoved = CC_CALLBACK_2(PveGuaiWuInfoLayer::onTouchMoved, this);
    liston->onTouchEnded = CC_CALLBACK_2(PveGuaiWuInfoLayer::onTouchEnded, this);
     liston->setSwallowTouches(false);
    dispatcher->addEventListenerWithSceneGraphPriority(liston, this);

    Sprite* mengHeiSp = Sprite::create("mengheiBg.png");
    CommonFunc::setShowAllSpriteSize(mengHeiSp, this->getBoundingBox().size.width, this->getBoundingBox().size.height);
    mengHeiSp->setPosition(this->getBoundingBox().size.width/2,this->getBoundingBox().size.height/2);
    mengHeiSp->setOpacity(215);
    this->addChild(mengHeiSp, -200);
    this->background = Sprite::create("pveInfoBg.png");
    CommonFunc::setShowAllSpriteSize(this->background, 521.6, 320);
    this->background->setPosition(Vec2(this->getBoundingBox().size.width/2, this->getBoundingBox().size.height/2));
    this->background->setLocalZOrder(-100);
    this->addChild(background);
    
//    this->imageSp = Sprite::create("bbg_arena.png");
//    CommonFunc::setShowAllSpriteSize(this->imageSp, this->getBoundingBox().size.width/3, this->getBoundingBox().size.width/3);
//    this->imageSp->setPosition(Vec2(this->imageSp->getBoundingBox().size.width/2+20, this->getBoundingBox().size.height-this->imageSp->getBoundingBox().size.height/2-20));
//    this->addChild(this->imageSp,100);
    auto bgScaleX = this->background->getScaleX();
    auto bgScaleY = this->background->getScaleY();
    this->textLabel = Label::createWithTTF("天色已晚，你正在搭建好的帐篷里睡觉，迷迷糊糊地听到有人在喊什么。祭坛？", "fonts/hanyixuejunti.ttf", 18);
    this->textLabel->setDimensions((this->background->getBoundingBox().size.width-80)/bgScaleX, this->background->getBoundingBox().size.height/3/bgScaleY);
    this->textLabel->setLineBreakWithoutSpace(true);
    this->textLabel->setPosition(Vec2(this->background->getBoundingBox().size.width/2/bgScaleX, this->background->getBoundingBox().size.height/2/bgScaleY));
    this->background->addChild(this->textLabel,100);
    
    char tempGuanKaNum[20] = {0};
    sprintf(tempGuanKaNum, "第%d关",this->index);
    this->guanKaLabel = Label::createWithTTF(tempGuanKaNum, "fonts/kaiti.ttf", 16);
    this->guanKaLabel->setDimensions(70/bgScaleX, 20/bgScaleY);
    this->guanKaLabel->setAlignment(TextHAlignment::CENTER);
    this->guanKaLabel->setPosition(70/bgScaleX,(this->background->getBoundingBox().size.height-40)/bgScaleY);
    this->guanKaLabel->enableBold();
    this->background->addChild(this->guanKaLabel, 200);

    
    
    this->startBtn = ui::Button::create("gongdacicheng.png");
    CommonFunc::initButton(this->startBtn, CC_CALLBACK_2(PveGuaiWuInfoLayer::startBtnClick, this), this->background->getBoundingBox().size.width/7/bgScaleX, Vec2(this->background->getBoundingBox().size.width/2/bgScaleX, 50/bgScaleY));
   // this->startBtn->setTitleText("攻打此城");
    this->startBtn->setTitleColor(Color3B(255, 255, 255));
    this->background->addChild(this->startBtn,100);
//    this->richText = ui::RichText::create();
//    this->richText->ignoreContentAdaptWithSize(true);
//    this->richText->setContentSize(Size(this->getBoundingBox().size.width-20, this->getBoundingBox().size.height-20));
//    this->richText->setPosition(Vec2(this->getBoundingBox().size.width/2, this->getBoundingBox().size.height/2));
//    this->addChild(this->richText,100);
//    
//    ui::RichElementText* reText = ui::RichElementText::create(1, Color3B::BLACK, 255, "jsdasdkahkdjhasjkhdanbcmdsnbfjkahfkjashfkjhjdhfhkajshkfdjashfkjahfksdjhfkdjshfdshbjskhadjhashdkasj", "fonts/楷体.ttf", 18);
//    
//    ui::RichElementImage* reImage = ui::RichElementImage::create(2, Color3B::WHITE, 255, "bbg_arena.png");
//    reImage->setWidth(this->getBoundingBox().size.width/3);
//    reImage->setHeight(this->getBoundingBox().size.width/3);
//    this->richText->pushBackElement(reImage);
//    this->richText->pushBackElement(reText);
}

void PveGuaiWuInfoLayer::startBtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        auto nextScene = PveFightLayer::createScene();
        this->pveLayer = PveFightLayer::create();
        this->pveLayer->setContentSize(screenSize);
        nextScene->addChild(this->pveLayer);
        this->pveLayer->setPosition(Vec2(screenSize.width/2-this->pveLayer->getBoundingBox().size.width/2, screenSize.height/2-this->pveLayer->getBoundingBox().size.height/2));
        // this->roleFormatLayer->setPosition(0,0);
        // this->pveLayer->preLayerName = "fuben";
        
        //            for (int i = 0; i < this->myData->size(); i++) {
        //                this->pveLayer->roleData.pushBack(this->myData->at(i));
        //            }
        
        for (int j = 0; j < this->guaiWuData->size(); j++) {
            this->pveLayer->enemyRoleData.pushBack(this->guaiWuData->at(j));
        }
        this->pveLayer->guaiWuID = this->index;
        this->pveLayer->initPveLayer();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0, nextScene));
    }
    
}

bool PveGuaiWuInfoLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    auto point = Director::getInstance()->convertToGL(touch->getLocationInView());
    auto rect = Rect(this->background->getPosition().x-this->background->getBoundingBox().size.width/2, this->background->getPosition().y-this->background->getBoundingBox().size.height/2, this->background->getBoundingBox().size.width, this->background->getBoundingBox().size.height);
    if (!rect.containsPoint(point)) {
        auto parentLayer = this->getParent();
        this->removeFromParentAndCleanup(true);
        parentLayer->removeFromParentAndCleanup(true);
    }
    return true;
}

void PveGuaiWuInfoLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
}

void PveGuaiWuInfoLayer::onTouchEnded(Touch *touch, Event *unused_event) {
    
}
