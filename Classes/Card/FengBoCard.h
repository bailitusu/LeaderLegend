//
//  FengBoCard.hpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#ifndef FengBoCard_h
#define FengBoCard_h

#include "cocos2d.h"
#include "Card.h"
class FightPlayer;
class FengBoCard : public Card {
    
public:
    CREATE_FUNC(FengBoCard);
    virtual bool init();
    
    //  virtual void didBeHit(Card* fromCard);
    //  virtual void runAnimation(FightPlayer* playerTemp);
    virtual void running(FightPlayer* enemyTemp);

    virtual void ultimateSkill();
    // virtual void cardDead();
    void nuQiManage();
    void hitAction();

    // void actionBlock();
};


#endif /* FengBoCard_h */
