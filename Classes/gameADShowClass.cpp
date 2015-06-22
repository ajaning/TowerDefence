//
//  gameADShowClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-12-27.
//
//

#include "gameADShowClass.h"
#include "gameADConClass.h"
#include "LcdAdapClass.h"
#include "WelcomeLayerClass.h"

#define DM_OFFERWALL_LIST_TAG   (1)
#define DM_OFFERWALL_VIDEO_TAG  (5)
#define DM_INTER_TAG    (10)

#define MENU_CLOSE_TAG  (100)

static char comBuffer[100] = {0};

gameADShowClass::gameADShowClass()
{

}

gameADShowClass::~gameADShowClass()
{

}

bool gameADShowClass::init()
{

     LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(this);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsShop-hd.plist");
    
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsShopAndroid-hd.plist");
    
    CCSprite* gameShopBgSprite = CCSprite::createWithSpriteFrameName("ShopMainBG.png");
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(gameShopBgSprite, ccp(size.width/2.0, size.height/2.0));
    CCSize bgSize = gameShopBgSprite->getContentSize();
    this->addChild(gameShopBgSprite,1);
    
    
    CCLabelTTF* wallListLab = CCLabelTTF::create("下载应用获取金币", "Arial", 20);
    CCMenuItemLabel* menuLab = CCMenuItemLabel::create(wallListLab, this, menu_selector(gameADShowClass::menuActionCallBack));
    menuLab->setTag(DM_OFFERWALL_LIST_TAG);
    menuLab->setPosition(ccp(bgSize.width * 18 /100.0, bgSize.height * 70 / 100.0));
    
    CCLabelTTF* wallVideo = CCLabelTTF::create("观看视频获取金币", "Arial", 20);
    CCMenuItemLabel* admenuLab = CCMenuItemLabel::create(wallVideo, this, menu_selector(gameADShowClass::menuActionCallBack));
    admenuLab->setTag(DM_OFFERWALL_VIDEO_TAG);
    admenuLab->setPosition(ccp(bgSize.width * 50 /100.0, bgSize.height * 70 / 100.0));
    
    
    CCLabelTTF* interLab = CCLabelTTF::create("插屏广告", "Arial", 20);
    CCMenuItemLabel* intermenu = CCMenuItemLabel::create(interLab, this, menu_selector(gameADShowClass::menuActionCallBack));
    intermenu->setTag(DM_INTER_TAG);
    intermenu->setPosition(ccp(bgSize.width * 80 /100.0, bgSize.height * 70 / 100.0));
    
    CCMenuItemImage* close = CCMenuItemImage::create("shop_close_normal.png", "shop_close_pressed.png", this, menu_selector(gameADShowClass::menuActionCallBack));
    close->setPosition(ccp(bgSize.width * 95 / 100.0, bgSize.height * 93 / 100.0));
    close->setTag(MENU_CLOSE_TAG);
    
    CCMenu* menu = CCMenu::create(menuLab,admenuLab,intermenu,close,NULL);
    menu->setPosition(CCPointZero);
    gameShopBgSprite->addChild(menu,10);
    
//    CCLabelTTF* mylab = CCLabelTTF::create("我获得奖励金币:", "Arial", 20);
//    mylab->setPosition(ccp(bgSize.width * 18 / 100.0,bgSize.height * 30 / 100.0));
//    gameShopBgSprite->addChild(mylab,222);
    
//    myGoldNumLab = CCLabelAtlas::create("0", "Themes/Items/numwhite.png", 13, 26, 46);
//    myGoldNumLab->setPosition(ccp(bgSize.width * 36 / 100.0,bgSize.height * 30 / 100.0));
//    gameShopBgSprite->addChild(myGoldNumLab,156);
    
//    this->scheduleUpdate();
    gameADConClass::shareGameADCon()->setCallBack(this, callfunc_selector(gameADShowClass::updateMyGlodNumLab));
    gameADConClass::shareGameADCon()->gameADLoadDMOfferWallConsumeTotal();
    return true;
}

CCScene* gameADShowClass::createMyScene()
{
    CCScene* scene = NULL;
    
    do {
        scene = CCScene::create();
        CC_BREAK_IF(!scene);
        
        gameADShowClass* welGaem = gameADShowClass::create();
        CC_BREAK_IF(!welGaem);
        
        scene->addChild(welGaem);
        
    } while (0);
    
    return scene;
}

void gameADShowClass::menuActionCallBack(cocos2d::CCObject *object)
{
    CCMenuItemLabel* menuItem = (CCMenuItemLabel*)object;
    
    switch (menuItem->getTag()) {
        case DM_OFFERWALL_LIST_TAG:
            
            gameADConClass::shareGameADCon()->gameADLoadDMOfferWallList();
            
            break;
        case DM_OFFERWALL_VIDEO_TAG:
            gameADConClass::shareGameADCon()->gameADLoadDMOfferWallVideo();
            break;
        case DM_INTER_TAG:
            gameADConClass::shareGameADCon()->gameADLoadDMInterAD();
            break;
        case MENU_CLOSE_TAG:
            CCDirector::sharedDirector()->replaceScene(WelcomeLayerClass::welcomSceneCreate());
            break;
        default:
            break;
    }
}


void gameADShowClass::updateMyGlodNumLab()
{
//    char pBuffer[20] = {0};
//    
//    int consumePoint = gameADConClass::shareGameADCon()->getGameDMConsumePointNum();
//    //    memset(comBuffer, 0, sizeof(comBuffer));
//    sprintf(pBuffer, "%d",consumePoint);
//    myGoldNumLab->setString(pBuffer);
//    CCLog("updateMyGlodNumLab = %s",pBuffer);
//    CCLog("ths myGoldNumLab->getString() = %s",myGoldNumLab->getString());
//    CCLog("gameADShowClass:: consumePoint = %d",consumePoint);
}

void gameADShowClass::update(float dt)
{
//    static float timerCounter = 0;
//    
//    timerCounter += dt;
//    
//    if (timerCounter > 1) {
//        
//        int consumePoint = gameADConClass::shareGameADCon()->getGameDMConsumePointNum();
//        
//        memset(comBuffer, 0, sizeof(comBuffer));
//        sprintf(comBuffer, "%d",consumePoint);
//        myGoldNumLab->setString(comBuffer);
//        timerCounter = 0;
//        CCLog("gameADShowClass::update consumePoint = %d",consumePoint);
//    }
}

