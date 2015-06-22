//
//  HUDClass.h
//  CaratonFatans
//
//  Created by jack on 13-8-12.
//
//

#ifndef __CaratonFatans__HUDClass__
#define __CaratonFatans__HUDClass__

#include <iostream>
#include "cocos2d.h"
#include "GameSpriteParm.h"

USING_NS_CC;
class HUDClass:public CCObject
{
private:
    HUDClass();
    ~HUDClass();
    bool init();
    bool isCheckFisrt();
    //CREATE_FUNC(HUDClass);
	static HUDClass* create();
public:
    static HUDClass* sharedHUD();
    void setHUDMoney(int money);
    int getHUDMoney(void);
    
    void setUserGoodsInfo(userGoodsDataStruct data);
    userGoodsDataStruct getUserGoodsInfo();
    
    void setUserPetsInfo(userPetDataStruct data);
    userPetDataStruct getUserPetInfo(PETS_BREED_EGG_TYPE type);
    
    int getUserMedicineNum();
    void setUserMedicineNum(int num);
    
    int getUserPetsNum();
    void setUserPetsNum(int num);
    
    int getUserBigNestNum();
    void setUserBigNestNum(int num);
    
    int getUserNestNum();
    void setUserNestNum(int num);
    
    int getUserMilkNum();
    void setUserMilkNum(int num);
    
    int getUserCookieNum();
    void setUserCookieNum(int num);
    
    int getCurSystemTime();
    
    void addPetsEggByType(PETS_BREED_EGG_TYPE eggType);
    
    gameLevelInfoStruct getGameCurLevelInfo(GAME_STAGE_TYPE gameStage,int level);
    void setGameCurLevelInfo(gameLevelInfoStruct info,GAME_STAGE_TYPE gameStage,int level);
    
    gameStageInfoStruct getGameCurStageInfo(GAME_STAGE_TYPE gameStage);
    void setGameCurStageInfo(gameStageInfoStruct info);
    
    GAME_STAGE_TYPE getGameStageLastesdID();
    void setGameStageLastedid(GAME_STAGE_TYPE type);
    
    int getUserStoneNum();
    void setUserStoneNum(int num);
    
    
private:
    int moneyNum;
};
#endif /* defined(__CaratonFatans__HUDClass__) */
