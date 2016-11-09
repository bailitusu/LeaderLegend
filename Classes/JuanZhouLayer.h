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
#include "cocos-ext.h"
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
    cocos2d::extension::ScrollView* srollView;
    Layer* continerLayer;
};

#endif /* JuanZhouLayer_h */
