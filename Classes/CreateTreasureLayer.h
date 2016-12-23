//
//  CreateTreasureLayer.hpp
//  OctMountain
//
//  Created by zc on 16/11/24.
//
//

#ifndef CreateTreasureLayer_h
#define CreateTreasureLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "TuZhi.h"
#include "Bag.h"
#include "ui/CocosGUI.h"
USING_NS_CC_EXT;
USING_NS_CC;

//class TuZhiData : public Ref {
//public:
//    virtual bool init();
//    CREATE_FUNC(TuZhiData);
//  //  Sprite* tuZhiSp;
//    std::string tuZhiSpImage;
//    std::string tuZhiInfo;
//    std::string tuZhiName;
//};

class CreateTreasureLayer : public Layer, TableViewDelegate, TableViewDataSource{
    
public:
    virtual bool init();
    CREATE_FUNC(CreateTreasureLayer);
    void initCreateFabaoLayer();
    void initTabelView();
    
    TableView* tuZhiTableView;
    Vector<TuZhi*> allData;
    ssize_t oldNum;
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    void initDetailUIInfo(TuZhi* tzOneData);
    void changeUIInfo(TuZhi* tz);
    Bag* myBag;
    Sprite* fabaoSp;
    Sprite* caiLiaoSp;
    Label* needGoldLabel;
    Label* needCaiLiaoLabel;
    Label* needTieLabel;
    
    Label* haveGoldLabel;
    Label* haveCaiLiaoLabel;
    Label* haveTieLabel;
    
    Sprite* finishFaBaoGeZi;
    
    ui::Button* daZaoBtn;
    void daZaoClick(Ref* pSender,ui::Widget::TouchEventType type);
    Layer* infoLayer;
};

#endif /* CreateTreasureLayer_h */
