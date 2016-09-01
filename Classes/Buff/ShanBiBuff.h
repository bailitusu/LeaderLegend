//
//  ShanBiBuff.hpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#ifndef ShanBiBuff_h
#define ShanBiBuff_h

#include "cocos2d.h"
#include "Buff.h"

class Card;
class ShanBiBuff : public Buff {
    
public:
    CREATE_FUNC(ShanBiBuff);
    virtual bool init();
    virtual void addBuff(Card* card,float value);
    virtual void decreaseBuff(Card* card,float value);
};


#endif /* ShanBiBuff_hpp */
