//
//  MapCell.cpp
//  OctLegend
//
//  Created by zc on 16/8/11.
//
//

#include "MapCell.h"


void MapCell::initCell(Vec2 position, int id) {
    this->position = position;
    this->index = id;
    this->obj = NULL;
}

bool MapCell::init() {
    return true;
}