//
//  CountDown.cpp
//  OctLegend
//
//  Created by zc on 16/9/23.
//
//

#include "CountDown.h"
#include <sstream>
#include <stdlib.h>
bool CountDown::init() {
    return true;
}

void CountDown::upDate(float delta) {
    pTime -= delta;
    char *mTime = new char[10];
    if (pTime <= 0) {
        unschedule(schedule_selector(CountDown::upDate));
    }
    sprintf(mTime ,"%d", (int)pTime);
    this->timeLabel->setString(mTime);
}

bool CountDown::initCountDown(float time) {
    pTime = time;
    
    this->timeLabel = Label::create();
    this->timeLabel->setPosition(0,0);
    this->addChild(this->timeLabel);
    schedule(schedule_selector(CountDown::upDate), 1.0f);

    return true;
}
