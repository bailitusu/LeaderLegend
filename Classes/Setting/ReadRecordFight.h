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

USING_NS_CC;
class SetRoleData;
class FightPlayer;
class Card;
class ReadRecordFight : public Ref {
    
public:
    CREATE_FUNC(ReadRecordFight);
    virtual bool init();
    void readNextFightRecord();
    int currentIndex;
    std::string currentJson;
    void readRecordFormMenmory();
    FightPlayer* player;
    FightPlayer* playerEnemy;
    Card* getCardFromIndex(int cardStandIndex,FightPlayer* fplayer);
    Vector<SetRoleData*> *roleData;
};

#endif /* ReadRecordFight_h */
