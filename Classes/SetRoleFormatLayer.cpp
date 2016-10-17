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
//    SetRoleFormatlayer* layer = SetRoleFormatlayer::create();
//    scene->addChild(layer);
//    layer->initSetRoleFormatLayer();
    return scene;
}

void SetRoleFormatlayer::initSetRoleFormatLayer() {

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto liston = EventListenerTouchOneByOne::create();
    liston->onTouchBegan = CC_CALLBACK_2(SetRoleFormatlayer::onTouchBegan, this);
    liston->onTouchMoved = CC_CALLBACK_2(SetRoleFormatlayer::onTouchMoved, this);
    liston->onTouchEnded = CC_CALLBACK_2(SetRoleFormatlayer::onTouchEnded, this);
    liston->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(liston, this);
    
    Sprite* background = Sprite::create("背景1.png");
    CommonFunc::setSpriteSize(background, this->getBoundingBox().size.width);
    background->setPosition(Vec2(this->getBoundingBox().size.width/2+origin.x, this->getBoundingBox().size.height/2+origin.y));
    background->setLocalZOrder(-100);
    this->addChild(background);
    
    this->player = FightPlayer::create();
    this->player->fpName = "player";
    this->player->fightLayer = this;
    this->player->initMap("leftmap.png", "left", Size(this->getBoundingBox().size.width*0.449,this->getBoundingBox().size.width*0.449));
    this->player->fMap->setPosition(this->getBoundingBox().size.width*0.015+origin.x, this->getBoundingBox().size.height*0.16+origin.y);
    
    for (int i = 0; i < this->roleData.size(); i++) {
        this->roleData.at(i)->card->initCardSprite(this->roleData.at(i)->imageName);
        this->player->setCardsPositon(this->roleData.at(i)->card, this->roleData.at(i)->cellIndex,50);
    }
//    this->initCardFormat(HouYiCard::create(),"xiaohei_stand_l0.png", 0, DunJiaTianShu::create());
//    this->initCardFormat(XuanWuCard::create(),"niutou_stand_l0.png", 1, DunJiaTianShu::create());
//    this->initCardFormat(XingTianCard::create(),"jiansheng_stand_l0.png", 2, DunJiaTianShu::create());
//    this->initCardFormat(ChangECard::create(),"bingnv_stand_l0.png", 3, DunJiaTianShu::create());
//    this->initCardFormat(TaoTieCard::create(),"panda_stand_l0.png", 4, DunJiaTianShu::create());
//    this->initCardFormat(FengHouCard::create(),"gugong_stand_l0.png", 5, DunJiaTianShu::create());
//    this->initCardFormat(FengBoCard::create(),"zhousi_stand_l0.png", 6, DunJiaTianShu::create());
//    this->initCardFormat(SuanYuCard::create(),"fengxing_stand_l0.png", 7, DunJiaTianShu::create());
    this->player->retain();
    
    if(this->preLayerName.compare("fuben") == 0) {
        this->addFightBtnUI();
        this->addEnemyBtnUI();
    }
    this->addBackBtnUI();
   // this->addFightBtnUI();
    this->infoLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 16);
    this->infoLabel->setTextColor(Color4B(0, 240, 0, 255));
    this->infoLabel->setOpacity(0);
    this->addChild(this->infoLabel,500);
}

void SetRoleFormatlayer::addBackBtnUI() {

    ui::Button *btn = ui::Button::create("CloseNormal.png");
    CommonFunc::initButton(btn,CC_CALLBACK_2(SetRoleFormatlayer::backBtn, this) , this->getBoundingBox().size.width*0.05, Vec2(this->getBoundingBox().size.width*0.96, this->getBoundingBox().size.height*0.92));
    this->addChild(btn,500);
}

void SetRoleFormatlayer::backBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (this->preLayerName.compare("buzhen") == 0) {
        Director::getInstance()->popScene();
    }else if(this->preLayerName.compare("fuben") == 0) {
        if (this->enemyPlayer != NULL) {
            this->enemyPlayer->release();
        }
        this->player->release();
        this->roleData.clear();
        this->enemyRoleData.clear();
        this->removeFromParent();
    }
    

}

void SetRoleFormatlayer::addFightBtnUI() {
    ui::Button *btn = ui::Button::create();
    btn->setTitleText("Start Fight");
    btn->setTitleColor(Color3B(255, 255, 255));
    btn->setTitleFontSize(15);
    btn->setPressedActionEnabled(true);
    btn->setContentSize(Size(100, 40));
    btn->setPosition(Vec2(this->getBoundingBox().size.width/2+origin.x,this->getBoundingBox().size.width*0.053+origin.y));
    btn->addTouchEventListener(CC_CALLBACK_2(SetRoleFormatlayer::startFightBtn, this));
    this->addChild(btn,500);
}

void SetRoleFormatlayer::addEnemyBtnUI() {
    this->enemyPlayer = FightPlayer::create();
    this->enemyPlayer->fpName = "enemyPlayer";
    this->enemyPlayer->fightLayer = this;
    this->enemyPlayer->initMap("rightmap.png", "right",Size(this->getBoundingBox().size.width*0.449,this->getBoundingBox().size.width*0.449));
    this->enemyPlayer->fMap->setPosition(this->getBoundingBox().size.width-(this->getBoundingBox().size.width*0.015+this->enemyPlayer->fMap->getBoundingBox().size.width+origin.x), this->getBoundingBox().size.height*0.16+origin.y);
    this->enemyPlayer->retain();
    for (int i = 0; i < this->enemyRoleData.size(); i++) {
        this->enemyRoleData.at(i)->card->initCardSprite(this->enemyRoleData.at(i)->imageName);
        this->enemyPlayer->setCardsPositon(this->enemyRoleData.at(i)->card, this->enemyRoleData.at(i)->cellIndex,50);
    }

}

void SetRoleFormatlayer::startFightBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    auto nextScene = FightLayer::createScene();
    //auto nextLayer = (FightLayer*)nextScene->getChildren().at(0);
    FightLayer* layer = FightLayer::create();
    for (int k = 0; k < this->removeRoleData.size(); k++) {
        this->roleData.eraseObject(this->removeRoleData.at(k));
    }
    nextScene->addChild(layer);
    for (int i = 0; i < this->roleData.size(); i++) {
        CC_SAFE_RETAIN(this->roleData.at(i)->card->cardSprite);
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
    CC_SAFE_RETAIN(this->player);
    this->player->release();
    if (this->enemyPlayer != NULL) {
        CC_SAFE_RETAIN(this->enemyPlayer);
        this->enemyPlayer->release();
    }
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, nextScene));
   // Director::getInstance()->replaceScene(nextScene);
}

//void SetRoleFormatlayer::initCardFormat(Card* card,std::string imageName, int standIndex,Treasure* treasure) {
//    
//
//    card->initCardSprite(imageName);
//    this->player->setCardsPositon(card, standIndex,50);
//    card->retain();
//    auto data = SetRoleData::create();
//    data->imageName = imageName;
//    data->cellIndex = standIndex;
//    data->magicGoods = treasure;
//    data->magicGoods->retain();
//    data->card = card;
//    data->noBring = false;
//    this->roleData.pushBack(data);
//}

bool SetRoleFormatlayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
 //      printf("%f------%f\n",this->getPosition().x,this->getPosition().y);
    auto touchLocation = touch->getLocationInView();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    for (int i = 0; i < this->roleData.size(); i++) {
        auto tempPoint = this->countCardOrigonPoint(this->roleData.at(i)->card,this->player);
        Rect rect = Rect(tempPoint.x, tempPoint.y, this->player->fMap->getBoundingBox().size.width/4, this->player->fMap->getBoundingBox().size.width/4);
        if (rect.containsPoint(touchLocation)) {
            this->currentMoveCard = this->roleData.at(i)->card;
           // schedule(schedule_selector(SetRoleFormatlayer::showInfo), 1.0);
            return true;
        }
    }
    this->currentMoveCard = NULL;
    
    if (this->preLayerName.compare("fuben") == 0) {
        for (int i = 0; i < this->enemyRoleData.size(); i++) {
            auto tempPoint = this->countCardOrigonPoint(this->enemyRoleData.at(i)->card,this->enemyPlayer);
            Rect rect = Rect(tempPoint.x, tempPoint.y, this->enemyPlayer->fMap->getBoundingBox().size.width/4, this->enemyPlayer->fMap->getBoundingBox().size.width/4);
            if (rect.containsPoint(touchLocation)) {
                this->currentInfoCard = this->enemyRoleData.at(i)->card;
                schedule(schedule_selector(SetRoleFormatlayer::showInfo), 1.0);
                return true;
            }
        }
        this->currentInfoCard = NULL;
    }
    return  true;
}

void SetRoleFormatlayer::showInfo(float dur) {
    unschedule(schedule_selector(SetRoleFormatlayer::showInfo));
    this->infoLabel->setString(this->currentInfoCard->cardName.c_str());
    this->infoLabel->setOpacity(255);
    this->infoLabel->setPosition(Vec2(this->currentInfoCard->cardSprite->getPosition().x+this->enemyPlayer->fMap->getPosition().x, this->currentInfoCard->cardSprite->getPosition().y+this->enemyPlayer->fMap->getPosition().y+40));
}

void SetRoleFormatlayer::disappearInfo() {
    this->infoLabel->setOpacity(0);
    
}

void SetRoleFormatlayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
 
    if (this->currentMoveCard != NULL) {
        auto point = Director::getInstance()->convertToGL(touch->getLocationInView());
        auto oldPoint = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
        auto distance = point-oldPoint;
        
      //  printf("pointx:%f-------oldpointx:%f--------distancex:%f\n",point.x,oldPoint.x,distance.x);
//        auto currentPoint = this->currentMoveCard->cardSprite->getPosition()+this->player->fMap->getPosition()+distance;
//        Rect rect = Rect(this->player->fMap->getPosition(),this->player->fMap->getBoundingBox().size);
//        if (rect.containsPoint(currentPoint)) {
//            
//        }
        this->currentMoveCard->cardSprite->setPosition(this->currentMoveCard->cardSprite->getPosition()+distance);
      //  printf("pointx:%f-------oldpointx:%f----cardX:%f----cardY:%f\n",point.x,oldPoint.x,this->currentMoveCard->cardSprite->getPosition().x,this->currentMoveCard->cardSprite->getPosition().y);
        
    }
}

Vec2 SetRoleFormatlayer::countCardOrigonPoint(Card *card,FightPlayer* tempPlayer) {
    Vec2 point = Vec2(0, 0);
    point.x = card->cardSprite->getPosition().x-tempPlayer->fMap->getBoundingBox().size.width/8+tempPlayer->fMap->getPosition().x+this->getPosition().x;
    point.y = card->cardSprite->getPosition().y-tempPlayer->fMap->getBoundingBox().size.width/8+tempPlayer->fMap->getPosition().y+this->getPosition().y;
    return point;
}

void SetRoleFormatlayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    if (this->currentInfoCard != NULL) {
        unschedule(schedule_selector(SetRoleFormatlayer::showInfo));
        this->disappearInfo();
    }

    if (this->currentMoveCard != NULL) {
        
        bool isTake = false;
        for (int i = 0; i < this->player->fMap->mapCellArray.size(); i++) {
            Vec2 point = Vec2(0,0);
            point.x = this->player->fMap->mapCellArray.at(i)->position.x-this->player->fMap->getBoundingBox().size.width/8+this->player->fMap->getPosition().x+this->getPosition().x;
            point.y = this->player->fMap->mapCellArray.at(i)->position.y-this->player->fMap->getBoundingBox().size.width/8+this->player->fMap->getPosition().y+this->getPosition().y;
            Rect rect = Rect(point.x,point.y,this->player->fMap->getBoundingBox().size.width/4,this->player->fMap->getBoundingBox().size.width/4);
//            printf("%f----x\n",this->currentMoveCard->cardSprite->getPosition().x+this->player->fMap->getPosition().x);
//            printf("%f----y\n", this->currentMoveCard->cardSprite->getPosition().y+this->player->fMap->getPosition().y);
            if (rect.containsPoint(Vec2(this->currentMoveCard->cardSprite->getPosition().x+this->player->fMap->getPosition().x+this->getPosition().x, this->currentMoveCard->cardSprite->getPosition().y+this->player->fMap->getPosition().y+this->getPosition().y))) {
                isTake = true;
                for (int n = 0; n < this->removeRoleData.size(); n++) {
                    if (this->removeRoleData.at(n)->card->cardName.compare(this->currentMoveCard->cardName) == 0) {
                        this->removeRoleData.erase(n);
                        break;
                    }
                }
                
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
        if (isTake == false) {
            for (int j = 0; j < this->player->fMap->mapCellArray.size(); j++) {
                if (this->player->fMap->mapCellArray.at(j)->obj != NULL) {
                    
                    if (((Card*)this->player->fMap->mapCellArray.at(j)->obj)->cardName.compare(this->currentMoveCard->cardName) == 0) {

                        this->player->fMap->mapCellArray.at(j)->obj = NULL;
                        break;
                    }
                }
            }
           // SetRoleData* temp;
            for (int i = 0; i < this->roleData.size(); i++) {
                if (this->roleData.at(i)->card->cardName.compare(this->currentMoveCard->cardName) == 0) {
                    this->removeRoleData.pushBack(this->roleData.at(i));
                }
            }
           // this->roleData.eraseObject(temp);
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
