//
//  GameBeginLayer.cpp
//  OctLegend
//
//  Created by zc on 16/9/27.
//
//

#include "GameBeginLayer.h"
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
#include "FuBenLayer.h"
#include "LingShoLayer.h"
#include "Bag/Bag.h"
#include "TuJianLayer.h"
bool GameBeginLayer::init() {
    if (!Layer::init()) {
        return  false;
    }
    return true;
}

Scene* GameBeginLayer::createScene() {
    Scene* scene = Scene::create();
    GameBeginLayer* layer = GameBeginLayer::create();
    scene->addChild(layer);
    layer->initGameBeginLayer();
    return scene;
}

//void GameBeginLayer::onEnter() {
//    this->initGameBeginLayer();
//
//}

void GameBeginLayer::initGameBeginLayer() {
    this->backgroundOne = Sprite::create("beijing_left.png");
    CommonFunc::setSpriteSize(this->backgroundOne, screenSize.width);
    this->backgroundOne->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height/2+origin.y));
    this->backgroundOne->setLocalZOrder(-100);
    this->addChild(this->backgroundOne);
    
    this->backgroundTwo = Sprite::create("beijing_right.png");
    CommonFunc::setSpriteSize(this->backgroundTwo, screenSize.width);
    this->backgroundTwo->setPosition(Vec2(screenSize.width/2+origin.x+screenSize.width, screenSize.height/2+origin.y));
    this->backgroundTwo->setLocalZOrder(-100);
    this->addChild(this->backgroundTwo);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto liston = EventListenerTouchOneByOne::create();
    liston->onTouchBegan = CC_CALLBACK_2(GameBeginLayer::onTouchBegan, this);
    liston->onTouchMoved = CC_CALLBACK_2(GameBeginLayer::onTouchMoved, this);
    liston->onTouchEnded = CC_CALLBACK_2(GameBeginLayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(liston, this);
    
    
    this->dragon = Dragon::create();
    this->dragon->initDragonShuXing();
    this->dragon->retain();
    
    this->playerBag = Bag::create();
    this->playerBag->taoZiNum = 100;
    this->playerBag->retain();
    
    this->cardFormatJJC(HouYiCard::create(),"xiaohei_stand_l0.png", 0, DunJiaTianShu::create());
    this->cardFormatJJC(XuanWuCard::create(),"niutou_stand_l0.png", 1, DunJiaTianShu::create());
    this->cardFormatJJC(XingTianCard::create(),"jiansheng_stand_l0.png", 2, DunJiaTianShu::create());
    this->cardFormatJJC(ChangECard::create(),"bingnv_stand_l0.png", 3, DunJiaTianShu::create());
    this->cardFormatJJC(TaoTieCard::create(),"panda_stand_l0.png", 4, DunJiaTianShu::create());
    this->cardFormatJJC(FengHouCard::create(),"gugong_stand_l0.png", 5, DunJiaTianShu::create());
    this->cardFormatJJC(FengBoCard::create(),"zhousi_stand_l0.png", 6, DunJiaTianShu::create());
    this->cardFormatJJC(SuanYuCard::create(),"fengxing_stand_l0.png", 7, DunJiaTianShu::create());
    
    
    this->cardFormatPVE(HouYiCard::create(),"xiaohei_stand_l0.png", 0, DunJiaTianShu::create());
//    this->cardFormatPVE(HouYiCard::create(),"xiaohei_stand_l0.png", 1, DunJiaTianShu::create());
//    this->cardFormatPVE(HouYiCard::create(),"xiaohei_stand_l0.png", 2, DunJiaTianShu::create());
//    this->cardFormatPVE(HouYiCard::create(),"xiaohei_stand_l0.png", 3, DunJiaTianShu::create());
//    this->cardFormatPVE(HouYiCard::create(),"xiaohei_stand_l0.png", 4, DunJiaTianShu::create());
//    this->cardFormatPVE(HouYiCard::create(),"xiaohei_stand_l0.png", 5, DunJiaTianShu::create());
//    this->cardFormatPVE(HouYiCard::create(),"xiaohei_stand_l0.png", 6, DunJiaTianShu::create());
//    this->cardFormatPVE(HouYiCard::create(),"xiaohei_stand_l0.png", 7, DunJiaTianShu::create());
    
    this->cardFormatPVE(XuanWuCard::create(),"niutou_stand_l0.png", 1, DunJiaTianShu::create());
    this->cardFormatPVE(XingTianCard::create(),"jiansheng_stand_l0.png", 2, DunJiaTianShu::create());
    this->cardFormatPVE(ChangECard::create(),"bingnv_stand_l0.png", 3, DunJiaTianShu::create());
    this->cardFormatPVE(TaoTieCard::create(),"panda_stand_l0.png", 4, DunJiaTianShu::create());
    this->cardFormatPVE(FengHouCard::create(),"gugong_stand_l0.png", 5, DunJiaTianShu::create());
    this->cardFormatPVE(FengBoCard::create(),"zhousi_stand_l0.png", 6, DunJiaTianShu::create());
    this->cardFormatPVE(SuanYuCard::create(),"fengxing_stand_l0.png", 7, DunJiaTianShu::create());
    this->buZhen = ui::Button::create("buzhen.png");

    
    auto scale = this->backgroundOne->getScale();
    
    CommonFunc::initButton(this->buZhen, CC_CALLBACK_2(GameBeginLayer::buZhenBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10/scale, screenSize.height/3*2/scale));
    this->backgroundOne->addChild(this->buZhen,50);
    
    this->faBao = ui::Button::create("fabao.png");
    CommonFunc::initButton(this->faBao, CC_CALLBACK_2(GameBeginLayer::faBaoBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10*2/scale, screenSize.height/3*2/scale));
    this->backgroundOne->addChild(this->faBao,50);
    
    this->jingJiChang = ui::Button::create("jingjichang.png");
    CommonFunc::initButton(this->jingJiChang, CC_CALLBACK_2(GameBeginLayer::jingJiChangBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10*3/scale, screenSize.height/3*2/scale));
    this->backgroundOne->addChild(this->jingJiChang,50);
    
    this->juHun = ui::Button::create("juhun.png");
    CommonFunc::initButton(this->juHun, CC_CALLBACK_2(GameBeginLayer::juHunBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10*4/scale, screenSize.height/3*2/scale));
    this->backgroundOne->addChild(this->juHun,50);
    
    this->lingShou = ui::Button::create("lingshou.png");
    CommonFunc::initButton(this->lingShou, CC_CALLBACK_2(GameBeginLayer::lingShouBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10/scale, screenSize.height/3/scale));
    this->backgroundOne->addChild(this->lingShou,50);
    
    this->renWu = ui::Button::create("renwu.png");
    CommonFunc::initButton(this->renWu, CC_CALLBACK_2(GameBeginLayer::renWuBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10*2/scale, screenSize.height/3/scale));
    this->backgroundOne->addChild(this->renWu,50);
    
    this->tianFu = ui::Button::create("tianfu.png");
    CommonFunc::initButton(this->tianFu, CC_CALLBACK_2(GameBeginLayer::tianFuBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10*3/scale, screenSize.height/3/scale));
    this->backgroundOne->addChild(this->tianFu,50);
    
    this->zhuXian = ui::Button::create("zhuxian.png");
    CommonFunc::initButton(this->zhuXian, CC_CALLBACK_2(GameBeginLayer::zhuXianBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10*4/scale, screenSize.height/3/scale));
    this->backgroundOne->addChild(this->zhuXian,50);
}

void GameBeginLayer::cardFormatJJC(Card* card,std::string imageName, int standIndex,Treasure* treasure) {
    
    
   // card->initCardSprite(imageName);
  //  this->player->setCardsPositon(card, standIndex,50);
    card->retain();
    auto jjcData = SetRoleData::create();
    jjcData->xiaoImageName = card->cardName+"_tx.jpg";
    jjcData->imageName = imageName;
    jjcData->cellIndex = standIndex;
    jjcData->magicGoods = treasure;
    jjcData->magicGoods->retain();
    jjcData->card = card;
    jjcData->noBring = false;
    this->jjcRoleData.pushBack(jjcData);
    
}

void GameBeginLayer::cardFormatPVE(Card* card,std::string imageName, int standIndex,Treasure* treasure) {
  //  card->initCardSprite(imageName);
    //  this->player->setCardsPositon(card, standIndex,50);
    card->retain();
    
    auto pveData = SetRoleData::create();
    pveData->xiaoImageName = card->cardName+"_tx.jpg";
    pveData->imageName = imageName;
    pveData->cellIndex = standIndex;
    pveData->magicGoods = treasure;
    pveData->magicGoods->retain();
    pveData->card = card;
    pveData->noBring = false;
    this->pveRoleData.pushBack(pveData);
}

void GameBeginLayer::buZhenBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    auto setRoleScene = SetRoleFormatlayer::createScene();
    SetRoleFormatlayer* layer = SetRoleFormatlayer::create();
    layer->setContentSize(screenSize);
    setRoleScene->addChild(layer);
    
    for (int i = 0; i < this->jjcRoleData.size(); i++) {
        layer->roleData.pushBack(this->jjcRoleData.at(i));
    }
    layer->preLayerName = "buzhen";
    layer->initSetRoleFormatLayer();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, setRoleScene));
}

void GameBeginLayer::faBaoBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    
}

void GameBeginLayer::jingJiChangBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    
}

void GameBeginLayer::juHunBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    
}

void GameBeginLayer::lingShouBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    auto lingShoScene = LingShoLayer::createScene();
    LingShoLayer* layer = LingShoLayer::create();
    layer->setContentSize(screenSize);
    
    lingShoScene->addChild(layer);
    layer->myBag = this->playerBag;
    layer->myDragon = this->dragon;
    layer->initLingShoLayer();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, lingShoScene));
}

void GameBeginLayer::renWuBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    auto tuJianScene = TuJianLayer::createScene();
    TuJianLayer* layer = TuJianLayer::create();
    layer->setContentSize(screenSize);
    
    tuJianScene->addChild(layer);

    layer->initTuJianLayer();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, tuJianScene));
}

void GameBeginLayer::tianFuBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    
}

void GameBeginLayer::zhuXianBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    auto fuBenScene = FuBenLayer::createScene();
    FuBenLayer* layer = FuBenLayer::create();
    layer->setContentSize(screenSize);
    fuBenScene->addChild(layer);
    
    for (int i = 0; i < this->pveRoleData.size(); i++) {
        layer->myRoleData.pushBack(this->pveRoleData.at(i));
    }
    layer->initFuBenLayer();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, fuBenScene));
}

bool GameBeginLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    return true;
}

void GameBeginLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {

    auto point = Director::getInstance()->convertToGL(touch->getLocationInView());
    auto oldPoint = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
    auto distance = point-oldPoint;
    
    if (this->backgroundOne->getPosition().x+distance.x > screenSize.width/2) {
        this->backgroundOne->setPosition(screenSize.width/2,screenSize.height/2);
        this->backgroundTwo->setPosition(screenSize.width*3/2,screenSize.height/2);
    }else if (this->backgroundTwo->getPosition().x+distance.x < screenSize.width/2) {
        this->backgroundTwo->setPosition(screenSize.width/2,screenSize.height/2);
        this->backgroundOne->setPosition(-screenSize.width/2,screenSize.height/2);
    }else {
        this->backgroundOne->setPosition(this->backgroundOne->getPosition().x+distance.x,screenSize.height/2);
        this->backgroundTwo->setPosition(this->backgroundTwo->getPosition().x+distance.x,screenSize.height/2);
    }
    
}

void GameBeginLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
}



