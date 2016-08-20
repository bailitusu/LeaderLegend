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

class StandMapCellInterface {
    
    
public:
    //int HP;
    virtual void didBeHit(float hitValue) = 0;
};

#endif /* StandMapCellInterface_hpp */
