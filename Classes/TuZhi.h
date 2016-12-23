//
//  TuZhi.hpp
//  OctMountain
//
//  Created by zc on 16/11/25.
//
//

#ifndef TuZhi_h
#define TuZhi_h

#include "cocos2d.h"
USING_NS_CC;

struct caiLiaoType {
    std::string jin = "jin";
    std::string mu = "mu";
    std::string shui = "shui";
    std::string huo = "huo";
    std::string tu = "tu";
};

class TuZhi : public Ref {
    
public:
    virtual bool init();
    CREATE_FUNC(TuZhi);
    //  Sprite* tuZhiSp;
    std::string tuZhiSpImage;
    std::string tuZhiInfo;
    std::string tuZhiName;
    std::string faBaoSpImage;
    std::string type;
    int needGoldNum;
    int needTieNum;
    int needCaiLiaoNum;
    
};

#endif /* TuZhi_h */
