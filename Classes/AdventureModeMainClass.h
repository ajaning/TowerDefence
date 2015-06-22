//
//  AdventureModeMainClass.h
//  CaratonFatans
//
//  Created by  Jack on 13-12-5.
//
//

#ifndef __CaratonFatans__AdventureModeMainClass__
#define __CaratonFatans__AdventureModeMainClass__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class AdventureModeMainClass:public CCLayer
{
private:
    AdventureModeMainClass();
    ~AdventureModeMainClass();
    bool init();
    void loadResAndInit();
    CREATE_FUNC(AdventureModeMainClass);
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void gotoPageIndexNow(int index);
    void gotoPageIndexActionCallBack();
    
    void selMenuCallBack(CCObject* menu);
    
public:
    static CCScene* createScene();
private:
    
    int curPageIndex;
    
    CCPoint userTouchStartPos;
    
    CCLayer* scrollLayer;
    CCMenuItemImage* leftPointMenu;
    CCMenuItemImage* rightPointMenu;
    
    CCArray* userPointArray;
    CCSprite* loadWaitSprite;
    
};

#endif /* defined(__CaratonFatans__AdventureModeMainClass__) */
