//
//  FightNetwork.hpp
//  OctLegend
//
//  Created by zc on 16/11/1.
//
//

#ifndef FightNetwork_h
#define FightNetwork_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define BaseURL "http://120.25.98.248:8900"
//#define PvePlayerTakeCardGetUrl "http://192.168.1.104:8900/player/"
//#define PveGuaiWuInfoGetUrl "http://192.168.1.104:8900/pve/%d"
//#define PveUpdataMyInfoPostUrl "http://192.168.1.104:8900/pve"
//#define PvpTrainingPostUrl "http://192.168.1.104:8900/pvp/training"
//#define PvpMatchPostUrl "http://192.168.1.104:8900/pvp/match"
//#define PvpMatchCheckOkPostUrl "http://192.168.1.104:8900/pvp/match/message"
//#define PvpBushuPostUrl "http://192.168.1.104:8900/pvp"
//#define PvpCheckBushuOkPostUrl "http://192.168.1.104:8900/pvp/message"

#define PvePlayerTakeCardGetUrl "http://120.25.98.248:8900/player/"
#define PveGuaiWuInfoGetUrl "http://120.25.98.248:8900/pve/%d"
#define PveUpdataMyInfoPostUrl "http://120.25.98.248:8900/pve"
#define PvpTrainingPostUrl "http://120.25.98.248:8900/pvp/training"
#define PvpMatchPostUrl "http://120.25.98.248:8900/pvp/match"
#define PvpMatchCheckOkPostUrl "http://120.25.98.248:8900/pvp/match/message"
#define PvpBushuPostUrl "http://120.25.98.248:8900/pvp"
#define PvpCheckBushuOkPostUrl "http://120.25.98.248:8900/pvp/message"

using namespace network;
class FightNetwork : public Ref {
    
public:
    static FightNetwork* GetInstance();

    virtual bool init();
    CREATE_FUNC(FightNetwork);
    void createPostHttp(std::string url,Ref* pTarget, SEL_HttpResponse pSelector,const char* data);
    void responseCallBack(HttpClient *sender, HttpResponse *response);
    void createGetHttp(std::string url,Ref* pTarget, SEL_HttpResponse pSelector);
    
private:
    
    static FightNetwork* fightNetwork;
};

#endif /* FightNetwork_h */
