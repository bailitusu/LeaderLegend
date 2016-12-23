//
//  PveGuaiWu.hpp
//  OctLegend
//
//  Created by zc on 16/11/2.
//
//

#ifndef PveGuaiWu_h
#define PveGuaiWu_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SetRoleFormatLayer.h"
#include "FightNetwork.h"
#include "PveFightLayer.h"

USING_NS_CC;
class FuBenLayer;
class PveGuaiWu : public Ref {
    
public:
    virtual bool init();
    CREATE_FUNC(PveGuaiWu);
    int index;
    FuBenLayer* preLayer;
    ui::Button* guaiWuBtn;
    void createGuaiWu(FuBenLayer* layer,std::string imageName,Vec2 position,float width);
    void btnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type);
   // SetRoleFormatlayer* roleFormatLayer;
    Vector<SetRoleData*> *myData;
    Vector<SetRoleData*> guaiWuData;
    void responseBack(HttpClient *sender, HttpResponse *response);
    bool analysisGuaiWuInfo(std::string info);
    void cardFormatGuaiWu(Card* card, int standIndex,Treasure* treasure);
    

};

#endif /* PveGuaiWu_h */
