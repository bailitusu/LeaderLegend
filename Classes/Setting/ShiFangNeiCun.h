//
//  ShiFangNeiCun.hpp
//  OctLegend
//
//  Created by zc on 16/9/8.
//
//

#ifndef ShiFangNeiCun_h
#define ShiFangNeiCun_h

#include "cocos2d.h"
USING_NS_CC;
class FightPlayer;
class ShiFangNeiCun : public Ref {
    
public:
    CREATE_FUNC(ShiFangNeiCun);
    virtual bool init();
    static void releaseMenmory(FightPlayer* player, FightPlayer* enemy);
};

#endif /* ShiFangNeiCun_h */
