//
//  ZhenFenBuff.hpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#ifndef ZhenFenBuff_h
#define ZhenFenBuff_h

#include "cocos2d.h"
#include "Buff.h"

class Card;
class ZhenFenBuff : public Buff {
    
public:
    CREATE_FUNC(ZhenFenBuff);
    virtual bool init();
    virtual void addBuff(Card* card);
    virtual void decreaseBuff(Card* card);
};
#endif /* ZhenFenBuff_h */
