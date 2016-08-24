//
//  ActionWait.cpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#include "ActionWait.h"

ActionWait* ActionWait::create(float duration) {
    ActionWait* wait = new ActionWait();
    wait->init(duration);
    wait->autorelease();
    return wait;
}

bool ActionWait::init(float duration) {
    if (ActionInterval::initWithDuration(duration)) {
        return true;
    }
    return false;
}

void ActionWait::update(float time) {
    
}
