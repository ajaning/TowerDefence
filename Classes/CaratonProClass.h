//
//  CaratonProClass.h
//  CaratonFatans
//
//  Created by jack on 13-11-6.
//
//

#ifndef __CaratonFatans__CaratonProClass__
#define __CaratonFatans__CaratonProClass__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class CaratonProClass:public CCNode
{
private:
    CaratonProClass();
    ~CaratonProClass();
    bool init(CCPoint pos);
    void aniActionCallBack(CCObject* object);
    void aniSelTimerCallBack(CCObject* object);
public:
    //CREATE_FUNC(CaratonProClass);
    static CaratonProClass* create(CCPoint pos);
    void setCaratonCurLifeValue(int value);
    int getCaratonCurLifeValue(void);
    bool checkCaratonIsBited(CCPoint enemyPos,CCSize enemySize);
    void userTouchCaraton();
    CCSize getCaratonSize();//获得胡萝卜的大小
    CCPoint getCaratonPos();
    void stopHLBAllAction();
private:
    
    bool isAnimationStart;//
    int totalLifeValue;
    int curLifeValue;
    
    CCAnimation* normalAniAction;
    CCSequence* shakeAction;
    CCAnimation* blinkAniAction;
    CCAnimation* coldAniAction;
    CCSprite* caratonSprite;
    CCSprite* lifeNumSprite;
};

#endif /* defined(__CaratonFatans__CaratonProClass__) */
