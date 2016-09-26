//
//  HuangDiCard.hpp
//  OctLegend
//
//  Created by zc on 16/8/12.
//
//

#ifndef HuangDiCard_h
#define HuangDiCard_h

#include "cocos2d.h"
#include "Card.h"
class FightPlayer;
class HuangDiCard: public Card {
    
public:
    CREATE_FUNC(HuangDiCard);
    virtual bool init();
    virtual void didBeHit(Card* fromCard, std::string hitKinds);
    virtual void runAnimation(FightPlayer* playerTemp);
    virtual void ultimateSkill();
    virtual void cardDead();
    
 //   void initCardSprite(std::string imageName);
    void actionBlock();
};

#endif /* HuangDiCard_hpp */
