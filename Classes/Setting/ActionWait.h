//
//  ActionWait.hpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#ifndef ActionWait_h
#define ActionWait_h

#include "cocos2d.h"
USING_NS_CC;

class ActionWait : public ActionInterval {
    
public:
    static ActionWait* create(float duration);
    bool init(float duration);
    virtual void update(float time);
};
#endif /* ActionWait_h */
