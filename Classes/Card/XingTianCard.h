//
//  XingTianCard.hpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#ifndef XingTianCard_h
#define XingTianCard_h

#include "cocos2d.h"
#include "Card.h"

class FightPlayer;
class XingTianCard : public Card {
    
public:
    CREATE_FUNC(XingTianCard);
    virtual bool init();
    virtual void running(FightPlayer* enemyTemp);
    virtual void didBeHit(Card* fromCard, std::string hitKinds);
    virtual void ultimateSkill();
    virtual void initCharacter();
    void nuQiManage();
    void hitAction();
   // void actionBlock();
};

#endif /* XingTianCard_hpp */
