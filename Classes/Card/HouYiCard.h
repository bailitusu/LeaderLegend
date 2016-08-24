//
//  HouYiCard.hpp
//  OctLegend
//
//  Created by zc on 16/8/20.
//
//

#ifndef HouYiCard_h
#define HouYiCard_h

#include "cocos2d.h"
#include "Card.h"
class FightPlayer;
class HouYiCard : public Card {
    
public:
    CREATE_FUNC(HouYiCard);
    virtual bool init();
    
  //  virtual void didBeHit(Card* fromCard);
   // virtual void runAnimation(FightPlayer* playerTemp);
    virtual void ultimateSkill();
  //  virtual void cardDead();
    virtual void running(FightPlayer* enemyTemp);
    void nuQiManage();
    void hitAction();
   // void actionBlock();
    
    
};

#endif /* HouYiCard_h */
