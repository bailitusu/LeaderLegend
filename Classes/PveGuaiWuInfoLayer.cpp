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
    return true;
}

void PveGuaiWuInfoLayer::initPveGuaiWuLayer() {
    this->background = Sprite::create("matchBg.jpg");
    CommonFunc::setShowAllSpriteSize(this->background, this->getBoundingBox().size.width, this->getBoundingBox().size.height);
    this->background->setPosition(Vec2(this->getBoundingBox().size.width/2, this->getBoundingBox().size.height/2));
    this->background->setLocalZOrder(-100);
    this->addChild(background);
    
    this->imageSp = Sprite::create("bbg_arena.png");
    CommonFunc::setShowAllSpriteSize(this->imageSp, this->getBoundingBox().size.width/3, this->getBoundingBox().size.width/3);
    this->imageSp->setPosition(Vec2(this->imageSp->getBoundingBox().size.width/2+20, this->getBoundingBox().size.height-this->imageSp->getBoundingBox().size.height/2-20));
    this->addChild(this->imageSp,100);
    
    this->textLabel = Label::createWithTTF("ssssss", "fonts/kaiti.ttf", 18);
    this->textLabel->setDimensions(this->getBoundingBox().size.width-this->getBoundingBox().size.width/3-60, this->getBoundingBox().size.width/3+10);
    this->textLabel->setLineBreakWithoutSpace(true);
    this->textLabel->setPosition(Vec2(this->textLabel->getDimensions().width/2+this->getBoundingBox().size.width/3+40, this->getBoundingBox().size.height-this->textLabel->getDimensions().height/2-20));
    this->addChild(this->textLabel,100);
    
    for (int i = 0; i < 3; i++) {
        Sprite* defenSp = Sprite::create("defenBg.png");
        CommonFunc::setSpriteSize(defenSp, this->getBoundingBox().size.width/9);
        defenSp->setPosition(this->getBoundingBox().size.width/4*(i+1),this->getBoundingBox().size.height*0.3);
        this->addChild(defenSp,100);
        this->deFenSpArray.pushBack(defenSp);
    }
    
    
    this->startBtn = ui::Button::create("classbtn.png");
    CommonFunc::initButton(this->startBtn, CC_CALLBACK_2(PveGuaiWuInfoLayer::startBtnClick, this), this->getBoundingBox().size.width/7, Vec2(this->getBoundingBox().size.width/2, 30));
    this->startBtn->setTitleText("攻打此城");
    this->startBtn->setTitleColor(Color3B(255, 255, 255));
    this->addChild(this->startBtn,100);
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



