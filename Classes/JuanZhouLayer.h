//
//  JuanZhouLayer.hpp
//  OctLegend
//
//  Created by zc on 16/10/22.
//
//

#ifndef JuanZhouLayer_h
#define JuanZhouLayer_h

#include "cocos2d.h"
USING_NS_CC;

class SetRoleData;
class JuanZhouLayer : public Layer{
    
public:
    virtual bool init();
    CREATE_FUNC(JuanZhouLayer);
    void initJuanZhou();
    Sprite* backgroundSp;
    Vector<SetRoleData*> psRoleData;
    void initRole();
};

#endif /* JuanZhouLayer_h */
