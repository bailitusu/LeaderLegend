//
//  PvpFightLayer.hpp
//  OctLegend
//
//  Created by zc on 16/11/3.
//
//

#ifndef PvpFightLayer_h
#define PvpFightLayer_h

#include "cocos2d.h"
#include "FightPlayer.h"
#include "SetRoleFormatLayer.h"
#include "ui/CocosGUI.h"
#include "LingShoLayer.h"
USING_NS_CC;
class PvpFightLayer : public Layer {
    
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PvpFightLayer);
    void initPvpLayer();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    void initChouTiLayer();
   // std::string battleKey;
    Layer* chouTiLayer;
    FightPlayer* player;
    FightPlayer* playerEnemy;
    std::string battleKey;
    std::string player1Key;
    std::string player2Key;
    Sprite* background;
    std::string fightInfo;
    
    ui::Button* chouTiBtn;
    void chouTibtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type);
    Vec2 countCardOrigonPoint(Card *card,FightPlayer* tempPlayer);
    Vector<SetRoleData*> myTakeRoleData;
    Card* moveCard;
    ui::Button* buShuOverBtn;
    void buShubtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type);
    void buShuResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void checkFightOk(float dur);
    void checkFightResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    int roundNum;
    Label* roundLabel;
    void gameOver();
    void enterMatchScene(float dur);
    void roundOver();
    bool isRounding;
    void daoJiShi(float dur);
    int timeNum;
    
    void initLeftChouTi();
    Layer* leftChouTi;
    Vector<SkillGezi*> dragonSkillData;
    
    ui::Button* leftChouTiBtn;
    void leftChouTiClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type);
    SkillGezi* currentClickSkill;
    void jisuanEnableSkill();
    void enableSkill(int skillType);
    
    Sprite* liziQiu;
   // ParticleSystem* cps;
    Sprite* longJuanFengSp;
    void longJuanFengBlock();
    void createLiangGezi(float dur);
  //  int* shunxuArray;
    int currentLiangNum;
};

#endif /* PvpFightLayer_h */
