//
//  TaoWuCard.hpp
//  OctMountain
//
//  Created by zc on 16/12/2.
//
//

#ifndef TaoWuCard_h
#define TaoWuCard_h

#include "cocos2d.h"
#include "Card.h"
class FightPlayer;
class TaoWuCard: public Card {
    
public:
    CREATE_FUNC(TaoWuCard);
    virtual bool init();

    void nuQiManage(OneRecord *info);
    
    void hitBlock(Vector<OneRecord*> affectRecordArray);
    void daHitBlock(Vector<OneRecord*> affectRecordArray);

    virtual void xiaoSkll(OneRecord* info);
    virtual void daSkill(OneRecord* info);

    virtual void runZhanLiAnimation();
    void moveAnimation(Vec2 target);
    void appearUI();
    virtual void preCardAudio();
    void xiaoHitMusic();
    void daHitMusic();

};


#endif /* TaoWuCard_h */
