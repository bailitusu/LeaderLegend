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
class ReadRecordFight;
class FightPlayer;
class DragonData;
USING_NS_CC;
class Dragon : public  Ref{
    
public:
    CREATE_FUNC(Dragon);
    virtual bool init();
    
    
    int bingLi;
//    int mianBao;
//    int baoJi;
    int minJie;
    int fangYu;
    int gongJi;
    int faLI;
    Sprite* dragonSprite;
    Vector<DragonSkill*> dragonSkillArray;
    Vector<DragonSkill*> allDragonSkillArray;
    int currentIndex;
    void runNextDragonSkill(FightPlayer* player);
    void addDragonSkill(DragonSkill* skill, int index);
    void initDragonShuXing();
    void runDragonAnimation(DragonData* dragonData,FightPlayer* player);
    ReadRecordFight* readRecordFight;
    void dragonAnimationBlock(DragonData* dragonData, FightPlayer* player);
    void runBlock(DragonData* dragonData);
};

#endif /* Dragon_h */
