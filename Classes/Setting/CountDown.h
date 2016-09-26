//
//  CountDown.hpp
//  OctLegend
//
//  Created by zc on 16/9/23.
//
//

#ifndef CountDown_h
#define CountDown_h

#include "cocos2d.h"
USING_NS_CC;

class CountDown : public Node {
    
public:
    void upDate(float delta);
    CREATE_FUNC(CountDown);
    virtual bool init();
    Label* timeLabel;
    float pTime;
    bool initCountDown(float time);
};

#endif /* CountDown_h */
