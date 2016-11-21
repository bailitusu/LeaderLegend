//
//  LingShoLayer.cpp
//  OctLegend
//
//  Created by zc on 16/10/11.
//
//

#include "LingShoLayer.h"
#include "Dragon.h"
#include "CommonFunc.h"
#include "Setting.h"
#include "SkillScrollLayer.h"
#include "DragonSkill.h"
#include "Bag.h"
#include "LingShouInfoLayer.h"

#include "AllArmyGuWu.h"
#include "HuiMieBoDong.h"
#include "JiuXiaoLongYin.h"
#include "ZaiShengLongHou.h"
#include "ZhanYiGaoAng.h"

bool LingShoLayer::init() {
    return true;
}

Scene* LingShoLayer::createScene() {
    Scene* scene = Scene::create();
    return scene;
}

void LingShoLayer::initLingShoLayer() {
    auto background = Sprite::create("buzhenBg2.jpg");//,bbg_fine_ship
   // CommonFunc::setSpriteSize(background, screenSize.width);
    CommonFunc::setShowAllSpriteSize(background, screenSize.width, screenSize.height);
    background->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height/2+origin.y));
    background->setLocalZOrder(-100);
    this->addChild(background);
    
    lingShouImage = Sprite::create("shouhu.png");
    CommonFunc::setSpriteSize(lingShouImage, screenSize.width*0.31);
    lingShouImage->setPosition(30+this->lingShouImage->getBoundingBox().size.width/2,screenSize.height-this->lingShouImage->getBoundingBox().size.height/2-45);
    this->addChild(lingShouImage,100);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto liston = EventListenerTouchOneByOne::create();
    liston->onTouchBegan = CC_CALLBACK_2(LingShoLayer::onTouchBegan, this);
    liston->onTouchMoved = CC_CALLBACK_2(LingShoLayer::onTouchMoved, this);
    liston->onTouchEnded = CC_CALLBACK_2(LingShoLayer::onTouchEnded, this);
  //  liston->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(liston, this);
    
   // this->initTaoZi();
   // this->initPeiYangBtn();
    this->initShuXingLabel();
    this->initTakeGezi();
    this->initAllGezi();
    
    this->backBtnUI();
}

void LingShoLayer::backBtnUI() {
    
    ui::Button *btn = ui::Button::create("fanhuijian.png");
    
    btn->setPressedActionEnabled(true);
    btn->setPosition(Vec2(screenSize.width*0.96, screenSize.height*0.92));
    btn->addTouchEventListener(CC_CALLBACK_2(LingShoLayer::backBtn, this));
    btn->setScale(screenSize.width*0.05/btn->getBoundingBox().size.width);
    
    // btn = CommonFunc::initButton(btn,CC_CALLBACK_2(FuBenLayer::backBtn, this) , screenSize.width*0.05, Vec2(screenSize.width*0.96, screenSize.height*0.92));
    this->addChild(btn,200);
}

void LingShoLayer::backBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        ((Scene*)this->getParent())->onExit();
        Director::getInstance()->popScene();
    }
    
    
}

//void LingShoLayer::initTaoZi() {
////    Sprite* taoZiSp = Sprite::create("taozi.jpg");
////    CommonFunc::setSpriteSize(taoZiSp, 30);
////    taoZiSp->setPosition(Vec2(this->lingShouImage->getPosition().x+screenSize.width*0.15-15, this->lingShouImage->getPosition().y+screenSize.height*0.075+5));
////    this->addChild(taoZiSp, 100);
//    
//    ui::Button *taoZiBtn = ui::Button::create("taozi.jpg");
//    
//    taoZiBtn->setScale(30/taoZiBtn->getBoundingBox().size.width);
//    taoZiBtn->setPressedActionEnabled(true);
//    //    levelBtn->setContentSize(Size(60, 40));
//    taoZiBtn->setPosition(Vec2(this->lingShouImage->getPosition().x+screenSize.width*0.15-15, this->lingShouImage->getPosition().y+screenSize.height*0.075+5));
//    taoZiBtn->addTouchEventListener(CC_CALLBACK_2(LingShoLayer::taoZiBtn, this));
//    this->addChild(taoZiBtn,100);
//    
//    char temp[20] = {0};
//    sprintf(temp, "x%d", this->myBag->taoZiNum);
//    this->taoZiNumLabel = this->createLabel(temp, Vec2(taoZiBtn->getPosition().x+40,taoZiBtn->getPosition().y));
//    this->taoZiNumLabel->setAlignment(TextHAlignment::LEFT);
//    
//}


void LingShoLayer::initPeiYangBtn() {
    ui::Button *peiYangBtn = ui::Button::create("classbtn.png");
    peiYangBtn->setTitleText("培养");
    peiYangBtn->setTitleColor(Color3B(255, 255, 255));
    peiYangBtn->setTitleAlignment(TextHAlignment::CENTER);
    peiYangBtn->setTitleFontSize(15);
    peiYangBtn->setPressedActionEnabled(true);
//    levelBtn->setContentSize(Size(60, 40));
    peiYangBtn->setScale(80/peiYangBtn->getBoundingBox().size.width);
    peiYangBtn->setAnchorPoint(Vec2(0.5, 0.5));
    peiYangBtn->setPosition(Vec2(this->lingShouImage->getPosition().x+this->lingShouImage->getBoundingBox().size.width/2+40,this->lingShouImage->getPosition().y+this->lingShouImage->getBoundingBox().size.height/2-170));
    peiYangBtn->addTouchEventListener(CC_CALLBACK_2(LingShoLayer::peiYangBtn, this));
    this->addChild(peiYangBtn,100);
    
//    ui::Button *skillBtn = ui::Button::create("classbtn.png");
//    skillBtn->setTitleText("技能");
//    skillBtn->setTitleColor(Color3B(255, 255, 255));
//    skillBtn->setTitleAlignment(TextHAlignment::CENTER);
//    skillBtn->setTitleFontSize(15);
//    skillBtn->setPressedActionEnabled(true);
////    skillBtn->setContentSize(Size(60, 40));
//    skillBtn->setPosition(Vec2(this->lingShouImage->getPosition().x+screenSize.width*0.15-10,this->lingShouImage->getPosition().y-screenSize.width*0.075+12));
//    skillBtn->addTouchEventListener(CC_CALLBACK_2(LingShoLayer::levelUpBtn, this));
//    this->addChild(skillBtn,100);
}

void LingShoLayer::peiYangBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    
}

//void LingShoLayer::skillBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
//    
//}

void LingShoLayer::initShuXingLabel() {
    this->createLabel("兵力:", Vec2(this->lingShouImage->getPosition().x+this->lingShouImage->getBoundingBox().size.width/2+30,this->lingShouImage->getPosition().y+this->lingShouImage->getBoundingBox().size.height/2-20));
    this->createLabel("攻击:", Vec2(this->lingShouImage->getPosition().x+this->lingShouImage->getBoundingBox().size.width/2+30,this->lingShouImage->getPosition().y+this->lingShouImage->getBoundingBox().size.height/2-45));
    this->createLabel("防御:", Vec2(this->lingShouImage->getPosition().x+this->lingShouImage->getBoundingBox().size.width/2+30,this->lingShouImage->getPosition().y+this->lingShouImage->getBoundingBox().size.height/2-70));
    this->createLabel("法力:", Vec2(this->lingShouImage->getPosition().x+this->lingShouImage->getBoundingBox().size.width/2+30,this->lingShouImage->getPosition().y+this->lingShouImage->getBoundingBox().size.height/2-95));
    this->createLabel("敏捷:", Vec2(this->lingShouImage->getPosition().x+this->lingShouImage->getBoundingBox().size.width/2+30,this->lingShouImage->getPosition().y+this->lingShouImage->getBoundingBox().size.height/2-120));
  //  this->createLabel(":", Vec2(35,this->lingShouImage->getPosition().y-screenSize.width*0.075-120));
    
    char tempVale[50] = {0};

    sprintf(tempVale, "%d",this->myDragon->bingLi);
    this->bingLiLabel = this->createLabel(tempVale, Vec2(this->lingShouImage->getPosition().x+this->lingShouImage->getBoundingBox().size.width/2+30+45,this->lingShouImage->getPosition().y+this->lingShouImage->getBoundingBox().size.height/2-20));
    this->bingLiLabel->setAlignment(TextHAlignment::LEFT);
    
    sprintf(tempVale, "%d",this->myDragon->gongJi);
    this->gongJiLabel = this->createLabel(tempVale, Vec2(this->lingShouImage->getPosition().x+this->lingShouImage->getBoundingBox().size.width/2+30+45,this->lingShouImage->getPosition().y+this->lingShouImage->getBoundingBox().size.height/2-45));
    this->gongJiLabel->setAlignment(TextHAlignment::LEFT);
    
    sprintf(tempVale, "%d",this->myDragon->fangYu);
    this->fangYuLabel = this->createLabel(tempVale, Vec2(this->lingShouImage->getPosition().x+this->lingShouImage->getBoundingBox().size.width/2+30+45,this->lingShouImage->getPosition().y+this->lingShouImage->getBoundingBox().size.height/2-70));
    this->fangYuLabel->setAlignment(TextHAlignment::LEFT);
    
    sprintf(tempVale, "%d",this->myDragon->faLI);
    this->faLiLabel = this->createLabel(tempVale, Vec2(this->lingShouImage->getPosition().x+this->lingShouImage->getBoundingBox().size.width/2+30+45,this->lingShouImage->getPosition().y+this->lingShouImage->getBoundingBox().size.height/2-95));
    this->faLiLabel->setAlignment(TextHAlignment::LEFT);
    
    sprintf(tempVale, "%d",this->myDragon->minJie);
    this->minJieLabel = this->createLabel(tempVale, Vec2(this->lingShouImage->getPosition().x+this->lingShouImage->getBoundingBox().size.width/2+30+45,this->lingShouImage->getPosition().y+this->lingShouImage->getBoundingBox().size.height/2-120));
    this->minJieLabel->setAlignment(TextHAlignment::LEFT);
    
//    sprintf(tempVale, "%d",this->myDragon->faLI);
//    this->faLiLabel = this->createLabel(tempVale, Vec2(this->lingShouImage->getPosition().x+this->lingShouImage->getBoundingBox().size.width/2+30+35,this->lingShouImage->getPosition().y-screenSize.width*0.075-120));
//    this->faLiLabel->setAlignment(TextHAlignment::LEFT);
}

Label* LingShoLayer::createLabel(std::string text,Vec2 positon) {
    auto label = Label::createWithTTF(text, "fonts/fangzhengjingheijianti.ttf", 19);
    label->setContentSize(Size(60, 20));
    label->setTextColor(dragonFontColor);
    label->setPosition(positon);
    this->addChild(label,100);
    return label;
}

void LingShoLayer::initTakeGezi() {
    for (int i = 0; i < 5; i++) {
        SkillGezi* gezi = SkillGezi::create();
        gezi->geZiSp = Sprite::create("gezi.jpg");
        CommonFunc::setSpriteSize(gezi->geZiSp, screenSize.width*0.082);
        this->addChild(gezi->geZiSp,100);
        gezi->index = i;
        gezi->geZiSp->setPosition(75+i*screenSize.width*0.082,80);// 48 57
       // printf("%f",gezi->geZiSp->getPosition().y);
        gezi->geziPositon = gezi->geZiSp->getPosition();
        this->takeSkillArray.pushBack(gezi);
    }
}

void LingShoLayer::initAllGezi() {
    scrollLayer = SkillScrollLayer::create();
    scrollLayer->setContentSize(Size(260,320));
    scrollLayer->initSkillScrollLayer();

    scrollLayer->setPosition(screenSize.width*0.73-scrollLayer->getBoundingBox().size.width/2,screenSize.height/2-scrollLayer->getBoundingBox().size.height/2);
    this->addChild(scrollLayer,100);
    for (int i = 0; i < 14; i++) {
        SkillGezi* allGezi = SkillGezi::create();

        allGezi->geZiSp = Sprite::create("allSkillGeziBg.png");
        CommonFunc::setSpriteSize(allGezi->geZiSp, scrollLayer->getBoundingBox().size.width*0.192);
        scrollLayer->continerLayer->addChild(allGezi->geZiSp,150);
        allGezi->geZiSp->setPosition(allGezi->geZiSp->getBoundingBox().size.width/2+allGezi->geZiSp->getBoundingBox().size.width*(i%4)+10*(i%4),scrollLayer->getBoundingBox().size.height-(scrollLayer->getBoundingBox().size.height/6-20+allGezi->geZiSp->getBoundingBox().size.height*(i/4)+10*(i/4))+scrollLayer->getBoundingBox().size.height);
      //  allGezi->geZiSp->setPosition(0,0);
        allGezi->index = i;
        allGezi->geziPositon = allGezi->geZiSp->getPosition();
        
        char skillImageName[20] = {0};
        sprintf(skillImageName, "s_%d.jpg",i);
        switch (i) {
            case 0:
                allGezi->obj = AllArmyGuWu::create();
                break;
            case 1:
                allGezi->obj = HuiMieBoDong::create();
                break;
            case 2:
                allGezi->obj = JiuXiaoLongYin::create();
                break;
            case 3:
                allGezi->obj = ZaiShengLongHou::create();
                break;
            case 4:
                allGezi->obj = ZhanYiGaoAng::create();
                break;
            default:
                allGezi->obj = DragonSkill::create();
                allGezi->obj->dargonInfoName = "超级技能";
                break;
        }
//        allGezi->obj = DragonSkill::create();
        if (i >= 20) {
            allGezi->obj->dragonSkillSp = Sprite::create("s_noHave.jpg");
            allGezi->obj->noHave = true;
        }else {
            allGezi->obj->dragonSkillSp = Sprite::create(skillImageName);
            allGezi->obj->noHave = false;
        }
        
        allGezi->obj->imageName = skillImageName;
        CommonFunc::setSpriteSize(allGezi->obj->dragonSkillSp, allGezi->geZiSp->getBoundingBox().size.width-8);
        allGezi->obj->dragonSkillSp->setPosition(allGezi->geZiSp->getPosition());
        scrollLayer->continerLayer->addChild(allGezi->obj->dragonSkillSp,200);
        allGezi->obj->retain();
        this->allSkillArray.pushBack(allGezi);
    }
}


bool LingShoLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    auto touchLocation = touch->getLocationInView();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    
    this->isShowInfo = false;
    
    
    for (int i = 0 ; i < this->takeSkillArray.size(); i++) {
        Rect takeSkillRect = Rect(this->takeSkillArray.at(i)->geZiSp->getPosition().x-this->takeSkillArray.at(i)->geZiSp->getBoundingBox().size.width/2,this->takeSkillArray.at(i)->geZiSp->getPosition().y-this->takeSkillArray.at(i)->geZiSp->getBoundingBox().size.height/2,this->takeSkillArray.at(i)->geZiSp->getBoundingBox().size.width,this->takeSkillArray.at(i)->geZiSp->getBoundingBox().size.height);
        if (takeSkillRect.containsPoint(touchLocation)) {
            if (this->takeSkillArray.at(i)->obj != NULL) {
                this->changeAllSkill(this->takeSkillArray.at(i)->obj);
                this->takeSkillArray.at(i)->obj->dragonSkillSp->removeFromParent();
                this->takeSkillArray.at(i)->obj->autorelease();
                this->takeSkillArray.at(i)->obj = NULL;
                break;
            }
        }
    }
    
    for (int i = 0; i < this->allSkillArray.size(); i++) {
        auto oneSkillPoint = this->allSkillArray.at(i)->obj->dragonSkillSp->getPosition()+this->scrollLayer->continerLayer->getPosition()+this->scrollLayer->getPosition();
        Rect rect = Rect(oneSkillPoint.x-24, oneSkillPoint.y-24, 48, 48);
        if (rect.containsPoint(touchLocation)) {
            if (this->allSkillArray.at(i)->obj->noHave == false) {
                this->currentInfoDs = this->allSkillArray.at(i)->obj;
                schedule(schedule_selector(LingShoLayer::showInfo), 0.5);
                return true;
            }
        }
    }
    this->currentInfoDs = NULL;
    

    return true;
}

void LingShoLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
}

void LingShoLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    if (this->scrollLayer->isMoved == false) {
        if (this->currentInfoDs != NULL) {
            unschedule(schedule_selector(LingShoLayer::showInfo));
            if (this->isShowInfo == true) {
                this->disapperInfo();
                return;
            }
           
        }
        
        
        
        bool isMaxTake = true;
        for (int j = 0; j < this->takeSkillArray.size(); j++) {
            if (this->takeSkillArray.at(j)->obj == NULL ) {
                isMaxTake = false;
                break;
            }
        }
        auto touchLocation = touch->getLocationInView();
        touchLocation = Director::getInstance()->convertToGL(touchLocation);
        for (int i = 0; i < this->allSkillArray.size(); i++) {
            Rect allSkillRect = Rect(this->scrollLayer->getPosition(),this->scrollLayer->getBoundingBox().size);
            
            if (allSkillRect.containsPoint(touchLocation)) {
                auto oneSkillPoint = this->allSkillArray.at(i)->obj->dragonSkillSp->getPosition()+this->scrollLayer->continerLayer->getPosition()+this->scrollLayer->getPosition();
                Rect rect = Rect(oneSkillPoint.x-24, oneSkillPoint.y-24, 48, 48);
               // printf("jinlaile-------\n");
                if (rect.containsPoint(touchLocation)) {
                    if (this->allSkillArray.at(i)->obj->noHave == false) {
                        
                        if (this->allSkillArray.at(i)->obj->dragonSkillSp->getOpacity() == 125) {
                            this->allSkillArray.at(i)->obj->dragonSkillSp->setOpacity(255);
                            this->changeTakeSkill(this->allSkillArray.at(i)->obj,true);
                        }else {
                            if (isMaxTake == false) {
                                this->allSkillArray.at(i)->obj->dragonSkillSp->setOpacity(125);
                                this->changeTakeSkill(this->allSkillArray.at(i)->obj,false);
                            }
                        }

                    }
                    break;
                }
                
            }
        }
    }else {
        this->scrollLayer->isMoved = false;
        unschedule(schedule_selector(LingShoLayer::showInfo));
        if (this->isShowInfo == true) {
            this->disapperInfo();
            return;
        }
    }

}


void LingShoLayer::showInfo(float dur) {
    unschedule(schedule_selector(LingShoLayer::showInfo));
    this->isShowInfo = true;
    if (this->lsInfoLayer == NULL) {
        this->lsInfoLayer = LingShouInfoLayer::create();
        this->lsInfoLayer->setContentSize(Size(300, 90));
        this->lsInfoLayer->setAnchorPoint(Vec2(0, 0));
        this->lsInfoLayer->dSkill = this->currentInfoDs;
        this->lsInfoLayer->skillImageName = this->currentInfoDs->imageName;
        this->lsInfoLayer->initLingShouInfoLayer();

        auto position = this->currentInfoDs->dragonSkillSp->getPosition()+this->scrollLayer->continerLayer->getPosition()+this->scrollLayer->getPosition();
        this->lsInfoLayer->setPosition(Vec2(position.x-200, position.y));
        this->addChild(this->lsInfoLayer,200);
        
        
    }else {
        printf("没有消失－－－－－－－－－－－－－－");
    }

    
}

void LingShoLayer::disapperInfo() {
    printf("--------进disapper－－－－\n");
    this->lsInfoLayer->removeFromParentAndCleanup(true);
    this->lsInfoLayer = NULL;
}

void LingShoLayer::changeTakeSkill(DragonSkill* ds, bool isRemove) {
    if (isRemove == true) {
        for (int i = 0; i < this->takeSkillArray.size(); i++) {
            if (this->takeSkillArray.at(i)->obj != NULL) {
                if (this->takeSkillArray.at(i)->obj->imageName.compare(ds->imageName) == 0) {
                    this->takeSkillArray.at(i)->obj->dragonSkillSp->removeFromParent();
                    this->takeSkillArray.at(i)->obj->autorelease();
                    this->takeSkillArray.at(i)->obj = NULL;
                    break;
                }
            }

        }
    }else {
        for (int i = 0; i < this->takeSkillArray.size(); i++) {
            if (this->takeSkillArray.at(i)->obj == NULL) {
                this->takeSkillArray.at(i)->obj = DragonSkill::create();
                this->takeSkillArray.at(i)->obj->dragonSkillSp = Sprite::create(ds->imageName);
                this->takeSkillArray.at(i)->obj->imageName = ds->imageName;
                CommonFunc::setSpriteSize(this->takeSkillArray.at(i)->obj->dragonSkillSp, this->takeSkillArray.at(i)->geZiSp->getBoundingBox().size.width-10);
                this->takeSkillArray.at(i)->obj->dragonSkillSp->setPosition(this->takeSkillArray.at(i)->geZiSp->getPosition());
                this->takeSkillArray.at(i)->obj->retain();
                this->addChild(this->takeSkillArray.at(i)->obj->dragonSkillSp,150);
                break;
            }
        }
        
    }
}

void LingShoLayer::changeAllSkill(DragonSkill *ds) {
    for (int i = 0; i < this->allSkillArray.size(); i++) {
        if (this->allSkillArray.at(i)->obj->imageName.compare(ds->imageName) == 0) {
            this->allSkillArray.at(i)->obj->dragonSkillSp->setOpacity(255);
            break;
        }
    }
}



bool SkillGezi::init() {
    return true;
}
