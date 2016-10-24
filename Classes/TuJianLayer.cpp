//
//  TuJianLayer.cpp
//  OctLegend
//
//  Created by zc on 16/10/17.
//
//

#include "TuJianLayer.h"
#include "CommonFunc.h"
#include "Card.h"
#include "Setting.h"

#include "HouYiCard.h"
#include "FengBoCard.h"
#include "FengHouCard.h"
#include "ChangECard.h"
#include "TaoTieCard.h"
#include "XingTianCard.h"
#include "SuanYuCard.h"
#include "XuanWuCard.h"
bool TuJianData::init() {
    return true;
}


Scene* TuJianLayer::createScene() {
    Scene* scene = Scene::create();
    return scene;
}

bool TuJianLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

void TuJianLayer::initTuJianLayer() {
    auto background = Sprite::create("tuJianLayerBg.jpg");
    CommonFunc::setSpriteSize(background, screenSize.width);
    background->setPosition(Vec2(screenSize.width/2, screenSize.height/2));
    this->addChild(background,-100);

    this->initOneCardData("houyi", "xiaohei_big.jpg");
    this->initOneCardData("change", "bingnv_big.jpg");
    this->initOneCardData("taotie", "panda_big.jpg");
    this->initOneCardData("xingtian", "jiansheng_big.jpg");
    this->initOneCardData("xuanwu", "niutou_big.jpg");
    this->initOneCardData("fengbo", "zhousi_big.jpg");
    this->initOneCardData("fenghou", "gugong_big.jpg");
    this->initOneCardData("suanyu", "fengxing_big.jpg");
    

    
    this->initDetailUI(this->allDataArray.at(0));
    this->initShuXingLabel();
    this->changeLabelText();
    this->initTabelView();
}

void TuJianLayer::initTabelView() {
    this->allInfoTabelView = TableView::create(this, Size(160,280));
    this->allInfoTabelView->setDelegate(this);
    this->allInfoTabelView->setDirection(ScrollView::Direction::VERTICAL);
    this->allInfoTabelView->setPosition(screenSize.width-170,screenSize.height-325);
    this->allInfoTabelView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    Sprite* tvBgSp = Sprite::create("tuJianBg.png");
    CommonFunc::setShowAllSpriteSize(tvBgSp, 180, 340);
    tvBgSp->setAnchorPoint(Vec2(0, 0));
    tvBgSp->setPosition(screenSize.width-190,screenSize.height-350);
    this->addChild(tvBgSp,90);
    this->addChild(this->allInfoTabelView,100);
    this->oldNum = 0;
}

Size TuJianLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) {
    return Size(140,80);
}

void TuJianLayer::scrollViewDidScroll(cocos2d::extension::ScrollView *view) {

}

void TuJianLayer::scrollViewDidZoom(cocos2d::extension::ScrollView *view) {

}

void TuJianLayer::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell) {
    
    if (this->oldNum != cell->getIdx()) {
        ((Sprite*)cell->getChildByTag(10))->setOpacity(125);
        if (table->cellAtIndex(this->oldNum) != NULL) {
            ((Sprite*)table->cellAtIndex(this->oldNum)->getChildByTag(10))->setOpacity(255);
        }
        
        this->oldNum = cell->getIdx();
        this->changeDetailUIInfo(this->allDataArray.at(this->oldNum));
    }else {
        ((Sprite*)cell->getChildByTag(10))->setOpacity(125);
    }
    
    
    
}

TableViewCell* TuJianLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) {
    
    //table->dequeueCell()
    TableViewCell *cell = table->dequeueCell();
    
    if (!cell) {
        //创建一个新的cell
        cell = new TableViewCell();
        cell->setContentSize(Size(140, 80));
        
        //加入到自动释放池中
        cell->autorelease();
        
        Sprite* cellBgSp = Sprite::create("tuJianCellBg.png");
        CommonFunc::setShowAllSpriteSize(cellBgSp, 140, 80);
        cellBgSp->setAnchorPoint(Vec2(0, 0));
        cellBgSp->setPosition(0,0);
        cellBgSp->setTag(10);
        cell->addChild(cellBgSp,200);
      
        Sprite *tjSp = Sprite::create(this->allDataArray.at(idx)->cardName+"_tx.jpg");
        CommonFunc::setSpriteSize(tjSp, 40);

        tjSp->setPosition(Vec2(35,cell->getBoundingBox().size.height/2));
        tjSp->setTag(20);
        cell->addChild(tjSp,250);
        
      
        Label *label = Label::createWithTTF(this->allDataArray.at(idx)->cardName, "fonts/楷体.ttf", 16);
    
        label->setAnchorPoint(Vec2(0, 0.5));
        label->setPosition(58,cell->getBoundingBox().size.height/2);
        

        //为标签做一个标记,以便于在cell在重用队列中被取出来时，能够获取的该label并重置label信息
        label->setTag(30);
        //将标签加入到cell中
        cell->addChild(label,300);

    }
    else
    {

        Label *label = (Label*)cell->getChildByTag(30);
        label->setString(this->allDataArray.at(idx)->cardName);
        
        Sprite* tjSp = (Sprite*)cell->getChildByTag(20);
        tjSp->removeFromParentAndCleanup(true);
        tjSp = Sprite::create(this->allDataArray.at(idx)->cardName+"_tx.jpg");
        CommonFunc::setSpriteSize(tjSp, 40);
        
        tjSp->setPosition(Vec2(35,cell->getBoundingBox().size.height/2));
        tjSp->setTag(20);
        cell->addChild(tjSp,250);
        
        Sprite* cellBgSp = (Sprite*)cell->getChildByTag(10);
        cellBgSp->removeFromParentAndCleanup(true);
        cellBgSp = Sprite::create("tuJianCellBg.png");
        CommonFunc::setShowAllSpriteSize(cellBgSp, 140, 80);
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

ssize_t TuJianLayer::numberOfCellsInTableView(cocos2d::extension::TableView *table) {
    return this->allDataArray.size();
}


void TuJianLayer::initOneCardData(std::string cardName, std::string bigImage) {
    TuJianData* tjData = TuJianData::create();
   // tjData->tuJianSp = Sprite::create("smallImage");
    
    tjData->bigImage = bigImage;
    tjData->cardName = cardName;
    tjData->xiaoZhaoImage = cardName+"_ss.jpg";
    tjData->daZhaoImage = cardName+"_bs.jpg";
    this->allDataArray.pushBack(tjData);
}

void TuJianLayer::changeDetailUIInfo(TuJianData *data) {
    auto bigSp = Sprite::create(data->bigImage);
    bigSp->setScale(this->bigSprite->getScale());
    bigSp->setPosition(this->bigSprite->getPosition());
    this->bigSprite->removeFromParentAndCleanup(true);
    this->infoLayer->addChild(bigSp,100);
    this->bigSprite = bigSp;
    
   // this->appearCard->autorelease();
    Card* card;
    if (data->cardName.compare("houyi") == 0) {
        card= HouYiCard::create();
    }else if(data->cardName.compare("change") == 0) {
        card = ChangECard::create();
    }else if(data->cardName.compare("taotie") == 0) {
        card = TaoTieCard::create();
    }else if(data->cardName.compare("xingtian") == 0) {
        card = XingTianCard::create();
    }else if(data->cardName.compare("xuanwu") == 0) {
        card = XuanWuCard::create();
    }else if(data->cardName.compare("fengbo") == 0) {
        card = FengBoCard::create();
    }else if(data->cardName.compare("fenghou") == 0) {
        card = FengBoCard::create();
    }else if(data->cardName.compare("suanyu") == 0) {
        card = SuanYuCard::create();
    }
    card->playerName = this->appearCard->playerName;
    card->cardSprite = Sprite::create(card->cardSpriteImageName+"_l0.png");
    if (data->cardName.compare("houyi") == 0 || data->cardName.compare("change") == 0 || data->cardName.compare("suanyu") == 0) {
        CommonFunc::setSpriteSize(card->cardSprite, screenSize.width*0.75);
    }else {
        CommonFunc::setSpriteSize(card->cardSprite, screenSize.width*0.62);
    }
    
    card->cardSprite->setPosition(this->appearCard->cardSprite->getPosition());
    
    this->appearCard->standAction->release();
    this->appearCard->cardSprite->stopAllActions();
    this->appearCard->cardSprite->removeFromParentAndCleanup(true);
    this->infoLayer->addChild(card->cardSprite,100);
    this->appearCard->release();
    this->appearCard = card;
    this->appearCard->runZhanLiAnimation();
    this->appearCard->retain();

    
    this->changeLabelText();
    
    auto xiaoZSp = Sprite::create(data->xiaoZhaoImage);
    CommonFunc::setSpriteSize(xiaoZSp, 40);
    xiaoZSp->setPosition(this->xiaoZhaoSp->getPosition());
    this->xiaoZhaoSp->removeFromParentAndCleanup(true);
    this->infoLayer->addChild(xiaoZSp,150);
    this->xiaoZhaoSp = xiaoZSp;
    
    auto daZSp = Sprite::create(data->daZhaoImage);
    CommonFunc::setSpriteSize(daZSp, 40);
    daZSp->setPosition(this->daZhaoSp->getPosition());
    this->daZhaoSp->removeFromParentAndCleanup(true);
    this->infoLayer->addChild(daZSp,150);
    this->daZhaoSp = daZSp;
        CommonFunc::removeAnimation();
    
}

void TuJianLayer::initDetailUI(TuJianData* data) {
    infoLayer = Layer::create();
    infoLayer->setContentSize(Size(screenSize.width*0.629, screenSize.height*0.8));
    infoLayer->setPosition(20,screenSize.height-infoLayer->getBoundingBox().size.height-10);
    this->addChild(infoLayer,25);
    
 //   printf("%f", infoLayer->getPosition().y);
    Sprite* infoBgSp = Sprite::create("infoBg.jpg");
    CommonFunc::setShowAllSpriteSize(infoBgSp, screenSize.width*0.629, screenSize.height*0.8);
    infoBgSp->setPosition(infoLayer->getBoundingBox().size.width/2,infoLayer->getBoundingBox().size.height/2);
    infoLayer->addChild(infoBgSp, 50);
    
    this->bigSprite = Sprite::create(data->bigImage);
    CommonFunc::setSpriteSize(this->bigSprite, screenSize.width*0.22);
    this->bigSprite->setPosition(25+this->bigSprite->getBoundingBox().size.width/2,infoLayer->getBoundingBox().size.height-this->bigSprite->getBoundingBox().size.height/2-20);
    infoLayer->addChild(this->bigSprite,100);
    
    if (data->cardName.compare("houyi") == 0) {
        this->appearCard = HouYiCard::create();
    }else if(data->cardName.compare("change") == 0) {
        this->appearCard = ChangECard::create();
    }else if(data->cardName.compare("taotie") == 0) {
        this->appearCard = TaoTieCard::create();
    }else if(data->cardName.compare("xingtian") == 0) {
        this->appearCard = XingTianCard::create();
    }else if(data->cardName.compare("xuanwu") == 0) {
        this->appearCard = XuanWuCard::create();
    }else if(data->cardName.compare("fengbo") == 0) {
        this->appearCard = FengBoCard::create();
    }else if(data->cardName.compare("fenghou") == 0) {
        this->appearCard = FengBoCard::create();
    }else if(data->cardName.compare("suanyu") == 0) {
        this->appearCard = SuanYuCard::create();
    }
    this->appearCard->playerName = "player";
    this->appearCard->cardSprite = Sprite::create(this->appearCard->cardSpriteImageName+"_l0.png");
    CommonFunc::setSpriteSize(this->appearCard->cardSprite, screenSize.width*0.75);
    this->appearCard->cardSprite->setPosition(infoLayer->getBoundingBox().size.width*0.555,infoLayer->getBoundingBox().size.height*0.7);
    infoLayer->addChild(this->appearCard->cardSprite,100);
    this->appearCard->runZhanLiAnimation();
    this->appearCard->retain();
    
    this->xiaoZhaoSp = Sprite::create(data->xiaoZhaoImage);
    CommonFunc::setSpriteSize(this->xiaoZhaoSp, 40);
    this->xiaoZhaoSp->setPosition(this->appearCard->cardSprite->getPosition().x-20,this->appearCard->cardSprite->getPosition().y-90);
    infoLayer->addChild(this->xiaoZhaoSp,150);
    
    this->daZhaoSp = Sprite::create(data->daZhaoImage);
    CommonFunc::setSpriteSize(this->daZhaoSp, 40);
    this->daZhaoSp->setPosition(this->xiaoZhaoSp->getPosition().x,this->xiaoZhaoSp->getPosition().y-50);
    infoLayer->addChild(this->daZhaoSp,150);
}

void TuJianLayer::initShuXingLabel() {
    
    infoLayer->addChild(CommonFunc::createLabel("武力:", Vec2(this->appearCard->cardSprite->getPosition().x+80,infoLayer->getBoundingBox().size.height-50)),100);
    infoLayer->addChild(CommonFunc::createLabel("统帅:", Vec2(this->appearCard->cardSprite->getPosition().x+80,infoLayer->getBoundingBox().size.height-70)),100);
    infoLayer->addChild(CommonFunc::createLabel("智力:", Vec2(this->appearCard->cardSprite->getPosition().x+80,infoLayer->getBoundingBox().size.height-90)),100);
    infoLayer->addChild(CommonFunc::createLabel("敏捷:", Vec2(this->appearCard->cardSprite->getPosition().x+80,infoLayer->getBoundingBox().size.height-110)),100);
    infoLayer->addChild(CommonFunc::createLabel("运气:", Vec2(this->appearCard->cardSprite->getPosition().x+80,infoLayer->getBoundingBox().size.height-130)),100);
    this->wuLiLabel = CommonFunc::createLabel("", Vec2(this->appearCard->cardSprite->getPosition().x+120, infoLayer->getBoundingBox().size.height-50));
    this->tongShuaiLabel = CommonFunc::createLabel("", Vec2(this->appearCard->cardSprite->getPosition().x+120, infoLayer->getBoundingBox().size.height-70));
    this->zhiLiLabel = CommonFunc::createLabel("", Vec2(this->appearCard->cardSprite->getPosition().x+120, infoLayer->getBoundingBox().size.height-90));
    this->minJieLabel = CommonFunc::createLabel("", Vec2(this->appearCard->cardSprite->getPosition().x+120, infoLayer->getBoundingBox().size.height-110));
    this->yunQiLabel = CommonFunc::createLabel("", Vec2(this->appearCard->cardSprite->getPosition().x+120, infoLayer->getBoundingBox().size.height-130));
    infoLayer->addChild(this->wuLiLabel,100);
    infoLayer->addChild(this->tongShuaiLabel,100);
    infoLayer->addChild(this->zhiLiLabel,100);
    infoLayer->addChild(this->minJieLabel,100);
    infoLayer->addChild(this->yunQiLabel,100);
}

void TuJianLayer::changeLabelText() {
    if (this->appearCard != NULL) {
        char tempText[20] = {0};
        sprintf(tempText, "%d",(int)this->appearCard->wuLi);
        this->wuLiLabel->setString(tempText);
        
        sprintf(tempText, "%d",(int)this->appearCard->tongShuai);
        this->tongShuaiLabel->setString(tempText);
        
        sprintf(tempText, "%d",(int)this->appearCard->zhiLi);
        this->zhiLiLabel->setString(tempText);
        
        sprintf(tempText, "%d",(int)this->appearCard->mingJie);
        this->minJieLabel->setString(tempText);
        
        sprintf(tempText, "%d",(int)this->appearCard->yunQi);
        this->yunQiLabel->setString(tempText);
        
    }
}
