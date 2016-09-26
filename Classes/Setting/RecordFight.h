//
//  RecordFight.hpp
//  OctLegend
//
//  Created by zc on 16/9/5.
//
//

#ifndef RecordFight_h
#define RecordFight_h

#include "cocos2d.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "OneRecord.h"
//class Card;
USING_NS_CC;

struct FightCommend {
    std::string xiaoZhao = "xiaozhao";
    std::string daZhao = "dazhao";
    std::string zhiLiao = "zhiliao";
    std::string hitValue = "hitvalue";
    std::string isBaoJi = "isbaoji";
    std::string isShanBi = "isshanbi";
    std::string isGeDang = "isgedang";
    std::string hitTarget = "hittarget";
    std::string affectCardArray = "affectCardArray";
};
static FightCommend fightComend;



class RecordFight : public Ref {
    
public:
    static RecordFight* GetInstance();
    //rapidjson::Document *aaaa;
    std::string currentJson;
    CREATE_FUNC(RecordFight);
    virtual bool init();
    void addItemToRecord(OneRecord* record);
    void addDragonItemToRecord(OneRecord* record);
   // void addHitResult(int recordIndex, OneRecord* record);
    void addItemOfNuqiBuff(int recordIndex, OneRecord* record);
    void addAffectCardArray(int recordIndex, OneRecord *record);
    void addFightResult(OneRecord* record,int recordIndex);
    int currentRecordIndex;
    void createRecord(int recordIndex,int myID, int enemyID);
private:

    static RecordFight* recordFight;
};

#endif /* RecordFight_h */
