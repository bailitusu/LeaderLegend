//
//  YiBingBuDao.hpp
//  OctLegend
//
//  Created by zc on 16/8/31.
//
//

#ifndef YiBingBuDao_h
#define YiBingBuDao_h

#include "cocos2d.h"
#include "Treasure.h"

class YiBingBuDao : public Treasure {
    
public:
    CREATE_FUNC(YiBingBuDao);
    virtual bool init();
    virtual bool spriteBrother(Card* card);
    virtual void initNuQi(Card* card);
    
    void blockBuDao(Card* card);
};

#endif /* YiBingBuDao_h */
