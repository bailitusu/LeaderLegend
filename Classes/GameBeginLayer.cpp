//
//  GameBeginLayer.cpp
//  OctLegend
//
//  Created by zc on 16/9/27.
//
//

#include "GameBeginLayer.h"
#include "CommonFunc.h"
#include "Setting.h"


#include "HouYiCard.h"
#include "ChangECard.h"
#include "TaoTieCard.h"
#include "XingTianCard.h"
#include "XuanWuCard.h"
#include "FengBoCard.h"
#include "FengHouCard.h"
#include "SuanYuCard.h"

#include "DunJiaTianShu.h"
#include "FuBenLayer.h"
#include "LingShoLayer.h"
#include "Bag.h"
#include "TuJianLayer.h"

#include "LoadingLayer.h"
#include "PvpMatchLayer.h"

#include "RoleInfoLayer.h"
#include "CreateTreasureLayer.h"
bool GameBeginLayer::init() {
    if (!Layer::init()) {
        return  false;
    }
    return true;
}

Scene* GameBeginLayer::createScene() {
    Scene* scene = Scene::create();
    GameBeginLayer* layer = GameBeginLayer::create();
    scene->addChild(layer);
    layer->initGameBeginLayer();
    return scene;
}

//void GameBeginLayer::onEnter() {
//    this->initGameBeginLayer();
//
//}

void GameBeginLayer::initGameBeginLayer() {
    this->backgroundOne = Sprite::create("diban.png");
    CommonFunc::setSpriteSize(this->backgroundOne, screenSize.width*1.1);
    this->backgroundOne->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height/2+origin.y));
    this->backgroundOne->setLocalZOrder(-100);
    this->addChild(this->backgroundOne);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("battle_bgm1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("battle_bgm1.mp3",true);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
//    this->backgroundTwo = Sprite::create("beijing_right.png");
//    CommonFunc::setSpriteSize(this->backgroundTwo, screenSize.width);
//    this->backgroundTwo->setPosition(Vec2(screenSize.width/2+origin.x+screenSize.width, screenSize.height/2+origin.y));
//    this->backgroundTwo->setLocalZOrder(-100);
//    this->addChild(this->backgroundTwo);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto liston = EventListenerTouchOneByOne::create();
    liston->onTouchBegan = CC_CALLBACK_2(GameBeginLayer::onTouchBegan, this);
    liston->onTouchMoved = CC_CALLBACK_2(GameBeginLayer::onTouchMoved, this);
    liston->onTouchEnded = CC_CALLBACK_2(GameBeginLayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(liston, this);
    
    
    this->dragon = Dragon::create();
    this->dragon->initDragonShuXing();
    this->dragon->retain();
    
    this->playerBag = Bag::create();
    this->playerBag->taoZiNum = 100;
    this->playerBag->retain();
    
    this->cardFormatJJC(HouYiCard::create(),"houyi_idle_0.png", 0, DunJiaTianShu::create());
    this->cardFormatJJC(XuanWuCard::create(),"xuanwu_idle_0.png", 1, DunJiaTianShu::create());
    this->cardFormatJJC(XingTianCard::create(),"xingtian_idle_0.png", 2, DunJiaTianShu::create());
    this->cardFormatJJC(ChangECard::create(),"change_idle_0.png", 3, DunJiaTianShu::create());
    this->cardFormatJJC(TaoTieCard::create(),"taotie_idle_0.png", 4, DunJiaTianShu::create());
    this->cardFormatJJC(FengHouCard::create(),"fenghou_idle_0.png", 5, DunJiaTianShu::create());
    this->cardFormatJJC(FengBoCard::create(),"fengbo_idle_0.png", 6, DunJiaTianShu::create());
    this->cardFormatJJC(SuanYuCard::create(),"suanyu_idle_0.png", 7, DunJiaTianShu::create());
    
    
    this->cardFormatPVE(HouYiCard::create(),"houyi_idle_0.png", 0, DunJiaTianShu::create());
    
    this->cardFormatPVE(XuanWuCard::create(),"xuanwu_idle_0.png", 1, DunJiaTianShu::create());
    this->cardFormatPVE(XingTianCard::create(),"xingtian_idle_0.png", 2, DunJiaTianShu::create());
    this->cardFormatPVE(ChangECard::create(),"change_idle_0.png", 3, DunJiaTianShu::create());
    this->cardFormatPVE(TaoTieCard::create(),"taotie_idle_0.png", 4, DunJiaTianShu::create());
    this->cardFormatPVE(FengHouCard::create(),"fenghou_idle_0.png", 5, DunJiaTianShu::create());
    this->cardFormatPVE(FengBoCard::create(),"fengbo_idle_0.png", 6, DunJiaTianShu::create());
    this->cardFormatPVE(SuanYuCard::create(),"suanyu_idle_0.png", 7, DunJiaTianShu::create());


    this->renWu = ui::Button::create("jingjichang.png");
    CommonFunc::initButton(this->renWu, CC_CALLBACK_2(GameBeginLayer::renWuBtn, this), 145, Vec2(380, 252));
    this->addChild(this->renWu,50);
    this->createUINameLabel("英雄殿堂",Vec2(this->renWu->getPosition().x+23,this->renWu->getPosition().y+25));
    
    this->buZhen = ui::Button::create("buzhenjianzhu.png");
    CommonFunc::initButton(this->buZhen, CC_CALLBACK_2(GameBeginLayer::buZhenBtn, this), 160, Vec2(255, 85));
    this->addChild(this->buZhen,50);
    this->createUINameLabel("演武场",Vec2(this->buZhen->getPosition().x,this->buZhen->getPosition().y+60));
    
    this->zhuXian = ui::Button::create("pve.png");
    CommonFunc::initButton(this->zhuXian, CC_CALLBACK_2(GameBeginLayer::zhuXianBtn, this), 180, Vec2(90, 85));
    this->addChild(this->zhuXian,50);
    this->createUINameLabel("征战",Vec2(this->zhuXian->getPosition().x+2,this->zhuXian->getPosition().y+40));
    
    this->lingShou = ui::Button::create("longjitan.png");
    CommonFunc::initButton(this->lingShou, CC_CALLBACK_2(GameBeginLayer::lingShouBtn, this),108, Vec2(155, 210));
    this->addChild(this->lingShou,50);
    this->createUINameLabel("祭坛",Vec2(this->lingShou->getPosition().x,this->lingShou->getPosition().y+50));
    
    this->jingJiChang = ui::Button::create("tujianjianzhu.png");
    CommonFunc::initButton(this->jingJiChang, CC_CALLBACK_2(GameBeginLayer::jingJiChangBtn, this), 110, Vec2(553, 185));
    this->addChild(this->jingJiChang,50);
    this->createUINameLabel("竞技场",Vec2(this->jingJiChang->getPosition().x,this->jingJiChang->getPosition().y+60));
    
    this->shangDian = ui::Button::create("shangcheng.png");
    CommonFunc::initButton(this->shangDian, CC_CALLBACK_2(GameBeginLayer::shangDianBtn, this), 158, Vec2(606, 68));
    this->addChild(this->shangDian,50);
    this->createUINameLabel("商城",Vec2(this->shangDian->getPosition().x,this->shangDian->getPosition().y+60));
//    auto scale = this->backgroundOne->getScale();
//    this->buZhen = ui::Button::create("buzhen.png");
//    CommonFunc::initButton(this->buZhen, CC_CALLBACK_2(GameBeginLayer::buZhenBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10/scale, screenSize.height/3*2/scale));
//    this->backgroundOne->addChild(this->buZhen,50);
//    
//    this->faBao = ui::Button::create("fabao.png");
//    CommonFunc::initButton(this->faBao, CC_CALLBACK_2(GameBeginLayer::faBaoBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10*2/scale, screenSize.height/3*2/scale));
//    this->backgroundOne->addChild(this->faBao,50);
//    
//    this->jingJiChang = ui::Button::create("jingjichang.png");
//    CommonFunc::initButton(this->jingJiChang, CC_CALLBACK_2(GameBeginLayer::jingJiChangBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10*3/scale, screenSize.height/3*2/scale));
//    this->backgroundOne->addChild(this->jingJiChang,50);
//    
//    this->juHun = ui::Button::create("juhun.png");
//    CommonFunc::initButton(this->juHun, CC_CALLBACK_2(GameBeginLayer::juHunBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10*4/scale, screenSize.height/3*2/scale));
//    this->backgroundOne->addChild(this->juHun,50);
//    
//    this->lingShou = ui::Button::create("lingshou.png");
//    CommonFunc::initButton(this->lingShou, CC_CALLBACK_2(GameBeginLayer::lingShouBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10/scale, screenSize.height/3/scale));
//    this->backgroundOne->addChild(this->lingShou,50);
//    
//    this->renWu = ui::Button::create("renwu.png");
//    CommonFunc::initButton(this->renWu, CC_CALLBACK_2(GameBeginLayer::renWuBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10*2/scale, screenSize.height/3/scale));
//    this->backgroundOne->addChild(this->renWu,50);
//    
//    this->tianFu = ui::Button::create("tianfu.png");
//    CommonFunc::initButton(this->tianFu, CC_CALLBACK_2(GameBeginLayer::tianFuBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10*3/scale, screenSize.height/3/scale));
//    this->backgroundOne->addChild(this->tianFu,50);
//    
//    this->zhuXian = ui::Button::create("zhuxian.png");
//    CommonFunc::initButton(this->zhuXian, CC_CALLBACK_2(GameBeginLayer::zhuXianBtn, this), screenSize.width/10/scale, Vec2(screenSize.width/10*4/scale, screenSize.height/3/scale));
//    this->backgroundOne->addChild(this->zhuXian,50);
    RoleInfoLayer* roleInfoLayer = RoleInfoLayer::create();
    roleInfoLayer->setContentSize(Size(380, 50));
    //roleInfoLayer->setContentSize(Size(120, 120));
    roleInfoLayer->initRoleInfoLayer();
    roleInfoLayer->setPosition(Vec2(190, screenSize.height-45));
   // roleInfoLayer->setPosition(Vec2(5, screenSize.height-215));
    this->addChild(roleInfoLayer,100);
    
//    Sprite* vipSp = Sprite::create("vip12.png");
//    CommonFunc::setSpriteSize(vipSp, 50);
//    vipSp->setPosition(100,screenSize.height-67);//x:118
//    this->addChild(vipSp,150);
    
    Sprite* playerTX = Sprite::create("playertx3.png");
    CommonFunc::setSpriteSize(playerTX, 80);//110
    //playerTX->setPosition(Vec2(playerTX->getBoundingBox().size.width/2-2, screenSize.height-playerTX->getBoundingBox().size.height/2+12));
    playerTX->setPosition(playerTX->getBoundingBox().size.width/2+5,screenSize.height-playerTX->getBoundingBox().size.height/2);
    this->addChild(playerTX,100);
    
    Sprite* playerNameBgSp = Sprite::create("infoBg.png");
    CommonFunc::setShowAllSpriteSize(playerNameBgSp, 130,35);
    playerNameBgSp->setPosition(Vec2(120, screenSize.height-22));
    this->addChild(playerNameBgSp,50);
    
    this->playerNameLabel = Label::createWithTTF("虎虎", "fonts/kaiti.ttf", 20);
    playerNameLabel->setTextColor(Color4B(255, 255, 255, 255));
    playerNameLabel->setDimensions(120, 30);
    playerNameLabel->setPosition(Vec2(playerNameBgSp->getPosition().x, playerNameBgSp->getPosition().y-5));
    playerNameLabel->setAlignment(TextHAlignment::CENTER);
    this->addChild(playerNameLabel,75);
    
    
    Sprite* zhanliBgSp = Sprite::create("zhanliBg.png");
    CommonFunc::setShowAllSpriteSize(zhanliBgSp, 150, 25);
    zhanliBgSp->setPosition(Vec2(140, screenSize.height-48));
    this->addChild(zhanliBgSp,50);
    
    Label* zlLabel = Label::createWithTTF("战力", "fonts/hanyixuejunti.ttf", 18);
    zlLabel->setTextColor(Color4B(228, 80, 62, 255));
    zlLabel->setDimensions(40, 25);
    zlLabel->setPosition(Vec2(zhanliBgSp->getPosition().x-20, zhanliBgSp->getPosition().y-3));
    zlLabel->setAlignment(TextHAlignment::LEFT);
    this->addChild(zlLabel,75);
    
    this->zhanliNumLabel = Label::createWithTTF("140021", "fonts/hanyixuejunti.ttf", 16);
    zhanliNumLabel->setTextColor(Color4B(254, 231, 119, 255));
    zhanliNumLabel->setDimensions(100, 25);
    zhanliNumLabel->setPosition(Vec2(zhanliBgSp->getPosition().x+53, zhanliBgSp->getPosition().y-4));
    zhanliNumLabel->setAlignment(TextHAlignment::LEFT);
    this->addChild(zhanliNumLabel,75);
}

void GameBeginLayer::createUINameLabel(std::string text, cocos2d::Vec2 position) {
    Sprite* uiBg = Sprite::create("mingchengUIBg.png");
    CommonFunc::setSpriteSize(uiBg, 80);
    uiBg->setPosition(position);
    this->addChild(uiBg,100);
    
    Label* uiLabel = Label::createWithTTF(text, "fonts/hanyixuejunti.ttf", 16);
    uiLabel->setDimensions(80, 20);
    uiLabel->setTextColor(dragonFontColor);
    uiLabel->setAlignment(TextHAlignment::CENTER);
    uiLabel->setPosition(Vec2(position.x, position.y-3));
    this->addChild(uiLabel,150);
}

void GameBeginLayer::cardFormatJJC(Card* card,std::string imageName, int standIndex,Treasure* treasure) {
    
    
   // card->initCardSprite(imageName);
  //  this->player->setCardsPositon(card, standIndex,50);
    card->retain();
    auto jjcData = SetRoleData::create();
    jjcData->xiaoImageName = card->cardName+"_tx.jpg";
    jjcData->imageName = imageName;
    jjcData->cellIndex = standIndex;
    jjcData->magicGoods = treasure;
    jjcData->magicGoods->retain();
    jjcData->card = card;
    jjcData->noBring = false;
    this->jjcRoleData.pushBack(jjcData);
    
}

void GameBeginLayer::cardFormatPVE(Card* card,std::string imageName, int standIndex,Treasure* treasure) {
  //  card->initCardSprite(imageName);
    //  this->player->setCardsPositon(card, standIndex,50);
    card->retain();
    
    auto pveData = SetRoleData::create();
    pveData->xiaoImageName = card->cardName+"_tx.jpg";
    pveData->imageName = imageName;
    pveData->cellIndex = standIndex;
    pveData->magicGoods = treasure;
    pveData->magicGoods->retain();
    pveData->card = card;
    pveData->noBring = false;
    this->pveRoleData.pushBack(pveData);
}

void GameBeginLayer::buZhenBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
//    if (type == ui::Widget::TouchEventType::ENDED) {
//        auto setRoleScene = SetRoleFormatlayer::createScene();
//        SetRoleFormatlayer* layer = SetRoleFormatlayer::create();
//        layer->setContentSize(screenSize);
//        setRoleScene->addChild(layer);
//        
//        for (int i = 0; i < this->jjcRoleData.size(); i++) {
//            layer->roleData.pushBack(this->jjcRoleData.at(i));
//        }
//        layer->preLayerName = "buzhen";
//        layer->initSetRoleFormatLayer();
//        Director::getInstance()->pushScene(TransitionFade::create(1.0f, setRoleScene));
//    }
    if (type == ui::Widget::TouchEventType::BEGAN) {
        if (this->zanWeiKaiFangSpBg == NULL && this->zanWeiKaiFangLabel == NULL) {
            this->zanWeiKaiFang();
        }
        
    }

}

void GameBeginLayer::faBaoBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    
}

void GameBeginLayer::jingJiChangBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        auto matchScene = PvpMatchLayer::createScene();
        PvpMatchLayer* layer = PvpMatchLayer::create();
        layer->setContentSize(screenSize);
        matchScene->addChild(layer);
        layer->initMatchLayer();
//        Director::getInstance()->pushScene(TransitionFade::create(1.0f, matchScene));
        this->enterLoadingLayer("replace", matchScene);
        
    }

}

void GameBeginLayer::shangDianBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        if (this->zanWeiKaiFangSpBg == NULL && this->zanWeiKaiFangLabel == NULL) {
             this->zanWeiKaiFang();
        }
//        CreateTreasureLayer* layer = CreateTreasureLayer::create();
//        layer->setContentSize(screenSize);
//        layer->setPosition(screenSize.width/2-layer->getBoundingBox().size.width/2,screenSize.height/2-layer->getBoundingBox().size.height/2);
//        layer->initCreateFabaoLayer();
//        this->addChild(layer, 200);
        
    }
}

void GameBeginLayer::enterLoadingLayer(std::string pushType, cocos2d::Scene *nextScene) {
    auto scene = LoadingLayer::CreateScene();
    LoadingLayer* loadLayer = LoadingLayer::GetInstance();
    loadLayer->setContentSize(screenSize);
    scene->addChild(loadLayer);
    loadLayer->pushType = pushType;
    loadLayer->nextScene = nextScene;
    loadLayer->initLoadLayer();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void GameBeginLayer::zanWeiKaiFang() {
    this->zanWeiKaiFangSpBg = Sprite::create("mingchengUIBg.png");
  //  CommonFunc::setShowAllSpriteSize(this->zanWeiKaiFangSpBg, 150, <#float height#>)
    CommonFunc::setSpriteSize(this->zanWeiKaiFangSpBg, 150);
    this->zanWeiKaiFangSpBg->setPosition(screenSize.width/2, screenSize.height/2);
    this->zanWeiKaiFangSpBg->setOpacity(0);
    this->addChild(this->zanWeiKaiFangSpBg,500);
    
    this->zanWeiKaiFangLabel = Label::createWithTTF("暂未开放", "fonts/hanyixuejunti.ttf", 24);
    this->zanWeiKaiFangLabel->setDimensions(150, this->zanWeiKaiFangSpBg->getBoundingBox().size.height);
    this->zanWeiKaiFangLabel->setTextColor(dragonFontColor);
    this->zanWeiKaiFangLabel->setAlignment(TextHAlignment::CENTER);
    this->zanWeiKaiFangLabel->setPosition(Vec2(screenSize.width/2, screenSize.height/2-12));
    this->zanWeiKaiFangLabel->setOpacity(0);
    this->addChild(this->zanWeiKaiFangLabel,550);
    
    auto appearBg = FadeTo::create(0.5, 255);
    auto disappearBg = FadeTo::create(1.5, 0);
    
    auto appearLabel = FadeTo::create(0.5, 255);
    auto disappearLabel = FadeTo::create(1.5, 0);
    auto block = CallFunc::create(CC_CALLBACK_0(GameBeginLayer::removeZanWeiKaiFang, this));
    this->zanWeiKaiFangSpBg->runAction(Sequence::create(appearBg,disappearBg,NULL));
    this->zanWeiKaiFangLabel->runAction(Sequence::create(appearLabel,disappearLabel,block,NULL));
    
}

void GameBeginLayer::removeZanWeiKaiFang() {
    this->zanWeiKaiFangLabel->stopAllActions();
    this->zanWeiKaiFangSpBg->stopAllActions();
    this->zanWeiKaiFangLabel->removeFromParentAndCleanup(true);
    this->zanWeiKaiFangLabel = NULL;
    this->zanWeiKaiFangSpBg->removeFromParentAndCleanup(true);
    this->zanWeiKaiFangSpBg = NULL;
}

void GameBeginLayer::lingShouBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        auto lingShoScene = LingShoLayer::createScene();
        LingShoLayer* layer = LingShoLayer::create();
        layer->setContentSize(screenSize);
        
        lingShoScene->addChild(layer);
        layer->myBag = this->playerBag;
        layer->myDragon = this->dragon;
        layer->initLingShoLayer();
        
        this->enterLoadingLayer("replace", lingShoScene);
       // Director::getInstance()->pushScene(TransitionFade::create(1.0f, lingShoScene));
    }

}

void GameBeginLayer::renWuBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        auto tuJianScene = TuJianLayer::createScene();
        TuJianLayer* layer = TuJianLayer::create();
        layer->setContentSize(screenSize);
        
        tuJianScene->addChild(layer);
        
        layer->initTuJianLayer();
        
        this->enterLoadingLayer("replace", tuJianScene);
       // Director::getInstance()->pushScene(TransitionFade::create(1.0f, tuJianScene));
    }

}

void GameBeginLayer::tianFuBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    
}

void GameBeginLayer::zhuXianBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        auto fuBenScene = FuBenLayer::createScene();
        FuBenLayer* layer = FuBenLayer::create();
        layer->setContentSize(screenSize);
        fuBenScene->addChild(layer);
        
        for (int i = 0; i < this->pveRoleData.size(); i++) {
            layer->myRoleData.pushBack(this->pveRoleData.at(i));
        }
        layer->initFuBenLayer();
        
        this->enterLoadingLayer("replace", fuBenScene);
       // Director::getInstance()->pushScene(TransitionFade::create(1.0f, fuBenScene));
    }

}

bool GameBeginLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    return true;
}

void GameBeginLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {

//    auto point = Director::getInstance()->convertToGL(touch->getLocationInView());
//    auto oldPoint = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
//    auto distance = point-oldPoint;
//    
//    if (this->backgroundOne->getPosition().x+distance.x > screenSize.width/2) {
//        this->backgroundOne->setPosition(screenSize.width/2,screenSize.height/2);
//        this->backgroundTwo->setPosition(screenSize.width*3/2,screenSize.height/2);
//    }else if (this->backgroundTwo->getPosition().x+distance.x < screenSize.width/2) {
//        this->backgroundTwo->setPosition(screenSize.width/2,screenSize.height/2);
//        this->backgroundOne->setPosition(-screenSize.width/2,screenSize.height/2);
//    }else {
//        this->backgroundOne->setPosition(this->backgroundOne->getPosition().x+distance.x,screenSize.height/2);
//        this->backgroundTwo->setPosition(this->backgroundTwo->getPosition().x+distance.x,screenSize.height/2);
//    }
    
}

void GameBeginLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
}



