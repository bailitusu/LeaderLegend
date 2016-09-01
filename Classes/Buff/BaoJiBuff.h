//
//  BaoJiBuff.hpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#ifndef BaoJiBuff_h
#define BaoJiBuff_h

#include "cocos2d.h"
#include "Buff.h"

class Card;
class BaojiBuff : public Buff {
    
public:
    CREATE_FUNC(BaojiBuff);
    virtual bool init();
    virtual void addBuff(Card* card,float value);
    virtual void decreaseBuff(Card* card,float value);
};

#endif /* BaoJiBuff_hpp */
