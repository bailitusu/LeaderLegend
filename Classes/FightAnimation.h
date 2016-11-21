//
//  FightAnimation.hpp
//  OctLegend
//
//  Created by zc on 16/10/24.
//
//

#ifndef FightAnimation_h
#define FightAnimation_h

#include "cocos2d.h"
USING_NS_CC;
class FightAnimation : public Ref  {
    
public:
    virtual bool init();
    CREATE_FUNC(FightAnimation);
    std::string playerID;
    std::string cardID;
    std::string type;
    int delay;
   // Vector<std::string> userInfo;
};


#endif /* FightAnimation_h */
