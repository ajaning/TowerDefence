//
//  comSpriteActionClass.cpp
//  CaratonFatans
//
//  Created by  Jack on 13-11-24.
//
//

#include "comSpriteActionClass.h"
#include "LcdAdapClass.h"

comSpriteActionClass::comSpriteActionClass()
{

}

comSpriteActionClass::~comSpriteActionClass()
{

}

bool comSpriteActionClass::init(COM_ANI_TYPE type)
{
    CCAssert(!(type == COM_ANI_TYPE_NONE || type == COM_ANI_TYPE_MAX), "cannot be NULL");
    char* pFileName = NULL;
    CCSize size  = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    //PNG resource had preload while the game is really start
    switch (type) {
        case COM_ANI_TYPE_OBJECT_CLEAR_ALL:
            pFileName = "targetscleard_CN.png";
            break;
        case COM_ANI_TYPE_FINAL_ATTACKING:
            pFileName = "finalwave.png";
            break;
        default:
            break;
    }
    
    CCSprite::initWithSpriteFrameName(pFileName);
    this->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
    this->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());
    
    if (type == COM_ANI_TYPE_OBJECT_CLEAR_ALL) {
        this->setPosition(ccp(size.width / 2, -this->getContentSize().height));
        
        CCMoveBy* mby = CCMoveBy::create(1, ccp(0, size.height * 15 / 100 + this->getContentSize().height));
        CCMoveBy* wait = CCMoveBy::create(3, ccp(0, 0));
        
        this->runAction(CCSequence::create(mby,wait,CCCallFunc::create(this, callfunc_selector(comSpriteActionClass::aniActionCallBack)),NULL));
    }
    else if (type == COM_ANI_TYPE_FINAL_ATTACKING)
    {
        this->setPosition(ccp(size.width / 2, size.height / 2));
        CCScaleBy* scaleTo = CCScaleBy::create(0.5, 1.5);
        CCMoveBy* wait = CCMoveBy::create(1, ccp(0, 0));
        this->runAction(CCSequence::create(scaleTo,wait,CCCallFunc::create(this, callfunc_selector(comSpriteActionClass::aniActionCallBack)),NULL));
    }
    
    
    return true;
}

comSpriteActionClass* comSpriteActionClass::create(COM_ANI_TYPE type)
{
    comSpriteActionClass* ani = new comSpriteActionClass();
    
    if (ani && ani->init(type)) {
        ani->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ani);
    }
    
    return ani;
}

void comSpriteActionClass::aniActionCallBack()
{
    this->stopAllActions();
    this->removeFromParentAndCleanup(true);
}
