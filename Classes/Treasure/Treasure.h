//
//  Treasure.hpp
//  OctLegend
//
//  Created by zc on 16/8/30.
//
//

#ifndef Treasure_h
#define Treasure_h

#include "cocos2d.h"
class Card;
class FightPlayer;
USING_NS_CC;
class Treasure : public Ref {
    
public:
    CREATE_FUNC(Treasure);
    virtual bool init();
    
    float gongJi;
    float fangYu;
    float faLi;
    float mingZhong;
    float shanBi;
    float baoJi;
    float level;
    float mianBao;
    bool isBuDao;
    std::string treasureName;
    int nuQiNum;
    virtual void initNuQi(Card* card);
    virtual void willRunAddNuQi(Card* card);
    virtual float specialMianShang(Card* card, float value);
    virtual void everyRoundAddHP(Card* card);
    virtual void bingFaHuiFuHp(FightPlayer* player);
    virtual bool spriteBrother(Card* card);
    virtual bool mianYiCuoZhi();
    virtual float fanTanWuLiHart(float hartValue);
    virtual float fanTanFaShuHart(float hartValue);
    virtual void initRecordNuqi(Card* card);
};

#endif /* Treasure_hpp */
