//
//  XuanWuCard.hpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#ifndef XuanWuCard_h
#define XuanWuCard_h

#include "cocos2d.h"
#include "Card.h"
class FightPlayer;
class XuanWuCard : public Card {

public:
    CREATE_FUNC(XuanWuCard);
    virtual bool init();

   // virtual void running(FightPlayer* enemyTemp);
    virtual void initCharacter();
   // virtual void ultimateSkill();
   // virtual void cardDead();
    void nuQiManage();
   // void hitAction();
    void zaiShengAction(bool isRecord);
    
    void hitBlock(Vector<OneRecord*> affectRecordArray);
    void daHitBlock(Vector<OneRecord*> affectRecordArray);
    void recordHit();
    virtual void xiaoSkll(OneRecord* info);
    virtual void daSkill(OneRecord* info);
    virtual void recordRuning(FightPlayer* enemyTemp);
    virtual void runZhanLiAnimation();
    void moveAnimation(Vec2 target);
    void appearUI();
    void recordUltimateSkill();
    virtual void preCardAudio();
    void xiaoHitMusic();
    void daHitMusic();
   // void actionBlock();
};

#endif /* XuanWuCard_h */
