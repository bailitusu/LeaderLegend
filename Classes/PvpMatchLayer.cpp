//
//  PvpMatchLayer.cpp
//  OctLegend
//
//  Created by zc on 16/11/3.
//
//

#include "PvpMatchLayer.h"
#include "CommonFunc.h"
#include "Setting.h"
#include "PvpFightLayer.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "SetRoleFormatLayer.h"

#include "HouYiCard.h"
#include "ChangECard.h"
#include "TaoTieCard.h"
#include "XingTianCard.h"
#include "XuanWuCard.h"
#include "FengBoCard.h"
#include "FengHouCard.h"
#include "SuanYuCard.h"

Scene* PvpMatchLayer::createScene() {
    Scene* scene = Scene::create();
    return scene;
}

bool PvpMatchLayer::init() {
    this->isMatchingPvp = false;
    this->isTraining = false;
    return true;
}

void PvpMatchLayer::initMatchLayer() {
    this->background = Sprite::create("matchBg.jpg");//bbg_arena.png
    CommonFunc::setSpriteSize(this->background, screenSize.width);
    this->background->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height/2+origin.y));
    this->background->setLocalZOrder(-100);
    this->addChild(background);
    
    this->trainingBtn = ui::Button::create("classbtn.png");
    CommonFunc::initButton(this->trainingBtn, CC_CALLBACK_2(PvpMatchLayer::trainingBtnClick, this), screenSize.width/8, Vec2(screenSize.width/3, screenSize.height*0.4));
    this->trainingBtn->setTitleText("开始训练");
    this->trainingBtn->setTitleColor(Color3B(255, 255, 255));
    this->addChild(this->trainingBtn,100);
    
    this->pvpMatchBtn = ui::Button::create("classbtn.png");
    CommonFunc::initButton(this->pvpMatchBtn, CC_CALLBACK_2(PvpMatchLayer::pvpMatchBtnClick, this), screenSize.width/8, Vec2(screenSize.width*2/3, screenSize.height*0.4));
    this->pvpMatchBtn->setTitleText("开始匹配");
    this->pvpMatchBtn->setTitleColor(Color3B(255, 255, 255));
    this->addChild(this->pvpMatchBtn,100);
    
    this->pipeiLabel = Label::createWithTTF("", "fonts/楷体.ttf", 19);
    this->pipeiLabel->setContentSize(Size(80,30));
    this->pipeiLabel->setAlignment(TextHAlignment::CENTER);
    this->pipeiLabel->setTextColor(Color4B(0, 0, 255, 255));
    this->pipeiLabel->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height*0.65+origin.x));
    this->addChild(this->pipeiLabel,100);
}

void PvpMatchLayer::trainingBtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        if (this->isTraining == false) {
            rapidjson::Document doc;
            doc.SetObject();
            rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
            rapidjson::Value tempKey;
            tempKey.SetString(myKey.c_str(), (unsigned int)strlen(myKey.c_str()));
            doc.AddMember("playerkey", tempKey, allocator);
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            doc.Accept(writer);
            
            this->pipeiLabel->setString("训练匹配中。。。。");
            
            FightNetwork* net = FightNetwork::GetInstance();
            net->createPostHttp(PvpTrainingPostUrl, this, httpresponse_selector(PvpMatchLayer::trainingResponse), buffer.GetString());
            this->isTraining = true;
        }
    }
}

void PvpMatchLayer::pvpMatchBtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        if (this->isMatchingPvp == false) {
            rapidjson::Document doc;
            doc.SetObject();
            rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
            rapidjson::Value tempKey;
            tempKey.SetString(myKey.c_str(), (unsigned int)strlen(myKey.c_str()));
            doc.AddMember("playerkey", tempKey, allocator);
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            doc.Accept(writer);
            
            this->pipeiLabel->setString("PVP匹配中。。。。");
            
            FightNetwork* net = FightNetwork::GetInstance();
            net->createPostHttp(PvpMatchPostUrl, this, httpresponse_selector(PvpMatchLayer::matchResponse), buffer.GetString());
            this->isMatchingPvp = true;
        }
    }
}

void PvpMatchLayer::trainingResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    if (response->isSucceed()) {
      //  schedule(schedule_selector(PvpMatchLayer::checkIsMatchSuccess), 2.0);
        
        std::vector<char>* info = response->getResponseData();
        std::string infoStr  = std::string(info->begin(),info->end());
        this->analysisResponseData(infoStr, "training");
    }
}

void PvpMatchLayer::matchResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    if (response->isSucceed()) {
        scheduleOnce(schedule_selector(PvpMatchLayer::checkIsMatchSuccess), 1.0);
        
//        std::vector<char>* info = response->getResponseData();
//        std::string infoStr  = std::string(info->begin(),info->end());
        
        
    }
}

bool PvpMatchLayer::analysisResponseData(std::string infoStr,std::string reponseName) {
    rapidjson::Document doc;
    doc.Parse<0>(infoStr.c_str());
    if(doc.HasParseError())
    {
        printf("Match------%s\n",infoStr.c_str());
        printf("Match-----GetParseError%u\n", doc.GetParseError());
        return false;
    }
    int code = doc["code"].GetInt();
    if (code == 0) {
        rapidjson::Value& data = doc["data"];
        this->battleID = data["battlekey"].GetString();
        this->player1 = data["player1key"].GetString();
        this->player2 = data["player2key"].GetString();
        rapidjson::Value& cardsArray = data["cardkeys"];
        for (int i = 0; i < cardsArray.Size(); i++) {
            std::string tempName = cardsArray[i].GetString();
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
            roleData->isPvpBuShu = false;
            this->myData.pushBack(roleData);
        }
        this->pipeiLabel->setString("匹配成功");
        scheduleOnce(schedule_selector(PvpMatchLayer::enterNextScene), 0.5);
        return true;
    }else {
        if (reponseName.compare("pvp") == 0) {
            this->isMatchingPvp = false;
        }else if(reponseName.compare("training") == 0) {
            this->isTraining = false;
        }
        
        std::string message = doc["message"].GetString();
        // printf("-------%s--------",message.c_str());
        this->pipeiLabel->setString(message);
    }
    return false;
}

void PvpMatchLayer::enterNextScene(float dur) {
    
    auto pvpFightScene = PvpFightLayer::createScene();
    PvpFightLayer* fLayer = PvpFightLayer::create();
    fLayer->setContentSize(screenSize);
    pvpFightScene->addChild(fLayer);
    fLayer->player1Key = this->player1;
    fLayer->player2Key = this->player2;
    fLayer->battleKey = this->battleID;
    for (int i = 0; i < this->myData.size(); i++) {
        fLayer->myTakeRoleData.pushBack(this->myData.at(i));
    }
    fLayer->initPvpLayer();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, pvpFightScene));
}

void PvpMatchLayer::checkIsMatchSuccess(float dur) {
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
    net->createPostHttp(PvpMatchCheckOkPostUrl, this, httpresponse_selector(PvpMatchLayer::matchSuccessResponse), buffer.GetString());
}

void PvpMatchLayer::matchSuccessResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    if (response->isSucceed()) {
        std::vector<char>* info = response->getResponseData();
        std::string infoStr  = std::string(info->begin(),info->end());
       // unschedule(schedule_selector(PvpMatchLayer::checkIsMatchSuccess));
        if (this->analysisResponseData(infoStr, "pvp") == false) {
            scheduleOnce(schedule_selector(PvpMatchLayer::checkIsMatchSuccess), 1.0);
        }
        
    }
}
