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

#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "Setting/RecordFight.h"
#include "OneRecord.h"

#include "ReadRecordFight.h"
#include "AnalysisJson.h"
//#include "FightNetwork.h"
Scene* FightLayer::createScene() {
    
    Scene* scene = Scene::create();
    
//    FightLayer* layer = FightLayer::create();
//    
//    scene->addChild(layer);
//    layer->initFightLayer();
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
    this->player->fpName = "player";
    this->player->fightLayer = this;
    this->player->initMap("leftmap.png", "left", Size(300,300));
    this->player->fMap->setPosition(10+origin.x, 40+origin.y);
    this->player->initDragon("dragon_left.png");
    this->player->fDragon->dragonSprite->setPosition(150+origin.x,screenSize.height+origin.y);
    
    this->enemyPlay = FightPlayer::create();
    this->enemyPlay->fpName = "enemyPlayer";
    this->enemyPlay->fightLayer = this;
    this->enemyPlay->initMap("rightmap.png", "right", Size(300,300));
    this->enemyPlay->fMap->setPosition(screenSize.width-(enemyPlay->fMap->getBoundingBox().size.width+10+origin.x),40+origin.y);
    this->enemyPlay->initDragon("dragon_right.png");
    this->enemyPlay->fDragon->dragonSprite->setPosition(screenSize.width-150+origin.x,screenSize.height+origin.y);
    
    this->player->enemy = this->enemyPlay;
    this->enemyPlay->enemy = this->player;
    this->player->xiangong = 20;
    this->enemyPlay->xiangong = 15;
    
    this->player->retain();
    this->enemyPlay->retain();
    this->startFight = false;



    
  //  printf("%d",this->roleData->at(0)->cellIndex);
//    for (int i = 0; i < this->roleData.size(); i++) {
//        this->player->initRecordTackCard(this->roleData.at(i)->card, this->roleData.at(i)->cellIndex, "player",this->roleData.at(i)->magicGoods);
//    }
//
//    this->player->initCardStandArray();
    
//    this->player->initRecordTackCard(XuanWuCard::create(), 0, "player",DunJiaTianShu::create());
//    this->player->initRecordTackCard(XingTianCard::create(), 3, "player",DunJiaTianShu::create());
//    this->player->initRecordTackCard(ChangECard::create(), 5, "player",DunJiaTianShu::create());
//    this->player->initRecordTackCard(TaoTieCard::create(), 6, "player",DunJiaTianShu::create());
//    this->player->initRecordTackCard(FengHouCard::create(), 9, "player",DunJiaTianShu::create());
//    this->player->initRecordTackCard(FengBoCard::create(), 10, "player",DunJiaTianShu::create());
//    this->player->initRecordTackCard(HouYiCard::create(), 12, "player",DunJiaTianShu::create());
//    this->player->initRecordTackCard(SuanYuCard::create(), 15, "player",DunJiaTianShu::create());
//    
//    this->player->initCardStandArray();

//    this->enemyPlay->initRecordTackCard(XuanWuCard::create(), 0, "enemyPlayer",DunJiaTianShu::create());
//    this->enemyPlay->initRecordTackCard(XingTianCard::create(), 3, "enemyPlayer",DunJiaTianShu::create());
//    this->enemyPlay->initRecordTackCard(ChangECard::create(), 5, "enemyPlayer",DunJiaTianShu::create());
//    this->enemyPlay->initRecordTackCard(TaoTieCard::create(), 6, "enemyPlayer",DunJiaTianShu::create());
//    this->enemyPlay->initRecordTackCard(FengHouCard::create(), 9, "enemyPlayer",DunJiaTianShu::create());
//    this->enemyPlay->initRecordTackCard(FengBoCard::create(), 10, "enemyPlayer",DunJiaTianShu::create());
//    this->enemyPlay->initRecordTackCard(HouYiCard::create(), 12, "enemyPlayer",DunJiaTianShu::create());
//    this->enemyPlay->initRecordTackCard(SuanYuCard::create(), 15, "enemyPlayer",DunJiaTianShu::create());
//    this->enemyPlay->initCardStandArray();
    
    
    background = Sprite::create("uv界面测试(1).png");//bbg_arena.png
    CommonFunc::setSpriteSize(background, screenSize.width);
    background->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height/2+origin.y));
    background->setLocalZOrder(-100);
    

    

    
    this->addChild(background);
    
 //   CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("battle_bgm.mp3");
//    auto rff = RecordFight::GetInstance();
//    rff->createRecord(1, 2, 3);
//    OneRecord* one = OneRecord::create();
//    one->hitTarget = 10;
//    rff->addItemToRecord(one);

    scheduleOnce(schedule_selector(FightLayer::startGame), 1.0);

}


void FightLayer::startGame(float dur) {
    ReadRecordFight* rf = ReadRecordFight::create();
    rf->player = this->player;
    rf->playerEnemy = this->enemyPlay;
    rf->currentJson = this->fightInfo.c_str();
    rf->readPlayerInfo();
    rf->retain();
    rf->readBigNextRecord();
}

void shifang() {
    //card->retain();
    //card->fPro->retain();
    //    this->player->retain();
    //this->enemyPlay->retain();
    //playerHuangdi->retain();
    //field->retain();
    //fDragon->retain();
    //card->magicGoods->retain();
}

bool FightLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    auto touchLocation = touch->getLocationInView();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    


//    if (this->startFight == false) {
//       
//        this->startFight = true;
//        auto field = FightField::create();
//        field->player = this->player;
//        field->enemyPlayer = this->enemyPlay;
//        // field->startFight();
//        for (int i = 0; i < this->roleData.size() ; i++) {
//            auto data = SetRoleData::create();
//            data->card = this->roleData.at(i)->card;
//            data->cellIndex = this->roleData.at(i)->cellIndex;
//            data->magicGoods = this->roleData.at(i)->magicGoods;
//            data->imageName = this->roleData.at(i)->imageName;
//            field->roleData.pushBack(data);
//        }
//        field->retain();
//        auto record = RecordFight::GetInstance();
//        record->createRecord(1, 2, 3);
//        record->currentRecordIndex= 0;
//        //    if (this->player->fDragon->dragonSkillArray.size() == 0 && ) {
//        //        <#statements#>
//        //    }
//        if (this->player->xiangong > this->enemyPlay->xiangong) {
//            auto wait = ActionWait::create(1.0);
//            auto apper = FadeTo::create(0.5, 255);
//            auto disapper = FadeTo::create(0.5, 0);
//            auto run = CallFunc::create(CC_CALLBACK_0(FightField::dragonRun,field,"player"));
//            auto block = CallFunc::create(CC_CALLBACK_0(FightField::dragonBlock,field,"player"));
//            this->player->fDragon->dragonSprite->runAction(Sequence::create(run,block, NULL));
//        }else {
//            auto wait = ActionWait::create(1.0);
//            auto apper = FadeTo::create(0.5, 255);
//            auto disapper = FadeTo::create(0.5, 0);
//            auto run = CallFunc::create(CC_CALLBACK_0(FightField::dragonRun,field,"enemy"));
//            auto block = CallFunc::create(CC_CALLBACK_0(FightField::dragonBlock,field,"enemy"));
//            this->enemyPlay->fDragon->dragonSprite->runAction(Sequence::create(run,block, NULL));
//        }
//
//    }
    
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
