//
//  XuanYunBuff.hpp
//  OctLegend
//
//  Created by zc on 16/8/27.
//
//

#ifndef XuanYunBuff_h
#define XuanYunBuff_h

#include "cocos2d.h"
#include "Buff.h"

class Card;
class XuanYunBuff : public Buff {
    
public:
    CREATE_FUNC(XuanYunBuff);
    virtual bool init();
    virtual void addBuff(Card* card);
    virtual void decreaseBuff(Card* card);
};

#endif /* XuanYunBuff_h */
