//
//  CaratonProClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-11-6.
//
//

#include "CaratonProClass.h"

#define MAX_LIFE_VALUE  (10)
#define TIMER_TIME  (10)
#define MAX_ANI_NUM (3)

CaratonProClass::CaratonProClass()
{

}

CaratonProClass::~CaratonProClass()
{
    
}

bool CaratonProClass::init(CCPoint pos)
{
    char pBuffer[20] = {0};
    CCArray* aniArray = CCArray::create();
    CCSpriteFrame* frame = NULL;
//    CCSpriteFrame* caratonFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hlb10.png");
    
    this->setPosition(pos);
    totalLifeValue = MAX_LIFE_VALUE;
    curLifeValue = MAX_LIFE_VALUE;
    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Items/Items01-hd.plist");
    
    //CCSprite::initWithSpriteFrameName("hlb10.png");
    
    
    
    
    for (int i = 11; i < 19; i++) {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "hlb%d.png",i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pBuffer);
        CCAssert(!(frame == NULL), "cannot be NULL");
        aniArray->addObject(frame);
    }
    
    coldAniAction = CCAnimation::createWithSpriteFrames(aniArray, 0.05);
    coldAniAction->retain();
    
    aniArray->removeAllObjects();
    
    for (int i = 21; i < 24; i++) {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "hlb%d.png",i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pBuffer);
        CCAssert(!(frame == NULL), "cannot be NULL");
        aniArray->addObject(frame);
    }
    
    blinkAniAction = CCAnimation::createWithSpriteFrames(aniArray, 0.2);
    blinkAniAction->retain();
    
    
    aniArray->removeAllObjects();
    CCRotateBy* rb1 = CCRotateBy::create(0.4, -20);
    aniArray->addObject(rb1);
    CCActionInterval* rb1rev = rb1->reverse();
    aniArray->addObject(rb1rev);
    CCRotateBy* rb2 = CCRotateBy::create(0.2, 10);
    aniArray->addObject(rb2);
    CCActionInterval* rb2reve = rb2->reverse();
    aniArray->addObject(rb2reve);
    
    shakeAction = CCSequence::create(rb1,rb1rev,rb2,rb2reve,rb1,rb1rev,rb2,rb2reve,rb1,rb1rev,rb2,rb2reve,CCCallFuncN::create(this, callfuncN_selector(CaratonProClass::aniActionCallBack)),NULL);
    shakeAction->retain();
    
    
    caratonSprite = CCSprite::createWithSpriteFrameName("hlb10.png");
    caratonSprite->setAnchorPoint(ccp(0.4,0));
    CCSize caratonSize = caratonSprite->getContentSize();
    caratonSprite->setPosition(ccp(0, 0));
    this->addChild(caratonSprite,1);
    
    CCSprite* hlbcloud0 = CCSprite::createWithSpriteFrameName("hlb0.png");
    hlbcloud0->setPosition(ccp(0, 0));
    this->addChild(hlbcloud0,-1);
    
    
    lifeNumSprite = CCSprite::createWithSpriteFrameName("BossHP10.png");
    CCAssert(!(lifeNumSprite == NULL), "cannot be NULL");
    
    CCSize carSize = caratonSprite->getContentSize();
    CCSize lifeSize = lifeNumSprite->getContentSize();
    lifeNumSprite->setPosition(ccp(carSize.width / 2, 0));
    this->addChild(lifeNumSprite,2);
    
    this->schedule(schedule_selector(CaratonProClass::aniSelTimerCallBack), TIMER_TIME);
    
    return true;
}

CaratonProClass* CaratonProClass::create(cocos2d::CCPoint pos)
{
    CaratonProClass* cara = new CaratonProClass();
    
    if (cara && cara->init(pos)) {
        cara->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(cara);
    }
    
    return cara;
}

void CaratonProClass::setCaratonCurLifeValue(int value)
{
    char* pFileName = NULL;
    CCSpriteFrame* frame = NULL;
    char pBuffer[20] = {0};
    
    curLifeValue = value;
    
    switch (curLifeValue) {
        case 9:
            {
                pFileName = "hlb9.png";
            }
            break;
        case 8:
        case 7:
            {
                pFileName = "hlb8.png";
            }
            break;
        case 6:
        case 5:
            {
                pFileName = "hlb6.png";
            }
            break;
        case 4:
            {
                pFileName = "hlb4.png";
            }
            break;
        case 3:
            {
                pFileName = "hlb3.png";
            }
            break;
        case 2:
            {
                pFileName = "hlb2.png";
            }
            break;
        case 1:
            {
                pFileName = "hlb1.png";
            }
            break;
        default:
            break;
    }
    
    if (pFileName != NULL) {
        caratonSprite->stopAllActions();
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pFileName);
        caratonSprite->setDisplayFrame(frame);
    }
    
    if (curLifeValue > 0) {
        sprintf(pBuffer, "BossHP%02d.png",curLifeValue);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pBuffer);
        lifeNumSprite->setDisplayFrame(frame);
    }
}

int CaratonProClass::getCaratonCurLifeValue()
{
    return curLifeValue;
}

CCSize CaratonProClass::getCaratonSize()
{
    return caratonSprite->getContentSize();
}

CCPoint CaratonProClass::getCaratonPos()
{
    return caratonSprite->getPosition();
}

void CaratonProClass::stopHLBAllAction()
{
    caratonSprite->stopAllActions();
}

void CaratonProClass::userTouchCaraton()
{
    if (curLifeValue == MAX_LIFE_VALUE) {
        caratonSprite->stopAllActions();
        caratonSprite->runAction(CCSequence::create(CCAnimate::create(coldAniAction),CCCallFuncN::create(this, callfuncN_selector(CaratonProClass::aniActionCallBack)),NULL));
    }
}

void CaratonProClass::aniSelTimerCallBack(cocos2d::CCObject *object)
{
    caratonSprite->stopAllActions();
    if (curLifeValue == MAX_LIFE_VALUE) {
        
        int aniIndex = CCRANDOM_0_1() * MAX_ANI_NUM + 1;
        
        if (aniIndex > MAX_ANI_NUM) {
            aniIndex = MAX_ANI_NUM;
        }
        switch (aniIndex) {
            case 1:
                {
                    caratonSprite->runAction(CCSequence::create(CCAnimate::create(blinkAniAction),CCCallFuncN::create(this, callfuncN_selector(CaratonProClass::aniActionCallBack)),NULL));
                }
                break;
            case 2:
                {
                    caratonSprite->runAction(CCSequence::create(CCAnimate::create(coldAniAction),CCCallFuncN::create(this, callfuncN_selector(CaratonProClass::aniActionCallBack)),NULL));
                }
                break;
            case 3:
                {
                    caratonSprite->runAction(shakeAction);
                }
                break;
            default:
                break;
        }
        
        this->schedule(schedule_selector(CaratonProClass::aniSelTimerCallBack), TIMER_TIME);
    }
    else
    {
        this->unschedule(schedule_selector(CaratonProClass::aniSelTimerCallBack));
    }
}


void CaratonProClass::aniActionCallBack(cocos2d::CCObject *object)
{
    char* pFileName = NULL;
    CCSpriteFrame* frame = NULL;
    
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hlb10.png");
    if (frame == NULL) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Items/Items01-hd.plist");
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hlb10.png");
    }
    
    if (frame != NULL) {
        caratonSprite->setDisplayFrame(frame);
    }
}


bool CaratonProClass::checkCaratonIsBited(cocos2d::CCPoint enemyPos, cocos2d::CCSize enemySize)
{
    bool isBited = false;
    
    CCSize caratonSize = caratonSprite->getPosition();
    CCPoint caratonPos = this->getPosition();
    CCRect caraRec = CCRectMake(caratonPos.x - caratonSize.width / 2, caratonPos.y - caratonSize.height / 2, caratonSize.width, caratonSize.height);
    
    CCRect enemyRec = CCRectMake(enemyPos.x - enemySize.width / 2, enemyPos.y - enemySize.height / 2, enemySize.width, enemySize.height);
    
    if (caraRec.intersectsRect(enemyRec)) {
        isBited = true;
    }
    
    
    return isBited;
}




