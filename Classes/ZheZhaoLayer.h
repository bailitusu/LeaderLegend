//
//  ZheZhaoLayer.hpp
//  OctMountain
//
//  Created by zc on 16/12/22.
//
//

#ifndef ZheZhaoLayer_h
#define ZheZhaoLayer_h

#include "cocos2d.h"

USING_NS_CC;

class ZheZhaoLayer : public Layer {
    
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(ZheZhaoLayer);
    
    void initThisLayer();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
};
#endif /* ZheZhaoLayer_h */
