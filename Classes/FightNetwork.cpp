//
//  FightNetwork.cpp
//  OctLegend
//
//  Created by zc on 16/11/1.
//
//

#include "FightNetwork.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace cocos2d::extension;


FightNetwork* FightNetwork::fightNetwork = NULL;

bool FightNetwork::init() {
    return true;
}

FightNetwork* FightNetwork::GetInstance() {
    if (fightNetwork == NULL) {
        fightNetwork = FightNetwork::create();
        fightNetwork->retain();
        return fightNetwork;
    }
    return fightNetwork;
}

void FightNetwork::createPostHttp(std::string url,Ref* pTarget, SEL_HttpResponse pSelector,const char* data) {
    auto request = new HttpRequest();
    request->setUrl(url);
    request->setRequestType(HttpRequest::Type::POST);
    request->setResponseCallback(pTarget, pSelector);
    
    request->setRequestData(data, strlen(data));
    HttpClient::getInstance()->send(request);
    HttpClient::getInstance()->setTimeoutForRead(3);
    HttpClient::getInstance()->setTimeoutForConnect(3);
    request->release();
    
}

void FightNetwork::responseCallBack(HttpClient *sender, HttpResponse *response) {
//    std::string tag = response->getHttpRequest()->getTag();
//    if (tag.compare("getFightRecord") == 0) {
//        printf("success");
//    }
    if (response->isSucceed()) {
        std::vector<char> *buffer = response->getResponseData();
        for (int i = 0; i < buffer->size(); i++) {
            printf("%c",(*buffer)[i]);
        }
    }
}

void FightNetwork::createGetHttp(std::string url, cocos2d::Ref *pTarget, SEL_HttpResponse pSelector) {
    auto request = new HttpRequest();
    request->setUrl(url);//?playerkey=zyh&battleid=1&cards=taotie-xingtian-change&cells=0-1-3
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(pTarget, pSelector);
 //   request->setTag("getFightRecord");
    HttpClient::getInstance()->send(request);
    HttpClient::getInstance()->setTimeoutForRead(3);
    HttpClient::getInstance()->setTimeoutForConnect(3);
    request->release();
}
