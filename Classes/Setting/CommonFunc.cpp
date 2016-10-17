//
//  CommonFunc.cpp
//  OctLegend
//
//  Created by zc on 16/8/10.
//
//

#include "CommonFunc.h"
#include <stdlib.h>
#include "Card.h"
#include "Setting.h"
#include <sstream>
USING_NS_CC;

void CommonFunc::setSpriteSize(cocos2d::Sprite *sp, float width) {
    Rect spRect = sp->getBoundingBox();
    sp->setScale(width/spRect.size.width);
//    sp->setScale(0.1);
//   Rect r = sp->getBoundingBox();
}

void CommonFunc::setShowAllSpriteSize(cocos2d::Sprite *sp, float width, float height) {
    Rect spRect = sp->getBoundingBox();
    sp->setScale(width/spRect.size.width, height/spRect.size.height);
}

ui::Button* CommonFunc::initButton(ui::Button*btn, const cocos2d::ui::AbstractCheckButton::ccWidgetTouchCallback &callback, float width, cocos2d::Vec2 positon) {
//    btn->setTitleText("Start Fight");
//    btn->setTitleColor(Color3B(255, 255, 255));
//    btn->setTitleFontSize(25);
    btn->setPressedActionEnabled(true);
   // btn->setContentSize(size);
    btn->setPosition(positon);
    btn->addTouchEventListener(callback);
    btn->setScale(width/btn->getBoundingBox().size.width);
    return btn;
}

bool CommonFunc::isInPercent(float percent) {
    int numUpArea = (int)100*percent;
    struct timeval now;
    gettimeofday(&now, NULL);
    unsigned rand_seed = (unsigned)(now.tv_sec*1000 + now.tv_usec/1000);
    srand(rand_seed);
    
    int randNum = rand()%100 + 1;
    if (randNum >= 1 && randNum <= numUpArea) {
        return true;
    }
    return false;
}

float CommonFunc::reckonHitValue(Card *gongJiCard, Card *fangShouCard, std::string hitType) {
    float tempValue = 0;
    if (hitType.compare("wuli") == 0) {
        
        float jinGongWuLiHitValue = gongJiCard->gongJi*(1+gongJiCard->wuliHart);
        float fangShouFangYuValue = fangShouCard->fangYu*(1+fangShouCard->wuliMianShang);
        if (jinGongWuLiHitValue >= fangShouFangYuValue) {
      
            if (fangShouCard->bingKinds == bingZhongType.jinZhan || fangShouCard->bingKinds == bingZhongType.fangYu || fangShouCard->bingKinds == bingZhongType.yuanCheng) {
                tempValue = (jinGongWuLiHitValue-fangShouFangYuValue+gongJiCard->cardLevel*20)*gongJiCard->hitLevel;
                
            }else if(fangShouCard->bingKinds == bingZhongType.guWu || fangShouCard->bingKinds == bingZhongType.zhiLiao || fangShouCard->bingKinds == bingZhongType.faShi) {
                tempValue = ((jinGongWuLiHitValue-fangShouFangYuValue)*1.2+gongJiCard->cardLevel*20)*gongJiCard->hitLevel;
                
            }
            
        }else {
            if (fangShouCard->bingKinds == bingZhongType.jinZhan || fangShouCard->bingKinds == bingZhongType.fangYu || fangShouCard->bingKinds == bingZhongType.yuanCheng) {
                tempValue = (gongJiCard->cardLevel*20-(fangShouFangYuValue-jinGongWuLiHitValue)*0.1)*gongJiCard->hitLevel;

            }else if(fangShouCard->bingKinds == bingZhongType.guWu || fangShouCard->bingKinds == bingZhongType.zhiLiao || fangShouCard->bingKinds == bingZhongType.faShi) {
                tempValue = (gongJiCard->cardLevel*20-(fangShouFangYuValue-jinGongWuLiHitValue)*0.1)*1.2*gongJiCard->hitLevel;
            }

        }

    }else if(hitType.compare("fashu") == 0) {
        float jinGongFaLiHitValue = gongJiCard->faLi*(1+gongJiCard->fashuHart);
        float fangShouFaLiHitValue = fangShouCard->faLi*(1+fangShouCard->fashuMianShang);
        
       
        if (fangShouCard->bingKinds == bingZhongType.jinZhan || fangShouCard->bingKinds == bingZhongType.fangYu || fangShouCard->bingKinds == bingZhongType.yuanCheng) {
            if (jinGongFaLiHitValue*1.2 >= fangShouFaLiHitValue){
                tempValue = (1.2*jinGongFaLiHitValue - fangShouFaLiHitValue + gongJiCard->cardLevel*20)*gongJiCard->hitLevel;
            }else {
                tempValue = gongJiCard->cardLevel*20*gongJiCard->hitLevel;
            }

        }else if(fangShouCard->bingKinds == bingZhongType.guWu || fangShouCard->bingKinds == bingZhongType.zhiLiao || fangShouCard->bingKinds == bingZhongType.faShi) {
            if (jinGongFaLiHitValue >= fangShouFaLiHitValue){
                tempValue = (jinGongFaLiHitValue - fangShouFaLiHitValue + gongJiCard->cardLevel*20)*gongJiCard->hitLevel;
            }else {
                tempValue = (gongJiCard->cardLevel*20-(fangShouFaLiHitValue-jinGongFaLiHitValue)*0.1)*gongJiCard->hitLevel;
            }
  
        }
        
    }
    if (tempValue <= 0) {
        tempValue = 1;
    }
    return tempValue;
    
}

float CommonFunc::reckonShanBiPercent(Card *gongJiCard, Card *fangShouCard, std::string hitType) {
    float tempPercent = 0;
    if (hitType.compare("wuli") == 0) {
        if (gongJiCard->mingZhong >= fangShouCard->shanBi) {
            tempPercent = 0.9 + (gongJiCard->mingZhong-fangShouCard->shanBi)*0.1;
        }else {
            tempPercent = 0.8 - (fangShouCard->shanBi - gongJiCard->mingZhong)*0.8;
        }
    }else if(hitType.compare("fashu") == 0) {
        tempPercent = 1;
    }
    return tempPercent;
}

float CommonFunc::reckonBaoJiPercent(Card *gongJiCard, Card *fangShouCard) {
    float tempPercent = 0;
    
    if (gongJiCard->baoJi >= fangShouCard->mianBao) {
        tempPercent = 0.2 + (gongJiCard->baoJi-fangShouCard->mianBao)*0.8;
    }else {
        tempPercent = 0.05 - (fangShouCard->shanBi - gongJiCard->mingZhong)*0.8;
    }
   
    return tempPercent;
}

float CommonFunc::reckonZhiLiaoValue(Card *zhiLiaoCard, Card *beZhiLiaoCard) {
    float zhiLiaoValue = zhiLiaoCard->faLi*0.2 + beZhiLiaoCard->MaxHP*0.02;
    float baoJiZhiliao = CommonFunc::reckonBaoJiPercent(zhiLiaoCard, beZhiLiaoCard)*0.5;
    if (CommonFunc::isInPercent(baoJiZhiliao)) {
        zhiLiaoValue = zhiLiaoValue*1.4;
    }
    return zhiLiaoValue;
}


Animate* CommonFunc::creatAnimation(std::string onePic, int picSumNum, float time, int loopTimes) {
    auto animation = Animation::create();
    for (int i = 0; i < picSumNum; i++) {
        char tempName[50] = {0};
        sprintf(tempName, onePic.c_str(),i);
        animation->addSpriteFrameWithFile(tempName);
    }
    animation->setDelayPerUnit(time/picSumNum);
    animation->setRestoreOriginalFrame(true);
    if (loopTimes != 0) {
        animation->setLoops(loopTimes);
    }

    return Animate::create(animation);
    //  auto animateAction= ;
    
}

Animate* CommonFunc::removeAnimation() {
//    for (int i = 0; i < picSumNum; i++) {
//        char tempName[50] = {0};
//        sprintf(tempName, onePic.c_str(),i);
//       
//    }
    SpriteFrameCache::getInstance()->removeSpriteFrames();

    Director::getInstance()->getTextureCache()->removeAllTextures();
    
}
//void CommonFunc::showHitValue(Label* textLabel,int hitValue, std::string text) {
//
//
//}



