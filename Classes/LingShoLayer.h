//
//  LingShoLayer.hpp
//  OctLegend
//
//  Created by zc on 16/10/11.
//
//

#ifndef LingShoLayer_h
#define LingShoLayer_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
class Bag;
class Dragon;
class DragonSkill;
class SkillScrollLayer;
class LingShouInfoLayer;
class SkillGezi : public Ref {
    
public:
    virtual bool init();
    CREATE_FUNC(SkillGezi);
    Sprite* geZiSp;
    DragonSkill* obj;
    int index;
    Vec2 geziPositon;
};


class LingShoLayer : public Layer {
    
public:
    virtual bool init();
    CREATE_FUNC(LingShoLayer);
    static Scene* createScene();
    Dragon* myDragon;
    Bag* myBag;
    void initLingShoLayer();
    Vector<SkillGezi*> takeSkillArray;
    Vector<SkillGezi*> allSkillArray;
    void initTakeGezi();
    void initAllGezi();
    void initPeiYangBtn();
    void initShuXingLabel();
 //   void initTaoZi();
    Sprite* lingShouImage;
    void peiYangBtn(Ref* sender, ui::Widget::TouchEventType type);
  //  void skillBtn(Ref* sender, ui::Widget::TouchEventType type);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    Label* bingLiLabel;
//    Label* mianBaoLabel;
//    Label* baoJiLabel;
    Label* minJieLabel;
    Label* fangYuLabel;
    Label* gongJiLabel;
    Label* faLiLabel;
    Label* taoZiNumLabel;
    Label* createLabel(std::string text,Vec2 positon);
    SkillScrollLayer* scrollLayer;
    void changeTakeSkill(DragonSkill* ds, bool isRemove);
    void changeAllSkill(DragonSkill* ds);
    
    DragonSkill* currentInfoDs;
    bool isShowInfo;
    void showInfo(float dur);
    void disapperInfo();
    LingShouInfoLayer* lsInfoLayer;
  //  void taoZiBtn(Ref* sender, ui::Widget::TouchEventType type);
    
    void backBtnUI();
    void backBtn(cocos2d::Ref *sender, ui::Widget::TouchEventType type);

};


#endif /* LingShoLayer_h */
