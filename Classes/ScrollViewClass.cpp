//
//  ScrollViewClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-7-18.
//
//

#include "ScrollViewClass.h"
#include "LcdAdapClass.h"
#define DELTA_SCROLL   (5)

ScrollViewClass::ScrollViewClass()
{

}

ScrollViewClass::~ScrollViewClass()
{
    
}

bool ScrollViewClass::init()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(this);
    
    this->setContentSize(size);
    curPageNum = 0;
    childLayerArray = CCArray::create();
    childLayerArray->retain();
    maxWidth = size.width;
    maxHeight = size.height;
    startDownPos = CCPoint(0,0);
    isTouchDelegate = false;
    isTouchSel = false;
    return true;
}


bool ScrollViewClass::init(cocos2d::CCRect rect)
{
    this->init();
    this->setPosition(rect.origin);
    this->setContentSize(rect.size);
    maxWidth = rect.size.width;
    maxHeight = rect.size.height;
    
    return true;
}

ScrollViewClass* ScrollViewClass::create()
{
    ScrollViewClass* scroll = new ScrollViewClass();
    if (scroll && scroll->init()) {
        scroll->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(scroll);
    }
    
    return scroll;
}

ScrollViewClass* ScrollViewClass::create(cocos2d::CCRect rect)
{
    ScrollViewClass* scroll = new ScrollViewClass();
    if (scroll && scroll->init(rect)) {
        scroll->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(scroll);
    }
    
    return scroll;
}

void ScrollViewClass::setTouchPrio(int prio)
{
//    this->removeTouchDelegate();
//    isTouchDelegate = true;
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, prio, false);
}

void ScrollViewClass::removeTouchDelegate()
{
//    if (isTouchDelegate) {
//        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
//        isTouchDelegate = false;
//    }
}


void ScrollViewClass::onEnter()
{
    CCLayer::onEnter();
    this->setTouchEnabled(true);
}

void ScrollViewClass::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void ScrollViewClass::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0,false);
}

bool ScrollViewClass::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    startDownPos = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

    
    return true;
}

void ScrollViewClass::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint curPos = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCPoint prePos = CCDirector::sharedDirector()->convertToGL(pTouch->getPreviousLocationInView());
    
    CCPoint diffPos = ccpSub(curPos, prePos);
    
    CCPoint myPos = this->getPosition();
    this->setPosition(ccpAdd(ccp(myPos.x, myPos.y), ccp(diffPos.x, 0)));
    
}

void ScrollViewClass::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint curPos = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCPoint prePos = startDownPos;
    
    CCPoint diffPos = ccpSub(curPos, prePos);
    if (ccpLength(ccp(diffPos.x, 0)) > DELTA_SCROLL) {//means scroll
        int count = childLayerArray->count();
        int index = curPageNum;
        if (diffPos.x < 0) {
            if ((index + 1) >= count) {
                this->gotoPage(curPageNum);
            }
            else
            {
                this->gotoPage(++curPageNum);
            }
        }
        else
        {
            if ((index - 1) <= 0) {
                curPageNum = 0;
                this->gotoPage(curPageNum);
            }
            else
            {
                this->gotoPage(--curPageNum);
            }
        }
    }
    else
    {
        if (isTouchSel) {
            CCLayer* curLayer = (CCLayer*)childLayerArray->objectAtIndex(curPageNum);
            curLayer->ccTouchEnded(pTouch, pEvent);
        }
    }
}


void ScrollViewClass::gotoPage(int index)
{
    CCActionInterval* moveTo = CCMoveTo::create(0.5f, ccp(-index * maxWidth, 0));
    this->runAction(moveTo);
}


void ScrollViewClass::addLayer(cocos2d::CCLayer *layer)
{
    CCAssert(!(layer == NULL), "cannot be NULL");
    int count = childLayerArray->count();
    layer->setContentSize(ccp(maxWidth,maxHeight));
    layer->setPosition(ccp((count) * maxWidth, 0));
    
    this->addChild(layer);
    childLayerArray->addObject(layer);
}

void ScrollViewClass::addlayer(cocos2d::CCLayer *layer, bool isSel, int selIndex)
{
    int count = 0;
    this->addLayer(layer);
    isTouchSel = isSel;
    count = childLayerArray->count();
    if (selIndex >= count && count > 0) {
        curPageNum = count - 1;
    }
    else if(selIndex < 0)
    {
        curPageNum = 0;
    }
    else
    {
        curPageNum = selIndex;
    }
    
    if (curPageNum > 0) {
        this->setPosition(-curPageNum * maxWidth, 0);
    }
    
}

int ScrollViewClass::getCurPageIndex()
{
    return (curPageNum + 1);
}

int ScrollViewClass::getTotalPageNum()
{
    return (childLayerArray->count());
}
