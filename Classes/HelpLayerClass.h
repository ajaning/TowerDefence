//
//  HelpLayerClass.h
//  CaratonFatans
//
//  Created by jack on 13-7-18.
//
//

#ifndef __CaratonFatans__HelpLayerClass__
#define __CaratonFatans__HelpLayerClass__

#include <iostream>
#include "cocos2d.h"
#include "ScrollViewClass.h"
USING_NS_CC;

class HelpLayerClass:public CCLayer
{
private:
    HelpLayerClass();
    ~HelpLayerClass();
    bool init();
    void helpMenuCallBack(CCObject* menu);
    CREATE_FUNC(HelpLayerClass);
public:
    static CCScene* createHelp();
private:
    ScrollViewClass* HelpScrollView;
    ScrollViewClass* TowerScrollView;
    CCSprite* monsterSprite;
    CCSprite* bottomNumSprite;
};

#endif /* defined(__CaratonFatans__HelpLayerClass__) */
