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
    
    this->enemyPlay = FightPlayer::create();
    this->enemyPlay->fightLayer = this;
    this->enemyPlay->initMap("rightmap.png", "right");
    this->enemyPlay->fMap->setPosition(screenSize.width-(enemyPlay->fMap->getBoundingBox().size.width+20+origin.x),80+origin.y);
    
    this->player->enemy = this->enemyPlay;
    this->enemyPlay->enemy = this->player;
    this->player->xiangong = 20;
    this->enemyPlay->xiangong = 15;
    
    this->player->retain();
    this->enemyPlay->retain();
    
    this->player->initTackCard(XingTianCard::create(), "xuanwu_left1.png", 0, "player");
    this->player->initTackCard(XuanWuCard::create(), "xingtian_left1.png", 3, "player");
    this->player->initTackCard(XingTianCard::create(), "change_left1.png", 5, "player");
    this->player->initTackCard(ChangECard::create(), "fengbo_left1.png", 6, "player");
    this->player->initTackCard(SuanYuCard::create(), "fenghou_left1.png", 9, "player");
    this->player->initTackCard(ChangECard::create(), "suanyu_left1.png", 10, "player");
    this->player->initTackCard(ChangECard::create(), "taotie_left1.png", 12, "player");
    this->player->initTackCard(ChangECard::create(), "houyi_left1.png", 15, "player");
//    for (int i = 0; i < 8; i ++) {
//        
//        auto playerHuangdi = HouYiCard::create();
//        playerHuangdi->initCardSprite("longLeft.png");
//        playerHuangdi->playerName = "player";
//       
//        this->player->setCardsPositon(playerHuangdi, i,10+i);
//        playerHuangdi->forPlayer = this->player;
//        playerHuangdi->fPro = FightProgress::create();
//        playerHuangdi->fPro->hpProBg->setPosition(playerHuangdi->cardSprite->getPosition().x,playerHuangdi->cardSprite->getPosition().y+playerHuangdi->cardSprite->getBoundingBox().size.height+10);
//        this->player->fMap->addChild(playerHuangdi->fPro->hpProBg,10+i+10);
//        
//        playerHuangdi->fPro->hpPro->setPosition(playerHuangdi->fPro->hpProBg->getPosition());
//        this->player->fMap->addChild(playerHuangdi->fPro->hpPro,10+i+20);
//
//        
//        playerHuangdi->fPro->initNuQiPro(0);
//        playerHuangdi->fPro->nuqiProBg->setPosition(playerHuangdi->cardSprite->getPosition().x,playerHuangdi->cardSprite->getPosition().y+playerHuangdi->cardSprite->getBoundingBox().size.height+5);
//        this->player->fMap->addChild(playerHuangdi->fPro->nuqiProBg, 10+i+10);
//        
//        playerHuangdi->fPro->nuqiPro->setPosition(playerHuangdi->fPro->nuqiProBg->getPosition());
//        this->player->fMap->addChild(playerHuangdi->fPro->nuqiPro,10+i+20);
//        playerHuangdi->initFightShuXing();
//        playerHuangdi->fPro->retain();
//        playerHuangdi->retain();
////        playerHuangdi->fPro->hpPro->setPosition(0, 0);
////        playerHuangdi->fPro->hpProBg->addChild( playerHuangdi->fPro->hpPro,51);
////        
//        
//       // playerHuangdi->retain();
//        //        Vec2 position = Vec2(((MapCell*)(player->fMap->mapCellArray->objectAtIndex(i)))->position.x, ((MapCell*)(player->fMap->mapCellArray->objectAtIndex(i)))->position.y);
//        //        ((MapCell*)(player->fMap->mapCellArray->objectAtIndex(i)))->obj = playerHuangdi;
//        //        playerHuangdi->cardSprite->setPosition(position.x, position.y);
//        
//    }
    this->player->initCardStandArray();
    //   ((MapCell*)(player->fMap->mapCellArray->objectAtIndex(0)))->obj->didBeHit(100);
//    for (int i = 0; i < 8; i ++) {
//        
//        auto enemyHuangdi = ChangECard::create();
//        enemyHuangdi->playerName = "enemyPlayer";
//        enemyHuangdi->initCardSprite("longRight.png");
//        this->enemyPlay->setCardsPositon(enemyHuangdi, i, 10+i);
//        enemyHuangdi->forPlayer = this->enemyPlay;
//        
//        enemyHuangdi->fPro = FightProgress::create();
//        enemyHuangdi->fPro->hpProBg->setPosition(enemyHuangdi->cardSprite->getPosition().x,enemyHuangdi->cardSprite->getPosition().y+enemyHuangdi->cardSprite->getBoundingBox().size.height+10);
//        this->enemyPlay->fMap->addChild(enemyHuangdi->fPro->hpProBg,10+i+10);
//        
//        enemyHuangdi->fPro->hpPro->setPosition(enemyHuangdi->fPro->hpProBg->getPosition());
//        this->enemyPlay->fMap->addChild(enemyHuangdi->fPro->hpPro,10+i+20);
//        
//        enemyHuangdi->fPro->initNuQiPro(0);
//        enemyHuangdi->fPro->nuqiProBg->setPosition(enemyHuangdi->cardSprite->getPosition().x,enemyHuangdi->cardSprite->getPosition().y+enemyHuangdi->cardSprite->getBoundingBox().size.height+5);
//        this->enemyPlay->fMap->addChild(enemyHuangdi->fPro->nuqiProBg, 10+i+10);
//        
//        enemyHuangdi->fPro->nuqiPro->setPosition(enemyHuangdi->fPro->nuqiProBg->getPosition());
//        this->enemyPlay->fMap->addChild(enemyHuangdi->fPro->nuqiPro,10+i+20);
//        
//        enemyHuangdi->fPro->retain();
//        enemyHuangdi->retain();
//       // enemyHuangdi->retain();
//        //        Vec2 position = Vec2(((MapCell*)(enemy->fMap->mapCellArray->objectAtIndex(i)))->position.x, ((MapCell*)(enemy->fMap->mapCellArray->objectAtIndex(i)))->position.y);
//        //
//        //        enemyHuangdi->cardSprite->setPosition(position.x, position.y);
//        
//        //   enemy->fMap->addChild(enemyHuangdi->cardSprite,10);
//        
//    }
    this->enemyPlay->initTackCard(XingTianCard::create(), "xuanwu_right1.png", 0, "enemyPlayer");
    this->enemyPlay->initTackCard(XuanWuCard::create(), "xingtian_right1.png", 3, "enemyPlayer");
    this->enemyPlay->initTackCard(XingTianCard::create(), "change_right1.png", 5, "enemyPlayer");
    this->enemyPlay->initTackCard(XingTianCard::create(), "fengbo_right1.png", 6, "enemyPlayer");
    this->enemyPlay->initTackCard(ChangECard::create(), "fenghou_right1.png", 9, "enemyPlayer");
    this->enemyPlay->initTackCard(ChangECard::create(), "suanyu_right1.png", 10, "enemyPlayer");
    this->enemyPlay->initTackCard(ChangECard::create(), "taotie_right1.png", 12, "enemyPlayer");
    this->enemyPlay->initTackCard(ChangECard::create(), "houyi_right1.png", 15, "enemyPlayer");
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
    field->startFight();
    field->retain();
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
