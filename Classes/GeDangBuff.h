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
   
    virtual void addBuff(Card* card,float value);
    virtual void decreaseBuff(Card* card,float value);
};
#endif /* GeDangBuff_h */
