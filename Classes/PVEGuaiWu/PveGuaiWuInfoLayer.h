//
//  PveGuaiWuInfoLayer.hpp
//  OctLegend
//
//  Created by zc on 16/11/8.
//
//

#ifndef PveGuaiWuInfoLayer_h
#define PveGuaiWuInfoLayer_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SetRoleFormatLayer.h"
USING_NS_CC;
class PveFightLayer;
class PveGuaiWu;
class PveGuaiWuInfoLayer : public Layer {
    
public:
    virtual bool init();
    CREATE_FUNC(PveGuaiWuInfoLayer);
    void initPveGuaiWuLayer();
   // ui::RichText* richText;
    std::string imageName;
    std::string textInfo;
    Sprite* background;
    Sprite* imageSp;
    Label* textLabel;
    Vector<Sprite*> deFenSpArray;
    PveGuaiWu* guaiWu;
    ui::Button* startBtn;
    Vector<SetRoleData*> *guaiWuData;
    void startBtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type);
    PveFightLayer* pveLayer;
    int index;
};

#endif /* PveGuaiWuInfoLayer_h */
