//
//  SkillScrollLayer.hpp
//  OctLegend
//
//  Created by zc on 16/10/13.
//
//

#ifndef SkillScrollLayer_h
#define SkillScrollLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "LingShoLayer.h"
#include "SkillScrollLayer.h"
USING_NS_CC;

class SkillScrollLayer : public Layer, public extension::ScrollViewDelegate {
    
public:
    virtual bool init();
    CREATE_FUNC(SkillScrollLayer);
    void initSkillScrollLayer();
    virtual void scrollViewDidScroll(extension::ScrollView* view);
    virtual void scrollViewDidZoom(extension::ScrollView* view);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    Layer* continerLayer;
    bool isMoved;
    
};
#endif /* SkillScrollLayer_h */
