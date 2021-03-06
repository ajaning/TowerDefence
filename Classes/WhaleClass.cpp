//
//  WhaleClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-11-13.
//
//

#include "WhaleClass.h"
#include "LcdAdapClass.h"
#include "HUDClass.h"
#include "PetsDropClass.h"

#define WHALE_TOTAL_LIFE_VALUE  (2000)
#define CUT_WHALE_ONCE_KILL_VALUE   (10)

#define WHALE_TAIL_ANI_TIME (2)
#define CUT_WAHLE_TOUCH_NUM (5)
#define CUT_WHALE_LENTH (20)

#define USER_TOUCH_MOVED_MAX_COUNTER    (2)

#define WHALE_SPEECH_SHOW_TIME  (10)

#define GAME_LEVEL_DISAPPEAR_ID （5）

typedef enum {
	WHALE_ANI_TYPE_NONE,
	WHALE_ANI_TYPE_SPEECH_CN_1,//鲸鱼台词
	WHALE_ANI_TYPE_SPEECH_CN_2,
	WHALE_ANI_TYPE_SPEECH_CN_3,
	WHALE_ANI_TYPE_SPEECH_CN_4,
	WHALE_ANI_TYPE_SPEECH_CN_5,
	WHALE_ANI_TYPE_SPEECH_CN_6,
	WHALE_ANI_TYPE_WARNNING,//警告标志
	WHALE_ANI_TYPE_BODY_ANGRY,//鲸鱼生气了
	WHALE_ANI_TYPE_BODY_BLEEDING,//身体流血了
	WHALE_ANI_TYPE_TAIL_GAUZE,//尾巴上的纱布
	WHALE_ANI_TYPE_BODY_GAUZE,//身体上的纱布
	WHALE_ANI_TYPE_EYE_PANIC_BEGIN,//开始惊恐的眼神，此为小惊恐，后面还有大的惊恐
	WHALE_ANI_TYPE_EYE_PANIC_NOW,//开始大的惊恐眼神
	WHALE_ANI_TYPE_EYE_TEAR_NOW,//鲸鱼流泪了
	WHALE_ANI_TYPE_LEFT_EYE_HURT,//左边的一只眼珠掉出来了
	WHALE_ANI_TYPE_MAX
}WHALE_ANI_TYPE;

typedef struct {
    bool isTouchStartValid;//检测起始触摸点是否在有效范围内
    bool isTouchValid;//检测触摸移动是否有效
    int movedCounter;//触摸计时
    float diffX;
    float diffy;
}userMovedStruct;

int userTouchMovedIndexArray[CUT_WAHLE_TOUCH_NUM] = {0};
userMovedStruct userTouchMovedArray[CUT_WAHLE_TOUCH_NUM] = {{false,false,0,0,0}};

WhaleClass::WhaleClass()
{

}

WhaleClass::~WhaleClass()
{
    if (userTouch1Array->count() > 0) {
        userTouch1Array->removeAllObjects();
        userTouch1Array->release();
    }
    
    if (userTouch2Array->count() > 0) {
        userTouch2Array->removeAllObjects();
        userTouch2Array->release();
    }
    
    if (userTouch3Array->count() > 0) {
        userTouch3Array->removeAllObjects();
        userTouch3Array->release();
    }
    
    if (userTouch4Array->count() > 0) {
        userTouch4Array->removeAllObjects();
        userTouch4Array->release();
    }
    
    if (userTouch5Array->count() > 0) {
        userTouch5Array->removeAllObjects();
        userTouch5Array->release();
    }
    
}

bool WhaleClass::init()
{
    ccColor4B color;
    char buffer[100] = {0};
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    CCSpriteFrame * frame = NULL;
    CCArray* aniArray = CCArray::create();
    
    userTouch1Array = CCArray::create();
    userTouch1Array->retain();
    
    userTouch2Array = CCArray::create();
    userTouch2Array->retain();
    
    userTouch3Array = CCArray::create();
    userTouch3Array->retain();
    
    userTouch4Array = CCArray::create();
    userTouch4Array->retain();
    
    userTouch5Array = CCArray::create();
    userTouch5Array->retain();
    
    memset(userTouchMovedArray, 0, sizeof(userTouchMovedArray));
    
    
    userTouchNum = 0;
    userTouchMovedCounter = 0;
    isUpdateTimerStart = false;
    isWhaleSpeechShow = false;
    whaleSpeechId = 0;
    whaleCurLifeValue = WHALE_TOTAL_LIFE_VALUE;
    whaleTotalLifeValue = WHALE_TOTAL_LIFE_VALUE;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Items/Items11-hd.plist");
    
    
    //whale body
    whaleBody = CCSprite::createWithSpriteFrameName("Whale11.png");
    whaleBody->getTexture()->setAliasTexParameters();
    CCSize whaleSize = whaleBody->getContentSize();
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(whaleBody, ccp(size.width + whaleSize.width / 2, -whaleSize.height / 2));
    this->addChild(whaleBody,1);
    
    //whale tail
    whaleTail = CCSprite::createWithSpriteFrameName("Whale12.png");
    whaleTail->getTexture()->setAliasTexParameters();
    whaleTail->setPosition(ccp(whaleSize.width / 2 , whaleSize.height / 2));
    aniArray->removeAllObjects();
    for (int i = 12; i < 14; i++) {
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "Whale%d.png",i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
//        CCAssert(!(frame), "cannot be NULL");
        aniArray->addObject(frame);
    }
    CCAnimation* tailAni = CCAnimation::createWithSpriteFrames(aniArray,WHALE_TAIL_ANI_TIME);
    whaleTail->runAction(CCRepeatForever::create(CCAnimate::create(tailAni)));
    whaleBody->addChild(whaleTail,2);
    
    
    //whale eye
    whaleEye = CCSprite::createWithSpriteFrameName("Whale21.png");
    whaleEye->getTexture()->setAliasTexParameters();
    whaleEye->setPosition(ccp(whaleSize.width / 2 , whaleSize.height / 2));
    aniArray->removeAllObjects();
    for (int i = 21; i < 23; i++) {
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "Whale%d.png",i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
        //        CCAssert(!(frame), "cannot be NULL");
        aniArray->addObject(frame);
    }
    CCAnimation* eyeAni = CCAnimation::createWithSpriteFrames(aniArray,1);
    whaleEye->runAction(CCRepeatForever::create(CCAnimate::create(eyeAni)));
    whaleBody->addChild(whaleEye,3);
    
    //whale spray
    whaleSpray = CCSprite::createWithSpriteFrameName("Whale01.png");
    whaleSpray->getTexture()->setAliasTexParameters();
    whaleSpray->setPosition(ccp(whaleSize.width / 2 , whaleSize.height * 60 / 100));
    aniArray->removeAllObjects();
    for (int i = 1; i < 5; i++) {
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "Whale%02d.png",i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
        //        CCAssert(!(frame), "cannot be NULL");
        aniArray->addObject(frame);
    }
    CCAnimation* sprayAni = CCAnimation::createWithSpriteFrames(aniArray,0.8);
    whaleSpray->runAction(CCRepeatForever::create(CCAnimate::create(sprayAni)));
    whaleBody->addChild(whaleSpray,4);
    
    whaleSpeechBG = NULL;
    whaleAngry = NULL;
    whaleBodyGauze = NULL;
    whaleTailGauze = NULL;
    whaleWarnning = NULL;
    whaleBleeding = NULL;
    whaleEyePanicBegin = NULL;
    whaleEyePanicNow = NULL;
    whaleEyeTear = NULL;
    whaleleftEyeHurt = NULL;
    
    whaleBlood1 = NULL;
    whaleBlood2 = NULL;
    
    this->whaleMovePathAni();
    return true;
}

WhaleClass* WhaleClass::create()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    WhaleClass* whale = new WhaleClass();
    if (whale && whale->init()) {
        whale->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(whale);
    }
    
    whale->setContentSize(size);
    return whale;
}

bool WhaleClass::init(cocos2d::CCObject *target, SEL_CallFunc func)
{
    CCAssert(!(target == NULL), "cannot be NULL");
    CCAssert(!(func == NULL), "cannot be NULL");
    
    myTarget = target;
    myFunc = func;
    
    this->init();
    return true;
}

WhaleClass* WhaleClass::create(cocos2d::CCObject *target, SEL_CallFunc func)
{
    WhaleClass* whale = new WhaleClass();
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    if (whale && whale->init(target, func)) {
        whale->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(whale);
    }
    
    whale->setContentSize(size);
    return whale;
}

void WhaleClass::getGameCurLevelAndTotalLevel(int curLevel, int totalLevel)
{
    char buffer[20] = {0};
    
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    CCSprite* menuCenterBG = CCSprite::createWithSpriteFrameName("MenuCenter_01_CN.png");
    CCAssert(!(menuCenterBG == NULL), "cannot be NULL");
    menuCenterBG->setPosition(ccp((size.width) / 2, (size.height * 94) / 100));
    this->addChild(menuCenterBG);
    
    menuCenterBG->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
    menuCenterBG->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());
    
    CCSize menuCenterBGSize = menuCenterBG->getContentSize();
    
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%02d",curLevel);
    CCLabelAtlas* curLevelLab = CCLabelAtlas::create(buffer, "Themes/Items/numyellow.png", 26, 24, 46);
    CCAssert(!(curLevelLab == NULL), "cannot be NULL");
    curLevelLab->setPosition(ccp(menuCenterBGSize.width * 10/ 100, menuCenterBGSize.height * 40 / 100));
    menuCenterBG->addChild(curLevelLab,2);
    
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%02d",totalLevel);
    CCLabelAtlas* totalLevelLab = CCLabelAtlas::create(buffer, "Themes/Items/numwhite.png", 13, 26, 46);
    CCAssert(!(totalLevelLab == NULL), "cannot be NULL");
    totalLevelLab->setPosition(ccp(menuCenterBGSize.width * 45 / 100, menuCenterBGSize.height * 40 /100));
    menuCenterBG->addChild(totalLevelLab,1);
    
    CCRotateBy* rby = CCRotateBy::create(1, 10);
    CCMoveBy* mby = CCMoveBy::create(1, ccp(0, -menuCenterBGSize.height * 2));
    CCFadeOut* fout = CCFadeOut::create(2);
    
    menuCenterBG->runAction(CCSequence::create(rby,mby,fout,CCCallFuncN::create(this, callfuncN_selector(WhaleClass::gameLevelHideActCallBack)),NULL));
    
}


void WhaleClass::gameLevelHideActCallBack(cocos2d::CCNode *node)
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    CCSprite* sprite = (CCSprite*)node;
    
    sprite->removeFromParentAndCleanup(true);
    
    whaleBlood1 = CCSprite::createWithSpriteFrameName("menublood_01.png");
    whaleBlood1->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
    whaleBlood1->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());
    CCSize blood1Size = whaleBlood1->getContentSize();
    whaleBlood1->setPosition(ccp(size.width  * 40/ 100, size.height + blood1Size.height));
    this->addChild(whaleBlood1,1000);
    
    
    whaleBlood2 = CCSprite::createWithSpriteFrameName("menublood_02.png");
    whaleBlood2->setPosition(ccp(blood1Size.width * 79 / 100, blood1Size.height / 2));
    whaleBlood1->addChild(whaleBlood2,900);
    whaleBlood2->setScaleX(0);
    
    CCMoveTo* mto = CCMoveTo::create(2, ccp(size.width / 2, size.height * 94 / 100));
    CCEaseBounceOut* bout = CCEaseBounceOut::create(mto);
    
    whaleBlood1->runAction(bout);
    
}

void WhaleClass::whaleMovePathAni()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    CCSize whaleSize = CCSize(whaleBody->getContentSize().width * LcdAdapClass::sharedLCDADAP()->getXScale(), whaleBody->getContentSize().height * LcdAdapClass::sharedLCDADAP()->getYScale());
    CCPoint startPos = ccp(size.width + whaleSize.width / 2, -whaleSize.height / 2);
    
    CCPoint totarget1 = ccp((size.width * 73)/ 100,size.height / 2);
    CCPoint totarget2 = ccp(size.width * 40/ 100,size.height / 2);
    CCPoint totarget3 = ccp(-size.width * 8/100.0,-size.height * 10 / 100.0);

    CCMoveBy* wait = CCMoveBy::create(15, ccp(0, 0));
    
    
    
    CCMoveTo* startMove = CCMoveTo::create(20, totarget1);
    CCMoveTo* moveTG2 = CCMoveTo::create(15, totarget2);
    CCMoveBy* moveWait = CCMoveBy::create(60, ccp(0,0));
    CCMoveTo* moveEnd = CCMoveTo::create(10, totarget3);
    CCCallFunc* func1 = CCCallFunc::create(this, callfunc_selector(WhaleClass::whaleMovePathAniTarget1CallBack));
    CCCallFunc* func2 = CCCallFunc::create(this, callfunc_selector(WhaleClass::whaleMovePathAniTarget2CallBack));
    CCCallFunc* func3 = CCCallFunc::create(this, callfunc_selector(WhaleClass::whaleMovePathAniTarget3CallBack));
    
    whaleBody->setPosition(startPos);
    
    whaleBody->runAction(CCSequence::create(startMove,func1,wait,moveTG2,func2,wait,moveWait,moveEnd,func3,NULL));
}

void WhaleClass::whaleMovePathAniTarget1CallBack()
{
    //first
    
    updateWhaleAniShowByID(WHALE_ANI_TYPE_SPEECH_CN_1, true);
    this->setWhaleSpeechShowID(WHALE_ANI_TYPE_SPEECH_CN_1);
}

void WhaleClass::whaleMovePathAniTarget2CallBack()
{
    updateWhaleAniShowByID(WHALE_ANI_TYPE_SPEECH_CN_2, true);
    this->setWhaleSpeechShowID(WHALE_ANI_TYPE_SPEECH_CN_2);
}

void WhaleClass::whaleMovePathAniTarget3CallBack()
{
    (myTarget->*myFunc)();
    
    this->removeFromParentAndCleanup(true);
}

void WhaleClass::checkWhaleWhichSpeechShowWhileByTouched()
{
    if (!isWhaleSpeechShow) {
        int value = this->getCurLifeValue();
        
        if (value > (whaleTotalLifeValue * 5 / 6)) {
            this->setWhaleSpeechShowID(WHALE_ANI_TYPE_SPEECH_CN_2);
        }
        else if (value > (whaleTotalLifeValue * 4 / 6) && value < (whaleTotalLifeValue * 5 / 6)){
            
            this->setWhaleSpeechShowID(WHALE_ANI_TYPE_SPEECH_CN_3);
        }
        else if (value > (whaleTotalLifeValue * 3 / 6 ) && value < (whaleTotalLifeValue * 4 / 6)){
            this->setWhaleSpeechShowID(WHALE_ANI_TYPE_SPEECH_CN_4);
        }
        else if (value > (whaleTotalLifeValue * 2 / 6) && value < (whaleTotalLifeValue * 4 / 6)){
            this->setWhaleSpeechShowID(WHALE_ANI_TYPE_SPEECH_CN_5);
        }
        else if (value < (whaleTotalLifeValue * 1 / 6)){
            this->setWhaleSpeechShowID(WHALE_ANI_TYPE_SPEECH_CN_6);
        }
    }
    
}


void WhaleClass::setWhaleSpeechShowID(int index)
{
    isWhaleSpeechShow = true;
    whaleSpeechId = index;
    this->schedule(schedule_selector(WhaleClass::whaleSpeechShowOrNotCallBack), WHALE_SPEECH_SHOW_TIME);
}

void WhaleClass::whaleSpeechShowOrNotCallBack(float del)
{
    isWhaleSpeechShow = false;
    updateWhaleAniShowByID(whaleSpeechId, false);
    this->unschedule(schedule_selector(WhaleClass::whaleSpeechShowOrNotCallBack));
}


void WhaleClass::updateWhaleAniShowByID(int aniId,bool isShow)
{
    WHALE_ANI_TYPE type = (WHALE_ANI_TYPE)aniId;
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    CCSize whaleSize = whaleBody->getContentSize();
    
    
    CCAssert(!(type == WHALE_ANI_TYPE_NONE || type == WHALE_ANI_TYPE_MAX), "cannot be INVALID");
    
    switch (aniId) {
        case WHALE_ANI_TYPE_SPEECH_CN_1:
        case WHALE_ANI_TYPE_SPEECH_CN_2:
        case WHALE_ANI_TYPE_SPEECH_CN_3:
        case WHALE_ANI_TYPE_SPEECH_CN_4:
        case WHALE_ANI_TYPE_SPEECH_CN_5:
        case WHALE_ANI_TYPE_SPEECH_CN_6:
            {
                char* pFileName = NULL;
                
                if (whaleSpeechBG == NULL) {
                    //whale speech bg
                    whaleSpeechBG = CCSprite::createWithSpriteFrameName("whalespeech_bg.png");
                    whaleSpeechBG->setPosition(ccp((whaleSize.width * 68/ 100), (whaleSize.height * 90 / 100)));
                    whaleBody->addChild(whaleSpeechBG,5);
                }
                
                CCSize speechBGSize = whaleSpeechBG->getContentSize();
                
                whaleSpeechBG->removeAllChildren();
                
                switch (aniId) {
                    case WHALE_ANI_TYPE_SPEECH_CN_1:
                        pFileName = "whalespeech_1_CN.png";
                        break;
                    case WHALE_ANI_TYPE_SPEECH_CN_2:
                        pFileName = "whalespeech_2_CN.png";
                        break;
                    case WHALE_ANI_TYPE_SPEECH_CN_3:
                        pFileName = "whalespeech_3_CN.png";
                        break;
                    case WHALE_ANI_TYPE_SPEECH_CN_4:
                        pFileName = "whalespeech_4_CN.png";
                        break;
                    case WHALE_ANI_TYPE_SPEECH_CN_5:
                        pFileName = "whalespeech_5_CN.png";
                        break;
                    case WHALE_ANI_TYPE_SPEECH_CN_6:
                        pFileName = "whalespeech_6_CN.png";
                        break;
                    default:
                        break;
                }
                CCSprite* speech = CCSprite::createWithSpriteFrameName(pFileName);
                speech->setPosition(ccp(speechBGSize.width/2,speechBGSize.height / 2));
                whaleSpeechBG->addChild(speech);
                whaleSpeechBG->setVisible(isShow);
            }
            break;
        case WHALE_ANI_TYPE_WARNNING:
            {
//                if (whaleWarnning == NULL) {
//                    
//                    char* pFileName = NULL;
//                    CCSpriteFrame* frame = NULL;
//                    CCArray* aniArray = CCArray::create();
//                    char pBuffer[20] = {0};
//                    
//                    
//                    whaleWarnning = CCSprite::createWithSpriteFrameName("warning_1.png");
//                    whaleWarnning->setPosition(ccp(-whaleSize.width / 2, 0));
//                    whaleNode->addChild(whaleWarnning,6);
//                    
//                    aniArray->removeAllObjects();
//                    for (int i = 1; i < 3; i++) {
//                        memset(pBuffer, 0, sizeof(pBuffer));
//                        sprintf(pBuffer, "warning_%d.png",i);
//                        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pBuffer);
//                        aniArray->addObject(frame);
//                    }
//                    CCAnimation* ani = CCAnimation::createWithSpriteFrames(aniArray, 0.5);
//                    whaleWarnning->runAction(CCRepeatForever::create(CCAnimate::create(ani)));
//                }
//                
//                whaleWarnning->setVisible(isShow);
            }
            break;
        case WHALE_ANI_TYPE_BODY_ANGRY:
            {
                if (whaleAngry == NULL) {
                    
                    CCSpriteFrame* frame = NULL;
                    CCArray* aniArray = CCArray::create();
                    char pBuffer[20] = {0};
                    
                    whaleAngry = CCSprite::createWithSpriteFrameName("Whale41.png");
                    whaleAngry->setPosition(ccp((whaleSize.width * 50/ 100), (whaleSize.height * 50 / 100)));
                    whaleBody->addChild(whaleAngry,7);
                    
                    aniArray->removeAllObjects();
                    for (int i = 41; i < 43; i++) {
                        memset(pBuffer, 0, sizeof(pBuffer));
                        sprintf(pBuffer, "Whale%d.png",i);
                        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pBuffer);
                        aniArray->addObject(frame);
                    }
                    CCAnimation* ani = CCAnimation::createWithSpriteFrames(aniArray, 0.5);
                    whaleAngry->runAction(CCRepeatForever::create(CCAnimate::create(ani)));
                }
                whaleAngry->setVisible(isShow);
            }
            break;
        case WHALE_ANI_TYPE_BODY_BLEEDING:
            {
                if (whaleBleeding == NULL) {
                    whaleBleeding = CCSprite::createWithSpriteFrameName("Whale51.png");
                    whaleBleeding->setPosition(ccp((whaleSize.width * 50/ 100), (whaleSize.height * 50 / 100)));
                    whaleBody->addChild(whaleBleeding,8);
                }
                whaleBleeding->setVisible(isShow);
            }
            break;
        case WHALE_ANI_TYPE_TAIL_GAUZE:
            {
                if (whaleTailGauze == NULL) {
                    
                    CCSpriteFrame* frame = NULL;
                    CCArray* aniArray = CCArray::create();
                    char pBuffer[20] = {0};
                    
                    whaleTailGauze = CCSprite::createWithSpriteFrameName("Whale61.png");
                    whaleTailGauze->setPosition(ccp((whaleSize.width * 50/ 100), (whaleSize.height * 50 / 100)));
                    whaleBody->addChild(whaleTailGauze,8);
                    
                    aniArray->removeAllObjects();
                    for (int i = 61; i < 63; i++) {
                        memset(pBuffer, 0, sizeof(pBuffer));
                        sprintf(pBuffer, "Whale%d.png",i);
                        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pBuffer);
                        aniArray->addObject(frame);
                    }
                    CCAnimation* ani = CCAnimation::createWithSpriteFrames(aniArray, WHALE_TAIL_ANI_TIME);
                    whaleTailGauze->runAction(CCRepeatForever::create(CCAnimate::create(ani)));
                }
                whaleTailGauze->setVisible(isShow);
            }
            break;
        case WHALE_ANI_TYPE_BODY_GAUZE:
            {
                if (whaleBodyGauze == NULL) {
                    whaleBodyGauze = CCSprite::createWithSpriteFrameName("Whale71.png");
                    whaleBodyGauze->setPosition(ccp((whaleSize.width * 50/ 100), (whaleSize.height * 50 / 100)));
                    whaleBody->addChild(whaleBodyGauze,9);
                }
                whaleBodyGauze->setVisible(isShow);
            }
            break;
        case WHALE_ANI_TYPE_EYE_PANIC_BEGIN:
            {
                if (whaleEyePanicBegin == NULL) {
                    whaleEyePanicBegin = CCSprite::createWithSpriteFrameName("Whale31.png");
                    whaleEyePanicBegin->setPosition(ccp((whaleSize.width * 50/ 100), (whaleSize.height * 50 / 100)));
                    whaleBody->addChild(whaleEyePanicBegin,10);
                }
                whaleEyePanicBegin->setVisible(isShow);
            }
            break;
        case WHALE_ANI_TYPE_EYE_PANIC_NOW:
            {
                if (whaleEyePanicNow == NULL) {
                    
                    CCSpriteFrame* frame = NULL;
                    CCArray* aniArray = CCArray::create();
                    char pBuffer[20] = {0};
                    
                    whaleEyePanicNow = CCSprite::createWithSpriteFrameName("Whale-11.png");
                    whaleEyePanicNow->setPosition(ccp((whaleSize.width * 50/ 100), (whaleSize.height * 50 / 100)));
                    whaleBody->addChild(whaleEyePanicNow,11);
                    
                    aniArray->removeAllObjects();
                    for (int i = 11; i < 13; i++) {
                        memset(pBuffer, 0, sizeof(pBuffer));
                        sprintf(pBuffer, "Whale-%d.png",i);
                        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pBuffer);
                        aniArray->addObject(frame);
                    }
                    CCAnimation* ani = CCAnimation::createWithSpriteFrames(aniArray, 2);
                    whaleEyePanicNow->runAction(CCRepeatForever::create(CCAnimate::create(ani)));

                }
                whaleEyePanicNow->setVisible(isShow);
            }
            break;
        case WHALE_ANI_TYPE_EYE_TEAR_NOW:
            {
                if (whaleEyeTear == NULL) {
                    
                    CCSpriteFrame* frame = NULL;
                    CCArray* aniArray = CCArray::create();
                    char pBuffer[20] = {0};
                    
                    whaleEyeTear = CCSprite::createWithSpriteFrameName("Whale-21.png");
                    whaleEyeTear->setPosition(ccp((whaleSize.width * 50/ 100), (whaleSize.height * 50 / 100)));
                    whaleBody->addChild(whaleEyeTear,12);
                    
                    aniArray->removeAllObjects();
                    for (int i = 21; i < 24; i++) {
                        memset(pBuffer, 0, sizeof(pBuffer));
                        sprintf(pBuffer, "Whale-%d.png",i);
                        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pBuffer);
                        aniArray->addObject(frame);
                    }
                    CCAnimation* ani = CCAnimation::createWithSpriteFrames(aniArray, 2);
                    whaleEyeTear->runAction(CCRepeatForever::create(CCAnimate::create(ani)));

                }
                whaleEyeTear->setVisible(isShow);
            }
            break;
        case WHALE_ANI_TYPE_LEFT_EYE_HURT:
            {
                if (whaleleftEyeHurt == NULL) {
                    whaleleftEyeHurt = CCSprite::createWithSpriteFrameName("Whale81.png");
                    whaleleftEyeHurt->setPosition(ccp((whaleSize.width * 50/ 100), (whaleSize.height * 50 / 100)));
                    whaleBody->addChild(whaleleftEyeHurt,13);
                }
                whaleleftEyeHurt->setVisible(isShow);
            }
            break;
        default:
            break;
    }
    
}

//void WhaleClass::registerWithTouchDispatcher()
//{
//    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
//}

void WhaleClass::onEnter()
{
    CCLayer::onEnter();
    this->setTouchEnabled(true);
    //CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void WhaleClass::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
    
}

void WhaleClass::updateWhaleLifeValue(int value)
{
    CCSize bloodBGSize = whaleBlood1->getContentSize();
    CCSize blood2Size =  whaleBlood2->getContentSize();
    float validWidth = 0;
    float bloodBGValidWidth = 342;//血量实际长度，BLOODBGSize是整个长度，包含透明部分
    float validBloodBGWidth = 350;//修正长度
    whaleCurLifeValue = value;
    
    validWidth = validBloodBGWidth - (bloodBGValidWidth * whaleCurLifeValue / whaleTotalLifeValue);
    
    whaleBlood2->setPosition(ccp(((bloodBGValidWidth * whaleCurLifeValue / whaleTotalLifeValue) + validWidth / 2), bloodBGSize.height / 2));
    whaleBlood2->setScaleX(validWidth/blood2Size.width);
    
    
    if (value > (whaleTotalLifeValue * 5 / 6)) {
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_BODY_ANGRY, true);
    }
    else if (value > (whaleTotalLifeValue * 4 / 6) && value < (whaleTotalLifeValue * 5 / 6)){
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_EYE_PANIC_BEGIN, true);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_BODY_ANGRY, false);
        
    }
    else if (value > (whaleTotalLifeValue * 3 / 6 ) && value < (whaleTotalLifeValue * 4 / 6)){
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_EYE_PANIC_NOW, true);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_BODY_BLEEDING, true);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_EYE_PANIC_BEGIN, false);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_BODY_ANGRY, false);
    }
    else if (value > (whaleTotalLifeValue * 2 / 6) && value < (whaleTotalLifeValue * 4 / 6)){
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_EYE_PANIC_NOW, true);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_BODY_BLEEDING, true);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_EYE_TEAR_NOW, true);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_TAIL_GAUZE, true);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_EYE_PANIC_BEGIN, false);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_BODY_ANGRY, false);
    }
    else if (value < (whaleTotalLifeValue * 1 / 6)){
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_LEFT_EYE_HURT, true);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_BODY_BLEEDING, true);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_TAIL_GAUZE, true);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_BODY_GAUZE, true);
        
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_EYE_PANIC_NOW, false);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_EYE_TEAR_NOW, false);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_EYE_PANIC_NOW, false);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_EYE_PANIC_BEGIN, false);
        this->updateWhaleAniShowByID(WHALE_ANI_TYPE_BODY_ANGRY, false);
    }
    
}

void WhaleClass::cutWhaleAniStart(cocos2d::CCPoint beginPos, cocos2d::CCPoint lastPos)
{
    float subLen = ccpLength(ccpSub(beginPos, lastPos));
    CCArray* aniArray = CCArray::create();
    
    
    if (subLen > CUT_WHALE_LENTH) {
        
        
        
        CCPoint cutPos = ccp((beginPos.x + lastPos.x) / 2, (beginPos.y + lastPos.y) / 2);
        float rotate = 0;
        
        if (beginPos.x == lastPos.x) {
            rotate = 90;
        }
        else if (beginPos.y == lastPos.y){
            rotate = 0;
        }
        else{
            
            float o = beginPos.x - lastPos.x;
            float a = beginPos.y - lastPos.y ;
            rotate = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );
            
            if( a < 0 )
            {
                if(  o < 0 )
                    rotate = 180 + fabs(rotate);
                else
                    rotate = 180 - fabs(rotate);
            }
        }
        
        CCSprite* cut = CCSprite::createWithSpriteFrameName("CutWhale.png");
        float maxValue = MAX(cut->getContentSize().width, cut->getContentSize().height);
        float validScale = subLen / maxValue;
        cut->setPosition(cutPos);
        cut->setScaleY(validScale);
        this->addChild(cut,10);
        cut->setRotation(rotate);
        
        aniArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("CutWhale.png"));
        
        CCAnimation* cutAni = CCAnimation::createWithSpriteFrames(aniArray,0.05);
        cut->runAction((CCActionInterval*)CCSequence::create(CCAnimate::create(cutAni),CCCallFuncN::create(this, callfuncN_selector(WhaleClass::cutWhaleAniCallBack)),NULL));
    }
}

bool WhaleClass::checkUserPointInWhaliBody(cocos2d::CCPoint curPoint)
{
    bool isValid = false;
    
    CCPoint whalePos = whaleBody->getPosition();
    CCSize whaleSize = whaleBody->getContentSize();
    CCRect whaleRect = CCRect(whalePos.x - whaleSize.width / 2, whalePos.y - whaleSize.height / 2, whaleSize.width, whaleSize.height / 2);
    
    if (whaleRect.containsPoint(curPoint)) {
        isValid = true;
    }
    
    return isValid;
}

int  WhaleClass::getCurLifeValue()
{
    return whaleCurLifeValue;
}

int WhaleClass::getTotalLifeValue()
{
    return whaleTotalLifeValue;
}


void WhaleClass::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCPoint whalePos = whaleBody->getPosition();
    CCSize whaleSize = CCSize(whaleBody->getContentSize().width * LcdAdapClass::sharedLCDADAP()->getXScale(), whaleBody->getContentSize().height * LcdAdapClass::sharedLCDADAP()->getYScale());
    CCRect whaleRect = CCRect(whalePos.x - whaleSize.width / 2, whalePos.y - whaleSize.height /2, whaleSize.width, whaleSize.height);
    
    CCSetIterator iter = pTouches->begin();
    int count = pTouches->count();
    
    if (count > CUT_WAHLE_TOUCH_NUM) {
        count = CUT_WAHLE_TOUCH_NUM;
    }
    userTouchNum = count;

    if (!isUpdateTimerStart) {
        isUpdateTimerStart = true;
        this->unscheduleUpdate();
        this->scheduleUpdate();
    }
    
    CCLog("touch num = %d",count);
    
    for (; iter != pTouches->end(); iter++) {
        CCTouch *mytouch = (CCTouch*)(*iter);
        
//        CCPoint prePoint = CCDirector::sharedDirector()->convertToGL(mytouch->getPreviousLocation());
//        CCPoint curPoint = CCDirector::sharedDirector()->convertToGL(mytouch->getLocationInView());
        CCPoint prePoint = this->convertToNodeSpace(mytouch->getLocation());
        CCPoint curPoint = this->convertToNodeSpace(mytouch->getPreviousLocation());
        
        CCNode* beginNode = CCNode::create();
        beginNode->setPosition(curPoint);
        
        CCNode* curNode = CCNode::create();
        curNode->setPosition(curPoint);
        
        CCNode* preNode = CCNode::create();
        preNode->setPosition(curPoint);
        
        CCNode* diffNode = CCNode::create();
        diffNode->setPosition(CCPointZero);
        
        if (mytouch->getID() == 0) {
            
            if (whaleRect.containsPoint(curPoint)) {
                userTouch1Array->removeAllObjects();
                userTouch1Array->insertObject(beginNode,0);
                userTouch1Array->insertObject(curNode, 1);
                userTouch1Array->insertObject(preNode, 2);
                userTouch1Array->insertObject(diffNode, 3);
                userTouchMovedArray[mytouch->getID()].isTouchStartValid = true;
            }
        }
        else if (mytouch->getID() == 1)
        {
            if (whaleRect.containsPoint(curPoint)) {
                userTouch2Array->removeAllObjects();
                userTouch2Array->insertObject(beginNode,0);
                userTouch2Array->insertObject(curNode, 1);
                userTouch2Array->insertObject(preNode, 2);
                userTouch2Array->insertObject(diffNode, 3);
                userTouchMovedArray[mytouch->getID()].isTouchStartValid = true;
            }
        }
        
    }
}

void WhaleClass::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCPoint whalePos = whaleBody->getPosition();
    CCSize whaleSize = CCSize(whaleBody->getContentSize().width * LcdAdapClass::sharedLCDADAP()->getXScale(), whaleBody->getContentSize().height * LcdAdapClass::sharedLCDADAP()->getYScale());
    CCRect whaleRect = CCRect(whalePos.x - whaleSize.width / 2, whalePos.y - whaleSize.height /2, whaleSize.width, whaleSize.height);
    
    CCSetIterator iter = pTouches->begin();
    int count = pTouches->count();
    
    if (count > CUT_WAHLE_TOUCH_NUM) {
        count = CUT_WAHLE_TOUCH_NUM;
    }
    userTouchNum = count;
    
    CCLog("touch num = %d",count);
    
    for (; iter != pTouches->end(); iter++) {

        bool isDirChanged = false;//检测手势的方向是否改变
        CCPoint subPos = CCPointZero;
        CCPoint beginPos = CCPointZero;
        CCNode* preNode = NULL;
        CCNode* beginNode = NULL;
        CCNode* curNode = NULL;
        CCNode* diffNode = NULL;
        CCTouch *mytouch = (CCTouch*)(*iter);
        
//        CCPoint startPoint = CCDirector::sharedDirector()->convertToGL(mytouch->getStartLocationInView());
//        CCPoint prePoint = CCDirector::sharedDirector()->convertToGL(mytouch->getPreviousLocationInView());
//        CCPoint curPoint = CCDirector::sharedDirector()->convertToGL(mytouch->getLocationInView());
        
        CCPoint prePoint = this->convertToNodeSpace(mytouch->getLocation());
        CCPoint curPoint = this->convertToNodeSpace(mytouch->getPreviousLocation());
        
        if (whaleRect.containsPoint(curPoint) && userTouchMovedArray[mytouch->getID()].isTouchStartValid) {
            if (mytouch->getID() == 0) {
                
                curNode = (CCNode*)userTouch1Array->objectAtIndex(1);
                preNode = (CCNode*)userTouch1Array->objectAtIndex(2);
                beginNode = (CCNode*)userTouch1Array->objectAtIndex(0);
                diffNode = (CCNode*)userTouch1Array->objectAtIndex(3);
            }
            else if (mytouch->getID() == 1)
            {
                curNode = (CCNode*)userTouch2Array->objectAtIndex(1);
                preNode = (CCNode*)userTouch2Array->objectAtIndex(2);
                beginNode = (CCNode*)userTouch2Array->objectAtIndex(0);
                diffNode = (CCNode*)userTouch2Array->objectAtIndex(3);
            }
            
            subPos = ccpSub(curPoint, prePoint);
            userTouchMovedArray[mytouch->getID()].movedCounter = 0;
            
            if (userTouchMovedArray[mytouch->getID()].diffX == 0 && userTouchMovedArray[mytouch->getID()].diffy == 0) { //means first
                diffNode->setPosition(subPos);
                userTouchMovedArray[mytouch->getID()].diffX = subPos.x;
                userTouchMovedArray[mytouch->getID()].diffy = subPos.y;
            }
            
            {
                CCPoint diffPos = diffNode->getPosition();
                
                if (diffPos.x > 0.0000001 && subPos.x > 0.0000001) {
                    isDirChanged = false;
                }
                else if (diffPos.x < -0.0000001 && subPos.x < -0.0000001){
                    isDirChanged = false;
                }
                else
                {
                    isDirChanged = true;
                }
                
                if (!isDirChanged) {
                    if (diffPos.y < -0.0000001 && subPos.y < -0.0000001) {
                        isDirChanged = false;
                    }
                    else if (diffPos.y > 0.0000001 && subPos.y > 0.0000001){
                        isDirChanged = false;
                    }
                    else
                    {
                        isDirChanged = true;
                    }
                }
                beginPos = beginNode->getPosition();
                if (isDirChanged) {
                    userTouchMovedArray[mytouch->getID()].isTouchValid = false;
                    this->cutWhaleAniStart(beginPos, prePoint);
                    
                    beginNode->setPosition(curPoint);
                    preNode->setPosition(curPoint);
                    diffNode->setPosition(CCPointZero);
                    userTouchMovedArray[mytouch->getID()].diffX = 0;
                    userTouchMovedArray[mytouch->getID()].diffy = 0;
                }
                else
                {
                    userTouchMovedArray[mytouch->getID()].isTouchValid = true;
                    preNode->setPosition(curNode->getPosition());
                }
                
                
                
                curNode->setPosition(curPoint);
            }
            
        }
        else if (whaleRect.containsPoint(curPoint))
        {
            beginNode = CCNode::create();
            curNode = CCNode::create();
            preNode = CCNode::create();
            diffNode = CCNode::create();
            
            beginNode->setPosition(curPoint);
            curNode->setPosition(curPoint);
            preNode->setPosition(curPoint);
            diffNode->setPosition(CCPointZero);
            
            if (mytouch->getID() == 0) {
                
                if (whaleRect.containsPoint(curPoint)) {
                    userTouch1Array->removeAllObjects();
                    userTouch1Array->insertObject(beginNode,0);
                    userTouch1Array->insertObject(curNode, 1);
                    userTouch1Array->insertObject(preNode, 2);
                    userTouch1Array->insertObject(diffNode, 3);
                    userTouchMovedArray[mytouch->getID()].isTouchStartValid = true;
                }
            }
            else if (mytouch->getID() == 1)
            {
                if (whaleRect.containsPoint(curPoint)) {
                    userTouch2Array->removeAllObjects();
                    userTouch2Array->insertObject(beginNode,0);
                    userTouch2Array->insertObject(curNode, 1);
                    userTouch2Array->insertObject(preNode, 2);
                    userTouch2Array->insertObject(diffNode, 3);
                    userTouchMovedArray[mytouch->getID()].isTouchStartValid = true;
                }
            }
        }
        else if (userTouchMovedArray[mytouch->getID()].isTouchStartValid)
        {
//            userTouchMovedArray[mytouch->getID()].movedCounter = 0;
//            userTouchMovedArray[mytouch->getID()].isTouchValid = false;
//            userTouchMovedArray[mytouch->getID()].isTouchStartValid = false;
            memset(&userTouchMovedArray[mytouch->getID()], 0, sizeof(userMovedStruct));
            
            if (mytouch->getID() == 0) {
                
                curNode = (CCNode*)userTouch1Array->objectAtIndex(1);
                beginNode = (CCNode*)userTouch1Array->objectAtIndex(0);
                beginPos = beginNode->getPosition();
                prePoint = curNode->getPosition();
                
                this->cutWhaleAniStart(beginPos, prePoint);
                userTouch1Array->removeAllObjects();
            }
            else if (mytouch->getID() == 1)
            {
                curNode = (CCNode*)userTouch2Array->objectAtIndex(1);
                beginNode = (CCNode*)userTouch2Array->objectAtIndex(0);
                beginPos = beginNode->getPosition();
                prePoint = curNode->getPosition();
                
                this->cutWhaleAniStart(beginPos, prePoint);
                
                userTouch2Array->removeAllObjects();
            }
           
        }
        
    }
    
//    if (!isUpdateTimerStart) {
//        isUpdateTimerStart = true;
//        this->unscheduleUpdate();
//        this->scheduleUpdate();
//    }
}

void WhaleClass::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCPoint whalePos = whaleBody->getPosition();
    CCSize whaleSize = CCSize(whaleBody->getContentSize().width * LcdAdapClass::sharedLCDADAP()->getXScale(), whaleBody->getContentSize().height * LcdAdapClass::sharedLCDADAP()->getYScale());
    CCRect whaleRect = CCRect(whalePos.x - whaleSize.width / 2, whalePos.y - whaleSize.height /2, whaleSize.width, whaleSize.height);
    
    CCSetIterator iter = pTouches->begin();
    int count = pTouches->count();
    
    if (count > CUT_WAHLE_TOUCH_NUM) {
        count = CUT_WAHLE_TOUCH_NUM;
    }
    
    CCLog("touch num = %d",count);
    
    for (; iter != pTouches->end(); iter++) {
        float subLen = 0;
        CCPoint beginPos = CCPointZero;
        CCTouch *mytouch = (CCTouch*)(*iter);
        

        
//        mytouch->getID();
//        
        CCPoint prePoint = this->convertToNodeSpace(mytouch->getPreviousLocation());//CCDirector::sharedDirector()->convertToGL(mytouch->getPreviousLocation());
        CCPoint curPoint = this->convertToNodeSpace(mytouch->getLocation());//CCDirector::sharedDirector()->convertToGL(mytouch->getLocationInView());
        
        if (prePoint.x == curPoint.x && prePoint.y == prePoint.y) {
            CCLog("stop");
        }
        
        CCNode* curNode = CCNode::create();
        curNode->setPosition(curPoint);
        
        if (whaleRect.containsPoint(curPoint) && userTouchMovedArray[mytouch->getID()].isTouchStartValid) {
            if (mytouch->getID() == 0) {
                CCNode* begin = (CCNode*)userTouch1Array->objectAtIndex(0);
                beginPos = begin->getPosition();
            }
            else if (mytouch->getID() == 1)
            {
                CCNode* begin = (CCNode*)userTouch2Array->objectAtIndex(0);
                beginPos = begin->getPosition();
            }
            
            this->cutWhaleAniStart(beginPos, curPoint);
        }
        
        memset(&userTouchMovedArray[mytouch->getID()], 0, sizeof(userMovedStruct));
        switch (mytouch->getID()) {
            case 0:
            {
                userTouch1Array->removeAllObjects();
                
            }
                break;
            case 1:
            {
                userTouch2Array->removeAllObjects();
            }
                break;
            case 2:
            {
                userTouch3Array->removeAllObjects();
            }
                break;
            case 3:
            {
                userTouch4Array->removeAllObjects();
            }
                break;
            case 4:
            {
                userTouch5Array->removeAllObjects();
            }
                break;
            default:
                break;
        }
        
    }

//    if (count == userTouchNum) {
//        isUpdateTimerStart = false;
//        this->unscheduleUpdate();
//    }
}

void WhaleClass::ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
//    CCSetIterator iter = pTouches->begin();
//    
//    for (; iter != pTouches->end(); iter++) {
//        CCTouch *mytouch = (CCTouch*)(*iter);
//        CCPoint curPoint = CCDirector::sharedDirector()->convertToGL(mytouch->getLocationInView());
//        CCLog("ccTouchesCancelled x = %f   y = %f",curPoint.x,curPoint.y);
//    }
}

void WhaleClass::whaleGiftShowWhileDead()
{
    
    (myTarget->*myFunc)();
    this->removeFromParentAndCleanup(true);
}

void WhaleClass::cutWhaleAniCallBack(cocos2d::CCNode *object)
{
    int curLife = this->getCurLifeValue();
    CCSprite* cutWahle = (CCSprite*)object;
    
    cutWahle->removeFromParentAndCleanup(true);
    
    curLife -= CUT_WHALE_ONCE_KILL_VALUE;
    
    if (curLife <= 0) {
        this->updateWhaleLifeValue(0);
        this->stopAllActions();
        whaleBody->stopAllActions();
        whaleBody->setVisible(false);
        PetsDropClass* gift = PetsDropClass::create(this, callfunc_selector(WhaleClass::whaleGiftShowWhileDead));
        this->addChild(gift,1000);
        gift->showWaleGift();
    }
    else
    {
        this->updateWhaleLifeValue(curLife);
        this->checkWhaleWhichSpeechShowWhileByTouched();
    }
}

void WhaleClass::update(float dt)
{
    CCNode* curNode = NULL;
    CCNode* beginNode = NULL;
    CCNode* preNode = NULL;
    CCNode* diffNode = NULL;
    
    for (int i = 0; i < CUT_WAHLE_TOUCH_NUM; i++) {

        if (userTouchMovedArray[i].isTouchValid) {
            userTouchMovedArray[i].movedCounter += 1;
            if (userTouchMovedArray[i].movedCounter >= USER_TOUCH_MOVED_MAX_COUNTER) {
                userTouchMovedArray[i].movedCounter = 0;
                
                switch (i) {
                    case 0:
                    {
                        diffNode = (CCNode*)userTouch1Array->objectAtIndex(3);
                        preNode  = (CCNode*)userTouch1Array->objectAtIndex(2);
                        curNode = (CCNode*)userTouch1Array->objectAtIndex(1);
                        beginNode = (CCNode*)userTouch1Array->objectAtIndex(0);
                    }
                        break;
                    case 1:
                    {
                        diffNode = (CCNode*)userTouch2Array->objectAtIndex(3);
                        preNode  = (CCNode*)userTouch2Array->objectAtIndex(2);
                        curNode = (CCNode*)userTouch2Array->objectAtIndex(1);
                        beginNode = (CCNode*)userTouch2Array->objectAtIndex(0);
                    }
                        break;
                    case 2:
                    {
                        
                    }
                        break;
                    case 3:
                    {
                        
                    }
                        break;
                    case 4:
                    {
                        
                    }
                        break;
                    default:
                        break;
                }
                
                if (userTouchMovedArray[i].isTouchValid == true) {
                    this->cutWhaleAniStart(beginNode->getPosition(), curNode->getPosition());
                    beginNode->setPosition(curNode->getPosition());
                    preNode->setPosition(curNode->getPosition());
                    diffNode->setPosition(CCPointZero);
                    userTouchMovedArray[i].diffX = 0;
                    userTouchMovedArray[i].diffy = 0;
                }
                
                
                
            }
        }
    }
}

