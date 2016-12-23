//
//  PvpFightLayer.cpp
//  OctLegend
//
//  Created by zc on 16/11/3.
//
//

#include "PvpFightLayer.h"
#include "FightMap.h"
#include "CommonFunc.h"
#include "MapCell.h"
#include "Setting.h"
#include "FightProgress.h"
#include "Dragon.h"
#include "ActionWait.h"
#include "FightNetwork.h"
#include "ReadRecordFight.h"
#include "PvpMatchLayer.h"

#include "AllArmyGuWu.h"
#include "JiuXiaoLongYin.h"
#include "HuiMieBoDong.h"
#include "ZaiShengLongHou.h"
#include "ZhanYiGaoAng.h"
//std::string mykey = "zyh";
Scene* PvpFightLayer::createScene() {
    Scene* scene = Scene::create();
    return scene;
}

bool PvpFightLayer::init() {
    if (!Layer::init()) {
    
        return false;
    }
    this->roundNum = 0;
    return true;
}

void PvpFightLayer::initPvpLayer() {
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto liston = EventListenerTouchOneByOne::create();
    liston->onTouchBegan = CC_CALLBACK_2(PvpFightLayer::onTouchBegan, this);
    liston->onTouchMoved = CC_CALLBACK_2(PvpFightLayer::onTouchMoved, this);
    liston->onTouchEnded = CC_CALLBACK_2(PvpFightLayer::onTouchEnded, this);
    liston->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(liston, this);
    
    auto gameOverListon = EventListenerCustom::create("pvpGameOver", CC_CALLBACK_0(PvpFightLayer::gameOver, this));
    dispatcher->addEventListenerWithFixedPriority(gameOverListon, 1);
    
    auto roundOverListon = EventListenerCustom::create("pvpRoundOver", CC_CALLBACK_0(PvpFightLayer::roundOver, this));
    dispatcher->addEventListenerWithFixedPriority(roundOverListon, 1);
    
    this->player = FightPlayer::create();
    this->player->fpName = "player";
    this->player->fightLayer = this;
    this->player->initMap("leftmap.png", "left", Size(300,300));
    this->player->fMap->setPosition(-2+origin.x, 56+origin.y);
    this->player->fMap->setLocalZOrder(300);
    this->player->initDragon("dragon_left.png");
    this->player->fDragon->dragonSprite->setPosition(150+origin.x,screenSize.height+origin.y);
    
    this->playerEnemy = FightPlayer::create();
    this->playerEnemy->fpName = "enemyPlayer";
    this->playerEnemy->fightLayer = this;
    this->playerEnemy->initMap("rightmap.png", "right", Size(300,300));
    this->playerEnemy->fMap->setPosition(screenSize.width-(this->playerEnemy->fMap->getBoundingBox().size.width+5+origin.x),50+origin.y);
   // this->playerEnemy->fMap->setLocalZOrder(300);
    this->playerEnemy->initDragon("dragon_right.png");
    this->playerEnemy->fDragon->dragonSprite->setPosition(screenSize.width-150+origin.x,screenSize.height+origin.y);
    
    this->player->enemy = this->playerEnemy;
    this->playerEnemy->enemy = this->player;
    this->player->playerKey = myKey;
    
    this->player->retain();
    this->playerEnemy->retain();
    
    this->background = Sprite::create("duizhanjiemian.png");//bbg_arena.png
    CommonFunc::setSpriteSize(this->background, screenSize.width);
    this->background->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height/2+origin.y));
    this->background->setLocalZOrder(-100);
    this->addChild(background);
    
    this->chouTiBtn = ui::Button::create("choutibtn_left.png");
    this->chouTiBtn->setAnchorPoint(Vec2(1, 0.5));
    CommonFunc::initButton(this->chouTiBtn, CC_CALLBACK_2(PvpFightLayer::chouTibtnClick, this), screenSize.width*0.072, Vec2(screenSize.width, screenSize.height*0.072));
    this->addChild(this->chouTiBtn,200);
    
    this->initChouTiLayer();
    this->roundLabel = Label::createWithTTF("", "fonts/fangzhengjingheijianti.ttf", 42);
    this->roundLabel->setSystemFontSize(42);
    this->roundLabel->setDimensions(80, 40);
    this->roundLabel->setAlignment(TextHAlignment::CENTER);
    this->roundLabel->setTextColor(Color4B(215, 215, 215, 255));
    this->roundLabel->enableBold();
    this->roundLabel->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height-28));
   // this->roundLabel->setLineBreakWithoutSpace(true);
    this->addChild(this->roundLabel,150);
    
    this->isRounding = false;
    this->roundLabel->setString("30");
    this->timeNum = 30;
    schedule(schedule_selector(PvpFightLayer::daoJiShi), 1.0);
    
    Sprite* timeZhuangShiSp = Sprite::create("zhuangshi.png");
    CommonFunc::setSpriteSize(timeZhuangShiSp, 190);
    timeZhuangShiSp->setPosition(screenSize.width/2,screenSize.height-timeZhuangShiSp->getBoundingBox().size.height/2);
    this->addChild(timeZhuangShiSp,-50);
    
    Sprite* timeBiaoDiSp = Sprite::create("biaodi.png");
    CommonFunc::setSpriteSize(timeBiaoDiSp, 180);
    timeBiaoDiSp->setPosition(screenSize.width/2,screenSize.height-timeBiaoDiSp->getBoundingBox().size.height/2);
    this->addChild(timeBiaoDiSp,-70);
    
    this->leftChouTiBtn = ui::Button::create("choutibtn_right.png");
    this->leftChouTiBtn->setAnchorPoint(Vec2(0, 0.5));
    CommonFunc::initButton(this->leftChouTiBtn, CC_CALLBACK_2(PvpFightLayer::leftChouTiClick, this), screenSize.width*0.072, Vec2(0, screenSize.height*0.072));
    this->addChild(this->leftChouTiBtn,200);
    
    this->initLeftChouTi();

    this->currentLiangNum = 0;
    
//    ParticleSystem *cps = ParticleMeteor::create();
//    cps->setPosition(screenSize.width/2,screenSize.height/2);
//    cps->setLife(0.05f);
//    cps->setTotalParticles(100);
//    cps->setDuration(-1);
//    cps->setEmissionRate(1000);
//    cps->setPosVar(Point(screenSize.width/2,screenSize.height/2));
//    this->addChild(cps,5000);
}

void PvpFightLayer::createLiangGezi(float dur) {
    int tempShunxu[16] = {0,1,2,3,7,6,5,4,8,9,10,11,15,14,13,12};
    if (this->currentLiangNum > 15) {
        this->currentLiangNum = 0;
    }
    ParticleSystem *cps = ParticleSun::create();
    cps->setPosition(this->playerEnemy->fMap->mapCellArray.at(tempShunxu[this->currentLiangNum])->position);
    cps->setLife(0.05f);
    cps->setTotalParticles(100);
    cps->setDuration(0.5);
    cps->setEmissionRate(cps->getTotalParticles()/cps->getLife());
    cps->setPosVar(Point(20,20));
    this->playerEnemy->fMap->addChild(cps,1);
    this->currentLiangNum++;
}


void PvpFightLayer::leftChouTiClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        if((this->leftChouTi->getActionByTag(10) == NULL) && (this->leftChouTi->getActionByTag(100) == NULL)) {
            if (this->leftChouTi->getPosition().x < 0) {
                
                auto moveOut = MoveTo::create(0.3f, Vec2(0, this->leftChouTi->getPosition().y));
                moveOut->setTag(10);
                this->leftChouTiBtn->loadTextureNormal("choutibtn_left.png");
                this->leftChouTi->runAction(moveOut);
            }else {
                auto moveIn = MoveTo::create(0.3f, Vec2(-this->leftChouTi->getBoundingBox().size.width, this->leftChouTi->getPosition().y));
                
                moveIn->setTag(100);
                this->leftChouTiBtn->loadTextureNormal("choutibtn_right.png");
                this->leftChouTi->runAction(moveIn);
            }
        }
        
        
    }
}

void PvpFightLayer::chouTibtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        if((this->chouTiLayer->getActionByTag(10) == NULL) && (this->chouTiLayer->getActionByTag(100) == NULL)) {
            if (this->chouTiLayer->getPosition().x < screenSize.width) {
                
                auto moveIn = MoveTo::create(0.3f, Vec2(screenSize.width, this->chouTiLayer->getPosition().y));
                moveIn->setTag(10);
                this->chouTiBtn->loadTextureNormal("choutibtn_left.png");
                this->chouTiLayer->runAction(moveIn);
            }else {
                auto moveOut = MoveTo::create(0.3f, Vec2(screenSize.width-this->chouTiLayer->getBoundingBox().size.width, this->chouTiLayer->getPosition().y));
                
                moveOut->setTag(100);
                this->chouTiBtn->loadTextureNormal("choutibtn_right.png");
                this->chouTiLayer->runAction(moveOut);
            }
        }


    }

}

void PvpFightLayer::initChouTiLayer() {
    this->chouTiLayer = Layer::create();
    this->chouTiLayer->setContentSize(Size(screenSize.width*0.46, screenSize.height*0.75));
    this->chouTiLayer->setPosition(Vec2(screenSize.width, screenSize.height/2-this->chouTiLayer->getBoundingBox().size.height/2));
    this->addChild(chouTiLayer,150);
    
    Sprite* bg = Sprite::create("buzhenBg2.jpg");

    CommonFunc::setShowAllSpriteSize(bg, this->chouTiLayer->getBoundingBox().size.width, this->chouTiLayer->getBoundingBox().size.height);
    bg->setPosition(this->chouTiLayer->getBoundingBox().size.width/2,this->chouTiLayer->getBoundingBox().size.height/2);
    this->chouTiLayer->addChild(bg, -100);
    
    for (int i = 0; i < this->myTakeRoleData.size(); i++) {
        Sprite* gezi = Sprite::create("herotouxiangbg.png");
        CommonFunc::setShowAllSpriteSize(gezi, this->chouTiLayer->getBoundingBox().size.width/4-5, this->chouTiLayer->getBoundingBox().size.width/4-5);
        gezi->setPosition(Vec2(8+this->chouTiLayer->getBoundingBox().size.width/8+(this->chouTiLayer->getBoundingBox().size.width/4-5)*(i%4), this->chouTiLayer->getBoundingBox().size.height-(this->chouTiLayer->getBoundingBox().size.height/8+this->chouTiLayer->getBoundingBox().size.height/4*(i/4))-10 ));
        this->chouTiLayer->addChild(gezi,100);
        
        this->myTakeRoleData.at(i)->xiaoSp = Sprite::create(this->myTakeRoleData.at(i)->xiaoImageName);
        CommonFunc::setShowAllSpriteSize(this->myTakeRoleData.at(i)->xiaoSp, this->chouTiLayer->getBoundingBox().size.width/4-14, this->chouTiLayer->getBoundingBox().size.width/4-14);
        this->myTakeRoleData.at(i)->xiaoSp->setPosition(gezi->getPosition());
        this->chouTiLayer->addChild(this->myTakeRoleData.at(i)->xiaoSp,150);
        
        Label* cardNameLabel = Label::createWithTTF(this->myTakeRoleData.at(i)->card->cardZhongWenName, "fonts/kaiti.ttf", 12);
        cardNameLabel->setDimensions(this->myTakeRoleData.at(i)->xiaoSp->getBoundingBox().size.width, 20);
        cardNameLabel->setAlignment(TextHAlignment::CENTER);
        cardNameLabel->setPosition(this->myTakeRoleData.at(i)->xiaoSp->getPosition().x,this->myTakeRoleData.at(i)->xiaoSp->getPosition().y-25);
        cardNameLabel->setName("namelabel");
        cardNameLabel->setTextColor(Color4B(225, 225, 225, 255));
        this->chouTiLayer->addChild(cardNameLabel,200);
        
        Sprite* labelNameBg = Sprite::create("zhanliBg.png");
        CommonFunc::setShowAllSpriteSize(labelNameBg, this->myTakeRoleData.at(i)->xiaoSp->getBoundingBox().size.width, 20);
        labelNameBg->setPosition(cardNameLabel->getPosition().x,cardNameLabel->getPosition().y+3);
        labelNameBg->setName("nameBgSp");
        this->chouTiLayer->addChild(labelNameBg,170);
    }
    
    this->buShuOverBtn = ui::Button::create("classbtn.png");
    CommonFunc::initButton(this->buShuOverBtn, CC_CALLBACK_2(PvpFightLayer::buShubtnClick, this), screenSize.width/8, Vec2(screenSize.width*0.22, screenSize.height*0.075));
    this->buShuOverBtn->setTitleFontSize(8);
    this->buShuOverBtn->setTitleAlignment(TextHAlignment::RIGHT);
    this->buShuOverBtn->setTitleText("部署完成");
    this->buShuOverBtn->setTitleColor(Color3B(255, 255, 255));
    this->addChild(this->buShuOverBtn,100);
}

void PvpFightLayer::initLeftChouTi() {
    this->leftChouTi = Layer::create();
    this->leftChouTi->setContentSize(Size(screenSize.width*0.46, screenSize.height*0.75));
    this->leftChouTi->setPosition(Vec2(-this->leftChouTi->getBoundingBox().size.width, screenSize.height/2-this->leftChouTi->getBoundingBox().size.height/2));

    this->addChild(leftChouTi,500);
    
    Sprite* bg = Sprite::create("buzhenBg2.jpg");
    
    CommonFunc::setShowAllSpriteSize(bg, this->leftChouTi->getBoundingBox().size.width, this->leftChouTi->getBoundingBox().size.height);
    bg->setPosition(this->leftChouTi->getBoundingBox().size.width/2,this->leftChouTi->getBoundingBox().size.height/2);
    this->leftChouTi->addChild(bg, -100);
    
    for (int i = 0; i < 5; i++) {
        SkillGezi* skill = SkillGezi::create();
        
        skill->geZiSp = Sprite::create("herotouxiangbg.png");
        CommonFunc::setShowAllSpriteSize(skill->geZiSp, this->leftChouTi->getBoundingBox().size.width/4-5, this->leftChouTi->getBoundingBox().size.width/4-5);
        skill->geZiSp->setPosition(Vec2(8+this->leftChouTi->getBoundingBox().size.width/8+(this->leftChouTi->getBoundingBox().size.width/4-5)*(i%4), this->leftChouTi->getBoundingBox().size.height-(this->leftChouTi->getBoundingBox().size.height/8+this->leftChouTi->getBoundingBox().size.height/4*(i/4))-10 ));
        this->leftChouTi->addChild(skill->geZiSp,100);
        skill->index = i;
        skill->geziPositon = skill->geZiSp->getPosition();
        
        char skillImage[20] = {0};
        sprintf(skillImage, "s_%d.jpg",i);
        switch (i) {
            case 0:
                skill->obj = AllArmyGuWu::create();
                break;
            case 1:
                skill->obj = HuiMieBoDong::create();
                break;
            case 2:
                skill->obj = JiuXiaoLongYin::create();
                break;
            case 3:
                skill->obj = ZaiShengLongHou::create();
                break;
            case 4:
                skill->obj = ZhanYiGaoAng::create();
                break;
            default:
                break;
        }
        skill->isEnable = false;
        skill->isChoice = false;
        skill->obj->dragonSkillSp = Sprite::create(skillImage);

        CommonFunc::setShowAllSpriteSize(skill->obj->dragonSkillSp, this->leftChouTi->getBoundingBox().size.width/4-14, this->leftChouTi->getBoundingBox().size.width/4-14);
        skill->obj->dragonSkillSp->setPosition(skill->geZiSp->getPosition());
        skill->obj->dragonSkillSp->setOpacity(125);
        this->leftChouTi->addChild(skill->obj->dragonSkillSp,150);
        skill->obj->retain();
        
        skill->choiceLabel = Label::createWithTTF("选中", "fonts/kaiti.ttf", 12);
        skill->choiceLabel->setOpacity(0);
        skill->choiceLabel->setDimensions(40, 20);
        skill->choiceLabel->setAnchorPoint(Vec2(1, 0));
        skill->choiceLabel->setPosition(skill->geZiSp->getPosition().x+skill->geZiSp->getBoundingBox().size.width/2-5,skill->geZiSp->getPosition().y-skill->geZiSp->getBoundingBox().size.height/2+5);
        this->leftChouTi->addChild(skill->choiceLabel,300);
        this->dragonSkillData.pushBack(skill);
    }

}

void PvpFightLayer::buShubtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        
        if (this->chouTiLayer->getPosition().x < screenSize.width) {
            
            auto moveIn = MoveTo::create(0.2f, Vec2(screenSize.width, this->chouTiLayer->getPosition().y));
            moveIn->setTag(10);
            
            this->chouTiLayer->runAction(moveIn);
        }
       // this->chouTiBtn->setTouchEnabled(false);
        
        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
        rapidjson::Value playerKey;
        rapidjson::Value battleKey;
        rapidjson::Value cardsArray(rapidjson::kArrayType);
        rapidjson::Value cellsArray(rapidjson::kArrayType);
        
        playerKey.SetString(myKey.c_str(), (unsigned int)strlen(myKey.c_str()));
        
        battleKey.SetString(this->battleKey.c_str(), (unsigned int)strlen(this->battleKey.c_str()));
        doc.AddMember("playerkey", playerKey, allocator);
        doc.AddMember("battlekey", battleKey, allocator);
        
        rapidjson::Value cardName;
        for (int i = 0; i < this->myTakeRoleData.size(); i++) {
            if (this->myTakeRoleData.at(i)->card->cardSprite != NULL && this->myTakeRoleData.at(i)->isPvpBuShu == false) {
                const char* tempName = this->myTakeRoleData.at(i)->card->cardName.c_str();
                cardName.SetString(tempName, (unsigned int)strlen(tempName));
                cardsArray.PushBack(cardName, allocator);
                cellsArray.PushBack(this->myTakeRoleData.at(i)->cellIndex, allocator);
                this->myTakeRoleData.at(i)->isPvpBuShu = true;
            }
        }
        printf("%d",cardsArray.Size());
        doc.AddMember("cardkeys", cardsArray, allocator);
        doc.AddMember("cellids", cellsArray, allocator);
        rapidjson::Value skillkey;
        if (this->currentClickSkill  != NULL) {
            skillkey.SetString(this->currentClickSkill->obj->dargonName.c_str(), (unsigned int)strlen(this->currentClickSkill->obj->dargonName.c_str()));
            doc.AddMember("guardiankey",skillkey , allocator);
        }

        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);
        
        FightNetwork* net = FightNetwork::GetInstance();
       // printf("%s/n",buffer.GetString());
       // this->buShuOverBtn->setTitleColor(Color3B(70, 80, 89));
        this->buShuOverBtn->setEnabled(false);
        this->roundLabel->setSystemFontSize(18);
        this->roundLabel->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height-40));
        this->roundLabel->setString("请等待");
        unschedule(schedule_selector(PvpFightLayer::daoJiShi));
        net->createPostHttp(PvpBushuPostUrl, this, httpresponse_selector(PvpFightLayer::buShuResponse), buffer.GetString());
    }

}

void PvpFightLayer::buShuResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    if (response->isSucceed()) {
        
        
        std::vector<char>* info = response->getResponseData();
        std::string infoStr  = std::string(info->begin(),info->end());
        rapidjson::Document doc;
        doc.Parse<0>(infoStr.c_str());
        if(doc.HasParseError())
        {
            printf("bushu-----GetParseError%u\n", doc.GetParseError());
            return;
        }
        int code = doc["code"].GetInt();
        if (code == 0) {
            scheduleOnce(schedule_selector(PvpFightLayer::checkFightOk), 1.5);
//            for (int i = 0; i < 3; i++) {
//
//            }
          //  this->checkFightOk(10);
            
        }else {
           // this->buShuOverBtn->setTitleColor(Color3B(255, 255, 255));
            this->buShuOverBtn->setEnabled(true);
            std::string message = doc["message"].GetString();
             printf("-------%s--------",message.c_str());
        }
    }else {
       // this->buShuOverBtn->setTitleColor(Color3B(255, 255, 255));
        this->buShuOverBtn->setEnabled(true);
    }
}

void PvpFightLayer::daoJiShi(float dur) {
    this->timeNum--;
    char rnum[30] = {0};
    sprintf(rnum, "%d",this->timeNum);
    this->roundLabel->setString(rnum);
    if (this->timeNum < 1) {
        unschedule(schedule_selector(PvpFightLayer::daoJiShi));
        this->buShubtnClick(this->buShuOverBtn, ui::Widget::TouchEventType::BEGAN);
        
    }

}

void PvpFightLayer::checkFightOk(float dur) {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    rapidjson::Value tempKey;
    tempKey.SetString(myKey.c_str(), (unsigned int)strlen(myKey.c_str()));
    printf("%s",myKey.c_str());
    doc.AddMember("playerkey", tempKey, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    
    FightNetwork* net = FightNetwork::GetInstance();
    net->createPostHttp(PvpCheckBushuOkPostUrl, this, httpresponse_selector(PvpFightLayer::checkFightResponse), buffer.GetString());
}

void PvpFightLayer::checkFightResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    if (response->isSucceed()) {
        std::vector<char>* info = response->getResponseData();
        std::string infoStr  = std::string(info->begin(),info->end());
     //   printf("%s", infoStr.c_str());
        rapidjson::Document doc;
        doc.Parse<0>(infoStr.c_str());
        if(doc.HasParseError())
        {
            printf("message-----GetParseError%u\n", doc.GetParseError());
            return;
        }
        int code = doc["code"].GetInt();
        if (code == 0) {
            this->buShuOverBtn->setOpacity(0);

          //  unschedule(schedule_selector(PvpFightLayer::checkFightOk));
            for (int i = 0; i < this->myTakeRoleData.size(); i++) {
                if(this->myTakeRoleData.at(i)->card->cardSprite != NULL) {
                    this->myTakeRoleData.at(i)->card->cardSprite->removeFromParentAndCleanup(true);
                    this->myTakeRoleData.at(i)->card->cardSprite = NULL;
                }
            }
            ReadRecordFight* rf = ReadRecordFight::getInstance();
            if (rf->player == NULL) {
                rf->player = this->player;
            }
            if (rf->playerEnemy == NULL) {
                rf->playerEnemy = this->playerEnemy;
            }
            rf->currentSmallIndex = 0;
            rf->currentBigIndex = -1;
            rf->currentDragonIndex = 0;
            rf->currentJson = infoStr.c_str();
            
            this->roundNum++;
            char rnum[10] = {0};
            this->isRounding = true;
            sprintf(rnum, "第%d回合",this->roundNum);
            this->roundLabel->setSystemFontSize(18);
            this->roundLabel->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height-40));
            this->roundLabel->setString(rnum);
            
            rf->gameOverLabel = this->roundLabel;
            rf->readPlayerInfo();
            rf->readBigNextRecord();
            
          //  schedule(schedule_selector(PvpFightLayer::createLiangGezi), 0.5);
        }else {
            scheduleOnce(schedule_selector(PvpFightLayer::checkFightOk), 1.5);
            std::string message = doc["message"].GetString();
            printf("-----------%s----------/n",message.c_str());
        }

    }else {
        scheduleOnce(schedule_selector(PvpFightLayer::checkFightOk), 1.5);
    }
    

}

void PvpFightLayer::roundOver() {
    this->chouTiBtn->setTouchEnabled(true);
    this->player->fMap->setLocalZOrder(300);
  //  this->buShuOverBtn->setTitleColor(Color3B(255, 255, 255));
    this->buShuOverBtn->setEnabled(true);
    this->buShuOverBtn->setOpacity(255);
    this->isRounding = false;
    this->roundLabel->setSystemFontSize(42);
    this->roundLabel->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height-28));
    this->roundLabel->setString("30");
    this->timeNum = 30;
    
    
    this->jisuanEnableSkill();
    
    schedule(schedule_selector(PvpFightLayer::daoJiShi), 1.0);
    
   // unschedule(schedule_selector(PvpFightLayer::createLiangGezi));
    
}

void PvpFightLayer::jisuanEnableSkill() {
    int onrKindsBollNumArray[5] = {0};
    for (int i = 0; i < this->player->haveBoll.size(); i++) {
        switch (this->player->haveBoll.at(i)->bollType) {
            case 1:
                onrKindsBollNumArray[4] = onrKindsBollNumArray[4]+1;
                if (onrKindsBollNumArray[4] >= 3) {
                    this->enableSkill(3);
                }
                break;
            case 10:
                onrKindsBollNumArray[3] = onrKindsBollNumArray[3]+10;
                if (onrKindsBollNumArray[3] >= 30) {
                    this->enableSkill(30);
                }
                break;
            case 100:
                onrKindsBollNumArray[2] = onrKindsBollNumArray[2]+100;
                if (onrKindsBollNumArray[2] >= 300) {
                    this->enableSkill(300);
                }
                break;
            case 1000:
                onrKindsBollNumArray[1] = onrKindsBollNumArray[1]+1000;
                if (onrKindsBollNumArray[1] >= 3000) {
                    this->enableSkill(3000);
                }
                break;
            case 10000:
                onrKindsBollNumArray[0] = onrKindsBollNumArray[0]+10000;
                if (onrKindsBollNumArray[0] >= 30000) {
                    this->enableSkill(30000);
                }
                break;
            default:
                break;
        }
    }

    
}

void PvpFightLayer::enableSkill(int skillType) {
    for (int i = 0; i < this->dragonSkillData.size(); i++) {
        if (this->dragonSkillData.at(i)->obj->zuheNum == skillType) {
            this->dragonSkillData.at(i)->obj->dragonSkillSp->setOpacity(255);
            this->dragonSkillData.at(i)->isEnable = true;
            int eraseSumNum = 3;
            Vector<Boll*> removeBoll;
            for (int j = 0; j < this->player->haveBoll.size(); j++) {
                if(this->player->haveBoll.at(j)->bollType == skillType/3) {
                    if (eraseSumNum > 0) {
                        removeBoll.pushBack(this->player->haveBoll.at(j));
                        eraseSumNum--;
                        
                    }else {
                        break;
                    }
                }
            }
            for (int n = 0; n < removeBoll.size(); n++) {
                this->player->haveBoll.eraseObject(removeBoll.at(n));
            }
            return;
        }
    }
}

void PvpFightLayer::gameOver() {
    
    scheduleOnce(schedule_selector(PvpFightLayer::enterMatchScene), 1.0);
}

void PvpFightLayer::enterMatchScene(float dur) {
    auto matchScene = PvpMatchLayer::createScene();
    PvpMatchLayer* layer = PvpMatchLayer::create();
    layer->setContentSize(screenSize);
    matchScene->addChild(layer);
    layer->initMatchLayer();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, matchScene));
}

Vec2 PvpFightLayer::countCardOrigonPoint(Card *card, FightPlayer *tempPlayer) {
    Vec2 point = Vec2(0, 0);
    point.x = card->cardSprite->getPosition().x-tempPlayer->fMap->getBoundingBox().size.width/8+tempPlayer->fMap->getPosition().x+this->getPosition().x;
    point.y = card->cardSprite->getPosition().y-tempPlayer->fMap->getBoundingBox().size.width/8+tempPlayer->fMap->getPosition().y+this->getPosition().y;
    return point;
}

bool PvpFightLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    auto touchLocation = touch->getLocationInView();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    if (this->isRounding == false) {
        for (int i = 0; i < this->myTakeRoleData.size(); i++) {
            auto xiaoCardPoint = Vec2(this->myTakeRoleData.at(i)->xiaoSp->getPosition().x-this->myTakeRoleData.at(i)->xiaoSp->getBoundingBox().size.width/2, this->myTakeRoleData.at(i)->xiaoSp->getPosition().y-this->myTakeRoleData.at(i)->xiaoSp->getBoundingBox().size.height/2);
            xiaoCardPoint = xiaoCardPoint+this->chouTiLayer->getPosition();
            Rect rect = Rect(xiaoCardPoint.x,xiaoCardPoint.y,this->myTakeRoleData.at(i)->xiaoSp->getBoundingBox().size.width,this->myTakeRoleData.at(i)->xiaoSp->getBoundingBox().size.height);
            
            if (rect.containsPoint(touchLocation)) {
                if (this->myTakeRoleData.at(i)->xiaoSp->getOpacity() > 125 ) {
                    this->myTakeRoleData.at(i)->card->initCardSprite(this->myTakeRoleData.at(i)->imageName);
                    auto point = Vec2(xiaoCardPoint.x+this->myTakeRoleData.at(i)->xiaoSp->getBoundingBox().size.width/2,xiaoCardPoint.y+this->myTakeRoleData.at(i)->xiaoSp->getBoundingBox().size.height/2);
                    this->myTakeRoleData.at(i)->card->cardSprite->setPosition(point-this->player->fMap->getPosition());
                    this->player->fMap->addChild(this->myTakeRoleData.at(i)->card->cardSprite,150);
                    this->myTakeRoleData.at(i)->xiaoSp->setOpacity(125);
                    
                    break;
                }
            }
        }
        this->moveCard = NULL;
        for (int i = 0; i < this->myTakeRoleData.size(); i++) {
            if (this->myTakeRoleData.at(i)->card->cardSprite != NULL && this->myTakeRoleData.at(i)->isPvpBuShu == false) {
                auto tempPoint = this->countCardOrigonPoint(this->myTakeRoleData.at(i)->card,this->player);
                Rect rect = Rect(tempPoint.x, tempPoint.y, this->player->fMap->getBoundingBox().size.width/4, this->player->fMap->getBoundingBox().size.width/4);
                if (rect.containsPoint(touchLocation)) {
                    if (this->myTakeRoleData.at(i)->isPvpBuShu == false) {
                        this->moveCard = this->myTakeRoleData.at(i)->card;
                    }
                    
                    //     printf("%s",this->currentMoveCard->cardName.c_str());
                    // schedule(schedule_selector(SetRoleFormatlayer::showInfo), 1.0);
                   // return true;
                    break;
                }
            }
        }
        
        
        for (int j = 0; j < this->dragonSkillData.size(); j++) {
            auto tempPoint = Vec2(this->dragonSkillData.at(j)->geZiSp->getPosition().x-this->dragonSkillData.at(j)->geZiSp->getBoundingBox().size.width/2, this->dragonSkillData.at(j)->geZiSp->getPosition().y-this->dragonSkillData.at(j)->geZiSp->getBoundingBox().size.height/2);
            tempPoint = tempPoint+this->leftChouTi->getPosition();
            Rect rect = Rect(tempPoint.x,tempPoint.y,this->dragonSkillData.at(j)->geZiSp->getBoundingBox().size.width,this->dragonSkillData.at(j)->geZiSp->getBoundingBox().size.height);
            if (rect.containsPoint(touchLocation)) {
                if (this->dragonSkillData.at(j)->isEnable == true) {
                    if (this->dragonSkillData.at(j)->isChoice == false) {
                        this->dragonSkillData.at(j)->isChoice = true;
                        this->dragonSkillData.at(j)->choiceLabel->setOpacity(255);
                        if (this->currentClickSkill != NULL) {
                            this->currentClickSkill->isChoice = false;
                            this->currentClickSkill->choiceLabel->setOpacity(0);
                        }
                        this->currentClickSkill = this->dragonSkillData.at(j);
                        break;
                    }else {
                        this->dragonSkillData.at(j)->choiceLabel->setOpacity(0);
                        this->dragonSkillData.at(j)->isChoice = false;
                        this->currentClickSkill = NULL;
                    }
                }
            }
        }
        
        
    }else {
//        for (int k = 0; k < this->player->fMap->getChildren().size(); k++) {
//            if (this->player->fMap->getChildren().at(k)->getTag() == 999) {
//                auto temp = (Sprite*)(this->player->fMap->getChildren().at(k));
//                auto point = Vec2(temp->getPosition().x-temp->getBoundingBox().size.width/2,temp->getPosition().y-temp->getBoundingBox().size.height/2);
//                point = point+this->player->fMap->getPosition();
//                Rect rect = Rect(point.x, point.y, temp->getBoundingBox().size.width, temp->getBoundingBox().size.height);
//                if (rect.containsPoint(touchLocation)) {
//                    temp->removeFromParentAndCleanup(true);
//                    break;
//                    
//                }
//            }
//        }
        for (int k = 0; k < this->player->allAppearBoll.size(); k++) {
            auto temp = this->player->allAppearBoll.at(k)->bollSp;
            auto point = Vec2(temp->getPosition().x-temp->getBoundingBox().size.width/2,temp->getPosition().y-temp->getBoundingBox().size.height/2);
            point = point+this->player->fMap->getPosition();
            Rect rect = Rect(point.x, point.y, temp->getBoundingBox().size.width, temp->getBoundingBox().size.height);
            if (rect.containsPoint(touchLocation)) {
                temp->removeFromParentAndCleanup(true);
                temp = NULL;
                this->player->haveBoll.pushBack(this->player->allAppearBoll.at(k));
                this->player->allAppearBoll.eraseObject(this->player->allAppearBoll.at(k));
                break;
            }
        }
        
        this->liziQiu = Sprite::create();
       // CommonFunc::setSpriteSize(this->liziQiu, 80);
        this->liziQiu->setPosition(touchLocation);
        this->addChild(this->liziQiu,5000);
        
      //  this->cps = ParticleSun::create();
        
    }
    
    
       return true;
}

void PvpFightLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    auto point = Director::getInstance()->convertToGL(touch->getLocationInView());
    auto oldPoint = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
    if (this->isRounding == false) {
        if (this->moveCard != NULL) {

            auto distance = point-oldPoint;
            this->moveCard->cardSprite->setPosition(this->moveCard->cardSprite->getPosition()+distance);
            
        }
    }else {
        if (this->liziQiu != NULL) {
            this->liziQiu->setPosition(point);
            
            ParticleSystem *cps = ParticleSun::create();

            cps->setPosition(0,5/this->liziQiu->getScaleX());
            cps->setLife(0.05f);
            cps->setTotalParticles(10);
            cps->setEmissionRate(cps->getTotalParticles()/cps->getLife());
            this->liziQiu->addChild(cps);
            
        }
    }

}
void PvpFightLayer::longJuanFengBlock() {
    this->longJuanFengSp->stopAllActions();
    this->longJuanFengSp->removeFromParentAndCleanup(true);
    this->longJuanFengSp= NULL;
}
void PvpFightLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    if (this->isRounding == false) {
        if (this->moveCard != NULL) {
            
            bool isTake = false;
            for (int i = 0; i < this->player->fMap->mapCellArray.size(); i++) {
                Vec2 point = Vec2(0,0);
                point.x = this->player->fMap->mapCellArray.at(i)->position.x-this->player->fMap->getBoundingBox().size.width/8+this->player->fMap->getPosition().x+this->getPosition().x;
                point.y = this->player->fMap->mapCellArray.at(i)->position.y-this->player->fMap->getBoundingBox().size.width/8+this->player->fMap->getPosition().y+this->getPosition().y;
                Rect rect = Rect(point.x,point.y,this->player->fMap->getBoundingBox().size.width/4,this->player->fMap->getBoundingBox().size.width/4);
                //            printf("%f----x\n",this->currentMoveCard->cardSprite->getPosition().x+this->player->fMap->getPosition().x);
                //            printf("%f----y\n", this->currentMoveCard->cardSprite->getPosition().y+this->player->fMap->getPosition().y);
                if (rect.containsPoint(Vec2(this->moveCard->cardSprite->getPosition().x+this->player->fMap->getPosition().x, this->moveCard->cardSprite->getPosition().y+this->player->fMap->getPosition().y))) {
                    isTake = true;
                    
                    Vec2 defaultCardPoint = Vec2(0, 0);
                    for (int j = 0; j < this->player->fMap->mapCellArray.size(); j++) {
                        if (this->player->fMap->mapCellArray.at(j)->obj != NULL) {
                            
                            if (((Card*)this->player->fMap->mapCellArray.at(j)->obj)->cardName.compare(this->moveCard->cardName) == 0) {
                                defaultCardPoint = this->player->fMap->mapCellArray.at(j)->position;
                                this->player->fMap->mapCellArray.at(j)->obj = NULL;
                                break;
                            }
                        }
                    }
                    if (this->player->fMap->mapCellArray.at(i)->obj != NULL) {
                        if (defaultCardPoint == Vec2(0, 0)) {
                            
                            for (int n = 0; n < this->myTakeRoleData.size(); n++) {
                                if (this->myTakeRoleData.at(n)->card->cardName.compare(((Card*)this->player->fMap->mapCellArray.at(i)->obj)->cardName) == 0) {
                                    this->myTakeRoleData.at(n)->xiaoSp->setOpacity(255);
                                    ((Card*)this->player->fMap->mapCellArray.at(i)->obj)->cardSprite->removeFromParentAndCleanup(true);
                                    ((Card*)this->player->fMap->mapCellArray.at(i)->obj)->cardSprite = NULL;
                                    break;
                                }
                                
                            }
                        }else {
                            ((Card*)this->player->fMap->mapCellArray.at(i)->obj)->cardSprite->setPosition(defaultCardPoint);
                            ((Card*)this->player->fMap->mapCellArray.at(i)->obj)->cellIndex = this->moveCard->cellIndex;
                            this->player->fMap->mapCellArray.at(this->moveCard->cellIndex)->obj = ((Card*)this->player->fMap->mapCellArray.at(i)->obj);
                        }
                        
                    }
                    this->moveCard->cardSprite->setPosition(this->player->fMap->mapCellArray.at(i)->position);
                    this->player->fMap->mapCellArray.at(i)->obj = this->moveCard;
                    this->moveCard->cellIndex = i;
                    break;
                }
            }
            if (isTake == false) {
                for (int j = 0; j < this->player->fMap->mapCellArray.size(); j++) {
                    if (this->player->fMap->mapCellArray.at(j)->obj != NULL) {
                        
                        if (((Card*)this->player->fMap->mapCellArray.at(j)->obj)->cardName.compare(this->moveCard->cardName) == 0) {
                            
                            this->player->fMap->mapCellArray.at(j)->obj = NULL;
                            break;
                        }
                    }
                }
                
                for (int i = 0; i < this->myTakeRoleData.size(); i++) {
                    if (this->myTakeRoleData.at(i)->card->cardName.compare(this->moveCard->cardName) == 0) {
                        this->moveCard->cardSprite->removeFromParentAndCleanup(true);
                        this->moveCard->cardSprite = NULL;
                        
                        this->myTakeRoleData.at(i)->xiaoSp->setOpacity(255);
                        break;
                    }
                }
                
            }
            
            for (int k = 0; k < this->myTakeRoleData.size(); k++) {
                this->myTakeRoleData.at(k)->cellIndex = this->myTakeRoleData.at(k)->card->cellIndex;
                //  printf("%s----%d\n",this->roleData.at(k)->card->cardName.c_str(),this->roleData.at(k)->cellIndex);
            }
        }

    }else {
        this->liziQiu->removeAllChildrenWithCleanup(true);
        this->liziQiu->removeFromParentAndCleanup(true);
        this->liziQiu = NULL;
        if (this->longJuanFengSp == NULL) {
            CommonFunc::removeAnimation();
            this->longJuanFengSp = Sprite::create("full_0.png");
            this->longJuanFengSp->setScale(2);
            this->longJuanFengSp->setPosition(this->playerEnemy->fMap->getPosition().x+this->playerEnemy->fMap->getBoundingBox().size.width/2,this->playerEnemy->fMap->getPosition().y+this->playerEnemy->fMap->getBoundingBox().size.height/2);
            this->addChild(this->longJuanFengSp,6000);
            
            Animate* longjuanFeng = CommonFunc::creatAnimation("full_%d.png", 12, animationFactor*12, 1);
            auto block = CallFunc::create(CC_CALLBACK_0(PvpFightLayer::longJuanFengBlock, this));
            this->longJuanFengSp->runAction(Sequence::create(longjuanFeng,block,NULL));
        }
    }
   
}

