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
#include "Treasure.h"
#include "ReadRecordFight.h"
USING_NS_CC;

class OneRecord;
class FightPlayer;
class Card: public Ref, public StandMapCellInterface  {

public:
    std::string cardName;
    std::string playerName;
    std::string cardSpriteImageName;
    std::string xiaoZhaoInfo;
    std::string daZhaoInfo;
    Sprite* cardSprite;
    Vec2 cardPosition;
    int cellIndex;
    CREATE_FUNC(Card);
    int HP;
    int MaxHP;
    
    Label *textLabel;
    virtual bool init();
    virtual void didBeHit(Card* fromCard, std::string hitKinds);
    virtual void recordDidBeHit(Card* fromCard, std::string hitKinds);
    virtual void runAnimation(FightPlayer* playerTemp);
    virtual void ultimateSkill();
    virtual void cardDead();
    virtual void initCardSprite(std::string imageName);
    virtual void initFightShuXing();
    
    virtual void addHP(Card* card,float hpValue);
    virtual void decreaseHP(Card* card,float hpValue);
    virtual void addNuQi(Card* card,int num);
    virtual void decreaseNuQi(Card* card,int num, bool isDaZhao);
    
    virtual void nuQiAppear(Card* card, int num);
    virtual void hpAppear(Card *card, int hitValue, int hp);
    
    virtual void recordAddHP(Card *card, float hpValue);
    virtual void recordCardDead();
    virtual void recordDecreaseHP(Card* card,float hpValue);
    virtual void recordAddNuqi(Card* card,int num);
    virtual void recordDecreaseNuqi(Card *card, int num,bool isDaZhao);
    virtual void recordRuning(FightPlayer* enemyTemp);
    virtual void willRun(FightPlayer* enemyTemp);
    virtual void running(FightPlayer* enemyTemp);
    
    virtual void endRun(FightPlayer* enemyTemp);
    
    virtual void xiaoSkll(OneRecord* info);
    virtual void daSkill(OneRecord* info);
    virtual void initCharacter();
    virtual void suckBlood(Card* fangYuCard);
    virtual void zaiShengBlood(bool isRecord);
    virtual void actionBlock();
    virtual void recordActionBlock();
    virtual void textLabelDisappearBlock();
    virtual void initHpLabel();
    virtual void showLabelText(Label* label, int hpValue, std::string text);
    virtual void runZhanLiAnimation();
    virtual void animationShanBi();
    virtual void stopStandAnimation();
    virtual void preCardAudio();
    virtual void preAddCardAnimationResource();
    
    virtual void beforeAnimation(OneRecord *info,Card* card);
    virtual void afterAnimation(OneRecord *info, Card* card);
    RepeatForever* standAction;
    
    Buff* fBuff;
    FightProgress* fPro;
    int nuQiNum;
    int nuQiNumMax;
    FightPlayer* forEnemy;
    FightPlayer* forPlayer;
    Vector<Buff*> buffArray;
    Treasure* magicGoods;
    ReadRecordFight* readRecordFight;
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
    int targetNum;
};

#endif /* Card_h */
