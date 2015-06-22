//
//  gameADShowClass.h
//  CaratonFatans
//
//  Created by jack on 13-12-27.
//
//

#ifndef __CaratonFatans__gameADShowClass__
#define __CaratonFatans__gameADShowClass__

#include <iostream>

#include "cocos2d.h"

USING_NS_CC;

class gameADShowClass:public CCLayer
{
private:
    gameADShowClass();
    ~gameADShowClass();
    bool init();
    
    
    virtual void update(float dt);
    void menuActionCallBack(CCObject* object);
    
    void updateMyGlodNumLab();
    
public:
    CREATE_FUNC(gameADShowClass);
    static CCScene* createMyScene();
private:
    CCLabelAtlas* myGoldNumLab;
};

#endif /* defined(__CaratonFatans__gameADShowClass__) */
