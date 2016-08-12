//
//  FightScene.hpp
//  OctLegend
//
//  Created by zc on 16/8/8.
//
//

#ifndef FightScene_h
#define FightScene_h

#include "cocos2d.h"

USING_NS_CC;
class FightPlayer;
class FightMap;
class FightLayer: public cocos2d::Layer {
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(FightLayer);
    FightPlayer* player;
    FightPlayer* enemy;
    Sprite* background;
//    FightMap* leftMap;
//    FightMap* rightMap;
};

#endif /* FightScene_h */
