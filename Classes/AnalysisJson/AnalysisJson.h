//
//  AnalysisJson.hpp
//  OctLegend
//
//  Created by zc on 16/10/24.
//
//

#ifndef AnalysisJson_h
#define AnalysisJson_h

#include "cocos2d.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;

class AnalysisJson : public Ref {
    
public:
    static AnalysisJson* GetInstance();
    virtual bool init();
    CREATE_FUNC(AnalysisJson);
    std::string initialJson;
    
    void readNextJson();
    int currentIndex;
    void readCurrentAnimationJson(rapidjson::Value &array);
    
private:
    static AnalysisJson* analysisJson;
};

#endif /* AnalysisJson_h */
