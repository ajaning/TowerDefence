//
//  PetsBreedClass.cpp
//  CaratonFatans
//
//  Created by  Jack on 13-11-25.
//
//

#include "PetsBreedClass.h"
#include "HUDClass.h"

#define FOOD_MENU_MILK_ID   (1)
#define FOOD_MENU_COOKIE_ID (2)

typedef struct {
    PETS_EGG_BREED_STATE_TYPE type;
    int breedTime;
}petsEggBreedStateTimeStruct;

typedef struct {
    PETS_FEED_STATE_TYPE feedState;
    int cookNum;
    int milkNum;
}petsFeedStateStruct;

typedef struct {
    PETS_BREED_EGG_TYPE eggType;
    petsEggBreedStateTimeStruct breedStateTime[PETS_EGG_BREED_STATE_TYPE_THR];
    petsFeedStateStruct bornFeedState[PETS_FEED_STATE_TYPE_THR];
}petsEggTypeBreedStruct;

#define PETS_SPEECH_MAX_INDEX  (3)

const char* pets_born_speech_a[] = {
    "speech_a_1_CN.png",
    "speech_a_2_CN.png",
};

const char* pets_born_speech_b[] = {
    "speech_b_1_CN.png",
    "speech_b_2_CN.png",
};

const char* pets_born_feeding_speech_a[] = {
    "speech_a_3_CN.png",
    "speech_a_4_CN.png",
};

const char* pets_born_feeding_speech_b[] = {
    "speech_b_3_CN.png",
    "speech_b_4_CN.png",
};


const char* pets_grown_speech_a[] = {
    "speech_a_5_CN.png",
    "speech_a_6_CN.png",
};

const char* pets_grown_speech_b[] = {
    "speech_b_5_CN.png",
    "speech_b_6_CN.png",
};






static petsEggTypeBreedStruct petsEggConfigData[] = {
    {PETS_BREED_EGG_TYPE_NONE,{
        
        {PETS_EGG_BREED_STATE_TYPE_NONE,0},
        
        {PETS_EGG_BREED_STATE_TYPE_NONE,0},
        
        {PETS_EGG_BREED_STATE_TYPE_NONE,0}},
        
        {
            {PETS_FEED_STATE_TYPE_NONE,0,0},
            {PETS_FEED_STATE_TYPE_NONE,0,0},
            {PETS_FEED_STATE_TYPE_NONE,0,0},
        }
    
    },
    
    {PETS_BREED_EGG_TYPE_BOSS_01,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_BOSS_01 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_BOSS_01 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_BOSS_01 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_BOSS_02,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_BOSS_02 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_BOSS_02 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_BOSS_02 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_BOSS_03,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_BOSS_03 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_BOSS_03 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_BOSS_03 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_BOSS_06,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_BOSS_06 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_BOSS_06 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_BOSS_06 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_FAT_01,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_FAT_01 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_FAT_01 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_FAT_01 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_FAT_02,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_FAT_02 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_FAT_02 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_FAT_02 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_FAT_03,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_FAT_03 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_FAT_03 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_FAT_03 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_FAT_06,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_FAT_06 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_FAT_06 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_FAT_06 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_FLY_01,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_FLY_01 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_FLY_01 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_FLY_01 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_FLY_02,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_FLY_02 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_FLY_02 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_FLY_02 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_FLY_03,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_FLY_03 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_FLY_03 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_FLY_03 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_FLY_06,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_FLY_06 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_FLY_06 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_FLY_06 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_LAND_01,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_LAND_01 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_LAND_01 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_LAND_01 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_LAND_02,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_LAND_02 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_LAND_02 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_LAND_02 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_LAND_03,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_LAND_03 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_LAND_03 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_LAND_03 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_LAND_06,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_LAND_06 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_LAND_06 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_LAND_06 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_LAND_2_01,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_LAND_2_01 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_LAND_2_01 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_LAND_2_01 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_LAND_2_02,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_LAND_2_02 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_LAND_2_02 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_LAND_2_02 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_LAND_2_03,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_LAND_2_03 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_LAND_2_03 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_LAND_2_03 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_LAND_2_06,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_LAND_2_06 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_LAND_2_06 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_LAND_2_06 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    },
    
    {PETS_BREED_EGG_TYPE_WHALE_06,{
        
        {PETS_EGG_BREED_STATE_TYPE_FIRST,PETS_EGG_BREED_TIME_TYPE_WHALE_06 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_SEC,PETS_EGG_BREED_TIME_TYPE_WHALE_06 * 2 / PETS_EGG_BREED_STATE_TYPE_THR},
        
        {PETS_EGG_BREED_STATE_TYPE_THR,PETS_EGG_BREED_TIME_TYPE_WHALE_06 * 3/ PETS_EGG_BREED_STATE_TYPE_THR}},
        {
            {PETS_FEED_STATE_TYPE_FIRST,50,50},
            {PETS_FEED_STATE_TYPE_SEC,50,50},
            {PETS_FEED_STATE_TYPE_THR,50,50},
        }
    }
};

static char comBuffer[20] = {0};

PetsBreedClass::PetsBreedClass()
{
    
}

PetsBreedClass::~PetsBreedClass()
{
//    if (breedSec > 0 || breedMin > 0 || breedHour > 0 || feededCookieNum > 0 || feededMilkNum > 0)
    {
        userPetDataStruct myPetInfo;
        
        int time = breedHour * 3600 + breedMin * 60 + breedSec;
        myPetInfo.breededTime = HUDClass::sharedHUD()->getCurSystemTime() - time;
        myPetInfo.breedState = myBreedState;
        myPetInfo.feedState = myFeedState;
        myPetInfo.eggType = myEggType;
        myPetInfo.curNeedCookieNum = curNeedCookieNum;
        myPetInfo.curNeedMilkNum = curNeedMilkNum;
        myPetInfo.eggState = petsEggState;
        HUDClass::sharedHUD()->setUserPetsInfo(myPetInfo);
    }
    
    if (petsBodyAni != NULL && petsBodyAni->retainCount() > 0) {
        petsBodyAni->release();
    }
    
    if (petsEyeAni != NULL && petsBodyAni->retainCount() > 0) {
        petsEyeAni->release();
    }
}

bool PetsBreedClass::init(PETS_BREED_EGG_TYPE eggType, PETS_EGG_BREED_STATE_TYPE breedType, int feededCookieNum, int feededMilkNum, int breededTime)
{
    this->comSetPetsEggType(eggType, breedType, curNeedCookieNum, curNeedMilkNum,breededTime);
    return true;
}

PetsBreedClass* PetsBreedClass::create(PETS_BREED_EGG_TYPE eggType, PETS_EGG_BREED_STATE_TYPE breedType, int feededCookieNum, int feededMilkNum, int breededTime)
{
    PetsBreedClass* egg = new PetsBreedClass();
    
    if (egg && egg->init(eggType, breedType, feededCookieNum, feededMilkNum,breededTime)) {
        egg->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(egg);
    }
    
    return egg;
}

void PetsBreedClass::initSprite()
{
    //only for default init
    
    int breededTime = 0;
    

    
    padSprite = CCSprite::createWithSpriteFrameName("PetNest01.png");
    CCSize padSize = padSprite->getContentSize();
    padSprite->setPosition(ccp(0, 0));
    this->addChild(padSprite,1);
    padSprite->setVisible(false);
    
    
    
    CCSize petsSize;
    
    
    if (myEggType == PETS_BREED_EGG_TYPE_WHALE_06) {
        petsEggSprite = CCSprite::createWithSpriteFrameName("SPetWhale11_06.png");
        
        petsSize = petsEggSprite->getContentSize();
        whaleTail = CCSprite::createWithSpriteFrameName("SPetWhale12_06.png");
        whaleTail->setPosition(ccp(petsSize.width / 2,petsSize.height / 2));
        whaleTail->setVisible(false);
        petsEggSprite->addChild(whaleTail,1);
    }
    else
    {
        petsEggSprite = CCSprite::createWithSpriteFrameName("EggBoss11_01.png");
        petsSize = petsEggSprite->getContentSize();
    }
    
    petsEggSprite->setPosition(ccp(0,0));
    petsEggSprite->setVisible(false);
    this->addChild(petsEggSprite,3);
    
    //if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN)
    {
        
        
        memset(comBuffer, 0, sizeof(comBuffer));
//        breedHour = breededTime / 3600;
//        breedMin = ((breededTime % 3600) / 60);
//        breedSec = ((breededTime % 3600) % 60);
        
        breedTimeBG = CCSprite::createWithSpriteFrameName("PetTimeBG.png");
        CCSize timeBGSize = breedTimeBG->getContentSize();
        if (myEggType == PETS_BREED_EGG_TYPE_WHALE_06) {
            breedTimeBG->setPosition(ccp(petsSize.width / 2, petsSize.height * 23 / 100));
        }
        else
        {
            breedTimeBG->setPosition(ccp(petsSize.width / 2, petsSize.height / 2));
        }
        petsEggSprite->addChild(breedTimeBG,3);
        breedTimeBG->setVisible(false);
        
        sprintf(comBuffer, "%02d",breedHour);
        myBreedTimeHourLAB = CCLabelAtlas::create(comBuffer, "Themes/Pets/PetNumBig.png", 13, 20, 46);
        myBreedTimeHourLAB->setPosition(ccp(timeBGSize.width * 13 / 100, timeBGSize.height * 6 / 100));
        
        breedTimeBG->addChild(myBreedTimeHourLAB,1);
        
        sprintf(comBuffer, "%02d",breedMin);
        myBreedTimeMinLAB = CCLabelAtlas::create(comBuffer, "Themes/Pets/PetNumBig.png", 13, 20, 46);
        myBreedTimeMinLAB->setPosition(ccp(timeBGSize.width * 40 / 100, timeBGSize.height * 6 / 100));
        
        breedTimeBG->addChild(myBreedTimeMinLAB,1);
        
        sprintf(comBuffer, "%02d",breedSec);
        myBreedTimeSecLAB = CCLabelAtlas::create(comBuffer, "Themes/Pets/PetNumBig.png", 13, 20, 46);
        myBreedTimeSecLAB->setPosition(ccp(timeBGSize.width * 65 / 100, timeBGSize.height * 6 / 100));
        
        breedTimeBG->addChild(myBreedTimeSecLAB,1);
        
        //this->scheduleUpdate();
    }
    //else
    {
        
        showSpeechBG_A = CCSprite::createWithSpriteFrameName("speech_a.png");
        showSpeechBG_A->setPosition(ccp(petsSize.width * 16 /100, petsSize.height * 58 / 100));
        CCSize speechBGASize = showSpeechBG_A->getContentSize();
        showPetsSpeechA = CCSprite::createWithSpriteFrameName("speech_a_1_CN.png");
        showPetsSpeechA->setPosition(ccp(speechBGASize.width / 2, speechBGASize.height / 2));
        showSpeechBG_A->addChild(showPetsSpeechA,1);
        showSpeechBG_A->setVisible(false);
        petsEggSprite->addChild(showSpeechBG_A,15);
        
        
        showSpeechBG_B = CCSprite::createWithSpriteFrameName("speech_b.png");
        showSpeechBG_B->setPosition(ccp(petsSize.width * 95 /100, petsSize.height * 58 / 100));
        CCSize speechBGBSize = showSpeechBG_B->getContentSize();
        showPetsSpeechB = CCSprite::createWithSpriteFrameName("speech_b_1_CN.png");
        showPetsSpeechB->setPosition(ccp(speechBGBSize.width / 2, speechBGBSize.height / 2));
        showSpeechBG_B->addChild(showPetsSpeechB,1);
        showSpeechBG_B->setVisible(false);
        petsEggSprite->addChild(showSpeechBG_B,15);
        
        //if (myBreedState == PETS_EGG_BREED_STATE_TYPE_BORN)
        {
            int userMilk = HUDClass::sharedHUD()->getUserMilkNum();
            int userCookieNum = HUDClass::sharedHUD()->getUserCookieNum();
            char *milkFileName = NULL;
            char *cookieFileName = NULL;
            
            feedTotalCookieNum = petsEggConfigData[myEggType].bornFeedState[myFeedState].cookNum;
            feedTotalMilkNum = petsEggConfigData[myEggType].bornFeedState[myFeedState].milkNum;
            if (feedTotalMilkNum <= userMilk) {
                milkFileName = "PetMilk01.png";
            }
            else
            {
                milkFileName = "PetMilk00.png";
            }
            
            if (feedTotalCookieNum <= userMilk) {
                cookieFileName = "PetCookie01.png";
            }
            else
            {
                cookieFileName = "PetCookie00.png";
            }
            
            showMilkMenu = CCMenuItemImage::create(milkFileName, milkFileName, this, menu_selector(PetsBreedClass::showFoodMenuActionCallBack));
            showMilkMenu->setTag(FOOD_MENU_MILK_ID);
            showMilkMenu->setPosition(ccp(petsSize.width * 15 / 100, petsSize.height * 20 /100));
            //padSprite->addChild(showMilkMenu,10);
            showMilkMenu->setVisible(false);
            
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%d",feedTotalMilkNum);
            int len = strlen(comBuffer);
            milkNumLab = CCLabelAtlas::create(comBuffer, "Themes/Pets/PetFeedNum.png", 9, 13, 46);
            milkNumLab->setPosition(ccp((showMilkMenu->getContentSize().width - 9 * len)/ 2, showMilkMenu->getContentSize().height * 15 / 100));
            showMilkMenu->addChild(milkNumLab,1);
            
            showCookieMenu = CCMenuItemImage::create(cookieFileName, cookieFileName, this, menu_selector(PetsBreedClass::showFoodMenuActionCallBack));
            showCookieMenu->setTag(FOOD_MENU_COOKIE_ID);
            showCookieMenu->setPosition(ccp(petsSize.width * 85 / 100, petsSize.height * 20 /100));
            //padSprite->addChild(showCookieMenu,10);
            showCookieMenu->setVisible(false);
            
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%d",feedTotalMilkNum);
            len = strlen(comBuffer);
            cookieNumLab = CCLabelAtlas::create(comBuffer, "Themes/Pets/PetFeedNum.png", 9, 13, 46);
            cookieNumLab->setPosition(ccp((showCookieMenu->getContentSize().width  - len * 9) / 2, showCookieMenu->getContentSize().height * 15 / 100));
            showCookieMenu->addChild(cookieNumLab,1);
            
            CCMenu* menu = CCMenu::create(showMilkMenu,showCookieMenu,NULL);
            menu->setPosition(CCPointZero);
            petsEggSprite->addChild(menu,10);
        }
        
        
        petsEyeSprite = CCSprite::createWithSpriteFrameName("SEPetBoss11_01.png");
        CCSize petsSize = petsEggSprite->getContentSize();
        petsEyeSprite->setPosition(ccp(petsSize.width / 2, petsSize.height / 2));
        petsEggSprite->addChild(petsEyeSprite,6);
        petsEyeSprite->setVisible(false);
        
    }
}

bool PetsBreedClass::init(userPetDataStruct petInfo)
{
    speechIndex = 0;
    breedTimeCounter = 0;
    breedHour = 0;
    breedMin = 0;
    breedSec = 0;
    curNeedMilkNum = 0;
    curNeedCookieNum = 0;
    feedTotalCookieNum = 0;
    feedTotalMilkNum = 0;
    petsEyeSprite = NULL;
    myBreedTimeHourLAB = NULL;
    myBreedTimeMinLAB = NULL;
    myBreedTimeSecLAB = NULL;
    
    milkNumLab = NULL;
    cookieNumLab = NULL;
    showMilkMenu = NULL;
    showCookieMenu = NULL;
    isShowFoodPad = false;
    
    showPetsSpeechA = NULL;
    showPetsSpeechB = NULL;
    showSpeechBG_A = NULL;
    showSpeechBG_B = NULL;
    
    petsEyeAni = NULL;
    petsBodyAni = NULL;
    
    
    myBreedTime = petInfo.breededTime;
    myFeedState = petInfo.feedState;
    myEggType = petInfo.eggType;
    curNeedMilkNum = petInfo.curNeedMilkNum;
    curNeedCookieNum = petInfo.curNeedCookieNum;
//    breedHour = petInfo.breededTime / 3600;
//    breedMin = (petInfo.breededTime % 3600) / 60;
//    breedSec = (petInfo.breededTime % 60);
    petsEggState = petInfo.eggState;
    myBreedState = petInfo.breedState;
    int diffSec = 0;
    
    if (petsEggState == PETS_EGG_STATE_TYPE_START_BREEDDING) {
        diffSec = HUDClass::sharedHUD()->getCurSystemTime() - myBreedTime;
    }
    
    breedHour = diffSec / 3600;
    breedMin = (diffSec % 3600) / 60;
    breedSec = (diffSec % 60);
    
    
    this->initSprite();
    this->init(petInfo.eggType, petInfo.breedState, petInfo.curNeedCookieNum, petInfo.curNeedMilkNum, diffSec);
    return true;
}


PetsBreedClass* PetsBreedClass::create(userPetDataStruct petInfo)
{

    PetsBreedClass* breed = new PetsBreedClass();
    
    if (breed && breed->init(petInfo)) {
        breed->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(breed);
    }
    
    return breed;
}

bool PetsBreedClass::init(userPetDataStruct petInfo, cocos2d::CCObject *target, SEL_CallFunc func)
{
    CCAssert(!(target == NULL), "cannot be NULL");
    CCAssert(!(func == NULL), "cannot be NULL");
    
    myTarget = target;
    myFunc = func;
    
    this->init(petInfo);
    
    return true;
}

PetsBreedClass* PetsBreedClass::create(userPetDataStruct petInfo, cocos2d::CCObject *target, SEL_CallFunc func)
{
    PetsBreedClass* breed = new PetsBreedClass();
    
    if (breed && breed->init(petInfo, target, func)) {
        breed->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(breed);
    }
    
    return breed;
}


void PetsBreedClass::comSetPetsEggType(PETS_BREED_EGG_TYPE eggType, PETS_EGG_BREED_STATE_TYPE breedType, int feededCookieNum, int feededMilkNum, int breededTime)
{
    CCAssert(!(eggType == PETS_BREED_EGG_TYPE_NONE || eggType == PETS_BREED_EGG_TYPE_MAX), "cannot be invalid");
    
    char *eyeAniFileName = NULL;
    char *petsEggAniFileName = NULL;
    char *padFileName = NULL;
    
    
    CCSpriteFrame* frame = NULL;
    CCArray* comArray = CCArray::create();
    

    
    myEggType = eggType;
    myBreedState = breedType;
    
    
    switch (eggType) {
        case PETS_BREED_EGG_TYPE_BOSS_01:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_BOSS_01].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggBoss1%d_01.png",i);
                        
                        break;
                    }
                    
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetBoss1%d_01.png";
                        eyeAniFileName = "SEPetBoss1%d_01.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetBoss1%d_01.png";
                    eyeAniFileName = "SEPetBoss1%d_01.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetBoss1%d_01.png";
                    eyeAniFileName = "EPetBoss1%d_01.png";
                }
            }
        }
            break;
        case PETS_BREED_EGG_TYPE_BOSS_02:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_BOSS_02].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggBoss1%d_02.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetBoss1%d_02.png";
                        eyeAniFileName = "SEPetBoss1%d_02.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetBoss1%d_02.png";
                    eyeAniFileName = "SEPetBoss1%d_02.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetBoss1%d_02.png";
                    eyeAniFileName = "EPetBoss1%d_02.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_BOSS_03:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_BOSS_03].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggBoss1%d_03.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetBoss1%d_03.png";
                        eyeAniFileName = "SEPetBoss1%d_03.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetBoss1%d_03.png";
                    eyeAniFileName = "SEPetBoss1%d_03.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetBoss1%d_03.png";
                    eyeAniFileName = "EPetBoss1%d_03.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_BOSS_06:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_BOSS_06].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggBoss1%d_06.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetBoss1%d_06.png";
                        eyeAniFileName = "SEPetBoss1%d_06.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetBoss1%d_06.png";
                    eyeAniFileName = "SEPetBoss1%d_06.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetBoss1%d_06.png";
                    eyeAniFileName = "EPetBoss1%d_06.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_FAT_01:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_FAT_01].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggFat1%d_01.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetFat1%d_01.png";
                        eyeAniFileName = "SEPetFat1%d_01.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetFat1%d_01.png";
                    eyeAniFileName = "SEPetFat1%d_01.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetFat1%d_01.png";
                    eyeAniFileName = "EPetFat1%d_01.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_FAT_02:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_FAT_02].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggFat1%d_02.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetFat1%d_02.png";
                        eyeAniFileName = "SEPetFat1%d_02.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetFat1%d_02.png";
                    eyeAniFileName = "SEPetFat1%d_02.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetFat1%d_02.png";
                    eyeAniFileName = "EPetFat1%d_02.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_FAT_03:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_FAT_03].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggFat1%d_03.png",i);
                        
                        break;
                    }
                    
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetFat1%d_03.png";
                        eyeAniFileName = "SEPetFat1%d_03.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetFat1%d_03.png";
                    eyeAniFileName = "SEPetFat1%d_03.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetFat1%d_03.png";
                    eyeAniFileName = "EPetFat1%d_03.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_FAT_06:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_FAT_06].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggFat1%d_06.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetFat1%d_06.png";
                        eyeAniFileName = "SEPetFat1%d_06.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetFat1%d_06.png";
                    eyeAniFileName = "SEPetFat1%d_06.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetFat1%d_06.png";
                    eyeAniFileName = "EPetFat1%d_06.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_FLY_01:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_FLY_01].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggFly1%d_01.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetFly1%d_01.png";
                        eyeAniFileName = "SEPetFly1%d_01.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetFly1%d_01.png";
                    eyeAniFileName = "SEPetFly1%d_01.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetFly1%d_01.png";
                    eyeAniFileName = "EPetFly1%d_01.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_FLY_02:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_FLY_02].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggFly1%d_02.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetFly1%d_02.png";
                        eyeAniFileName = "SEPetFly1%d_02.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetFly1%d_02.png";
                    eyeAniFileName = "SEPetFly1%d_02.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetFly1%d_02.png";
                    eyeAniFileName = "EPetFly1%d_02.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_FLY_03:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_FLY_03].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggFly1%d_03.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetFly1%d_03.png";
                        eyeAniFileName = "SEPetFly1%d_03.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetFly1%d_03.png";
                    eyeAniFileName = "SEPetFly1%d_03.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetFly1%d_03.png";
                    eyeAniFileName = "EPetFly1%d_03.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_FLY_06:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_FLY_06].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggFly1%d_06.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetFly1%d_06.png";
                        eyeAniFileName = "SEPetFly1%d_06.png";                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetFly1%d_06.png";
                    eyeAniFileName = "SEPetFly1%d_06.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetFly1%d_06.png";
                    eyeAniFileName = "EPetFly1%d_06.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_LAND_01:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_LAND_01].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggLand1%d_01.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetLand1%d_01.png";
                        eyeAniFileName = "SEPetLand1%d_01.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetLand1%d_01.png";
                    eyeAniFileName = "SEPetLand1%d_01.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetLand1%d_01.png";
                    eyeAniFileName = "EPetLand1%d_01.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_LAND_02:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_LAND_02].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggLand1%d_02.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetLand1%d_02.png";
                        eyeAniFileName = "SEPetLand1%d_02.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetLand1%d_02.png";
                    eyeAniFileName = "SEPetLand1%d_02.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetLand1%d_02.png";
                    eyeAniFileName = "EPetLand1%d_02.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_LAND_03:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_LAND_03].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggLand1%d_03.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetLand1%d_03.png";
                        eyeAniFileName = "SEPetLand1%d_03.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetLand1%d_03.png";
                    eyeAniFileName = "SEPetLand1%d_03.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetLand1%d_03.png";
                    eyeAniFileName = "EPetLand1%d_03.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_LAND_06:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_LAND_06].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggLand1%d_06.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetLand1%d_06.png";
                        eyeAniFileName = "SEPetLand1%d_06.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetLand1%d_06.png";
                    eyeAniFileName = "SEPetLand1%d_06.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetLand1%d_06.png";
                    eyeAniFileName = "EPetLand1%d_06.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_LAND_2_01:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_LAND_2_01].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggLand2%d_01.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetLand2%d_01.png";
                        eyeAniFileName = "SEPetLand2%d_01.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetLand2%d_01.png";
                    eyeAniFileName = "SEPetLand2%d_01.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetLand2%d_01.png";
                    eyeAniFileName = "EPetLand2%d_01.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_LAND_2_02:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_LAND_2_02].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggLand2%d_02.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetLand2%d_02.png";
                        eyeAniFileName = "SEPetLand2%d_02.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetLand2%d_02.png";
                    eyeAniFileName = "SEPetLand2%d_02.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetLand2%d_02.png";
                    eyeAniFileName = "EPetLand2%d_02.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_LAND_2_03:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_LAND_2_03].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggLand2%d_03.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetLand2%d_03.png";
                        eyeAniFileName = "SEPetLand2%d_03.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetLand2%d_03.png";
                    eyeAniFileName = "SEPetLand2%d_03.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetLand2%d_03.png";
                    eyeAniFileName = "EPetLand2%d_03.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_LAND_2_06:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_LAND_2_06].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNest01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggLand2%d_06.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNest02.png";
                        
                        petsEggAniFileName = "SPetLand2%d_06.png";
                        eyeAniFileName = "SEPetLand2%d_06.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNest02.png";
                    
                    petsEggAniFileName = "SPetLand2%d_06.png";
                    eyeAniFileName = "SEPetLand2%d_06.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNest03.png";
                    petsEggAniFileName = "PetLand2%d_06.png";
                    eyeAniFileName = "EPetLand2%d_06.png";
                }
            }
        }
            break;
            
        case PETS_BREED_EGG_TYPE_WHALE_06:
        {
            if (breedType < PETS_EGG_BREED_STATE_TYPE_BORN) {
                for (int i = (int)(PETS_EGG_BREED_STATE_TYPE_FIRST); i < (int)(PETS_EGG_BREED_STATE_TYPE_BORN) ; i++) {
                    
                    if (breededTime <= petsEggConfigData[PETS_BREED_EGG_TYPE_WHALE_06].breedStateTime[i].breedTime)
                    {
                        
                        padFileName = "PetNestBig01.png";
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "EggWhale1%d_06.png",i);
                        
                        break;
                    }
                    else if(petsEggState > PETS_EGG_STATE_TYPE_ONLY_AN_EGG)
                    {
                        breedMin = 0;
                        breedSec = 0;
                        breedHour = 0;
                        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
                        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
                        padFileName = "PetNestBig01.png";
                        
                        petsEggAniFileName = "SPetWhale1%d_06.png";
                        eyeAniFileName = "SEPetWhale1%d_06.png";
                        break;
                    }
                }
            }
            else
            {
                if (breedType == PETS_EGG_BREED_STATE_TYPE_BORN) {
                    padFileName = "PetNestBig01.png";
                    
                    petsEggAniFileName = "SPetWhale1%d_06.png";
                    eyeAniFileName = "SEPetWhale1%d_06.png";
                }
                else if (breedType == PETS_EGG_BREED_STATE_TYPE_GROWN)
                {
                    padFileName = "PetNestBig02.png";
                    petsEggAniFileName = "PetWhale1%d_06.png";
                    eyeAniFileName = "EPetWhale1%d_06.png";
                    
                }
            }
        }
            break;
        default:
            break;
    }
    
    
    feedTotalCookieNum = petsEggConfigData[myEggType].bornFeedState[myFeedState].cookNum;
    feedTotalMilkNum = petsEggConfigData[myEggType].bornFeedState[myFeedState].milkNum;
    
    
    if (petsEggState == PETS_EGG_STATE_TYPE_ONLY_AN_EGG) {
        petsEggSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
        
        petsEggSprite->setVisible(true);
    }
    else
    {
        padSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(padFileName));
        CCSize padSize = padSprite->getContentSize();
        padSprite->setVisible(true);
        
        if (myBreedState < PETS_EGG_BREED_STATE_TYPE_BORN) {
            
            petsEggSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
            
            petsEggSprite->setVisible(true);
            
            int  breedTime = breedHour * 3600 + breedMin * 60 + breedSec;

            int TotalTime = petsEggConfigData[myEggType].breedStateTime[PETS_EGG_BREED_STATE_TYPE_THR - 1].breedTime;
            int diffTime = TotalTime - breedTime;
            int sec = 0;//diffTime % 60;
            int min = 0;//(diffTime % 3600) / 60;
            int hour = 0;//(diffTime / 3600);
            
            if (diffTime >= 0) {
                sec = diffTime % 60;
                min = (diffTime % 3600) / 60;
                hour = (diffTime / 3600);
            }
//            breedHour = breededTime / 3600;
//            breedMin = ((breededTime % 3600) / 60);
//            breedSec = ((breededTime % 3600) % 60);
            
            breedTimeBG->setVisible(true);
            
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%02d",hour);
            myBreedTimeHourLAB->setString(comBuffer);
            
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%02d",min);
            myBreedTimeMinLAB->setString(comBuffer);
            
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%02d",sec);
            myBreedTimeSecLAB->setString(comBuffer);
            
            this->scheduleUpdate();
        }
        else
        {
            breedTimeBG->setVisible(false);
            
            speechIndex = 0;
            this->petsSpeechShow();
            
            if (myBreedState == PETS_EGG_BREED_STATE_TYPE_BORN) {
                int userMilk = HUDClass::sharedHUD()->getUserMilkNum();
                int userCookieNum = HUDClass::sharedHUD()->getUserCookieNum();
                char *milkFileName = NULL;
                char *cookieFileName = NULL;
                
                if (feedTotalMilkNum <= userMilk) {
                    milkFileName = "PetMilk01.png";
                }
                else
                {
                    milkFileName = "PetMilk00.png";
                }
                
                if (feedTotalCookieNum <= userMilk) {
                    cookieFileName = "PetCookie01.png";
                }
                else
                {
                    cookieFileName = "PetCookie00.png";
                }
                
                showMilkMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(milkFileName));
                
                showMilkMenu->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(milkFileName));
                
                //showMilkMenu->setVisible(false);
                
                memset(comBuffer, 0, sizeof(comBuffer));
                if (curNeedCookieNum > 0) {
                    sprintf(comBuffer, "%d",curNeedCookieNum);
                }
                else
                {
                    sprintf(comBuffer, "%d",feedTotalMilkNum);
                }
                milkNumLab->setString(comBuffer);
                
                showCookieMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(cookieFileName));
                showCookieMenu->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(cookieFileName));
                
                //showCookieMenu->setVisible(true);
                
                memset(comBuffer, 0, sizeof(comBuffer));
                if (curNeedMilkNum > 0) {
                    sprintf(comBuffer, "%d",curNeedMilkNum);
                }
                else
                {
                    sprintf(comBuffer, "%d",feedTotalMilkNum);
                }
                cookieNumLab->setString(comBuffer);
            }
            
            CCSpriteFrame* petsBody = NULL;
            for (int i = 1; i < 4; i++) {
                memset(comBuffer, 0, sizeof(comBuffer));
                sprintf(comBuffer, petsEggAniFileName,i);
                frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer);
                comArray->addObject(frame);
                if (i == 1) {
                    petsBody = frame;
                    petsEggSprite->setDisplayFrame(frame);
                    petsEggSprite->stopAllActions();
                    petsEggSprite->setVisible(true);
                    
                }
                else if ((i == 2) && (eggType == PETS_BREED_EGG_TYPE_WHALE_06))
                {
                    comArray->removeAllObjects();
                    comArray->addObject(frame);
                    CCSize whaleSize = petsEggSprite->getContentSize();
                    whaleTail->setDisplayFrame(frame);
                    whaleTail->setPosition(ccp(whaleSize.width / 2, whaleSize.height / 2));
                    showSpeechBG_A->setPosition(ccp(whaleSize.width * 10 /100, whaleSize.height * 75 / 100));
                    showSpeechBG_B->setPosition(ccp(whaleSize.width * 67 /100, whaleSize.height * 75 / 100));
                    whaleTail->stopAllActions();
                    whaleTail->setVisible(true);
                }
                petsEggSprite->getTexture()->setAliasTexParameters();
            }
            
            if (petsBodyAni != NULL) {
                petsBodyAni->release();
            }
            
            petsBodyAni = CCAnimation::createWithSpriteFrames(comArray,0.15);
            petsBodyAni->retain();
            int timeBase = 5;
            int timeDelTaMax = 10;
            
            int waitTime = timeBase + (CCRANDOM_0_1() * timeDelTaMax);
            
            CCMoveBy* wait = CCMoveBy::create(waitTime, ccp(0, 0));
            if (myEggType == PETS_BREED_EGG_TYPE_WHALE_06) {
                whaleTail->runAction(CCSequence::create(wait,CCAnimate::create(petsBodyAni),CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsBodyAniCallBack)),NULL));
            }
            else
            {
                petsEggSprite->runAction(CCSequence::create(wait,CCAnimate::create(petsBodyAni),CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsBodyAniCallBack)),NULL));
            }
            
            comArray->removeAllObjects();
            
            for (int i = 1; i < 3; i++) {//eye ani
                memset(comBuffer, 0, sizeof(comBuffer));
                sprintf(comBuffer, eyeAniFileName,i);
                frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer);
                comArray->addObject(frame);
                
                if (i == 1) {
                    petsEyeSprite->setDisplayFrame(frame);
                    petsEyeSprite->stopAllActions();
                    petsEyeSprite->setVisible(false);
                    if (myEggType == PETS_BREED_EGG_TYPE_WHALE_06) {
                        CCSize whaleSize = petsEggSprite->getContentSize();
                        petsEyeSprite->setPosition(ccp(whaleSize.width / 2, whaleSize.height / 2));
                    }
                }
            }
            
            if (petsEyeAni != NULL) {
                petsEyeAni->release();
            }
            
            petsEyeAni = CCAnimation::createWithSpriteFrames(comArray,0.15);
            petsEyeAni->retain();
            
        }
    }
}


void PetsBreedClass::petsSpeechShow()
{
    showSpeechBG_A->setVisible(false);
    showSpeechBG_B->setVisible(false);
    showPetsSpeechA->stopAllActions();
    showPetsSpeechB->stopAllActions();
    
    int timeBase = 5;
    int timeDelTaMax = 10;
    
    int waitTime = timeBase + (CCRANDOM_0_1() * timeDelTaMax);
    int waitTime2 = 5;//timeBase + CCRANDOM_0_1() * timeDelTaMax;
    
    CCMoveBy* wait = CCMoveBy::create(waitTime, ccp(0, 0));
    CCMoveBy* wait2 = CCMoveBy::create(waitTime2, ccp(0, 0));
    
    int speech_ab = (CCRANDOM_0_1() * 2);//0-a,1-b
    int index = (CCRANDOM_0_1() * 2);
    
    if (speech_ab >= 2) {
        speech_ab = 1;
    }
    
    if (index >= 2) {
        index = 1;
    }
    
    if (myBreedState == PETS_EGG_BREED_STATE_TYPE_BORN) {
        if (myFeedState == PETS_FEED_STATE_TYPE_FIRST) {

            if (speech_ab == 0) {
                
                if (speechIndex == 0) {
                    showPetsSpeechA->runAction(CCSequence::create(wait,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
                }
                else if (speechIndex == 1){
                    showPetsSpeechA->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pets_born_speech_a[index]));
                    showSpeechBG_A->setVisible(this->randomShowSprite());
                    showPetsSpeechA->runAction(CCSequence::create(wait2,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
                }
                else if (speechIndex == 2){
                    showPetsSpeechA->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pets_born_speech_a[index]));
                    showSpeechBG_A->setVisible(this->randomShowSprite());
                    showPetsSpeechA->runAction(CCSequence::create(wait2,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
                }
                
                
            }
            else if (speech_ab == 1){
                if (speechIndex == 0) {
                    showPetsSpeechB->runAction(CCSequence::create(wait,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
                }
                else if (speechIndex == 1){
                    showPetsSpeechB->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pets_born_speech_b[index]));
                    showSpeechBG_B->setVisible(this->randomShowSprite());
                    showPetsSpeechB->runAction(CCSequence::create(wait2,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
                }
                else if (speechIndex == 2){
                    showPetsSpeechB->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pets_born_speech_b[index]));
                    showSpeechBG_B->setVisible(this->randomShowSprite());
                    showPetsSpeechB->runAction(CCSequence::create(wait2,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
                }
            }
            
        }
        else if (myFeedState == PETS_FEED_STATE_TYPE_SEC || myFeedState == PETS_FEED_STATE_TYPE_THR){
        
            
            if (speech_ab == 0) {
                
                if (speechIndex == 0) {
                    showPetsSpeechA->runAction(CCSequence::create(wait,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
                }
                else if (speechIndex == 1){
                    showPetsSpeechA->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pets_born_feeding_speech_a[index]));
                    showSpeechBG_A->setVisible(this->randomShowSprite());
                    showPetsSpeechA->runAction(CCSequence::create(wait2,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
                }
                else if (speechIndex == 2){
                    showPetsSpeechA->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pets_born_feeding_speech_a[index]));
                    showSpeechBG_A->setVisible(this->randomShowSprite());
                    showPetsSpeechA->runAction(CCSequence::create(wait2,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
                }
                
                
            }
            else if (speech_ab == 1){
                if (speechIndex == 0) {
                    showPetsSpeechB->runAction(CCSequence::create(wait,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
                }
                else if (speechIndex == 1){
                    showPetsSpeechB->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pets_born_feeding_speech_b[index]));
                    showSpeechBG_B->setVisible(this->randomShowSprite());
                    showPetsSpeechB->runAction(CCSequence::create(wait2,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
                }
                else if (speechIndex == 2){
                    showPetsSpeechB->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pets_born_feeding_speech_b[index]));
                    showSpeechBG_B->setVisible(this->randomShowSprite());
                    showPetsSpeechB->runAction(CCSequence::create(wait2,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
                }
            }
            
        
        }
        
    }
    else if (myBreedState == PETS_EGG_BREED_STATE_TYPE_GROWN){
        if (speech_ab == 0) {
            
            if (speechIndex == 0) {
                showPetsSpeechA->runAction(CCSequence::create(wait,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
            }
            else if (speechIndex == 1){
                showPetsSpeechA->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pets_grown_speech_a[index]));
                showSpeechBG_A->setVisible(this->randomShowSprite());
                showPetsSpeechA->runAction(CCSequence::create(wait2,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
            }
            else if (speechIndex == 2){
                showPetsSpeechA->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pets_grown_speech_a[index]));
                showSpeechBG_A->setVisible(this->randomShowSprite());
                showPetsSpeechA->runAction(CCSequence::create(wait2,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
            }
            
            
        }
        else if (speech_ab == 1){
            if (speechIndex == 0) {
                showPetsSpeechB->runAction(CCSequence::create(wait,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
            }
            else if (speechIndex == 1){
                showPetsSpeechB->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pets_grown_speech_b[index]));
                showSpeechBG_B->setVisible(this->randomShowSprite());
                showPetsSpeechB->runAction(CCSequence::create(wait2,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
            }
            else if (speechIndex == 2){
                showPetsSpeechB->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pets_grown_speech_b[index]));
                showSpeechBG_B->setVisible(this->randomShowSprite());
                showPetsSpeechB->runAction(CCSequence::create(wait2,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsSpeechShowCallBack)),NULL));
            }
        }
        
    }
}


void PetsBreedClass::petsSpeechShowCallBack()
{
    speechIndex++;
    if (speechIndex > 2) {
        speechIndex = 0;
    }
    this->petsSpeechShow();
}

void PetsBreedClass::showPetsEggPad()
{
//    if (petsEggState == PETS_EGG_STATE_TYPE_ONLY_AN_EGG) {
//        int nestNum = HUDClass::sharedHUD()->getUserNestNum();
//        
//        if (nestNum > 0) {
//            petsEggState = PETS_EGG_STATE_TYPE_START_BREED;
//            nestNum -= 1;
//            HUDClass::sharedHUD()->setUserNestNum(nestNum);
//            this->updateTargetFunc();
//            
//            myBreedState = PETS_EGG_BREED_STATE_TYPE_FIRST;
//            myFeedState = PETS_FEED_STATE_TYPE_FIRST;
//            curNeedMilkNum = 0;
//            curNeedCookieNum = 0;
//            breedHour = 0;
//            breedMin = 0;
//            breedSec = 0;
//            curSystemTime = system(NULL);
//            this->comSetPetsEggType(myEggType, myBreedState, curNeedCookieNum, curNeedMilkNum, 0);
//        }
//    }
//    else if (petsEggState == PETS_EGG_STATE_TYPE_START_BREED && (myBreedState >= PETS_EGG_BREED_STATE_TYPE_FIRST && myBreedState <PETS_EGG_BREED_STATE_TYPE_BORN))
//    {
//        
//    }
}

void PetsBreedClass::showOrHideFoodPad(bool flag)
{
//    if (flag) {
//        milkNumLab->setVisible(flag);
//        cookieNumLab->setVisible(flag);
//    }
    if (myBreedState == PETS_EGG_BREED_STATE_TYPE_BORN) {
        if (feedTotalMilkNum > 0) {
            showMilkMenu->setVisible(flag);
        }
        
        if (feedTotalCookieNum > 0) {
            showCookieMenu->setVisible(flag);
        }
        
        isShowFoodPad = flag;
//        speechIndex = 1;
//        this->petsSpeechShow();
    }
    else if (myBreedState == PETS_EGG_BREED_STATE_TYPE_GROWN){
        showMilkMenu->setVisible(false);
        
        showCookieMenu->setVisible(false);
        
        isShowFoodPad = false;
        
        speechIndex = 1;
        this->petsSpeechShow();
    }
}

bool PetsBreedClass::getShowOrHideFoodPad()
{
    return isShowFoodPad;
}

PETS_BREED_EGG_TYPE PetsBreedClass::getPetsEggType()
{
    return myEggType;
}

PETS_EGG_STATE_TYPE PetsBreedClass::getPetsBreedState()
{
    return petsEggState;
}


void PetsBreedClass::setPetsBreedState(PETS_EGG_STATE_TYPE type)
{
    if (type == PETS_EGG_STATE_TYPE_START_BREEDDING && petsEggState == PETS_EGG_STATE_TYPE_ONLY_AN_EGG) {
        
        petsEggState = PETS_EGG_STATE_TYPE_START_BREEDDING;
        myBreedState = PETS_EGG_BREED_STATE_TYPE_FIRST;
        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
        curNeedMilkNum = 0;
        curNeedCookieNum = 0;
        breedHour = 0;
        breedMin = 0;
        breedSec = 0;
        myBreedTime = 0;
        this->comSetPetsEggType(myEggType, myBreedState, curNeedCookieNum, curNeedMilkNum, 0);
    }
    else if ((type == PETS_EGG_STATE_TYPE_START_BORN && petsEggState == PETS_EGG_STATE_TYPE_START_BREEDDING)){
        
        this->unscheduleUpdate();
        breedHour = 0;
        breedMin = 0;
        breedSec = 0;
        myBreedTime = 0;
        petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
        myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
        myFeedState = PETS_FEED_STATE_TYPE_FIRST;
        this->petsEggBreedSuccessStartAni();
    }
}

CCSize PetsBreedClass::getPetsEggSpriteSize()
{
    return petsEggSprite->getContentSize();
}

void PetsBreedClass::petsBodyAniCallBack()
{
    //petsEggSprite->setVisible(false);
    petsEyeSprite->setVisible((this->randomShowSprite()));
    
    int timeBase = 5;
    int timeDelTaMax = 10;
    
    int waitTime = timeBase + (CCRANDOM_0_1() * timeDelTaMax);
    CCMoveBy* wait2 = CCMoveBy::create(waitTime, ccp(0, 0));
    petsEyeSprite->runAction(CCSequence::create(CCAnimate::create(petsEyeAni),CCAnimate::create(petsEyeAni),CCAnimate::create(petsEyeAni),CCAnimate::create(petsEyeAni),CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsEyeAniCallBack)),NULL));

}

void PetsBreedClass::petsEyeAniCallBack()
{
    petsEyeSprite->setVisible(false);
    petsEggSprite->stopAllActions();
    
    int timeBase = 5;
    int timeDelTaMax = 10;
    
    int waitTime = timeBase + (CCRANDOM_0_1() * timeDelTaMax);
    CCMoveBy* wait = CCMoveBy::create(waitTime, ccp(0, 0));
    if (myEggType == PETS_BREED_EGG_TYPE_WHALE_06) {
        whaleTail->runAction(CCSequence::create(wait,CCAnimate::create(petsBodyAni),wait,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsBodyAniCallBack)),NULL));
    }
    else
    {
        petsEggSprite->runAction(CCSequence::create(wait,CCAnimate::create(petsBodyAni),wait,CCCallFunc::create(this, callfunc_selector(PetsBreedClass::petsBodyAniCallBack)),NULL));
    }
    
}


void PetsBreedClass::showFoodMenuActionCallBack(cocos2d::CCObject *object)
{
    CCMenuItemImage* menuitem = (CCMenuItemImage*)object;
    
    this->showOrHideFoodPad(false);
    
    switch (menuitem->getTag()) {
        case FOOD_MENU_COOKIE_ID:
            {
                int cookieNum = HUDClass::sharedHUD()->getUserCookieNum();
                
                if (feedTotalCookieNum <= cookieNum || (curNeedCookieNum > 0 && curNeedCookieNum <= cookieNum)) {
                    if (curNeedCookieNum == 0) {
                        cookieNum -= feedTotalCookieNum;
                    }
                    else
                    {
                        cookieNum -= curNeedCookieNum;
                    }
                    
                    curNeedCookieNum = 0;
                    
                    HUDClass::sharedHUD()->setUserCookieNum(cookieNum);
                    this->updateTargetFunc();
                    myFeedState = (PETS_FEED_STATE_TYPE)(myFeedState + 1);
                    if (myFeedState >= PETS_FEED_STATE_TYPE_MAX) {
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_GROWN;
                        petsEggState = PETS_EGG_STATE_TYPE_GROWN;
                        //this->comSetPetsEggType(myEggType, myBreedState, 0, 0, 0);
                    }
                    else
                    {
                        feedTotalCookieNum = petsEggConfigData[myEggType].bornFeedState[myFeedState - 1].cookNum;
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "%d",feedTotalCookieNum);
                        int len = strlen(comBuffer);
                        
                        cookieNumLab->setPosition(ccp((showCookieMenu->getContentSize().width - 9 * len)/ 2, showCookieMenu->getContentSize().height * 15 / 100));
                        cookieNumLab->setString(comBuffer);
                        
                    }
                    
                    this->petsFeedStartAni();
                    
                    
                }
                else
                {
                    if (curNeedCookieNum == 0) {
                        curNeedCookieNum = feedTotalCookieNum - cookieNum;//还需要个数
                    }
                    else
                    {
                        curNeedCookieNum = curNeedCookieNum - cookieNum;//还需要个数
                    }
                    HUDClass::sharedHUD()->setUserCookieNum(0);
                    this->updateTargetFunc();
                    
                    
                    memset(comBuffer, 0, sizeof(comBuffer));
                    sprintf(comBuffer, "%d",curNeedCookieNum);
                    cookieNumLab->setString(comBuffer);
                    int len = strlen(comBuffer);
                    
                    cookieNumLab->setPosition(ccp((showCookieMenu->getContentSize().width - 9 * len)/ 2, showCookieMenu->getContentSize().height * 15 / 100));
                    
                    showCookieMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("PetCookie00.png"));
                    showCookieMenu->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("PetCookie00.png"));
                    
                }
            }
            break;
        case FOOD_MENU_MILK_ID:
            {
                int milkNum = HUDClass::sharedHUD()->getUserMilkNum();//hud
                
                if (feedTotalMilkNum <= milkNum || (curNeedMilkNum > 0 && curNeedMilkNum <= milkNum)) {
                    if (curNeedMilkNum == 0) {
                        milkNum -= feedTotalMilkNum;
                    }
                    else
                    {
                        milkNum -= curNeedMilkNum;
                    }
                    
                    curNeedMilkNum = 0;
                    
                    HUDClass::sharedHUD()->setUserMilkNum(milkNum);
                    this->updateTargetFunc();
                    
                    
                    myFeedState = (PETS_FEED_STATE_TYPE)(myFeedState + 1);
                    if (myFeedState >= PETS_FEED_STATE_TYPE_MAX) {//grown now
                        myBreedState = PETS_EGG_BREED_STATE_TYPE_GROWN;
                        petsEggState = PETS_EGG_STATE_TYPE_GROWN;
                        //this->comSetPetsEggType(myEggType, myBreedState, 0, 0, 0);
                    }
                    else
                    {
                        feedTotalMilkNum = petsEggConfigData[myEggType].bornFeedState[myFeedState - 1].milkNum;
                        memset(comBuffer, 0, sizeof(comBuffer));
                        sprintf(comBuffer, "%d",feedTotalMilkNum);
                        int len = strlen(comBuffer);
                        
                        milkNumLab->setPosition(ccp((showMilkMenu->getContentSize().width - 9 * len)/ 2, showMilkMenu->getContentSize().height * 15 / 100));
                        milkNumLab->setString(comBuffer);
                        
                    }
                    
                    
                    this->petsFeedStartAni();
                    
                }
                else
                {
                    if (curNeedMilkNum == 0) {
                        curNeedMilkNum = feedTotalMilkNum - milkNum;//还需要个数
                    }
                    else if (curNeedMilkNum > 0)
                    {
                        curNeedMilkNum = curNeedMilkNum - milkNum;//还需要个数
                    }
                    memset(comBuffer, 0, sizeof(comBuffer));
                    sprintf(comBuffer, "%d",curNeedMilkNum);
                    int len = strlen(comBuffer);
                    
                    milkNumLab->setPosition(ccp((showMilkMenu->getContentSize().width - 9 * len)/ 2, showMilkMenu->getContentSize().height * 15 / 100));
                    milkNumLab->setString(comBuffer);
                    
                    HUDClass::sharedHUD()->setUserMilkNum(0);
                    this->updateTargetFunc();
                    showMilkMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("PetMilk00.png"));
                    showMilkMenu->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("PetMilk00.png"));
                    
                    
                }
            }
            break;
        default:
            break;
    }
    
    
    
}

void PetsBreedClass::petsFeedStartAni()
{
    CCSize petsSize = petsEggSprite->getContentSize();
    CCArray* aniArray = CCArray::create();
    CCSprite* feedOk = CCSprite::createWithSpriteFrameName("PetBeFeed01.png");
    
    feedOk->setPosition(ccp(petsSize.width / 2, petsSize.height / 2));
    petsEggSprite->addChild(feedOk,50);
    for (int i = 1; i < 10; i++) {
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "PetBeFeed%02d.png",i);
        aniArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
    }
    
    feedOk->runAction(CCSequence::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(aniArray,0.1)),CCCallFuncN::create(this, callfuncN_selector(PetsBreedClass::petsFeedSuccessAniCallBack)),NULL));
}

void PetsBreedClass::petsEggBreedSuccessAniCallBack(cocos2d::CCNode *node)
{
    CCSprite* sprite = (CCSprite*)node;
    
    sprite->stopAllActions();
    sprite->removeFromParentAndCleanup(true);
    
    this->comSetPetsEggType(myEggType, myBreedState, 0,0,0);
    speechIndex = 0;
    this->petsSpeechShow();
}

void PetsBreedClass::petsEggBreedSuccessStartAni()
{
    CCSize petSize = petsEggSprite->getContentSize();
    CCArray* aniArray = CCArray::create();
    CCSprite* bornAni = CCSprite::createWithSpriteFrameName("PetEvolution1.png");
    
    bornAni->setPosition(ccp(petSize.width / 2, petSize.height / 2));
    petsEggSprite->addChild(bornAni,50);
    for (int i = 1; i < 4; i++) {
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "PetEvolution%d.png",i);
        aniArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
    }
    
    bornAni->runAction(CCSequence::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(aniArray,0.2)),CCCallFuncN::create(this, callfuncN_selector(PetsBreedClass::petsEggBreedSuccessAniCallBack)),NULL));
}

void PetsBreedClass::petsFeedSuccessAniCallBack(cocos2d::CCNode *node)
{
    CCSprite* sprite = (CCSprite*)node;
    
    sprite->stopAllActions();
    sprite->removeFromParentAndCleanup(true);
    
    speechIndex = 0;

    if (myBreedState == PETS_EGG_BREED_STATE_TYPE_GROWN) {//grown now
        this->comSetPetsEggType(myEggType, myBreedState, 0, 0, 0);
    }
    
    this->petsSpeechShow();
}


bool PetsBreedClass::randomShowSprite()
{
    bool isShow = false;
    
    int baseNum = CCRANDOM_0_1() * 10;
    int showNum = 3;
    int value = baseNum % showNum;
    
    if (value == 0 && baseNum != 0) {
        isShow = true;
    }
    
    return isShow;
}

void PetsBreedClass::updateTargetFunc()
{
    if (myTarget != NULL && myFunc != NULL) {
        (myTarget->*myFunc)();
    }
}


void PetsBreedClass::update(float dt)
{
    breedTimeCounter += dt;
    if (breedTimeCounter >= 1) {//1 second

        breedTimeCounter = 0;
        
        breedSec += 1;
        
        if (breedSec >= 60) {
            breedSec = 0;
            breedMin += 1;
            
            if (breedMin >= 60) {
                breedMin = 0;
                
                breedHour += 1;
                
                if (breedHour >= 24) {
                    
                }
            }
        }
        
        
        
        int  breedTime = breedHour * 3600 + breedMin * 60 + breedSec;
        int type = myEggType;
        int state = PETS_EGG_BREED_STATE_TYPE_THR;
        int TotalTime = petsEggConfigData[myEggType].breedStateTime[PETS_EGG_BREED_STATE_TYPE_THR - 1].breedTime;
        int diffTime = TotalTime - breedTime;
        
        if (diffTime < 0) {
            //egg breed over

            breedMin = 0;
            breedSec = 0;
            breedHour = 0;
            PETS_EGG_BREED_STATE_TYPE breedType = PETS_EGG_BREED_STATE_TYPE_BORN;
            
            this->unscheduleUpdate();
            
            myBreedState = PETS_EGG_BREED_STATE_TYPE_BORN;
            myFeedState = PETS_FEED_STATE_TYPE_FIRST;
            petsEggState = PETS_EGG_STATE_TYPE_START_BORN;
            
            this->petsEggBreedSuccessStartAni();
        }
        else
        {
            int sec = diffTime % 60;
            int min = (diffTime % 3600) / 60;
            int hour = (diffTime / 3600);
            
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%02d",hour);
            myBreedTimeHourLAB->setString(comBuffer);
            
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%02d",min);
            myBreedTimeMinLAB->setString(comBuffer);
            
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%02d",sec);
            myBreedTimeSecLAB->setString(comBuffer);
        }
    }
}
