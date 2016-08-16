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
USING_NS_CC;

class AttackRule : public Ref {
    
public:
    CREATE_FUNC(AttackRule);
    virtual bool init();
    int ruleOneArray[64] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
                             2,1,3,4,6,5,7,8,10,9,11,12,14,13,15,16,
                             3,2,4,1,7,6,8,5,11,10,12,9,15,14,16,13,
                             4,3,2,1,8,7,6,5,12,11,10,9,16,15,14,13};
    int ruleTwoArray[64] = {1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16,
                            2,6,10,14,1,5,9,13,3,7,11,15,4,8,12,16,
                            3,7,11,15,2,6,10,14,4,8,12,16,1,5,9,13,};
    static int Rule(int standIndex);
};

#endif /* AttackRule_h */
