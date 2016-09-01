//
//  HuFuTreasure.hpp
//  OctLegend
//
//  Created by zc on 16/8/30.
//
//

#ifndef HuFuTreasure_h
#define HuFuTreasure_h

#include "cocos2d.h"
#include "Treasure.h"

class HuFuTreasure : public Treasure {
    
public:
    CREATE_FUNC(HuFuTreasure);
    virtual bool init();
    virtual void willRunAddNuQi(Card* card);
    virtual float specialMianShang(Card* card, float value);
    virtual void initNuQi(Card* card);
};

#endif /* HuFuTreasure_h */
