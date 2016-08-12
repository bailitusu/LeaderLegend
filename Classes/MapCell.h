//
//  MapCell.hpp
//  OctLegend
//
//  Created by zc on 16/8/11.
//
//

#ifndef MapCell_h
#define MapCell_h

#include <stdio.h>
#include "cocos2d.h"
#include "StandMapCellInterface.h"
USING_NS_CC;
class MapCell : public  Node{
    
public:
   // MapCell(Vec2 position, int id);
    StandMapCellInterface *obj;
    Vec2 position;
    int index;
    CREATE_FUNC(MapCell);
    void initCell(Vec2 position, int id);
    virtual bool init();
};

#endif /* MapCell_h */
