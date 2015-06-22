//
//  gameADConClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-12-25.
//
//


#include "gameADConClass.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "gameADViewController.h"
#include "gameDMInterObject.h"
#include "gameDMADShowCon.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "com_game_ad_gameADCon.h"
#endif

static gameADConClass* shareADCon = NULL;

gameADConClass::gameADConClass()
{
    gameDMADOfferWallListState = GAME_AD_REQUSEST_STATE_TYPE_NONE;
    gameDMADOfferWallVideoState = GAME_AD_REQUSEST_STATE_TYPE_NONE;
    
    gameDMADOfferWallGetConsumePointState = GAME_AD_REQUSEST_STATE_TYPE_NONE;
    gameDMADOfferWallSetConsumePointState = GAME_AD_REQUSEST_STATE_TYPE_NONE;
    gameDMADInterState = GAME_AD_REQUSEST_STATE_TYPE_NONE;
    
    curUserConsumePoint = 0;
    
    isRequsetOver = false;
    
    myObject = NULL;
    myFunc = NULL;
}

gameADConClass::~gameADConClass()
{

}

bool gameADConClass::init()
{

    return true;
}

gameADConClass* gameADConClass::shareGameADCon()
{
    if(shareADCon == NULL)
    {
        shareADCon = new gameADConClass();
        shareADCon->init();
    }
    
    return shareADCon;
}

void gameADConClass::showADNow()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    UIWindow* window = [[UIApplication sharedApplication] keyWindow];

    gameDMADShowCon* showCon = [[gameDMADShowCon alloc] init];
    [showCon showOfferWall_Manager];
//    [showCon showOfferWall_LIST:window.rootViewController];
//    [showCon showOfferWall_VIDEO:window.rootViewController];
    
//    gameDMInterObject* dminter = [[gameDMInterObject alloc] init];
//    [dminter showDMInter:window.rootViewController];
//    gameADViewController* gameAD = [[gameADViewController alloc] init];
//    
//    [gameAD showOfferWall_VIDEO];
//    
//    [window.rootViewController presentViewController:gameAD animated:YES completion:nil];
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif
}

void gameADConClass::gameADLoadDMOfferWallList()
{
    gameDMADOfferWallListState = GAME_AD_REQUSEST_STATE_TYPE_NONE;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    gameLoadDMOfferWallList();
#endif
}
void gameADConClass::gameADLoadDMOfferWallVideo()
{
    gameDMADOfferWallVideoState = GAME_AD_REQUSEST_STATE_TYPE_NONE;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    gameLoadDMOfferWallVideo();
#endif
}

void gameADConClass::gameADLoadDMOfferWallConsumeTotal()
{
    gameDMADOfferWallGetConsumePointState = GAME_AD_REQUSEST_STATE_TYPE_NONE;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    gameLoadDMOfferWallConsumeTotal();
#endif
}

void gameADConClass::gameADSetDMOfferConsume(int consumePoint)
{
    gameDMADOfferWallSetConsumePointState = GAME_AD_REQUSEST_STATE_TYPE_NONE;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    gameSetDMOfferConsume(consumePoint);
#endif
}


void gameADConClass::gameADLoadDMInterAD()
{
    
    gameDMADInterState = GAME_AD_REQUSEST_STATE_TYPE_NONE;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    UIWindow* window = [[UIApplication sharedApplication] keyWindow];
    [[gameDMADShowCon sharedDMADShow] showDMInter:window.rootViewController];
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    gameLoadDMInterAD();
#endif
}


void gameADConClass::gameADShowDMInterAD()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [[gameDMADShowCon sharedDMADShow] showDMInterNow];
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    gameShowDMInterAD();
#endif
}

void gameADConClass::gameDMADRequsetState(GAME_DM_AD_EVENT_TYPE eventType,int state,int value)
{
    
    switch (eventType) {
        case GAME_DM_AD_EVENT_TYPE_OFFERWALL_LIST_REQUEST:
            gameDMADOfferWallListState = state;
            break;
        case GAME_DM_AD_EVENT_TYPE_OFFERWALL_VIDEO_REQUEST:
            gameDMADOfferWallVideoState = state;
            break;
        case GAME_DM_AD_EVENT_TYPE_OFFERWALL_GET_CONSUME_POINT_REQUEST:
            gameDMADOfferWallGetConsumePointState = state;
            curUserConsumePoint = value;
            if (myObject != NULL && myFunc != NULL) {
                (myObject->*myFunc)();
            }
            break;
        case GAME_DM_AD_EVENT_TYPE_OFFERWALL_SET_CONSUME_POINT_REQUEST:
            gameDMADOfferWallSetConsumePointState = state;
            break;
        case GAME_DM_AD_EVENT_TYPE_INTER_REQUEST:
            gameDMADInterState = state;
//            this->checkGameLoadDMInterOK();
//            this->gameADShowDMInterAD();
            break;
        default:
            break;
    }
    CCLOG("gameDMADRequsetState = %d   value = %d",state,value);
    
}

bool gameADConClass::checkGameLoadDMInterOK()
{
    if (gameDMADInterState == GAME_AD_REQUSEST_STATE_TYPE_SUCESS) {
        CCLOG("gameDMADInterState = success");
        this->gameADShowDMInterAD();
        return true;
    }
    
    return false;
}

int gameADConClass::getGameDMConsumePointNum()
{
    return curUserConsumePoint;
}


bool gameADConClass::getIsRequsetOver()
{
    return isRequsetOver;
}

void gameADConClass::setCallBack(cocos2d::CCObject *target, SEL_CallFunc func)
{
    myObject = target;
    myFunc = func;
}




