//
//  AttackRule.cpp
//  OctLegend
//
//  Created by zc on 16/8/16.
//
//

#include "AttackRule.h"
#include "MapCell.h"

bool AttackRule::init() {
//    ruleOneArray = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
//        2,1,3,4,6,5,7,8,10,9,11,12,14,13,15,16,
//        3,2,4,1,7,6,8,5,11,10,12,9,15,14,16,13,
//        4,3,2,1,8,7,6,5,12,11,10,9,16,15,14,13};
//    ruleTwoArray[64] = {1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16,
//        2,6,10,14,1,5,9,13,3,7,11,15,4,8,12,16,
//        3,7,11,15,2,6,10,14,4,8,12,16,1,5,9,13,
//        4,8,12,16,3,7,11,15,2,6,10,14,1,5,9,13};
//    ruleThirdArray[64] = {13,14,15,16,9,10,11,12,5,6,7,8,1,2,3,4,
//        14,13,15,16,10,9,11,12,6,5,7,8,2,1,3,4,
//        15,14,16,13,11,10,12,9,7,6,8,5,3,2,4,1,
//        16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    return true;
}
int AttackRule::ruleOneArray[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
    2,1,3,4,6,5,7,8,10,9,11,12,14,13,15,16,
    3,2,4,1,7,6,8,5,11,10,12,9,15,14,16,13,
    4,3,2,1,8,7,6,5,12,11,10,9,16,15,14,13};
int AttackRule::ruleTwoArray[] = {1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16,
    2,6,10,14,1,5,9,13,3,7,11,15,4,8,12,16,
    3,7,11,15,2,6,10,14,4,8,12,16,1,5,9,13,
    4,8,12,16,3,7,11,15,2,6,10,14,1,5,9,13};
int AttackRule::ruleThirdArray[] = {13,14,15,16,9,10,11,12,5,6,7,8,1,2,3,4,
    14,13,15,16,10,9,11,12,6,5,7,8,2,1,3,4,
    15,14,16,13,11,10,12,9,7,6,8,5,3,2,4,1,
    16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};



int AttackRule::Rule(int standIndex, int ruleNum, FightMap* map) {
    int temp = standIndex % 4 +1;
    
    for (int i = (temp-1)*16; i< (temp*16) ; i++) {
        switch (ruleNum) {
            case 1:
                if ((map->mapCellArray.at(ruleOneArray[i]-1))->obj != NULL) {
                    
                    return ruleOneArray[i]-1;
                }
                break;
            case 2:
                if ((map->mapCellArray.at(ruleTwoArray[i]-1))->obj != NULL) {
                    return ruleTwoArray[i]-1;
                }
                break;
            case 3:
                if ((map->mapCellArray.at(ruleThirdArray[i]-1))->obj != NULL) {
                    return ruleThirdArray[i]-1;
                }
                break;
            default:
                break;
        }
    }
    return AttackError;
}