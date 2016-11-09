//
//  PvpFightLayer.cpp
//  OctLegend
//
//  Created by zc on 16/11/3.
//
//

#include "PvpFightLayer.h"
#include "FightMap.h"
#include "CommonFunc.h"
#include "MapCell.h"
#include "Setting.h"
#include "FightProgress.h"
#include "Dragon/Dragon.h"
#include "Setting/ActionWait.h"
#include "FightNetwork.h"
#include "ReadRecordFight.h"
#include "PvpMatchLayer.h"

//std::string mykey = "zyh";
Scene* PvpFightLayer::createScene() {
    Scene* scene = Scene::create();
    return scene;
}

bool PvpFightLayer::init() {
    if (!Layer::init()) {
    
        return false;
    }
    this->roundNum = 0;
    return true;
}

void PvpFightLayer::initPvpLayer() {
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto liston = EventListenerTouchOneByOne::create();
    liston->onTouchBegan = CC_CALLBACK_2(PvpFightLayer::onTouchBegan, this);
    liston->onTouchMoved = CC_CALLBACK_2(PvpFightLayer::onTouchMoved, this);
    liston->onTouchEnded = CC_CALLBACK_2(PvpFightLayer::onTouchEnded, this);
    liston->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(liston, this);
    
    auto gameOverListon = EventListenerCustom::create("pvpGameOver", CC_CALLBACK_0(PvpFightLayer::gameOver, this));
    dispatcher->addEventListenerWithFixedPriority(gameOverListon, 1);
    
    auto roundOverListon = EventListenerCustom::create("pvpRoundOver", CC_CALLBACK_0(PvpFightLayer::roundOver, this));
    dispatcher->addEventListenerWithFixedPriority(roundOverListon, 1);
    
    this->player = FightPlayer::create();
    this->player->fpName = "player";
    this->player->fightLayer = this;
    this->player->initMap("leftmap.png", "left", Size(300,300));
    this->player->fMap->setPosition(10+origin.x, 40+origin.y);
    this->player->fMap->setLocalZOrder(300);
    this->player->initDragon("dragon_left.png");
    this->player->fDragon->dragonSprite->setPosition(150+origin.x,screenSize.height+origin.y);
    
    this->playerEnemy = FightPlayer::create();
    this->playerEnemy->fpName = "enemyPlayer";
    this->playerEnemy->fightLayer = this;
    this->playerEnemy->initMap("rightmap.png", "right", Size(300,300));
    this->playerEnemy->fMap->setPosition(screenSize.width-(this->playerEnemy->fMap->getBoundingBox().size.width+10+origin.x),40+origin.y);
    this->playerEnemy->fMap->setLocalZOrder(300);
    this->playerEnemy->initDragon("dragon_right.png");
    this->playerEnemy->fDragon->dragonSprite->setPosition(screenSize.width-150+origin.x,screenSize.height+origin.y);
    
    this->player->enemy = this->playerEnemy;
    this->playerEnemy->enemy = this->player;
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
    CommonFunc::initButton(this->chouTiBtn, CC_CALLBACK_2(PvpFightLayer::chouTibtnClick, this), screenSize.width*0.072, Vec2(screenSize.width, screenSize.height*0.072));
    this->addChild(this->chouTiBtn,200);
    
    this->initChouTiLayer();
    this->roundLabel = Label::createWithTTF("", "fonts/楷体.ttf", 19);
    this->roundLabel->setContentSize(Size(80,30));
    this->roundLabel->setAlignment(TextHAlignment::CENTER);
    this->roundLabel->setTextColor(Color4B(0, 0, 255, 255));
    this->roundLabel->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height-20));
    this->addChild(this->roundLabel,100);
    
}

void PvpFightLayer::chouTibtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
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

void PvpFightLayer::initChouTiLayer() {
    this->chouTiLayer = Layer::create();
    this->chouTiLayer->setContentSize(Size(screenSize.width*0.46, screenSize.height*0.75));
    this->chouTiLayer->setPosition(Vec2(screenSize.width, screenSize.height/2-this->chouTiLayer->getBoundingBox().size.height/2));
    this->addChild(chouTiLayer,100);
    
    Sprite* bg = Sprite::create("buzhenBg2.jpg");

    CommonFunc::setShowAllSpriteSize(bg, this->chouTiLayer->getBoundingBox().size.width, this->chouTiLayer->getBoundingBox().size.height);
    bg->setPosition(this->chouTiLayer->getBoundingBox().size.width/2,this->chouTiLayer->getBoundingBox().size.height/2);
    this->chouTiLayer->addChild(bg, -100);
    
    for (int i = 0; i < this->myTakeRoleData.size(); i++) {
        Sprite* gezi = Sprite::create("herotouxiangbg.png");
        CommonFunc::setShowAllSpriteSize(gezi, this->chouTiLayer->getBoundingBox().size.width/4-5, this->chouTiLayer->getBoundingBox().size.width/4-5);
        gezi->setPosition(Vec2(8+this->chouTiLayer->getBoundingBox().size.width/8+(this->chouTiLayer->getBoundingBox().size.width/4-5)*(i%4), this->chouTiLayer->getBoundingBox().size.height-(this->chouTiLayer->getBoundingBox().size.height/8+this->chouTiLayer->getBoundingBox().size.height/4*(i/4))-10 ));
        this->chouTiLayer->addChild(gezi,100);
        
        this->myTakeRoleData.at(i)->xiaoSp = Sprite::create(this->myTakeRoleData.at(i)->xiaoImageName);
        CommonFunc::setShowAllSpriteSize(this->myTakeRoleData.at(i)->xiaoSp, this->chouTiLayer->getBoundingBox().size.width/4-14, this->chouTiLayer->getBoundingBox().size.width/4-14);
        this->myTakeRoleData.at(i)->xiaoSp->setPosition(gezi->getPosition());
        this->chouTiLayer->addChild(this->myTakeRoleData.at(i)->xiaoSp,150);
    }
    
    this->buShuOverBtn = ui::Button::create("classbtn.png");
    CommonFunc::initButton(this->buShuOverBtn, CC_CALLBACK_2(PvpFightLayer::buShubtnClick, this), screenSize.width/8, Vec2(screenSize.width*0.06, screenSize.height*0.075));
    this->buShuOverBtn->setTitleText("部署完成");
    this->buShuOverBtn->setTitleColor(Color3B(255, 255, 255));
    this->addChild(this->buShuOverBtn,100);
}

void PvpFightLayer::buShubtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        
        if (this->chouTiLayer->getPosition().x < screenSize.width) {
            
            auto moveIn = MoveTo::create(0.2f, Vec2(screenSize.width, this->chouTiLayer->getPosition().y));
            moveIn->setTag(10);
            
            this->chouTiLayer->runAction(moveIn);
        }
        this->chouTiBtn->setTouchEnabled(false);
        
        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
        rapidjson::Value playerKey;
        rapidjson::Value battleKey;
        rapidjson::Value cardsArray(rapidjson::kArrayType);
        rapidjson::Value cellsArray(rapidjson::kArrayType);
        
        playerKey.SetString(myKey.c_str(), (unsigned int)strlen(myKey.c_str()));
        
        battleKey.SetString(this->battleKey.c_str(), (unsigned int)strlen(this->battleKey.c_str()));
        doc.AddMember("playerkey", playerKey, allocator);
        doc.AddMember("battlekey", battleKey, allocator);
        
        rapidjson::Value cardName;
        for (int i = 0; i < this->myTakeRoleData.size(); i++) {
            if (this->myTakeRoleData.at(i)->card->cardSprite != NULL && this->myTakeRoleData.at(i)->isPvpBuShu == false) {
                const char* tempName = this->myTakeRoleData.at(i)->card->cardName.c_str();
                cardName.SetString(tempName, (unsigned int)strlen(tempName));
                cardsArray.PushBack(cardName, allocator);
                cellsArray.PushBack(this->myTakeRoleData.at(i)->cellIndex, allocator);
                this->myTakeRoleData.at(i)->isPvpBuShu = true;
            }
        }
        printf("%d",cardsArray.Size());
        doc.AddMember("cardkeys", cardsArray, allocator);
        doc.AddMember("cellids", cellsArray, allocator);
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);
        
        FightNetwork* net = FightNetwork::GetInstance();
        printf("%s/n",buffer.GetString());
        net->createPostHttp(PvpBushuPostUrl, this, httpresponse_selector(PvpFightLayer::buShuResponse), buffer.GetString());
    }

}

void PvpFightLayer::buShuResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    if (response->isSucceed()) {
        
        
        std::vector<char>* info = response->getResponseData();
        std::string infoStr  = std::string(info->begin(),info->end());
        rapidjson::Document doc;
        doc.Parse<0>(infoStr.c_str());
        if(doc.HasParseError())
        {
            printf("bushu-----GetParseError%u\n", doc.GetParseError());
            return;
        }
        int code = doc["code"].GetInt();
        if (code == 0) {
            scheduleOnce(schedule_selector(PvpFightLayer::checkFightOk), 1.5);
//            for (int i = 0; i < 3; i++) {
//
//            }
          //  this->checkFightOk(10);
        }else {
            std::string message = doc["message"].GetString();
             printf("-------%s--------",message.c_str());
        }
    }
}

void PvpFightLayer::checkFightOk(float dur) {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    rapidjson::Value tempKey;
    tempKey.SetString(myKey.c_str(), (unsigned int)strlen(myKey.c_str()));
    doc.AddMember("playerkey", tempKey, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    
    FightNetwork* net = FightNetwork::GetInstance();
    net->createPostHttp(PvpCheckBushuOkPostUrl, this, httpresponse_selector(PvpFightLayer::checkFightResponse), buffer.GetString());
}

void PvpFightLayer::checkFightResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    if (response->isSucceed()) {
        std::vector<char>* info = response->getResponseData();
        std::string infoStr  = std::string(info->begin(),info->end());
     //   printf("%s", infoStr.c_str());
        rapidjson::Document doc;
        doc.Parse<0>(infoStr.c_str());
        if(doc.HasParseError())
        {
            printf("message-----GetParseError%u\n", doc.GetParseError());
            return;
        }
        int code = doc["code"].GetInt();
        if (code == 0) {
          //  unschedule(schedule_selector(PvpFightLayer::checkFightOk));
            for (int i = 0; i < this->myTakeRoleData.size(); i++) {
                if(this->myTakeRoleData.at(i)->card->cardSprite != NULL) {
                    this->myTakeRoleData.at(i)->card->cardSprite->removeFromParentAndCleanup(true);
                    this->myTakeRoleData.at(i)->card->cardSprite = NULL;
                }
            }
            ReadRecordFight* rf = ReadRecordFight::getInstance();
            if (rf->player == NULL) {
                rf->player = this->player;
            }
            if (rf->playerEnemy == NULL) {
                rf->playerEnemy = this->playerEnemy;
            }
            rf->currentSmallIndex = 0;
            rf->currentBigIndex = -1;
            rf->currentDragonIndex = 0;
            rf->currentJson = infoStr.c_str();
            rf->gameOverLabel = this->roundLabel;
            rf->readPlayerInfo();
            rf->readBigNextRecord();
            this->roundNum++;
            char rnum[10] = {0};
  
            sprintf(rnum, "第%d回合",this->roundNum);
            this->roundLabel->setString(rnum);
        }else {
            scheduleOnce(schedule_selector(PvpFightLayer::checkFightOk), 1.5);
            std::string message = doc["message"].GetString();
            printf("-----------%s----------/n",message.c_str());
        }

    }else {
        scheduleOnce(schedule_selector(PvpFightLayer::checkFightOk), 1.5);
    }
    

}

void PvpFightLayer::roundOver() {
    this->chouTiBtn->setTouchEnabled(true);
}

void PvpFightLayer::gameOver() {
    scheduleOnce(schedule_selector(PvpFightLayer::enterMatchScene), 1.0);
}

void PvpFightLayer::enterMatchScene(float dur) {
    auto matchScene = PvpMatchLayer::createScene();
    PvpMatchLayer* layer = PvpMatchLayer::create();
    layer->setContentSize(screenSize);
    matchScene->addChild(layer);
    layer->initMatchLayer();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, matchScene));
}

Vec2 PvpFightLayer::countCardOrigonPoint(Card *card, FightPlayer *tempPlayer) {
    Vec2 point = Vec2(0, 0);
    point.x = card->cardSprite->getPosition().x-tempPlayer->fMap->getBoundingBox().size.width/8+tempPlayer->fMap->getPosition().x+this->getPosition().x;
    point.y = card->cardSprite->getPosition().y-tempPlayer->fMap->getBoundingBox().size.width/8+tempPlayer->fMap->getPosition().y+this->getPosition().y;
    return point;
}

bool PvpFightLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    auto touchLocation = touch->getLocationInView();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    
    for (int i = 0; i < this->myTakeRoleData.size(); i++) {
        auto xiaoCardPoint = Vec2(this->myTakeRoleData.at(i)->xiaoSp->getPosition().x-this->myTakeRoleData.at(i)->xiaoSp->getBoundingBox().size.width/2, this->myTakeRoleData.at(i)->xiaoSp->getPosition().y-this->myTakeRoleData.at(i)->xiaoSp->getBoundingBox().size.height/2);
        xiaoCardPoint = xiaoCardPoint+this->chouTiLayer->getPosition();
        Rect rect = Rect(xiaoCardPoint.x,xiaoCardPoint.y,this->myTakeRoleData.at(i)->xiaoSp->getBoundingBox().size.width,this->myTakeRoleData.at(i)->xiaoSp->getBoundingBox().size.height);
        
        if (rect.containsPoint(touchLocation)) {
            if (this->myTakeRoleData.at(i)->xiaoSp->getOpacity() > 125 ) {
                this->myTakeRoleData.at(i)->card->initCardSprite(this->myTakeRoleData.at(i)->imageName);
                auto point = Vec2(xiaoCardPoint.x+this->myTakeRoleData.at(i)->xiaoSp->getBoundingBox().size.width/2,xiaoCardPoint.y+this->myTakeRoleData.at(i)->xiaoSp->getBoundingBox().size.height/2);
                this->myTakeRoleData.at(i)->card->cardSprite->setPosition(point-this->player->fMap->getPosition());
                this->player->fMap->addChild(this->myTakeRoleData.at(i)->card->cardSprite,150);
                this->myTakeRoleData.at(i)->xiaoSp->setOpacity(125);

                break;
            }
        }
    }
    
    for (int i = 0; i < this->myTakeRoleData.size(); i++) {
        if (this->myTakeRoleData.at(i)->card->cardSprite != NULL && this->myTakeRoleData.at(i)->isPvpBuShu == false) {
            auto tempPoint = this->countCardOrigonPoint(this->myTakeRoleData.at(i)->card,this->player);
            Rect rect = Rect(tempPoint.x, tempPoint.y, this->player->fMap->getBoundingBox().size.width/4, this->player->fMap->getBoundingBox().size.width/4);
            if (rect.containsPoint(touchLocation)) {
                if (this->myTakeRoleData.at(i)->isPvpBuShu == false) {
                    this->moveCard = this->myTakeRoleData.at(i)->card;
                }
                
                //     printf("%s",this->currentMoveCard->cardName.c_str());
                // schedule(schedule_selector(SetRoleFormatlayer::showInfo), 1.0);
                return true;
            }
        }
    }
    this->moveCard = NULL;
    return true;
}

void PvpFightLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    if (this->moveCard != NULL) {
        auto point = Director::getInstance()->convertToGL(touch->getLocationInView());
        auto oldPoint = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
        auto distance = point-oldPoint;
        this->moveCard->cardSprite->setPosition(this->moveCard->cardSprite->getPosition()+distance);
  
    }
}

void PvpFightLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
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
   
                        for (int n = 0; n < this->myTakeRoleData.size(); n++) {
                            if (this->myTakeRoleData.at(n)->card->cardName.compare(((Card*)this->player->fMap->mapCellArray.at(i)->obj)->cardName) == 0) {
                                this->myTakeRoleData.at(n)->xiaoSp->setOpacity(255);
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
            
            for (int i = 0; i < this->myTakeRoleData.size(); i++) {
                if (this->myTakeRoleData.at(i)->card->cardName.compare(this->moveCard->cardName) == 0) {
                    this->moveCard->cardSprite->removeFromParentAndCleanup(true);
                    this->moveCard->cardSprite = NULL;

                    this->myTakeRoleData.at(i)->xiaoSp->setOpacity(255);
                    break;
                }
            }
 
        }
        
        for (int k = 0; k < this->myTakeRoleData.size(); k++) {
            this->myTakeRoleData.at(k)->cellIndex = this->myTakeRoleData.at(k)->card->cellIndex;
            //  printf("%s----%d\n",this->roleData.at(k)->card->cardName.c_str(),this->roleData.at(k)->cellIndex);
        }
    }

}

