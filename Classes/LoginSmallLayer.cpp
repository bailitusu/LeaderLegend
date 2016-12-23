//
//  LoginSmallLayer.cpp
//  OctMountain
//
//  Created by zc on 16/11/23.
//
//

#include "LoginSmallLayer.h"
#include "CommonFunc.h"
#include "Setting.h"
#include "RegisterSmallLayer.h"
#include "GameBeginLayer.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
bool LoginSmallLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    this->userKeyboardAppear = false;
    this->textFieldClickNum = 0;
    return true;
}

void LoginSmallLayer::initLoginSmallLayer() {
    Sprite* background = Sprite::create("zhuceSmallBg.png");
    CommonFunc::setShowAllSpriteSize(background, this->getBoundingBox().size.width, this->getBoundingBox().size.height);
    background->setPosition(this->getBoundingBox().size.width/2,this->getBoundingBox().size.height/2);
    this->addChild(background,-100);
    
    Label* title = Label::createWithTTF("OCT账号登陆", "fonts/kaiti.ttf", 20);
    title->setAlignment(TextHAlignment::CENTER);
    title->setTextColor(zhuceTitle);
    title->setDimensions(this->getBoundingBox().size.width*2/3, 20);
    title->setPosition(this->getBoundingBox().size.width/2,this->getBoundingBox().size.height-23);
    this->addChild(title,100);
    
    this->serverNameLabel = Label::createWithTTF("28区 横扫千军", "fonts/kaiti.ttf", 18);
    this->serverNameLabel->setAlignment(TextHAlignment::LEFT);
    this->serverNameLabel->setDimensions(120, 20);
    this->serverNameLabel->setTextColor(zhuceTitle);
    this->serverNameLabel->setPosition(this->getBoundingBox().size.width/2+20,this->getBoundingBox().size.height-60);
    this->addChild(this->serverNameLabel,100);
    
    this->changeServerBtn = ui::Button::create("btnBg1.png");
    this->changeServerBtn->setTitleText("更换服务器");
    this->changeServerBtn->setTitleColor(Color3B(225, 225, 225));
    this->changeServerBtn->setPressedActionEnabled(true);
    this->changeServerBtn->setPosition(Vec2(60, this->getBoundingBox().size.height-60));
    this->changeServerBtn->addTouchEventListener(CC_CALLBACK_2(LoginSmallLayer::changeServerClick, this));
    this->addChild(changeServerBtn, 100);
    
    Label* usrIDLabel = Label::createWithTTF("账号：", "fonts/kaiti.ttf", 18);
    usrIDLabel->setAlignment(TextHAlignment::CENTER);
    usrIDLabel->setTextColor(Color4B(0, 0, 0, 255));
    usrIDLabel->setDimensions(50, 20);
    usrIDLabel->setPosition(40,this->getBoundingBox().size.height-100);
    this->addChild(usrIDLabel,100);
    
    Sprite* userTFBgSp = Sprite::create("shurukuang.png");
    CommonFunc::setShowAllSpriteSize(userTFBgSp, this->getBoundingBox().size.width, 40);
    userTFBgSp->setPosition(this->getBoundingBox().size.width/2,this->getBoundingBox().size.height-100);
    this->addChild(userTFBgSp, 50);
    this->userIDTF = ui::TextField::create("请输入帐号", "fonts/kaiti.ttf", 18);
    this->userIDTF->setPosition(userTFBgSp->getPosition());
    this->userIDTF->addEventListener(CC_CALLBACK_2(LoginSmallLayer::userTFEvent, this));
    //this->userIDTF->setContentSize(Size(180, 40));
    // this->userIDTF->setTextAreaSize(Size(180, 20));
    this->userIDTF->setTouchSize(Size(220,20));
    this->userIDTF->setTouchAreaEnabled(true);
    this->userIDTF->setMaxLength(20);
    this->userIDTF->setMaxLengthEnabled(true);
    this->userIDTF->setCursorEnabled(true);
    this->userIDTF->setTextColor(Color4B(255, 255, 255, 255));
    
    //  this->userIDTF->setTextHorizontalAlignment(TextHAlignment::LEFT);
    
    this->addChild(this->userIDTF,100);
    
    Label* pwdLabel = Label::createWithTTF("密码：", "fonts/kaiti.ttf", 18);
    pwdLabel->setAlignment(TextHAlignment::CENTER);
    pwdLabel->setTextColor(Color4B(0, 0, 0, 255));
    pwdLabel->setDimensions(50, 20);
    pwdLabel->setPosition(40,this->getBoundingBox().size.height-150);
    this->addChild(pwdLabel,100);
    
    Sprite* pwdBgSp = Sprite::create("shurukuang.png");
    CommonFunc::setShowAllSpriteSize(pwdBgSp, this->getBoundingBox().size.width, 40);
    pwdBgSp->setPosition(this->getBoundingBox().size.width/2,this->getBoundingBox().size.height-150);
    this->addChild(pwdBgSp, 50);
    
    this->passwordTF = ui::TextField::create("请输入密码", "fonts/kaiti.ttf", 18);
    this->passwordTF->setPosition(pwdBgSp->getPosition());
    this->passwordTF->addEventListener(CC_CALLBACK_2(LoginSmallLayer::pawTFEvent, this));
    this->passwordTF->setMaxLength(20);
    this->passwordTF->setTouchSize(Size(220,20));
    this->passwordTF->setTouchAreaEnabled(true);
    //    this->passwordTF->setContentSize(Size(180, 40));
    this->passwordTF->setMaxLengthEnabled(true);
    this->passwordTF->setPasswordEnabled(true);
    this->passwordTF->setCursorEnabled(true);
    this->passwordTF->setPasswordStyleText("*");
    this->passwordTF->setTextColor(Color4B(255, 255, 255, 255));
    this->addChild(this->passwordTF,100);
    
    this->loginBtn = ui::Button::create("btnBg1.png");
    this->loginBtn->setTitleText("立即登录");
    this->loginBtn->setTitleColor(Color3B(225, 225, 225));
    this->loginBtn->setPressedActionEnabled(true);
    this->loginBtn->setPosition(Vec2(this->getBoundingBox().size.width*3/4, 50));
    this->loginBtn->addTouchEventListener(CC_CALLBACK_2(LoginSmallLayer::loginClick, this));
    this->addChild(loginBtn, 100);
    
    this->registerBtn = ui::Button::create("btnBg1.png");
    this->registerBtn->setTitleText("立即注册");
    this->registerBtn->setTitleColor(Color3B(225, 225, 225));
    this->registerBtn->setPressedActionEnabled(true);
    this->registerBtn->setPosition(Vec2(this->getBoundingBox().size.width/4, 50));
    this->registerBtn->addTouchEventListener(CC_CALLBACK_2(LoginSmallLayer::registerClick, this));
    this->addChild(registerBtn, 100);
}

void LoginSmallLayer::loginClick(cocos2d::Ref *pSender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
//        if (this->userIDTF->getString().compare(myKey) != 0 || this->passwordTF->getString().compare(myPassWord) != 0) {
//            if (this->errorLabel == NULL && this->errorBgSp == NULL) {
//                this->creatErrorLabel();
//            }
//        }else if(this->userIDTF->getString().compare(myKey) == 0 || this->passwordTF->getString().compare(myPassWord) == 0) {
//
//        }
        
        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
        rapidjson::Value account;
        rapidjson::Value password;
        account.SetString(this->userIDTF->getString().c_str(), (unsigned int)strlen(this->userIDTF->getString().c_str()));
        doc.AddMember("account", account, allocator);
        password.SetString(this->passwordTF->getString().c_str(), (unsigned int)strlen(this->passwordTF->getString().c_str()));
        doc.AddMember("password", password, allocator);
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);

        
        FightNetwork* net = FightNetwork::GetInstance();
        net->createPostHttp(loginPostUrl, this, httpresponse_selector(LoginSmallLayer::loginResponse), buffer.GetString());

    }

    
}

void LoginSmallLayer::loginResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    if (response->isSucceed()) {
//        Scene* nextScene = GameBeginLayer::createScene();
//        Director::getInstance()->replaceScene(TransitionFade::create(1.0, nextScene));
        
        std::vector<char>* info = response->getResponseData();
        std::string infoStr  = std::string(info->begin(),info->end());
    //    printf("%s",infoStr.c_str());
        
        rapidjson::Document doc;
        doc.Parse<0>(infoStr.c_str());
        if (doc.HasParseError()) {
            printf("登录失败");
            return;
        }
        int code = doc["code"].GetInt();
        if (code == 0) {
            rapidjson::Value& data = doc["data"];
            myKey = data["id"].GetString();
            Scene* nextScene = GameBeginLayer::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0, nextScene));
            
        }
    }
}

void LoginSmallLayer::registerClick(cocos2d::Ref *pSender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        
        auto block = CallFunc::create(CC_CALLBACK_0(LoginSmallLayer::enterRegisterSmallLayer, this));
    //    this->runAction(Sequence::create(fadeOut,block, NULL));
        
        for (int i = 0; i < this->getChildren().size(); i++) {
            auto fadeOut = FadeTo::create(1.0, 0);
            if (i == this->getChildren().size()-1) {
                this->getChildren().at(i)->runAction(Sequence::create(fadeOut,block, NULL));
            }else {
                this->getChildren().at(i)->runAction(fadeOut);
            }
        }
    }

}

void LoginSmallLayer::changeServerClick(cocos2d::Ref *pSender, ui::Widget::TouchEventType type) {
    
}

void LoginSmallLayer::enterRegisterSmallLayer() {

    RegisterSmallLayer* rsLayer = RegisterSmallLayer::create();
    rsLayer->setContentSize(Size(screenSize.width/2,screenSize.height*2/3));
    rsLayer->initRegisterSmallLayer();
    rsLayer->setPosition(screenSize.width/2-rsLayer->getBoundingBox().size.width/2,screenSize.height/2-rsLayer->getBoundingBox().size.height/2);
    this->getParent()->addChild(rsLayer,150);
    this->removeFromParentAndCleanup(true);
}

void LoginSmallLayer::userTFEvent(cocos2d::Ref *pSender, ui::TextField::EventType type) {
    switch (type) {
        case ui::TextField::EventType::ATTACH_WITH_IME:{
            this->stopAllActions();
            this->userKeyboardAppear = true;
            auto moveTo = MoveTo::create(0.3, Vec2(screenSize.width/2-this->getBoundingBox().size.width/2, screenSize.height-this->getBoundingBox().size.height));
            this->runAction(moveTo);
            break;
        }
        case ui::TextField::EventType::DETACH_WITH_IME: {
            this->stopAllActions();
            this->userKeyboardAppear = false;
            auto moveTo = MoveTo::create(0.3, Vec2(screenSize.width/2-this->getBoundingBox().size.width/2, screenSize.height/2-this->getBoundingBox().size.height/2));
            this->runAction(moveTo);
            break;
        }
        default:
            break;
    }
}

void LoginSmallLayer::pawTFEvent(Ref* pSender, ui::TextField::EventType type) {
    switch (type) {
        case ui::TextField::EventType::ATTACH_WITH_IME:{
            this->userKeyboardAppear = false;
            this->stopAllActions();
            auto moveTo = MoveTo::create(0.3, Vec2(screenSize.width/2-this->getBoundingBox().size.width/2, screenSize.height-this->getBoundingBox().size.height));
            this->runAction(moveTo);
            break;
        }
        case ui::TextField::EventType::DETACH_WITH_IME: {
            this->stopAllActions();
            if (this->userKeyboardAppear == false) {
                auto moveTo = MoveTo::create(0.3, Vec2(screenSize.width/2-this->getBoundingBox().size.width/2, screenSize.height/2-this->getBoundingBox().size.height/2));
                this->runAction(moveTo);
            }

            
            
            break;
        }
        default:
            break;
    }
}

void LoginSmallLayer::creatErrorLabel() {
    this->errorBgSp = Sprite::create("mingchengUIBg.png");
    //  CommonFunc::setShowAllSpriteSize(this->zanWeiKaiFangSpBg, 150, <#float height#>)
    CommonFunc::setSpriteSize(this->errorBgSp, 150);
    this->errorBgSp->setPosition(screenSize.width/2, screenSize.height-this->errorBgSp->getBoundingBox().size.height/2-10);
    this->errorBgSp->setOpacity(0);
    this->addChild(this->errorBgSp,500);
    
    this->errorLabel = Label::createWithTTF("用户名密码错误", "fonts/hanyixuejunti.ttf", 24);
    this->errorLabel->setDimensions(150, this->errorBgSp->getBoundingBox().size.height);
    this->errorLabel->setTextColor(dragonFontColor);
    this->errorLabel->setAlignment(TextHAlignment::CENTER);
    this->errorLabel->setPosition(Vec2(screenSize.width/2, screenSize.height/2-12));
    this->errorLabel->setOpacity(0);
    this->addChild(this->errorLabel,550);
    
    auto appearBg = FadeTo::create(0.5, 255);
    auto disappearBg = FadeTo::create(1.5, 0);
    
    auto appearLabel = FadeTo::create(0.5, 255);
    auto disappearLabel = FadeTo::create(1.5, 0);
    auto block = CallFunc::create(CC_CALLBACK_0(LoginSmallLayer::removeErrorLabel, this));
    this->errorBgSp->runAction(Sequence::create(appearBg,disappearBg,NULL));
    this->errorLabel->runAction(Sequence::create(appearLabel,disappearLabel,block,NULL));
}

void LoginSmallLayer::removeErrorLabel() {
    this->errorLabel->stopAllActions();
    this->errorBgSp->stopAllActions();
    this->errorLabel->removeFromParentAndCleanup(true);
    this->errorLabel = NULL;
    this->errorBgSp->removeFromParentAndCleanup(true);
    this->errorBgSp = NULL;
}
