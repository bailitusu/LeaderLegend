//
//  FightMap.hpp
//  OctLegend
//
//  Created by zc on 16/8/8.
//
//

#ifndef FightMap_h
#define FightMap_h

#include "cocos2d.h"
#include "MapCell.h"
USING_NS_CC;

class FightMap : public Layer{
  
public:
    void init(std::string imageName, std::string direction, Size mapLayerSize);
   // float MapOneLineFun(float y);
    void initMapCell(int id, float orginY, int lineNum,std::string direction);
    
    void creatMap(std::string direction);
    Vector<MapCell*> mapCellArray;
    Vector<MapCell*> hitNineCell(int hitCellIndex);
    Vector<MapCell*> hitHengPaiCell(int hitCellIndex);
    Vector<MapCell*> hitAllCell();
    Vector<MapCell*> hitNuQiMax();
    Sprite* map;
    float mapScale;
    CREATE_FUNC(FightMap);
    virtual bool init();
};
#endif /* FightMap_h */
