//
//  GeDangBuff.hpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#ifndef GeDangBuff_h
#define GeDangBuff_h

#include "cocos2d.h"
#include "Buff.h"

class Card;
class GeDangBuff : public Buff {
    
public:
    CREATE_FUNC(GeDangBuff);
    virtual bool init();
    float defaultGeDang;
    virtual void add(Card* card);
    virtual void decrease(Card* card);
};
#endif /* GeDangBuff_h */
