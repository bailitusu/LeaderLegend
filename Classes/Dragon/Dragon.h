//
//  Dragon.hpp
//  OctLegend
//
//  Created by zc on 16/8/29.
//
//

#ifndef Dragon_h
#define Dragon_h

#include "cocos2d.h"
#include "DragonSkill.h"
class FightPlayer;
USING_NS_CC;
class Dragon : public  Ref{
    
public:
    CREATE_FUNC(Dragon);
    virtual bool init();
    
    
    int bingLi;
    float mianBao;
    float baoJi;
    float fangYu;
    float gongJi;
    float faLI;
    Sprite* dragonSprite;
    Vector<DragonSkill*> dragonSkillArray;
    int currentIndex;
    void runNextDragonSkill(FightPlayer* player);
    void addDragonSkill(DragonSkill* skill, int index);
};

#endif /* Dragon_h */
