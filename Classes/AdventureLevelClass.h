//
//  AdventureLevelClass.h
//  CaratonFatans
//
//  Created by  Jack on 13-12-5.
//
//

#ifndef __CaratonFatans__AdventureLevelClass__
#define __CaratonFatans__AdventureLevelClass__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class AdventureLevelClass:public CCLayer
{
private:
    AdventureLevelClass();
    ~AdventureLevelClass();
    bool init();
    
    void loadResAndInit();
    
    CREATE_FUNC(AdventureLevelClass);
    
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
    
    int levelNum;
    
    CCPoint userTouchStartPos;
    
    CCLayer* scrollLayer;

    CCArray* levelShadeArray;//关卡图片加阴影
    CCArray* levelNormalArray;//关卡图片正常显示
    CCSprite* levelTowerTypeSP;//每关炮塔种类
    CCSprite* levelNumSP;//每关关卡数目
    
    CCSprite* curShadeLevelSprite;
    CCSprite* curNormalLevelSprite;
    
    CCSprite* bgSprite;//game bg
    CCMenuItemImage* gameStartMenu;
    
    CCSprite* loadWaitSprite;
    
};
#endif /* defined(__CaratonFatans__AdventureLevelClass__) */
