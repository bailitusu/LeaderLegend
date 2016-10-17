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
#include "Bag/Bag.h"
bool LingShoLayer::init() {
    return true;
}

Scene* LingShoLayer::createScene() {
    Scene* scene = Scene::create();
    return scene;
}

void LingShoLayer::initLingShoLayer() {
    auto background = Sprite::create("bbg_fine_ship.jpg");
    CommonFunc::setSpriteSize(background, screenSize.width);
    background->setPosition(Vec2(screenSize.width/2+origin.x, screenSize.height/2+origin.y));
    background->setLocalZOrder(-100);
    this->addChild(background);
    
    lingShouImage = Sprite::create("DragonBaby.jpg");
    CommonFunc::setSpriteSize(lingShouImage, screenSize.width*0.15);
    lingShouImage->setPosition(70,screenSize.height-70);
    this->addChild(lingShouImage,100);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto liston = EventListenerTouchOneByOne::create();
    liston->onTouchBegan = CC_CALLBACK_2(LingShoLayer::onTouchBegan, this);
    liston->onTouchMoved = CC_CALLBACK_2(LingShoLayer::onTouchMoved, this);
    liston->onTouchEnded = CC_CALLBACK_2(LingShoLayer::onTouchEnded, this);
  //  liston->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(liston, this);
    
    this->initTaoZi();
    this->initLevelAndSkillBtn();
    this->initShuXingLabel();
    this->initTakeGezi();
    this->initAllGezi();
}

void LingShoLayer::initTaoZi() {
//    Sprite* taoZiSp = Sprite::create("taozi.jpg");
//    CommonFunc::setSpriteSize(taoZiSp, 30);
//    taoZiSp->setPosition(Vec2(this->lingShouImage->getPosition().x+screenSize.width*0.15-15, this->lingShouImage->getPosition().y+screenSize.height*0.075+5));
//    this->addChild(taoZiSp, 100);
    
    ui::Button *taoZiBtn = ui::Button::create("taozi.jpg");
    
    taoZiBtn->setScale(30/taoZiBtn->getBoundingBox().size.width);
    taoZiBtn->setPressedActionEnabled(true);
    //    levelBtn->setContentSize(Size(60, 40));
    taoZiBtn->setPosition(Vec2(this->lingShouImage->getPosition().x+screenSize.width*0.15-15, this->lingShouImage->getPosition().y+screenSize.height*0.075+5));
    taoZiBtn->addTouchEventListener(CC_CALLBACK_2(LingShoLayer::taoZiBtn, this));
    this->addChild(taoZiBtn,100);
    
    char temp[20] = {0};
    sprintf(temp, "x%d", this->myBag->taoZiNum);
    this->taoZiNumLabel = this->createLabel(temp, Vec2(taoZiBtn->getPosition().x+40,taoZiBtn->getPosition().y));
    this->taoZiNumLabel->setAlignment(TextHAlignment::LEFT);
    
}

void LingShoLayer::taoZiBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        
    
        this->myBag->taoZiNum--;
        char temp[20] = {0};
        sprintf(temp, "x%d", this->myBag->taoZiNum);
        this->taoZiNumLabel->setString(temp);
        
        struct timeval now;
        gettimeofday(&now, NULL);
        unsigned rand_seed = (unsigned)(now.tv_sec*1000 + now.tv_usec/1000);
        srand(rand_seed);
        
        int randNum = rand()%6 + 1;
        char tempVale[50] = {0};

        switch (randNum) {
            case 1:
                this->myDragon->bingLi++;
                sprintf(tempVale, "%d",this->myDragon->bingLi);
                this->bingLiLabel->setString(tempVale);
                break;
            case 2:
                this->myDragon->mianBao++;
                sprintf(tempVale, "%d",this->myDragon->mianBao);
                this->mianBaoLabel->setString(tempVale);
                break;
            case 3:
                this->myDragon->baoJi++;
                sprintf(tempVale, "%d",this->myDragon->baoJi);
                this->baoJiLabel->setString(tempVale);
                break;
            case 4:
                this->myDragon->fangYu++;
                sprintf(tempVale, "%d",this->myDragon->fangYu);
                this->fangYuLabel->setString(tempVale);
                break;
            case 5:
                this->myDragon->gongJi++;
                sprintf(tempVale, "%d",this->myDragon->gongJi);
                this->gongJiLabel->setString(tempVale);
                break;
            case 6:
                this->myDragon->faLI++;
                sprintf(tempVale, "%d",this->myDragon->faLI);
                this->faLiLabel->setString(tempVale);
                break;
            default:
                break;
        }
    }
}

void LingShoLayer::initLevelAndSkillBtn() {
    ui::Button *levelBtn = ui::Button::create("classbtn.png");
    levelBtn->setTitleText("升级");
    levelBtn->setTitleColor(Color3B(255, 255, 255));
    levelBtn->setTitleAlignment(TextHAlignment::CENTER);
    levelBtn->setTitleFontSize(15);
    levelBtn->setPressedActionEnabled(true);
//    levelBtn->setContentSize(Size(60, 40));
    levelBtn->setPosition(Vec2(this->lingShouImage->getPosition().x+screenSize.width*0.15-10,this->lingShouImage->getPosition().y-5));
    levelBtn->addTouchEventListener(CC_CALLBACK_2(LingShoLayer::levelUpBtn, this));
    this->addChild(levelBtn,100);
    
    ui::Button *skillBtn = ui::Button::create("classbtn.png");
    skillBtn->setTitleText("技能");
    skillBtn->setTitleColor(Color3B(255, 255, 255));
    skillBtn->setTitleAlignment(TextHAlignment::CENTER);
    skillBtn->setTitleFontSize(15);
    skillBtn->setPressedActionEnabled(true);
//    skillBtn->setContentSize(Size(60, 40));
    skillBtn->setPosition(Vec2(this->lingShouImage->getPosition().x+screenSize.width*0.15-10,this->lingShouImage->getPosition().y-screenSize.width*0.075+12));
    skillBtn->addTouchEventListener(CC_CALLBACK_2(LingShoLayer::levelUpBtn, this));
    this->addChild(skillBtn,100);
}

void LingShoLayer::levelUpBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    
}

void LingShoLayer::skillBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type) {
    
}

void LingShoLayer::initShuXingLabel() {
    this->createLabel("兵力:", Vec2(35,this->lingShouImage->getPosition().y-screenSize.width*0.075-20));
    this->createLabel("免爆:", Vec2(35,this->lingShouImage->getPosition().y-screenSize.width*0.075-40));
    this->createLabel("暴击:", Vec2(35,this->lingShouImage->getPosition().y-screenSize.width*0.075-60));
    this->createLabel("防御:", Vec2(35,this->lingShouImage->getPosition().y-screenSize.width*0.075-80));
    this->createLabel("攻击:", Vec2(35,this->lingShouImage->getPosition().y-screenSize.width*0.075-100));
    this->createLabel("法力:", Vec2(35,this->lingShouImage->getPosition().y-screenSize.width*0.075-120));
    
    char tempVale[50] = {0};

    sprintf(tempVale, "%d",this->myDragon->bingLi);
    this->bingLiLabel = this->createLabel(tempVale, Vec2(70,this->lingShouImage->getPosition().y-screenSize.width*0.075-20));
    this->bingLiLabel->setAlignment(TextHAlignment::LEFT);
    
    sprintf(tempVale, "%d",this->myDragon->mianBao);
    this->mianBaoLabel = this->createLabel(tempVale, Vec2(70,this->lingShouImage->getPosition().y-screenSize.width*0.075-40));
    this->mianBaoLabel->setAlignment(TextHAlignment::LEFT);
    
    sprintf(tempVale, "%d",this->myDragon->baoJi);
    this->baoJiLabel = this->createLabel(tempVale, Vec2(70,this->lingShouImage->getPosition().y-screenSize.width*0.075-60));
    this->baoJiLabel->setAlignment(TextHAlignment::LEFT);
    
    sprintf(tempVale, "%d",this->myDragon->fangYu);
    this->fangYuLabel = this->createLabel(tempVale, Vec2(70,this->lingShouImage->getPosition().y-screenSize.width*0.075-80));
    this->fangYuLabel->setAlignment(TextHAlignment::LEFT);
    
    sprintf(tempVale, "%d",this->myDragon->gongJi);
    this->gongJiLabel = this->createLabel(tempVale, Vec2(70,this->lingShouImage->getPosition().y-screenSize.width*0.075-100));
    this->gongJiLabel->setAlignment(TextHAlignment::LEFT);
    
    sprintf(tempVale, "%d",this->myDragon->faLI);
    this->faLiLabel = this->createLabel(tempVale, Vec2(70,this->lingShouImage->getPosition().y-screenSize.width*0.075-120));
    this->faLiLabel->setAlignment(TextHAlignment::LEFT);
}

Label* LingShoLayer::createLabel(std::string text,Vec2 positon) {
    auto label = Label::createWithTTF(text, "fonts/楷体.ttf", 16);
    label->setContentSize(Size(40, 20));
    label->setTextColor(Color4B(0, 0, 255, 255));
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
        gezi->geZiSp->setPosition(48+i*screenSize.width*0.082,this->lingShouImage->getPosition().y-screenSize.width*0.075-190);
        gezi->geziPositon = gezi->geZiSp->getPosition();
        this->takeSkillArray.pushBack(gezi);
    }
}

void LingShoLayer::initAllGezi() {
    scrollLayer = SkillScrollLayer::create();
    scrollLayer->setContentSize(Size(260,320));
    scrollLayer->initSkillScrollLayer();

    scrollLayer->setPosition(screenSize.width*0.775-scrollLayer->getBoundingBox().size.width/2,screenSize.height/2-scrollLayer->getBoundingBox().size.height/2+8);
    this->addChild(scrollLayer,100);
    for (int i = 0; i < 20; i++) {
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
        allGezi->obj = DragonSkill::create();
        allGezi->obj->dragonSkillSp = Sprite::create(skillImageName);
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
    for (int i = 0 ; i < this->takeSkillArray.size(); i++) {
        Rect takeSkillRect = Rect(this->takeSkillArray.at(i)->geZiSp->getPosition().x-this->takeSkillArray.at(i)->geZiSp->getBoundingBox().size.width/2,this->takeSkillArray.at(i)->geZiSp->getPosition().y-this->takeSkillArray.at(i)->geZiSp->getBoundingBox().size.height/2,this->takeSkillArray.at(i)->geZiSp->getBoundingBox().size.width,this->takeSkillArray.at(i)->geZiSp->getBoundingBox().size.height);
        if (takeSkillRect.containsPoint(touchLocation)) {
            if (this->takeSkillArray.at(i)->obj != NULL) {
                this->changeAllSkill(this->takeSkillArray.at(i)->obj);
                this->takeSkillArray.at(i)->obj->dragonSkillSp->removeFromParent();
                this->takeSkillArray.at(i)->obj->autorelease();
                this->takeSkillArray.at(i)->obj = NULL;
            }
        }
    }
    return true;
}

void LingShoLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
}

void LingShoLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    if (this->scrollLayer->isMoved == false) {
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
                    if (this->allSkillArray.at(i)->obj->dragonSkillSp->getOpacity() == 125) {
                        this->allSkillArray.at(i)->obj->dragonSkillSp->setOpacity(255);
                        this->changeTakeSkill(this->allSkillArray.at(i)->obj,true);
                    }else {
                        if (isMaxTake == false) {
                            this->allSkillArray.at(i)->obj->dragonSkillSp->setOpacity(125);
                            this->changeTakeSkill(this->allSkillArray.at(i)->obj,false);
                        }
                    }

                    
                    break;
                }
                
            }
        }
    }else {
        this->scrollLayer->isMoved = false;
    }

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
