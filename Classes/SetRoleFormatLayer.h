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
#include "FightPlayer.h"
#include "ui/CocosGUI.h"
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
};

class SetRoleFormatlayer : public cocos2d::Layer {
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SetRoleFormatlayer);
    void initSetRoleFormatLayer();
    FightPlayer* player;
    Vector<SetRoleData*> roleData;
    void initCardFormat(Card* card,std::string imageName, int standIndex,Treasure* treasure);
    Vec2 countCardOrigonPoint(Card *card);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    Card* currentMoveCard;
    void startFightBtn(Ref* sender, ui::Widget::TouchEventType type);
};


#endif /* SetRoleFormatLayer_h */
