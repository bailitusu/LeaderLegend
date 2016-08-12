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
#include "FightPlayer.h"
Scene* FightLayer::createScene() {
    
    Scene* scene = Scene::create();
    
    Layer* layer = FightLayer::create();
    
    scene->addChild(layer);
    return scene;
}

bool FightLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    player = FightPlayer::create();
    player->fightLayer = this;
    player->initMap("leftmap.png", "left");
    player->fMap->setPosition(20+origin.x, 80+origin.y);
    
    enemy = FightPlayer::create();
    enemy->fightLayer = this;
    enemy->initMap("rightmap.png", "right");
    enemy->fMap->setPosition(screenSize.width-(enemy->fMap->getBoundingBox().size.width+20+origin.x),80+origin.y);
    
    player->enemy = enemy;
    enemy->enemy = player;
//    leftMap = FightMap::create();
//    leftMap->init("leftmap.png", "left");
//
//    leftMap->map->setPosition(0, 0);
//    leftMap->setPosition(20+origin.x, 80+origin.y);
//
//    this->addChild(leftMap);
//    // fightmap->map->setPosition(screenSize.width*0.25+origin.x, screenSize.height/3+origin.y);
//    
//    rightMap = FightMap::create();
//    rightMap->init("rightmap.png", "right");
//    rightMap->map->setPosition(0,0);
//    rightMap->setPosition(screenSize.width-(rightMap->getBoundingBox().size.width+20+origin.x), 80+origin.y);
//    this->addChild(rightMap);

    
    for (int i = 0; i < 16; i ++) {
        auto enemy = HuangDiCard::create();
        //enemy->setPosition(screenSize.width*0.39+origin.x, screenSize.height*0.506+origin.y);
        //enemy->setPosition(270-40+origin.x, 165+30+origin.y);
        Vec2 position = Vec2(((MapCell*)(player->fMap->mapCellArray->objectAtIndex(i)))->position.x, ((MapCell*)(player->fMap->mapCellArray->objectAtIndex(i)))->position.y);
        ((MapCell*)(player->fMap->mapCellArray->objectAtIndex(i)))->obj = enemy;
        enemy->cardSprite->setPosition(position.x, position.y);
        // enemy->setPosition(0,0);
//        enemy->setAnchorPoint(Vec2(0.5, 0));
        // player->setFlippedX(true);
//        CommonFunc::setSpriteSize(enemy->cardSprite, screenSize.width*0.075);
        player->fMap->addChild(enemy->cardSprite,10);
        break;
    }
    ((MapCell*)(player->fMap->mapCellArray->objectAtIndex(0)))->obj->didBeHit(100);
    for (int i = 0; i < 16; i ++) {
        auto enemyplayer = Sprite::create("long.png");
        //enemy->setPosition(screenSize.width*0.39+origin.x, screenSize.height*0.506+origin.y);
        //enemy->setPosition(270-40+origin.x, 165+30+origin.y);
        Vec2 position = Vec2(((MapCell*)(enemy->fMap->mapCellArray->objectAtIndex(i)))->position.x, ((MapCell*)(enemy->fMap->mapCellArray->objectAtIndex(i)))->position.y);
        
        enemyplayer->setPosition(position.x, position.y);
        // enemy->setPosition(0,0);
        enemyplayer->setAnchorPoint(Vec2(0.5, 0));
        // player->setFlippedX(true);
        CommonFunc::setSpriteSize(enemyplayer, screenSize.width*0.075);
        enemy->fMap->addChild(enemyplayer,10);
        break;
    }
    
    
    background = Sprite::create("begin.jpg");
    CommonFunc::setSpriteSize(background, screenSize.width);
    background->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height/2+origin.y));
    background->setLocalZOrder(-100);
    this->addChild(background);
    
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
