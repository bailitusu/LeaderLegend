//
//  QiongQiCard.hpp
//  OctMountain
//
//  Created by zc on 16/12/2.
//
//

#ifndef QiongQiCard_h
#define QiongQiCard_h

#include "cocos2d.h"
#include "Card.h"
class FightPlayer;
class QiongQiCard : public Card {
    
public:
    CREATE_FUNC(QiongQiCard);
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


#endif /* QiongQiCard_h */
