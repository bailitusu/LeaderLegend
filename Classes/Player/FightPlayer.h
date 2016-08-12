//
//  FightPlayer.hpp
//  OctLegend
//
//  Created by zc on 16/8/12.
//
//

#ifndef FightPlayer_h
#define FightPlayer_h

#include "cocos2d.h"
#include "FightMap.h"
#include "Card.h"
#include "FightLayer.h"
USING_NS_CC;
class FightPlayer : public Ref {
    
public:
    FightMap* fMap;
    Vector<Card*> cardArray;
    CREATE_FUNC(FightPlayer);
    virtual bool init();
    void initMap(std::string imageName,std::string direction);
    FightLayer* fightLayer;
    FightPlayer* enemy;
};

#endif /* FightPlayer_h */
