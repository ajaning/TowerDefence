//
//  gameADConClass.h
//  CaratonFatans
//
//  Created by jack on 13-12-25.
//
//

#ifndef __CaratonFatans__gameADConClass__
#define __CaratonFatans__gameADConClass__

#include <iostream>
#include "cocos2d.h"

typedef enum {
    GAME_DM_AD_EVENT_TYPE_NONE = 0,
    GAME_DM_AD_EVENT_TYPE_OFFERWALL_LIST_REQUEST,//积分墙列表请求
    GAME_DM_AD_EVENT_TYPE_OFFERWALL_VIDEO_REQUEST,//积分墙视频请求
    GAME_DM_AD_EVENT_TYPE_OFFERWALL_GET_CONSUME_POINT_REQUEST,//获取积分墙的积分
    GAME_DM_AD_EVENT_TYPE_OFFERWALL_SET_CONSUME_POINT_REQUEST,//积分墙消费
    GAME_DM_AD_EVENT_TYPE_INTER_REQUEST,//插入普通广告
    GAME_DM_AD_EVENT_TYPE_MAX
}GAME_DM_AD_EVENT_TYPE;

typedef enum {
    GAME_AD_REQUSEST_STATE_TYPE_NONE = 0,
    GAME_AD_REQUSEST_STATE_TYPE_SUCESS = 1,
    GAME_AD_REQUSEST_STATE_TYPE_FAIL = -1,
    GAME_AD_REQUSEST_STATE_TYPE_USER_CLOSE = 2,
    GAME_AD_REQUSEST_STATE_TYPE_MAX
}GAME_AD_REQUSEST_STATE_TYPE;

USING_NS_CC;


class gameADConClass:public CCObject
{
private:
    gameADConClass();
    ~gameADConClass();
    bool init();
public:
    CREATE_FUNC(gameADConClass);
    static gameADConClass* shareGameADCon();
    void showADNow();
    
    void gameADLoadDMOfferWallList();
    void gameADLoadDMOfferWallVideo();
    void gameADLoadDMOfferWallConsumeTotal();
    void gameADSetDMOfferConsume(int consumePoint);
    void gameADLoadDMInterAD();
    
    void gameDMADRequsetState(GAME_DM_AD_EVENT_TYPE eventType,int state,int value);
    bool getIsRequsetOver();
    
    void gameADShowDMInterAD();
    bool checkGameLoadDMInterOK();
    
    int getGameDMConsumePointNum();
    
    void setCallBack(CCObject* target,SEL_CallFunc func);
    
private:
    
    bool isRequsetOver;
    int gameDMADOfferWallListState;
    int gameDMADOfferWallVideoState;
    int gameDMADOfferWallGetConsumePointState;
    int gameDMADOfferWallSetConsumePointState;
    int gameDMADInterState;
    
    int curUserConsumePoint;
    
    CCObject* myObject;
    SEL_CallFunc myFunc;
};

#endif /* defined(__CaratonFatans__gameADConClass__) */
