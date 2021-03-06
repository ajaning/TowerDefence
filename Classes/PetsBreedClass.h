//
//  PetsBreedClass.h
//  CaratonFatans
//
//  Created by  Jack on 13-11-25.
//
//

#ifndef __CaratonFatans__PetsBreedClass__
#define __CaratonFatans__PetsBreedClass__

#include <iostream>
#include "cocos2d.h"
#include "GameSpriteParm.h"
USING_NS_CC;



class PetsBreedClass:public CCNode
{
private:
    PetsBreedClass();
    ~PetsBreedClass();
    bool init(PETS_BREED_EGG_TYPE eggType, PETS_EGG_BREED_STATE_TYPE breedType,int feededCookieNum,int feededMilkNum,int breededTime);
    static PetsBreedClass* create(PETS_BREED_EGG_TYPE eggType, PETS_EGG_BREED_STATE_TYPE breedType,int feededCookieNum,int feededMilkNum,int breededTime);//breedType means breed state,breededtime means 已经培育的时间
    
    void initSprite();
    
    bool init(userPetDataStruct petInfo);
    bool init(userPetDataStruct petInfo,CCObject* target,SEL_CallFunc func);
    
    void comSetPetsEggType(PETS_BREED_EGG_TYPE eggType, PETS_EGG_BREED_STATE_TYPE breedType,int feededCookieNum,int feededMilkNum,int breededTime);
    
    
    void petsEggBreedSuccessStartAni();
    void petsEggBreedSuccessAniCallBack(CCNode* node);
    
    void petsFeedStartAni();
    void petsFeedSuccessAniCallBack(CCNode* node);
    
    void showFoodMenuActionCallBack(CCObject* object);
    
    void petsBodyAniCallBack();
    void petsEyeAniCallBack();
    
    
    void petsSpeechShow();
    void petsSpeechShowCallBack();
    
    bool randomShowSprite();
    
    void updateTargetFunc();
    
    void showPetsEggPad();
    
    
    virtual void update(float dt);
public:
    //CREATE_FUNC(PetsBreedClass);
    
    static PetsBreedClass* create(userPetDataStruct petInfo);
    static PetsBreedClass* create(userPetDataStruct petInfo,CCObject* target,SEL_CallFunc func);

    CCSize getPetsEggSpriteSize();
    void showOrHideFoodPad(bool flag);//false-hide,true-show
    bool getShowOrHideFoodPad();
    
    void setPetsBreedState(PETS_EGG_STATE_TYPE type);
    PETS_EGG_STATE_TYPE getPetsBreedState();
    
    PETS_BREED_EGG_TYPE getPetsEggType();
private:
    
    bool isShowFoodPad;
    
    
    int curNeedCookieNum;//还需要饼干数目
    int curNeedMilkNum;//还需要牛奶数目
    int feedTotalCookieNum;//在当前喂养状态总共需要的饼干数量
    int feedTotalMilkNum;//在当前喂养状态总共需要的牛奶数量
    
    int myBreedTime;
    
    float breedTimeCounter;
    
    int breedHour;//已经哺育的时间
    int breedMin;
    int breedSec;
    
    CCSprite* whaleTail;
    
    CCObject* myTarget;
    SEL_CallFunc myFunc;
    
    PETS_EGG_STATE_TYPE petsEggState;//判定当前蛋的状态，就是判断有无窝
    
    PETS_BREED_EGG_TYPE myEggType;
    PETS_EGG_BREED_STATE_TYPE myBreedState;
    
    PETS_FEED_STATE_TYPE myFeedState;
    
    CCLabelAtlas* cookieNumLab;
    CCLabelAtlas* milkNumLab;
    CCMenuItemImage* showCookieMenu;
    CCMenuItemImage* showMilkMenu;
    
    CCSprite* breedTimeBG;//breed time background
    CCLabelAtlas* myBreedTimeHourLAB;//
    CCLabelAtlas* myBreedTimeMinLAB;//
    CCLabelAtlas* myBreedTimeSecLAB;//
    
    CCAnimation* petsBodyAni;
    CCAnimation* petsEyeAni;
    
    CCSprite* petsEyeSprite;//
    CCSprite* petsEggSprite;
    CCSprite* padSprite;//孵化的窝随蛋的孵化程度而改变
    
    int speechIndex;
    CCSprite* showSpeechBG_A;
    CCSprite* showSpeechBG_B;
    CCSprite* showPetsSpeechA;
    CCSprite* showPetsSpeechB;
    
};

#endif /* defined(__CaratonFatans__PetsBreedClass__) */
