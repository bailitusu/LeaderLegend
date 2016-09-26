//
//  XingTianCard.hpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#ifndef XingTianCard_h
#define XingTianCard_h

#include "cocos2d.h"
#include "Card.h"

class FightPlayer;
class XingTianCard : public Card {
    
public:
    CREATE_FUNC(XingTianCard);
    virtual bool init();
  //  virtual void running(FightPlayer* enemyTemp);
  //  virtual void didBeHit(Card* fromCard, std::string hitKinds);
   // virtual void ultimateSkill();
    virtual void initCharacter();
    void nuQiManage();
  //  void hitAction();
    void hitBlock(Vector<OneRecord*> affectRecordArray);
    void daHitBlock(Vector<OneRecord*> affectRecordArray);
    void recordHit();
    virtual void xiaoSkll(OneRecord* info);
    virtual void daSkill(OneRecord* info);
    virtual void recordRuning(FightPlayer* enemyTemp);
    virtual void runZhanLiAnimation();
    int hitTimes;
    void appearUI();
    void recordUltimateSkill();
    void moveAnimation(Vec2 target);
   // void actionBlock();
};

#endif /* XingTianCard_hpp */
