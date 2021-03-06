//
//  PetsDropClass.cpp
//  CaratonFatans
//
//  Created by  Jack on 13-11-21.
//
//

#include "PetsDropClass.h"
#include "LcdAdapClass.h"
#include "GameSpriteParm.h"
#include "GameParam.h"
#include "HUDClass.h"

#define MENU_ID_GIFT    (1000)
#define MENU_ID_USER_YES    (12)

#define SPRITE_ACTION_ID_MENUMOVEBY (MENU_ID_GIFT)
#define SPRITE_ACTION_ID_SPARKSCALE  (14)



PetsDropClass::PetsDropClass()
{

}

PetsDropClass::~PetsDropClass()
{
    
}

bool PetsDropClass::init()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    myTarget = NULL;
    myFunc = NULL;
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsDrop-hd.plist");
    
    
    CCMenuItemImage* item = CCMenuItemImage::create("giftbox_small.png", "giftbox_small.png", this, menu_selector(PetsDropClass::menuBtnCallBack));
    item->setPosition(ccp(size.width / 2, size.height));
    item->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
    item->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());
    item->setTag(MENU_ID_GIFT);
    item->runAction(CCSequence::create(CCMoveBy::create(0.25, ccp(0, -size.height * 8/ 10)),CCCallFuncN::create(this, callfuncN_selector(PetsDropClass::spriteActionCallBack)),NULL));
    CCMenu* menu = CCMenu::create(item,NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu,10);
    
    
    return true;
}

PetsDropClass* PetsDropClass::create()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    PetsDropClass* drop = new PetsDropClass();
    if (drop && drop->init()) {
        drop->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(drop);
    }
    
    drop->setContentSize(size);
    
    return drop;
}

bool PetsDropClass::init(cocos2d::CCObject *target, SEL_CallFunc func)
{
    CCAssert(!(target == NULL), "cannot be NULL");
    CCAssert(!(func == NULL), "cannot be NULL");
    
    //this->init();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsDrop-hd.plist");
    
    myTarget = target;
    myFunc = func;
    
    
    
    return true;
}

PetsDropClass* PetsDropClass::create(cocos2d::CCObject *target, SEL_CallFunc func)
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    PetsDropClass* drop = new PetsDropClass();
    if (drop && drop->init(target,func)) {
        drop->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(drop);
    }
    
    drop->setContentSize(size);
    
    return drop;
}


void PetsDropClass::showWaleGift()
{
    char* pFileName = "icon_egg.png";
    char* pFileCNName = "text_egg_CN.png";
    char* eggFileName = "Icon_EggWhale11_06.png";
    int scoreNum = 1;
    
    HUDClass::sharedHUD()->addPetsEggByType(PETS_BREED_EGG_TYPE_WHALE_06);
    this->showGift(pFileName, pFileCNName, eggFileName, scoreNum);
}

char* PetsDropClass::generateGiftsEggType(void)
{
    char *pfileName = NULL;
    
//    int maxValue = (int)PETS_DROP_GIFT_EGG_TYPE_MAX - 1;
//    PETS_DROP_GIFT_EGG_TYPE eggType = (PETS_DROP_GIFT_EGG_TYPE)(CCRANDOM_0_1() * maxValue);
//    if (eggType >= PETS_DROP_GIFT_EGG_TYPE_MAX) {
//        eggType = (PETS_DROP_GIFT_EGG_TYPE)(PETS_DROP_GIFT_EGG_TYPE_MAX - 1);
//    }
    
    int validIndex = 0;
    int maxNum = PETS_BREED_EGG_TYPE_MAX - 1;
    int eggBuffer[PETS_BREED_EGG_TYPE_MAX] = {0};  //鲸鱼蛋必须打死鲸鱼才有
    PETS_BREED_EGG_TYPE breedEggType = PETS_BREED_EGG_TYPE_LAND_01;
    
    
    for (int i = 0; i < maxNum; i++) {
        breedEggType = (PETS_BREED_EGG_TYPE)(PETS_BREED_EGG_TYPE_LAND_01 + i);
        userPetDataStruct petInfo = HUDClass::sharedHUD()->getUserPetInfo(breedEggType);
        if (petInfo.eggState == PETS_EGG_STATE_TYPE_NONE) {
            eggBuffer[validIndex] = breedEggType;
            validIndex++;
        }
    }
    
    int randomIndex = CCRANDOM_0_1() * validIndex;
    
    if (randomIndex > 0) {
        randomIndex -= 1;
    }
    
    breedEggType = (PETS_BREED_EGG_TYPE)eggBuffer[randomIndex];
    HUDClass::sharedHUD()->addPetsEggByType(breedEggType);
    
    switch (breedEggType) {
        case PETS_BREED_EGG_TYPE_BOSS_01:
            pfileName = "Icon_EggBoss11_01.png";
            
            break;
        case PETS_BREED_EGG_TYPE_BOSS_02:
            pfileName = "Icon_EggBoss11_02.png";

            break;
        case PETS_BREED_EGG_TYPE_BOSS_03:
            pfileName = "Icon_EggBoss11_03.png";

            break;
        case PETS_BREED_EGG_TYPE_BOSS_06:
            pfileName = "Icon_EggBoss11_06.png";

            break;
        case PETS_BREED_EGG_TYPE_FAT_01:
            pfileName = "Icon_EggFat11_01.png";

            break;
        case PETS_BREED_EGG_TYPE_FAT_02:
            pfileName = "Icon_EggFat11_02.png";

            break;
        case PETS_BREED_EGG_TYPE_FAT_03:
            pfileName = "Icon_EggFat11_03.png";

            break;
        case PETS_BREED_EGG_TYPE_FAT_06:
            pfileName = "Icon_EggFat11_06.png";

            break;
        case PETS_BREED_EGG_TYPE_FLY_01:
            pfileName = "Icon_EggFly11_01.png";

            break;
        case PETS_BREED_EGG_TYPE_FLY_02:
            pfileName = "Icon_EggFly11_02.png";

            break;
        case PETS_BREED_EGG_TYPE_FLY_03:
            pfileName = "Icon_EggFly11_03.png";

            break;
        case PETS_BREED_EGG_TYPE_FLY_06:
            pfileName = "Icon_EggFlay11_06.png";

            break;
        case PETS_BREED_EGG_TYPE_LAND_01:
            pfileName = "Icon_EggLand11_01.png";

            break;
        case PETS_BREED_EGG_TYPE_LAND_02:
            pfileName = "Icon_EggLand11_02.png";

            break;
        case PETS_BREED_EGG_TYPE_LAND_03:
            pfileName = "Icon_EggLand11_03.png";

            break;
        case PETS_BREED_EGG_TYPE_LAND_06:
            pfileName = "Icon_EggLand11_06.png";

            break;
        case PETS_BREED_EGG_TYPE_LAND_2_01:
            pfileName = "Icon_EggLand21_01.png";

            break;
        case PETS_BREED_EGG_TYPE_LAND_2_02:
            pfileName = "Icon_EggLand21_02.png";

            break;
        case PETS_BREED_EGG_TYPE_LAND_2_03:
            pfileName = "Icon_EggLand21_03.png";

            break;
        case PETS_BREED_EGG_TYPE_LAND_2_06:
            pfileName = "Icon_EggLand21_06.png";

            break;
        case PETS_BREED_EGG_TYPE_WHALE_06:
            pfileName = "Icon_EggWhale11_06.png";
            
            break;
        default:
            break;
    }
    
    if (pfileName != NULL) {
        return pfileName;
    }
}

void PetsDropClass::generateGiftsType()
{
    char *pFileName = NULL;
    char *pFileCNName = NULL;
    char *eggFileName = {0};
//    int maxValue = (int)PETS_DROP_GIFT_TYPE_MAX - 1;
//    PETS_DROP_GIFT_TYPE giftType = (PETS_DROP_GIFT_TYPE)(CCRANDOM_0_1() * maxValue + 1);
//    if (giftType >= PETS_DROP_GIFT_TYPE_MAX) {
//        giftType = (PETS_DROP_GIFT_TYPE)(PETS_DROP_GIFT_TYPE_MAX - 1);
//    }
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();

    int userCookieNum = HUDClass::sharedHUD()->getUserCookieNum();
    int userMilkNum = HUDClass::sharedHUD()->getUserMilkNum();
    int userMedicineNum = HUDClass::sharedHUD()->getUserMedicineNum();
    
    int userPetNum = HUDClass::sharedHUD()->getUserPetsNum();
    int userBigNestNum = HUDClass::sharedHUD()->getUserBigNestNum();
    int userNestNum = HUDClass::sharedHUD()->getUserNestNum();
    int giftBuffer[PETS_DROP_GIFT_TYPE_MAX] = {0};
    int index = 0;
    int scoreNum = 0;
    
    giftBuffer[0] = PETS_DROP_GIFT_TYPE_COOKIE;
    giftBuffer[1] = PETS_DROP_GIFT_TYPE_MEDICINE;
    giftBuffer[2] = PETS_DROP_GIFT_TYPE_MILK;
    index = 3;
    if (userBigNestNum < USER_BIG_NEST_NUM_MAX) {
        giftBuffer[3] = PETS_DROP_GIFT_TYPE_BIGNEST;
        index++;
        if (userPetNum < USER_PET_NUM_MAX){
            giftBuffer[4] = PETS_DROP_GIFT_TYPE_EGG;
            index++;
            if (userNestNum < USER_NEST_NUM_MAX){
                giftBuffer[5] = PETS_DROP_GIFT_TYPE_NEST;
                index++;
            }
        }
        else if (userNestNum < USER_NEST_NUM_MAX){
            giftBuffer[4] = PETS_DROP_GIFT_TYPE_NEST;
            index++;
        }
    }
    else if (userPetNum < USER_PET_NUM_MAX){
        giftBuffer[3] = PETS_DROP_GIFT_TYPE_EGG;
        index++;
        if (userNestNum < USER_NEST_NUM_MAX){
            giftBuffer[4] = PETS_DROP_GIFT_TYPE_NEST;
            index++;
        }
    }
    else if (userNestNum < USER_NEST_NUM_MAX){
        giftBuffer[3] = PETS_DROP_GIFT_TYPE_NEST;
        index++;
    }

    PETS_DROP_GIFT_TYPE giftType = PETS_DROP_GIFT_TYPE_NONE;
    int giftIndex = (CCRANDOM_0_1() * index);
    
    if (giftIndex > 0) {
        giftIndex -= 1;
    }
    giftType = (PETS_DROP_GIFT_TYPE)giftBuffer[giftIndex];
    
    if (giftType == PETS_DROP_GIFT_TYPE_MILK || giftType == PETS_DROP_GIFT_TYPE_COOKIE || giftType == PETS_DROP_GIFT_TYPE_MEDICINE) {
        
        scoreNum = CCRANDOM_0_1() * 20 + 1;
    }
    else if(giftType == PETS_DROP_GIFT_TYPE_NEST || giftType == PETS_DROP_GIFT_TYPE_BIGNEST)
    {
        scoreNum = 1;
    }
    
    
    switch (giftType) {
        case PETS_DROP_GIFT_TYPE_BIGNEST:
            pFileName = "icon_bignest.png";
            pFileCNName = "text_bignest_CN.png";
            userBigNestNum += 1;//scoreNum;
            HUDClass::sharedHUD()->setUserBigNestNum(userBigNestNum);
            break;
        case PETS_DROP_GIFT_TYPE_COOKIE:
            pFileName = "icon_cookie.png";
            pFileCNName = "text_cookie_CN.png";
            userCookieNum += scoreNum;
            HUDClass::sharedHUD()->setUserCookieNum(userCookieNum);
            break;
        case PETS_DROP_GIFT_TYPE_EGG:
            pFileName = "icon_egg.png";
            pFileCNName = "text_egg_CN.png";
            eggFileName =  this->generateGiftsEggType();
            break;
        case PETS_DROP_GIFT_TYPE_MEDICINE:
            pFileName = "icon_medicine.png";
            pFileCNName = "text_medicine_CN.png";
            userMedicineNum += scoreNum;
            HUDClass::sharedHUD()->setUserMedicineNum(userMedicineNum);
            break;
        case PETS_DROP_GIFT_TYPE_MILK:
            pFileName = "icon_milk.png";
            pFileCNName = "text_milk_CN.png";
            userMilkNum += scoreNum;
            HUDClass::sharedHUD()->setUserMilkNum(userMilkNum);
            break;
        case PETS_DROP_GIFT_TYPE_NEST:
            pFileName = "icon_nest.png";
            pFileCNName = "text_nest_CN.png";
            userNestNum += scoreNum;
            HUDClass::sharedHUD()->setUserNestNum(userNestNum);
            break;
            
        default:
            break;
    }
    
//    ccColor4B color;
//    
//    color.a = 255;
//    color.r = 60;
//    color.g = 60;
//    color.b = 60;
//    
//    CCLayerColor::initWithColor(color);
    
    this->showGift(pFileName, pFileCNName, eggFileName, scoreNum);

//    CCSprite* rewardbg = CCSprite::createWithSpriteFrameName("reward_bg.png");
//    rewardbg->setPosition(ccp(size.width /2, size.height / 2));
//    rewardbg->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
//    rewardbg->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());
//    CCSize rewardbgSize = rewardbg->getContentSize();
//    this->addChild(rewardbg,3);
//    
//    CCSprite* giftBg = CCSprite::createWithSpriteFrameName(pFileName);
//    giftBg->setPosition(ccp(rewardbgSize.width * 3 / 10, rewardbgSize.height / 2));
//    rewardbg->addChild(giftBg,1);
//    
//    CCSprite* gifText = CCSprite::createWithSpriteFrameName(pFileCNName);
//    gifText->setPosition(ccp(rewardbgSize.width * 63/ 100, rewardbgSize.height * 68/ 100));
//    rewardbg->addChild(gifText,2);
//    
//    CCMenuItemImage* item = CCMenuItemImage::create("ok_normal_CN.png", "ok_pressed_CN.png", this, menu_selector(PetsDropClass::menuBtnCallBack));
//    item->setPosition(ccp(rewardbgSize.width * 58 / 100, rewardbgSize.height * 33 /100));
//    item->setTag(MENU_ID_USER_YES);
//    CCMenu* menu = CCMenu::create(item,NULL);
//    menu->setPosition(CCPointZero);
//    rewardbg->addChild(menu,3);
//    
//    if (eggFileName != NULL) {
//        CCSprite* egg = CCSprite::createWithSpriteFrameName(eggFileName);
//        CCAssert(!(egg == NULL), "cannot be NULL");
//        egg->setPosition(ccp(rewardbgSize.width * 3 / 10, rewardbgSize.height / 2));
//        rewardbg->addChild(egg,4);
//    }
//    else
//    {
//        char buffer[5] = {0};
//        
//        CCSprite* addX = CCSprite::createWithSpriteFrameName("x.png");
//        addX->setPosition(ccp(rewardbgSize.width * 26 /100, rewardbgSize.height * 31 / 100));
//        rewardbg->addChild(addX,5);
//        
//        sprintf(buffer, "%d",scoreNum);
//        
//        CCLabelAtlas* textNum = CCLabelAtlas::create(buffer, "Themes/Pets/icon_num.png", 17, 26, 46);
//        textNum->setPosition(ccp(rewardbgSize.width * 31 / 100, rewardbgSize.height * 25 /100));
//        rewardbg->addChild(textNum,6);
//    }
//    
//    CCSprite* spark = CCSprite::createWithSpriteFrameName("spark.png");
//    spark->setPosition(ccp(size.width / 2, size.height / 2));
//    CCSize sparkSize = spark->getContentSize();
//    //spark->setRotation(30 * i);
//    float maxLcdValue = MAX(size.width, size.height);
//    spark->setScaleX((maxLcdValue/ sparkSize.width) * 1.5);
//    spark->setScaleY((maxLcdValue / sparkSize.height) * 1.5);
//    this->addChild(spark,1);
//    
//    
//    spark->runAction(CCRepeatForever::create(CCRotateBy::create(1, 30)));
}

void PetsDropClass::showGift(char *pFileName, char *pFileCNName, char *eggFileName, int scoreNum)
{
    CCAssert(!(pFileName == NULL), "cannot be NULL");
    CCAssert(!(pFileCNName == NULL), "cannot be NULL");
    
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    
    CCSprite* rewardbg = CCSprite::createWithSpriteFrameName("reward_bg.png");
    rewardbg->setPosition(ccp(size.width /2, size.height / 2));
    rewardbg->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
    rewardbg->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());
    CCSize rewardbgSize = rewardbg->getContentSize();
    this->addChild(rewardbg,3);
    
    CCSprite* giftBg = CCSprite::createWithSpriteFrameName(pFileName);
    giftBg->setPosition(ccp(rewardbgSize.width * 3 / 10, rewardbgSize.height / 2));
    rewardbg->addChild(giftBg,1);
    
    CCSprite* gifText = CCSprite::createWithSpriteFrameName(pFileCNName);
    gifText->setPosition(ccp(rewardbgSize.width * 63/ 100, rewardbgSize.height * 68/ 100));
    rewardbg->addChild(gifText,2);
    
    CCMenuItemImage* item = CCMenuItemImage::create("ok_normal_CN.png", "ok_pressed_CN.png", this, menu_selector(PetsDropClass::menuBtnCallBack));
    item->setPosition(ccp(rewardbgSize.width * 58 / 100, rewardbgSize.height * 33 /100));
    item->setTag(MENU_ID_USER_YES);
    CCMenu* menu = CCMenu::create(item,NULL);
    menu->setPosition(CCPointZero);
    rewardbg->addChild(menu,3);
    
    if (eggFileName != NULL) {
        CCSprite* egg = CCSprite::createWithSpriteFrameName(eggFileName);
        CCAssert(!(egg == NULL), "cannot be NULL");
        egg->setPosition(ccp(rewardbgSize.width * 3 / 10, rewardbgSize.height / 2));
        rewardbg->addChild(egg,4);
    }
    else
    {
        char buffer[5] = {0};
        
        CCSprite* addX = CCSprite::createWithSpriteFrameName("x.png");
        addX->setPosition(ccp(rewardbgSize.width * 27 /100, rewardbgSize.height * 31 / 100));
        rewardbg->addChild(addX,5);
        
        sprintf(buffer, "%d",scoreNum);
        
        CCLabelAtlas* textNum = CCLabelAtlas::create(buffer, "Themes/Pets/icon_num.png", 17, 26, 46);
        textNum->setPosition(ccp(rewardbgSize.width * 30 / 100, rewardbgSize.height * 25 /100));
        rewardbg->addChild(textNum,6);
    }
    
    CCSprite* spark = CCSprite::createWithSpriteFrameName("spark.png");
    spark->setPosition(ccp(size.width / 2, size.height / 2));
    CCSize sparkSize = spark->getContentSize();
    //spark->setRotation(30 * i);
    float maxLcdValue = MAX(size.width, size.height);
    spark->setScaleX((maxLcdValue/ sparkSize.width) * 1.5);
    spark->setScaleY((maxLcdValue / sparkSize.height) * 1.5);
    this->addChild(spark,1);
    
    
    spark->runAction(CCRepeatForever::create(CCRotateBy::create(1, 30)));
}

void PetsDropClass::menuBtnCallBack(cocos2d::CCObject *object)
{
    CCMenuItemImage* menuItem = (CCMenuItemImage*)object;
    
    switch (menuItem->getTag()) {
        case MENU_ID_GIFT:
            {
                CCSprite* spark_s = CCSprite::createWithSpriteFrameName("spark_s.png");
                spark_s->setPosition(menuItem->getPosition());
                spark_s->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
                spark_s->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());
                this->addChild(spark_s,2);
                CCScaleBy* scaleby = CCScaleBy::create(0.25, 5);
                spark_s->setTag(SPRITE_ACTION_ID_SPARKSCALE);
                spark_s->runAction(CCSequence::create(scaleby,CCCallFuncN::create(this, callfuncN_selector(PetsDropClass::spriteActionCallBack)),NULL));
                
                menuItem->removeAllChildrenWithCleanup(true);
            }
            break;
        case MENU_ID_USER_YES:
            {
                if (myTarget != NULL && myFunc != NULL) {
                    (myTarget->*myFunc)();
                }
                
                this->removeFromParentAndCleanup(true);
            }
            break;
        default:
            break;
    }
}

void PetsDropClass::spriteActionCallBack(cocos2d::CCNode *object)
{
    CCSprite* sprite = (CCSprite*)object;
    
    switch (sprite->getTag()) {
        case SPRITE_ACTION_ID_MENUMOVEBY:
            {
                CCSize spriteSize = sprite->getContentSize();
                CCMoveBy* wait = CCMoveBy::create(2, ccp(0, 0));
                CCMoveBy* mby1 = CCMoveBy::create(0.1, ccp(0, spriteSize.height * 1));
                CCActionInterval* mby2 = mby1->reverse();
                sprite->runAction(CCRepeatForever::create(CCSequence::create(wait,mby1,mby2,NULL)));
            }
            break;
        case SPRITE_ACTION_ID_SPARKSCALE:
            {
                sprite->removeFromParentAndCleanup(true);
                this->generateGiftsType();
            }
            break;
        default:
            break;
    }
}

