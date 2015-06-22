//
//  PetsNestClass.cpp
//  CaratonFatans
//
//  Created by  Jack on 13-11-25.
//
//

#include "PetsNestClass.h"
#include "LcdAdapClass.h"
#include "WelcomeLayerClass.h"
#include "HUDClass.h"
#include "PetsBreedClass.h"
#include "GameShowSendWBClass.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "GameWBConClass.h"
#endif

#include "gameShopClass.h"

#define SCROLL_DELTA_LEN    (5)
#define PETS_EGG_NUM_MAX (20)
#define PAGE_EGG_NUM_MAX (15)


typedef enum {
    POPUP_MENU_TAG_TYPE_NONE,
    
    POPUP_MENU_TAG_TYPE_NEED_NEST,
    POPUP_MENU_TAG_TYPE_USED_NEST,
    POPUP_MENU_TAG_TYPE_NEED_BIGNEST,
    POPUP_MENU_TAG_TYPE_USED_BIGNEST,
    POPUP_MENU_TAG_TYPE_NEED_MEDICINE,
    POPUP_MENU_TAG_TYPE_USED_MEDICINE,
    POPUP_MENU_TAG_TYPE_CLOSE,
    POPUP_MENU_TAG_TYPE_WEIBO_CLOSE,
    POPUP_MENU_TAG_TYPE_WEIBO_SEL_SINA,
    POPUP_MENU_TAG_TYPE_WEIBO_SEL_TC,
    POPUP_MENU_TAG_TYPE_MAX
}POPUP_MENU_TAG_TYPE;


typedef enum {
    PETS_MENU_ID_TYPE_NONE,
    PETS_MENU_ID_TYPE_HOME,
    PETS_MENU_ID_TYPE_WEIBO,
    PETS_MENU_ID_TYPE_WEIBO_CLOSE,
    PETS_MENU_ID_TYPE_WEIBO_SINA,
    PETS_MENU_ID_TYPE_WEIBO_TC,
    PETS_MENU_ID_TYPE_SHOP,
    PETS_MENU_ID_TYPE_MAX
}PETS_MENU_ID_TYPE;

static char comBuffer[20] = {0};

static PetsBreedClass* userSelEgg = NULL;

PetsNestClass::PetsNestClass()
{
    
}

PetsNestClass::~PetsNestClass()
{
    petsEggArray->release();
    userSelEgg = NULL;
}

bool PetsNestClass::init()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    CCArray* comArray = CCArray::create();
    
    isShowPopUP = false;
    layerNum = 2;
    layerPosIndex = 1;
    startTouchPos = ccp(0,0);
    selEggState = PETS_EGG_STATE_TYPE_NONE;
    selEggType = PETS_BREED_EGG_TYPE_NONE;
    
//    HUDClass::sharedHUD()->setUserCookieNum(250);
//    HUDClass::sharedHUD()->setUserMilkNum(250);
//    HUDClass::sharedHUD()->setUserNestNum(2);
//    HUDClass::sharedHUD()->setUserMedicineNum(2);
    
    LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(this);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsSNS-hd.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsNest-hd.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsEgg-hd.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsIcon-hd.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsTheme01-hd.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsTheme02-hd.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsTheme03-hd.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsTheme06-hd.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsWhale-hd.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Pets/PetsTip-hd.plist");
    
    gameBG = CCSprite::createWithSpriteFrameName("PetMainBG.png");
    CCSize gameBGSize = gameBG->getContentSize();
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(gameBG, ccp(size.width / 2, size.height / 2));
    //gameBG->setPosition(ccp(size.width / 2, size.height / 2));
    this->addChild(gameBG,1);
    
    
    shareWBSprite = CCSprite::createWithSpriteFrameName("share_bg.png");
    CCSize shareWBSize = shareWBSprite->getContentSize();
    shareWBSprite->setPosition(ccp(gameBGSize.width / 2, gameBGSize.height + (shareWBSize.height)));
    gameBG->addChild(shareWBSprite,0);
    
    CCSprite* wbleftSprite = CCSprite::createWithSpriteFrameName("share_left.png");
    wbleftSprite->setPosition(ccp(shareWBSize.width * 24.0/100.0, shareWBSize.height * 40/100.0));
    shareWBSprite->addChild(wbleftSprite,1);
    
    CCSprite* wbrightBG = CCSprite::createWithSpriteFrameName("share_right_CN.png");
    wbrightBG->setPosition(ccp(shareWBSize.width * 65/100, shareWBSize.height * 40/100));
    shareWBSprite->addChild(wbrightBG,1);
    
    CCMenuItemImage* sinaWB = CCMenuItemImage::create("share_weibo_normal.png", "share_weibo_normal.png", this, menu_selector(PetsNestClass::menuSelActionCallBack));
    sinaWB->setPosition(ccp(shareWBSize.width * 54/100, shareWBSize.height * 40/100));
    sinaWB->setTag(PETS_MENU_ID_TYPE_WEIBO_SINA);
    
    CCMenuItemImage* tcWB = CCMenuItemImage::create("share_tencent_normal.png", "share_tencent_pressed.png", this, menu_selector(PetsNestClass::menuSelActionCallBack));
    tcWB->setPosition(ccp(shareWBSize.width * 74/100, shareWBSize.height * 40/100));
    tcWB->setTag(PETS_MENU_ID_TYPE_WEIBO_TC);
    
    CCMenuItemImage* closeWB = CCMenuItemImage::create("share_close_normal.png", "share_close_pressed.png", this, menu_selector(PetsNestClass::menuSelActionCallBack));
    closeWB->setPosition(ccp(shareWBSize.width * 92/100, shareWBSize.height * 66/100));
    closeWB->setTag(PETS_MENU_ID_TYPE_WEIBO_CLOSE);
    
    CCMenu* wbmenu = CCMenu::create(sinaWB,tcWB,closeWB,NULL);
    wbmenu->setPosition(CCPointZero);
    shareWBSprite->addChild(wbmenu,10);
    
    
    CCSprite* petToolBar = CCSprite::createWithSpriteFrameName("PetToolBar.png");
    CCSize toolBarSize = petToolBar->getContentSize();
    petToolBar->setPosition(ccp(gameBGSize.width / 2, gameBGSize.height * 93 / 100));
    gameBG->addChild(petToolBar,1);
    
    CCMenuItemImage* home = CCMenuItemImage::create("PetBack01.png", "PetBack02.png", this, menu_selector(PetsNestClass::menuSelActionCallBack));
    home->setTag((int)PETS_MENU_ID_TYPE_HOME);
    home->setPosition(ccp(toolBarSize.width * 5 /100, toolBarSize.height/ 2));
    comArray->addObject(home);
    
    CCMenuItemImage* weibo = CCMenuItemImage::create("PetMenu01.png", "PetMenu02.png", this, menu_selector(PetsNestClass::menuSelActionCallBack));
    weibo->setTag((int)PETS_MENU_ID_TYPE_WEIBO);
    weibo->setPosition(ccp(toolBarSize.width * 15 /100, toolBarSize.height/ 2));
    comArray->addObject(weibo);
    
    CCMenuItemImage* shop = CCMenuItemImage::create("PetShop01_CN.png", "PetShop02_CN.png", this, menu_selector(PetsNestClass::menuSelActionCallBack));
    shop->setTag((int)PETS_MENU_ID_TYPE_SHOP);
    shop->setPosition(ccp(toolBarSize.width * 88 /100, toolBarSize.height/ 2));
    comArray->addObject(shop);
    
    CCMenu* menu = CCMenu::createWithArray(comArray);
    menu->setPosition(CCPointZero);
    
    petToolBar->addChild(menu,1);
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%d",HUDClass::sharedHUD()->getUserCookieNum());
    
    userCookiNumLab = CCLabelAtlas::create(comBuffer, "Themes/Pets/PetNumBig.png", 13, 20, 46);
    userCookiNumLab->setPosition(ccp(toolBarSize.width * 32 / 100, toolBarSize.height * 45 /100));
    petToolBar->addChild(userCookiNumLab,5);
    
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%d",HUDClass::sharedHUD()->getUserMilkNum());
    
    userMilkNumLab = CCLabelAtlas::create(comBuffer, "Themes/Pets/PetNumBig.png", 13, 20, 46);
    userMilkNumLab->setPosition(ccp(toolBarSize.width * 49 / 100, toolBarSize.height * 45 /100));
    petToolBar->addChild(userMilkNumLab,5);
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%d",HUDClass::sharedHUD()->getUserNestNum());
    
    userNestNumLab = CCLabelAtlas::create(comBuffer, "Themes/Pets/PetNumBig.png", 13, 20, 46);
    userNestNumLab->setPosition(ccp(toolBarSize.width * 70 / 100, toolBarSize.height * 45 /100));
    petToolBar->addChild(userNestNumLab,5);
    
    
    
    
    farmLayer = CCLayer::create();
    farmLayer->setContentSize(ccp(size.width * layerNum, size.height));
    farmLayer->setPosition(ccp(size.width * -1, 0));
    this->addChild(farmLayer,5);
    
    petsEggArray = CCArray::create();
    petsEggArray->retain();
    
    this->initPetLayer();
    this->initTipsBG();
    
    
    return true;
}

void PetsNestClass::initTipsBG()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    
    tipShowBG = CCSprite::createWithSpriteFrameName("spopup_bg.png");
    CCSize tipBGSize = tipShowBG->getContentSize();
//    tipShowBG->setPosition(ccp(size.width / 2, size.height / 2));
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(tipShowBG, ccp(size.width / 2, size.height / 2));
    this->addChild(tipShowBG,100);
    tipShowBG->setVisible(false);
    
    tipLeftIconBG = CCSprite::createWithSpriteFrameName("icon_egg.png");
    tipLeftIconBG->setPosition(ccp(tipBGSize.width * 22 /100, tipBGSize.height / 2));
    tipShowBG->addChild(tipLeftIconBG,1);
    
    tipLeftSprite = CCSprite::createWithSpriteFrameName("Icon_EggFat11_01.png");
    tipLeftSprite->setPosition(ccp(tipBGSize.width * 22 /100, tipBGSize.height / 2));
    tipShowBG->addChild(tipLeftSprite,2);
    
    tipCenterTextSprite = CCSprite::createWithSpriteFrameName("medicine_use_CN.png");
    tipCenterTextSprite->setPosition(ccp(tipBGSize.width * 65 / 100, tipBGSize.height * 66 /100));
    tipShowBG->addChild(tipCenterTextSprite,3);
    
    userMedicneNumLab = CCLabelAtlas::create("5", "Themes/Pets/mystone_num.png", 13, 26, 46);
    CCSize textSize = tipCenterTextSprite->getContentSize();
    userMedicneNumLab->setPosition(ccp(textSize.width * 28  /100, textSize.height * 34 / 100));
    tipCenterTextSprite->addChild(userMedicneNumLab,2);
    userMedicneNumLab->setVisible(false);
    
    popupYESMenuItem = CCMenuItemImage::create("popup_btnbg_normal.png", "popup_btnbg_pressed.png", this, menu_selector(PetsNestClass::popupMenuSelCallBack));
    popupYESMenuItem->setTag(POPUP_MENU_TAG_TYPE_NEED_NEST);
    popupYESMenuItem->setPosition(ccp(tipBGSize.width * 66 / 100, tipBGSize.height * 27 /100));
    
    CCMenuItemImage* close = CCMenuItemImage::create("pet_close_normal.png", "pet_close_pressed.png",this,menu_selector(PetsNestClass::popupMenuSelCallBack));
    close->setTag(POPUP_MENU_TAG_TYPE_CLOSE);
    close->setPosition(ccp(tipBGSize.width * 92 /100, tipBGSize.height * 86 /100));
    
    CCMenu* menu = CCMenu::create(popupYESMenuItem,close,NULL);
    menu->setPosition(CCPointZero);
    tipShowBG->addChild(menu,4);
    
    menuYESText = CCSprite::createWithSpriteFrameName("btn_use_CN.png");
    menuYESText->setPosition(ccp(tipBGSize.width * 66 / 100, tipBGSize.height * 27 /100));
    tipShowBG->addChild(menuYESText,5);
    
    
    
}


CCScene* PetsNestClass::createScene()
{
    CCScene* scene = NULL;
    
    do {
        scene = CCScene::create();
        CC_BREAK_IF(!scene);
        
        PetsNestClass* monsterNest = PetsNestClass::create();
        
        CC_BREAK_IF(!monsterNest);
        
        scene->addChild(monsterNest);
        
    } while (0);
    
    return scene;
}

void PetsNestClass::initPetLayer()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
//    int petNum = HUDClass::sharedHUD()->getUserPetsNum();
//    getUserPetsDataStruct userGetInfo;
//    PETS_BREED_EGG_TYPE eggType = PETS_BREED_EGG_TYPE_NONE;
//    int rowIndex = 0;
//    int columIndex = 0;
//    int rowNum = 3;
//    int columNum = 5;
//    float columPos[5] = {size.width * 0.1,size.width * 0.3,size.width / 2,size.width * 0.7,size.width * 0.9};
//    float rowPos[3] = {size.height * 0.72,size.height * 0.48,size.height * 0.18};
//    int offsetX = (int)size.width;
//    int addPetEggNum = 0;
//    
//    
//    if (petNum > 0) {
//        layerNum += (petNum - 1) / PAGE_EGG_NUM_MAX;
//        farmLayer->setContentSize(ccp(size.width * layerNum, size.height));
//    }
//    
//    for (int i = 1; i <= (PETS_EGG_NUM_MAX + 1); i++) {//20个一般的蛋与一个鲸鱼蛋
//        
//        eggType = (PETS_BREED_EGG_TYPE)(PETS_BREED_EGG_TYPE_NONE + i);
//        
//        
//        
//        offsetX = size.width * (1 + (int)(addPetEggNum/PAGE_EGG_NUM_MAX));
//        userPetDataStruct petinfo = HUDClass::sharedHUD()->getUserPetInfo(eggType);
////        if (eggType == PETS_BREED_EGG_TYPE_WHALE_06)
////        {
////            petinfo.eggType = eggType;
////            petinfo.eggState = PETS_EGG_STATE_TYPE_ONLY_AN_EGG;
////            petinfo.breedState = PETS_EGG_BREED_STATE_TYPE_FIRST;
////            petinfo.feedState = PETS_FEED_STATE_TYPE_FIRST;
////            petinfo.breededTime = HUDClass::sharedHUD()->getCurSystemTime();
////            petinfo.curNeedMilkNum = 0;
////            petinfo.curNeedCookieNum = 0;
////        }
////        petinfo.eggType = eggType;
////        petinfo.eggState = PETS_EGG_STATE_TYPE_ONLY_AN_EGG;
////        petinfo.breedState = PETS_EGG_BREED_STATE_TYPE_FIRST;
////        petinfo.feedState = PETS_FEED_STATE_TYPE_FIRST;
////        petinfo.breededTime = HUDClass::sharedHUD()->getCurSystemTime();
////        petinfo.curNeedMilkNum = 0;
////        petinfo.curNeedCookieNum = 0;
//        
//        if (petinfo.breedState > PETS_EGG_BREED_STATE_TYPE_NONE && petinfo.eggType == eggType) {
//            PetsBreedClass* breedEgg = PetsBreedClass::create(petinfo, this, callfunc_selector(PetsNestClass::updateUserNumLab));//PetsBreedClass::create(petinfo);
//
//            
//            if (eggType == PETS_BREED_EGG_TYPE_WHALE_06) {
//                LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(breedEgg, ccp(size.width /2 , size.height / 2));
//            }
//            else
//            {
//                LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(breedEgg, ccp(columPos[columIndex] + offsetX, rowPos[rowIndex]));
//                addPetEggNum += 1;
//                columIndex = addPetEggNum % columNum;
//                if ((columIndex % columNum == 0)) {
//                    rowIndex++;
//                    if (rowIndex >= rowNum) {
//                        rowIndex = 0;
//                    }
//                }
//            }
//            farmLayer->addChild(breedEgg,10);
//            
//            petsEggArray->addObject(breedEgg);
//            
//        }
//    }
//
    this->updateFarmPets();
    
    whaleBG = CCSprite::createWithSpriteFrameName("whale_bg.png");
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(whaleBG, ccp(size.width / 2 * layerPosIndex, size.height / 2));
    farmLayer->addChild(whaleBG,1);
    
}


void PetsNestClass::menuSelActionCallBack(cocos2d::CCObject *object)
{
    CCMenuItemImage* menuitem = (CCMenuItemImage*)object;
    
    switch (menuitem->getTag()) {
        case PETS_MENU_ID_TYPE_HOME:
            {
                CCDirector::sharedDirector()->replaceScene(WelcomeLayerClass::welcomSceneCreate());
            }
            break;
        case PETS_MENU_ID_TYPE_WEIBO:
            {
//                CCDirector::sharedDirector()->replaceScene(GameShowSendWBClass::createScene());
//                this->addChild(GameShowSendWBClass::create(),1000);
                
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
                CCRenderTexture* in_texture = CCRenderTexture::create(size.width, size.height);
                
                in_texture->begin();
                gameBG->visit();
                farmLayer->visit();
                in_texture->end();
                
                CCLog("%d",in_texture->saveToFile(GAME_WB_PIC_NAME, kCCImageFormatPNG));
//                GameWBConClass::sharedWBCON()->showWBView();
                CCSize gameBGSize = gameBG->getContentSize();
                CCMoveTo* mto = CCMoveTo::create(0.5, ccp(gameBGSize.width/2,gameBGSize.height * 60/100));
                shareWBSprite->runAction(mto);
#endif
            }
            break;
        case PETS_MENU_ID_TYPE_WEIBO_SINA:
            {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                if (GameWBConClass::sharedWBCON()->checkDeviceNetState()) {
                    GameWBConClass::sharedWBCON()->SetSinWbOrTCWbIsSelected(false);
                    GameWBConClass::sharedWBCON()->showWBView();
                }
                else
                {
                    CCSize gameBGSize = gameBG->getContentSize();
                    GameShowNetClass* show = GameShowNetClass::create();
                    show->showNetState(GAME_NET_WORK_STATE_TYPE_NONET);
                    show->setPosition(ccp(gameBGSize.width/2, gameBGSize.height * 1/10));
                    gameBG->addChild(show,1000);
                }
#endif
            }
            break;
        case PETS_MENU_ID_TYPE_WEIBO_TC:
            {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                if (GameWBConClass::sharedWBCON()->checkDeviceNetState()) {
                    GameWBConClass::sharedWBCON()->SetSinWbOrTCWbIsSelected(true);
                    GameWBConClass::sharedWBCON()->showWBView();
                }
                else
                {
                    CCSize gameBGSize = gameBG->getContentSize();
                    GameShowNetClass* show = GameShowNetClass::create();
                    show->showNetState(GAME_NET_WORK_STATE_TYPE_NONET);
                    show->setPosition(ccp(gameBGSize.width/2, gameBGSize.height * 1/10));
                    gameBG->addChild(show,1000);
                    
                }
#endif
            }
            break;
        case PETS_MENU_ID_TYPE_WEIBO_CLOSE:
            {
                CCSize wbBGSize = shareWBSprite->getContentSize();
                CCSize gameBGSize = gameBG->getContentSize();
                CCMoveTo* mto = CCMoveTo::create(0.5, ccp(gameBGSize.width/2,gameBGSize.height + wbBGSize.height));
                shareWBSprite->runAction(mto);
            }
            break;
        case PETS_MENU_ID_TYPE_SHOP:
            {
                gameShopClass* shop = gameShopClass::create(this, callfunc_selector(PetsNestClass::updateUserFoodsNumAndPets));
                this->addChild(shop,1000);
            }
            break;
        default:
            break;
    }
    
}

void PetsNestClass::showPopUpBG()
{
    CCAssert(!(selEggState == PETS_EGG_STATE_TYPE_NONE || selEggState == PETS_EGG_STATE_TYPE_MAX || selEggType == PETS_BREED_EGG_TYPE_NONE || selEggType == PETS_BREED_EGG_TYPE_MAX), "cannot be INVALID");
    char* eggFileName = NULL;
    
    tipShowBG->setVisible(true);
    
    
    switch (selEggType) {
        case PETS_BREED_EGG_TYPE_LAND_01:
            eggFileName = "Icon_EggLand11_01.png";
            break;
        case PETS_BREED_EGG_TYPE_LAND_2_01:
            eggFileName= "Icon_EggLand21_01.png";
            break;
        case PETS_BREED_EGG_TYPE_FLY_01:
            eggFileName = "Icon_EggFly11_01.png";
            break;
        case PETS_BREED_EGG_TYPE_FAT_01:
            eggFileName = "Icon_EggFat11_01.png";
            break;
        case PETS_BREED_EGG_TYPE_BOSS_01:
            eggFileName = "Icon_EggBoss11_01.png";
            break;
        case PETS_BREED_EGG_TYPE_LAND_02:
            eggFileName = "Icon_EggLand11_02.png";
            break;
        case PETS_BREED_EGG_TYPE_LAND_2_02:
            eggFileName= "Icon_EggLand21_02.png";
            break;
        case PETS_BREED_EGG_TYPE_FLY_02:
            eggFileName = "Icon_EggFly11_02.png";
            break;
        case PETS_BREED_EGG_TYPE_FAT_02:
            eggFileName = "Icon_EggFat11_02.png";
            break;
        case PETS_BREED_EGG_TYPE_BOSS_02:
            eggFileName = "Icon_EggBoss11_02.png";
            break;
        case PETS_BREED_EGG_TYPE_LAND_03:
            eggFileName = "Icon_EggLand11_03.png";
            break;
        case PETS_BREED_EGG_TYPE_LAND_2_03:
            eggFileName= "Icon_EggLand21_03.png";
            break;
        case PETS_BREED_EGG_TYPE_FLY_03:
            eggFileName = "Icon_EggFly11_03.png";
            break;
        case PETS_BREED_EGG_TYPE_FAT_03:
            eggFileName = "Icon_EggFat11_03.png";
            break;
        case PETS_BREED_EGG_TYPE_BOSS_03:
            eggFileName = "Icon_EggBoss11_03.png";
            break;
        case PETS_BREED_EGG_TYPE_LAND_06:
            eggFileName = "Icon_EggLand11_06.png";
            break;
        case PETS_BREED_EGG_TYPE_LAND_2_06:
            eggFileName= "Icon_EggLand21_06.png";
            break;
        case PETS_BREED_EGG_TYPE_FLY_06:
            eggFileName = "Icon_EggFly11_06.png";
            break;
        case PETS_BREED_EGG_TYPE_FAT_06:
            eggFileName = "Icon_EggFat11_06.png";
            break;
        case PETS_BREED_EGG_TYPE_BOSS_06:
            eggFileName = "Icon_EggBoss11_01.png";
            break;
        case PETS_BREED_EGG_TYPE_WHALE_06:
            eggFileName = "Icon_EggWhale11_06.png";
            break;
        default:
            break;
    }
    
    
    if (selEggState == PETS_EGG_STATE_TYPE_ONLY_AN_EGG) {
        int nestNum = HUDClass::sharedHUD()->getUserNestNum();
        int bigNestNum = HUDClass::sharedHUD()->getUserBigNestNum();
        
        if (selEggType == PETS_BREED_EGG_TYPE_WHALE_06) {
            if (bigNestNum <= 0) {
                tipCenterTextSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("whalenest_need_CN.png"));
                menuYESText->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_whalenest_CN.png"));
                tipLeftSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tip_whalenest.png"));
                tipLeftIconBG->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tip_nest.png"));
                popupYESMenuItem->setTag(POPUP_MENU_TAG_TYPE_NEED_BIGNEST);
            }
            else
            {
                tipCenterTextSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("nest_use_CN.png"));
                menuYESText->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_use_CN.png"));
                tipLeftIconBG->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_egg.png"));
                tipLeftSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(eggFileName));
                tipLeftSprite->setVisible(true);
                
                popupYESMenuItem->setTag(POPUP_MENU_TAG_TYPE_USED_NEST);
            }
        }
        else if (nestNum <= 0){
            tipCenterTextSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("nest_need_CN.png"));
            menuYESText->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_whalenest_CN.png"));
            tipLeftIconBG->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tip_nest.png"));
            tipLeftSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_nest_CN.png"));
            tipLeftSprite->setVisible(true);
            
            popupYESMenuItem->setTag(POPUP_MENU_TAG_TYPE_NEED_NEST);
        }
        else if (nestNum > 0) {
            
            tipCenterTextSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("nest_use_CN.png"));
            menuYESText->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_use_CN.png"));
            tipLeftIconBG->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_egg.png"));
            tipLeftSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(eggFileName));
            tipLeftSprite->setVisible(true);
            
            popupYESMenuItem->setTag(POPUP_MENU_TAG_TYPE_USED_NEST);
        }
        
        
        isShowPopUP = true;
    }
    else if (selEggState == PETS_EGG_STATE_TYPE_START_BREEDDING){
        
        int medicineNum = HUDClass::sharedHUD()->getUserMedicineNum();
        
        if (medicineNum <= 0) {
            tipCenterTextSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("medicine_need_CN.png"));
            menuYESText->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_whalenest_CN.png"));
            tipLeftIconBG->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tip_medicine.png"));
            tipLeftSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_medicine_CN.png"));
            tipLeftSprite->setVisible(true);
            
            popupYESMenuItem->setTag(POPUP_MENU_TAG_TYPE_NEED_MEDICINE);
        }
        else
        {
            
            
            tipCenterTextSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("medicine_use_CN.png"));
            menuYESText->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_use_CN.png"));
            tipLeftIconBG->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_egg.png"));
            tipLeftSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(eggFileName));
            tipLeftSprite->setVisible(true);
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%d",HUDClass::sharedHUD()->getUserMedicineNum());
            userMedicneNumLab->setString(comBuffer);
            userMedicneNumLab->setVisible(true);
            
            popupYESMenuItem->setTag(POPUP_MENU_TAG_TYPE_USED_MEDICINE);
        }
        isShowPopUP = true;
    }
    
}

void PetsNestClass::popupMenuSelCallBack(CCObject* object)
{
    CCMenuItemImage* menuitem = (CCMenuItemImage*)object;
    
    isShowPopUP = false;
    tipShowBG->setVisible(false);
    switch (menuitem->getTag()) {
            
        case POPUP_MENU_TAG_TYPE_USED_NEST:
            {
                int nestNum = 0;
                
                if (selEggType == PETS_BREED_EGG_TYPE_WHALE_06) {
                    nestNum = HUDClass::sharedHUD()->getUserBigNestNum();
                    
                    if (nestNum > 0) {
                        nestNum -= 1;
                        HUDClass::sharedHUD()->setUserBigNestNum(nestNum);
                        this->updateUserNumLab();
                    }
                }
                else
                {
                    nestNum = HUDClass::sharedHUD()->getUserNestNum();
                    if (nestNum > 0) {
                        nestNum -= 1;
                        HUDClass::sharedHUD()->setUserNestNum(nestNum);
                        this->updateUserNumLab();
                    }
                }
                
                if (userSelEgg != NULL) {
                    userSelEgg->setPetsBreedState(PETS_EGG_STATE_TYPE_START_BREEDDING);
                }
            }
            break;
        case POPUP_MENU_TAG_TYPE_USED_MEDICINE:
            {
                int medicineNum = 0;
                
                {
                    medicineNum = HUDClass::sharedHUD()->getUserMedicineNum();
                    if (medicineNum > 0) {
                        medicineNum -= 1;
                        HUDClass::sharedHUD()->setUserMedicineNum(medicineNum);
                        this->updateUserNumLab();
                    }
                }
                if (userSelEgg != NULL) {
                    userSelEgg->setPetsBreedState(PETS_EGG_STATE_TYPE_START_BORN);
                }
                userMedicneNumLab->setVisible(false);
            }
            break;
            
        case POPUP_MENU_TAG_TYPE_NEED_BIGNEST:
        case POPUP_MENU_TAG_TYPE_CLOSE:
        case POPUP_MENU_TAG_TYPE_NEED_MEDICINE:
        case POPUP_MENU_TAG_TYPE_NEED_NEST:
            {
                tipShowBG->setVisible(false);
                if (userSelEgg->getPetsBreedState() == PETS_EGG_STATE_TYPE_START_BREEDDING) {
                    userSelEgg->unscheduleUpdate();
                    userSelEgg->scheduleUpdate();
                }
            }
            break;
            
        default:
            break;
    }
}

void PetsNestClass::updateFarmPets()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    int petNum = HUDClass::sharedHUD()->getUserPetsNum();
    //getUserPetsDataStruct userGetInfo;
    PETS_BREED_EGG_TYPE eggType = PETS_BREED_EGG_TYPE_NONE;
    int rowIndex = 0;
    int columIndex = 0;
    int rowNum = 3;
    int columNum = 5;
    float columPos[5] = {size.width * 0.1,size.width * 0.3,size.width / 2,size.width * 0.7,size.width * 0.9};
    float rowPos[3] = {size.height * 0.72,size.height * 0.48,size.height * 0.18};
    int offsetX = (int)size.width;
    int addPetEggNum = 0;
    
    
    if (petNum > 0) {
        layerNum += (petNum - 1) / PAGE_EGG_NUM_MAX;
        farmLayer->setContentSize(ccp(size.width * layerNum, size.height));
    }
    
    for (int i = 1; i <= (PETS_EGG_NUM_MAX + 1); i++) {//20个一般的蛋与一个鲸鱼蛋
        
        eggType = (PETS_BREED_EGG_TYPE)(PETS_BREED_EGG_TYPE_NONE + i);
        
        
        
        offsetX = size.width * (1 + (int)(addPetEggNum/PAGE_EGG_NUM_MAX));
        userPetDataStruct petinfo = HUDClass::sharedHUD()->getUserPetInfo(eggType);
        //        if (eggType == PETS_BREED_EGG_TYPE_WHALE_06)
        //        {
        //            petinfo.eggType = eggType;
        //            petinfo.eggState = PETS_EGG_STATE_TYPE_ONLY_AN_EGG;
        //            petinfo.breedState = PETS_EGG_BREED_STATE_TYPE_FIRST;
        //            petinfo.feedState = PETS_FEED_STATE_TYPE_FIRST;
        //            petinfo.breededTime = HUDClass::sharedHUD()->getCurSystemTime();
        //            petinfo.curNeedMilkNum = 0;
        //            petinfo.curNeedCookieNum = 0;
        //        }
        //        petinfo.eggType = eggType;
        //        petinfo.eggState = PETS_EGG_STATE_TYPE_ONLY_AN_EGG;
        //        petinfo.breedState = PETS_EGG_BREED_STATE_TYPE_FIRST;
        //        petinfo.feedState = PETS_FEED_STATE_TYPE_FIRST;
        //        petinfo.breededTime = HUDClass::sharedHUD()->getCurSystemTime();
        //        petinfo.curNeedMilkNum = 0;
        //        petinfo.curNeedCookieNum = 0;
        
        if (petinfo.breedState > PETS_EGG_BREED_STATE_TYPE_NONE && petinfo.eggType == eggType) {
            PetsBreedClass* breedEgg = PetsBreedClass::create(petinfo, this, callfunc_selector(PetsNestClass::updateUserNumLab));//PetsBreedClass::create(petinfo);
            
            
            if (eggType == PETS_BREED_EGG_TYPE_WHALE_06) {
                LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(breedEgg, ccp(size.width /2 , size.height / 2));
            }
            else
            {
                LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(breedEgg, ccp(columPos[columIndex] + offsetX, rowPos[rowIndex]));
                addPetEggNum += 1;
                columIndex = addPetEggNum % columNum;
                if ((columIndex % columNum == 0)) {
                    rowIndex++;
                    if (rowIndex >= rowNum) {
                        rowIndex = 0;
                    }
                }
            }
            farmLayer->addChild(breedEgg,10);
            
            petsEggArray->addObject(breedEgg);
            
        }
    }
}

void PetsNestClass::updateUserFoodsNumAndPets()
{
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%d",HUDClass::sharedHUD()->getUserCookieNum());
    userCookiNumLab->setString(comBuffer);
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%d",HUDClass::sharedHUD()->getUserMilkNum());
    userMilkNumLab->setString(comBuffer);
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%d",HUDClass::sharedHUD()->getUserNestNum());
    userNestNumLab->setString(comBuffer);
    
    this->updateFarmPets();
}


void PetsNestClass::onEnter()
{
    CCLayer::onEnter();
//    this->setTouchEnabled(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void PetsNestClass::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void PetsNestClass::gotoPage(int index)
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    CCMoveTo* mto = CCMoveTo::create(0.5, ccp(size.width * -index, 0));
    farmLayer->runAction(mto);
    
}

void PetsNestClass::updateUserNumLab()
{
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%d",HUDClass::sharedHUD()->getUserCookieNum());
    userCookiNumLab->setString(comBuffer);
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%d",HUDClass::sharedHUD()->getUserMilkNum());
    userMilkNumLab->setString(comBuffer);
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%d",HUDClass::sharedHUD()->getUserNestNum());
    userNestNumLab->setString(comBuffer);
}


bool PetsNestClass::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    startTouchPos = this->convertToNodeSpace(pTouch->getLocation());
    return true;
}

void PetsNestClass::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    CCPoint curPos = farmLayer->convertToNodeSpace(pTouch->getLocation());
    CCPoint prePos = farmLayer->convertToNodeSpace(pTouch->getPreviousLocation());
    
    CCLOG("curPos x = %f  y = %f",curPos.x,curPos.y);
    
    CCPoint diffPos = ccpSub(curPos, prePos);
    
    CCPoint myPos = farmLayer->getPosition();
    farmLayer->setPosition(ccpAdd(ccp(myPos.x, myPos.y), ccp(diffPos.x, 0)));
    
    
    
}

void PetsNestClass::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    CCPoint curPos = this->convertToNodeSpace(pTouch->getLocation());
    CCPoint prePos = startTouchPos;
    CCPoint diffPos = ccpSub(curPos, prePos);
    
    if (ccpLength(ccp(diffPos.x, 0)) > SCROLL_DELTA_LEN) {
        if (diffPos.x < 0) {
            layerPosIndex += 1;
            if (layerPosIndex >= (layerNum - 1)) {
                layerPosIndex = layerNum - 1;
            }
        }
        else
        {
            layerPosIndex -= 1;
            if (layerPosIndex <= 0) {
                layerPosIndex = 0;
            }
        }
        
        this->gotoPage(layerPosIndex);
    }
    else
    {
        curPos = farmLayer->convertToNodeSpace(pTouch->getLocation());
        for (int i = 0; i < petsEggArray->count(); i++) {
            PetsBreedClass* egg = (PetsBreedClass*)petsEggArray->objectAtIndex(i);
            CCPoint eggPos = egg->getPosition();
            CCSize eggSize = egg->getPetsEggSpriteSize();
            CCRect eggRect = CCRect(eggPos.x - eggSize.width / 2, eggPos.y - eggSize.height / 2, eggSize.width, eggSize.height);
            
            if (eggRect.containsPoint(curPos) && !egg->getShowOrHideFoodPad()) {
                
                if (egg->getPetsBreedState() == PETS_EGG_STATE_TYPE_ONLY_AN_EGG || egg->getPetsBreedState() == PETS_EGG_STATE_TYPE_START_BREEDDING) {
                    if (!isShowPopUP) {
                        selEggType = egg->getPetsEggType();
                        selEggState = egg->getPetsBreedState();
                        userSelEgg = egg;
                        if (egg->getPetsBreedState() == PETS_EGG_STATE_TYPE_START_BREEDDING) {
                            egg->unscheduleUpdate();
                        }
                        this->showPopUpBG();
                    }
                }
                else
                {
                    egg->showOrHideFoodPad(true);
                }
                break;
            }
            
        }
    }
    
    CCLOG("curPos x = %f  y = %f",curPos.x,curPos.y);
    
    
}




