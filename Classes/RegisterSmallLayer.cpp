//
//  RegisterSmallLayer.cpp
//  OctMountain
//
//  Created by zc on 16/11/22.
//
//

#include "RegisterSmallLayer.h"
#include "CommonFunc.h"
#include "Setting.h"
#include "GameBeginLayer.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
bool RegisterSmallLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

void RegisterSmallLayer::initRegisterSmallLayer() {
    Sprite* background = Sprite::create("zhuceSmallBg.png");
    CommonFunc::setShowAllSpriteSize(background, this->getBoundingBox().size.width, this->getBoundingBox().size.height);
    background->setPosition(this->getBoundingBox().size.width/2,this->getBoundingBox().size.height/2);
    this->addChild(background,-100);
    
    Label* title = Label::createWithTTF("OCT账号注册", "fonts/kaiti.ttf", 20);
    title->setAlignment(TextHAlignment::CENTER);
    title->setTextColor(zhuceTitle);
    title->setDimensions(this->getBoundingBox().size.width*2/3, 20);
    title->setPosition(this->getBoundingBox().size.width/2,this->getBoundingBox().size.height-20);
    this->addChild(title,100);
    
    Label* usrIDLabel = Label::createWithTTF("账号：", "fonts/kaiti.ttf", 18);
    usrIDLabel->setAlignment(TextHAlignment::LEFT);
    usrIDLabel->setTextColor(Color4B(0, 0, 0, 255));
    usrIDLabel->setDimensions(65, 20);
    usrIDLabel->setPosition(50,this->getBoundingBox().size.height-70);
    this->addChild(usrIDLabel,100);
    
    Sprite* userTFBgSp = Sprite::create("shurukuang.png");
    CommonFunc::setShowAllSpriteSize(userTFBgSp, this->getBoundingBox().size.width, 40);
    userTFBgSp->setPosition(this->getBoundingBox().size.width/2,this->getBoundingBox().size.height-70);
    this->addChild(userTFBgSp, 50);
    this->userIDTF = ui::TextField::create("请输入手机号", "fonts/kaiti.ttf", 18);
    this->userIDTF->setPosition(userTFBgSp->getPosition());
    this->userIDTF->addEventListener(CC_CALLBACK_2(RegisterSmallLayer::userTFEvent, this));
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
    
//    Label* yanZhengLabel = Label::createWithTTF("验证码：", "fonts/kaiti.ttf", 18);
//    yanZhengLabel->setAlignment(TextHAlignment::LEFT);
//    yanZhengLabel->setTextColor(Color4B(0, 0, 0, 255));
//    yanZhengLabel->setDimensions(65, 20);
//    yanZhengLabel->setPosition(50,this->getBoundingBox().size.height-120);
//    this->addChild(yanZhengLabel,100);
//    
//    Sprite* yanZhengTFBgSp = Sprite::create("shurukuang.png");
//    CommonFunc::setShowAllSpriteSize(yanZhengTFBgSp, this->getBoundingBox().size.width, 40);
//    yanZhengTFBgSp->setPosition(this->getBoundingBox().size.width/2,this->getBoundingBox().size.height-120);
//    this->addChild(yanZhengTFBgSp, 50);
//    this->yanZhenMaTF = ui::TextField::create("请输入验证码", "fonts/kaiti.ttf", 18);
//    this->yanZhenMaTF->setPosition(yanZhengTFBgSp->getPosition());
//    this->yanZhenMaTF->addEventListener(CC_CALLBACK_2(RegisterSmallLayer::yanZhengTFEvent, this));
//    //this->userIDTF->setContentSize(Size(180, 40));
//    // this->userIDTF->setTextAreaSize(Size(180, 20));
//    this->yanZhenMaTF->setTouchSize(Size(220,20));
//    this->yanZhenMaTF->setTouchAreaEnabled(true);
//    this->yanZhenMaTF->setMaxLength(20);
//    this->yanZhenMaTF->setMaxLengthEnabled(true);
//    this->yanZhenMaTF->setCursorEnabled(true);
//    this->yanZhenMaTF->setTextColor(Color4B(255, 255, 255, 255));
//    this->addChild(this->yanZhenMaTF,100);
    
    Label* pwdLabel = Label::createWithTTF("密码：", "fonts/kaiti.ttf", 18);
    pwdLabel->setAlignment(TextHAlignment::LEFT);
    pwdLabel->setTextColor(Color4B(0, 0, 0, 255));
    pwdLabel->setDimensions(65, 20);

    pwdLabel->setPosition(50,this->getBoundingBox().size.height-120);
    this->addChild(pwdLabel,100);
    
    Sprite* pwdBgSp = Sprite::create("shurukuang.png");
    CommonFunc::setShowAllSpriteSize(pwdBgSp, this->getBoundingBox().size.width, 40);
    pwdBgSp->setPosition(this->getBoundingBox().size.width/2,this->getBoundingBox().size.height-120);
    this->addChild(pwdBgSp, 50);
    
    this->passwordTF = ui::TextField::create("请输入密码", "fonts/kaiti.ttf", 18);
    this->passwordTF->setPosition(pwdBgSp->getPosition());
    this->passwordTF->addEventListener(CC_CALLBACK_2(RegisterSmallLayer::pawTFEvent, this));
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
    
    this->regsiterBtn = ui::Button::create("btnBg1.png");
    this->regsiterBtn->setTitleText("注册");
    this->regsiterBtn->setTitleColor(Color3B(225, 225, 225));
    this->regsiterBtn->setPressedActionEnabled(true);
    this->regsiterBtn->setPosition(Vec2(this->getBoundingBox().size.width/2, 40));
    this->regsiterBtn->addTouchEventListener(CC_CALLBACK_2(RegisterSmallLayer::regsiterClick, this));
    this->addChild(regsiterBtn, 100);
}

void RegisterSmallLayer::regsiterClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {

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
        net->createPostHttp(zhucePostUrl, this, httpresponse_selector(RegisterSmallLayer::regsiterResponse), buffer.GetString());
    }
}


void RegisterSmallLayer::regsiterResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    if (response->isSucceed()) {
//        myKey = this->userIDTF->getString();
//        myPassWord = this->passwordTF->getString();
//        Scene* nextScene = GameBeginLayer::createScene();
//        Director::getInstance()->replaceScene(TransitionFade::create(1.0, nextScene));
        std::vector<char>* info = response->getResponseData();
        std::string infoStr  = std::string(info->begin(),info->end());
      //  printf("%s",infoStr.c_str());
        
        rapidjson::Document doc;
        doc.Parse<0>(infoStr.c_str());
        if (doc.HasParseError()) {
            printf("注册失败");
            return;
        }
        int code = doc["code"].GetInt();
        if (code == 0) {
            rapidjson::Value& data = doc["data"];
//            myKey = data["id"].GetString();
//            std::string tempUserID = "userID_" + this->userIDTF->getString();
//            std::string tempPwd = "passWord_" + this->passwordTF->getString();
//            std::string tempAuto = "auto_" + this->userIDTF->getString();
            UserDefault::getInstance()->setStringForKey("userID", this->userIDTF->getString().c_str());
            UserDefault::getInstance()->setStringForKey("pwd", this->passwordTF->getString().c_str());
            UserDefault::getInstance()->setStringForKey("auto", "true");
            if (UserDefault::getInstance()->isXMLFileExist() == true) {
                printf("---------");
            }
            UserDefault::getInstance()->flush();
            Scene* nextScene = GameBeginLayer::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0, nextScene));
            
        }
    }
}
//void RegisterSmallLayer::yanZhengTFEvent(cocos2d::Ref *pSender, ui::TextField::EventType type) {
//    switch (type) {
//        case ui::TextField::EventType::ATTACH_WITH_IME:{
//            this->stopAllActions();
//            auto moveTo = MoveTo::create(0.3, Vec2(screenSize.width/2-this->getBoundingBox().size.width/2, screenSize.height-this->getBoundingBox().size.height));
//            this->runAction(moveTo);
//            break;
//        }
//        case ui::TextField::EventType::DETACH_WITH_IME: {
//            auto moveTo = MoveTo::create(0.3, Vec2(screenSize.width/2-this->getBoundingBox().size.width/2, screenSize.height/2-this->getBoundingBox().size.height/2));
//            this->runAction(moveTo);
//            break;
//        }
//        default:
//            break;
//    }
//}

void RegisterSmallLayer::userTFEvent(cocos2d::Ref *pSender, ui::TextField::EventType type) {
    switch (type) {
        case ui::TextField::EventType::ATTACH_WITH_IME:{
            this->stopAllActions();
            auto moveTo = MoveTo::create(0.3, Vec2(screenSize.width/2-this->getBoundingBox().size.width/2, screenSize.height-this->getBoundingBox().size.height));
            this->runAction(moveTo);
            break;
        }
        case ui::TextField::EventType::DETACH_WITH_IME: {
            auto moveTo = MoveTo::create(0.3, Vec2(screenSize.width/2-this->getBoundingBox().size.width/2, screenSize.height/2-this->getBoundingBox().size.height/2));
            this->runAction(moveTo);
            break;
        }
        default:
            break;
    }
}

void RegisterSmallLayer::pawTFEvent(Ref* pSender, ui::TextField::EventType type) {
    switch (type) {
        case ui::TextField::EventType::ATTACH_WITH_IME:{
            this->stopAllActions();
            auto moveTo = MoveTo::create(0.3, Vec2(screenSize.width/2-this->getBoundingBox().size.width/2, screenSize.height-this->getBoundingBox().size.height));
            this->runAction(moveTo);
            break;
        }
        case ui::TextField::EventType::DETACH_WITH_IME: {
            auto moveTo = MoveTo::create(0.3, Vec2(screenSize.width/2-this->getBoundingBox().size.width/2, screenSize.height/2-this->getBoundingBox().size.height/2));
            this->runAction(moveTo);
            break;
        }
        default:
            break;
    }
}
