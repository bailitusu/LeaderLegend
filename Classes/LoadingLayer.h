//
//  LoadingLayer.hpp
//  OctMountain
//
//  Created by zc on 16/11/21.
//
//

#ifndef LoadingLayer_h
#define LoadingLayer_h

#include "cocos2d.h"
USING_NS_CC;
class LoadingLayer : public Layer {
    
public:
    static LoadingLayer* GetInstance();
    virtual bool init();
    CREATE_FUNC(LoadingLayer);
    static Scene* CreateScene();
    void loading(std::string imageName);
    void loadedCallBack(Texture2D *texture);
    int totalNum;
    int haveLoadNum;
    void initLoadLayer();
    ProgressTimer* loadBar;
    Sprite* loadSpBg;
    Scene* nextScene;
    void progressBlock(std::string type);
    std::string pushType;
    
private:
    static LoadingLayer* loadingLayer;
};

#endif /* LoadingLayer_h */
