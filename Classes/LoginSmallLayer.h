//
//  LoginSmallLayer.hpp
//  OctMountain
//
//  Created by zc on 16/11/23.
//
//

#ifndef LoginSmallLayer_h
#define LoginSmallLayer_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FightNetwork.h"

USING_NS_CC;

class LoginSmallLayer : public Layer {
    
public:
    virtual bool init();
    CREATE_FUNC(LoginSmallLayer);
    void initLoginSmallLayer();
    ui::TextField* userIDTF;
    ui::TextField* passwordTF;
    void userTFEvent(Ref* pSender, ui::TextField::EventType type);
    void pawTFEvent(Ref* pSender, ui::TextField::EventType type);
    
    ui::Button* loginBtn;
    ui::Button* registerBtn;
    void loginClick(Ref* pSender,ui::Widget::TouchEventType type);
    void registerClick(Ref* pSender,ui::Widget::TouchEventType type);
    void creatErrorLabel();
    void removeErrorLabel();
    Label* errorLabel;
    Sprite* errorBgSp;
    void enterRegisterSmallLayer();
    int textFieldClickNum;
    bool userKeyboardAppear;
    Label* serverNameLabel;
    ui::Button* changeServerBtn;
    void changeServerClick(Ref* pSender,ui::Widget::TouchEventType type);
    void loginResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
  //  bool pwdKeyboardAppear;
};

#endif /* LoginSmallLayer_h */
