//
//  ReadRecordFight.cpp
//  OctLegend
//
//  Created by zc on 16/9/8.
//
//

#include "ReadRecordFight.h"
#include "RecordFight.h"
#include "FightPlayer.h"

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
#include "BingFaTreasure.h"
#include "YiBingBuDao.h"
#include "MianYiCuoZhiTreasure.h"
#include "FanTanWuLiTreasure.h"
#include "FanTanFaShuTreasure.h"
#include "HuFuTreasure.h"
#include "SetRoleFormatLayer.h"
bool ReadRecordFight::init() {
    this->currentIndex = 0;
    return true;
}

void ReadRecordFight::readRecordFormMenmory() {
    this->currentJson = RecordFight::GetInstance()->currentJson;
    
    for (int i = 0; i < this->roleData->size(); i++) {
       // this->player->initTackCard(this->roleData->at(i)->card, this->roleData->at(i)->imageName, this->roleData->at(i)->cellIndex, "player",this->roleData->at(i)->magicGoods);
        if (this->roleData->at(i)->card->cardName.compare("houyi") == 0) {
            this->player->initTackCard(HouYiCard::create(), this->roleData->at(i)->imageName, this->roleData->at(i)->cellIndex, "player",this->roleData->at(i)->magicGoods);
        }else if (this->roleData->at(i)->card->cardName.compare("change") == 0) {
            this->player->initTackCard(ChangECard::create(), this->roleData->at(i)->imageName, this->roleData->at(i)->cellIndex, "player",this->roleData->at(i)->magicGoods);
        }else if (this->roleData->at(i)->card->cardName.compare("xingtian") == 0) {
            this->player->initTackCard(XingTianCard::create(), this->roleData->at(i)->imageName, this->roleData->at(i)->cellIndex, "player",this->roleData->at(i)->magicGoods);
        }else if (this->roleData->at(i)->card->cardName.compare("taotie") == 0) {
            this->player->initTackCard(TaoTieCard::create(), this->roleData->at(i)->imageName, this->roleData->at(i)->cellIndex, "player",this->roleData->at(i)->magicGoods);
        }else if (this->roleData->at(i)->card->cardName.compare("fenghou") == 0) {
            this->player->initTackCard(FengHouCard::create(), this->roleData->at(i)->imageName, this->roleData->at(i)->cellIndex, "player",this->roleData->at(i)->magicGoods);
        }else if (this->roleData->at(i)->card->cardName.compare("fengbo") == 0) {
            this->player->initTackCard(FengBoCard::create(), this->roleData->at(i)->imageName, this->roleData->at(i)->cellIndex, "player",this->roleData->at(i)->magicGoods);
        }else if (this->roleData->at(i)->card->cardName.compare("suanyu") == 0) {
            this->player->initTackCard(SuanYuCard::create(), this->roleData->at(i)->imageName, this->roleData->at(i)->cellIndex, "player",this->roleData->at(i)->magicGoods);
        }else if (this->roleData->at(i)->card->cardName.compare("xuanwu") == 0) {
            this->player->initTackCard(XuanWuCard::create(), this->roleData->at(i)->imageName, this->roleData->at(i)->cellIndex, "player",this->roleData->at(i)->magicGoods);
        }
    }
    
//    this->player->initTackCard(XingTianCard::create(), "jiansheng_stand_0.png", 3, "player",DunJiaTianShu::create());
//    this->player->initTackCard(ChangECard::create(), "bingnv_stand_0.png", 5, "player",DunJiaTianShu::create());
//    this->player->initTackCard(TaoTieCard::create(), "panda_stand_0.png", 6, "player",DunJiaTianShu::create());
//    this->player->initTackCard(FengHouCard::create(), "gugong_stand_0.png", 9, "player",DunJiaTianShu::create());
//    this->player->initTackCard(FengBoCard::create(), "zhousi_stand_0.png", 10, "player",DunJiaTianShu::create());
//    this->player->initTackCard(HouYiCard::create(), "xiaohei_stand_0.png", 12, "player",DunJiaTianShu::create());
//    this->player->initTackCard(SuanYuCard::create(), "fengxing_stand_0.png", 15, "player",DunJiaTianShu::create());

    this->player->initCardStandArray();

    this->playerEnemy->initTackCard(XuanWuCard::create(), "niutou_stand_r0.png", 0, "enemyPlayer",DunJiaTianShu::create());
    this->playerEnemy->initTackCard(XingTianCard::create(), "jiansheng_stand_r0.png", 3, "enemyPlayer",DunJiaTianShu::create());
    this->playerEnemy->initTackCard(ChangECard::create(),"bingnv_stand_r0.png" , 5, "enemyPlayer",DunJiaTianShu::create());
    this->playerEnemy->initTackCard(TaoTieCard::create(), "panda_stand_r0.png", 6, "enemyPlayer",DunJiaTianShu::create());
    this->playerEnemy->initTackCard(FengHouCard::create(), "gugong_stand_r0.png", 9, "enemyPlayer",DunJiaTianShu::create());
    this->playerEnemy->initTackCard(FengBoCard::create(), "zhousi_stand_r0.png", 10, "enemyPlayer",DunJiaTianShu::create());
    this->playerEnemy->initTackCard(HouYiCard::create(), "xiaohei_stand_r0.png", 12, "enemyPlayer",DunJiaTianShu::create());
    this->playerEnemy->initTackCard(SuanYuCard::create(), "fengxing_stand_r0.png", 15, "enemyPlayer",DunJiaTianShu::create());
    this->playerEnemy->initCardStandArray();
    
    for (int i = 0; i < 8; i++) {
        this->player->cardArray.at(i)->readRecordFight = this;
        this->playerEnemy->cardArray.at(i)->readRecordFight = this;
    }
    
    
}

Card* ReadRecordFight::getCardFromIndex(int cardStandIndex, FightPlayer* fplayer) {
    for (int i = 0; i < fplayer->fMap->mapCellArray.size(); i++) {
        if ((Card*)fplayer->fMap->mapCellArray.at(i)->obj != NULL ) {
            if(((Card*)fplayer->fMap->mapCellArray.at(i)->obj)->cellIndex == cardStandIndex) {
                return ((Card*)fplayer->fMap->mapCellArray.at(i)->obj);
            }
        }
    }
    return NULL;
    
    
//    for (int i = 0; i < fplayer->cardArray.size(); i++) {
//        if (fplayer->cardArray.at(i)->cardName.compare(cardName) == 0) {
//            return fplayer->cardArray.at(i);
//        }
//    }
//    return NULL;
}


void ReadRecordFight::readNextFightRecord() {
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    doc.Parse<0>(this->currentJson.c_str());
 //   printf("%d", this->currentIndex);
    if(doc.HasParseError())
    {
        printf("GetParseError%u\n", doc.GetParseError());
        return;
    }
    if (!doc.IsObject()) {
        return;
    }
    rapidjson::Value& fightArray = doc["fightArray"];
    if (this->currentIndex >= fightArray.Size()) {
        return;
    }
    rapidjson::Value& item = fightArray[this->currentIndex];
    rapidjson::Value& cardName = item["cardname"];
    std::string playerName = item["playername"].GetString();
    Card* card;
    OneRecord* oneRecordInfo = OneRecord::create();
    
    if (playerName.compare("player") == 0) {
        card = this->getCardFromIndex(item["standindex"].GetInt(), this->player);
      //  printf("%s--------%s----%d------HP:%d\n",playerName.c_str(),item["cardname"].GetString() ,item["standindex"].GetInt(),item["currentHP"].GetInt());
    }else if(playerName.compare("enemyPlayer") == 0) {
        card = this->getCardFromIndex(item["standindex"].GetInt() ,this->playerEnemy);
      //  printf("%s--------%s----%d------HP:%d\n",playerName.c_str(),item["cardname"].GetString(), item["standindex"].GetInt(),item["currentHP"].GetInt());
    }
   // card->readRecordFight = this;
    card->willRun(card->forPlayer->enemy);
    
    rapidjson::Value& affectArray = item["affectArray"];
    if (!affectArray.IsArray()) {
        return;
    }
    Vector<OneRecord*> tempRecordVector;
    for (int i = 0; i < affectArray.Size(); i++) {
        OneRecord* oneInfo = OneRecord::create();
        oneInfo->isShanBi = affectArray[i]["isshanbi"].GetBool();
        oneInfo->hitValue = affectArray[i]["hitvalue"].GetDouble();
        oneInfo->isBaoJi = affectArray[i]["isbaoji"].GetBool();
        oneInfo->isGeDang = affectArray[i]["isgedang"].GetBool();
        oneInfo->fanTanWuLiHartValue = affectArray[i]["fantanwuli"].GetDouble();
        oneInfo->fanTanFaShuHartValue = affectArray[i]["fantanfashu"].GetDouble();
        oneInfo->playerName = affectArray[i]["playername"].GetString();
        oneInfo->zhiLiao = affectArray[i]["zhiliao"].GetDouble();
        if (oneInfo->playerName.compare("player") == 0) {
            oneInfo->card = this->getCardFromIndex(affectArray[i]["standindex"].GetInt() ,this->player);
        }else if(oneInfo->playerName.compare("enemyPlayer") == 0){
            oneInfo->card = this->getCardFromIndex(affectArray[i]["standindex"].GetInt() ,this->playerEnemy);
 
        }
    //    oneInfo->enemyNuQiChange = affectArray[i]["enemynuqichange"].GetInt();
        tempRecordVector.pushBack(oneInfo);
    }
    oneRecordInfo->affectRecordArray = tempRecordVector;
    if(item["xiaozhao"].GetBool() == true ) {
        
        oneRecordInfo->isLianJi = item["islianji"].GetBool();
        oneRecordInfo->hitTarget = item["hittarget"].GetInt();
        card->xiaoSkll(oneRecordInfo);
       // card->xiaoSkll(<#OneRecord *info#>);
    }else if (item["dazhao"].GetBool() == true) {
        oneRecordInfo->hitTarget = item["hittarget"].GetInt();
        card->daSkill(oneRecordInfo);
    }
    card->endRun(card->forPlayer->enemy);
    this->currentIndex++;
    
    
}