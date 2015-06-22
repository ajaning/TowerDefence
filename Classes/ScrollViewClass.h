//
//  ScrollViewClass.h
//  CaratonFatans
//
//  Created by jack on 13-7-18.
//
//

#ifndef __CaratonFatans__ScrollViewClass__
#define __CaratonFatans__ScrollViewClass__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class ScrollViewClass:public CCLayer
{
private:
    ScrollViewClass();
    ~ScrollViewClass();
    bool  init();
    bool init(CCRect rect);
    void gotoPage(int index);
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void registerWithTouchDispatcher(void);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
public:
    static ScrollViewClass* create();
    void setTouchPrio(int prio);
    void removeTouchDelegate(void);
    static ScrollViewClass* create(CCRect rect);
    void addLayer(CCLayer* layer);
    void addlayer(CCLayer* layer,bool isSel,int selIndex);
    int getCurPageIndex();
    int getTotalPageNum();
private:
    CCArray* childLayerArray;
    int curPageNum;
    int touchPrio;
    float maxWidth;
    float maxHeight;
    CCPoint startDownPos;
    bool isTouchDelegate;
    bool isTouchSel;
};

#endif /* defined(__CaratonFatans__ScrollViewClass__) */
