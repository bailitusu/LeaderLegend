//
//  PvpMatchLayer.hpp
//  OctLegend
//
//  Created by zc on 16/11/3.
//
//

#ifndef PvpMatchLayer_h
#define PvpMatchLayer_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FightNetwork.h"
USING_NS_CC;
class SetRoleData;
class PvpMatchLayer :  public Layer{
    
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PvpMatchLayer);
    void initMatchLayer();
    
    Sprite* background;
    ui::Button* trainingBtn;
    ui::Button* pvpMatchBtn;
    Label* pipeiLabel;
    bool isTraining;
    bool isMatchingPvp;
    void trainingBtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type);
    void pvpMatchBtnClick(cocos2d::Ref *sender, ui::Widget::TouchEventType type);
    void trainingResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void matchResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void matchSuccessResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void checkIsMatchSuccess(float dur);
    void enterNextScene(float dur);
    bool analysisResponseData(std::string infoStr,std::string reponseName);
    Vector<SetRoleData*> myData;
    std::string battleID;
    std::string player1;
    std::string player2;
};

#endif /* PvpMatchLayer_h */
