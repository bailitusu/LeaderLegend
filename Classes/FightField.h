//
//  FightField.hpp
//  OctLegend
//
//  Created by zc on 16/8/12.
//
//

#ifndef FightField_h
#define FightField_h

#include "cocos2d.h"
#include "Card.h"
#include "SetRoleFormatLayer.h"
class FightPlayer;
USING_NS_CC;
class FightField : public  Ref{
    
public:
  //  Vector<Card*> releaseArray;
    FightPlayer* player;
    FightPlayer* enemyPlayer;
    int playerIndex;
    int enemyIndex;
    int roundNum;
    CREATE_FUNC(FightField);
    virtual bool init();
    void playerNextRun();
    void enemyPlayerNextRun();
    void startFight();
    void netxRound();
    void dragonBlock(std::string playerName);
    bool isHasCard(FightPlayer* tempPlayer);
    void dragonRun(std::string playerName);
    Vector<SetRoleData*> roleData;
};

#endif /* FightField_h */
