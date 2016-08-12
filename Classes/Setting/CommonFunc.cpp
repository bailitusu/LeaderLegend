//
//  CommonFunc.cpp
//  OctLegend
//
//  Created by zc on 16/8/10.
//
//

#include "CommonFunc.h"
USING_NS_CC;

void CommonFunc::setSpriteSize(cocos2d::Sprite *sp, float width) {
    Rect spRect = sp->getBoundingBox();
    sp->setScale(width/spRect.size.width);
//    sp->setScale(0.1);
//   Rect r = sp->getBoundingBox();
}