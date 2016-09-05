//
//  FightScene.cpp
//  OctLegend
//
//  Created by zc on 16/8/8.
//
//

#include "FightLayer.h"
#include "FightMap.h"
#include "CommonFunc.h"
#include "MapCell.h"
#include "Setting.h"

#include "FightField.h"
#include "FightProgress.h"

#include "HuangDiCard.h"
#include "HouYiCard.h"
#include "ChangECard.h"
#include "TaoTieCard.h"
#include "XingTianCard.h"
#include "XuanWuCard.h"
#include "FengBoCard.h"
#include "FengHouCard.h"
#include "SuanYuCard.h"

#include "Dragon/Dragon.h"
#include "Setting/ActionWait.h"
#include "Treasure/HuFuTreasure.h"
#include "DunJiaTianShu.h"
#include "BingFaTreasure.h"
#include "YiBingBuDao.h"
#include "MianYiCuoZhiTreasure.h"
#include "FanTanWuLiTreasure.h"
#include "FanTanFaShuTreasure.h"
Scene* FightLayer::createScene() {
    
    Scene* scene = Scene::create();
    
    FightLayer* layer = FightLayer::create();
    
    scene->addChild(layer);
    layer->initFightLayer();
    return scene;
}

bool FightLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    
    return true;
}

void FightLayer::initFightLayer() {
    ID = 1;
    // this->setTouchEnabled(true);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto liston = EventListenerTouchOneByOne::create();
    liston->onTouchBegan = CC_CALLBACK_2(FightLayer::onTouchBegan, this);
    liston->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(liston, this);
    // Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this, true);
    this->player = FightPlayer::create();
    this->player->fightLayer = this;
    this->player->initMap("leftmap.png", "left");
    this->player->fMap->setPosition(20+origin.x, 80+origin.y);
    this->player->initDragon("dragon_left.png");
    this->player->fDragon->dragonSprite->setPosition(150+origin.x,screenSize.height+origin.y);
    
    this->enemyPlay = FightPlayer::create();
    this->enemyPlay->fightLayer = this;
    this->enemyPlay->initMap("rightmap.png", "right");
    this->enemyPlay->fMap->setPosition(screenSize.width-(enemyPlay->fMap->getBoundingBox().size.width+20+origin.x),80+origin.y);
    this->enemyPlay->initDragon("dragon_right.png");
    this->enemyPlay->fDragon->dragonSprite->setPosition(screenSize.width-150+origin.x,screenSize.height+origin.y);
    
    this->player->enemy = this->enemyPlay;
    this->enemyPlay->enemy = this->player;
    this->player->xiangong = 20;
    this->enemyPlay->xiangong = 15;
    
    this->player->retain();
    this->enemyPlay->retain();
    
    this->player->initTackCard(XingTianCard::create(), "jianshengwalk_0.png", 0, "player",HuFuTreasure::create());
    this->player->initTackCard(XuanWuCard::create(), "xingtian_left1.png", 3, "player",YiBingBuDao::create());
    this->player->initTackCard(FengHouCard::create(), "fengbo_left1.png", 5, "player",HuFuTreasure::create());
    this->player->initTackCard(HouYiCard::create(), "xiaoheiZhanLi_0.png", 6, "player",HuFuTreasure::create());
    this->player->initTackCard(SuanYuCard::create(), "fenghou_left1.png", 9, "player",HuFuTreasure::create());
    this->player->initTackCard(TaoTieCard::create(), "suanyu_left1.png", 10, "player",HuFuTreasure::create());
    this->player->initTackCard(ChangECard::create(), "taotie_left1.png", 12, "player",HuFuTreasure::create());
    this->player->initTackCard(FengBoCard::create(), "houyi_left1.png", 15, "player",HuFuTreasure::create());

    this->player->initCardStandArray();

    this->enemyPlay->initTackCard(XingTianCard::create(), "jianshengwalk_0.png", 0, "enemyPlayer",HuFuTreasure::create());
    this->enemyPlay->initTackCard(XuanWuCard::create(), "xingtian_right1.png", 3, "enemyPlayer",YiBingBuDao::create());
    this->enemyPlay->initTackCard(FengHouCard::create(),"fengbo_right1.png" , 5, "enemyPlayer",HuFuTreasure::create());
    this->enemyPlay->initTackCard(HouYiCard::create(), "xiaoheiZhanLi_0.png", 6, "enemyPlayer",HuFuTreasure::create());
    this->enemyPlay->initTackCard(SuanYuCard::create(), "fenghou_right1.png", 9, "enemyPlayer",HuFuTreasure::create());
    this->enemyPlay->initTackCard(TaoTieCard::create(), "suanyu_right1.png", 10, "enemyPlayer",HuFuTreasure::create());
    this->enemyPlay->initTackCard(ChangECard::create(), "taotie_right1.png", 12, "enemyPlayer",HuFuTreasure::create());
    this->enemyPlay->initTackCard(FengBoCard::create(), "houyi_right1.png", 15, "enemyPlayer",HuFuTreasure::create());
    this->enemyPlay->initCardStandArray();
    
//    Sprite* ttt = Sprite::create("taotieLeft.png");
//    ttt->setAnchorPoint(Vec2(0.5, 0));
//    ttt->setPosition(238, 177);
//    CommonFunc::setSpriteSize(ttt, 100);
//    this->addChild(ttt, 100);
    background = Sprite::create("begin.jpg");
    CommonFunc::setSpriteSize(background, screenSize.width);
    background->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height/2+origin.y));
    background->setLocalZOrder(-100);
    
//    auto bbbb= Sprite::create("longRight.png");
//    bbbb->setPosition(screenSize.width/2+origin.x,screenSize.height/2+origin.y);
//    CommonFunc::setSpriteSize(bbbb, 50);
//    this->addChild(bbbb);
//    auto aaa = Label::createWithTTF("1111111", "fonts/Marker Felt.ttf", 16);
////    aaa->setOpacity(255);
//    aaa->setString("eeeeeee");
//    aaa->setTextColor(Color4B(0, 0, 240, 255));
//    aaa->setPosition(screenSize.width/2+origin.x,screenSize.height/2+origin.y);
//    this->addChild(aaa,100);
    

    
    this->addChild(background);
}

void shifang() {
   // enemyHuangdi->fPro->retain();
    //playerHuangdi->fPro->retain();
    //    this->player->retain();
    //this->enemyPlay->retain();
    //playerHuangdi->retain();
    //field->retain();
    //fDragon->retain();
}

bool FightLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    auto touchLocation = touch->getLocationInView();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    
//    Card* aaa = this->player->cardArray.at(0);
   // aaa->fPro->nuqiPro->setPercentage(33);
    //aaa->fPro->hpPro->setPercentage(aaa->fPro->hpPro->getPercentage()+20);
//    ProgressFromTo* ac = ProgressFromTo::create(1.0, 0, 100);
//    aaa->fPro->hpPro->runAction(ac);
    auto field = FightField::create();
    field->player = this->player;
    field->enemyPlayer = this->enemyPlay;
   // field->startFight();
    field->retain();
//    if (this->player->fDragon->dragonSkillArray.size() == 0 && ) {
//        <#statements#>
//    }
    if (this->player->xiangong > this->enemyPlay->xiangong) {
        auto wait = ActionWait::create(1.0);
        auto apper = FadeTo::create(0.5, 255);
        auto disapper = FadeTo::create(0.5, 0);
        auto run = CallFunc::create(CC_CALLBACK_0(FightField::dragonRun,field,"player"));
        auto block = CallFunc::create(CC_CALLBACK_0(FightField::dragonBlock,field,"player"));
        this->player->fDragon->dragonSprite->runAction(Sequence::create(apper,disapper,run,wait,block, NULL));
    }else {
        auto wait = ActionWait::create(1.0);
        auto apper = FadeTo::create(0.5, 255);
        auto disapper = FadeTo::create(0.5, 0);
        auto run = CallFunc::create(CC_CALLBACK_0(FightField::dragonRun,field,"enemy"));
        auto block = CallFunc::create(CC_CALLBACK_0(FightField::dragonBlock,field,"enemy"));
        this->enemyPlay->fDragon->dragonSprite->runAction(Sequence::create(apper,disapper,run,wait,block, NULL));
    }
    return true;
}

void FightLayer::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
