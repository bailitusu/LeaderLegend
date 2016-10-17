//
//  GameBeginLayer.hpp
//  OctLegend
//
//  Created by zc on 16/9/27.
//
//

#ifndef GameBeginLayer_h
#define GameBeginLayer_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "SetRoleFormatLayer.h"
#include "Dragon.h"
USING_NS_CC;
class Bag;
class Treasure;
class GameBeginLayer : public Layer {
    
public:
  //  virtual void onEnter();
    virtual bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(GameBeginLayer);
    void initGameBeginLayer();
    Sprite* backgroundOne;
    Sprite* backgroundTwo;
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    ui::Button* buZhen;
    ui::Button* faBao;
    ui::Button* jingJiChang;
    ui::Button* juHun;
    ui::Button* lingShou;
    ui::Button* renWu;
    ui::Button* tianFu;
    ui::Button* zhuXian;
    
    void buZhenBtn(Ref* sender, ui::Widget::TouchEventType type);
    void faBaoBtn(Ref* sender, ui::Widget::TouchEventType type);
    void jingJiChangBtn(Ref* sender, ui::Widget::TouchEventType type);
    void juHunBtn(Ref* sender, ui::Widget::TouchEventType type);
    void lingShouBtn(Ref* sender, ui::Widget::TouchEventType type);
    void renWuBtn(Ref* sender, ui::Widget::TouchEventType type);
    void tianFuBtn(Ref* sender, ui::Widget::TouchEventType type);
    void zhuXianBtn(Ref* sender, ui::Widget::TouchEventType type);
    
    //FightPlayer* player;
    Bag* playerBag;
    Dragon* dragon;
    Vector<SetRoleData*> jjcRoleData;
    Vector<SetRoleData*> pveRoleData;
    void cardFormatJJC(Card* card,std::string imageName, int standIndex,Treasure* treasure);
    void cardFormatPVE(Card* card,std::string imageName, int standIndex,Treasure* treasure);
    
};

#endif /* GameBeginLayer_h */
