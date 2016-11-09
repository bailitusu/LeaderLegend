//
//  PveFightLayer.cpp
//  OctLegend
//
//  Created by zc on 16/11/8.
//
//

#include "PveFightLayer.h"
#include "Setting.h"
#include "CommonFunc.h"

#include "HouYiCard.h"
#include "ChangECard.h"
#include "TaoTieCard.h"
#include "XingTianCard.h"
#include "XuanWuCard.h"
#include "FengBoCard.h"
#include "FengHouCard.h"
#include "SuanYuCard.h"

#include "FightLayer.h"
bool PveFightLayer::init() {
    if (!Layer::init()) {
        
        return false;
    }

    return true;
}

Scene* PveFightLayer::createScene() {
    Scene* scene = Scene::create();
    return scene;
}

void PveFightLayer::initPveLayer() {
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto liston = EventListenerTouchOneByOne::create();
    liston->onTouchBegan = CC_CALLBACK_2(PveFightLayer::onTouchBegan, this);
    liston->onTouchMoved = CC_CALLBACK_2(PveFightLayer::onTouchMoved, this);
    liston->onTouchEnded = CC_CALLBACK_2(PveFightLayer::onTouchEnded, this);
    liston->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(liston, this);
    

    
    this->player = FightPlayer::create();
    this->player->fpName = "player";
    this->player->fightLayer = this;
    this->player->initMap("leftmap.png", "left", Size(300,300));
    this->player->fMap->setPosition(10+origin.x, 40+origin.y);
    this->player->fMap->setLocalZOrder(300);

    
    this->playerEnemy = FightPlayer::create();
    this->playerEnemy->fpName = "enemyPlayer";
    this->playerEnemy->fightLayer = this;
    this->playerEnemy->initMap("rightmap.png", "right", Size(300,300));
    this->playerEnemy->fMap->setPosition(screenSize.width-(this->playerEnemy->fMap->getBoundingBox().size.width+10+origin.x),40+origin.y);
   // this->playerEnemy->fMap->setLocalZOrder(300);


    this->player->playerKey = myKey;
    
    this->player->retain();
    this->playerEnemy->retain();
    
    this->background = Sprite::create("uv界面测试(1).png");//bbg_arena.png
    CommonFunc::setSpriteSize(this->background, screenSize.width);
    this->background->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height/2+origin.y));
    this->background->setLocalZOrder(-100);
    this->addChild(background);
    
    this->chouTiBtn = ui::Button::create("choutibtn_left.png");
    this->chouTiBtn->setAnchorPoint(Vec2(1, 0.5));
    CommonFunc::initButton(this->chouTiBtn, CC_CALLBACK_2(PveFightLayer::chouTibtnClick, this), screenSize.width*0.072, Vec2(screenSize.width, screenSize.height*0.072));
    this->addChild(this->chouTiBtn,200);
    
    this->addMyTakeCard();

    this->initEnemyInfo();
}

void PveFightLayer::addMyTakeCard() {

    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    rapidjson::Value tempKey;
    tempKey.SetString(myKey.c_str(), (unsigned int)strlen(myKey.c_str()));
    doc.AddMember("playerkey", tempKey, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    
    std::string url = PvePlayerTakeCardGetUrl;
    url = url + myKey+"/cards";
    FightNetwork* net = FightNetwork::GetInstance();
    net->createGetHttp(url, this, httpresponse_selector(PveFightLayer::takeCardResponse));


}

void PveFightLayer::takeCardResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    std::vector<char>* info = response->getResponseData();
    std::string infoStr  = std::string(info->begin(),info->end());
    rapidjson::Document doc;
    doc.Parse<0>(infoStr.c_str());
    if(doc.HasParseError())
    {
        printf("pvePlayerCardinfo-----GetParseError%u\n", doc.GetParseError());
        return ;
    }

    int code = doc["code"].GetInt();
    if (code == 0) {
        rapidjson::Value& dataArray = doc["data"];
        for (int i = 0; i < dataArray.Size(); i++) {
            std::string tempName = dataArray[i].GetString();
            auto roleData = SetRoleData::create();
            if (tempName.compare("houyi") == 0) {
                roleData->card = HouYiCard::create();
                roleData->card->retain();
            }else if(tempName.compare("xuanwu") == 0) {
                roleData->card = XuanWuCard::create();
                roleData->card->retain();
            }else if(tempName.compare("change") == 0) {
                roleData->card = ChangECard::create();
                roleData->card->retain();
            }else if(tempName.compare("fenghou") == 0) {
                roleData->card = FengHouCard::create();
                roleData->card->retain();
            }else if(tempName.compare("fengbo") == 0) {
                roleData->card = FengBoCard::create();
                roleData->card->retain();
            }else if(tempName.compare("suanyu") == 0) {
                roleData->card = SuanYuCard::create();
                roleData->card->retain();
            }else if(tempName.compare("xingtian") == 0) {
                roleData->card = XingTianCard::create();
                roleData->card->retain();
            }else if(tempName.compare("taotie") == 0) {
                roleData->card = TaoTieCard::create();
                roleData->card->retain();
            }
            roleData->xiaoImageName = roleData->card->cardName+"_tx.jpg";
            roleData->imageName = roleData->card->cardSpriteImageName+"_l0.png";

            this->myAllData.pushBack(roleData);
        }
        this->initChouTiLayer();
    }
    
}

void PveFightLayer::initEnemyInfo() {
    for (int i = 0; i < this->enemyRoleData.size(); i++) {
        this->enemyRoleData.at(i)->card->initCardSprite(this->enemyRoleData.at(i)->imageName);
        this->playerEnemy->setCardsPositon(this->enemyRoleData.at(i)->card, this->enemyRoleData.at(i)->cellIndex,50);
    }
}

void PveFightLayer::chouTibtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        if((this->chouTiLayer->getActionByTag(10) == NULL) && (this->chouTiLayer->getActionByTag(100) == NULL)) {
            if (this->chouTiLayer->getPosition().x < screenSize.width) {
                
                auto moveIn = MoveTo::create(0.3f, Vec2(screenSize.width, this->chouTiLayer->getPosition().y));
                moveIn->setTag(10);
                this->chouTiBtn->loadTextureNormal("choutibtn_left.png");
                this->chouTiLayer->runAction(moveIn);
            }else {
                auto moveOut = MoveTo::create(0.3f, Vec2(screenSize.width-this->chouTiLayer->getBoundingBox().size.width, this->chouTiLayer->getPosition().y));
                
                moveOut->setTag(100);
                this->chouTiBtn->loadTextureNormal("choutibtn_right.png");
                this->chouTiLayer->runAction(moveOut);
            }
        }
        
        
    }
    
}

void PveFightLayer::initChouTiLayer() {
    this->chouTiLayer = Layer::create();
    this->chouTiLayer->setContentSize(Size(screenSize.width*0.46, screenSize.height*0.75));
    this->chouTiLayer->setPosition(Vec2(screenSize.width, screenSize.height/2-this->chouTiLayer->getBoundingBox().size.height/2));
    this->addChild(chouTiLayer,100);
    
    Sprite* bg = Sprite::create("buzhenBg2.jpg");
    
    CommonFunc::setShowAllSpriteSize(bg, this->chouTiLayer->getBoundingBox().size.width, this->chouTiLayer->getBoundingBox().size.height);
    bg->setPosition(this->chouTiLayer->getBoundingBox().size.width/2,this->chouTiLayer->getBoundingBox().size.height/2);
    this->chouTiLayer->addChild(bg, -100);
    
    for (int i = 0; i < this->myAllData.size(); i++) {
        Sprite* gezi = Sprite::create("herotouxiangbg.png");
        CommonFunc::setShowAllSpriteSize(gezi, this->chouTiLayer->getBoundingBox().size.width/4-5, this->chouTiLayer->getBoundingBox().size.width/4-5);
        gezi->setPosition(Vec2(8+this->chouTiLayer->getBoundingBox().size.width/8+(this->chouTiLayer->getBoundingBox().size.width/4-5)*(i%4), this->chouTiLayer->getBoundingBox().size.height-(this->chouTiLayer->getBoundingBox().size.height/8+this->chouTiLayer->getBoundingBox().size.height/4*(i/4))-10 ));
        this->chouTiLayer->addChild(gezi,100);
        
        this->myAllData.at(i)->xiaoSp = Sprite::create(this->myAllData.at(i)->xiaoImageName);
        CommonFunc::setShowAllSpriteSize(this->myAllData.at(i)->xiaoSp, this->chouTiLayer->getBoundingBox().size.width/4-14, this->chouTiLayer->getBoundingBox().size.width/4-14);
        this->myAllData.at(i)->xiaoSp->setPosition(gezi->getPosition());
        this->chouTiLayer->addChild(this->myAllData.at(i)->xiaoSp,150);
    }
    
    this->startFightBtn = ui::Button::create("classbtn.png");
    CommonFunc::initButton(this->startFightBtn, CC_CALLBACK_2(PveFightLayer::startFightBtnClick, this), screenSize.width/8, Vec2(screenSize.width*0.06, screenSize.height*0.075));
    this->startFightBtn->setTitleText("开始战斗");
    this->startFightBtn->setTitleColor(Color3B(255, 255, 255));
    this->addChild(this->startFightBtn,100);
}

Vec2 PveFightLayer::countCardOrigonPoint(Card *card, FightPlayer *tempPlayer) {
    Vec2 point = Vec2(0, 0);
    point.x = card->cardSprite->getPosition().x-tempPlayer->fMap->getBoundingBox().size.width/8+tempPlayer->fMap->getPosition().x+this->getPosition().x;
    point.y = card->cardSprite->getPosition().y-tempPlayer->fMap->getBoundingBox().size.width/8+tempPlayer->fMap->getPosition().y+this->getPosition().y;
    return point;
}

bool PveFightLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    auto touchLocation = touch->getLocationInView();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    
    for (int i = 0; i < this->myAllData.size(); i++) {
        auto xiaoCardPoint = Vec2(this->myAllData.at(i)->xiaoSp->getPosition().x-this->myAllData.at(i)->xiaoSp->getBoundingBox().size.width/2, this->myAllData.at(i)->xiaoSp->getPosition().y-this->myAllData.at(i)->xiaoSp->getBoundingBox().size.height/2);
        xiaoCardPoint = xiaoCardPoint+this->chouTiLayer->getPosition();
        Rect rect = Rect(xiaoCardPoint.x,xiaoCardPoint.y,this->myAllData.at(i)->xiaoSp->getBoundingBox().size.width,this->myAllData.at(i)->xiaoSp->getBoundingBox().size.height);
        
        if (rect.containsPoint(touchLocation)) {
            if (this->myAllData.at(i)->xiaoSp->getOpacity() > 125 ) {
                this->myAllData.at(i)->card->initCardSprite(this->myAllData.at(i)->imageName);
                auto point = Vec2(xiaoCardPoint.x+this->myAllData.at(i)->xiaoSp->getBoundingBox().size.width/2,xiaoCardPoint.y+this->myAllData.at(i)->xiaoSp->getBoundingBox().size.height/2);
                this->myAllData.at(i)->card->cardSprite->setPosition(point-this->player->fMap->getPosition());
                this->player->fMap->addChild(this->myAllData.at(i)->card->cardSprite,150);
                this->myAllData.at(i)->xiaoSp->setOpacity(125);
                
                break;
            }
        }
    }
    
    for (int i = 0; i < this->myAllData.size(); i++) {
        if (this->myAllData.at(i)->card->cardSprite != NULL ) {
            auto tempPoint = this->countCardOrigonPoint(this->myAllData.at(i)->card,this->player);
            Rect rect = Rect(tempPoint.x, tempPoint.y, this->player->fMap->getBoundingBox().size.width/4, this->player->fMap->getBoundingBox().size.width/4);
            if (rect.containsPoint(touchLocation)) {
               // if (this->myAllData.at(i)->isPvpBuShu == false) {
                    this->moveCard = this->myAllData.at(i)->card;
             //   }
                
                //     printf("%s",this->currentMoveCard->cardName.c_str());
                // schedule(schedule_selector(SetRoleFormatlayer::showInfo), 1.0);
                return true;
            }
        }
    }
    this->moveCard = NULL;

    return true;
}

void PveFightLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    if (this->moveCard != NULL) {
        auto point = Director::getInstance()->convertToGL(touch->getLocationInView());
        auto oldPoint = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
        auto distance = point-oldPoint;
        this->moveCard->cardSprite->setPosition(this->moveCard->cardSprite->getPosition()+distance);
        
    }
}

void PveFightLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    if (this->moveCard != NULL) {
        
        bool isTake = false;
        for (int i = 0; i < this->player->fMap->mapCellArray.size(); i++) {
            Vec2 point = Vec2(0,0);
            point.x = this->player->fMap->mapCellArray.at(i)->position.x-this->player->fMap->getBoundingBox().size.width/8+this->player->fMap->getPosition().x+this->getPosition().x;
            point.y = this->player->fMap->mapCellArray.at(i)->position.y-this->player->fMap->getBoundingBox().size.width/8+this->player->fMap->getPosition().y+this->getPosition().y;
            Rect rect = Rect(point.x,point.y,this->player->fMap->getBoundingBox().size.width/4,this->player->fMap->getBoundingBox().size.width/4);
            //            printf("%f----x\n",this->currentMoveCard->cardSprite->getPosition().x+this->player->fMap->getPosition().x);
            //            printf("%f----y\n", this->currentMoveCard->cardSprite->getPosition().y+this->player->fMap->getPosition().y);
            if (rect.containsPoint(Vec2(this->moveCard->cardSprite->getPosition().x+this->player->fMap->getPosition().x, this->moveCard->cardSprite->getPosition().y+this->player->fMap->getPosition().y))) {
                isTake = true;
                
                Vec2 defaultCardPoint = Vec2(0, 0);
                for (int j = 0; j < this->player->fMap->mapCellArray.size(); j++) {
                    if (this->player->fMap->mapCellArray.at(j)->obj != NULL) {
                        
                        if (((Card*)this->player->fMap->mapCellArray.at(j)->obj)->cardName.compare(this->moveCard->cardName) == 0) {
                            defaultCardPoint = this->player->fMap->mapCellArray.at(j)->position;
                            this->player->fMap->mapCellArray.at(j)->obj = NULL;
                            break;
                        }
                    }
                }
                if (this->player->fMap->mapCellArray.at(i)->obj != NULL) {
                    if (defaultCardPoint == Vec2(0, 0)) {
                        
                        for (int n = 0; n < this->myAllData.size(); n++) {
                            if (this->myAllData.at(n)->card->cardName.compare(((Card*)this->player->fMap->mapCellArray.at(i)->obj)->cardName) == 0) {
                                this->myAllData.at(n)->xiaoSp->setOpacity(255);
                                ((Card*)this->player->fMap->mapCellArray.at(i)->obj)->cardSprite->removeFromParentAndCleanup(true);
                                ((Card*)this->player->fMap->mapCellArray.at(i)->obj)->cardSprite = NULL;
                                break;
                            }
                            
                        }
                    }else {
                        ((Card*)this->player->fMap->mapCellArray.at(i)->obj)->cardSprite->setPosition(defaultCardPoint);
                        ((Card*)this->player->fMap->mapCellArray.at(i)->obj)->cellIndex = this->moveCard->cellIndex;
                        this->player->fMap->mapCellArray.at(this->moveCard->cellIndex)->obj = ((Card*)this->player->fMap->mapCellArray.at(i)->obj);
                    }
                    
                }
                this->moveCard->cardSprite->setPosition(this->player->fMap->mapCellArray.at(i)->position);
                this->player->fMap->mapCellArray.at(i)->obj = this->moveCard;
                this->moveCard->cellIndex = i;
                break;
            }
        }
        if (isTake == false) {
            for (int j = 0; j < this->player->fMap->mapCellArray.size(); j++) {
                if (this->player->fMap->mapCellArray.at(j)->obj != NULL) {
                    
                    if (((Card*)this->player->fMap->mapCellArray.at(j)->obj)->cardName.compare(this->moveCard->cardName) == 0) {
                        
                        this->player->fMap->mapCellArray.at(j)->obj = NULL;
                        break;
                    }
                }
            }
            
            for (int i = 0; i < this->myAllData.size(); i++) {
                if (this->myAllData.at(i)->card->cardName.compare(this->moveCard->cardName) == 0) {
                    this->moveCard->cardSprite->removeFromParentAndCleanup(true);
                    this->moveCard->cardSprite = NULL;
                    
                    this->myAllData.at(i)->xiaoSp->setOpacity(255);
                    break;
                }
            }
            
        }
        
        for (int k = 0; k < this->myAllData.size(); k++) {
            this->myAllData.at(k)->cellIndex = this->myAllData.at(k)->card->cellIndex;
            //  printf("%s----%d\n",this->roleData.at(k)->card->cardName.c_str(),this->roleData.at(k)->cellIndex);
        }
    }

}

void PveFightLayer::startFightBtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        bool isHaveRole = false;
        for (int i = 0; i < this->myAllData.size(); i++) {
            if (this->myAllData.at(i)->card->cardSprite != NULL) {
                isHaveRole = true;
                break;
            }
        }
        if (isHaveRole == true) {
            this->upServerTakeRoleInfo();
        }
        
    }
}

void PveFightLayer::upServerTakeRoleInfo() {
    FightNetwork* net = FightNetwork::GetInstance();
    
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    rapidjson::Value cardsArray(rapidjson::kArrayType);
    rapidjson::Value cellsArray(rapidjson::kArrayType);
    rapidjson::Value tempKey;
    tempKey.SetString(myKey.c_str(), (unsigned int)strlen(myKey.c_str()));
    doc.AddMember("playerkey", tempKey, allocator);
    
    doc.AddMember("battleid", this->guaiWuID, allocator);
    for (int i = 0; i < this->myAllData.size(); i++) {
        if (this->myAllData.at(i)->card->cardSprite != NULL) {
            rapidjson::Value tempname;
            const char* aaa = this->myAllData.at(i)->card->cardName.c_str();
            tempname.SetString(aaa, ((unsigned int)strlen(aaa)));
            cardsArray.PushBack(tempname, allocator);
            cellsArray.PushBack(this->myAllData.at(i)->cellIndex, allocator);
        }

    }
    
    doc.AddMember("cards", cardsArray, allocator);
    doc.AddMember("cells", cellsArray, allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    
    net->createPostHttp(PveUpdataMyInfoPostUrl, this, httpresponse_selector(PveFightLayer::upResponse), buffer.GetString());
}

void PveFightLayer::upResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    if (response->isSucceed()) {
        std::vector<char>* info = response->getResponseData();
        std::string infoStr  = std::string(info->begin(),info->end());
        auto nextScene = FightLayer::createScene();
        FightLayer* layer = FightLayer::create();
        nextScene->addChild(layer);
        
        for (int i = 0; i < this->myAllData.size(); i++) {
            if (this->myAllData.at(i)->card->cardSprite != NULL) {
                CC_SAFE_RETAIN(this->myAllData.at(i)->card->cardSprite);
                this->myAllData.at(i)->card->cardSprite->removeFromParentAndCleanup(true);
            }
            this->myAllData.at(i)->card->release();
            //  nextLayer->roleData->pushBack(this->roleData.at(i));
        }
        layer->fightInfo = infoStr;
        layer->initFightLayer();
        // nextLayer->ID = 10;
        CC_SAFE_RETAIN(this->player);
        this->player->release();
        if (this->playerEnemy != NULL) {
            CC_SAFE_RETAIN(this->playerEnemy);
            this->playerEnemy->release();
        }
        
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, nextScene));
        
    }
}


