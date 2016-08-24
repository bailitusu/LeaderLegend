//
//  XuanWuCard.hpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#ifndef XuanWuCard_h
#define XuanWuCard_h

#include "cocos2d.h"
#include "Card.h"
class FightPlayer;
class XuanWuCard : public Card {

public:
    CREATE_FUNC(XuanWuCard);
    virtual bool init();
    
    virtual void didBeHit(Card* fromCard);
    virtual void runAnimation(FightPlayer* playerTemp);
    virtual void ultimateSkill();
    virtual void cardDead();
    void addNuqi();
    void hitAction();
    void actionBlock();
};

#endif /* XuanWuCard_h */