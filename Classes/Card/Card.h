//
//  Card.hpp
//  OctLegend
//
//  Created by zc on 16/8/12.
//
//

#ifndef Card_h
#define Card_h

#include "cocos2d.h"
#include "StandMapCellInterface.h"
#include "FightProgress.h"
#include "Buff.h"
USING_NS_CC;

class FightPlayer;
class Card: public Ref, public StandMapCellInterface  {

public:
    std::string cardName;
    std::string playerName;
    Sprite* cardSprite;
    Vec2 cardPosition;
    int cellIndex;
    CREATE_FUNC(Card);
    int HP;
    int MaxHP;
    virtual bool init();
    virtual void didBeHit(Card* fromCard, std::string hitKinds);
    virtual void runAnimation(FightPlayer* playerTemp);
    virtual void ultimateSkill();
    virtual void cardDead();
    virtual void initCardSprite(std::string imageName);
    virtual void initFightShuXing();
    
    virtual void addHP(Card* card,float hpValue);
    virtual void decreaseHP(Card* card,float hpValue);
    virtual void addNuQi(Card* card,int num);
    virtual void decreaseNuQi(Card* card,int num, bool isDaZhao);
    
    virtual void willRun(FightPlayer* enemyTemp);
    virtual void running(FightPlayer* enemyTemp);
    virtual void endRun(FightPlayer* enemyTemp);
    
    virtual void initCharacter();
    virtual void suckBlood();
    virtual void zaiShengBlood();
    virtual void actionBlock();
    Buff* fBuff;
    FightProgress* fPro;
    FightPlayer* forEnemy;
    FightPlayer* forPlayer;
    Vector<Buff*> buffArray;
    Buff* isHaveThisBuff(std::string buffName);
    int hitRuleNum;
    
    int bingKinds;
    int huiHe;
    float wuLi;
    float tongShuai;
    float zhiLi;
    float mingJie;
    float yunQi;
    float gongJi;
    float faLi;
    float fangYu;

    
    float wuliHart;
    float wuliMianShang;
    float fashuMianShang;
    float fashuHart;
    float mingZhong;
    float baoJi;
    float shanBi;
    float mianBao;
    float geDang;
    float xianZhi;
    float fanJi;
    float fashuShanBi;
    float lianJi;
    float xianGong;
    
    float zhiLiao;
    float xiXue;
    float hitLevel;
    int cardLevel;
    float hitValue;
};

#endif /* Card_h */
