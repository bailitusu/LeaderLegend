//
//  TuJianLayer.hpp
//  OctLegend
//
//  Created by zc on 16/10/17.
//
//

#ifndef TuJianLayer_h
#define TuJianLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
class Card;

class TuJianData : public Ref {
    
public:
    virtual bool init();
    CREATE_FUNC(TuJianData);
    Sprite* tuJianSp;
    std::string bigImage;
    std::string cardName;
    std::string xiaoZhaoImage;
    std::string daZhaoImage;
    std::string cardLabelName;
    
};

class TuJianLayer : public Layer, TableViewDataSource, TableViewDelegate {
    
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TuJianLayer);
    Vector<TuJianData*> allDataArray;
    void initTuJianLayer();
    void initOneCardData(std::string cardName,std::string cardLabelName,std::string bigImage);
    Sprite* bigSprite;
    Sprite* xiaoZhaoSp;
    Sprite* daZhaoSp;
    Label* xiaoZhaoLabel;
    Label* daZhaoLabel;
    Card* appearCard;
    void initDetailUI(TuJianData* data);
    void changeDetailUIInfo(TuJianData* data);
    void initShuXingLabel();
    Label* wuLiLabel;
    Label* tongShuaiLabel;
    Label* zhiLiLabel;
    Label* minJieLabel;
    Label* yunQiLabel;
    void changeLabelText();
    Layer* infoLayer;
    TableView* allInfoTabelView;
    ssize_t oldNum;
    void initTabelView();
    
    
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);

    void backBtnUI();
    void backBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type);
};

#endif /* TuJianLayer_hpp */
