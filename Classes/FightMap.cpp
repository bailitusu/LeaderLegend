//
//  FightMap.cpp
//  OctLegend
//
//  Created by zc on 16/8/8.
//
//

#include "FightMap.h"
#include "CommonFunc.h"
#include "MapCell.h"
#include "Card.h"
#include "StandMapCellInterface.h"
#include "FightProgress.h"
void FightMap::init(std::string imageName,std::string direction, Size mapLayerSize) {

    map = Sprite::create(imageName);
    map->setLocalZOrder(0);
    map->setAnchorPoint(Vec2(0, 0));
   // mapCellArray = CCArray::create();
    map->setOpacity(0);
    this->addChild(map);
   // CommonFunc::setSpriteSize(map, Director::getInstance()->getVisibleSize().width*0.405);
    this->mapScale = mapLayerSize.width/270;
    CommonFunc::setSpriteSize(map, mapLayerSize.width);
    this->setContentSize(Size(map->getBoundingBox().size.width, map->getBoundingBox().size.width));

    this->creatMap(direction);


}

bool FightMap::init() {
    return true;
}

float MapOneLineFun(float y) {
    float x = (y + 40788/175)*35/236;
    
    return x;
}

float MapTwoLineFun(float y) {
    float x = (y + 120176/125)*25/236;
    
    return x;
}

float MapThirdLineFun(float y) {
    float x = (y + 198324/75)*15/236;
    
    return x;
}

float MapFourLineFun(float y) {
    float x = (y + 277092/25)*5/236;
    
    return x;
}

//void FightMap::creatRightMap() {
////    for (int i = 0; i < 4; i++) {
////        this->initMapCell(i, 30.6, i);
////    }
////    
////    for (int i = 4; i < 8; i++) {
////        this->initMapCell(i, 86.4, i-4);
////    }
////    for (int i = 8; i < 12; i++) {
////        this->initMapCell(i, 138.6, i-4*2);
////    }
////    for (int i = 12; i < 16; i++) {
////        this->initMapCell(i, 187.2, i-4*3);
////    }
//    for (int i = 0; i < 4;  i++) {
//        this->initMapCell(i*4, 187.2, i);
//        this->initMapCell(i*4+1, 138.6, i);
//        this->initMapCell(i*4+2, 86.4, i);
//        this->initMapCell(i*4+3, 30.6, i);
//    }
//    
//}

void FightMap::creatMap(std::string direction) {

    for (int i = 0; i < 4;  i++) {
        
        this->initMapCell(i*4, 187.2*this->mapScale, i,direction);
        this->initMapCell(i*4+1, 138.6*this->mapScale, i,direction);
        this->initMapCell(i*4+2, 86.4*this->mapScale, i,direction);
        this->initMapCell(i*4+3, 30.6*this->mapScale, i,direction);
    }
//    this->initMapCell(0, 30.6, 1);
//    this->initMapCell(1, 86.4, 1);
//    this->initMapCell(2, 138.6, 1);
//    this->initMapCell(3, 187.2, 1);
    

}

void FightMap::initMapCell(int id, float orginY, int lineNum, std::string direction) {
    MapCell* cell = MapCell::create();
    
    switch (lineNum) {
        case 3:
            if (direction.compare("left") == 0) {
                cell->initCell(Vec2(MapOneLineFun(orginY)*this->mapScale, orginY+10), id);
            }else if (direction.compare("right") == 0) {
                cell->initCell(Vec2(this->getBoundingBox().size.width-MapOneLineFun(orginY)*this->mapScale, orginY+10), id);
            }
            
            break;
        case 2:
            if (direction.compare("left") == 0) {
                cell->initCell(Vec2(MapTwoLineFun(orginY)*this->mapScale, orginY+10), id);
            }else if (direction.compare("right") == 0) {
                cell->initCell(Vec2(this->getBoundingBox().size.width-MapTwoLineFun(orginY)*this->mapScale, orginY+10), id);
            }
            //cell->initCell(Vec2(MapTwoLineFun(orginY), orginY-10), id);
            break;
        case 1:
            if (direction.compare("left") == 0) {
                cell->initCell(Vec2(MapThirdLineFun(orginY)*this->mapScale, orginY+10), id);
            }else if (direction.compare("right") == 0) {
                cell->initCell(Vec2(this->getBoundingBox().size.width-MapThirdLineFun(orginY)*this->mapScale, orginY+10), id);
            }
           // cell->initCell(Vec2(MapThirdLineFun(orginY), orginY-10), id);
            break;
        case 0:
            if (direction.compare("left") == 0) {
                cell->initCell(Vec2(MapFourLineFun(orginY)*this->mapScale, orginY+10), id);
            }else if (direction.compare("right") == 0) {
                cell->initCell(Vec2(this->getBoundingBox().size.width-MapFourLineFun(orginY)*this->mapScale, orginY+10), id);
            }
           // cell->initCell(Vec2(MapFourLineFun(orginY), orginY-10), id);
        default:
            break;
    }
    this->addChild(cell);
    mapCellArray.pushBack(cell);
}

Vector<MapCell*> FightMap::hitNineCell(int hitCellIndex) {
    Vector<MapCell*> tempVector;
    int paiNum = hitCellIndex/4;
    int hitCellIndexArray[9] = {hitCellIndex-4-1,hitCellIndex-4,hitCellIndex-4+1,hitCellIndex-1,hitCellIndex,hitCellIndex+1,hitCellIndex+4-1,hitCellIndex+4,hitCellIndex+4+1};
   // for (int i = 0; i < mapCellArray.size(); i++) {
        for (int j = 0; j < 9; j++) {
            if(hitCellIndexArray[j] >= 0 && hitCellIndexArray[j] <= 15) {
                if (j < 3) {
                    if(hitCellIndexArray[j]/4 == paiNum-1) {
                        if(mapCellArray.at(hitCellIndexArray[j])->obj != NULL) {
                            tempVector.pushBack(mapCellArray.at(hitCellIndexArray[j]));
                        }
                    }
                }
                if(j >= 3 && j < 6) {
                    if(hitCellIndexArray[j]/4 == paiNum) {
                        if(mapCellArray.at(hitCellIndexArray[j])->obj != NULL) {
                            tempVector.pushBack(mapCellArray.at(hitCellIndexArray[j]));
                        }
                    }
                }else {
                    if(hitCellIndexArray[j]/4 == paiNum+1) {
                        if(mapCellArray.at(hitCellIndexArray[j])->obj != NULL) {
                            tempVector.pushBack(mapCellArray.at(hitCellIndexArray[j]));
                        }
                    }
                }
            }
        }
   // }
    return tempVector;
}

Vector<MapCell*> FightMap::hitHengPaiCell(int hitCellIndex) {
    Vector<MapCell*> tempVector;
    int paiNum = hitCellIndex / 4;
    for (int i = paiNum*4; i < paiNum*4+4; i++) {
        if (this->mapCellArray.at(i)->obj != NULL) {
            tempVector.pushBack(this->mapCellArray.at(i));
        }
    }
    return tempVector;
}

Vector<MapCell*> FightMap::hitAllCell() {
    Vector<MapCell*> tempVector;
    for (int i = 0; i < this->mapCellArray.size(); i++) {
        if (this->mapCellArray.at(i)->obj != NULL) {
            tempVector.pushBack(this->mapCellArray.at(i));
        }
    }
    return tempVector;
}

Vector<MapCell*> FightMap::hitNuQiMax() {
    Vector<MapCell*> tempVector;
    for (int i = 0; i < this->mapCellArray.size(); i++) {
        if (this->mapCellArray.at(i)->obj != NULL) {
            
            if (((Card*)this->mapCellArray.at(i)->obj)->fPro->nuqiPro->getPercentage() >= 100) {
                tempVector.pushBack(this->mapCellArray.at(i));
            }
        }
    }
    return tempVector;
}





