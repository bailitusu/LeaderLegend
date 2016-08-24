//
//  StandMapCellInterface.hpp
//  OctLegend
//
//  Created by zc on 16/8/12.
//
//

#ifndef StandMapCellInterface_h
#define StandMapCellInterface_h

#include "cocos2d.h"
class Card;
class StandMapCellInterface {
    
    
public:
    //int HP;
    virtual void didBeHit(Card* fromCard) = 0;
};

#endif /* StandMapCellInterface_hpp */
