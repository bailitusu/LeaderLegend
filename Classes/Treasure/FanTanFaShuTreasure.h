//
//  FanTanFaShuTreasure.hpp
//  OctLegend
//
//  Created by zc on 16/8/31.
//
//

#ifndef FanTanFaShuTreasure_h
#define FanTanFaShuTreasure_h

#include "cocos2d.h"
#include "Treasure.h"

class FanTanFaShuTreasure : public Treasure {
    
public:
    CREATE_FUNC(FanTanFaShuTreasure);
    virtual bool init();
    virtual void initNuQi(Card* card);
    virtual float fanTanFaShuHart(float hartValue);
};

#endif /* FanTanFaShuTreasure_h */
