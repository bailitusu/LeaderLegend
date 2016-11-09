//
//  FengHouCard.hpp
//  OctLegend
//
//  Created by zc on 16/8/24.
//
//

#ifndef FengHouCard_h
#define FengHouCard_h

#include "cocos2d.h"
#include "Card.h"
class FengHouCard : public Card {
    
public:
    CREATE_FUNC(FengHouCard);
    virtual bool init();

//    virtual void ultimateSkill();
//    virtual void running(FightPlayer* enemyTemp);

    void nuQiManage(OneRecord *info);
   // void hitAction();
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
};


#endif /* FengHouCard_h */
