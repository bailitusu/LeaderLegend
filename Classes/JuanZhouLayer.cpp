//
//  JuanZhouLayer.cpp
//  OctLegend
//
//  Created by zc on 16/10/22.
//
//

#include "JuanZhouLayer.h"
#include "SetRoleFormatLayer.h"
#include "CommonFunc.h"
#include "Setting.h"
bool JuanZhouLayer::init() {
    return true;
}

void JuanZhouLayer::initJuanZhou() {
    
    this->backgroundSp = Sprite::create("juanzhouBg.jpg");
    CommonFunc::setShowAllSpriteSize(this->backgroundSp,this->getBoundingBox().size.width, this->getBoundingBox().size.height);
    this->backgroundSp->setAnchorPoint(Vec2(0, 0));
    this->backgroundSp->setPosition(0,0);
    this->addChild(this->backgroundSp, -100);
    this->initRole();
    
//    this->srollView = ScrollView::create();
//    this->continerLayer = Layer::create();
}

void JuanZhouLayer::initRole() {
    
    auto scaleX = this->backgroundSp->getScaleX();
    auto scaleY = this->backgroundSp->getScaleY();
    for (int i = 0; i < this->psRoleData.size(); i++) {
        this->psRoleData.at(i)->xiaoSp = Sprite::create(this->psRoleData.at(i)->xiaoImageName);
        CommonFunc::setShowAllSpriteSize(this->psRoleData.at(i)->xiaoSp, this->getBoundingBox().size.height*0.7/scaleX, this->getBoundingBox().size.height*0.7/scaleY);
    //    printf("%f",this->psRoleData.at(i)->xiaoSp->getBoundingBox().size.width);
       // CommonFunc::setSpriteSize(this->psRoleData.at(i)->xiaoSp, );
        this->psRoleData.at(i)->xiaoSp->setPosition(Vec2( (this->getBoundingBox().size.width*0.0133+this->psRoleData.at(i)->xiaoSp->getBoundingBox().size.width/2+(this->getBoundingBox().size.width*0.00833+this->psRoleData.at(i)->xiaoSp->getBoundingBox().size.width)*i), this->getBoundingBox().size.height/2/scaleY));
        this->backgroundSp->addChild(this->psRoleData.at(i)->xiaoSp,100);
    }
}
