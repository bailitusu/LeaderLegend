//
//  FuBenLayer.cpp
//  OctLegend
//
//  Created by zc on 16/9/28.
//
//

#include "FuBenLayer.h"
#include "CommonFunc.h"
#include "Setting.h"
#include "HuangDiCard.h"
#include "HouYiCard.h"
#include "ChangECard.h"
#include "TaoTieCard.h"
#include "XingTianCard.h"
#include "XuanWuCard.h"
#include "FengBoCard.h"
#include "FengHouCard.h"
#include "SuanYuCard.h"

#include "DunJiaTianShu.h"
Scene* FuBenLayer::createScene() {
    Scene* scene = Scene::create();
//    FuBenLayer* layer = FuBenLayer::create();
//    scene->addChild(layer);
    return scene;
}

bool FuBenLayer::init() {
    return true;
}

//void FuBenLayer::onExit() {
//    Layer::onExit();
//}

void FuBenLayer::initFuBenLayer() {
    auto background = Sprite::create("yaosai.jpg");
    CommonFunc::setSpriteSize(background, screenSize.width);
    background->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height/2+origin.y));
    background->setLocalZOrder(-100);
    this->addChild(background);
    
    this->backBtnUI();
    
    this->enemyOne = ui::Button::create("shushi.png");
    CommonFunc::initButton(this->enemyOne, CC_CALLBACK_2(FuBenLayer::enemyOneBtn, this), screenSize.width/3, Vec2(screenSize.width/10*7, screenSize.height/2));
    this->addChild(this->enemyOne,50);
    this->readEnemyData();
    
}

void FuBenLayer::backBtnUI() {
    
    ui::Button *btn = ui::Button::create("CloseNormal.png");
    btn = CommonFunc::initButton(btn,CC_CALLBACK_2(FuBenLayer::backBtn, this) , screenSize.width*0.05, Vec2(screenSize.width*0.96, screenSize.height*0.92));
    this->addChild(btn,200);
}

void FuBenLayer::backBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {

        Director::getInstance()->popScene();
   
}


void FuBenLayer::enemyOneBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType typr) {
    
    
    this->roleFormatLayer = SetRoleFormatlayer::create();
    this->roleFormatLayer->setContentSize(screenSize/5*4);
    this->addChild(this->roleFormatLayer,100);
    this->roleFormatLayer->setPosition(Vec2(screenSize.width/2-this->roleFormatLayer->getBoundingBox().size.width/2, screenSize.height/2-this->roleFormatLayer->getBoundingBox().size.height/2));
   // this->roleFormatLayer->setPosition(0,0);
    this->roleFormatLayer->preLayerName = "fuben";
    
    for (int i = 0; i < this->myRoleData.size(); i++) {
        this->roleFormatLayer->roleData.pushBack(this->myRoleData.at(i));
    }
    
    for (int j = 0; j < this->enemyRoleData.size(); j++) {
        this->roleFormatLayer->enemyRoleData.pushBack(this->enemyRoleData.at(j));
    }
    this->roleFormatLayer->initSetRoleFormatLayer();
}

void FuBenLayer::cardFormatEnemy(Card* card,std::string imageName, int standIndex,Treasure* treasure) {
    card->initCardSprite(imageName);
    //  this->player->setCardsPositon(card, standIndex,50);
    card->retain();
    
    auto pveData = SetRoleData::create();
    pveData->imageName = imageName;
    pveData->cellIndex = standIndex;
    pveData->magicGoods = treasure;
    pveData->magicGoods->retain();
    pveData->card = card;
    pveData->noBring = false;
    this->enemyRoleData.pushBack(pveData);
}

void FuBenLayer::readEnemyData() {
    this->cardFormatEnemy(HouYiCard::create(),"xiaohei_stand_r0.png", 0, DunJiaTianShu::create());
    this->cardFormatEnemy(XuanWuCard::create(),"niutou_stand_r0.png", 1, DunJiaTianShu::create());
    this->cardFormatEnemy(XingTianCard::create(),"jiansheng_stand_r0.png", 2, DunJiaTianShu::create());
    this->cardFormatEnemy(ChangECard::create(),"bingnv_stand_r0.png", 3, DunJiaTianShu::create());
    this->cardFormatEnemy(TaoTieCard::create(),"panda_stand_r0.png", 4, DunJiaTianShu::create());
    this->cardFormatEnemy(FengHouCard::create(),"gugong_stand_r0.png", 5, DunJiaTianShu::create());
    this->cardFormatEnemy(FengBoCard::create(),"zhousi_stand_r0.png", 6, DunJiaTianShu::create());
    this->cardFormatEnemy(SuanYuCard::create(),"fengxing_stand_r0.png", 7, DunJiaTianShu::create());
    
}
