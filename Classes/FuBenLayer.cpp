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

#include "HouYiCard.h"
#include "ChangECard.h"
#include "TaoTieCard.h"
#include "XingTianCard.h"
#include "XuanWuCard.h"
#include "FengBoCard.h"
#include "FengHouCard.h"
#include "SuanYuCard.h"
#include "FightNetwork.h"
#include "DunJiaTianShu.h"


#include "ZheZhaoLayer.h"
Scene* FuBenLayer::createScene() {
    Scene* scene = Scene::create();
//    FuBenLayer* layer = FuBenLayer::create();
//    scene->addChild(layer);
    return scene;
}

bool FuBenLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

//void FuBenLayer::onExit() {
//    Layer::onExit();
//}

void FuBenLayer::initFuBenLayer() {
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto liston = EventListenerTouchOneByOne::create();
    liston->onTouchBegan = CC_CALLBACK_2(FuBenLayer::onTouchBegan, this);
    liston->onTouchMoved = CC_CALLBACK_2(FuBenLayer::onTouchMoved, this);
    liston->onTouchEnded = CC_CALLBACK_2(FuBenLayer::onTouchEnded, this);
   // liston->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(liston, this);
    
//    TestLayer* la = TestLayer::create();
//    la->setContentSize(screenSize);
//    la->initThisLayer();
//    this->addChild(la,1000);
//    Sprite* diTuLabelSp = Sprite::create("shijieditu.png");
//    CommonFunc::setSpriteSize(diTuLabelSp, 100);
//    diTuLabelSp->setPosition(Vec2(diTuLabelSp->getBoundingBox().size.width/2+10, screenSize.height-diTuLabelSp->getBoundingBox().size.height/2-10));
//    this->addChild(diTuLabelSp,300);
    
    this->background = Sprite::create("matchBg.jpg");
  //  CommonFunc::setSpriteSize(background, screenSize.width);
    CommonFunc::setShowAllSpriteSize(background, screenSize.width, screenSize.height);
    this->background->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height/2+origin.y));
    this->background->setLocalZOrder(-100);
    this->addChild(this->background);
    
    this->backBtnUI();
//    PveGuaiWu* pveGuaiWu1 = PveGuaiWu::create();
//    
//    pveGuaiWu1->index = 4;
//    pveGuaiWu1->createGuaiWu(this, "pve1.png", Vec2(this->background->getBoundingBox().size.width/2+10, this->background->getBoundingBox().size.height/2-50),70);
//  //  pveGuaiWu->myData = &this->myRoleData;
//    pveGuaiWu1->retain();
//    this->background->addChild(pveGuaiWu1->guaiWuBtn,50);
//
//    PveGuaiWu* pveGuaiWu2 = PveGuaiWu::create();
//    pveGuaiWu2->index = 5;
//    pveGuaiWu2->createGuaiWu(this, "pve2.png", Vec2(this->background->getBoundingBox().size.width/2-200, this->background->getBoundingBox().size.height/2+75),70);
//    //  pveGuaiWu->myData = &this->myRoleData;
//    pveGuaiWu2->retain();
//    this->background->addChild(pveGuaiWu2->guaiWuBtn,50);
//    
//    
//    PveGuaiWu* pveGuaiWu3 = PveGuaiWu::create();
//    pveGuaiWu3->index = 6;
//    pveGuaiWu3->createGuaiWu(this, "pve3.png", Vec2(this->background->getBoundingBox().size.width/2-100, this->background->getBoundingBox().size.height/2-100),70);
//    //  pveGuaiWu->myData = &this->myRoleData;
//    pveGuaiWu3->retain();
//    this->background->addChild(pveGuaiWu3->guaiWuBtn,50);

    for (int i = 1; i < 9; i++) {
        PveGuaiWu* pveGuaiWu = PveGuaiWu::create();
        pveGuaiWu->index = i;
        char tempName[20] = {0};
        sprintf(tempName, "pve%d.png",i);
        char tempGuanKa[20] = {0};
        sprintf(tempGuanKa, "第%d关",i);
        Label* guankaLabel = Label::createWithTTF(tempGuanKa, "fonts/hanyixuejunti.ttf", 14);
        guankaLabel->setDimensions(70, 20);
        guankaLabel->setAlignment(TextHAlignment::CENTER);
        guankaLabel->setTextColor(dragonFontColor);
        
        if (i < 5) {
            pveGuaiWu->createGuaiWu(this, tempName, Vec2(this->getBoundingBox().size.width/5*i, this->getBoundingBox().size.height*2/3+10),70);
            guankaLabel->setPosition(this->getBoundingBox().size.width/5*i,this->getBoundingBox().size.height*2/3-pveGuaiWu->guaiWuBtn->getBoundingBox().size.height/2);
        }else {
            pveGuaiWu->createGuaiWu(this, tempName, Vec2(this->getBoundingBox().size.width/5*(i%5+1), this->getBoundingBox().size.height/3),70);
            guankaLabel->setPosition(this->getBoundingBox().size.width/5*(i%5+1),this->getBoundingBox().size.height/3-10-pveGuaiWu->guaiWuBtn->getBoundingBox().size.height/2);
        }
        

        pveGuaiWu->retain();
        this->addChild(guankaLabel,50);
        this->addChild(pveGuaiWu->guaiWuBtn,50);
        this->guaiWuArray.pushBack(pveGuaiWu);
    }
    
    this->readEnemyData();
    
    
}

void FuBenLayer::backBtnUI() {
    
    ui::Button *btn = ui::Button::create("fanhuijian.png");
    
    btn->setPressedActionEnabled(true);
    btn->setPosition(Vec2(screenSize.width*0.96, screenSize.height*0.92));
    btn->addTouchEventListener(CC_CALLBACK_2(FuBenLayer::backBtn, this));
    btn->setScale(screenSize.width*0.05/btn->getBoundingBox().size.width);
    
   // btn = CommonFunc::initButton(btn,CC_CALLBACK_2(FuBenLayer::backBtn, this) , screenSize.width*0.05, Vec2(screenSize.width*0.96, screenSize.height*0.92));
    this->addChild(btn,200);
}

void FuBenLayer::backBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        ((Scene*)this->getParent())->onExit();
         Director::getInstance()->popScene();
    }
    
   
}


//void FuBenLayer::enemyOneBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType typr) {
//    
//    this->roleFormatLayer = SetRoleFormatlayer::create();
//    this->roleFormatLayer->setContentSize(screenSize);
//    this->addChild(this->roleFormatLayer,100);
//    this->roleFormatLayer->setPosition(Vec2(screenSize.width/2-this->roleFormatLayer->getBoundingBox().size.width/2, screenSize.height/2-this->roleFormatLayer->getBoundingBox().size.height/2));
//   // this->roleFormatLayer->setPosition(0,0);
//    this->roleFormatLayer->preLayerName = "fuben";
//    
//    for (int i = 0; i < this->myRoleData.size(); i++) {
//        this->roleFormatLayer->roleData.pushBack(this->myRoleData.at(i));
//    }
//    
//    for (int j = 0; j < this->enemyRoleData.size(); j++) {
//        this->roleFormatLayer->enemyRoleData.pushBack(this->enemyRoleData.at(j));
//    }
//    this->roleFormatLayer->initSetRoleFormatLayer();
//}

void FuBenLayer::cardFormatEnemy(Card* card,std::string imageName, int standIndex,Treasure* treasure) {
    card->initCardSprite(imageName);
    //  this->player->setCardsPositon(card, standIndex,50);
    card->cardSprite->setScaleX(-1);
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
    this->cardFormatEnemy(HouYiCard::create(),"houyi_idle_0.png", 0, DunJiaTianShu::create());
    this->cardFormatEnemy(XuanWuCard::create(),"xuanwu_idle_0.png", 1, DunJiaTianShu::create());
    this->cardFormatEnemy(XingTianCard::create(),"xingtian_idle_0.png", 2, DunJiaTianShu::create());
    this->cardFormatEnemy(ChangECard::create(),"change_idle_0.png", 3, DunJiaTianShu::create());
    this->cardFormatEnemy(TaoTieCard::create(),"taotie_idle_0.png", 4, DunJiaTianShu::create());
    this->cardFormatEnemy(FengHouCard::create(),"fenghou_idle_0.png", 5, DunJiaTianShu::create());
    this->cardFormatEnemy(FengBoCard::create(),"fengbo_idle_0.png", 6, DunJiaTianShu::create());
    this->cardFormatEnemy(SuanYuCard::create(),"suanyu_idle_0.png", 7, DunJiaTianShu::create());
    
}

bool FuBenLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
    return true;
}

void FuBenLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
//    auto point = Director::getInstance()->convertToGL(touch->getLocationInView());
//    auto oldPoint = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
//    auto distance = point-oldPoint;
////    if (<#condition#>) {
////        <#statements#>
////    }
//    auto maxX = this->background->getBoundingBox().size.width/2;
//    auto minX = -(this->background->getBoundingBox().size.width/2-screenSize.width);
//    auto maxY = this->background->getBoundingBox().size.height/2;
//    auto minY = -(this->background->getBoundingBox().size.height/2-screenSize.height);
//    auto mubiaoPoint = this->background->getPosition()+distance;
//    
//    Rect fanWei = Rect(minX, minY, this->background->getBoundingBox().size.width-screenSize.width, this->background->getBoundingBox().size.height-screenSize.height);
//    if (fanWei.containsPoint(mubiaoPoint)) {
//        this->background->setPosition(mubiaoPoint);
//    }

}

void FuBenLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
}
