//
//  ChangECard.hpp
//  OctLegend
//
//  Created by zc on 16/8/20.
//
//

#ifndef ChangECard_h
#define ChangECard_h

#include "cocos2d.h"
#include "Card.h"
class ChangECard : public Card {
    
public:
    CREATE_FUNC(ChangECard);
    virtual bool init();
    
//    virtual void didBeHit(Card* fromCard);
//    virtual void runAnimation(FightPlayer* playerTemp);
    virtual void ultimateSkill();
    virtual void running(FightPlayer* enemyTemp);
//    virtual void cardDead();
    void nuQiManage();
    void hitAction();
//    void actionBlock();
};

#endif /* ChangECard_h */
