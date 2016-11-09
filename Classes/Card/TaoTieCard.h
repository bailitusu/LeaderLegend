//
//  TaoTieCard.hpp
//  OctLegend
//
//  Created by zc on 16/8/20.
//
//

#ifndef TaoTieCard_h
#define TaoTieCard_h

#include "cocos2d.h"
#include "Card.h"
class FightPlayer;
class TaoTieCard: public Card {
    
public:
    CREATE_FUNC(TaoTieCard);
    virtual bool init();
    
  //  virtual void ultimateSkill();
    void recordUltimateSkill();
    //virtual void running(FightPlayer* enemyTemp);
    void nuQiManage(OneRecord *info);

    void hitBlock(Vector<OneRecord*> affectRecordArray);
    void daHitBlock(Vector<OneRecord*> affectRecordArray);
    void recordHit();
    virtual void xiaoSkll(OneRecord* info);
    virtual void daSkill(OneRecord* info);
    virtual void recordRuning(FightPlayer* enemyTemp);
    virtual void runZhanLiAnimation();
    void moveAnimation(Vec2 target);
    void appearUI();
    virtual void preCardAudio();
    void xiaoHitMusic();
    void daHitMusic();
//    void actionBlock();
};

#endif /* TaoTieCard_h */
