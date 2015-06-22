//
//  GameSubLevelSelClass.h
//  CaratonFatans
//
//  Created by jack on 13-7-22.
//
//

#ifndef __CaratonFatans__GameSubLevelSelClass__
#define __CaratonFatans__GameSubLevelSelClass__

#include "cocos2d.h"

USING_NS_CC;

class GameSubLevelSelClass:public CCLayer
{
private:
    GameSubLevelSelClass();
    ~GameSubLevelSelClass();
    virtual void onEnter();
    virtual void onExit();
    
    bool init(cocos2d::CCObject *target, cocos2d::SEL_CallFunc selector);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
public:
    static GameSubLevelSelClass* create(cocos2d::CCObject *target, cocos2d::SEL_CallFunc selector);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
private:
    CCObject* myTarget;
    SEL_CallFunc mySelector;
};

#endif /* defined(__CaratonFatans__GameSubLevelSelClass__) */
