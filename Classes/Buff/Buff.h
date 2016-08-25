//
//  Buff.hpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#ifndef Buff_h
#define Buff_h

#include "cocos2d.h"
USING_NS_CC;
class Card;
class Buff : public Ref {
    
public:
    CREATE_FUNC(Buff);
    virtual bool init();
    virtual void addBuff(Card* card);
    virtual void decreaseBuff(Card* card);
    virtual bool thisBuffisEffect();
    int huiHeNum;
    float defaultValue;
    std::string buffName;
};


#endif /* Buff_h */
