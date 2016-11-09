//
//  PveFightLayer.hpp
//  OctLegend
//
//  Created by zc on 16/11/8.
//
//

#ifndef PveFightLayer_h
#define PveFightLayer_h

#include "cocos2d.h"
#include "FightPlayer.h"
#include "SetRoleFormatLayer.h"
#include "ui/CocosGUI.h"
#include "FightNetwork.h"
USING_NS_CC;
class PveFightLayer : public Layer {
    
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PveFightLayer);
    void initPveLayer();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    void initChouTiLayer();
    // std::string battleKey;
    Layer* chouTiLayer;
    FightPlayer* player;
    FightPlayer* playerEnemy;

    Sprite* background;
    std::string fightInfo;
    
    ui::Button* chouTiBtn;
    void chouTibtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type);
    void startFightBtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type);
    Vec2 countCardOrigonPoint(Card *card,FightPlayer* tempPlayer);
  //  Vector<SetRoleData*> myTakeRoleData;
    Vector<SetRoleData*> myAllData;
    Vector<SetRoleData*> enemyRoleData;
    void addMyTakeCard();
    void takeCardResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    Card* moveCard;
    ui::Button* startFightBtn;
    
    void upServerTakeRoleInfo();
    void upResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void initEnemyInfo();
    int guaiWuID;
};

#endif /* PveFightLayer_h */
