//
//  SetRoleFormatLayer.hpp
//  OctLegend
//
//  Created by zc on 16/9/20.
//
//

#ifndef SetRoleFormatLayer_h
#define SetRoleFormatLayer_h

#include "cocos2d.h"
//#include "FightPlayer.h"
#include "FightPlayer.h"
#include "ui/CocosGUI.h"
//#include "network/HttpClient.h"
//#include "network/HttpRequest.h"
//#include "network/HttpResponse.h"
#include "FightNetwork.h"
USING_NS_CC;
class Treasure;
class SetRoleData : public Ref {
    
public:
    virtual bool init();
    CREATE_FUNC(SetRoleData);
    Card* card;
    int cellIndex;
    Treasure* magicGoods;
    std::string imageName;
    bool noBring;
    std::string xiaoImageName;
    Sprite* xiaoSp;
    bool isPvpBuShu;
    
};

class JuanZhouLayer;
class SetRoleFormatlayer : public cocos2d::Layer {
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SetRoleFormatlayer);
    void initSetRoleFormatLayer();
    FightPlayer* player;
    FightPlayer* enemyPlayer;
    Vector<SetRoleData*> roleData;
    Vector<SetRoleData*> enemyRoleData;
    Vector<SetRoleData*> removeRoleData;
   // void initCardFormat(Card* card,std::string imageName, int standIndex,Treasure* treasure);
    Vec2 countCardOrigonPoint(Card *card,FightPlayer* tempPlayer);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    Card* currentMoveCard;
    void startFightBtn(Ref* sender, ui::Widget::TouchEventType type);
    void addFightBtnUI();
    void addBackBtnUI();
    void addEnemyBtnUI();
    void backBtn(Ref* sender, ui::Widget::TouchEventType type);
    Label* infoLabel;
    void showInfo(float dur);
    void disappearInfo();
    std::string preLayerName;
    Card* currentInfoCard;
    void initJzLayer();
    JuanZhouLayer* jzLayer;
    Card* currentTakeCard;
    
    void upServerTakeRoleInfo();
    void upServerResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
};


#endif /* SetRoleFormatLayer_h */
