//
//  ReadRecordFight.hpp
//  OctLegend
//
//  Created by zc on 16/9/8.
//
//

#ifndef ReadRecordFight_h
#define ReadRecordFight_h

#include "cocos2d.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "OneRecord.h"
USING_NS_CC;
class SetRoleData;
class FightPlayer;
class Card;


class DragonData : public Ref{
    
public:
    virtual bool init();
    CREATE_FUNC(DragonData);
    std::string dragonSkillName;
    Vector<OneRecord*> dragonAffectArray;
    
};

class ReadRecordFight : public Ref {
    
public:
    static ReadRecordFight* getInstance();
    
    CREATE_FUNC(ReadRecordFight);
    virtual bool init();
    void readNextFightRecord();
    void readBigNextRecord();
    int currentSmallIndex;
    int currentBigIndex;
    std::string currentJson;
    void readRecordFormMenmory();
    FightPlayer* player;
    FightPlayer* playerEnemy;
    Card* getCardFromIndex(int cardStandIndex,FightPlayer* fplayer);
    Vector<SetRoleData*> *roleData;
    void readPlayerInfo();
    void initPlayerCard(FightPlayer*tempPlayer, std::string cardName,std::string imageName, int cellIndex, std::string pName,int hp,int maxHp,int sp,int maxSp);
    void analysisBeforeOrAfterArray(Vector<OneRecord*> *tempBefore,rapidjson::Value& tempArray);
    void readDragonInfo();
    void readNextDragon();
    int currentDragonIndex;
    void showGameOver(std::string winner);
    Label* gameOverLabel;
    std::string fightName;

private:
    static ReadRecordFight* readFight;
};

#endif /* ReadRecordFight_h */
