//
//  LingShouInfoLayer.hpp
//  OctLegend
//
//  Created by zc on 16/10/21.
//
//

#ifndef LingShouInfoLayer_h
#define LingShouInfoLayer_h

#include "cocos2d.h"
USING_NS_CC;

class Dragon;
class DragonSkill;
class LingShouInfoLayer :  public Layer{
    
public:
    virtual bool init();
    CREATE_FUNC(LingShouInfoLayer);
    Label* dragonNameLabel;
    void initLingShouInfoLayer();
    DragonSkill* dSkill;
};

#endif /* LingShouInfoLayer_h */
