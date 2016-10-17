//
//  ChangECard.hpp
//  OctLegend
//
//  Created by zc on 16/8/20.
//
//

#ifndef ChangECard_h
#define ChangECard_h

#include "cocos2d.h"
#include "Card.h"
class ChangECard : public Card {
    
public:
    CREATE_FUNC(ChangECard);
    virtual bool init();
    
    void recordUltimateSkill();
    void nuQiManage();
    void hitBlock(Vector<OneRecord*> affectRecordArray);
    void daHitBlock(Vector<OneRecord*> affectRecordArray);
    void recordHit();
    virtual void xiaoSkll(OneRecord* info);
    virtual void daSkill(OneRecord* info);
    virtual void recordRuning(FightPlayer* enemyTemp);
    virtual void runZhanLiAnimation();
    void appearUI();
    virtual void preCardAudio();
   // void xiaoHitMusic();
    //int hitTimes;
};

#endif /* ChangECard_h */
