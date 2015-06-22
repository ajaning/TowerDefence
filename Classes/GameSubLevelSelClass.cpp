//
//  GameSubLevelSelClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-7-22.
//
//

#include "GameSubLevelSelClass.h"

GameSubLevelSelClass::GameSubLevelSelClass()
{

}

GameSubLevelSelClass::~GameSubLevelSelClass()
{
//    myTarget->release();
}

bool GameSubLevelSelClass::init(cocos2d::CCObject *target, cocos2d::SEL_CallFunc selector)
{
    CCAssert(!(target == NULL), "cannot be NULL");
    CCAssert(!(selector == NULL), "cannot be NULL");
//    if (target)
//    {
//        target->retain();
//    }
//    
//    if (myTarget)
//    {
//        myTarget->release();
//    }
    
    myTarget = target;
    mySelector = selector;
    return true;
}

GameSubLevelSelClass* GameSubLevelSelClass::create(cocos2d::CCObject *target, cocos2d::SEL_CallFunc selector)
{
    GameSubLevelSelClass* sel = new GameSubLevelSelClass();
    if (sel && sel->init(target, selector)) {
        sel->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(sel);
    }
    
    return sel;
}

void GameSubLevelSelClass::onEnter()
{
    CCLayer::onEnter();
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void GameSubLevelSelClass::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
};

bool GameSubLevelSelClass::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void GameSubLevelSelClass::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    (myTarget->*mySelector)();
}