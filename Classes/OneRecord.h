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
    int hitValue;
    Vector<OneRecord*> affectRecordArray;
    Vector<OneRecord*> beforeArray;
    Vector<OneRecord*> afterArray;
    bool isBaoJi;
    bool isShanBi;
    bool isGeDang;
    int standIndex;
    Card* card;
    float fanTanWuLiHartValue;
    float fanTanFaShuHartValue;
    std::string dragonSkillName;
    int nuQiChange;
    std::string whoSuccess;
    bool isLianJi;
    int hitTarget;
    std::string cardName;
    std::string playerName;
    int offsetHP;
    std::string buffName;
    std::string reason;
    std::string addbuffName;
    std::string removebuffName;
    int currentHP;
    int maxHP;
    int skillId;
    int nuQiMax;
    CREATE_FUNC(OneRecord);
    virtual bool init();
    int ballNum;
};

#endif /* OneRecord_h */
