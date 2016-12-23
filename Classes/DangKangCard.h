//
//  DangKangCard.hpp
//  OctMountain
//
//  Created by zc on 16/12/2.
//
//

#ifndef DangKangCard_h
#define DangKangCard_h

#include "cocos2d.h"
#include "Card.h"
class FightPlayer;
class DangKangCard : public Card {
    
public:
    CREATE_FUNC(DangKangCard);
    virtual bool init();
    
  //  virtual void initCharacter();

    void nuQiManage(OneRecord *info);

   // void zaiShengAction(bool isRecord);
    
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


#endif /* DangKangCard_h */
