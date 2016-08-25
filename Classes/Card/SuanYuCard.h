//
//  SuanYuCard.hpp
//  OctLegend
//
//  Created by zc on 16/8/25.
//
//

#ifndef SuanYuCard_h
#define SuanYuCard_h

#include "cocos2d.h"
#include "Card.h"
class FightPlayer;
class SuanYuCard : public Card {
    
public:
    CREATE_FUNC(SuanYuCard);
    virtual bool init();
    

    virtual void running(FightPlayer* enemyTemp);
    virtual void initCharacter();
    virtual void ultimateSkill();
    virtual void didBeHit(Card* fromCard, std::string hitKinds);
    void nuQiManage();
    void hitAction();

};


#endif /* SuanYuCard_h */
