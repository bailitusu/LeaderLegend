//
//  RegisterSmallLayer.hpp
//  OctMountain
//
//  Created by zc on 16/11/22.
//
//

#ifndef RegisterSmallLayer_h
#define RegisterSmallLayer_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FightNetwork.h"
USING_NS_CC;

class RegisterSmallLayer : public Layer {
    
public:
    virtual bool init();
    CREATE_FUNC(RegisterSmallLayer);
    void initRegisterSmallLayer();
    ui::TextField* userIDTF;
    ui::TextField* passwordTF;
 //   ui::TextField* yanZhenMaTF;
    void userTFEvent(Ref* pSender, ui::TextField::EventType type);
    void pawTFEvent(Ref* pSender, ui::TextField::EventType type);
  //  void yanZhengTFEvent(Ref* pSender, ui::TextField::EventType type);
    ui::Button* regsiterBtn;
    void regsiterClick(Ref* sender, ui::Widget::TouchEventType type);
    void regsiterResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
};

#endif /* RegisterSmallLayer_h */
