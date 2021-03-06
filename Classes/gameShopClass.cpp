//
//  gameShopClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-12-25.
//
//

#include "gameShopClass.h"
#include "LcdAdapClass.h"
#include "HUDClass.h"

#define GAME_SHOP_MENU_TAG_BUY_COOKIE  (5)

#define GAME_SHOP_MENU_TAG_BUY_MILK  (10)
#define GAME_SHOP_MENU_TAG_BUY_MEDICINE  (15)
#define GAME_SHOP_MENU_TAG_BUY_NEST  (25)
#define GAME_SHOP_MENU_TAG_BUY_EGG  (35)
#define GAME_SHOP_MENU_TAG_CLOSE  (45)


#define GAME_SHOP_MILK_NEED_STONE_NUM   (1)
#define GAME_SHOP_COOKIE_NEED_STONE_NUM   (1)
#define GAME_SHOP_MEDICINE_NEED_STONE_NUM   (2)
#define GAME_SHOP_NEST_NEED_STONE_NUM   (8)
#define GAME_SHOP_EGG_NEED_STONE_NUM   (8)


static char comBuffer[255] = {0};

gameShopClass::gameShopClass()
{
    gameShopBgSprite = NULL;
    userStoneNum = 0;
    userStoneNumLab = NULL;
}


gameShopClass::~gameShopClass()
{
    
}

bool gameShopClass::init()
{
    LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(this);
    return true;
}

bool gameShopClass::init(cocos2d::CCObject *target, cocos2d::SEL_CallFunc func)
{
    CCAssert(!(target == NULL), "invalid");
    CCAssert(!(func == NULL), "invalid");
    
    this->init();
    myTarget = target;
    myFunc = func;
    return true;
}


gameShopClass* gameShopClass::create(cocos2d::CCObject *target, SEL_CallFunc func)
{
    gameShopClass* shop = new gameShopClass();
    
    if (shop && shop->init(target, func)) {
        shop->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(shop);
    }
    
    return shop;
}

void gameShopClass::loadResAndInit()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsShopAndroid-hd.plist");
    
    gameShopBgSprite = CCSprite::createWithSpriteFrameName("shop_mainbg.png");
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(gameShopBgSprite, ccp(size.width/2.0, size.height/2.0));
    CCSize bgSize = gameShopBgSprite->getContentSize();
    this->addChild(gameShopBgSprite,1);
    
    userStoneNum = HUDClass::sharedHUD()->getUserStoneNum();
    userStoneNum = 100;
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%d",userStoneNum);
    
    userStoneNumLab = CCLabelAtlas::create(comBuffer, "Themes/Pets/mystone_num.png", 13, 26, 46);
    userStoneNumLab->setPosition(ccp(bgSize.width/2.0, bgSize.height * 72/100.0));
    gameShopBgSprite->addChild(userStoneNumLab,10);
    
    
    CCArray* menuArray = CCArray::create();
    
    for (int i = 0; i < 5; i++) {
        CCMenuItemImage* menuItem = CCMenuItemImage::create("exchange_normal.png", "exchange_pressed.png", this, menu_selector(gameShopClass::menuActionCallBack));
        menuItem->setPosition(ccp((bgSize.width * (i * 16.5 + 17.5)) / 100.0, bgSize.height * 7 /100.0));
        
        switch (i) {
            case 0:
                menuItem->setTag(GAME_SHOP_MENU_TAG_BUY_COOKIE);
                cookieBuyMenu = menuItem;
                break;
            case 1:
                menuItem->setTag(GAME_SHOP_MENU_TAG_BUY_MILK);
                milkBuyMenu = menuItem;
                break;
            case 2:
                menuItem->setTag(GAME_SHOP_MENU_TAG_BUY_MEDICINE);
                medicineBuyMenu = menuItem;
                break;
            case 3:
                menuItem->setTag(GAME_SHOP_MENU_TAG_BUY_NEST);
                nestBuyMenu = menuItem;
                break;
            case 4:
                menuItem->setTag(GAME_SHOP_MENU_TAG_BUY_EGG);
                eggBuyMenu = menuItem;
                break;
                
            default:
                break;
        }
        
        menuArray->addObject(menuItem);
    }
    
    CCMenuItemImage* closeItem = CCMenuItemImage::create("shop_close_normal.png", "shop_close_pressed.png", this, menu_selector(gameShopClass::menuActionCallBack));
    closeItem->setPosition(ccp(bgSize.width * 92/ 100.0, bgSize.height * 94 /100.0));
    closeItem->setTag(GAME_SHOP_MENU_TAG_CLOSE);
    menuArray->addObject(closeItem);
    
    
    
    CCMenu* menu = CCMenu::createWithArray(menuArray);
    menu->setPosition(CCPointZero);
    gameShopBgSprite->addChild(menu,5);
    
    
    this->updateMenuBuyState();
    
    
}

void gameShopClass::onEnter()
{
    CCLayer::onEnter();
    this->loadResAndInit();
}

void gameShopClass::onExit()
{
    CCLayer::onExit();
}

void gameShopClass::updateMenuBuyState()
{
    char* disablePNG = "exchange_disable.png";
    char* normalPNG = "exchange_normal.png";
    char* pressedPNG = "exchange_pressed.png";
    
    
    if (userStoneNum < GAME_SHOP_COOKIE_NEED_STONE_NUM) {
        cookieBuyMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(disablePNG));
        cookieBuyMenu->setEnabled(false);
    }
    else if(userStoneNum >= GAME_SHOP_COOKIE_NEED_STONE_NUM)
    {
        cookieBuyMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalPNG));
        cookieBuyMenu->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pressedPNG));
        cookieBuyMenu->setEnabled(true);
    }
    
    if (userStoneNum < GAME_SHOP_MILK_NEED_STONE_NUM) {
        milkBuyMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(disablePNG));
        milkBuyMenu->setEnabled(false);
    }
    else if(userStoneNum >= GAME_SHOP_MILK_NEED_STONE_NUM)
    {
        milkBuyMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalPNG));
        milkBuyMenu->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pressedPNG));
        milkBuyMenu->setEnabled(true);
    }
    
    if (userStoneNum < GAME_SHOP_MEDICINE_NEED_STONE_NUM) {
        medicineBuyMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(disablePNG));
        medicineBuyMenu->setEnabled(false);
    }
    else if(userStoneNum >= GAME_SHOP_MEDICINE_NEED_STONE_NUM)
    {
        medicineBuyMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalPNG));
        medicineBuyMenu->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pressedPNG));
        medicineBuyMenu->setEnabled(true);
    }
    
    if (userStoneNum < GAME_SHOP_NEST_NEED_STONE_NUM) {
        nestBuyMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(disablePNG));
        nestBuyMenu->setEnabled(false);
    }
    else if(userStoneNum >= GAME_SHOP_NEST_NEED_STONE_NUM)
    {
        nestBuyMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalPNG));
        nestBuyMenu->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pressedPNG));
        nestBuyMenu->setEnabled(true);
    }
    
    if (userStoneNum < GAME_SHOP_EGG_NEED_STONE_NUM) {
        eggBuyMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(disablePNG));
        eggBuyMenu->setEnabled(false);
    }
    else if(userStoneNum >= GAME_SHOP_EGG_NEED_STONE_NUM)
    {
        eggBuyMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalPNG));
        eggBuyMenu->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pressedPNG));
        eggBuyMenu->setEnabled(true);
    }
}


void gameShopClass::menuActionCallBack(cocos2d::CCObject *object)
{
    CCMenuItemImage* menuItem = (CCMenuItemImage*)object;
    int valueNum = 0;
    
    
    switch (menuItem->getTag()) {
        case GAME_SHOP_MENU_TAG_BUY_COOKIE:
            {
                if (userStoneNum >= GAME_SHOP_COOKIE_NEED_STONE_NUM) {
                    userStoneNum -= GAME_SHOP_COOKIE_NEED_STONE_NUM;
                    valueNum = HUDClass::sharedHUD()->getUserCookieNum();
                    valueNum += 35;
                    HUDClass::sharedHUD()->setUserCookieNum(valueNum);
                    cookieBuyMenu->setEnabled(false);
                    this->showBuySuccessTips("成功兑换35个饼干");
                }
            }
            break;
        case GAME_SHOP_MENU_TAG_BUY_MILK:
            {
                if (userStoneNum >= GAME_SHOP_MILK_NEED_STONE_NUM) {
                    userStoneNum -= GAME_SHOP_MILK_NEED_STONE_NUM;
                    
                    valueNum = HUDClass::sharedHUD()->getUserMilkNum();
                    valueNum += 10;
                    HUDClass::sharedHUD()->setUserMilkNum(valueNum);
                    milkBuyMenu->setEnabled(false);
                    this->showBuySuccessTips("成功兑换10颗牛奶");
                }
            }
            break;
        case GAME_SHOP_MENU_TAG_BUY_MEDICINE:
            {
                if (userStoneNum >= GAME_SHOP_MEDICINE_NEED_STONE_NUM) {
                    userStoneNum -= GAME_SHOP_MEDICINE_NEED_STONE_NUM;

                    valueNum = HUDClass::sharedHUD()->getUserMedicineNum();
                    valueNum += 1;
                    HUDClass::sharedHUD()->setUserMedicineNum(valueNum);

                    medicineBuyMenu->setEnabled(false);
                    this->showBuySuccessTips("成功兑换一个大力丸");
                }
            }
            break;
        case GAME_SHOP_MENU_TAG_BUY_NEST:
            {
                if (userStoneNum >= GAME_SHOP_NEST_NEED_STONE_NUM) {
                    userStoneNum -= GAME_SHOP_NEST_NEED_STONE_NUM;
                    
                    valueNum = HUDClass::sharedHUD()->getUserNestNum();
                    valueNum += 1;
                    HUDClass::sharedHUD()->setUserNestNum(valueNum);
                    nestBuyMenu->setEnabled(false);
                    this->showBuySuccessTips("成功兑换一个窝");
                }
            }
            break;
        case GAME_SHOP_MENU_TAG_BUY_EGG:
            {
                if (userStoneNum >= GAME_SHOP_EGG_NEED_STONE_NUM) {
                    userStoneNum -= GAME_SHOP_EGG_NEED_STONE_NUM;
                                        
                    this->generateEggType();
                    eggBuyMenu->setEnabled(false);
                    this->showBuySuccessTips("恭喜获得神秘的蛋");
                }
            }
            break;
        case GAME_SHOP_MENU_TAG_CLOSE:
            {
                if (myTarget != NULL) {
                    (myTarget->*myFunc)();
                }
                
                this->removeFromParentAndCleanup(true);
                return;
            }
            break;
        default:
            break;
    }
    
    if (userStoneNum < 0) {
        userStoneNum = 0;
    }
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%d",userStoneNum);
    userStoneNumLab->setString(comBuffer);
    this->updateMenuBuyState();
}

void gameShopClass::generateEggType()
{
    char *pfileName = NULL;
    
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

}

void gameShopClass::showBuySuccessTips(char *showText)
{
    
    CCSprite* showTips = CCSprite::createWithSpriteFrameName("buycheck_bg.png");
    
    showTips->setPosition(ccp(gameShopBgSprite->getContentSize().width/2.0, gameShopBgSprite->getContentSize().height/2.0));
    
    showTips->setScale(0.1);
    
    CCLabelTTF* text = NULL;
    
    if (showText == NULL) {
        text = CCLabelTTF::create("兑换物品成功", "Arial", 24);
    }
    else
    {
        text = CCLabelTTF::create(showText, "Arial", 24);
    }
    
    text->setPosition(ccp(showTips->getContentSize().width * 60 /100.0, showTips->getContentSize().height /2.0));
    text->setHorizontalAlignment(kCCTextAlignmentCenter);
    
    ccColor3B color;
    color.r = 255;
    color.g = 0;
    color.b = 0;
    
    text->setFontFillColor(color);
    showTips->addChild(text,1);
    
    CCMoveBy* wait = CCMoveBy::create(1, ccp(0, 0));
    
    showTips->runAction(CCSequence::create(CCScaleTo::create(0.2, 1),wait,CCCallFuncN::create(this, callfuncN_selector(gameShopClass::showBuySuccessCallBack)),NULL));
    gameShopBgSprite->addChild(showTips,1000);
}

void gameShopClass::showBuySuccessCallBack(cocos2d::CCNode *node)
{
    CCSprite* sprite = (CCSprite*)node;
    
    sprite->stopAllActions();
    sprite->removeFromParentAndCleanup(true);
}

