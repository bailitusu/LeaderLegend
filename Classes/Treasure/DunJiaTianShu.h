//
//  DunJiaTianShu.hpp
//  OctLegend
//
//  Created by zc on 16/8/30.
//
//

#ifndef DunJiaTianShu_h
#define DunJiaTianShu_h

#include "cocos2d.h"
#include "Treasure.h"

class DunJiaTianShu : public Treasure {
    
public:
    CREATE_FUNC(DunJiaTianShu);
    virtual bool init();
    virtual void initNuQi(Card* card);
};

#endif /* DunJiaTianShu_h */
