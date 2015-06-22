//
//  WelcomeLayerClass.h
//  CaratonFatans
//
//  Created by jack on 13-7-15.
//
//

#ifndef __CaratonFatans__WelcomeLayerClass__
#define __CaratonFatans__WelcomeLayerClass__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class WelcomeLayerClass:public CCLayer
{
private:
    WelcomeLayerClass();
    ~WelcomeLayerClass();
    bool init();
    CREATE_FUNC(WelcomeLayerClass);
    
    void cloudMoveByCallBack(CCNode* parent);
    void selMenuCallBack(CCObject* parent);
public:
    static CCScene* welcomSceneCreate();
private:
    CCSprite* luoboSprite;
    CCSprite* enemySprite;
    CCSprite* cloudBGSprite;
};


#endif /* defined(__CaratonFatans__WelcomeLayerClass__) */
