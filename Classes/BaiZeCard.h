//
//  BaiZeCard.hpp
//  OctMountain
//
//  Created by zc on 16/12/2.
//
//

#ifndef BaiZeCard_h
#define BaiZeCard_h

#include "cocos2d.h"
#include "Card.h"
class BaiZeCard : public Card {
    
public:
    CREATE_FUNC(BaiZeCard);
    virtual bool init();
    
    void nuQiManage(OneRecord *info);
    void hitBlock(Vector<OneRecord*> affectRecordArray);
    void daHitBlock(Vector<OneRecord*> affectRecordArray);

    virtual void xiaoSkll(OneRecord* info);
    virtual void daSkill(OneRecord* info);

    virtual void runZhanLiAnimation();
    void appearUI();

};

#endif /* BaiZeCard_h */
