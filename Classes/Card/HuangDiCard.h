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
class HuangDiCard: public Card {
    
public:
    CREATE_FUNC(HuangDiCard);
    virtual bool init();
    void didBeHit(int hitValue);
    virtual void runAnimation();
    void getMsg(Ref* sender);
    void initCardSprite(std::string imageName);
    void actionBlock();
    
};

#endif /* HuangDiCard_hpp */
