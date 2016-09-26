//
//  SetRoleFormatLayer.cpp
//  OctLegend
//
//  Created by zc on 16/9/20.
//
//

#include "SetRoleFormatLayer.h"
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
#include "FightLayer.h"

bool SetRoleFormatlayer::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

Scene* SetRoleFormatlayer::createScene() {
    Scene* scene = Scene::create();
    SetRoleFormatlayer* layer = SetRoleFormatlayer::create();
    scene->addChild(layer);
    layer->initSetRoleFormatLayer();
    return scene;
}

void SetRoleFormatlayer::initSetRoleFormatLayer() {

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto liston = EventListenerTouchOneByOne::create();
    liston->onTouchBegan = CC_CALLBACK_2(SetRoleFormatlayer::onTouchBegan, this);
    liston->onTouchMoved = CC_CALLBACK_2(SetRoleFormatlayer::onTouchMoved, this);
    liston->onTouchEnded = CC_CALLBACK_2(SetRoleFormatlayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(liston, this);
    
    Sprite* background = Sprite::create("背景1.png");
    CommonFunc::setSpriteSize(background, screenSize.width);
    background->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height/2+origin.y));
    background->setLocalZOrder(-100);
    this->addChild(background);
    
    this->player = FightPlayer::create();
    this->player->fpName = "player";
    this->player->fightLayer = this;
    this->player->initMap("leftmap.png", "left");
    this->player->fMap->setPosition(screenSize.width/2+origin.x-this->player->fMap->getBoundingBox().size.width/2, screenSize.height/2+origin.y-this->player->fMap->getBoundingBox().size.height/2);
    
    this->initCardFormat(HouYiCard::create(),"xiaohei_stand_l0.png", 0, DunJiaTianShu::create());
    this->initCardFormat(XuanWuCard::create(),"niutou_stand_l0.png", 1, DunJiaTianShu::create());
    this->initCardFormat(XingTianCard::create(),"jiansheng_stand_l0.png", 2, DunJiaTianShu::create());
    this->initCardFormat(ChangECard::create(),"bingnv_stand_l0.png", 3, DunJiaTianShu::create());
    this->initCardFormat(TaoTieCard::create(),"panda_stand_l0.png", 4, DunJiaTianShu::create());
    this->initCardFormat(FengHouCard::create(),"gugong_stand_l0.png", 5, DunJiaTianShu::create());
    this->initCardFormat(FengBoCard::create(),"zhousi_stand_l0.png", 6, DunJiaTianShu::create());
    this->initCardFormat(SuanYuCard::create(),"fengxing_stand_l0.png", 7, DunJiaTianShu::create());
    this->player->retain();
    
    ui::Button *btn = ui::Button::create();
    btn->setTitleText("Start Fight");
    btn->setTitleColor(Color3B(255, 255, 255));
    btn->setTitleFontSize(25);
    btn->setPressedActionEnabled(true);
    btn->setContentSize(Size(100, 40));
    btn->setPosition(Vec2(screenSize.width+origin.x-100,70));
    btn->addTouchEventListener(CC_CALLBACK_2(SetRoleFormatlayer::startFightBtn, this));
    this->addChild(btn,500);
}

void SetRoleFormatlayer::startFightBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    auto nextScene = FightLayer::createScene();
    //auto nextLayer = (FightLayer*)nextScene->getChildren().at(0);
    FightLayer* layer = FightLayer::create();

    nextScene->addChild(layer);
    for (int i = 0; i < this->roleData.size(); i++) {
        this->roleData.at(i)->card->cardSprite->removeFromParent();
        auto tempData = SetRoleData::create();
        tempData->imageName = this->roleData.at(i)->imageName;
        tempData->cellIndex = this->roleData.at(i)->cellIndex;
        tempData->card = this->roleData.at(i)->card;
        tempData->magicGoods = this->roleData.at(i)->magicGoods;
        layer->roleData.pushBack(tempData);
      //  nextLayer->roleData->pushBack(this->roleData.at(i));
    }
  //  layer->roleData = &this->roleData;
    
    layer->initFightLayer();
   // nextLayer->ID = 10;
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, nextScene));
   // Director::getInstance()->replaceScene(nextScene);
}

void SetRoleFormatlayer::initCardFormat(Card* card,std::string imageName, int standIndex,Treasure* treasure) {
    

    card->initCardSprite(imageName);
    this->player->setCardsPositon(card, standIndex,50);
    card->retain();
    auto data = SetRoleData::create();
    data->imageName = imageName;
    data->cellIndex = standIndex;
    data->magicGoods = treasure;
    data->magicGoods->retain();
    data->card = card;
    this->roleData.pushBack(data);
}

bool SetRoleFormatlayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    auto touchLocation = touch->getLocationInView();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    for (int i = 0; i < this->roleData.size(); i++) {
        auto tempPoint = this->countCardOrigonPoint(this->roleData.at(i)->card);
        Rect rect = Rect(tempPoint.x, tempPoint.y, 66, 66);
        if (rect.containsPoint(touchLocation)) {
            this->currentMoveCard = this->roleData.at(i)->card;
            return true;
        }
    }
    this->currentMoveCard = NULL;
    
    return  true;
}

void SetRoleFormatlayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    if (this->currentMoveCard != NULL) {
        auto point = Director::getInstance()->convertToGL(touch->getLocationInView());
        auto oldPoint = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
        auto distance = point-oldPoint;
//        auto currentPoint = this->currentMoveCard->cardSprite->getPosition()+this->player->fMap->getPosition()+distance;
//        Rect rect = Rect(this->player->fMap->getPosition(),this->player->fMap->getBoundingBox().size);
//        if (rect.containsPoint(currentPoint)) {
//            
//        }
        this->currentMoveCard->cardSprite->setPosition(this->currentMoveCard->cardSprite->getPosition()+distance);
        
    }
}

Vec2 SetRoleFormatlayer::countCardOrigonPoint(Card *card) {
    Vec2 point = Vec2(0, 0);
    point.x = card->cardSprite->getPosition().x-33+this->player->fMap->getPosition().x;
    point.y = card->cardSprite->getPosition().y+this->player->fMap->getPosition().y;
    return point;
}

void SetRoleFormatlayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    if (this->currentMoveCard != NULL) {
        for (int i = 0; i < this->player->fMap->mapCellArray.size(); i++) {
            Vec2 point = Vec2(0,0);
            point.x = this->player->fMap->mapCellArray.at(i)->position.x-33+this->player->fMap->getPosition().x;
            point.y = this->player->fMap->mapCellArray.at(i)->position.y-33+this->player->fMap->getPosition().y;
            Rect rect = Rect(point.x,point.y,66,66);
//            printf("%f----x\n",this->currentMoveCard->cardSprite->getPosition().x+this->player->fMap->getPosition().x);
//            printf("%f----y\n", this->currentMoveCard->cardSprite->getPosition().y+this->player->fMap->getPosition().y);
            if (rect.containsPoint(Vec2(this->currentMoveCard->cardSprite->getPosition().x+this->player->fMap->getPosition().x, this->currentMoveCard->cardSprite->getPosition().y+this->player->fMap->getPosition().y))) {
                
                Vec2 defaultCardPoint = Vec2(0, 0);
                for (int j = 0; j < this->player->fMap->mapCellArray.size(); j++) {
                    if (this->player->fMap->mapCellArray.at(j)->obj != NULL) {

                        if (((Card*)this->player->fMap->mapCellArray.at(j)->obj)->cardName.compare(this->currentMoveCard->cardName) == 0) {
                            defaultCardPoint = this->player->fMap->mapCellArray.at(j)->position;
                            this->player->fMap->mapCellArray.at(j)->obj = NULL;
                            break;
                        }
                    }
                }
                if (this->player->fMap->mapCellArray.at(i)->obj != NULL) {
                    ((Card*)this->player->fMap->mapCellArray.at(i)->obj)->cardSprite->setPosition(defaultCardPoint);
                    ((Card*)this->player->fMap->mapCellArray.at(i)->obj)->cellIndex = this->currentMoveCard->cellIndex;
                    this->player->fMap->mapCellArray.at(this->currentMoveCard->cellIndex)->obj = ((Card*)this->player->fMap->mapCellArray.at(i)->obj);
                }
                this->currentMoveCard->cardSprite->setPosition(this->player->fMap->mapCellArray.at(i)->position);
                this->player->fMap->mapCellArray.at(i)->obj = this->currentMoveCard;
                this->currentMoveCard->cellIndex = i;
                break;
            }
        }
        
        for (int k = 0; k < this->roleData.size(); k++) {
            this->roleData.at(k)->cellIndex = this->roleData.at(k)->card->cellIndex;
          //  printf("%s----%d\n",this->roleData.at(k)->card->cardName.c_str(),this->roleData.at(k)->cellIndex);
        }
    }
}

bool SetRoleData::init() {
    return true;
}
