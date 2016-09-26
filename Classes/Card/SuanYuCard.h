//
//  SuanYuCard.hpp
//  OctLegend
//
//  Created by zc on 16/8/25.
//
//

#ifndef SuanYuCard_h
#define SuanYuCard_h

#include "cocos2d.h"
#include "Card.h"
class FightPlayer;
class SuanYuCard : public Card {
    
public:
    CREATE_FUNC(SuanYuCard);
    virtual bool init();
    

    //virtual void running(FightPlayer* enemyTemp);
    virtual void initCharacter();
    //virtual void ultimateSkill();
    //virtual void didBeHit(Card* fromCard, std::string hitKinds);
    void nuQiManage();
  //  void hitAction();
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

};


#endif /* SuanYuCard_h */
