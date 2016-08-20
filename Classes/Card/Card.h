//
//  Card.hpp
//  OctLegend
//
//  Created by zc on 16/8/12.
//
//

#ifndef Card_h
#define Card_h

#include "cocos2d.h"
#include "StandMapCellInterface.h"
#include "FightProgress.h"
USING_NS_CC;
class FightPlayer;
class Card: public Ref, public StandMapCellInterface  {

public:
    std::string cardName;
    std::string playerName;
    Sprite* cardSprite;
    Vec2 cardPosition;
    int cellIndex;
    CREATE_FUNC(Card);
    int HP;
    virtual bool init();
    virtual void didBeHit(float hitValue);
    virtual void runAnimation(FightPlayer* playerTemp);
    virtual void ultimateSkill();
    virtual void cardDead();
    FightProgress* fPro;
    FightPlayer* forEnemy;
    FightPlayer* forPlayer;
};

#endif /* Card_h */
