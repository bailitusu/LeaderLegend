//
//  JiuXiaoLongYin.hpp
//  OctLegend
//
//  Created by zc on 16/8/30.
//
//

#ifndef JiuXiaoLongYin_h
#define JiuXiaoLongYin_h

#include "cocos2d.h"
#include "DragonSkill.h"
class JiuXiaoLongYin : public DragonSkill {
    
public:
    CREATE_FUNC(JiuXiaoLongYin);
    virtual bool init();
    virtual void runSkill(FightPlayer* player);
};

#endif /* JiuXiaoLongYin_hpp */
