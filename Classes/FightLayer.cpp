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
#include "HuangDiCard.h"
#include "FightField.h"
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
    this->player->xiangong = 10;
    this->enemyPlay->xiangong = 5;
    
    this->player->retain();
    this->enemyPlay->retain();
    
    
    for (int i = 0; i < 8; i ++) {
        
        auto playerHuangdi = HuangDiCard::create();
        playerHuangdi->initCardSprite("taotieLeft.png");
        playerHuangdi->playerName = "player";
        
        this->player->setCardsPositon(playerHuangdi, i,10+i);
       // playerHuangdi->retain();
        //        Vec2 position = Vec2(((MapCell*)(player->fMap->mapCellArray->objectAtIndex(i)))->position.x, ((MapCell*)(player->fMap->mapCellArray->objectAtIndex(i)))->position.y);
        //        ((MapCell*)(player->fMap->mapCellArray->objectAtIndex(i)))->obj = playerHuangdi;
        //        playerHuangdi->cardSprite->setPosition(position.x, position.y);
        
    }
    this->player->initCardStandArray();
    //   ((MapCell*)(player->fMap->mapCellArray->objectAtIndex(0)))->obj->didBeHit(100);
    for (int i = 0; i < 8; i ++) {
        
        auto enemyHuangdi = HuangDiCard::create();
        enemyHuangdi->playerName = "enemyPlayer";
        enemyHuangdi->initCardSprite("taotieRight.png");
        this->enemyPlay->setCardsPositon(enemyHuangdi, i, 10+i);
       // enemyHuangdi->retain();
        //        Vec2 position = Vec2(((MapCell*)(enemy->fMap->mapCellArray->objectAtIndex(i)))->position.x, ((MapCell*)(enemy->fMap->mapCellArray->objectAtIndex(i)))->position.y);
        //
        //        enemyHuangdi->cardSprite->setPosition(position.x, position.y);
        
        //   enemy->fMap->addChild(enemyHuangdi->cardSprite,10);
        
    }
    this->enemyPlay->initCardStandArray();
    
    background = Sprite::create("begin.jpg");
    CommonFunc::setSpriteSize(background, screenSize.width);
    background->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height/2+origin.y));
    background->setLocalZOrder(-100);
    this->addChild(background);
}

bool FightLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    auto touchLocation = touch->getLocationInView();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    
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
