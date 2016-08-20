//
//  AttackRule.hpp
//  OctLegend
//
//  Created by zc on 16/8/16.
//
//

#ifndef AttackRule_h
#define AttackRule_h

#include "cocos2d.h"
#include "FightMap.h"
USING_NS_CC;

class AttackRule : public Ref {
    
public:
    CREATE_FUNC(AttackRule);
    virtual bool init();
    static int ruleOneArray[64];
    static int ruleTwoArray[64];
    static int ruleThirdArray[64];
    
    static int Rule(int standIndex, int ruleNum, FightMap* map);
};

#endif /* AttackRule_h */
