//
//  OneRecord.hpp
//  OctLegend
//
//  Created by zc on 16/9/6.
//
//

#ifndef OneRecord_h
#define OneRecord_h

#include "cocos2d.h"

USING_NS_CC;
class Card;
class OneRecord : public Ref {
    
public:
    bool isDaZhao;
    bool isXiaoZhao;
    float zhiLiao;
    float hitValue;
    Vector<OneRecord*> affectRecordArray;
    bool isBaoJi;
    bool isShanBi;
    bool isGeDang;
    int standIndex;
    Card* card;
    float fanTanWuLiHartValue;
    float fanTanFaShuHartValue;
    std::string dragonSkillName;
    int enemyNuQiChange;
    std::string whoSuccess;
    bool isLianJi;
    int hitTarget;
    std::string cardName;
    std::string playerName;
    int currentHP;
    CREATE_FUNC(OneRecord);
    virtual bool init();
};

#endif /* OneRecord_h */
