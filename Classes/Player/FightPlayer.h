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
class FightLayer;
USING_NS_CC;
class FightPlayer : public Ref {
    
public:
    FightMap* fMap;

    Vector<Card*> cardArray;
    CREATE_FUNC(FightPlayer);
    virtual bool init();

    FightLayer* fightLayer;
    FightPlayer* enemy;
    int xiangong;
    void initMap(std::string imageName,std::string direction);
    
    void setCardsPositon(Card *card, int index, int zPoint);
    void initCardStandArray();
    void initTackCard(Card* card, std::string imageName, int standIndex, std::string playerName);
};

#endif /* FightPlayer_h */
