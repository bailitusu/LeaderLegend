//
//  BingFaTreasure.hpp
//  OctLegend
//
//  Created by zc on 16/8/30.
//
//

#ifndef BingFaTreasure_h
#define BingFaTreasure_h

#include "cocos2d.h"
#include "Treasure.h"

class BingFaTreasure : public Treasure {
    
public:
    CREATE_FUNC(BingFaTreasure);
    virtual bool init();
    virtual void initNuQi(Card* card);
    virtual void bingFaHuiFuHp(FightPlayer* player);
};

#endif /* BingFaTreasure_h */
