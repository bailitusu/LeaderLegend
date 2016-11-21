//
//  HouYiCard.hpp
//  OctLegend
//
//  Created by zc on 16/8/20.
//
//

#ifndef HouYiCard_h
#define HouYiCard_h

#include "cocos2d.h"
#include "Card.h"
class FightPlayer;
class HouYiCard : public Card {
    
public:
    CREATE_FUNC(HouYiCard);
    virtual bool init();
    
  //  virtual void didBeHit(Card* fromCard);
   // virtual void runAnimation(FightPlayer* playerTemp);
   // virtual void ultimateSkill();
   // void recordUltimateSkill();
  //  virtual void cardDead();
  //  virtual void running(FightPlayer* enemyTemp);
    void nuQiManage(OneRecord *info);
    void hitBlock(Vector<OneRecord*> affectRecordArray);
    void daHitBlock(Vector<OneRecord*> affectRecordArray);
   // void recordHit();
    virtual void xiaoSkll(OneRecord* info);
    virtual void daSkill(OneRecord* info);
   // virtual void recordRuning(FightPlayer* enemyTemp);
    virtual void runZhanLiAnimation();
    int hitTimes;
    void appearUI(Animate* tempAnimate);
    virtual void preCardAudio();
   // virtual void preAddCardAnimationResource();
    void xiaoHitMusic();

//    virtual void beforeAnimation(OneRecord *info);
//    virtual void afterAnimation(OneRecord *info);
   // void actionBlock();
    
    
};

#endif /* HouYiCard_h */
