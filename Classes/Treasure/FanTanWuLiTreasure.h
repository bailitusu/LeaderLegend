//
//  FanTanWuLiTreasure.hpp
//  OctLegend
//
//  Created by zc on 16/8/31.
//
//

#ifndef FanTanWuLiTreasure_h
#define FanTanWuLiTreasure_h

#include "cocos2d.h"
#include "Treasure.h"

class FanTanWuLiTreasure : public Treasure {
    
public:
    CREATE_FUNC(FanTanWuLiTreasure);
    virtual bool init();
    virtual void initNuQi(Card* card);
    virtual float fanTanWuLiHart(float hartValue);
};

#endif /* FanTanWuLiTreasure_h */
