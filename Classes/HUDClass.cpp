//
//  HUDClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-8-12.
//
//

#include "HUDClass.h"
#include "GameParam.h"


#define ISFIRSTCREATE   "ISFIRSTCREATE"
#define GAME_MONEY_NUM  "GAME_MONEY_NUM"



//{由于数据量少，数据存储在CCUSERDEFALUT中



static char comBuffer[255] = {0};
static HUDClass* mHUD = NULL;

HUDClass::HUDClass()
{

}

HUDClass::~HUDClass()
{

}

bool HUDClass::init()
{
//    moneyNum = 0;
    moneyNum = 0;//CCUserDefault::sharedUserDefault()->getIntegerForKey(GAME_MONEY_NUM);
    CCLog("%s",CCUserDefault::sharedUserDefault()->getXMLFilePath().c_str());
    return true;
}

HUDClass* HUDClass::create()
{
	HUDClass* hud = new HUDClass();
	if (hud && hud->init())
	{

	}
	else
	{
		CC_SAFE_DELETE(hud);
	}
	return hud;
}

HUDClass* HUDClass::sharedHUD()
{
    if (mHUD == NULL) {
//         mHUD = new HUDClass();
//         mHUD->init();
		mHUD = HUDClass::create();
    }
    return mHUD;
}

int HUDClass::getCurSystemTime()
{
    int sec;

    cc_timeval tv;
    //struct tm* mytm;
    //gettimeofday(&tv, NULL);
    CCTime::gettimeofdayCocos2d(&tv, NULL);
    sec = (int)tv.tv_sec;
    
    return sec;
}

void HUDClass::setGameCurStageInfo(gameStageInfoStruct info)
{
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "stage%d_has",info.stageType);
    CCUserDefault::sharedUserDefault()->setBoolForKey(comBuffer, true);
    CCUserDefault::sharedUserDefault()->flush();
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "stage%d_Locked",info.stageType);
    CCUserDefault::sharedUserDefault()->setBoolForKey(comBuffer, info.isStageLocked);
    CCUserDefault::sharedUserDefault()->flush();
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "stage%d_LLIndex",info.stageType);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(comBuffer, info.lastLevelIndex);
    CCUserDefault::sharedUserDefault()->flush();
}


GAME_STAGE_TYPE HUDClass::getGameStageLastesdID()
{
    GAME_STAGE_TYPE lastedStage = GAME_STAGE_TYPE_SKY;
    
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("gameStageLasted")) {
        lastedStage = (GAME_STAGE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("game_stage_LID");
    }
    
    return lastedStage;
}

void HUDClass::setGameStageLastedid(GAME_STAGE_TYPE type)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("gameStageLasted", true);
    CCUserDefault::sharedUserDefault()->flush();
    CCUserDefault::sharedUserDefault()->setIntegerForKey("game_stage_LID", type);
    CCUserDefault::sharedUserDefault()->flush();
}

//void HUDClass::setCurLevelIsClearAllObject(GAME_STAGE_TYPE stage, int level, bool flag)
//{
//    CCAssert(!(stage == GAME_STAGE_TYPE_NONE || stage == GAME_STAGE_TYPE_MAX), "invalid");
//    CCAssert(!(level <= 0), "invalid");
//    
//    memset(comBuffer, 0, sizeof(comBuffer));
//    sprintf(comBuffer, "gameStage%d_LL%d_CLRO",stage,level);
//    CCUserDefault::sharedUserDefault()->setBoolForKey(comBuffer, flag);
//    CCUserDefault::sharedUserDefault()->flush();
//    
//}
//
//bool HUDClass::getCurLevelIsClearAllObject(GAME_STAGE_TYPE stage, int level)
//{
//    CCAssert(!(stage == GAME_STAGE_TYPE_NONE || stage == GAME_STAGE_TYPE_MAX), "invalid");
//    CCAssert(!(level <= 0), "invalid");
//    
//    bool isClearAll = false;
//    
//    memset(comBuffer, 0, sizeof(comBuffer));
//    sprintf(comBuffer, "gameStage%d_LL%d_CLRO",stage,level);
//    
//    if (CCUserDefault::sharedUserDefault()->getBoolForKey(comBuffer)) {
//        isClearAll = true;
//    }
//    
//    return isClearAll;
//}
//
//void HUDClass::setCurLevelUserGained(GAME_STAGE_TYPE stage, int level, int userGained)
//{
//    CCAssert(!(stage == GAME_STAGE_TYPE_NONE || stage == GAME_STAGE_TYPE_MAX), "invalid");
//    CCAssert(!(level <= 0 || userGained <=0 || userGained > 4), "invalid");
//    
//    memset(comBuffer, 0, sizeof(comBuffer));
//    sprintf(comBuffer, "gameStage%d_LL%d_USRGAIN",stage,level);
//    CCUserDefault::sharedUserDefault()->setIntegerForKey(comBuffer, userGained);
//    CCUserDefault::sharedUserDefault()->flush();
//    
//}
//
//int HUDClass::getCurLevelUserGained(GAME_STAGE_TYPE stage, int level)
//{
//    CCAssert(!(stage == GAME_STAGE_TYPE_NONE || stage == GAME_STAGE_TYPE_MAX), "invalid");
//    CCAssert(!(level <= 0), "invalid");
//    
//    int gained  = 0;
//    
//    memset(comBuffer, 0, sizeof(comBuffer));
//    sprintf(comBuffer, "gameStage%d_LL%d_USRGAIN",stage,level);
//    
//    gained = CCUserDefault::sharedUserDefault()->getIntegerForKey(comBuffer);
//    
//    if (gained < 0) {
//        gained = 0;
//    }
//    
//    return gained;
//}


gameStageInfoStruct HUDClass::getGameCurStageInfo(GAME_STAGE_TYPE gameStage)
{
    gameStageInfoStruct info;
    info.lastLevelIndex = 1;
    info.isStageLocked = true;
    info.stageType = gameStage;
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "stage%d_has",gameStage);
    
    if (CCUserDefault::sharedUserDefault()->getBoolForKey(comBuffer)) {
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "stage%d_Locked",gameStage);
        info.isStageLocked = CCUserDefault::sharedUserDefault()->getBoolForKey(comBuffer);
        
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "stage%d_LLIndex",gameStage);
        info.lastLevelIndex = CCUserDefault::sharedUserDefault()->getIntegerForKey(comBuffer);
    }
    
    return info;
}

void HUDClass::setGameCurLevelInfo(gameLevelInfoStruct info, GAME_STAGE_TYPE gameStage, int level)
{
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "stage%d_levle%d_has",gameStage,level);//表明这个字段存在
    CCUserDefault::sharedUserDefault()->setBoolForKey(comBuffer, true);
    CCUserDefault::sharedUserDefault()->flush();
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "stage%d_levle%d_Locked",gameStage,level);
    CCUserDefault::sharedUserDefault()->setBoolForKey(comBuffer, info.isLevelLocked);
    CCUserDefault::sharedUserDefault()->flush();
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "stage%d_levle%d_CLRALL",gameStage,level);
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey(comBuffer)) {
        CCUserDefault::sharedUserDefault()->setBoolForKey(comBuffer, info.isClearAllObject);
        CCUserDefault::sharedUserDefault()->flush();
    }
    
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "stage%d_levle%d_GAINED",gameStage,level);
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey(comBuffer) < info.UserGained) {
        CCUserDefault::sharedUserDefault()->setIntegerForKey(comBuffer, info.UserGained);
        CCUserDefault::sharedUserDefault()->flush();
    }
    
}

gameLevelInfoStruct HUDClass::getGameCurLevelInfo(GAME_STAGE_TYPE gameStage, int level)
{
    gameLevelInfoStruct info;
    info.isLevelLocked = true;
    info.isClearAllObject = false;
    info.UserGained = 0;
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "stage%d_levle%d_has",gameStage,level);//表明这个字段存在
    
    if (CCUserDefault::sharedUserDefault()->getBoolForKey(comBuffer)) {
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "stage%d_levle%d_Locked",gameStage,level);
        info.isLevelLocked = CCUserDefault::sharedUserDefault()->getBoolForKey(comBuffer);
        
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "stage%d_levle%d_CLRALL",gameStage,level);
        info.isClearAllObject = CCUserDefault::sharedUserDefault()->getBoolForKey(comBuffer);
        
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "stage%d_levle%d_GAINED",gameStage,level);
        info.UserGained = CCUserDefault::sharedUserDefault()->getIntegerForKey(comBuffer);
    }
    
    
    return info;
}


void HUDClass::setHUDMoney(int money)
{
    moneyNum = money;
    if (moneyNum < 0) {
        moneyNum = 0;
    }
//     CCUserDefault::sharedUserDefault()->setIntegerForKey(GAME_MONEY_NUM, moneyNum);
//     CCUserDefault::sharedUserDefault()->flush();
}

int HUDClass::getHUDMoney()
{
    return moneyNum;
}

int HUDClass::getUserCookieNum()
{
    
    int num = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_COOKIE_NUM");
    
    return num;
}


void HUDClass::setUserCookieNum(int num)
{
    int cookieNum = num;
    if (cookieNum < 0) {
        cookieNum = 0;
    }
    
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_COOKIE_NUM", num);
    CCUserDefault::sharedUserDefault()->flush();
}

int HUDClass::getUserBigNestNum()
{
    int num = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_BIGNEST_NUM");
    
    return num;
}

void HUDClass::setUserBigNestNum(int num)
{
    int bigNestNum = num;
    
    if (bigNestNum > USER_BIG_NEST_NUM_MAX) {
        bigNestNum = USER_BIG_NEST_NUM_MAX;
    }
    else if (bigNestNum < 0){
        bigNestNum = 0;
    }
    
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_BIGNEST_NUM", bigNestNum);
    CCUserDefault::sharedUserDefault()->flush();
}


int HUDClass::getUserNestNum()
{
    int num = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_NEST_NUM");
    
    return num;

}

void HUDClass::setUserNestNum(int num)
{
    int nestNum = num;
    
    if (nestNum > USER_NEST_NUM_MAX) {
        nestNum = USER_NEST_NUM_MAX;
    }
    else if (nestNum < 0)
    {
        nestNum = 0;
    }
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_NEST_NUM", nestNum);
    CCUserDefault::sharedUserDefault()->flush();
}

int HUDClass::getUserMilkNum()
{
    
    int num = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_MILK_NUM");
    
    return num;
}

void HUDClass::setUserMilkNum(int num)
{
    int milkNum = num;
    
    if (milkNum < 0) {
        milkNum = 0;
    }
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_MILK_NUM", num);
    CCUserDefault::sharedUserDefault()->flush();
}

int HUDClass::getUserMedicineNum()
{
    int num = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_MEDICINE_NUM");
    
    return num;
}

void HUDClass::setUserMedicineNum(int num)
{
    int meNum = num;
    
    if (meNum < 0) {
        meNum = 0;
    }
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_MEDICINE_NUM", num);
    CCUserDefault::sharedUserDefault()->flush();
}

int HUDClass::getUserPetsNum()
{
    
    int num = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_NUM");
    
    return num;
}

void HUDClass::setUserPetsNum(int num)
{
    int petNum = num;
    
    if (petNum > USER_PET_NUM_MAX) {
        petNum = USER_PET_NUM_MAX;
    }
    else if (petNum < 0)
    {
        petNum = 0;
    }
    
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_NUM", num);
    CCUserDefault::sharedUserDefault()->flush();
}

void HUDClass::setUserGoodsInfo(userGoodsDataStruct data)
{
    this->setUserMilkNum(data.userMilkNum);
    this->setUserCookieNum(data.userCookieNum);
    this->setUserPetsNum(data.userPetsNum);
}

userGoodsDataStruct HUDClass::getUserGoodsInfo()
{
    userGoodsDataStruct data;
    data.userCookieNum = this->getUserCookieNum();
    data.userMilkNum = this->getUserMilkNum();
    data.userPetsNum = this->getUserPetsNum();
    
    return data;
}


void HUDClass::addPetsEggByType(PETS_BREED_EGG_TYPE eggType)
{
    CCAssert(!(eggType == PETS_BREED_EGG_TYPE_NONE || eggType == PETS_BREED_EGG_TYPE_MAX), "cannot be invalid");
    userPetDataStruct userPet = this->getUserPetInfo(eggType);
    int petNum = this->getUserPetsNum();
    
    
    if ((userPet.eggState == PETS_EGG_STATE_TYPE_NONE || userPet.eggState == PETS_EGG_STATE_TYPE_MAX) && (petNum < USER_PET_NUM_MAX)) {//means no egg in user NPC
        
        userPetDataStruct petinfo;
        
        petinfo.eggType = eggType;
        petinfo.eggState = PETS_EGG_STATE_TYPE_ONLY_AN_EGG;
        petinfo.breededTime = 0;
        petinfo.breedState = PETS_EGG_BREED_STATE_TYPE_FIRST;
        petinfo.curNeedCookieNum = 0;
        petinfo.curNeedMilkNum = 0;
        petinfo.feedState = PETS_FEED_STATE_TYPE_FIRST;
        
        if (petNum < 0) {
            petNum = 0;
        }
        petNum += 1;
        this->setUserPetsNum(petNum);
        this->setUserPetsInfo(petinfo);
    }
    
    
}

void HUDClass::setUserPetsInfo(userPetDataStruct data)
{
    switch (data.eggType) {
        case PETS_BREED_EGG_TYPE_BOSS_01:
            {
                CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_BOSS_01", true);
                CCUserDefault::sharedUserDefault()->flush();
                CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_01_BREED_STATE", (int)data.breedState);\
                CCUserDefault::sharedUserDefault()->flush();
                CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_01_FEED_STATE", data.feedState);
                CCUserDefault::sharedUserDefault()->flush();
                CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_01_BREED_TIME", data.breededTime);
                CCUserDefault::sharedUserDefault()->flush();
                CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_01_NEEDED_MILK_NUM", data.curNeedMilkNum);
                CCUserDefault::sharedUserDefault()->flush();
                CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_01_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
                CCUserDefault::sharedUserDefault()->flush();
                
                CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_01_EGG_STATE", data.eggState);
                CCUserDefault::sharedUserDefault()->flush();
                
            }
            break;
        case PETS_BREED_EGG_TYPE_BOSS_02:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_BOSS_02", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_02_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_02_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_02_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_02_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_02_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_02_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_BOSS_03:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_BOSS_03", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_03_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_03_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_03_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_03_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_03_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_03_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_BOSS_06:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_BOSS_06", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_06_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_06_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_06_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_06_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_06_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_BOSS_06_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FAT_01:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_FAT_01", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_01_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_01_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_01_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_01_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_01_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_01_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FAT_02:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_FAT_02", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_02_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_02_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_02_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_02_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_02_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_02_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FAT_03:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_FAT_03", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_03_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_03_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_03_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_03_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_03_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_03_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FAT_06:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_FAT_06", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_06_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_06_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_06_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_06_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_06_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FAT_06_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FLY_01:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_FLY_01", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_01_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_01_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_01_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_01_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_01_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_01_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FLY_02:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_FLY_02", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_02_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_02_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_02_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_02_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_02_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_02_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FLY_03:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_FLY_03", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_03_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_03_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_03_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_03_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_03_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_03_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FLY_06:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_FLY_06", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_06_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_06_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_06_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_06_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_06_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_FLY_06_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_01:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_LAND_01", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_01_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_01_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_01_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_01_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_01_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_01_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_02:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_LAND_02", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_02_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_02_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_02_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_02_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_02_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_02_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_03:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_LAND_03", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_03_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_03_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_03_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_03_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_03_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_03_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_06:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_LAND_06", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_06_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_06_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_06_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_06_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_06_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_06_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_2_01:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_LAND_2_01", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_01_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_01_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_01_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_01_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_01_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_01_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_2_02:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_LAND_2_02", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_02_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_02_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_02_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_02_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_02_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_02_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_2_03:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_LAND_2_03", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_03_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_03_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_03_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_03_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_03_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_03_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_2_06:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_LAND_2_06", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_06_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_06_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_06_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_06_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_06_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_LAND_2_06_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
        }
            break;
        case PETS_BREED_EGG_TYPE_WHALE_06:
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey("USER_PETS_WHALE_06", true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_WHALE_06_BREED_STATE", data.breedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_WHALE_06_FEED_STATE", data.feedState);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_WHALE_06_BREED_TIME", data.breededTime);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_WHALE_06_NEEDED_MILK_NUM", data.curNeedMilkNum);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_WHALE_06_NEEDED_COOKIE_NUM", data.curNeedCookieNum);
            CCUserDefault::sharedUserDefault()->flush();
            
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_PETS_WHALE_06_EGG_STATE", data.eggState);
            CCUserDefault::sharedUserDefault()->flush();
            
            
        }
            break;
            
        default:
            break;
    }
}

userPetDataStruct HUDClass::getUserPetInfo(PETS_BREED_EGG_TYPE type)
{
    userPetDataStruct petsInfo;
    
    petsInfo.curNeedCookieNum = 0;
    petsInfo.curNeedMilkNum = 0;
    petsInfo.breededTime = 0;
    petsInfo.breedState = PETS_EGG_BREED_STATE_TYPE_NONE;
    petsInfo.eggType = type;
    petsInfo.feedState = PETS_FEED_STATE_TYPE_NONE;
    petsInfo.eggState = PETS_EGG_STATE_TYPE_NONE;
    
    
    switch (type) {
        case PETS_BREED_EGG_TYPE_BOSS_01:
        {
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_BOSS_01")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_01_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_01_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_01_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_01_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_01_NEEDED_COOKIE_NUM");
                
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_01_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_BOSS_02:
        {
            
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_BOSS_02")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_02_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_02_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_02_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_02_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_02_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_02_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_BOSS_03:
        {
            
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_BOSS_03")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_03_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_03_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_03_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_03_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_03_NEEDED_COOKIE_NUM");
                
                
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_03_EGG_STATE");
                
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_BOSS_06:
        {
            
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_BOSS_06")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_06_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_06_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_06_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_06_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_06_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_BOSS_06_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FAT_01:
        {
            
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_FAT_01")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_01_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_01_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_01_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_01_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_01_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_01_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FAT_02:
        {
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_FAT_02")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_02_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_02_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_02_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_02_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_02_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_02_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FAT_03:
        {
            
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_FAT_03")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_03_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_03_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_03_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_03_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_03_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_03_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FAT_06:
        {
            
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_FAT_06")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_06_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_06_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_06_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_06_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_06_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FAT_06_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FLY_01:
        {
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_FLY_01")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_01_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_01_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_01_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_01_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_01_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_01_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FLY_02:
        {
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_FLY_02")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_02_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_02_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_02_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_02_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_02_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_02_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FLY_03:
        {
            
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_FLY_03")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_03_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_03_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_03_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_03_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_03_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_03_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_FLY_06:
        {
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_FLY_06")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_06_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_06_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_06_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_06_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_06_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_FLY_06_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_01:
        {
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_LAND_01")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_01_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_01_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_01_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_01_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_01_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_01_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_02:
        {
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_LAND_02")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_02_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_02_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_02_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_02_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_02_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_02_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_03:
        {
            
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_LAND_03")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_03_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_03_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_03_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_03_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_03_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_03_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_06:
        {
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_LAND_06")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_06_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_06_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_06_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_06_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_06_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_06_EGG_STATE");
            }
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_2_01:
        {
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_LAND_2_01")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_01_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_01_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_01_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_01_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_01_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_01_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_2_02:
        {
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_LAND_2_02")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_02_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_02_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_02_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_02_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_02_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_02_EGG_STATE");
            }
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_2_03:
        {
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_LAND_2_03")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_03_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_03_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_03_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_03_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_03_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_03_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_LAND_2_06:
        {
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_LAND_2_06")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_06_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_06_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_06_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_06_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_06_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_LAND_2_06_EGG_STATE");
            }
            
        }
            break;
        case PETS_BREED_EGG_TYPE_WHALE_06:
        {
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("USER_PETS_WHALE_06")) {
                
                petsInfo.breedState = (PETS_EGG_BREED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_WHALE_06_BREED_STATE");
                petsInfo.feedState = (PETS_FEED_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_WHALE_06_FEED_STATE");
                petsInfo.breededTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_WHALE_06_BREED_TIME");
                
                petsInfo.curNeedMilkNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_WHALE_06_NEEDED_MILK_NUM");
                
                petsInfo.curNeedCookieNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_WHALE_06_NEEDED_COOKIE_NUM");
                petsInfo.eggState = (PETS_EGG_STATE_TYPE)CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_PETS_WHALE_06_EGG_STATE");
            }
            
        }
            break;
            
        default:
            break;
    }
    
    
    return petsInfo;
}

int HUDClass::getUserStoneNum()
{
    int num = 0;
    
    num = CCUserDefault::sharedUserDefault()->getIntegerForKey("USER_STONE_NUM");
    
    if (num < 0) {
        num = 0;
    }
    
    return num;
}

void HUDClass::setUserStoneNum(int num)
{
    if (num < 0) {
        num = 0;
    }
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("USER_STONE_NUM", num);
    
}


