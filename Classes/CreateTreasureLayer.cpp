//
//  CreateTreasureLayer.cpp
//  OctMountain
//
//  Created by zc on 16/11/24.
//
//

#include "CreateTreasureLayer.h"
#include "CommonFunc.h"
#include "Setting.h"

bool CreateTreasureLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

void CreateTreasureLayer::initCreateFabaoLayer() {
    auto background = Sprite::create("registerBg.jpg");
    CommonFunc::setShowAllSpriteSize(background, this->getBoundingBox().size.width, this->getBoundingBox().size.height);
    background->setPosition(Vec2(this->getBoundingBox().size.width/2, this->getBoundingBox().size.height/2));
    this->addChild(background, -100);
    
    Label* title = Label::createWithTTF("法宝打造", "fonts/kaiti.ttf", 24);
    title->setAlignment(TextHAlignment::CENTER);
    title->setTextColor(zhuceTitle);
    title->setDimensions(this->getBoundingBox().size.width*0.18, 20);
    title->setPosition(this->getBoundingBox().size.width/2,this->getBoundingBox().size.height-this->getBoundingBox().size.height*0.0533);
    this->addChild(title,100);
    
    this->myBag = Bag::create();
    this->myBag->tieNum = 100;
    this->myBag->goldNum = 10000000;
    this->myBag->huoCaiLiaoNum = 10;
    this->myBag->shuiCaiLiaoNum = 100;
    this->myBag->muCaiLiaoNum = 80;
    this->myBag->jinCaiLiaoNum = 876;
    this->myBag->tuCaiLiaoNum = 667;
    this->myBag->retain();
    for (int i = 0; i < 12; i++) {
        TuZhi* tzData = TuZhi::create();
        caiLiaoType cailiao;
        char jzImageName[20] = {0};
        sprintf(jzImageName, "juanzhou_%d.png",i+1);
        tzData->tuZhiSpImage = jzImageName;
        tzData->tuZhiName = "毒牙";
        tzData->tuZhiInfo = "100级 爪刺";
        tzData->needTieNum = i+10;
        tzData->needGoldNum = (i+1)*100;
        tzData->type = cailiao.huo;
        tzData->needCaiLiaoNum = (i+1)*10;
        
        char fbImageName[20] = {0};
        sprintf(fbImageName, "fabao_%d.png",i+1);
        
        tzData->faBaoSpImage = fbImageName;
        this->allData.pushBack(tzData);
    }
    this->initTabelView();
    this->initDetailUIInfo(this->allData.at(2));
}

void CreateTreasureLayer::initDetailUIInfo(TuZhi* tzOneData) {
    infoLayer = Layer::create();
    infoLayer->setContentSize(Size(400,315));
    infoLayer->setPosition(230,this->getBoundingBox().size.height/2-infoLayer->getBoundingBox().size.height/2-10);
    this->addChild(infoLayer ,100);
    
    Size infoLayerSize = infoLayer->getBoundingBox().size;
    
    Sprite* infoLayerBgSp = Sprite::create("buzhenBg2.jpg");
    CommonFunc::setShowAllSpriteSize(infoLayerBgSp, infoLayer->getBoundingBox().size.width, infoLayer->getBoundingBox().size.height);
    infoLayerBgSp->setPosition(infoLayerSize.width/2,infoLayerSize.height/2);
    infoLayer->addChild(infoLayerBgSp,-100);
    
    this->fabaoSp = Sprite::create(tzOneData->faBaoSpImage);
    CommonFunc::setShowAllSpriteSize(this->fabaoSp, 120, 120);
    this->fabaoSp->setPosition(20+this->fabaoSp->getBoundingBox().size.width/2,infoLayer->getBoundingBox().size.height-20-this->fabaoSp->getBoundingBox().size.height/2);
    infoLayer->addChild(this->fabaoSp,100);
    Sprite* fabaoGezi = Sprite::create("tuzhigezi.png");
    CommonFunc::setShowAllSpriteSize(fabaoGezi, this->fabaoSp->getBoundingBox().size.width+10, this->fabaoSp->getBoundingBox().size.height+10);
    fabaoGezi->setPosition(this->fabaoSp->getPosition());
    infoLayer->addChild(fabaoGezi,70);
    
    Label* fabaoShuXingLabel = Label::createWithTTF("打造完成后会出现随机4条可重复属性（命中，闪避，暴击，免爆，物理伤害，法术伤害，伤害减免）", "fonts/kaiti.ttf", 18);
    fabaoShuXingLabel->setAnchorPoint(Vec2(0, 0.5));
    fabaoShuXingLabel->setPosition(this->fabaoSp->getPosition().x+this->fabaoSp->getBoundingBox().size.width/2+10,this->fabaoSp->getPosition().y);
    fabaoShuXingLabel->setAlignment(TextHAlignment::LEFT);
    fabaoShuXingLabel->setTextColor(Color4B(225, 225, 225, 255));
    fabaoShuXingLabel->setDimensions(220, 90);
    fabaoShuXingLabel->setLineBreakWithoutSpace(true);
    infoLayer->addChild(fabaoShuXingLabel,100);
    
    
    this->caiLiaoSp = Sprite::create(tzOneData->type+".png");
    CommonFunc::setShowAllSpriteSize(this->caiLiaoSp, 35, 35);
    this->caiLiaoSp->setPosition(this->fabaoSp->getPosition().x-this->fabaoSp->getBoundingBox().size.width/2+20,this->fabaoSp->getPosition().y-100);
    infoLayer->addChild(this->caiLiaoSp,100);
    Sprite* caiLiaoGezi = Sprite::create("tuzhigezi.png");
    CommonFunc::setShowAllSpriteSize(caiLiaoGezi, this->caiLiaoSp->getBoundingBox().size.width+10, this->caiLiaoSp->getBoundingBox().size.height+10);
    caiLiaoGezi->setPosition(this->caiLiaoSp->getPosition());
    infoLayer->addChild(caiLiaoGezi,70);
    
    char cailiaoNum[30] = {0};
    bool isCaiLiaoZuGou = false;
    if (tzOneData->type.compare("huo") == 0) {
        if (this->myBag->huoCaiLiaoNum >= tzOneData->needCaiLiaoNum) {
            isCaiLiaoZuGou = true;
        }
        sprintf(cailiaoNum, "%d/%d",this->myBag->huoCaiLiaoNum,tzOneData->needCaiLiaoNum);
    }else if(tzOneData->type.compare("shui") == 0) {
        if (this->myBag->shuiCaiLiaoNum >= tzOneData->needCaiLiaoNum) {
            isCaiLiaoZuGou = true;
        }
        sprintf(cailiaoNum, "%d/%d",this->myBag->shuiCaiLiaoNum,tzOneData->needCaiLiaoNum);
    }else if(tzOneData->type.compare("tu") == 0) {
        if (this->myBag->tuCaiLiaoNum >= tzOneData->needCaiLiaoNum) {
            isCaiLiaoZuGou = true;
        }
        sprintf(cailiaoNum, "%d/%d",this->myBag->tuCaiLiaoNum,tzOneData->needCaiLiaoNum);
    }else if(tzOneData->type.compare("mu") == 0) {
        if (this->myBag->muCaiLiaoNum >= tzOneData->needCaiLiaoNum) {
            isCaiLiaoZuGou = true;
        }
        sprintf(cailiaoNum, "%d/%d",this->myBag->muCaiLiaoNum,tzOneData->needCaiLiaoNum);
    }else if(tzOneData->type.compare("jin") == 0) {
        if (this->myBag->jinCaiLiaoNum >= tzOneData->needCaiLiaoNum) {
            isCaiLiaoZuGou = true;
        }
        sprintf(cailiaoNum, "%d/%d",this->myBag->jinCaiLiaoNum,tzOneData->needCaiLiaoNum);
    }
    
    
    this->needCaiLiaoLabel = Label::createWithTTF(cailiaoNum, "fonts/kaiti.ttf", 18);
    if (isCaiLiaoZuGou == true) {
        this->needCaiLiaoLabel->setTextColor(lvse);
    }else {
        this->needCaiLiaoLabel->setTextColor(hongse);
    }
    this->needCaiLiaoLabel->setAlignment(TextHAlignment::LEFT);
    this->needCaiLiaoLabel->setDimensions(120, 20);
    this->needCaiLiaoLabel->setPosition(caiLiaoGezi->getPosition().x+90,caiLiaoGezi->getPosition().y);
    infoLayer->addChild(this->needCaiLiaoLabel,100);
    
    Sprite* tieSp = Sprite::create("kuangshi.png");
    CommonFunc::setShowAllSpriteSize(tieSp, 40, 40);
    tieSp->setPosition(this->fabaoSp->getPosition().x-this->fabaoSp->getBoundingBox().size.width/2+20,this->fabaoSp->getPosition().y-155);
    infoLayer->addChild(tieSp,100);
    Sprite* tieGezi = Sprite::create("tuzhigezi.png");
    CommonFunc::setShowAllSpriteSize(tieGezi, tieSp->getBoundingBox().size.width+5, tieSp->getBoundingBox().size.height+5);
    tieGezi->setPosition(tieSp->getPosition());
    infoLayer->addChild(tieGezi,70);
    
    char tieNum[30] = {0};
    sprintf(tieNum, "%d/%d",this->myBag->tieNum,tzOneData->needTieNum);
    this->needTieLabel = Label::createWithTTF(tieNum, "fonts/kaiti.ttf", 18);
    if (this->myBag->tieNum >= tzOneData->needTieNum) {
        this->needTieLabel->setTextColor(lvse);
    }else {
        this->needTieLabel->setTextColor(hongse);
    }
    this->needTieLabel->setAlignment(TextHAlignment::LEFT);
    this->needTieLabel->setDimensions(120, 20);
    this->needTieLabel->setPosition(tieGezi->getPosition().x+90,tieGezi->getPosition().y);
    infoLayer->addChild(this->needTieLabel,100);
    
    this->finishFaBaoGeZi = Sprite::create("tuzhigezi.png");
    CommonFunc::setShowAllSpriteSize(this->finishFaBaoGeZi, 100, 100);
    this->finishFaBaoGeZi->setPosition(fabaoShuXingLabel->getPosition().x+this->finishFaBaoGeZi->getBoundingBox().size.width/2,caiLiaoGezi->getPosition().y+caiLiaoGezi->getBoundingBox().size.height/2-this->finishFaBaoGeZi->getBoundingBox().size.height/2);
    infoLayer->addChild(this->finishFaBaoGeZi,70);
    
    char needgoldNum[60] = {0};
    sprintf(needgoldNum, "消耗: %d",tzOneData->needGoldNum);
    this->needGoldLabel = Label::createWithTTF(needgoldNum, "fonts/kaiti.ttf", 18);
    this->needGoldLabel->setDimensions(150, 20);
    this->needGoldLabel->setAlignment(TextHAlignment::LEFT);
    this->needGoldLabel->setTextColor(Color4B(225, 225, 225, 255));
    this->needGoldLabel->setAnchorPoint(Vec2(0, 0.5));
    this->needGoldLabel->setPosition(this->finishFaBaoGeZi->getPosition().x+this->finishFaBaoGeZi->getBoundingBox().size.width/2+10,this->finishFaBaoGeZi->getPosition().y+20);
    infoLayer->addChild(this->needGoldLabel,100);
    
    char havegoldNum[60] = {0};
    sprintf(havegoldNum, "拥有: %d",this->myBag->goldNum);
    this->haveGoldLabel = Label::createWithTTF(havegoldNum, "fonts/kaiti.ttf", 18);
    this->haveGoldLabel->setDimensions(150, 20);
    this->haveGoldLabel->setAlignment(TextHAlignment::LEFT);
    this->haveGoldLabel->setTextColor(Color4B(225, 225, 225, 255));
    this->haveGoldLabel->setAnchorPoint(Vec2(0, 0.5));
    this->haveGoldLabel->setPosition(this->finishFaBaoGeZi->getPosition().x+this->finishFaBaoGeZi->getBoundingBox().size.width/2+10,this->finishFaBaoGeZi->getPosition().y-20);
    infoLayer->addChild(this->haveGoldLabel,100);
    
    this->daZaoBtn = ui::Button::create("btnBg1.png");
    this->daZaoBtn->setTitleText("开始打造");
    this->daZaoBtn->setTitleColor(Color3B(225, 225, 225));
    this->daZaoBtn->setPressedActionEnabled(true);
    this->daZaoBtn->setPosition(Vec2(infoLayer->getBoundingBox().size.width-this->daZaoBtn->getBoundingBox().size.width, 40));
    this->daZaoBtn->addTouchEventListener(CC_CALLBACK_2(CreateTreasureLayer::daZaoClick, this));
    infoLayer->addChild(this->daZaoBtn, 100);
}

void CreateTreasureLayer::daZaoClick(cocos2d::Ref *pSender, ui::Widget::TouchEventType type) {
    
}

void CreateTreasureLayer::initTabelView() {
    this->tuZhiTableView = TableView::create(this, Size(this->getBoundingBox().size.width*0.24,this->getBoundingBox().size.height*0.746));
    this->tuZhiTableView->setDelegate(this);
    this->tuZhiTableView->setDirection(ScrollView::Direction::VERTICAL);
    this->tuZhiTableView->setPosition(this->getBoundingBox().size.width*0.055,this->getBoundingBox().size.height/2-this->tuZhiTableView->getBoundingBox().size.height/2-this->getBoundingBox().size.height*0.0266);
    this->tuZhiTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    Sprite* tvBgSp = Sprite::create("tuJianBg.png");
    CommonFunc::setShowAllSpriteSize(tvBgSp, this->getBoundingBox().size.width*0.27, this->getBoundingBox().size.height*0.853);
    tvBgSp->setAnchorPoint(Vec2(0, 0));
    tvBgSp->setPosition(this->getBoundingBox().size.width*0.03,this->getBoundingBox().size.height/2-this->getBoundingBox().size.height*0.426-this->getBoundingBox().size.height*0.0266);
    this->addChild(tvBgSp, 90);
    this->addChild(this->tuZhiTableView,100);
    this->oldNum = 0;
    
}

Size CreateTreasureLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) {
    return Size(this->getBoundingBox().size.width*0.24*0.875, this->getBoundingBox().size.height*0.746*0.25);
}

void CreateTreasureLayer::scrollViewDidScroll(cocos2d::extension::ScrollView *view) {
  
    
    
}

void CreateTreasureLayer::scrollViewDidZoom(cocos2d::extension::ScrollView *view) {
    
}

void CreateTreasureLayer::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell) {
    if (this->oldNum != cell->getIdx()) {
        ((Sprite*)cell->getChildByTag(10))->setOpacity(125);
        if (table->cellAtIndex(this->oldNum) != NULL) {
            ((Sprite*)table->cellAtIndex(this->oldNum)->getChildByTag(10))->setOpacity(255);
        }
        
        this->oldNum = cell->getIdx();
        this->changeUIInfo(this->allData.at(this->oldNum));
    }else {
        ((Sprite*)cell->getChildByTag(10))->setOpacity(125);
    }
}

void CreateTreasureLayer::changeUIInfo(TuZhi *tz) {
    this->fabaoSp->removeFromParentAndCleanup(true);
    this->fabaoSp = Sprite::create(tz->faBaoSpImage);
    CommonFunc::setShowAllSpriteSize(this->fabaoSp, 120, 120);
    this->fabaoSp->setPosition(20+this->fabaoSp->getBoundingBox().size.width/2,infoLayer->getBoundingBox().size.height-20-this->fabaoSp->getBoundingBox().size.height/2);
    infoLayer->addChild(this->fabaoSp,100);
    
    this->caiLiaoSp->removeFromParentAndCleanup(true);
    
    this->caiLiaoSp = Sprite::create(tz->type+".png");
    CommonFunc::setShowAllSpriteSize(this->caiLiaoSp, 35, 35);
    this->caiLiaoSp->setPosition(this->fabaoSp->getPosition().x-this->fabaoSp->getBoundingBox().size.width/2+20,this->fabaoSp->getPosition().y-100);
    infoLayer->addChild(this->caiLiaoSp,100);
    
    char cailiaoNum[30] = {0};
    bool isCaiLiaoZuGou = false;
    if (tz->type.compare("huo") == 0) {
        if (this->myBag->huoCaiLiaoNum >= tz->needCaiLiaoNum) {
            isCaiLiaoZuGou = true;
        }
        sprintf(cailiaoNum, "%d/%d",this->myBag->huoCaiLiaoNum,tz->needCaiLiaoNum);
    }else if(tz->type.compare("shui") == 0) {
        if (this->myBag->shuiCaiLiaoNum >= tz->needCaiLiaoNum) {
            isCaiLiaoZuGou = true;
        }
        sprintf(cailiaoNum, "%d/%d",this->myBag->shuiCaiLiaoNum,tz->needCaiLiaoNum);
    }else if(tz->type.compare("tu") == 0) {
        if (this->myBag->tuCaiLiaoNum >= tz->needCaiLiaoNum) {
            isCaiLiaoZuGou = true;
        }
        sprintf(cailiaoNum, "%d/%d",this->myBag->tuCaiLiaoNum,tz->needCaiLiaoNum);
    }else if(tz->type.compare("mu") == 0) {
        if (this->myBag->muCaiLiaoNum >= tz->needCaiLiaoNum) {
            isCaiLiaoZuGou = true;
        }
        sprintf(cailiaoNum, "%d/%d",this->myBag->muCaiLiaoNum,tz->needCaiLiaoNum);
    }else if(tz->type.compare("jin") == 0) {
        if (this->myBag->jinCaiLiaoNum >= tz->needCaiLiaoNum) {
            isCaiLiaoZuGou = true;
        }
        sprintf(cailiaoNum, "%d/%d",this->myBag->jinCaiLiaoNum,tz->needCaiLiaoNum);
    }
    
    this->needCaiLiaoLabel->setString(cailiaoNum);
    if (isCaiLiaoZuGou == true) {
        this->needCaiLiaoLabel->setTextColor(lvse);
    }else {
        this->needCaiLiaoLabel->setTextColor(hongse);
    }
    
    char tieNum[30] = {0};
    sprintf(tieNum, "%d/%d",this->myBag->tieNum,tz->needTieNum);
    if (this->myBag->tieNum >= tz->needTieNum) {
        this->needTieLabel->setTextColor(lvse);
    }else {
        this->needTieLabel->setTextColor(hongse);
    }
    this->needTieLabel->setString(tieNum);
    
    char needgoldNum[60] = {0};
    sprintf(needgoldNum, "消耗: %d",tz->needGoldNum);
    this->needGoldLabel->setString(needgoldNum);
    
    char havegoldNum[60] = {0};
    sprintf(havegoldNum, "拥有: %d",this->myBag->goldNum);
    this->haveGoldLabel->setString(havegoldNum);
}

TableViewCell* CreateTreasureLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) {
    TableViewCell *cell = table->dequeueCell();
    
    if (!cell) {
        //创建一个新的cell
        cell = new TableViewCell();
        cell->setContentSize(Size(this->getBoundingBox().size.width*0.24*0.875, this->getBoundingBox().size.height*0.746*0.25));
        
        //加入到自动释放池中
        cell->autorelease();
        
        Sprite* cellBgSp = Sprite::create("infoBg.png");
        CommonFunc::setShowAllSpriteSize(cellBgSp, cell->getBoundingBox().size.width, cell->getBoundingBox().size.height);
        cellBgSp->setAnchorPoint(Vec2(0, 0));
        cellBgSp->setPosition(0,0);
        cellBgSp->setTag(10);
        cell->addChild(cellBgSp,200);
        
        Sprite *tzSp= Sprite::create(this->allData.at(idx)->tuZhiSpImage);
        CommonFunc::setSpriteSize(tzSp, cell->getBoundingBox().size.width*0.392);
        
        tzSp->setPosition(Vec2(cell->getBoundingBox().size.width*0.214,cell->getBoundingBox().size.height/2-cell->getBoundingBox().size.height*0.057));
        tzSp->setTag(20);
        cell->addChild(tzSp,250);
        
        
        Label *nameLabel = Label::createWithTTF(this->allData.at(idx)->tuZhiName, "fonts/fangzhengjingheijianti.ttf", 14);
        nameLabel->setTextColor(ziSe);
        nameLabel->setDimensions(cell->getBoundingBox().size.width/2, cell->getBoundingBox().size.height*0.286);
        nameLabel->setAnchorPoint(Vec2(0, 0.5));
        nameLabel->setAlignment(TextHAlignment::LEFT);
        nameLabel->setPosition(cell->getBoundingBox().size.width*0.428,cell->getBoundingBox().size.height/2+cell->getBoundingBox().size.height*0.143);
        
        Label *infoLabel = Label::createWithTTF(this->allData.at(idx)->tuZhiInfo, "fonts/fangzhengjingheijianti.ttf", 12);
        infoLabel->setTextColor(dragonFontColor);
        infoLabel->setDimensions(cell->getBoundingBox().size.width/2, cell->getBoundingBox().size.height*0.571);
        infoLabel->setLineBreakWithoutSpace(true);
        infoLabel->setAnchorPoint(Vec2(0, 1));
        infoLabel->setAlignment(TextHAlignment::LEFT);
        infoLabel->setPosition(cell->getBoundingBox().size.width*0.428,cell->getBoundingBox().size.height/2-cell->getBoundingBox().size.height*0.114);
        //为标签做一个标记,以便于在cell在重用队列中被取出来时，能够获取的该label并重置label信息
        infoLabel->setTag(30);
        nameLabel->setTag(40);
        //将标签加入到cell中
        cell->addChild(nameLabel,300);
        cell->addChild(infoLabel,300);
        
    }
    else
    {
        Label *labelXiao = (Label*)cell->getChildByTag(30);
        labelXiao->setString(this->allData.at(idx)->tuZhiInfo);
        
        Label *label = (Label*)cell->getChildByTag(40);
        label->setString(this->allData.at(idx)->tuZhiName);
        
        Sprite* tzSp = (Sprite*)cell->getChildByTag(20);
        tzSp->removeFromParentAndCleanup(true);
        tzSp = Sprite::create(this->allData.at(idx)->tuZhiSpImage);
        CommonFunc::setSpriteSize(tzSp, cell->getBoundingBox().size.width*0.392);
        
        tzSp->setPosition(Vec2(cell->getBoundingBox().size.width*0.214,cell->getBoundingBox().size.height/2-cell->getBoundingBox().size.height*0.057));
        tzSp->setTag(20);
        cell->addChild(tzSp,250);
        
        Sprite* cellBgSp = (Sprite*)cell->getChildByTag(10);
        cellBgSp->removeFromParentAndCleanup(true);
        cellBgSp = Sprite::create("infoBg.png");
        CommonFunc::setShowAllSpriteSize(cellBgSp, cell->getBoundingBox().size.width, cell->getBoundingBox().size.height);
        cellBgSp->setAnchorPoint(Vec2(0, 0));
        cellBgSp->setPosition(0,0);
        cellBgSp->setTag(10);
        cell->addChild(cellBgSp,200);
        if (idx == this->oldNum) {
            cellBgSp->setOpacity(125);
        }else {
            cellBgSp->setOpacity(255);
        }
        
        
        
    }
    return cell;

}

ssize_t CreateTreasureLayer::numberOfCellsInTableView(cocos2d::extension::TableView *table) {
    return this->allData.size();
}
