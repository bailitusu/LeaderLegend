//
//  FengHouCard.hpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#ifndef FengHouCard_h
#define FengHouCard_h

#include "cocos2d.h"
#include "Card.h"
class FengHouCard : public Card {
    
public:
    CREATE_FUNC(FengHouCard);
    virtual bool init();

    virtual void ultimateSkill();
    virtual void running(FightPlayer* enemyTemp);

    void nuQiManage();
    void hitAction();

};


#endif /* FengHouCard_h */
