//
//  FuBenLayer.hpp
//  OctLegend
//
//  Created by zc on 16/9/28.
//
//

#ifndef FuBenLayer_h
#define FuBenLayer_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SetRoleFormatLayer.h"
USING_NS_CC;
class FuBenLayer : public Layer {
    
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(FuBenLayer);
    void initFuBenLayer();
    ui::Button* enemyOne;
   // void enemyOneBtn(Ref* sender, ui::Widget::TouchEventType typr);
    Vector<SetRoleData*> myRoleData;
    Vector<SetRoleData*> enemyRoleData;
    SetRoleFormatlayer* roleFormatLayer;
    void cardFormatEnemy(Card* card,std::string imageName, int standIndex,Treasure* treasure);
    void readEnemyData();
    void backBtnUI();
    void backBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type);
    //virtual void onExit();
};

#endif /* FuBenLayer_h */
