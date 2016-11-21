//
//  MianYiCuoZhiTreasure.hpp
//  OctLegend
//
//  Created by zc on 16/8/31.
//
//

#ifndef MianYiCuoZhiTreasure_h
#define MianYiCuoZhiTreasure_h

#include "cocos2d.h"
#include "Treasure.h"

class MianYiCuoZhiTreasure : public Treasure {
    
public:
    CREATE_FUNC(MianYiCuoZhiTreasure);
    virtual bool init();
    virtual void initNuQi(Card* card);
    virtual bool mianYiCuoZhi();
    virtual void everyRoundAddHP(Card* card);
};

#endif /* MianYiCuoZhiTreasure_h */
