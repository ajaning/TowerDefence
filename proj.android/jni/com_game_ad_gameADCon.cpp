//
//  com_game_ad_gameADCon.cpp
//  
//
//  Created by jack on 13-12-27.
//
//

#include "com_game_ad_gameADCon.h"
#include <string>
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h> 
#include "gameADConClass.h"

//#define CLASSNAME "com.game.ad.gameADCon"

using namespace cocos2d;
/*
 * Class:     com_game_ad_gameADCon
 * Method:    dmOfferWallAddListStateCallBack
 * Signature: (I)V
 */

JNIEXPORT void JNICALL Java_com_game_ad_gameADCon_dmOfferWallAddListStateCallBack
(JNIEnv * env, jclass tmpClass, jint value)
{
    CCLog("jack state = %d",value);
    gameADConClass::shareGameADCon()->gameDMADRequsetState(GAME_DM_AD_EVENT_TYPE_OFFERWALL_LIST_REQUEST,value,0);
}

/*
 * Class:     com_game_ad_gameADCon
 * Method:    dmOfferWallCacheVideoStateCallBack
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_game_ad_gameADCon_dmOfferWallCacheVideoStateCallBack
(JNIEnv * env, jclass tmpClass, jint value)
{
    CCLog("jack state = %d",value);
    gameADConClass::shareGameADCon()->gameDMADRequsetState(GAME_DM_AD_EVENT_TYPE_OFFERWALL_VIDEO_REQUEST,value,0);
}

/*
 * Class:     com_game_ad_gameADCon
 * Method:    dmOfferWallPlayVideoStateCallBack
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_game_ad_gameADCon_dmOfferWallPlayVideoStateCallBack
(JNIEnv * env, jclass tmpClass, jint value)
{
    CCLog("jack state = %d",value);
    gameADConClass::shareGameADCon()->gameDMADRequsetState(GAME_DM_AD_EVENT_TYPE_OFFERWALL_VIDEO_REQUEST,value,0);
}

/*
 * Class:     com_game_ad_gameADCon
 * Method:    dmOfferWallCheckPointsStateCallBack
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_game_ad_gameADCon_dmOfferWallCheckPointsStateCallBack
(JNIEnv * env, jclass tmpClass, jint value, jint value2)
{
    CCLog("jack state = %d",value);
    gameADConClass::shareGameADCon()->gameDMADRequsetState(GAME_DM_AD_EVENT_TYPE_OFFERWALL_GET_CONSUME_POINT_REQUEST,value,value2);
}

/*
 * Class:     com_game_ad_gameADCon
 * Method:    dmOfferWallConsumePointStateCallBack
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_game_ad_gameADCon_dmOfferWallConsumePointStateCallBack
(JNIEnv * env, jclass tmpClass, jint value, jint value2)
{
    CCLog("jack state = %d",value);
    gameADConClass::shareGameADCon()->gameDMADRequsetState(GAME_DM_AD_EVENT_TYPE_OFFERWALL_SET_CONSUME_POINT_REQUEST,value,value2);
}



/*
 * Class:     com_game_ad_gameADCon
 * Method:    dmInterADLoadResulta
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_game_ad_gameADCon_dmInterADLoadResulta
(JNIEnv * env, jclass tmpClass, jint value)
{
    CCLog("jack state = %d",value);
    gameADConClass::shareGameADCon()->gameDMADRequsetState(GAME_DM_AD_EVENT_TYPE_INTER_REQUEST,value,0);
}

void gameLoadDMOfferWallList()
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "com.game.ad.gameADCon", "showDMOfferWallList", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID,t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void gameLoadDMOfferWallVideo()
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "com.game.ad.gameADCon", "showDMOfferVideo", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID,t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void gameLoadDMOfferWallConsumeTotal()
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "com.game.ad.gameADCon", "showDMOfferCheckPoints", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID,t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void gameSetDMOfferConsume(int consumePoint)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "com.game.ad.gameADCon", "showDMOfferConsumeResult", "(I)V"))
    {
        t.env->CallStaticVoidMethod(t.classID,t.methodID,consumePoint);
        t.env->DeleteLocalRef(t.classID);
    }
}

void gameLoadDMInterAD()
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "com.game.ad.gameADCon", "loadDMInterAD", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID,t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void gameShowDMInterAD()
{
	JniMethodInfo t;

	    if (JniHelper::getStaticMethodInfo(t, "com.game.ad.gameADCon", "showDMInterAD", "()V"))
	    {
	        t.env->CallStaticVoidMethod(t.classID,t.methodID);
	        t.env->DeleteLocalRef(t.classID);
	    }
}
