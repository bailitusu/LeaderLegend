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

#include "SetRoleFormatLayer.h"
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
    Vector<SetRoleData*> roleData;
    std::string fightInfo;
    bool startFight;
    void startGame(float dur);
    void overGame();
    void backPreScene(float dur);
    int huiheNum;
    Label* huiheLabel;
    void nextRound();
};

#endif /* FightScene_h */
