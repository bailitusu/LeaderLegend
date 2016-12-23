//
//  Boll.hpp
//  OctMountain
//
//  Created by zc on 16/11/30.
//
//

#ifndef Boll_h
#define Boll_h

#include "cocos2d.h"
USING_NS_CC;
class Boll : public Ref {
    
public:
    virtual bool init();
    CREATE_FUNC(Boll);
    Sprite* bollSp;
   // Sprite* createBoll();
    int bollType;
    
};

#endif /* Boll_h */
