//
//  MingZhongBuff.hpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#ifndef MingZhongBuff_h
#define MingZhongBuff_h

#include "cocos2d.h"
#include "Buff.h"

class Card;
class MingZhongBuff : public Buff {
    
public:
    CREATE_FUNC(MingZhongBuff);
    virtual bool init();
    virtual void addBuff(Card* card);
    virtual void decreaseBuff(Card* card);
};

#endif /* MingZhongBuff_h */
