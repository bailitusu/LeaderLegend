//
//  AnalysisJson.cpp
//  OctLegend
//
//  Created by zc on 16/10/24.
//
//

#include "AnalysisJson.h"
#include "FightAnimation.h"

AnalysisJson* AnalysisJson::analysisJson = NULL;
bool AnalysisJson::init() {
    this->initialJson = "[[{\"cardid\":\"xuanwu\",\"player\":\"0\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":0,\"cardid\":\"xuanwu\"}},{\"cardid\":\"xingtian\",\"player\":\"0\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":3,\"cardid\":\"xingtian\"}},{\"cardid\":\"houyi\",\"player\":\"0\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":5,\"cardid\":\"houyi\"}},{\"cardid\":\"taotie\",\"player\":\"0\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":6,\"cardid\":\"taotie\"}},{\"cardid\":\"fengbo\",\"player\":\"0\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":9,\"cardid\":\"fengbo\"}},{\"cardid\":\"fenghou\",\"player\":\"0\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":10,\"cardid\":\"fenghou\"}},{\"cardid\":\"change\",\"player\":\"0\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":12,\"cardid\":\"change\"}},{\"cardid\":\"suanyu\",\"player\":\"0\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":15,\"cardid\":\"suanyu\"}},{\"cardid\":\"xuanwu\",\"player\":\"1\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":0,\"cardid\":\"xuanwu\"}},{\"cardid\":\"xingtian\",\"player\":\"1\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":3,\"cardid\":\"xingtian\"}},{\"cardid\":\"houyi\",\"player\":\"1\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":5,\"cardid\":\"houyi\"}},{\"cardid\":\"taotie\",\"player\":\"1\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":6,\"cardid\":\"taotie\"}},{\"cardid\":\"fengbo\",\"player\":\"1\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":9,\"cardid\":\"fengbo\"}},{\"cardid\":\"fenghou\",\"player\":\"1\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":10,\"cardid\":\"fenghou\"}},{\"cardid\":\"change\",\"player\":\"1\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":12,\"cardid\":\"change\"}},{\"cardid\":\"suanyu\",\"player\":\"1\",\"type\":\"addCharacter\",\"userinfo\":{\"cellid\":15,\"cardid\":\"suanyu\"}},{\"cardid\":\"xuanwu\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"xuanwu\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"xuanwu\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}},{\"cardid\":\"xuanwu\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"value\":5,\"type\":\"hp\",\"remain\":35,\"max\":40}},{\"cardid\":\"xuanwu\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}}],[{\"cardid\":\"xuanwu\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"xuanwu\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"xuanwu\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":2}},{\"cardid\":\"xuanwu\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"value\":5,\"type\":\"hp\",\"remain\":35,\"max\":40}},{\"cardid\":\"xuanwu\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":2}}],[{\"cardid\":\"xingtian\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"xingtian\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"xingtian\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}},{\"cardid\":\"xingtian\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"value\":10,\"type\":\"hp\",\"remain\":20,\"max\":30}},{\"cardid\":\"xingtian\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}}],[{\"cardid\":\"xingtian\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"xingtian\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"xingtian\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":2}},{\"cardid\":\"xingtian\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"value\":10,\"type\":\"hp\",\"remain\":20,\"max\":30}},{\"cardid\":\"xingtian\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":2}}],[{\"cardid\":\"houyi\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"houyi\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"houyi\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}},{\"cardid\":\"houyi\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"value\":10,\"type\":\"hp\",\"remain\":20,\"max\":30}},{\"cardid\":\"houyi\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}}],[{\"cardid\":\"houyi\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"houyi\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"houyi\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":2}},{\"cardid\":\"houyi\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"value\":10,\"type\":\"hp\",\"remain\":20,\"max\":30}},{\"cardid\":\"houyi\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":2}}],[{\"cardid\":\"taotie\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"taotie\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"taotie\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}},{\"cardid\":\"taotie\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"value\":5,\"type\":\"hp\",\"remain\":25,\"max\":30}},{\"cardid\":\"taotie\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":0}}],[{\"cardid\":\"taotie\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"taotie\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"taotie\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}},{\"cardid\":\"taotie\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"value\":5,\"type\":\"hp\",\"remain\":25,\"max\":30}},{\"cardid\":\"taotie\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":0}}],[{\"cardid\":\"fengbo\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"houyi\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"fengbo\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}},{\"cardid\":\"houyi\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"value\":10,\"type\":\"hp\",\"remain\":10,\"max\":30}},{\"cardid\":\"houyi\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":3}}],[{\"cardid\":\"fengbo\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"houyi\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"fengbo\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}},{\"cardid\":\"houyi\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"value\":10,\"type\":\"hp\",\"remain\":10,\"max\":30}},{\"cardid\":\"houyi\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":3}}],[{\"cardid\":\"fenghou\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"taotie\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"fenghou\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}},{\"cardid\":\"taotie\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"value\":10,\"type\":\"hp\",\"remain\":15,\"max\":30}},{\"cardid\":\"taotie\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":2}}],[{\"cardid\":\"fenghou\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"taotie\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"fenghou\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}},{\"cardid\":\"taotie\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"value\":10,\"type\":\"hp\",\"remain\":15,\"max\":30}},{\"cardid\":\"taotie\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}}],[{\"cardid\":\"change\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"change\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"change\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":2}},{\"cardid\":\"change\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"value\":-10,\"type\":\"hp\",\"remain\":20,\"max\":20}},{\"cardid\":\"change\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":2}}],[{\"cardid\":\"change\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"change\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"change\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":2}},{\"cardid\":\"change\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"value\":-10,\"type\":\"hp\",\"remain\":20,\"max\":20}},{\"cardid\":\"change\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":2}}],[{\"cardid\":\"suanyu\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"xingtian\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"suanyu\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}},{\"cardid\":\"xingtian\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"value\":10,\"type\":\"hp\",\"remain\":10,\"max\":30}},{\"cardid\":\"xingtian\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":3}}],[{\"cardid\":\"suanyu\",\"player\":\"1\",\"type\":\"action\",\"userinfo\":{\"type\":\"hit\"}},{\"cardid\":\"xingtian\",\"player\":\"0\",\"type\":\"action\",\"userinfo\":{\"type\":\"behit\"}}],[{\"cardid\":\"suanyu\",\"player\":\"1\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":1}},{\"cardid\":\"xingtian\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"value\":10,\"type\":\"hp\",\"remain\":10,\"max\":30}},{\"cardid\":\"xingtian\",\"player\":\"0\",\"type\":\"text\",\"userinfo\":{\"type\":\"sp\",\"value\":3}}]]";
    return true;
}

AnalysisJson* AnalysisJson::GetInstance() {
    if (analysisJson == NULL) {
        analysisJson = AnalysisJson::create();
        analysisJson->retain();
        return analysisJson;
    }
    return analysisJson;
}

void AnalysisJson::readNextJson() {
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    doc.Parse<0>(this->initialJson.c_str());
    
    if(doc.HasParseError())
    {
        printf("GetParseError%u\n", doc.GetParseError());
        return;
    }
    if (!doc.IsArray()) {
        return;
    }
    
    if (this->currentIndex >= doc.Size()) {
        return;
    }
    
    rapidjson::Value &itemArray = doc[this->currentIndex];
    this->currentIndex++;
    if (!itemArray.IsArray()) {
        printf("no array error");
        return;
    }
  //  std::string aaa = itemArray[0]["playerid"].GetString();
    this->readCurrentAnimationJson(itemArray);
    
}


void AnalysisJson::readCurrentAnimationJson(rapidjson::Value &array) {
    FightAnimation* fa = FightAnimation::create();
    for (int i = 0; i < array.Size(); i++) {
        fa->playerID = array[i]["player"].GetString();
        fa->cardID = array[i]["cardid"].GetString();
        fa->type = array[i]["type"].GetString();
       // fa->delay = array[i]["delay"].GetInt();

        rapidjson::Value &userObj = array[i]["userinfo"];
        if (!userObj.IsObject()) {
            return;
        }
        if (fa->type.compare("action") == 0) {
            std::string aaa = userObj["type"].GetString();
            printf("%s",aaa.c_str());
        }else if (fa->type.compare("text") == 0) {
//            std::string 
        }
        
    }
}
