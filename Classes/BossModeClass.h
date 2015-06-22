//
//  BossModeClass.h
//  CaratonFatans
//
//  Created by  Jack on 13-12-3.
//
//

#ifndef __CaratonFatans__BossModeClass__
#define __CaratonFatans__BossModeClass__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class BossModeClass:public CCLayer
{
private:
    BossModeClass();
    ~BossModeClass();
    bool init();
    CREATE_FUNC(BossModeClass);
    
    void loadResAndInit();
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void gotoBossIndexNow(int index);
    void gotoBossIndexActionCallBack();
    
    
    void menuSelActionCallBack(CCObject* object);
    
    
public:
    static CCScene* createScene();
private:
    
    int bossIndex;
    
    CCSprite* curHideShadeBossSprite;
    CCSprite* curSelBossSprite;
    CCArray* bossShaderArray;//BOSS阴影图像，由GL混合生成
    CCArray* bossNormalArray;//BOSS正常图片
    
    CCPoint userTouchStartPos;
    
    CCLayer* showBossLayer;//展示BOSS的LAYER
    
    CCSprite* gameBG;
    CCSprite* lightSprite;
    CCSprite* bossNameSprite;
//    CCSprite* userHonourSprite;//用户荣誉
    CCSprite* bloodValueSprite;
    CCSprite* bossTimeLimitSprite;
    CCMenuItemImage* startBossMenuItem;
    
    
    
};

#endif /* defined(__CaratonFatans__BossModeClass__) */
