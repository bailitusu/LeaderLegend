//
//  FightProgress.hpp
//  OctLegend
//
//  Created by zc on 16/8/17.
//
//

#ifndef FightProgress_h
#define FightProgress_h

#include "cocos2d.h"

USING_NS_CC;
class FightProgress : public Ref  {
    
public:
    ProgressTimer* hpPro;
    ProgressTimer* nuqiPro;
    CREATE_FUNC(FightProgress);
    virtual bool init();
    Sprite* hpProBg;
    Sprite* nuqiProBg;
    void initNuQiPro(float precent);
    void setNuQiProPrecent(float precent);
};


#endif /* FightProgress_h */
