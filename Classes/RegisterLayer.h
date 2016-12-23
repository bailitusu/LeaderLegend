//
//  RegisterLayer.hpp
//  OctMountain
//
//  Created by zc on 16/11/22.
//
//

#ifndef RegisterLayer_h
#define RegisterLayer_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "LoginSmallLayer.h"
#include "FightNetwork.h"
USING_NS_CC;

class RegisterLayer : public Layer {
    
public:
    virtual bool init();
    CREATE_FUNC(RegisterLayer);
    void initRegisterLayer();
    static Scene* createScene();
    void youkeClick(Ref* sender, ui::Widget::TouchEventType type);
    void enterClick(Ref* sender, ui::Widget::TouchEventType type);
    LoginSmallLayer* smallLoginLayer;
    ui::Button* youkeBtn;
    ui::Button* enterBtn;
    void autoLogin(float dur);
    void autoLoginBlock(float dur);
    void quickSignUpResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void autoLoginResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
};
#endif /* RegisterLayer_h */
