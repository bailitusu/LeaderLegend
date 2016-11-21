//
//  RecordFight.cpp
//  OctLegend
//
//  Created by zc on 16/9/5.
//
//

#include "RecordFight.h"
#include "Card.h"

RecordFight* RecordFight::recordFight = NULL;
bool RecordFight::init() {

    return true;
}

RecordFight* RecordFight::GetInstance() {
    if (recordFight == NULL) {
        recordFight = RecordFight::create();
        recordFight->retain();
        return recordFight;
    }
    return recordFight;
}

void RecordFight::createRecord(int recordIndex, int myID, int enemyID) {
    rapidjson::Document recordDoc;
    recordDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = recordDoc.GetAllocator();
    rapidjson::Value array(rapidjson::kArrayType);
    
    recordDoc.AddMember("recordIndex", recordIndex, allocator);
    recordDoc.AddMember("myID", myID, allocator);
    recordDoc.AddMember("enemyID", enemyID, allocator);

    recordDoc.AddMember("fightArray", array, allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    recordDoc.Accept(writer);
    

    this->currentJson = buffer.GetString();

    printf("%s\n",buffer.GetString());
}

void RecordFight::addItemToRecord(OneRecord* record) {
    

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
    rapidjson::Value& fightArray = doc["fightArray"];
    rapidjson::Value object(rapidjson::kObjectType);
    rapidjson::Value affectCardArray(rapidjson::kArrayType);
    object.AddMember("xiaozhao", record->isXiaoZhao, allocator);
    object.AddMember("dazhao", record->isDaZhao, allocator);
    object.AddMember("zhiliao", record->zhiLiao, allocator);
    object.AddMember("islianji", record->isLianJi, allocator);
    object.AddMember("hittarget", record->hitTarget, allocator);
 //   object.AddMember("nuqichange", record->enemyNuQiChange, allocator);
    object.AddMember("cardname", rapidjson::Value(record->cardName.c_str(), allocator), allocator);
    object.AddMember("standindex", record->standIndex, allocator);
    object.AddMember("playername", rapidjson::Value(record->playerName.c_str(), allocator), allocator);
    object.AddMember("currentHP", record->currentHP, allocator);
    object.AddMember("affectArray", affectCardArray, allocator);
   // object.AddMember("enemynuqichange", record->enemyNuQiChange, allocator);
    fightArray.PushBack(object, allocator);
   // doc.AddMember("aaaaa", "hehe", allocator);
    this->currentRecordIndex = fightArray.Size();
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    this->currentJson = buffer.GetString();
  //  printf("%s\n",buffer.GetString());

}

void RecordFight::addDragonItemToRecord(OneRecord *record) {
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
    rapidjson::Value& fightArray = doc["fightArray"];
    rapidjson::Value object(rapidjson::kObjectType);
    rapidjson::Value affectCardArray(rapidjson::kArrayType);
    object.AddMember("dragonskillname", rapidjson::Value(record->dragonSkillName.c_str(), allocator), allocator);
    object.AddMember("playername", rapidjson::Value(record->playerName.c_str(), allocator), allocator);
    
    fightArray.PushBack(object, allocator);
    // doc.AddMember("aaaaa", "hehe", allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    this->currentJson = buffer.GetString();
    
}


void RecordFight::addItemOfNuqiBuff(int recordIndex, OneRecord *record) {
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
//    rapidjson::Value& fightArray = doc["fightArray"];
//    rapidjson::Value& item = fightArray[recordIndex-1];
//    item.AddMember("enemynuqichange", record->enemyNuQiChange, allocator);
//    
    
    rapidjson::Value& fightArray = doc["fightArray"];
    rapidjson::Value& item = fightArray[recordIndex-1];
    rapidjson::Value& cardArray = item["affectArray"];
    rapidjson::Value objectCard(rapidjson::kObjectType);
    objectCard.AddMember("enemynuqichange", record->nuQiChange, allocator);

    cardArray.PushBack(objectCard, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    this->currentJson = buffer.GetString();
  //  printf("%s\n",buffer.GetString());
}


void RecordFight::addAffectCardArray(int recordIndex, OneRecord *record) {
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
    rapidjson::Value& fightArray = doc["fightArray"];
    rapidjson::Value& item = fightArray[recordIndex-1];
    rapidjson::Value& cardArray = item["affectArray"];
    rapidjson::Value objectCard(rapidjson::kObjectType);
    objectCard.AddMember("hitvalue", record->hitValue, allocator);
    objectCard.AddMember("zhiliao", record->zhiLiao, allocator);
    objectCard.AddMember("behitcardName", rapidjson::Value(record->cardName.c_str(), allocator), allocator);
    objectCard.AddMember("standindex", record->standIndex, allocator);
    objectCard.AddMember("isbaoji", record->isBaoJi, allocator);
    objectCard.AddMember("isshanbi", record->isShanBi,allocator);
    objectCard.AddMember("isgedang", record->isGeDang, allocator);
    objectCard.AddMember("fantanwuli", record->fanTanWuLiHartValue, allocator);
    objectCard.AddMember("fantanfashu", record->fanTanFaShuHartValue, allocator);
    objectCard.AddMember("playername", rapidjson::Value(record->playerName.c_str(), allocator), allocator);
    cardArray.PushBack(objectCard, allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    this->currentJson = buffer.GetString();
   // printf("%s\n",buffer.GetString());
}

void RecordFight::addFightResult(OneRecord *record,int recordIndex) {
    
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

    doc.AddMember("fightresult", rapidjson::Value(record->whoSuccess.c_str(), allocator), allocator);

    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    
    
    auto path = FileUtils::getInstance()->getWritablePath();
    char tempFileName[50] = {0};
    sprintf(tempFileName, "fight_%d.json", recordIndex);
    path.append(tempFileName);
    
    FILE* file = fopen(path.c_str(), "wb");
    if(file)
    {
        fputs(buffer.GetString(), file);
        fclose(file);
    }
    this->currentJson = buffer.GetString();
    printf("%s\n",buffer.GetString());
}

