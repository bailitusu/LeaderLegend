//
//  RegisterLayer.cpp
//  OctMountain
//
//  Created by zc on 16/11/22.
//
//

#include "RegisterLayer.h"
#include "CommonFunc.h"
#include "Setting.h"
#include "GameBeginLayer.h"

bool RegisterLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

void RegisterLayer::initRegisterLayer() {
    Sprite* background = Sprite::create("registerBg.jpg");
    CommonFunc::setShowAllSpriteSize(background, screenSize.width, screenSize.height);
    background->setPosition(screenSize.width/2,screenSize.height/2);
    this->addChild(background,-100);
    
    youkeBtn = ui::Button::create("btnBg1.png");
    youkeBtn->setPressedActionEnabled(true);
    youkeBtn->setScale(1.5);
    youkeBtn->setTitleText("游客进入");
    youkeBtn->addTouchEventListener(CC_CALLBACK_2(RegisterLayer::youkeClick, this));
    youkeBtn->setPosition(Vec2(screenSize.width/2,screenSize.height/6));
    this->addChild(youkeBtn,100);
    
    enterBtn = ui::Button::create("btnBg1.png");
    enterBtn->setPressedActionEnabled(true);
    enterBtn->setScale(1.5);
    enterBtn->setTitleText("快速注册");
    enterBtn->addTouchEventListener(CC_CALLBACK_2(RegisterLayer::enterClick, this));
    enterBtn->setPosition(Vec2(screenSize.width/2,screenSize.height/6+50));
    this->addChild(enterBtn,100);
    
    std::string userID =  UserDefault::getInstance()->getStringForKey("userID");
    if (userID.compare("") != 0) {
        //  if (UserDefault::getInstance()->isXMLFileExist()) {
        scheduleOnce(schedule_selector(RegisterLayer::autoLogin), 1.0);
        // this->autoLogin(0);
        youkeBtn->setEnabled(false);
        enterBtn->setEnabled(false);
        youkeBtn->setOpacity(0);
        enterBtn->setOpacity(0);
        //  }
    }

    

}

void RegisterLayer::autoLogin(float dur) {
    
    std::string userID =  UserDefault::getInstance()->getStringForKey("userID");
    std::string pwd = UserDefault::getInstance()->getStringForKey("pwd");
    std::string isAutoLogin = UserDefault::getInstance()->getStringForKey("auto");
    
    if (isAutoLogin.compare("true") == 0) {

        
        Sprite* autoLoadingBg = Sprite::create("mingchengUIBg.png");
        //  CommonFunc::setShowAllSpriteSize(this->zanWeiKaiFangSpBg, 150, <#float height#>)
        CommonFunc::setSpriteSize(autoLoadingBg, 150);
        autoLoadingBg->setPosition(screenSize.width/2, screenSize.height/2);
        this->addChild(autoLoadingBg,500);
        
        Label* autoLoadingLabel = Label::createWithTTF("自动登录中", "fonts/hanyixuejunti.ttf", 22);
        autoLoadingLabel->setDimensions(150, autoLoadingLabel->getBoundingBox().size.height);
        autoLoadingLabel->setTextColor(dragonFontColor);
        autoLoadingLabel->setAlignment(TextHAlignment::CENTER);
        autoLoadingLabel->setPosition(Vec2(screenSize.width/2, screenSize.height/2));
        this->addChild(autoLoadingLabel,550);
        scheduleOnce(schedule_selector(RegisterLayer::autoLoginBlock), 1.0);

    }else {
        youkeBtn->setEnabled(true);
        enterBtn->setEnabled(true);
        youkeBtn->setOpacity(255);
        enterBtn->setOpacity(255);
    }

}

void RegisterLayer::autoLoginBlock(float dur) {
    std::string userID =  UserDefault::getInstance()->getStringForKey("userID");
    std::string pwd = UserDefault::getInstance()->getStringForKey("pwd");
    std::string isAutoLogin = UserDefault::getInstance()->getStringForKey("auto");
    
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    rapidjson::Value account;
    rapidjson::Value password;
    account.SetString(userID.c_str(), (unsigned int)strlen(userID.c_str()));
    doc.AddMember("account", account, allocator);
    password.SetString(pwd.c_str(), (unsigned int)strlen(pwd.c_str()));
    doc.AddMember("password", password, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    
    FightNetwork* net = FightNetwork::GetInstance();
    net->createPostHttp(loginPostUrl, this, httpresponse_selector(RegisterLayer::autoLoginResponse), buffer.GetString());
}

void RegisterLayer::youkeClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {

        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

        doc.AddMember("account","", allocator);
        doc.AddMember("password","", allocator);
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);
        
        FightNetwork* net = FightNetwork::GetInstance();
        net->createPostHttp(zhucePostUrl, this, httpresponse_selector(RegisterLayer::quickSignUpResponse),buffer.GetString());

    }

}

void RegisterLayer::autoLoginResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    if (response->isSucceed()) {
        //        Scene* nextScene = GameBeginLayer::createScene();
        //        Director::getInstance()->replaceScene(TransitionFade::create(1.0, nextScene));
        
        std::vector<char>* info = response->getResponseData();
        std::string infoStr  = std::string(info->begin(),info->end());
        //    printf("%s",infoStr.c_str());
        
        rapidjson::Document doc;
        doc.Parse<0>(infoStr.c_str());
        if (doc.HasParseError()) {
            printf("自动登录失败");
            return;
        }
        int code = doc["code"].GetInt();
        if (code == 0) {
            rapidjson::Value& data = doc["data"];
            printf("%s",data["id"].GetString());
            myKey = data["id"].GetString();
            printf("%s",myKey.c_str());

            Scene* nextScene = GameBeginLayer::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0, nextScene));
            
        }
    }
}

void RegisterLayer::quickSignUpResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    if (response->isSucceed()) {
        std::vector<char>* info = response->getResponseData();
        std::string infoStr  = std::string(info->begin(),info->end());
        printf("%s",infoStr.c_str());

        rapidjson::Document doc;
        doc.Parse<0>(infoStr.c_str());
        if (doc.HasParseError()) {
            printf("游客登录失败");
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

void RegisterLayer::enterClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        this->smallLoginLayer = LoginSmallLayer::create();
        this->smallLoginLayer->setContentSize(Size(screenSize.width/2,screenSize.height*2/3));
        this->smallLoginLayer->initLoginSmallLayer();
        this->smallLoginLayer->setPosition(screenSize.width/2-this->smallLoginLayer->getBoundingBox().size.width/2,screenSize.height/2-this->smallLoginLayer->getBoundingBox().size.height/2);
        this->addChild(this->smallLoginLayer,150);
        
        this->youkeBtn->setEnabled(false);
        this->youkeBtn->setOpacity(0);
        this->enterBtn->setEnabled(false);
        this->enterBtn->setOpacity(0);
    }
}

Scene* RegisterLayer::createScene() {
    Scene* scene = Scene::create();
    RegisterLayer* regLayer = RegisterLayer::create();
    regLayer->setContentSize(screenSize);
    regLayer->initRegisterLayer();
    scene->addChild(regLayer);
    return scene;
}
