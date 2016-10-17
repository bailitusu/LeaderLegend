//
//  TuJianLayer.hpp
//  OctLegend
//
//  Created by zc on 16/10/17.
//
//

#ifndef TuJianLayer_h
#define TuJianLayer_h

#include "cocos2d.h"
USING_NS_CC;
class TuJianLayer : public Layer {
    
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TuJianLayer);
    
};

#endif /* TuJianLayer_hpp */
