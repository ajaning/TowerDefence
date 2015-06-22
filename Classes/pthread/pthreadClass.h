//
//  pthreadClass.h
//  Kingdom Battle
//
//  Created by jack on 13-7-1.
//
//

#ifndef __Kingdom_Battle__pthreadClass__
#define __Kingdom_Battle__pthreadClass__

#include "cocos2d.h"
#include <pthread.h>

class pthreadClass:public cocos2d::CCObject
{
private:
    pthreadClass();
    ~pthreadClass();
    bool init(cocos2d::CCObject *target, cocos2d::SEL_CallFunc selector);
    static void* startTask(void *pargs);
    void doSomething(void);
public:
    static pthreadClass* create(cocos2d::CCObject *target, cocos2d::SEL_CallFunc selector);
    //void start(cocos2d::CCObject* target,cocos2d::SEL_CallFunc selector);
    void stop();
public:
    pthread_t mypthread;
    cocos2d::CCObject* myTarget;
    cocos2d::SEL_CallFunc mySelector;
};
#endif /* defined(__Kingdom_Battle__pthreadClass__) */
