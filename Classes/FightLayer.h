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
#include "FightPlayer.h"
USING_NS_CC;
class FightPlayer;
class FightMap;
class FightLayer: public cocos2d::Layer {
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    void initFightLayer();
    void menuCloseCallback(cocos2d::Ref* pSender);
    int ID;
    CREATE_FUNC(FightLayer);
    FightPlayer* player;
    FightPlayer* enemyPlay;
    Sprite* background;
//    FightMap* leftMap;
//    FightMap* rightMap;
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
};

#endif /* FightScene_h */
