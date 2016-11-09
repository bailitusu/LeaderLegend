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



#include "Dragon.h"
#include "DunJiaTianShu.h"
#include "BingFaTreasure.h"
#include "YiBingBuDao.h"
#include "MianYiCuoZhiTreasure.h"
#include "FanTanWuLiTreasure.h"
#include "FanTanFaShuTreasure.h"
#include "HuFuTreasure.h"
#include "SetRoleFormatLayer.h"



ReadRecordFight* ReadRecordFight::readFight = NULL;

ReadRecordFight* ReadRecordFight::getInstance() {
    if (readFight == NULL) {
        readFight = ReadRecordFight::create();
        readFight->retain();
        return readFight;
    }
    return readFight;
}

bool ReadRecordFight::init() {
    this->currentSmallIndex = 0;
    this->currentBigIndex = -1;
    this->currentDragonIndex = 0;
    return true;
}

void ReadRecordFight::readPlayerInfo() {
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    doc.Parse<0>(this->currentJson.c_str());
    if(doc.HasParseError())
    {
        printf("GetParseError%u\n", doc.GetParseError());
        return;
    }
    if (!doc.IsObject()) {
        return;
    }

    rapidjson::Value& dataArray = doc["data"];
   // rapidjson::Value& aaa = doc["rounds"];
    rapidjson::Value player1;
    rapidjson::Value player2;
    if (dataArray.IsObject()) {
        player1 = dataArray["player1"];
        player2 = dataArray["player2"];
    }else {
        player1 = dataArray[0]["player1"];
        player2 = dataArray[0]["player2"];
    }

    rapidjson::Value& pOneCardArray = player1["cardkeys"];
    rapidjson::Value& pTwoCardArray = player2["cardkeys"];
    
    rapidjson::Value& pOneCardCellArray = player1["cellids"];
    rapidjson::Value& pTwoCardCellArray = player2["cellids"];
    std::string player1Key = player1["playerkey"].GetString();
    std::string player2Key = player2["playerkey"].GetString();
    std::string cardName;
    int cellIndex;
    std::string imageName;
    if (player1Key.compare(myKey) == 0) {
    //    printf("one--------%d", pOneCardArray.Size());
        for (int i = 0; i < pOneCardArray.Size(); i++) {
            cardName = pOneCardArray[i].GetString();
            cellIndex = pOneCardCellArray[i].GetInt();
            imageName = "_stand_l0.png";
            this->initPlayerCard(this->player,cardName, imageName, cellIndex, "player");

        }
        this->player->initCardStandArray();
      //  printf("enemy--------%d", pTwoCardArray.Size());
        for (int i = 0; i < pTwoCardArray.Size(); i++) {
            cardName = pTwoCardArray[i].GetString();
            cellIndex = pTwoCardCellArray[i].GetInt();
            imageName = "_stand_r0.png";
            this->initPlayerCard(this->playerEnemy,cardName, imageName, cellIndex, "enemyPlayer");
        }
        this->playerEnemy->initCardStandArray();
    }else if(player2Key.compare(myKey) == 0) {
        
        for (int i = 0; i < pTwoCardArray.Size(); i++) {
            cardName = pTwoCardArray[i].GetString();
            cellIndex = pTwoCardCellArray[i].GetInt();
            imageName = "_stand_l0.png";
            this->initPlayerCard(this->player,cardName, imageName, cellIndex, "player");
            
        }
        this->player->initCardStandArray();
        
        for (int i = 0; i < pOneCardArray.Size(); i++) {
            cardName = pOneCardArray[i].GetString();
            cellIndex = pOneCardCellArray[i].GetInt();
            imageName = "_stand_r0.png";
            this->initPlayerCard(this->playerEnemy,cardName, imageName, cellIndex, "enemyPlayer");
        }
        this->playerEnemy->initCardStandArray();
    }
    
    for (int i = 0; i < 16; i++) {  //最多16个人
        if (i < this->player->cardArray.size()) {
            this->player->cardArray.at(i)->readRecordFight = this;
        }
        if (i < this->playerEnemy->cardArray.size()) {
            this->playerEnemy->cardArray.at(i)->readRecordFight = this;
        }
        
    }
    this->player->fDragon->readRecordFight = this;
    this->playerEnemy->fDragon->readRecordFight = this;
    
}



void ReadRecordFight::initPlayerCard(FightPlayer* tempPlayer, std::string cardName,std::string imageName, int cellIndex, std::string pName) {
    
    


    if (cardName.compare("houyi") == 0) {
        imageName = "xiaohei"+imageName;
        tempPlayer->initTackCard(HouYiCard::create(), imageName, cellIndex, pName,NULL);
    }else if (cardName.compare("change") == 0) {
        imageName = "bingnv"+imageName;
        tempPlayer->initTackCard(ChangECard::create(), imageName, cellIndex, pName,NULL);
    }else if (cardName.compare("xingtian") == 0) {
        imageName = "jiansheng"+imageName;
        tempPlayer->initTackCard(XingTianCard::create(), imageName, cellIndex, pName,NULL);
    }else if (cardName.compare("taotie") == 0) {
        imageName = "panda"+imageName;
        tempPlayer->initTackCard(TaoTieCard::create(), imageName, cellIndex, pName,NULL);
    }else if (cardName.compare("fenghou") == 0) {
        imageName = "gugong"+imageName;
        tempPlayer->initTackCard(FengHouCard::create(), imageName, cellIndex, pName,NULL);
    }else if (cardName.compare("fengbo") == 0) {
        imageName = "zhousi"+imageName;
        tempPlayer->initTackCard(FengBoCard::create(), imageName, cellIndex, pName,NULL);
    }else if (cardName.compare("suanyu") == 0) {
        imageName = "fengxing"+imageName;
        tempPlayer->initTackCard(SuanYuCard::create(), imageName, cellIndex, pName,NULL);
    }else if (cardName.compare("xuanwu") == 0) {
        imageName = "niutou"+imageName;
        tempPlayer->initTackCard(XuanWuCard::create(), imageName, cellIndex, pName,NULL);
    }
}

void ReadRecordFight::readRecordFormMenmory() {
  //  this->currentJson = RecordFight::GetInstance()->currentJson;
    
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
    
//    this->player->initTackCard(XuanWuCard::create(), "niutou_stand_l0.png", 0, "player",DunJiaTianShu::create());
//    this->player->initTackCard(XingTianCard::create(), "jiansheng_stand_l0.png", 3, "player",DunJiaTianShu::create());
//    this->player->initTackCard(ChangECard::create(), "bingnv_stand_l0.png", 5, "player",DunJiaTianShu::create());
//    this->player->initTackCard(TaoTieCard::create(), "panda_stand_l0.png", 6, "player",DunJiaTianShu::create());
//    this->player->initTackCard(FengHouCard::create(), "gugong_stand_l0.png", 9, "player",DunJiaTianShu::create());
//    this->player->initTackCard(FengBoCard::create(), "zhousi_stand_l0.png", 10, "player",DunJiaTianShu::create());
//    this->player->initTackCard(HouYiCard::create(), "xiaohei_stand_l0.png", 12, "player",DunJiaTianShu::create());
//    this->player->initTackCard(SuanYuCard::create(), "fengxing_stand_l0.png", 15, "player",DunJiaTianShu::create());

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
        if (i < this->player->cardArray.size()) {
            this->player->cardArray.at(i)->readRecordFight = this;
        }
        
        this->playerEnemy->cardArray.at(i)->readRecordFight = this;
    }
    
   //  CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("battle_bgm.mp3",true);
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

bool DragonData::init() {
    return true;
}



void ReadRecordFight::readDragonInfo() {

    
    
}

void ReadRecordFight::showGameOver(std::string winner) {
    this->gameOverLabel->setString(winner+"  is  winner!!");
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    EventCustom event = EventCustom("pvpGameOver");
    dispatcher->dispatchEvent(&event);
}



void ReadRecordFight::readBigNextRecord() {
    rapidjson::Document doc;
    doc.Parse<0>(this->currentJson.c_str());
    if(doc.HasParseError())
    {
        printf("big next GetParseError%u\n", doc.GetParseError());
        return;
    }
    if (!doc.IsObject()) {
        return;
    }
    rapidjson::Value& dataArray = doc["data"];
    rapidjson::Value roundArray;
    if (dataArray.IsObject()) {
        roundArray = dataArray["rounds"];
    }else {
        roundArray = dataArray[0]["rounds"];
    }
//    rapidjson::Value& roundArray = dataArray[0]["rounds"];
    this->currentBigIndex++;
    if (this->currentBigIndex >= roundArray.Size()) {
        if (dataArray.IsArray() == true) {

            if (dataArray.Size() == 2) {
                rapidjson::Value& result = dataArray[1];
                if (result.HasMember("isgameover") == true) {
                    bool isover = result["isgameover"].GetBool();
                    if (isover == true) {
                        this->showGameOver(result["winner"].GetString());
                        return;
                    }
                }else {
                    auto dispatcher = Director::getInstance()->getEventDispatcher();
                    EventCustom event = EventCustom("pvpRoundOver");
                    dispatcher->dispatchEvent(&event);
                }

            }else {
                auto dispatcher = Director::getInstance()->getEventDispatcher();
                EventCustom event = EventCustom("pvpRoundOver");
                dispatcher->dispatchEvent(&event);
            }
        }
        return;
    }else {
        this->readNextDragon();
    }
}

void ReadRecordFight::readNextDragon() {
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    doc.Parse<0>(this->currentJson.c_str());
    if(doc.HasParseError())
    {
        printf("next dragon GetParseError%u\n", doc.GetParseError());
        return;
    }
    if (!doc.IsObject()) {
        return;
    }
    rapidjson::Value& dataArray = doc["data"];
    rapidjson::Value dragonArray;
    if (dataArray.IsObject()) {
        dragonArray = dataArray["guardians"];
    }else {
        dragonArray = dataArray[0]["guardians"];
    }
//    rapidjson::Value& dragonArray = dataArray[0]["guardians"];
    if (this->currentBigIndex >= dragonArray.Size()) {
        this->readNextFightRecord();
        return;
    }
    rapidjson::Value& oneItemArray = dragonArray[this->currentBigIndex];
    if (this->currentDragonIndex >= oneItemArray.Size()) {
        this->currentDragonIndex = 0;
        this->readNextFightRecord();
        return;
    }
    rapidjson::Value& item = oneItemArray[this->currentDragonIndex];

    rapidjson::Value& dragonAffectArray = item["affectarray"];
    
    DragonData* dragonData = DragonData::create();
    dragonData->dragonSkillName = item["guardiankey"].GetString();
    
    for (int i = 0; i < dragonAffectArray.Size(); i++) {
        OneRecord* tempDragonData = OneRecord::create();
        std::string playerKey = dragonAffectArray[i]["playerkey"].GetString();
        if (playerKey.compare(myKey) == 0) {
            tempDragonData->playerName = "player";
        }else {
            tempDragonData->playerName = "enemyPlayer";
        }

        tempDragonData->nuQiChange = dragonAffectArray[i]["sp"].GetInt();
        tempDragonData->currentHP = dragonAffectArray[i]["hp"].GetInt();
        tempDragonData->hitValue = dragonAffectArray[i]["hitvalue"].GetInt();
        tempDragonData->maxHP = dragonAffectArray[i]["maxhp"].GetInt();
        tempDragonData->standIndex = dragonAffectArray[i]["cellid"].GetInt();
        dragonData->dragonAffectArray.pushBack(tempDragonData);
    }
    dragonData->retain();
    this->currentDragonIndex++;
    std::string tempKey = item["playerkey"].GetString();
    if (tempKey.compare(myKey) == 0) {

        this->player->fDragon->runDragonAnimation(dragonData,this->player);
    }else {
        this->playerEnemy->fDragon->runDragonAnimation(dragonData,this->playerEnemy);
    }
}

void ReadRecordFight::readNextFightRecord() {
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

 //   printf("---------%s\n", this->currentJson.c_str());
    doc.Parse<0>(currentJson.c_str());

    if(doc.HasParseError())
    {
        printf("nextFight Record GetParseError%u\n", doc.GetParseError());
        return;
    }
    if (!doc.IsObject()) {
        return;
    }
    rapidjson::Value& dataArray = doc["data"];
    rapidjson::Value roundArray;
    if (dataArray.IsObject()) {
        roundArray = dataArray["rounds"];
    }else {
        roundArray = dataArray[0]["rounds"];
    }
//    rapidjson::Value& roundArray = dataArray[0]["rounds"];
    rapidjson::Value& fightArray = roundArray[this->currentBigIndex];
    if (this->currentSmallIndex >= fightArray.Size()) {
        this->currentSmallIndex = 0;
        this->readBigNextRecord();
        return;
    }
    rapidjson::Value& item = fightArray[this->currentSmallIndex];
 //   rapidjson::Value& cardName = item["cardname"];
    std::string playerKey = item["playerkey"].GetString();
    std::string playerName;
    if (playerKey.compare(myKey) == 0) {
        playerName = "player";
    }else {
        playerName = "enemyPlayer";
    }
    Card* card;
    OneRecord* oneRecordInfo = OneRecord::create();
    
    if (playerName.compare("player") == 0) {
        card = this->getCardFromIndex(item["cellid"].GetInt(), this->player);
      //  printf("%s--------%s----%d------HP:%d\n",playerName.c_str(),item["cardname"].GetString() ,item["standindex"].GetInt(),item["currentHP"].GetInt());
    }else if(playerName.compare("enemyPlayer") == 0) {
        card = this->getCardFromIndex(item["cellid"].GetInt() ,this->playerEnemy);
      //  printf("%s--------%s----%d------HP:%d\n",playerName.c_str(),item["cardname"].GetString(), item["standindex"].GetInt(),item["currentHP"].GetInt());
    }
   // card->readRecordFight = this;
    card->willRun(card->forPlayer->enemy);
    
    
    rapidjson::Value& affectArray = item["affectarray"];
    if (!affectArray.IsArray()) {
        printf("affectArray  is on array!");
        return;
    }
    Vector<OneRecord*> tempRecordVector;
    for (int i = 0; i < affectArray.Size(); i++) {
        OneRecord* oneInfo = OneRecord::create();
        oneInfo->isShanBi = affectArray[i]["isshanbi"].GetBool();
        oneInfo->hitValue = affectArray[i]["hitvalue"].GetDouble();
        oneInfo->isBaoJi = affectArray[i]["isbaoji"].GetBool();
        oneInfo->isGeDang = affectArray[i]["isgedang"].GetBool();
//        oneInfo->fanTanWuLiHartValue = affectArray[i]["fantanwuli"].GetDouble();
//        oneInfo->fanTanFaShuHartValue = affectArray[i]["fantanfashu"].GetDouble();
        std::string pKey = affectArray[i]["playerkey"].GetString();
        if (pKey.compare(myKey) == 0) {
            oneInfo->playerName = "player";
        }else {
            oneInfo->playerName = "enemyPlayer";
        }
       // oneInfo->playerName = affectArray[i]["playername"].GetString();
       // oneInfo->zhiLiao = affectArray[i]["zhiliao"].GetDouble();
        if (oneInfo->playerName.compare("player") == 0) {
            oneInfo->card = this->getCardFromIndex(affectArray[i]["cellid"].GetInt() ,this->player);
        }else if(oneInfo->playerName.compare("enemyPlayer") == 0){
            oneInfo->card = this->getCardFromIndex(affectArray[i]["cellid"].GetInt() ,this->playerEnemy);
 
        }
        
        if (affectArray[i].HasMember("addbuff")) {
            oneInfo->addbuffName = affectArray[i]["addbuff"].GetString();
        }else if(affectArray[i].HasMember("removebuff")) {
            oneInfo->removebuffName = affectArray[i]["removebuff"].GetString();
        }
        oneInfo->currentHP = affectArray[i]["hp"].GetInt();
        oneInfo->maxHP = affectArray[i]["maxhp"].GetInt();
        oneInfo->nuQiChange = affectArray[i]["sp"].GetInt();
        oneInfo->card->MaxHP = oneInfo->maxHP;
    //    oneInfo->enemyNuQiChange = affectArray[i]["enemynuqichange"].GetInt();
        tempRecordVector.pushBack(oneInfo);
    }
    oneRecordInfo->affectRecordArray = tempRecordVector;
    oneRecordInfo->hitTarget = item["targetcellid"].GetInt();
    oneRecordInfo->nuQiChange = item["sp"].GetInt();
    oneRecordInfo->cardName = item["cardkey"].GetString();
    if (oneRecordInfo->cardName.compare("houyi") == 0) {
        if (item.HasMember("islianji") == true) {
            oneRecordInfo->isLianJi = item["islianji"].GetBool();
        }
        
    }
    rapidjson::Value& beforeArray = item["before"];
    if (!affectArray.IsArray()) {
        printf("before  is no array!");
        return;
    }
    Vector<OneRecord*> tempBefore(0);
    this->analysisBeforeOrAfterArray(&tempBefore, beforeArray);
    
    rapidjson::Value& afterArray = item["after"];
    if (!affectArray.IsArray()) {
        printf("before  is no array!");
        return;
    }
    Vector<OneRecord*> tempAfter(0);
    this->analysisBeforeOrAfterArray(&tempAfter, afterArray);
    
    oneRecordInfo->beforeArray = tempBefore;
    oneRecordInfo->afterArray = tempAfter;
    oneRecordInfo->skillId = item["skillid"].GetInt();
    card->beforeAnimation(oneRecordInfo,card);
//    if(item["skillid"].GetInt() == 1 ) {
//        
//        card->xiaoSkll(oneRecordInfo);
//       // card->xiaoSkll(<#OneRecord *info#>);
//    }else if (item["skillid"].GetInt() == 2) {
//        
//        card->daSkill(oneRecordInfo);
//    }
    card->endRun(card->forPlayer->enemy);
    this->currentSmallIndex++;
    
}


void ReadRecordFight::analysisBeforeOrAfterArray(Vector<OneRecord *> *tempBefore, rapidjson::Value &tempArray) {
    if (tempArray.Size() == 0) {
        tempBefore->clear();
        return;
    }
    
    for (int n = 0; n < tempArray.Size(); n++) {
        OneRecord* oneBeforeInfo = OneRecord::create();
        std::string pKey = tempArray[n]["playerkey"].GetString();
        if (pKey.compare(myKey) == 0) {
            oneBeforeInfo->playerName = "player";
        }else {
            oneBeforeInfo->playerName = "enemyPlayer";
        }
        if (oneBeforeInfo->playerName.compare("player") == 0) {
            oneBeforeInfo->card = this->getCardFromIndex(tempArray[n]["cellid"].GetInt() ,this->player);
        }else if(oneBeforeInfo->playerName.compare("enemyPlayer") == 0){
            oneBeforeInfo->card = this->getCardFromIndex(tempArray[n]["cellid"].GetInt() ,this->playerEnemy);
            
        }
        oneBeforeInfo->reason = tempArray[n]["reason"].GetString();
        if (oneBeforeInfo->reason.compare("changehp") == 0) {
            oneBeforeInfo->currentHP = tempArray[n]["hp"].GetInt();
            oneBeforeInfo->maxHP = tempArray[n]["maxhp"].GetInt();
            oneBeforeInfo->offsetHP = tempArray[n]["offsethp"].GetInt();
        }else if(oneBeforeInfo->reason.compare("changesp") == 0) {
            oneBeforeInfo->nuQiChange = tempArray[n]["sp"].GetInt();
        }else if(oneBeforeInfo->reason.compare("addbuff") == 0) {
            oneBeforeInfo->buffName = tempArray[n]["buffname"].GetString();
        }
        tempBefore->pushBack(oneBeforeInfo);
    }

}

