//
//  Buff.cpp
//  OctLegend
//
//  Created by zc on 16/8/22.
//
//

#include "Buff.h"
#include "Card.h"

bool Buff::init() {
    this->huiHeNum = 0;
    return true;
}

void Buff::addBuff(Card *card) {

}

void Buff::decreaseBuff(Card *card) {
    
}

bool Buff::thisBuffisEffect() {
    if (this->huiHeNum != 0) {
        this->huiHeNum--;
        return true;
    }
    
    return false;
}