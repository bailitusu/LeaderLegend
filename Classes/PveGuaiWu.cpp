//
//  PveGuaiWu.cpp
//  OctLegend
//
//  Created by zc on 16/11/2.
//
//

#include "PveGuaiWu.h"
#include "CommonFunc.h"
#include "Setting.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "HouYiCard.h"
#include "ChangECard.h"
#include "TaoTieCard.h"
#include "XingTianCard.h"
#include "XuanWuCard.h"
#include "FengBoCard.h"
#include "FengHouCard.h"
#include "SuanYuCard.h"
#include "PveGuaiWuInfoLayer.h"

bool PveGuaiWu::init() {
    return true;
}

void PveGuaiWu::createGuaiWu(Layer* layer,std::string imageName, cocos2d::Vec2 position,float width) {
    this->preLayer = layer;
    this->guaiWuBtn = ui::Button::create(imageName);
    CommonFunc::initButton(this->guaiWuBtn, CC_CALLBACK_2(PveGuaiWu::btnClick, this), width, position);
   // layer->addChild(this->guaiWuBtn,50);
}

void PveGuaiWu::btnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        FightNetwork* net = FightNetwork::GetInstance();
        char url[50] = {0};
        sprintf(url, PveGuaiWuInfoGetUrl,this->index);
        net->createGetHttp(url, this, httpresponse_selector(PveGuaiWu::responseBack));
    }

}

bool PveGuaiWu::analysisGuaiWuInfo(std::string info) {
    rapidjson::Document doc;
    doc.Parse<0>(info.c_str());
    if(doc.HasParseError())
    {
        printf("GuaiWuInfo-----GetParseError%u\n", doc.GetParseError());
        return false;
    }
    rapidjson::Value& data = doc["data"];
    rapidjson::Value& character = data["characters"];
    rapidjson::Value& cardsArray = character["cardkeys"];
    rapidjson::Value& cellsArray = character["cellids"];
    
    for (int i = 0; i < cardsArray.Size(); i++) {
        std::string cardName = cardsArray[i].GetString();
        int standIndex = cellsArray[i].GetInt();
        if (cardName.compare("houyi") == 0) {
            this->cardFormatGuaiWu(HouYiCard::create(), standIndex, NULL);
        }else if(cardName.compare("xuanwu") == 0) {
            this->cardFormatGuaiWu(XuanWuCard::create(), standIndex, NULL);
        }else if(cardName.compare("xingtian") == 0) {
            this->cardFormatGuaiWu(XingTianCard::create(), standIndex, NULL);
        }else if(cardName.compare("taotie") == 0) {
            this->cardFormatGuaiWu(TaoTieCard::create(), standIndex, NULL);
        }else if(cardName.compare("fenghou") == 0) {
            this->cardFormatGuaiWu(FengHouCard::create(), standIndex, NULL);
        }else if(cardName.compare("fengbo") == 0) {
            this->cardFormatGuaiWu(FengBoCard::create(), standIndex, NULL);
        }else if(cardName.compare("change") == 0) {
            this->cardFormatGuaiWu(ChangECard::create(), standIndex, NULL);
        }else if(cardName.compare("suanyu") == 0) {
            this->cardFormatGuaiWu(SuanYuCard::create(), standIndex, NULL);
        }
    }
    return true;
}

void PveGuaiWu::cardFormatGuaiWu(Card* card, int standIndex,Treasure* treasure) {
    
    card->initCardSprite(card->cardSpriteImageName+"_r0.png");
    //  this->player->setCardsPositon(card, standIndex,50);
    card->retain();
    
    auto roleData = SetRoleData::create();
    roleData->imageName = card->cardSpriteImageName+"_r0.png";
    roleData->cellIndex = standIndex;
//    roleData->magicGoods = treasure;
//    roleData->magicGoods->retain();
    roleData->card = card;
    roleData->noBring = false;
    this->guaiWuData.pushBack(roleData);
}

void PveGuaiWu::responseBack(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    if (response->isSucceed()) {
        std::vector<char>* info = response->getResponseData();
        std::string infoStr  = std::string(info->begin(),info->end());
        if(this->analysisGuaiWuInfo(infoStr)) {

            PveGuaiWuInfoLayer* infoLayer = PveGuaiWuInfoLayer::create();
            infoLayer->setContentSize(Size(400, 300));
            this->preLayer->addChild(infoLayer,300);
            infoLayer->setPosition(Vec2(screenSize.width/2-infoLayer->getBoundingBox().size.width/2, screenSize.height/2-infoLayer->getBoundingBox().size.height/2));
            infoLayer->guaiWuData = &this->guaiWuData;
            infoLayer->index = this->index;
            infoLayer->initPveGuaiWuLayer();
            
        }
    }
}


