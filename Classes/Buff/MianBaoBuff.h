//
//  MianBaoBuff.hpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#ifndef MianBaoBuff_h
#define MianBaoBuff_h

#include "cocos2d.h"
#include "Buff.h"

class Card;
class MianBaoBuff : public Buff {
    
public:
    CREATE_FUNC(MianBaoBuff);
    virtual bool init();
    virtual void addBuff(Card* card);
    virtual void decreaseBuff(Card* card);
};

#endif /* MianBaoBuff_h */
