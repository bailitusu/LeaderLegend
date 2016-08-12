//
//  Card.hpp
//  OctLegend
//
//  Created by zc on 16/8/12.
//
//

#ifndef Card_h
#define Card_h

#include "cocos2d.h"
#include "StandMapCellInterface.h"
USING_NS_CC;

class Card: public Ref, public StandMapCellInterface  {

public:
    Sprite* cardSprite;
    Vec2 cardPosition;
    CREATE_FUNC(Card);
    virtual bool init();
    void didBeHit(int hitValue);
};

#endif /* Card_h */