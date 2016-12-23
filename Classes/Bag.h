//
//  Bag.hpp
//  OctLegend
//
//  Created by zc on 16/10/14.
//
//

#ifndef Bag_h
#define Bag_h

#include "cocos2d.h"
USING_NS_CC;
class Bag : public Ref {
    
public:
    virtual bool init();
    CREATE_FUNC(Bag);
    int taoZiNum;
    int huoCaiLiaoNum;
    int shuiCaiLiaoNum;
    int jinCaiLiaoNum;
    int muCaiLiaoNum;
    int tuCaiLiaoNum;
    int tieNum;
    int goldNum;
};

#endif /* Bag_h */
