//
//  RoleInfoLayer.hpp
//  OctMountain
//
//  Created by zc on 16/11/22.
//
//

#ifndef RoleInfoLayer_h
#define RoleInfoLayer_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class RoleInfoLayer : public Layer {
    
public:
    virtual bool init();
    CREATE_FUNC(RoleInfoLayer);
    void initRoleInfoLayer();
    Label* goldNumLabel;
    Label* zuanShiNumLabel;
    Label* tiLiLabel;
    ui::Button* goldBtn;
    ui::Button* zuanShiBtn;
    ui::Button* tiLiBtn;
    void goldClick(Ref* sender, ui::Widget::TouchEventType type);
    void zuanShiClick(Ref* sender, ui::Widget::TouchEventType type);
    void tiLiClick(Ref* sender, ui::Widget::TouchEventType type);
    
    Label* creatOneInfo(std::string infoImage,ui::Button* btn,Vec2 bgPoint);
    
};

#endif /* RoleInfoLayer_h */
