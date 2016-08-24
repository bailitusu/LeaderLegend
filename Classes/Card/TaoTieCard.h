//
//  TaoTieCard.hpp
//  OctLegend
//
//  Created by zc on 16/8/20.
//
//

#ifndef TaoTieCard_h
#define TaoTieCard_h

#include "cocos2d.h"
#include "Card.h"
class FightPlayer;
class TaoTieCard: public Card {
    
public:
    CREATE_FUNC(TaoTieCard);
    virtual bool init();
    
//    virtual void didBeHit(Card* fromCard);
//    virtual void runAnimation(FightPlayer* playerTemp);
    virtual void ultimateSkill();
//    virtual void cardDead();
    virtual void running(FightPlayer* enemyTemp);
    void nuQiManage();
    void hitAction();
//    void actionBlock();
};

#endif /* TaoTieCard_h */
