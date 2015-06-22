//
//  pthreadClass.cpp
//  Kingdom Battle
//
//  Created by jack on 13-7-1.
//
//

#include "pthreadClass.h"
USING_NS_CC;

pthreadClass::pthreadClass()
{
    myTarget = NULL;
}

pthreadClass::~pthreadClass()
{
    
}

bool pthreadClass::init(cocos2d::CCObject *target, cocos2d::SEL_CallFunc selector)
{
    CCAssert(!(target == NULL), "target cannot be NULL");
    CCAssert(!(selector == NULL), "selector cannot be NULL");

    if (target)
    {
        target->retain();
    }
    
    if (myTarget)
    {
        myTarget->release();
    }
    
    myTarget = target;
    mySelector = selector;
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int prio = sched_get_priority_max(SCHED_OTHER);
    pthread_attr_setschedpolicy(&attr, prio);
    pthread_create(&mypthread, &attr, pthreadClass::startTask, this);
    return true;
}

pthreadClass* pthreadClass::create(cocos2d::CCObject *target, cocos2d::SEL_CallFunc selector)
{
    CCAssert(!(target == NULL), "target cannot be NULL");
    CCAssert(!(selector == NULL), "selector cannot be NULL");

    pthreadClass* pthread = new pthreadClass();
    if (pthread && pthread->init(target,selector)) {
        pthread->autorelease();
    }else{
        CC_SAFE_DELETE(pthread);
    }
    return pthread;
}

//void pthreadClass::start(cocos2d::CCObject *target, cocos2d::SEL_CallFunc selector)
//{
//    CCAssert(!(target == NULL), "target cannot be NULL");
//    CCAssert(!(selector == NULL), "selector cannot be NULL");
//    myTarget = target;
//    mySelector = selector;
//    
//}

void pthreadClass::stop()
{
    //pthread_cancel(pthread_self());
}

void* pthreadClass::startTask(void *pargs)
{
    pthread_detach(pthread_self());
    pthreadClass* mypk = (pthreadClass*)pargs;
    //mypk->myTarget->*mySelector(mypk):
    mypk->doSomething();
    CCLog("hello Jack");
    return NULL;
}

void pthreadClass::doSomething()
{
    (myTarget->*mySelector)();
}

