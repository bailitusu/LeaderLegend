//
//  GongGaoLayer.hpp
//  OctMountain
//
//  Created by zc on 16/11/22.
//
//

#ifndef GongGaoLayer_h
#define GongGaoLayer_h

#include "cocos2d.h"
USING_NS_CC;

class GongGaoLayer : public Layer {
    
public:
    virtual bool init();
    CREATE_FUNC(GongGaoLayer);
    static Scene* createScene();
    void enterNextScene(float dur);
};

#endif /* GongGaoLayer_h */
