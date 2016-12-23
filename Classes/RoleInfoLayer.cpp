//
//  RoleInfoLayer.cpp
//  OctMountain
//
//  Created by zc on 16/11/22.
//
//

#include "RoleInfoLayer.h"
#include "CommonFunc.h"
#include "Setting.h"
bool RoleInfoLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

void RoleInfoLayer::initRoleInfoLayer() {
//    this->goldBtn = ui::Button::create("buy1.png");
//    this->goldBtn->setScale(22/this->goldBtn->getBoundingBox().size.width);
//    this->goldBtn->setPressedActionEnabled(true);
//    this->goldBtn->addTouchEventListener(CC_CALLBACK_2(RoleInfoLayer::goldClick, this));
//    this->addChild(this->goldBtn,150);
    this->goldNumLabel =this->creatOneInfo("qian.png", this->goldBtn, Vec2(55,this->getBoundingBox().size.height/2));
    
//    this->tiLiBtn = ui::Button::create("buy1.png");
//    this->tiLiBtn->setScale(22/this->tiLiBtn->getBoundingBox().size.width);
//    this->tiLiBtn->setPressedActionEnabled(true);
//    this->tiLiBtn->addTouchEventListener(CC_CALLBACK_2(RoleInfoLayer::tiLiClick, this));
//    this->addChild(this->tiLiBtn,150);
    this->tiLiLabel = this->creatOneInfo("zuanshi.png", this->tiLiBtn, Vec2(this->goldNumLabel->getPosition().x+110+10, this->getBoundingBox().size.height/2));
    //this->tiLiLabel = this->creatOneInfo("tilibao.png", this->tiLiBtn, Vec2(55,this->getBoundingBox().size.height/2+30));
    
//    this->zuanShiBtn = ui::Button::create("buy1.png");
//    this->zuanShiBtn->setScale(22/this->zuanShiBtn->getBoundingBox().size.width);
//    this->zuanShiBtn->setPressedActionEnabled(true);
//    this->zuanShiBtn->addTouchEventListener(CC_CALLBACK_2(RoleInfoLayer::zuanShiClick, this));
//    this->addChild(this->zuanShiBtn,150);
//   // this->zuanShiNumLabel = this->creatOneInfo("baoshi.png", this->zuanShiBtn, Vec2(this->tiLiLabel->getPosition().x+110+10, this->getBoundingBox().size.height/2));
//    this->zuanShiNumLabel = this->creatOneInfo("baoshi.png", this->zuanShiBtn,  Vec2(55,this->getBoundingBox().size.height/2+60));
    
    
}

Label* RoleInfoLayer::creatOneInfo(std::string infoImage, ui::Button *btn, Vec2 bgPoint) {
    Sprite* bgSp = Sprite::create("infoBg.png");
    CommonFunc::setShowAllSpriteSize(bgSp, 90, 20);
    bgSp->setPosition(bgPoint);
    this->addChild(bgSp,100);
    
    auto infoLabel = Label::createWithTTF("1万", "fonts/kaiti.ttf", 14);
    infoLabel->setDimensions(80, 20);
    infoLabel->setPosition(Vec2(bgPoint.x, bgPoint.y-3));
    infoLabel->setAlignment(TextHAlignment::CENTER);
    infoLabel->setTextColor(Color4B(255, 255, 255, 255));
    this->addChild(infoLabel,150);
    
    Sprite* infoSp = Sprite::create(infoImage);
    CommonFunc::setShowAllSpriteSize(infoSp, 30,30);//22 22
    infoSp->setPosition(bgPoint.x-bgSp->getBoundingBox().size.width/2+5,bgPoint.y+3);
    this->addChild(infoSp,150);
    
   // btn->setPosition(Vec2(bgPoint.x+bgSp->getBoundingBox().size.width/2-5,bgPoint.y));
    return infoLabel;
}

void RoleInfoLayer::goldClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    
}

void RoleInfoLayer::tiLiClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {

}

void RoleInfoLayer::zuanShiClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    
}
