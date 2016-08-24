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

void Buff::add(Card *card) {

}

void Buff::decrease(Card *card) {
    
}

bool Buff::thisBuffisEffect() {
    if (this->huiHeNum != 0) {
        this->huiHeNum--;
        return true;
    }
    
    return false;
}