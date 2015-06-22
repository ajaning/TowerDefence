//
//  GameStartLayerClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-7-24.
//
//

#include "GameStartLayerClass.h"
#include "MoneyScoreClass.h"
#include "GameLogoRotateClass.h"
#include "GameShowValidPos.h"
#include "ShowWinLoseClass.h"
#include "GameStageConClass.h"
#include "PetsDropClass.h"
#include "comSpriteActionClass.h"
#include "AdventureLevelClass.h"
#include "BossModeClass.h"
#include "GameMusicConClass.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "GameWBConClass.h"
#endif

#define GAME_MENU_SEL_SPEED2X   (9)
#define GAME_MENU_SEL_PAUSE     (10)
#define GAME_MENU_SEL_PAUSE_SELITEM (12)
#define GAME_MENU_SEL_PAUSE_SELITEM_RESUME (13)
#define GAME_MENU_SEL_PAUSE_SELITEM_RESTART (14)
#define GAME_MENU_SEL_PAUSE_SELITEM_SELSTAGE (15)
#define GAME_MENU_SEL_WB_SINA   (50)
#define GAME_MENU_SEL_WB_TECENT (55)

typedef struct {
    int objectId;
    GAME_TOWER_TYPE towerType;
}objectTowerType;//当GAME中的OBJECT死亡时会产生炮塔

objectTowerType objectTowerBuffer[] = {
    {0,GAME_TOWER_TYPE_NONE},
    {1,GAME_TOWER_TYPE_SHIT},
    {2,GAME_TOWER_TYPE_BOTTLE},
    {3,GAME_TOWER_TYPE_FAN},
    {4,GAME_TOWER_TYPE_STAR},
    {5,GAME_TOWER_TYPE_BALL},
    {6,GAME_TOWER_TYPE_BLUESTAR},
    {7,GAME_TOWER_TYPE_SUN},
    {8,GAME_TOWER_TYPE_PIN},
    {9,GAME_TOWER_TYPE_BOTTLE},
    {10,GAME_TOWER_TYPE_FIREBOTTLE},
    {11,GAME_TOWER_TYPE_SNOW},
    {12,GAME_TOWER_TYPE_PLANE},
    {13,GAME_TOWER_TYPE_PIN},
    {14,GAME_TOWER_TYPE_ROCKET},
    {15,GAME_TOWER_TYPE_FIREBOTTLE},
    {16,GAME_TOWER_TYPE_SNOW},
    {17,GAME_TOWER_TYPE_PLANE},
    {18,GAME_TOWER_TYPE_CUTTLE}
};


GAME_STAGE_TYPE extremeMapThemeId[] = {
    GAME_STAGE_TYPE_NONE,
    GAME_STAGE_TYPE_SKY,
    GAME_STAGE_TYPE_SKY,
    GAME_STAGE_TYPE_SKY,
    GAME_STAGE_TYPE_SKY,
    GAME_STAGE_TYPE_SKY,
    GAME_STAGE_TYPE_JUNG,
    GAME_STAGE_TYPE_JUNG,
    GAME_STAGE_TYPE_JUNG,
    GAME_STAGE_TYPE_JUNG,
    GAME_STAGE_TYPE_JUNG,
    GAME_STAGE_TYPE_DESERT,
    GAME_STAGE_TYPE_DESERT,
    GAME_STAGE_TYPE_DESERT,
    GAME_STAGE_TYPE_DESERT,
    GAME_STAGE_TYPE_DESERT,
    GAME_STAGE_TYPE_SKY,
    GAME_STAGE_TYPE_SKY,
    GAME_STAGE_TYPE_JUNG,
    GAME_STAGE_TYPE_JUNG,
    GAME_STAGE_TYPE_DESERT,
    GAME_STAGE_TYPE_MAX,
};

typedef struct {
    GAME_STAGE_TYPE gameStageId;
    int gameThemeMapID;
}gameBossModeThemeStruct;


gameBossModeThemeStruct bossStageThemeConfig[] = {
    {GAME_STAGE_TYPE_NONE,0},
    {GAME_STAGE_TYPE_SKY,13},
    {GAME_STAGE_TYPE_SKY,14},
    {GAME_STAGE_TYPE_SKY,15},
    {GAME_STAGE_TYPE_SKY,16},
    {GAME_STAGE_TYPE_JUNG,13},
    {GAME_STAGE_TYPE_JUNG,14},
    {GAME_STAGE_TYPE_JUNG,15},
    {GAME_STAGE_TYPE_JUNG,16},
    {GAME_STAGE_TYPE_DESERT,13},
    {GAME_STAGE_TYPE_DESERT,14},
    {GAME_STAGE_TYPE_DESERT,15},
    {GAME_STAGE_TYPE_DESERT,16},
    {GAME_STAGE_TYPE_DEEPSEA,19},
    {GAME_STAGE_TYPE_DEEPSEA,20},
    {GAME_STAGE_TYPE_DEEPSEA,21},
    {GAME_STAGE_TYPE_DEEPSEA,22},
};




static char combuffer[255] = {0};


GameStartLayerClass::GameStartLayerClass()
{

}

GameStartLayerClass::~GameStartLayerClass()
{
    pathArray->release();
    mapPutArray->release();
    enemyArray->release();
    enemyMonsterArray->release();
    enemyObjectArray->release();
    deadSpriteArray->release();
    towerArray->release();
    bulletEffectArray->release();
    bulletArray->release();
    towerShowUpArray->release();
    
    userSelTower = NULL;
    isLayerOver = true;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    

}

void GameStartLayerClass::initTower()
{
    //read the tower type from data
    char pBuffer[150] = {0};
    int towerType = 0;
    int bulletOrder = GAMEING_TOWER_BULLET_ZORDER;
    
    towerAnchorBatch = NULL;
    towerArrowBatch = NULL;
    towerBallBatch = NULL;
    towerBlueStarBatch = NULL;
    towerBottleBatch = NULL;
    towerBuffBatch = NULL;
    towerCuttleBatch = NULL;
    towerFanBatch = NULL;
    towerFireBottleBatch = NULL;
    towerFishBatch = NULL;
    towerMushRoomBatch = NULL;
    towerPinBatch = NULL;
    towerPlaneBatch = NULL;
    towerRocketBatch = NULL;
    towerShitBatch = NULL;
    towerSnowBatch = NULL;
    towerStarBatch = NULL;
    towerSunBatch = NULL;
    showNewTowerFeature = NULL;
    
    
	towerType = GameStageConClass::sharedStageCon()->getGameStageAddTowerType();
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TAnchor-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TArrow-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TBall-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TBlueStar-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TBottle-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TBuff-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TCuttle-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TFan-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TFireBottle-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TFish-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TMushroom-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TPin-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TPlane-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TRocket-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TShit-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TSnow-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TStar-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Towers/TSun-hd.plist");
    
    
    
    //if ((towerType & GAME_ADD_TOWER_TYPE_BOTTLE) == GAME_ADD_TOWER_TYPE_BOTTLE)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TBottle");
        towerBottleBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerBottleBatch,bulletOrder);
    }
    //if ((towerType & GAME_ADD_TOWER_TYPE_ANCHOR) == GAME_ADD_TOWER_TYPE_ANCHOR)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TAnchor");
        towerAnchorBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerAnchorBatch,bulletOrder);
    }
    //if ((towerType & GAME_ADD_TOWER_TYPE_ARROW) == GAME_ADD_TOWER_TYPE_ARROW)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TArrow");
        towerArrowBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerArrowBatch,bulletOrder);
    }
    
    //if ((towerType & GAME_ADD_TOWER_TYPE_BALL) == GAME_ADD_TOWER_TYPE_BALL)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TBall");
        towerBallBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerBallBatch,bulletOrder);
    }
    //if ((towerType & GAME_ADD_TOWER_TYPE_BLUESTAR) == GAME_ADD_TOWER_TYPE_BLUESTAR)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TBlueStar");
        towerBlueStarBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerBlueStarBatch,bulletOrder);
    }
    //if ((towerType & GAME_ADD_TOWER_TYPE_BUFF) == GAME_ADD_TOWER_TYPE_BUFF)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TBuff");
        towerBuffBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerBuffBatch,bulletOrder);
    }
    //if ((towerType & GAME_ADD_TOWER_TYPE_CUTTLE) == GAME_ADD_TOWER_TYPE_CUTTLE)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TCuttle");
        towerCuttleBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerCuttleBatch,bulletOrder);
    }
    //if ((towerType & GAME_ADD_TOWER_TYPE_FAN) == GAME_ADD_TOWER_TYPE_FAN)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TFan");
        towerFanBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerFanBatch,bulletOrder);
    }
    //if ((towerType & GAME_ADD_TOWER_TYPE_FIREBOTTLE) == GAME_ADD_TOWER_TYPE_FIREBOTTLE)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TFireBottle");
        towerFireBottleBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerFireBottleBatch,bulletOrder);
    }
    //if ((towerType & GAME_ADD_TOWER_TYPE_FISH) == GAME_ADD_TOWER_TYPE_FISH)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TFish");
        towerFishBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerFishBatch,bulletOrder);
    }
    //if ((towerType & GAME_ADD_TOWER_TYPE_MUSHROOM) == GAME_ADD_TOWER_TYPE_MUSHROOM)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TMushroom");
        towerMushRoomBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerMushRoomBatch,bulletOrder);
    }
    //if ((towerType & GAME_ADD_TOWER_TYPE_PIN) == GAME_ADD_TOWER_TYPE_PIN)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TPin");
        towerPinBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerPinBatch,bulletOrder);
    }
    
    //if ((towerType & GAME_ADD_TOWER_TYPE_PLANE) == GAME_ADD_TOWER_TYPE_PLANE)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TPlane");
        towerPlaneBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerPlaneBatch,bulletOrder);
    }
    
    //if ((towerType & GAME_ADD_TOWER_TYPE_ROCKET) == GAME_ADD_TOWER_TYPE_ROCKET)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TRocket");
        towerRocketBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerRocketBatch,bulletOrder);
    }
    //if ((towerType & GAME_ADD_TOWER_TYPE_SHIT) == GAME_ADD_TOWER_TYPE_SHIT)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TShit");
        towerShitBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerShitBatch,bulletOrder);
    }
   //if ((towerType & GAME_ADD_TOWER_TYPE_SNOW) == GAME_ADD_TOWER_TYPE_SNOW)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TSnow");
        towerSnowBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerSnowBatch,bulletOrder);
    }
    //if ((towerType & GAME_ADD_TOWER_TYPE_STAR) == GAME_ADD_TOWER_TYPE_STAR)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TStar");
        towerStarBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerStarBatch,bulletOrder);
    }
    //if ((towerType & GAME_ADD_TOWER_TYPE_SUN) == GAME_ADD_TOWER_TYPE_SUN)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-hd.pvr.ccz","Themes/Towers/TSun");
        towerSunBatch = CCSpriteBatchNode::create(pBuffer);
        this->addChild(towerSunBatch,bulletOrder);
    }
}

void GameStartLayerClass::loadCommonImgAndInitGameMenu()
{
    char pFileName[100] = {0};
    CCArray* menuArray = CCArray::create();
    ccColor4B color;
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    float delta = 10;
    
    for (int i = 0; i < 5; i++) {
        memset(pFileName, 0, sizeof(pFileName));
        sprintf(pFileName, "Themes/Items/Items%02d-hd.plist",i);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pFileName);
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/scene/weibo-hd.plist");
    CCArray *animFrames = CCArray::create();
    
    char str[64] = {0};
    
    for (int i = 1; i < 5; i++) {
        sprintf(str, "select_%02d.png", i);
        CCLOG("%s",str);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        animFrames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.05);
    
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "selAnim");
    
    CCSprite* menuBG = CCSprite::createWithSpriteFrameName("MenuBG.png");
    //    menuBG->setScaleX(xScale);
    //    menuBG->setScaleY(yScale);
    CCSize menuBGSize = menuBG->getContentSize();

    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(menuBG, ccp(size.width / 2, size.height - (menuBGSize.height / 2) * yScale));
    this->addChild(menuBG,GAMEING_MENU_ZORDER);
    
    
 // for gamesel menu{
    color.a = 75;
    color.r = 125;
    color.g = 0;
    color.b = 0;
    gameSelItemLayer = CCLayerColor::create(color);
    CCSize layerSize = CCSizeMake(size.width, size.height);
    gameSelItemLayer->setContentSize(layerSize);
    gameSelItemLayer->setVisible(false);
    this->addChild(gameSelItemLayer,1000);
    
    memset(pFileName, 0, sizeof(pFileName));
    strcat(pFileName, "Themes/scene/gamemenu-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pFileName);
    
    CCSprite* wbBg = CCSprite::createWithSpriteFrameName("share_bg.png");
    CCSize wbBgSize = wbBg->getContentSize();
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(wbBg, ccp(size.width/2, size.height/10));
    gameSelItemLayer->addChild(wbBg,2);
    
    CCSprite* wbBgCn = CCSprite::createWithSpriteFrameName("share_bg_CN.png");
    wbBgCn->setPosition(ccp(wbBgSize.width/2,wbBgSize.height/2));
    wbBg->addChild(wbBgCn,1);
    
    CCMenuItemImage* sinawbBtn = CCMenuItemImage::create("share_weibo_normal.png", "share_weibo_press.png", this, menu_selector(GameStartLayerClass::gameMenuSelCallBack));
    sinawbBtn->setTag(GAME_MENU_SEL_WB_SINA);
    sinawbBtn->setPosition(ccp(wbBgSize.width * 16/100, wbBgSize.height * 35/100));
    
    CCMenuItemImage* tcwbBtn = CCMenuItemImage::create("share_tweibo_normal.png", "share_tweibo_press.png", this, menu_selector(GameStartLayerClass::gameMenuSelCallBack));
    tcwbBtn->setTag(GAME_MENU_SEL_WB_TECENT);
    tcwbBtn->setPosition(ccp(wbBgSize.width * 80/100, wbBgSize.height * 35/100));
    
    CCMenu* wbMenu = CCMenu::create(sinawbBtn,tcwbBtn,NULL);
    wbMenu->setPosition(CCPointZero);
    wbBg->addChild(wbMenu,5);
    
    
    
    CCSprite* gameSelBg = CCSprite::createWithSpriteFrameName("menu_bg.png");
    //gameSelBg->setPosition(ccp(layerSize.width / 2, layerSize.height / 2));
    CCSize gameSelBgSize = gameSelBg->getContentSize();
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(gameSelBg, ccp(size.width/2, size.height/2));
    gameSelItemLayer->addChild(gameSelBg,5);
    
    CCMenuItemImage* reseumeGame = CCMenuItemImage::create("menu_resume_normal_CN.png", "menu_resume_pressed_CN.png", this, menu_selector(GameStartLayerClass::gameMenuSelCallBack));
    reseumeGame->setTag(GAME_MENU_SEL_PAUSE_SELITEM_RESUME);
    CCSize resumeSize = reseumeGame->getContentSize();
    reseumeGame->setPosition(ccp(gameSelBgSize.width / 2, gameSelBgSize.height * 77 / 100.0));
    menuArray->addObject(reseumeGame);
    
    CCMenuItemImage* restartGame = CCMenuItemImage::create("menu_restart_normal_CN.png", "menu_restart_pressed_CN.png", this, menu_selector(GameStartLayerClass::gameMenuSelCallBack));
    restartGame->setTag(GAME_MENU_SEL_PAUSE_SELITEM_RESTART);
    CCSize restartSize = restartGame->getContentSize();
    restartGame->setPosition(ccp(gameSelBgSize.width / 2, gameSelBgSize.height * 51/ 100.0));
    menuArray->addObject(restartGame);
    
    CCMenuItemImage* newGame = CCMenuItemImage::create("menu_quit_normal_CN.png", "menu_quit_normal_CN.png", this, menu_selector(GameStartLayerClass::gameMenuSelCallBack));
    newGame->setTag(GAME_MENU_SEL_PAUSE_SELITEM_SELSTAGE);
    CCSize newGameSize = newGame->getContentSize();
    newGame->setPosition(ccp(gameSelBgSize.width / 2, gameSelBgSize.height * 24 /100.0));
    menuArray->addObject(newGame);
    
    CCMenu* selItemmenu = CCMenu::createWithArray(menuArray);
    selItemmenu->setPosition(CCPointZero);
    gameSelBg->addChild(selItemmenu,GAMEING_MENU_ZORDER);
//}
    
    updateGameCurMoneyLab = CCLabelAtlas::create("52", "Themes/Items/numwhite.png", 13, 26, 46);
    CCAssert(!(updateGameCurMoneyLab == NULL), "cannot be NULL");
    updateGameCurMoneyLab->setPosition(ccp(menuBGSize.width /10, menuBGSize.height * 40 / 100));
    menuBG->addChild(updateGameCurMoneyLab);
    
    menuCenterBG = CCSprite::createWithSpriteFrameName("MenuCenter_01_CN.png");
    CCAssert(!(menuCenterBG == NULL), "cannot be NULL");
    menuCenterBG->setPosition(ccp((menuBGSize.width) / 2, (menuBGSize.height) /2));
    menuBG->addChild(menuCenterBG);
    
    
    CCSize menuCenterBGSize = menuCenterBG->getContentSize();
    curLevelLab = CCLabelAtlas::create("01", "Themes/Items/numyellow.png", 26, 24, 46);
    CCAssert(!(curLevelLab == NULL), "cannot be NULL");
    curLevelLab->setPosition(ccp(menuCenterBGSize.width * 10/ 100, menuCenterBGSize.height * 40 / 100));
    menuCenterBG->addChild(curLevelLab,2);
    
    totalLevelLab = CCLabelAtlas::create("20", "Themes/Items/numwhite.png", 13, 26, 46);
    CCAssert(!(totalLevelLab == NULL), "cannot be NULL");
    totalLevelLab->setPosition(ccp(menuCenterBGSize.width * 45 / 100, menuCenterBGSize.height * 40 /100));
    menuCenterBG->addChild(totalLevelLab,1);
    
    menuArray->removeAllObjects();
    
    gameSpeed2XMenu = CCMenuItemImage::create("speed11.png", "speed12.png", this, menu_selector(GameStartLayerClass::gameMenuSelCallBack));
    gameSpeed2XMenu->setTag(GAME_MENU_SEL_SPEED2X);
    CCSize speed2XSize = gameSpeed2XMenu->getContentSize();
    gameSpeed2XMenu->setPosition(ccp(menuBGSize.width  - menuBGSize.width / 5 - speed2XSize.width / 2, speed2XSize.height / 2));
    menuArray->addObject(gameSpeed2XMenu);
    
    gamePauseMenu = CCMenuItemImage::create("pause01.png", "pause02.png", this, menu_selector(GameStartLayerClass::gameMenuSelCallBack));
    gamePauseMenu->setTag(GAME_MENU_SEL_PAUSE);
    CCSize pauseMenuSize = gamePauseMenu->getContentSize();
    gamePauseMenu->setPosition(ccp(menuBGSize.width  - menuBGSize.width / 8 - pauseMenuSize.width / 2, pauseMenuSize.height / 2));
    menuArray->addObject(gamePauseMenu);
    
    gameSelItemMenu = CCMenuItemImage::create("menu01.png", "menu02.png", this, menu_selector(GameStartLayerClass::gameMenuSelCallBack));
    gameSelItemMenu->setTag(GAME_MENU_SEL_PAUSE_SELITEM);
    CCSize selItemSize = gameSelItemMenu->getContentSize();
    gameSelItemMenu->setPosition(ccp(menuBGSize.width - menuBGSize.width / 18 - selItemSize.width / 2, selItemSize.height / 2));
    menuArray->addObject(gameSelItemMenu);
    
    CCMenu* menu = CCMenu::createWithArray(menuArray);
    menu->setPosition(CCPointZero);
    menuBG->addChild(menu,GAMEING_MENU_ZORDER);
    
    
    //{for boss Mode blood
    
    if (gameModeType == GAME_MODE_TYPE_BOSS) {
        
        menuCenterBG->setVisible(false);
        gameSpeed2XMenu->setVisible(false);
        
        bossTimeBGSprite = CCSprite::createWithSpriteFrameName("honor_0.png");
        CCSize timeBGSize = bossTimeBGSprite->getContentSize();
        //bossTimeBGSprite->setPosition(ccp(size.width * 12/100, -timeBGSize.height));
        LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(bossTimeBGSprite, ccp(size.width * 12/100, -timeBGSize.height/2));
        this->addChild(bossTimeBGSprite,GAMEING_SHOW_GO_ZODER);
        
        memset(combuffer, 0, sizeof(combuffer));
        sprintf(combuffer,"%03d", bossCurTime);
        
        timeLab = CCLabelAtlas::create(combuffer, "Themes/Items/numwhite.png", 13, 26, 46);
        timeLab->setPosition(ccp(timeBGSize.width/5, timeBGSize.height * 15/100));
        bossTimeBGSprite->addChild(timeLab,1);
        
        bossKOSprite = CCSprite::createWithSpriteFrameName("honor_1.png");
        bossKOSprite->setPosition(ccp(timeBGSize.width * 78/100, timeBGSize.height * 42/100));
        bossTimeBGSprite->addChild(bossKOSprite,1);
        
        
        
        bossBloodBG = CCSprite::createWithSpriteFrameName("menublood_01.png");
        CCSize blood1Size = bossBloodBG->getContentSize();
        bossBloodBG->setPosition(ccp(menuBGSize.width  * 52/ 100, menuBGSize.height * 46 /100));
        menuBG->addChild(bossBloodBG,2);
        
        bossBloodMvSprite = CCSprite::createWithSpriteFrameName("menublood_02.png");
        bossBloodMvSprite->setPosition(ccp(blood1Size.width * 79 / 100, blood1Size.height / 2));
        bossBloodBG->addChild(bossBloodMvSprite,1);
        bossBloodMvSprite->setScaleX(0);
        
        
    }
    
}

void GameStartLayerClass::initShowValidPos()
{
	if (mapPutArray && (mapPutArray->count() > 0))
	{
		int count  = mapPutArray->count();

		for (int i = 0; i < count; i++)
		{
			int colum = 0;
			int row = 0;
			MapPassClass* pass = (MapPassClass*)mapPutArray->objectAtIndex(i);
			CCAssert(!(pass == NULL),"cannot be NULL");
			if (pass->getIsCanPutOnMap())
			{
				int k = 0;
				int m = 0;

				CCSize passSize = pass->getAreaSize();
				CCPoint passOrigin = CCSizeMake(pass->getPosition().x - passSize.width / 2,pass->getPosition().y - passSize.height / 2);
				CCSize tiledSize = CCSize(gameMapTiledSize.width,gameMapTiledSize.height);
				colum = passSize.width / tiledSize.width;
				row = passSize.height / tiledSize.height;

				for (int k = 0; k < row; k++)
				{
					for (int j = 0; j < colum; j++)
					{
						float x = gameMapTiledSize.width * j;
						float y =gameMapTiledSize.height * k;
						CCPoint pos = ccp(passOrigin.x + gameMapTiledSize.width / 2 + x,passOrigin.y + gameMapTiledSize.height / 2 + y);
						GameShowValidPos* valid = GameShowValidPos::create();
                        LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(valid, pos);
						//valid->setPosition(pos);
						this->addChild(valid,GAMEING_VALIDPOS_ZORDER);
					}
				}
			}
		}
	}
	
}

void GameStartLayerClass::updateShowGameHelpState(cocos2d::CCPoint pos)
{
    showHelpPL->setPadDictorPos(pos);
    showHelpPL->updateShowHelpPlayState();
}

void GameStartLayerClass::checkGameDoBeforeStart()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    if (isShowGameHelp) {
        showHelpPL = HelpPlayGame::create(this, callfunc_selector(GameStartLayerClass::showGameHelpCallBack),showHelpPlayGamePos);
        this->addChild(showHelpPL,GAMEING_SHOW_HELP_ZODER);
    }
    else if ((GameStageConClass::sharedStageCon()->getShowNewTowerType() > GAME_SUBROUND_ADD_NEW_TOWER_TYPE_NONE && GameStageConClass::sharedStageCon()->getShowNewTowerType() < GAME_SUBROUND_ADD_NEW_TOWER_TYPE_MAX) && (!GameStageConClass::sharedStageCon()->getIsGameReStart())){
        
        showNewTowerFeature = ShowTowerFeatureClass::create(GameStageConClass::sharedStageCon()->getShowNewTowerType(), this, callfunc_selector(GameStartLayerClass::showTowerFeatureBeforeGameCallBack));
        
        this->addChild(showNewTowerFeature,GAMEING_SHOW_NEWTOWER_FEATURE_ZORDER);
        
    }
    else if(!isLogoShowOver)
    {
        if (GameStageConClass::sharedStageCon()->getIsGameReStart()) {
            
            GameStageConClass::sharedStageCon()->setIsGameReStart(false);
            this->gameShowGoBgAniStart();
            this->gameShowStartAni(true);
        }
        else
        {
            GameLogoRotateClass* rotate = GameLogoRotateClass::create(ccp(size.width / 2, size.height / 2), this, callfunc_selector(GameStartLayerClass::logoShowOverCallBack));
            LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(rotate, ccp(size.width / 2, size.height / 2));
            this->addChild(rotate,GAMEING_SHOW_GO_ZODER);
            this->gameShowStartAni(false);
        }
    }
}

void GameStartLayerClass::whaleLayerCallBack()
{
    gameSpeed2XMenu->setVisible(true);
    menuCenterBG->setVisible(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void GameStartLayerClass::showGameHelpCallBack()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    CCSize layerScale = LcdAdapClass::sharedLCDADAP()->getLayerScaleSize();
    HELP_PLAYGAME_STATE_TYPE helpType = showHelpPL->getHelpStateType();
    
    switch (helpType) {
        case HELP_PLAYGAME_STATE_TYPE_START:
            {
                
            }
            break;
        case HELP_PLAYGAME_STATE_TYPE_PRE_SEL:
            {
                
                
                isSelPutTower = false;
                userTouchPos = showHelpPlayGamePos;
                
                CCPoint padPos = ccpAdd(showHelpPlayGamePos, ccp(-30 * LcdAdapClass::sharedLCDADAP()->getXScale(),62 * LcdAdapClass::sharedLCDADAP()->getYScale()));//scale
                showHelpPL->setPadDictorPos(padPos);
                this->updateUserTouchEndEvent(userTouchPos);
            }
            break;
        case HELP_PLAYGAME_STATE_TYPE_SELECT_TOWER:
            {
                userTouchPos = showHelpPlayGamePos;
                showHelpPL->setPadDictorPos(showHelpPlayGamePos);
                showHelpPL->updateShowHelpPlayState();
            }
            break;
        case HELP_PLAYGAME_STATE_TYPE_PRE_UPDATE:
            {
//                this->checkIsCanPutOnMap(showHelpPlayGamePos);
                CCPoint padPos = ccpAdd(showHelpPlayGamePos, ccp(0,52 * LcdAdapClass::sharedLCDADAP()->getYScale()));//scale
                showHelpPL->setPadDictorPos(padPos);
                this->updateUserTouchEndEvent(showHelpPlayGamePos);
            }
            break;
        case HELP_PLAYGAME_STATE_TYPE_UPDATE_TOWER:
            {
                showHelpPL->updateShowHelpPlayState();
            }
            break;
        case HELP_PLAYGAME_STATE_TYPE_SELL_TOWER:
            {
                showHelpPL->setPadDictorPos(showHelpPlayGamePos);
                showHelpPL->restartHelpNow();
            }
            break;
        case HELP_PLAYGAME_STATE_TYPE_HELP_OVER:
            {
                showHelpPL->removeFromParentAndCleanup(true);
                showHelpPL = NULL;
                isShowGameHelp = false;


                if (!isLogoShowOver) {
//                    GameLogoRotateClass* rotate = GameLogoRotateClass::create(ccp(size.width / 2, size.height / 2), this, callfunc_selector(GameStartLayerClass::logoShowOverCallBack));
//                    
//                    this->addChild(rotate,GAMEING_SHOW_GO_ZODER);
                    GameLogoRotateClass* rotate = GameLogoRotateClass::create(ccp(size.width / 2, size.height / 2), this, callfunc_selector(GameStartLayerClass::logoShowOverCallBack));
                    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(rotate, ccp(size.width / 2, size.height / 2));
                    this->addChild(rotate,GAMEING_SHOW_GO_ZODER);
                    this->gameShowStartAni(false);
                }
            }
            break;
        default:
            break;
    }
}

void GameStartLayerClass::initGame()
{
    char pFileName[100] = {0};
    char pBuffer[100] = {0};
    CCArray* aniArray = CCArray::create();
    
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    xScale = 1.0f;
    yScale = 1.0f;
    isGameShowGift = false;
    isGameShowWhale = false;
    isAllObjectClear = false;
    isLastFinall = false;
    isAllMonstersDead = false;
    isGamePause = false;
    isGameSpeed2X = false;
    isGameSelItem = false;
    gameBGSprite = NULL;
    userSelTower = NULL;
    addEnemyNum = 0;
    addEnemyTimeCounter = 0;
	gameCurMoney = 0;
    proCaraton = NULL;
    isShowGameHelp = false;
    isGameRealStartNow = false;
    isLogoShowOver = false;
    showHelpPL = NULL;
    userSelEnemy = NULL;
    bossSelSprite = NULL;
    isNowAddMonster = false;
    gameModeType = GameStageConClass::sharedStageCon()->getGameModeType();
    bossCurTime = GameStageConClass::sharedStageCon()->getBossTimeLimit();
    isLayerOver = false;
    isUserTouched = false;
    isCheckTouchValiding = false;
    isSelPutTower = false;
    userTouchPos = ccp(0,0);
    gameWhale = NULL;
    
    showHelpPlayGamePos = ccp(0,0);
    //isShowGameHelp = true;
    if (GameStageConClass::sharedStageCon()->getGameStageIndex() == (int)GAME_STAGE_TYPE_SKY && GameStageConClass::sharedStageCon()->getGameStageRoundIndex() == 1) {
        isShowGameHelp = true;//means 第一个主题第一个关卡显示帮助
    }
    
    
    
    userTouchType = GAME_USER_TOUCH_TYPE_NONE;
    gameMapTiledSize = CCSizeMake(0, 0);
    
    pathArray = CCArray::create();
    pathArray->retain();
    mapPutArray = CCArray::create();
    mapPutArray->retain();
    deadSpriteArray = CCArray::create();
    deadSpriteArray->retain();
    enemyArray = CCArray::create();
    enemyArray->retain();
    
    enemyMonsterArray = CCArray::create();
    enemyMonsterArray->retain();
    enemyObjectArray = CCArray::create();
    enemyObjectArray->retain();
    
    towerArray = CCArray::create();
    towerArray->retain();
    bulletArray = CCArray::create();
    bulletArray->retain();
    bulletEffectArray = CCArray::create();
    bulletEffectArray->retain();
    towerShowUpArray = CCArray::create();
    towerShowUpArray->retain();
    
    addEnemyPlan = GameAddEnemyClass::create(GameStageConClass::sharedStageCon()->getGameStageIndex());
    this->addChild(addEnemyPlan);
    
    CCTMXTiledMap* map = NULL;
    
    if (gameModeType == GAME_MODE_TYPE_BOSS) {
        if (((GAME_STAGE_TYPE)GameStageConClass::sharedStageCon()->getGameStageIndex() == GAME_STAGE_TYPE_BOSS_MODE))
        {
            memset(pBuffer, 0, sizeof(pBuffer));
            sprintf(pBuffer, "Themes/Theme%d/BG0/BG%d-hd.plist",bossStageThemeConfig[GameStageConClass::sharedStageCon()->getGameStageRoundIndex()].gameStageId,GameStageConClass::sharedStageCon()->getGameThemeBGColorID());
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            
            memset(pFileName, 0, sizeof(pFileName));
            sprintf(pFileName, "Themes/Theme%d/Items/Monsters01-hd.plist",bossStageThemeConfig[GameStageConClass::sharedStageCon()->getGameStageRoundIndex()].gameStageId);
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pFileName);
            
            memset(pFileName, 0, sizeof(pFileName));
            sprintf(pFileName, "Themes/Theme%d/Items/Object%02d-hd.plist",bossStageThemeConfig[GameStageConClass::sharedStageCon()->getGameStageRoundIndex()].gameStageId,GameStageConClass::sharedStageCon()->getGameThemeBGColorID());
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pFileName);
            
            memset(pBuffer, 0, sizeof(pBuffer));
            sprintf(pBuffer, "Themes/Theme%d/BG%d/BG-hd.plist",bossStageThemeConfig[GameStageConClass::sharedStageCon()->getGameStageRoundIndex()].gameStageId,bossStageThemeConfig[GameStageConClass::sharedStageCon()->getGameStageRoundIndex()].gameThemeMapID);
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
        }
    }
    else if (gameModeType == GAME_MODE_TYPE_ADVENTURE)
    {
        if (((GAME_STAGE_TYPE)GameStageConClass::sharedStageCon()->getGameStageIndex() == GAME_STAGE_TYPE_EXTRE)) {
            
            memset(pBuffer, 0, sizeof(pBuffer));
            sprintf(pBuffer, "Themes/Theme%d/BG0/BG%d-hd.plist",extremeMapThemeId[GameStageConClass::sharedStageCon()->getGameStageRoundIndex()],GameStageConClass::sharedStageCon()->getGameThemeBGColorID());
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            
            memset(pFileName, 0, sizeof(pFileName));
            sprintf(pFileName, "Themes/Theme%d/Items/Monsters01-hd.plist",extremeMapThemeId[GameStageConClass::sharedStageCon()->getGameStageRoundIndex()]);
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pFileName);
            
            memset(pFileName, 0, sizeof(pFileName));
            sprintf(pFileName, "Themes/Theme%d/Items/Object%02d-hd.plist",extremeMapThemeId[GameStageConClass::sharedStageCon()->getGameStageRoundIndex()],GameStageConClass::sharedStageCon()->getGameThemeBGColorID());
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pFileName);
            
            memset(pBuffer, 0, sizeof(pBuffer));
            sprintf(pBuffer, "Themes/Theme%d/BG%d/BG-hd.plist",GameStageConClass::sharedStageCon()->getGameStageIndex(),GameStageConClass::sharedStageCon()->getGameStageRoundIndex());
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
        }
        else
        {
            memset(pBuffer, 0, sizeof(pBuffer));
            sprintf(pBuffer, "Themes/Theme%d/BG0/BG%d-hd.plist",GameStageConClass::sharedStageCon()->getGameStageIndex(),GameStageConClass::sharedStageCon()->getGameThemeBGColorID());
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            
            memset(pFileName, 0, sizeof(pFileName));
            sprintf(pFileName, "Themes/Theme%d/Items/Monsters01-hd.plist",GameStageConClass::sharedStageCon()->getGameStageIndex());
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pFileName);
            
            memset(pFileName, 0, sizeof(pFileName));
            sprintf(pFileName, "Themes/Theme%d/Items/Object%02d-hd.plist",GameStageConClass::sharedStageCon()->getGameStageIndex(),GameStageConClass::sharedStageCon()->getGameThemeBGColorID());
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pFileName);
            
            memset(pBuffer, 0, sizeof(pBuffer));
            sprintf(pBuffer, "Themes/Theme%d/BG%d/BG-hd.plist",GameStageConClass::sharedStageCon()->getGameStageIndex(),GameStageConClass::sharedStageCon()->getGameStageRoundIndex());
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
        }
    }
    
    
    memset(pBuffer, 0, sizeof(pBuffer));
    sprintf(pBuffer, "BG%d.png",GameStageConClass::sharedStageCon()->getGameThemeBGColorID());
    gameBGSprite = CCSprite::createWithSpriteFrameName(pBuffer);
    gameBGSprite->getTexture()->setAliasTexParameters();
    CCSize bgSize = gameBGSprite->getContentSize();
    xScale = size.width/bgSize.width;
    yScale = size.height/bgSize.height;
    
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(gameBGSprite, ccp(size.width/2, size.height/2));
    this->addChild(gameBGSprite,1);
    
    
    this->loadCommonImgAndInitGameMenu();
    this->initTower();
	
    
    
    
    towerShowPad = TowerSelPadClass::create(this, callfunc_selector(GameStartLayerClass::selTowerPadCallBack));
    this->addChild(towerShowPad,GAMEING_TOWER_SHOWPAD_ZODER);
    
    userTowerAdd = TowerAddTypeClass::create(this, callfunc_selector(GameStartLayerClass::addTowerSelCallBack));
    userTowerAdd->setValidTowerType(GameStageConClass::sharedStageCon()->getGameStageAddTowerType());
    this->addChild(userTowerAdd,GAMING_TOWER_ADD_ZODER);
    
    memset(pBuffer, 0, sizeof(pBuffer));
    sprintf(pBuffer, "%02d",GameStageConClass::sharedStageCon()->getGameStageSubRoundIndex());
    curLevelLab->setString(pBuffer);
    
    memset(pBuffer, 0, sizeof(pBuffer));
    sprintf(pBuffer, "%d",GameStageConClass::sharedStageCon()->getGameStageSubRoundNum());
    totalLevelLab->setString(pBuffer);
    
    
    
    
    CCSprite* path = CCSprite::createWithSpriteFrameName("Path.png");
    path->getTexture()->setAliasTexParameters();
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(path, ccp(size.width/2, size.height/2));
    this->addChild(path,GAMEING_PATH_ZODER);
    
    
    
    if (gameModeType == GAME_MODE_TYPE_BOSS) {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "Themes/Theme%d/BG%d/BGPath.tmx",bossStageThemeConfig[GameStageConClass::sharedStageCon()->getGameStageRoundIndex()].gameStageId,bossStageThemeConfig[GameStageConClass::sharedStageCon()->getGameStageRoundIndex()].gameThemeMapID);
    }
    else
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "Themes/Theme%d/BG%d/BGPath.tmx",GameStageConClass::sharedStageCon()->getGameStageIndex(),GameStageConClass::sharedStageCon()->getGameStageRoundIndex());
    }
    
    
    map = CCTMXTiledMap::create(pBuffer);
    LcdAdapClass::sharedLCDADAP()->setGameMapTiledSize(map->getTileSize());
    gameMapTiledSize = LcdAdapClass::sharedLCDADAP()->getGameMapTiledSize();
    CCLog("the tiled width  = %f height = %f",gameMapTiledSize.width,gameMapTiledSize.height);
    mapObjectGroup = map->objectGroupNamed("PATH");
    CCDictionary* dic = NULL;
    
    int posIndex = 0;
    
    float tileWidth = map->getTileSize().width;
    float tileHight = map->getTileSize().height;
    do {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "PT%d",(posIndex + 1));
        posIndex++;
        dic = mapObjectGroup->objectNamed(pBuffer);
        if (dic != NULL) {
            float x = dic->valueForKey("x")->floatValue();
            float y = dic->valueForKey("y")->floatValue();
            x += tileWidth / 2;
            y -= tileHight / 2;
            CCNode* node = CCNode::create();
            //            node->setPosition(ccp(x, y));
            LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(node, ccp(x,y));
            LcdAdapClass::sharedLCDADAP()->setAdaptorMapPos(node, ccp(x,y));
            CCAssert(!(pathArray == NULL), "cannot be NULL");
            pathArray->addObject(node);
        }
    } while ((dic != NULL));
    
    dic = NULL;
    posIndex = 0;
    AllObjectNum = 0;
    do {
        for (int i = 0; i < 50; i++) {
            memset(pBuffer, 0, sizeof(pBuffer));
            sprintf(pBuffer, "%dOb%d",(posIndex + 1),(i + 1));
            dic = mapObjectGroup->objectNamed(pBuffer);
            if (dic != NULL) {
                float x = dic->valueForKey("x")->floatValue();
                float y = dic->valueForKey("y")->floatValue();
                float width = dic->valueForKey("width")->floatValue();
                float height = dic->valueForKey("height")->floatValue();
                int objectID = dic->valueForKey("type")->intValue();
                x += width/ 2;
                y += height/2;
                memset(pFileName, 0, sizeof(pFileName));
                sprintf(pFileName, "cloud%02d.png", (posIndex + 1));
                //                CCSprite* sprite = CCSprite::createWithSpriteFrameName(pFileName);
                EnemySpriteClass* object = EnemySpriteClass::createEnemy(pFileName, (GAME_ENEMY_OBJECT_LIFE + (i + 1) * 20), 50, pathArray);
                object->setEnemyType(GAME_ENEMY_TYPE_OBJECT);
                object->setDeathArray(deadSpriteArray);
                object->setEnemyObjectID(objectID);
                object->setEnemyObjectToTowerNum_X(width / tileWidth);
                object->setEnemyObjectToTowerNum_Y(height / tileHight);
                enemyObjectArray->addObject(object);
                CCPoint adaptorMapPos = LcdAdapClass::sharedLCDADAP()->setAdaptorMapPos(object, ccp(x,y));
                this->addChild(object,GAMEING_ENEMY_OBJECT_ZORDER);
                this->enemyArray->addObject(object);
                AllObjectNum++;
                MapPassClass* mapPos = MapPassClass::create(adaptorMapPos, CCSize(width * LcdAdapClass::sharedLCDADAP()->getMapXScale(), height * LcdAdapClass::sharedLCDADAP()->getMapYScale()));
                this->mapPutArray->addObject(mapPos);
            }
            
            
            memset(pBuffer, 0, sizeof(pBuffer));
            sprintf(pBuffer, "%dT%d",(posIndex + 1),(i + 1));
            dic = mapObjectGroup->objectNamed(pBuffer);
            if (dic != NULL) {
                float x = dic->valueForKey("x")->floatValue();
                float y = dic->valueForKey("y")->floatValue();
                float width = dic->valueForKey("width")->floatValue();
                float height = dic->valueForKey("height")->floatValue();
                x += width/ 2;
                y += height/2;
                MapPassClass* mapPos = MapPassClass::create(LcdAdapClass::sharedLCDADAP()->setAdaptorMapPos(ccp(x,y)), CCSize(width * LcdAdapClass::sharedLCDADAP()->getMapXScale(), height * LcdAdapClass::sharedLCDADAP()->getMapYScale()));
                mapPos->setIsCanPutOnMap(true);
                this->mapPutArray->addObject(mapPos);
                
                int objectID = dic->valueForKey("type")->intValue();
                if (objectID > 0) {
                    GAME_TOWER_TYPE towerType = objectTowerBuffer[objectID].towerType;
                    this->checkIsCanPutOnMap(LcdAdapClass::sharedLCDADAP()->setAdaptorMapPos(ccp(x,y)));//这里会更正位置并把值放在userTouchPos
                    this->addGameTowerType(towerType, userTouchPos);
                }
                
            }
            
        }
        
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "Obj%d",(posIndex + 1));
        dic = mapObjectGroup->objectNamed(pBuffer);
        if (dic != NULL) {
            float x = dic->valueForKey("x")->floatValue();
            float y = dic->valueForKey("y")->floatValue();
            float width = dic->valueForKey("width")->floatValue();
            float height = dic->valueForKey("height")->floatValue();
            x += width/ 2;
            y += height/2;
            MapPassClass* mapPos = MapPassClass::create(LcdAdapClass::sharedLCDADAP()->setAdaptorMapPos(ccp(x,y)), CCSize(width * LcdAdapClass::sharedLCDADAP()->getMapXScale(), height * LcdAdapClass::sharedLCDADAP()->getMapYScale()));
            mapPos->setIsCanPutOnMap(true);
            this->mapPutArray->addObject(mapPos);
            
            if (isShowGameHelp) {
                if (posIndex == 0) {
                    showHelpPlayGamePos = ccp(x,y);
                }
            }
        }
        posIndex++;
    } while (posIndex < 50);
    
    this->initShowValidPos();
    
    CCNode* firstPos = (CCNode*)pathArray->objectAtIndex(0);
    CCNode* secPos = (CCNode*)pathArray->objectAtIndex(1);
    CCSprite* startPng = CCSprite::createWithSpriteFrameName("start01.png");
    CCPoint pos = firstPos->getPosition();

    CCPoint diffPos = ccpSub(secPos->getPosition(), firstPos->getPosition());
    float xOffset = 0;
    float yOffset = 0;
    
    if (diffPos.x >= -0.0000001 && diffPos.x <= 0.0000001) {
        xOffset = 0;
        if (diffPos.y > 0.0000001) {
            yOffset = 0;
        }
        else if(diffPos.y < -0.0000001)
        {
            yOffset = 1;
        }
    }
    else if (diffPos.y >= -0.0000001 && diffPos.y <= 0.0000001)
    {
        yOffset = 1;
//        if (diffPos.x > 0.0000001) {
//            xOffset = -1;
//        }
//        else if (diffPos.x < -0.0000001)
//        {
//            xOffset = 1;
//        }
    }
    
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(startPng, ccp(pos.x, pos.y + yOffset * tileHight  / 2));
    this->addChild(startPng,GAMEING_START_POS_ZORDER);
    
    
	gameCurMoney = GameStageConClass::sharedStageCon()->getGameStageRoundMoney();
	HUDClass::sharedHUD()->setHUDMoney(gameCurMoney);
	sprintf(pBuffer,"%d",gameCurMoney);
	updateGameCurMoneyLab->setString(pBuffer);
    
    userSelEnemyPointSprite = CCSprite::createWithSpriteFrameName("point01.png");
    userSelEnemyPointSprite->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
    userSelEnemyPointSprite->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());
    userSelEnemyPointSprite->setVisible(false);
    this->addChild(userSelEnemyPointSprite,GAMEING_USER_SEL_ENEMY_ZORDER);
    for (int i = 1; i < 4; i++) {
        memset(combuffer, 0, sizeof(combuffer));
        sprintf(combuffer, "point%02d.png",i);
        aniArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(combuffer));
    }
    userSelEnemyPointSprite->runAction(CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(aniArray,0.25))));
    
    
    if (gameModeType == GAME_MODE_TYPE_ADVENTURE) {//add game mode here
        
        int num = pathArray->count();
        CCNode* posNode = NULL;
        
        
        if (num > 2) {
            posNode = (CCNode*)pathArray->objectAtIndex(num - 2);
            proCaraton = CaratonProClass::create(posNode->getPosition());
        }
        else
        {
            proCaraton = CaratonProClass::create(ccp(0,0));
        }
        
        LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(proCaraton, posNode->getPosition());
        this->addChild(proCaraton,GAMEING_CARATON_ZORDER);
    }
    
//    if (gameModeType == GAME_MODE_TYPE_BOSS) {
//        this->initBossTimeBG();
//    }
    
    this->checkGameDoBeforeStart();
    this->scheduleUpdate();
}


bool GameStartLayerClass::init()
{
    
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(this);
    loadWaitSprite = CCSprite::create("loading-hd.png");
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(loadWaitSprite, ccp(size.width /2, size.height /2));
    this->addChild(loadWaitSprite,GAMING_LOADING_ZODER);
    
//    loadWaitSprite->runAction(CCSequence::create(CCMoveBy::create(1, ccp(0, 0)),CCCallFunc::create(this, callfunc_selector(GameStartLayerClass::loadingAniCallBack))));
    
    return true;
}

void GameStartLayerClass::loadingAniCallBack()
{
//    loadWaitSprite->stopAllActions();
//    this->initGame();
//    
//    loadWaitSprite->removeFromParentAndCleanup(true);
}

void GameStartLayerClass::initBossTimeBG()
{
//    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
//    
//    if (menuCenterBG != NULL) {
//        menuCenterBG->setVisible(false);
//    }
//    
//    if (gameSpeed2XMenu != NULL) {
//        gameSpeed2XMenu->setVisible(false);
//    }
//    
//    bossTimeBGSprite = CCSprite::createWithSpriteFrameName("honor_0.png");
//    CCSize timeBGSize = bossTimeBGSprite->getContentSize();
//    //bossTimeBGSprite->setPosition(ccp(size.width * 12/100, -timeBGSize.height));
//    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(bossTimeBGSprite, ccp(size.width * 12/100, -timeBGSize.height));
//    this->addChild(bossTimeBGSprite,GAMEING_SHOW_GO_ZODER);
//    
//    
//    
//    timeLab = CCLabelAtlas::create("000", "Themes/Items/numwhite.png", 13, 26, 46);
//    timeLab->setPosition(ccp(timeBGSize.width/5, timeBGSize.height * 28/100));
//    bossTimeBGSprite->addChild(timeLab,1);
//    
//    bossKOSprite = CCSprite::createWithSpriteFrameName("honor_1.png");
//    bossKOSprite->setPosition(ccp(timeBGSize.width * 78/100, timeBGSize.height * 42/100));
//    bossTimeBGSprite->addChild(bossKOSprite,1);
//    
//    
//    
//    bossBloodBG = CCSprite::createWithSpriteFrameName("menublood_01.png");
//    CCSize blood1Size = bossBloodBG->getContentSize();
//    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(bossBloodBG, ccp(size.width  * 40/ 100, size.height * 94 /100));
//    this->addChild(bossBloodBG,GAMEING_BOSS_BLOOD_ZORDER);
//    
//    bossBloodMvSprite = CCSprite::createWithSpriteFrameName("menublood_02.png");
//    bossBloodMvSprite->setPosition(ccp(blood1Size.width * 79 / 100, blood1Size.height / 2));
//    bossBloodBG->addChild(bossBloodMvSprite,1);
//    bossBloodMvSprite->setScaleX(0);
    
    
    
}

void GameStartLayerClass::initBossTimeBGAniCallBack()
{
    
}

void GameStartLayerClass::updateBossModeBloodValue()
{
    //static int curLife = 1000;
    
    CCAssert(!(bossSelSprite == NULL), "cannot be NULL");
    
    CCSize bloodBGSize = bossBloodBG->getContentSize();
    CCSize blood2Size =  bossBloodMvSprite->getContentSize();
    float validWidth = 0;
    float bloodBGValidWidth = 342;//血量实际长度，BLOODBGSize是整个长度，包含透明部分
    float validBloodBGWidth = 350;//修正长度

    int totalValue = bossSelSprite->getTotalLifeValue();
    int curLife = bossSelSprite->getCurLifeValue();
    
    bool isAddMonstersFinish = addEnemyPlan->checkIsAddMonstersFinish();
    int monstersNum = addEnemyPlan->getAddMonsterNum();
    
    validWidth = validBloodBGWidth - (bloodBGValidWidth * curLife / totalValue);
    
    bossBloodMvSprite->setPosition(ccp(((bloodBGValidWidth * curLife / totalValue) + validWidth / 2), bloodBGSize.height / 2));
    bossBloodMvSprite->setScaleX(validWidth/blood2Size.width);
    
    if (curLife <= 0) {
        monstersNum -= 1;
        addEnemyPlan->setMonsterNum(monstersNum);
    }
    
    if (monstersNum <= 0 && isAddMonstersFinish) {
        isLayerOver = true;
        GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_ITEM_GAME_WIN);
        this->gamePauseOrSpeedSpriteState(false,true);
        isGameRealStartNow = false;
//        this->unscheduleUpdate();
        GameStageConClass::sharedStageCon()->setGameBossLastTime(bossCurTime);
        this->unschedule(schedule_selector(GameStartLayerClass::updateBossTimeBgState));
        gameWinLoseStruct tmp;
        tmp.curRoundIndex = GameStageConClass::sharedStageCon()->getGameStageRoundIndex();
        tmp.curSubRoundIndex = GameStageConClass::sharedStageCon()->getGameStageSubRoundIndex();
        tmp.gameModeType = GAME_MODE_TYPE_BOSS;
        tmp.gameWinLoseType = GAME_WINLOSE_TYPE_WIN;
        tmp.totalSubRoundNum = GameStageConClass::sharedStageCon()->getGameStageSubRoundNum();
        ShowWinLoseClass::sharedShow(tmp)->showGameOver(this);
        
        {
            gameLevelInfoStruct info;
            
            info.isLevelLocked = false;
            info.isClearAllObject = isAllObjectClear;
            info.UserGained = 0;
            
            if (bossCurTime >=0 && bossCurTime <=(GameStageConClass::sharedStageCon()->getBossTimeLimit() * 30/100.0)) {
                info.UserGained = 1;
            }
            else if(bossCurTime >= (GameStageConClass::sharedStageCon()->getBossTimeLimit() * 40 / 100.0) && bossCurTime <=(GameStageConClass::sharedStageCon()->getBossTimeLimit() * 60 /100.0)){
                info.UserGained = 2;
            }
            else if (bossCurTime >= (GameStageConClass::sharedStageCon()->getBossTimeLimit() * 70 / 100.0) && bossCurTime <=(GameStageConClass::sharedStageCon()->getBossTimeLimit())){
                info.UserGained = 3;
            }
            
            HUDClass::sharedHUD()->setGameCurLevelInfo(info, (GAME_STAGE_TYPE)GameStageConClass::sharedStageCon()->getGameStageIndex(), GameStageConClass::sharedStageCon()->getGameStageRoundIndex());
            
            
            int tmpStageRoundNum = GameStageConClass::sharedStageCon()->getGameStageRoundNum();
            int tmpStageRoundIndex = GameStageConClass::sharedStageCon()->getGameStageRoundIndex();
            
            if (GameStageConClass::sharedStageCon()->getGameModeType() == GAME_MODE_TYPE_BOSS) {
                int tmpStageIndex = GameStageConClass::sharedStageCon()->getGameStageIndex();
                
                info.isClearAllObject = false;
                info.UserGained = 0;
                info.isLevelLocked = false;
                
                
                if (tmpStageRoundIndex < tmpStageRoundNum) {
                    tmpStageRoundIndex += 1;
                    HUDClass::sharedHUD()->setGameCurLevelInfo(info, (GAME_STAGE_TYPE)tmpStageIndex, tmpStageRoundIndex);
                }
                
                
            }
        }
    }
    
}

void GameStartLayerClass::updateBossTimeBgState(float delta)
{
    bossCurTime -= 1;
    if (bossCurTime <0) {
        bossCurTime = 0;
    }
    
    
    this->unschedule(schedule_selector(GameStartLayerClass::updateBossTimeBgState));
    memset(combuffer, 0, sizeof(combuffer));
    sprintf(combuffer, "%03d",bossCurTime);
    timeLab->setString(combuffer);
    
    if (bossCurTime == 0) {
        isLayerOver = true;
        GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_ITEM_GAME_LOSE);
        this->gamePauseOrSpeedSpriteState(false,true);
        this->isGameRealStartNow = false;
        this->unschedule(schedule_selector(GameStartLayerClass::updateBossTimeBgState));
//        this->unscheduleUpdate();
        gameWinLoseStruct tmp;
        tmp.curRoundIndex = GameStageConClass::sharedStageCon()->getGameStageRoundIndex();
        tmp.curSubRoundIndex = GameStageConClass::sharedStageCon()->getGameStageSubRoundIndex();
        tmp.gameModeType = GAME_MODE_TYPE_BOSS;
        tmp.gameWinLoseType = GAME_WINLOSE_TYPE_LOSE;
        tmp.totalSubRoundNum = GameStageConClass::sharedStageCon()->getGameStageSubRoundNum();
        ShowWinLoseClass::sharedShow(tmp)->showGameOver(this);
    }
    else
    {
        if (isGameRealStartNow) {
            this->schedule(schedule_selector(GameStartLayerClass::updateBossTimeBgState), 1);
        }
    }
    
    
}


void GameStartLayerClass::logoShowOverCallBack()
{
//    this->setTouchEnabled(true);
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
//    isLogoShowOver = true;
    GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_ITEM_GO);
    this->gameShowGoBgAniStart();
}



void GameStartLayerClass::gameShowGoBgAniStart()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    gameGoBgSprite = CCSprite::createWithSpriteFrameName("countdown_11.png");
    gameGoBgSprite->setVisible(false);
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(gameGoBgSprite, ccp(size.width/2, size.height/2));
    
    gameGoBgSprite->runAction(CCSequence::create(CCMoveBy::create(0.15, ccp(0, 0)),CCCallFuncN::create(this, callfuncN_selector(GameStartLayerClass::gameShowGoBgAniCallBack)),NULL));
    this->addChild(gameGoBgSprite,GAMEING_SHOW_GO_ZODER);
}

void GameStartLayerClass::gameShowGoBgAniCallBack(cocos2d::CCNode *node)
{
    CCSize size = gameGoBgSprite->getContentSize();
    
    gameGoBgSprite->setVisible(true);
    CCSprite* go = CCSprite::createWithSpriteFrameName("countdown_13.png");
    go->setPosition(ccp(size.width/2, size.height/2));
    go->setScale(1.5);
    
    go->runAction(CCSequence::create(CCScaleTo::create(0.15, 1),CCMoveBy::create(0.5, ccp(0, 0)),CCCallFuncN::create(this, callfuncN_selector(GameStartLayerClass::gameShowGoAniCallBack)),NULL));
    
    gameGoBgSprite->addChild(go,1);
    //LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(go, ccp(size.width/2, size.height/2));
    
}

void GameStartLayerClass::gameShowGoAniCallBack(cocos2d::CCNode *node)
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    CCSprite* go = (CCSprite*)node;
    
    go->stopAllActions();
    isGameRealStartNow = true;
    if (gameModeType == GAME_MODE_TYPE_BOSS) {
        
        
        gameGoBgSprite->runAction(CCSequence::create(CCMoveTo::create(0.5, ccp(size.width * 12/100, -1)),CCCallFuncN::create(this, callfuncN_selector(GameStartLayerClass::gameShowGoMoveAniCallBack)),NULL));
    }
    else
    {
        gameGoBgSprite->removeFromParentAndCleanup(true);
        gameGoBgSprite = NULL;
        
        
        
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
        isLogoShowOver = true;
    }
}

void GameStartLayerClass::gameShowGoMoveAniCallBack(cocos2d::CCNode *node)
{
    CCSize timeBGSize = bossTimeBGSprite->getContentSize();

    gameGoBgSprite->removeFromParentAndCleanup(true);
    gameGoBgSprite = NULL;
    
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
    isLogoShowOver = true;
    
    bossTimeBGSprite->runAction(CCSequence::create(CCMoveBy::create(0.25, ccp(0, timeBGSize.height * 3/2)),CCCallFunc::create(this, callfunc_selector(GameStartLayerClass::initBossTimeBGAniCallBack)),NULL));
}



CCScene* GameStartLayerClass::createGameStart()
{
    CCScene* scene = NULL;
    
    do {
        scene = CCScene::create();
        CC_BREAK_IF(!scene);
        
        GameStartLayerClass* startGame = GameStartLayerClass::create();
        CC_BREAK_IF(!startGame);
        
        scene->addChild(startGame);
        
    } while (0);
    
    return scene;
}

void GameStartLayerClass::onEnter()
{
    CCLayer::onEnter();
    this->initGame();
    loadWaitSprite->removeFromParentAndCleanup(true);
}

void GameStartLayerClass::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

bool GameStartLayerClass::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void GameStartLayerClass::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (isGameRealStartNow) {
        
    }
}

void GameStartLayerClass::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (isGameRealStartNow) {
        CCPoint curPos = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        userTouchPos = this->convertToNodeSpace(pTouch->getLocation());
        this->updateUserTouchEndEvent(userTouchPos);
    }
}


void GameStartLayerClass::updateUserTouchEndEvent(cocos2d::CCPoint pos)
{
    int i = 0;
    bool isFindEnemy = false;
    bool isFindTower = false;
    EnemySpriteClass* enemy = NULL;
    if (enemyArray && enemyArray->count()) {
        do {
            if (i < enemyArray->count()) {
                enemy = (EnemySpriteClass*)enemyArray->objectAtIndex(i);
                i++;
                if (enemy && !(enemy->getIsDead()) && enemy->retainCount() > 0) {
                    CCSize enemySize = enemy->getContentSize();
                    
                    enemySize.width *= LcdAdapClass::sharedLCDADAP()->getXScale();
                    enemySize.height *= LcdAdapClass::sharedLCDADAP()->getYScale();
                    
                    CCPoint enemyPos = enemy->getPosition();
                    CCRect enemyRect = CCRect(enemyPos.x - enemySize.width / 2, enemyPos.y - enemySize.height / 2, enemySize.width, enemySize.height);
                    if (enemyRect.containsPoint(pos)) {
                        isFindEnemy = true;
                        userSelEnemy = enemy;
                        userSelEnemyPointSprite->setVisible(true);
                        break;
                    }
                }
            }
            else
            {
                break;
            }
        } while (1);
    }
    
    if (isFindEnemy && towerArray && towerArray->count()) {
        int index = 0;
        AttackTowerClass* tower = NULL;
        do {
            if (index < towerArray->count()) {
                tower = (AttackTowerClass*)towerArray->objectAtIndex(index);
                index++;
                if (tower && enemy) {
                    if (tower->userSetAttackObject(enemy)) {
                        isFindTower = true;
                        //break;
                    }
                }
            }
            else
            {
                break;
            }
        } while (tower != NULL);
    }
    
    if (!isFindTower && !isFindEnemy) {
        if (gameModeType == GAME_MODE_TYPE_ADVENTURE) {
            CCSize caratonSize = proCaraton->getCaratonSize();
            CCPoint caratonPos = proCaraton->getPosition();
            CCRect caratonRect = CCRect(caratonPos.x - caratonSize.width /2, caratonPos.y - caratonSize.height / 2, caratonSize.width, caratonSize.height);
            if (caratonRect.containsPoint(pos)) {
                proCaraton->userTouchCaraton();
                return;
            }
        }
    }
    
    if (!isFindTower || !isFindEnemy) {
        
        if (isSelPutTower || userSelTower) {
            if (isSelPutTower) {
                userTowerAdd->hideAddTowerType();
                isSelPutTower = false;
            }
            
            if (userSelTower != NULL) {
                towerShowPad->hideUpSelPad(userSelTower);
                userSelTower->setZOrder(20);
                userSelTower = NULL;
                
            }
            
            
        }
        else if (!isSelPutTower && userSelTower == NULL) {
            isSelPutTower = this->checkIsCanPutOnMap(pos);
            
            if (isSelPutTower) {
                if (!userTowerAdd->getIsShowAddTowerType()) {
                    userTowerAdd->setPosition(userTouchPos);
                    userTowerAdd->showAddTowerType();
                }
            }
            
            if (userSelTower != NULL) {
                userSelTower->setZOrder(GAMEING_TOWER_SHOWPAD_ZODER);
                towerShowPad->showUpSelPad(userSelTower);
                
            }
            else if (!isSelPutTower && !isFindEnemy)
            {
                this->gameShowStopIconAniStart(pos);
            }
        }
        else //show stop icon
        {
            if(!isGameShowWhale && !isGameShowGift)
            {
                this->gameShowStopIconAniStart(pos);
            }
            
        }
    }
}


void GameStartLayerClass::spriteHurtedAniStart(cocos2d::CCPoint pos)
{
    int index = 20;
    int maxNum = 5;
    char buffer[12] = {0};
    CCSprite* air = NULL;
    CCArray* aniArray = new CCArray();
    CCSpriteFrame* frame = NULL;
    
    for (int i = index; i< (index + maxNum); i++) {
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "air%02d.png",(i+1));
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
        if (i == index) {
            air = CCSprite::createWithSpriteFrame(frame);
            air->setPosition(pos);
            this->addChild(air,GAMEING_SHOW_COM_ANI);
        }
        aniArray->addObject(frame);
    }
    
    air->runAction(CCSequence::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(aniArray,0.05)),CCCallFuncN::create(this, callfuncN_selector(GameStartLayerClass::spriteHurtedAniCallBack)),NULL));
}

void GameStartLayerClass::spriteHurtedAniCallBack(cocos2d::CCNode *node)
{
    CCSprite* deadAni = (CCSprite*)node;
    
    deadAni->stopAllActions();
    deadAni->removeFromParentAndCleanup(true);
}


void GameStartLayerClass::gameShowStopIconAniStart(cocos2d::CCPoint pos)
{
    CCSprite* stopIcon = CCSprite::createWithSpriteFrameName("forbidden.png");
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(stopIcon, pos);
    this->addChild(stopIcon,GAMEING_SHOW_STOP_ICON_ZORDER);
    
    CCFadeOut* out = CCFadeOut::create(1);
    
    stopIcon->runAction(CCSequence::create(out,CCCallFuncN::create(this, callfuncN_selector(GameStartLayerClass::gameShowStopIconAniCallBack)),NULL));
    
}

void GameStartLayerClass::gameShowStopIconAniCallBack(cocos2d::CCNode *node)
{
    CCSprite* stopAni = (CCSprite*)node;
    
    stopAni->stopAllActions();
    stopAni->removeFromParentAndCleanup(true);
}

void GameStartLayerClass::gameShowStartAni(bool restart)
{
    int dir = -1;
    float angle = 0;
    float xOffset = 0;
    float yOffset = 0;
    CCNode* node0 = (CCNode*)pathArray->objectAtIndex(0);
    CCNode* node1 = (CCNode*)pathArray->objectAtIndex(1);
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    CCPoint subPos = ccpSub(node1->getPosition(), node0->getPosition());
    
    if (subPos.x >= -0.0000001 && subPos.x <= 0.0000001) {
        xOffset = 0;
        yOffset = 1;
        if (subPos.y > 0.0000001) {
            angle = -90;
            dir = 1;
        }
        else if(subPos.y < -0.0000001)
        {
            angle = 90;
            dir = -1;
        }
    }
    else if (subPos.y >= -0.0000001 && subPos.y <= 0.0000001)
    {
        xOffset = 1;
        yOffset = 0;
        if (subPos.x > 0.0000001) {
            angle = 0;
            dir = 1;
        }
        else if (subPos.x < -0.0000001)
        {
            angle = 180;
            dir = -1;
        }
    }
    
    CCSprite* arrow1 = CCSprite::createWithSpriteFrameName("arrow.png");
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(arrow1, node0->getPosition());
    this->addChild(arrow1,GAMEING_SHOW_COM_ANI);
    arrow1->setRotation(angle);

    
    CCMoveBy* wait = CCMoveBy::create(0.15, ccp(0, 0));
    CCFadeIn* fin = CCFadeIn::create(0.15);
    CCFadeOut* fout = CCFadeOut::create(0.15);
    if (restart) {
        arrow1->runAction(CCSequence::create(wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,CCCallFuncN::create(this, callfuncN_selector(GameStartLayerClass::gameShowStartAniCallBack)),NULL));
    }
    else
    {
        arrow1->runAction(CCSequence::create(wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,CCCallFuncN::create(this, callfuncN_selector(GameStartLayerClass::gameShowStartAniCallBack)),NULL));
    }
    
    
    CCSprite* arrow2 = CCSprite::createWithSpriteFrameName("arrow.png");
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(arrow2, ccpAdd(node0->getPosition(), ccp(xOffset * dir * size.width * 4/100, yOffset * dir * size.height * 7/100)));
    this->addChild(arrow2,GAMEING_SHOW_COM_ANI);
    arrow2->setRotation(angle);
    if (restart) {
        arrow2->runAction(CCSequence::create(wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,CCCallFuncN::create(this, callfuncN_selector(GameStartLayerClass::gameShowStartAniCallBack)),NULL));
    }
    else
    {
        arrow2->runAction(CCSequence::create(wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,CCCallFuncN::create(this, callfuncN_selector(GameStartLayerClass::gameShowStartAniCallBack)),NULL));
    }
    
    CCSprite* arrow3 = CCSprite::createWithSpriteFrameName("arrow.png");
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(arrow3, ccpAdd(node0->getPosition(), ccp(xOffset * dir * size.width * 4 * 2/100, yOffset * dir * size.height * 7 * 2/100)));
    this->addChild(arrow3,GAMEING_SHOW_COM_ANI);
    arrow3->setRotation(angle);
    if (restart) {
        arrow3->runAction(CCSequence::create(wait,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,CCCallFuncN::create(this, callfuncN_selector(GameStartLayerClass::gameShowStartAniCallBack)),NULL));
    }
    else
    {
        arrow3->runAction(CCSequence::create(wait,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,wait,wait,fin,wait,wait,fout,CCCallFuncN::create(this, callfuncN_selector(GameStartLayerClass::gameShowStartAniCallBack)),NULL));
    }
    
    
}

void GameStartLayerClass::gameShowStartAniCallBack(CCNode* node)
{
    static int index = 0;
    CCSprite* sprite = (CCSprite*)node;
    
    index += 1;
    
    if (index >= 3) {
        
        isNowAddMonster = true;
        if (gameModeType == GAME_MODE_TYPE_BOSS) {
            this->schedule(schedule_selector(GameStartLayerClass::updateBossTimeBgState), 1);
        }
    }
    sprite->stopAllActions();
    sprite->removeFromParentAndCleanup(true);
}

void GameStartLayerClass::showTowerFeatureBeforeGameCallBack()
{
    if(!isLogoShowOver)
    {
        if (GameStageConClass::sharedStageCon()->getIsGameReStart()) {
            
            GameStageConClass::sharedStageCon()->setIsGameReStart(false);
            this->gameShowGoBgAniStart();
            this->gameShowStartAni(true);
        }
        else
        {
            CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
            
            GameLogoRotateClass* rotate = GameLogoRotateClass::create(ccp(size.width / 2, size.height / 2), this, callfunc_selector(GameStartLayerClass::logoShowOverCallBack));
            LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(rotate, ccp(size.width / 2, size.height / 2));
            this->addChild(rotate,GAMEING_SHOW_GO_ZODER);
            this->gameShowStartAni(false);
        }
    }
}

void GameStartLayerClass::gameMenuSelCallBack(cocos2d::CCObject *parent)
{
    if (parent) {
        CCMenuItemImage* menu = (CCMenuItemImage*)parent;
        
        int tag = menu->getTag();
        
        switch (tag) {
            case GAME_MENU_SEL_SPEED2X:
                {
					if (isGameRealStartNow) {
                        if (!isGameSpeed2X)
                        {
                            CCSpriteFrame* frame0 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("speed21.png");
                            menu->setNormalSpriteFrame(frame0);
                            isGameSpeed2X = true;
                        }
                        else
                        {
                            CCSpriteFrame* frame0 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("speed11.png");
                            menu->setNormalSpriteFrame(frame0);
                            isGameSpeed2X = false;
                        }
                        
                        if (!isGamePause) {
                            this->gamePauseOrSpeedSpriteState(true,isGameSpeed2X);
                        }
                    }
                }
                break;
            case GAME_MENU_SEL_PAUSE:
                {
                    
                    if (isGameRealStartNow) {
                        if (!isGamePause) {
                            CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MenuCenter_02_CN.png");
                            
                            menuCenterBG->setDisplayFrame(frame);
                            curLevelLab->setVisible(false);
                            totalLevelLab->setVisible(false);
                            
                            CCSpriteFrame* frame0 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pause11.png");
                            menu->setNormalSpriteFrame(frame0);
                            isGamePause = true;
                            
                            if (gameModeType == GAME_MODE_TYPE_BOSS) {
                                this->unschedule(schedule_selector(GameStartLayerClass::updateBossTimeBgState));
                            }
                        }
                        else
                        {
                            CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MenuCenter_01_CN.png");
                            
                            menuCenterBG->setDisplayFrame(frame);
                            curLevelLab->setVisible(true);
                            totalLevelLab->setVisible(true);
                            isGamePause = false;
                            
                            CCSpriteFrame* frame0 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pause01.png");
                            menu->setNormalSpriteFrame(frame0);
                            
                            if (gameModeType == GAME_MODE_TYPE_BOSS) {
                                this->unschedule(schedule_selector(GameStartLayerClass::updateBossTimeBgState));
                                this->schedule(schedule_selector(GameStartLayerClass::updateBossTimeBgState), 1);
                            }
                            
                            
                        }
                        this->gamePauseOrSpeedSpriteState(false,isGamePause);
                        if (!isGamePause) {
                            //this->gamePauseOrSpeedSpriteState(true,isGameSpeed2X);
                        }
                    }
                }
                break;
            case GAME_MENU_SEL_PAUSE_SELITEM:
                {
                    if (isGameRealStartNow) {
                        CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                        CCRenderTexture* in_texture = CCRenderTexture::create(size.width, size.height);
                        
                        in_texture->begin();
                        gameBGSprite->visit();
                        this->visit();
                        in_texture->end();
                        
                        CCLog("%d",in_texture->saveToFile(GAME_WB_PIC_NAME, kCCImageFormatPNG));
#endif
                        isGameSelItem = true;
                        gameSelItemLayer->setVisible(true);
                        isGamePause = true;
                        
                        this->gamePauseOrSpeedSpriteState(false, isGamePause);
                        isGameRealStartNow = false;
                        
                        
                        if (gameModeType == GAME_MODE_TYPE_BOSS) {
                            this->unschedule(schedule_selector(GameStartLayerClass::updateBossTimeBgState));
                        }
                    }
                }
                break;
            case GAME_MENU_SEL_PAUSE_SELITEM_RESUME:
                {
                    isGameSelItem = false;
                    gameSelItemLayer->setVisible(false);
                    isGamePause = false;
                    
                    this->gamePauseOrSpeedSpriteState(false, isGamePause);
                    isGameRealStartNow = true;
                    
                    if (gameModeType == GAME_MODE_TYPE_BOSS) {
                        this->unschedule(schedule_selector(GameStartLayerClass::updateBossTimeBgState));
                        this->schedule(schedule_selector(GameStartLayerClass::updateBossTimeBgState), 1);
                    }
//                    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(gameSelItemLayer);
//                    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
                }
                break;
            case GAME_MENU_SEL_PAUSE_SELITEM_RESTART:
                {
//                    int tmpIndex = GameStageConClass::sharedStageCon()->getConfigDataFirstIndex();
//                    GameStageConClass::sharedStageCon()->setConfigDataIndex(tmpIndex);
                    isGameSelItem = false;
                    isLayerOver = true;
                    GameStageConClass::sharedStageCon()->setIsGameReStart(true);
                    CCDirector::sharedDirector()->replaceScene(GameStartLayerClass::createGameStart());
                }
                break;
            case GAME_MENU_SEL_PAUSE_SELITEM_SELSTAGE:
                {
                    isGameSelItem = false;
                    isLayerOver = true;
                    if (gameModeType == GAME_MODE_TYPE_ADVENTURE) {
                        CCDirector::sharedDirector()->replaceScene(AdventureLevelClass::createScene());
                    }
                    else if (gameModeType == GAME_MODE_TYPE_BOSS)
                    {
                        CCDirector::sharedDirector()->replaceScene(BossModeClass::createScene());
                    }
                }
                break;
            case GAME_MENU_SEL_WB_SINA:
            case GAME_MENU_SEL_WB_TECENT:
                {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                    if (GameWBConClass::sharedWBCON()->checkDeviceNetState()) {
                        
                        if (tag == GAME_MENU_SEL_WB_SINA) {
                            GameWBConClass::sharedWBCON()->SetSinWbOrTCWbIsSelected(false);
                        }
                        else
                        {
                            GameWBConClass::sharedWBCON()->SetSinWbOrTCWbIsSelected(true);
                        }
                        GameWBConClass::sharedWBCON()->showWBView();
                    }
                    else
                    {
                        CCSize size = gameSelItemLayer->getContentSize();
                        
                        GameShowNetClass* show = GameShowNetClass::create();
                        show->showNetState(GAME_NET_WORK_STATE_TYPE_NONET);
                        show->setPosition(ccp(size.width/2, size.height/10));
                        gameSelItemLayer->addChild(show,10000);
                    }
#endif
                }
                break;
            default:
                break;
        }
    }
}

void GameStartLayerClass::gamePauseOrSpeedSpriteState(bool isSpeed,bool flag)
{
    if (enemyMonsterArray != NULL && enemyMonsterArray->count() > 0) {

        int count = enemyMonsterArray->count();
        for (int i = 0; i < count; i++) {
            EnemySpriteClass* enemy = (EnemySpriteClass*)enemyMonsterArray->objectAtIndex(i);
            if (enemy != NULL && enemy->getEnemyType() == GAME_ENEMY_TYPE_MONSTERS) {
                if(isSpeed)
				{
					enemy->setIsSpeed2X(flag);
				}
				else
				{
					enemy->setEnemyPauseState(flag);
				}
            }
        }
    }
    
    if (towerArray != NULL && towerArray->count() > 0) {
        int count = towerArray->count();
        
        for (int i = 0; i < count; i++) {
            AttackTowerClass* tower = (AttackTowerClass*)towerArray->objectAtIndex(i);
            if (tower != NULL) {
                if (isSpeed)
                {
					tower->setIsSpeed2X(flag);
                }
				else
				{
					tower->setIsTowerPause(flag);
				}
                
            }
        }
    }
    
    if (bulletArray != NULL && bulletArray->count() > 0) {
        int count = bulletArray->count();
        
        for (int i = 0; i < count; i++) {
            TowerBulletClass* bullet = (TowerBulletClass*)bulletArray->objectAtIndex(i);
            if (bullet != NULL) {
                if (isSpeed)
                {
					bullet->setIsSpeed2X(flag);
                }
				else
				{
					bullet->setIsBulletPause(flag);
				}
                
            }
        }
    }
    
    if (bulletEffectArray != NULL && bulletEffectArray->count() > 0) {
        int count = bulletEffectArray->count();
        
        for (int i = 0; i < count; i++) {
            TowerBulletEffect* effect = (TowerBulletEffect*)bulletEffectArray->objectAtIndex(i);
            if (effect != NULL) {
                if (isSpeed)
                {
					effect->setIsSpeed2X(flag);
                }
				else
				{
					effect->setIsBulletEffectPause(flag);
				}
                
            }
        }
    }
}


bool GameStartLayerClass::checkIsCanPutOnMap(cocos2d::CCPoint pos)
{
    int index = 0;
    bool isValid = false;
    CCPoint selPos = ccp(0,0);
    
    if (mapPutArray->count() > 0) {
        MapPassClass* mapPut = NULL;
        do {
            if (index < mapPutArray->count()) {
                mapPut = (MapPassClass*)mapPutArray->objectAtIndex(index);
                index++;
                if (mapPut->getIsCanPutOnMap()) {
                    CCSize size = mapPut->getAreaSize();
                    CCPoint mapPos = mapPut->getPosition();
                    CCPoint mapOrigin = ccp(mapPos.x - size.width / 2, mapPos.y - size.height / 2);
                    CCRect validRect = CCRect(mapPos.x - size.width / 2, mapPos.y - size.height / 2, size.width, size.height);
                    if (validRect.containsPoint(pos)) {
                        isValid = true;
                        //i will modified here {
                        int x = 0;
                        int y = 0;
                        if (((int)pos.x) == 0) {
                            x = 0;
                        }
                        else
                        {
//                            x = ((int)pos.x) / ((int)(mapOrigin.x + gameMapTiledSize.width));
                            x = (abs(pos.x - mapOrigin.x)) / gameMapTiledSize.width;
                        }
                        
                        if (((int)pos.y) == 0) {
                            y = 0;
                        }
                        else
                        {
//                            y = ((int)pos.y) / ((int)(mapOrigin.y + gameMapTiledSize.height));
                            y = (abs(pos.y - mapOrigin.y)) / gameMapTiledSize.height;
                        }
                        selPos = ccp(mapOrigin.x + gameMapTiledSize.width / 2  + x * gameMapTiledSize.width,mapOrigin.y + gameMapTiledSize.height / 2 + y*gameMapTiledSize.height);
                        userTouchPos = selPos;
                        //}
                        break;
                    }
                }
            }
            else
            {
                break;
            }
        } while (mapPut != NULL);
        
    }
    index = 0;
    if (towerArray && towerArray->count()) {
        AttackTowerClass* tower = NULL;
        do {
            if (index < towerArray->count()) {
                tower = (AttackTowerClass*)towerArray->objectAtIndex(index);
                index++;
//                CCSize size = tower->getContentSize();
                CCSize size = gameMapTiledSize;
                CCPoint towerPos = tower->getPosition();
                float maxValue = (size.width > size.height)?size.width:size.height;
                CCRect validRect = CCRect(towerPos.x - maxValue / 2, towerPos.y - maxValue / 2, maxValue, maxValue);
                if (validRect.containsPoint(pos)) {
                    isValid = false;
                    if (userSelTower && towerShowPad->getIsShowTowerPAD() && userSelTower != tower) {
                        towerShowPad->setIsHideTowerPAD(true);
                    }
                    else
                    {
                        userSelTower = tower;
                        towerShowPad->setIsHideTowerPAD(false);
                    }
//                    
//                    do {
//                        
//                    } while (userSelTower && towerShowPad->getIsHideTowerPAD());
//                    break;
                }
            }
            else
            {
                break;
            }
        } while (tower != NULL);
    }
    
    if (isValid && userSelTower && towerShowPad->getIsShowTowerPAD()) {
        towerShowPad->setIsHideTowerPAD(true);
//        do {
//            
//        } while (isTowerHidePAD);
        //userSelTower = NULL;
    }
    
    return isValid;
}

void GameStartLayerClass::updateGameSpriteState()
{
	bool isAddMonstersFinish = false;
    int count = 0;
    unsigned int monstersNum = 0;
	char pBuffer[10] = {0};

//    if (towerArray->count() > 0) {
//        int count = towerArray->count();
//        int curMoney = gameCurMoney;
//        
//        for (int i = 0; i < count; i++) {
//            
//            AttackTowerClass* tower = (AttackTowerClass*)towerArray->objectAtIndex(i);
//            if (tower->getTowerPayMoney() > curMoney) {
//                tower->setIsShowTowerUpGrade(false);
//            }
//            else if((tower->getTowerPayMoney() <= curMoney))
//            {
//                if (towerShowPad->getIsShowTowerPAD() == false) {
//                    tower->setIsShowTowerUpGrade(true);
//                }
//            }
//        }
//    }
    
    
	isAddMonstersFinish = addEnemyPlan->checkIsAddMonstersFinish();
    monstersNum = addEnemyPlan->getAddMonsterNum();
    
    if (gameModeType == GAME_MODE_TYPE_BOSS) {//find the boss
        
        if (bossSelSprite == NULL) {
            for (int i = 0; i < enemyMonsterArray->count(); i++) {
                EnemySpriteClass* enemy = (EnemySpriteClass*)enemyMonsterArray->objectAtIndex(i);
                
                if (enemy->getEnemyMonsterTypeID() == GameStageConClass::sharedStageCon()->getBossMonsterTypeID()) {
                    bossSelSprite = enemy;
                    bossSelSprite->setTotalLifeValue(GAME_ENEMY_MONSTERS_BOSS_BIG_LIFE);//for test
//                    bossSelSprite->setTotalLifeValue(GameStageConClass::sharedStageCon()->getBossBloodValue());
                    break;
                }
            }
        }
        else
        {
            this->updateBossModeBloodValue();
            
        }
    }
    
    if (deadSpriteArray->count() > 0) {
        
        
       count  = deadSpriteArray->count();
        
        for (int i = 0; i < count; i++) {
            EnemySpriteClass* enemy = (EnemySpriteClass*)deadSpriteArray->objectAtIndex(i);
            GAME_MONEY_SCORE_TYPE money = enemy->getMoneyType();
            MoneyScoreClass* score = MoneyScoreClass::create(money, enemy->getPosition());
            LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(score, ccp(enemy->getPosition().x, enemy->getPosition().y + enemy->getContentSize().height * 3.0 /2.0));
            this->addChild(score,GAMEING_ENEMY_TO_SCORE_ZORDER);
            
            if (userSelEnemy == enemy) {
                userSelEnemy = NULL;
                userSelEnemyPointSprite->setVisible(false);
            }
            
			if (enemy->getEnemyType() == GAME_ENEMY_TYPE_MONSTERS && monstersNum > 0)
			{
				monstersNum -= 1;
                enemyMonsterArray->removeObject(enemy);
			}
            else if (enemy->getEnemyType() == GAME_ENEMY_TYPE_OBJECT)
            {
                int objectID = enemy->getEnemyObjectID();
                if (objectID > 0){
                    
                    int xNum = enemy->getEnemyObjectToTowerNum_X();
                    int yNum = enemy->getEnemyObjectToTowerNum_Y();
                    CCPoint enemyPos = enemy->getPosition();
                    CCSize mapTileSize = LcdAdapClass::sharedLCDADAP()->getGameMapTiledSize();
                    CCPoint originPos = ccp((enemyPos.x - (mapTileSize.width*xNum / 2)), (enemyPos.y - mapTileSize.height * yNum / 2));
                    for (int i = 0; i < xNum; i++) {
                        for (int j = 0; j < yNum; j++) {
                            
                            CCPoint newTowerPos = ccp((originPos.x + mapTileSize.width*(i + 0.5)), (originPos.y + mapTileSize.height*(j + 0.5)));
                            
                            this->addGameTowerType(objectTowerBuffer[objectID].towerType, newTowerPos);
                        }
                    }
                    
                }
                
                enemyObjectArray->removeObject(enemy);
                {
                    int i = 0;
                    CCPoint enemyPos = enemy->getPosition();
                    MapPassClass* mapPut = NULL;
                    
                    for (i = 0; i < mapPutArray->count(); i++) {
                        mapPut = (MapPassClass*)mapPutArray->objectAtIndex(i);
                        if (mapPut && !(mapPut->getIsDealed())) {
                            CCSize mapPosSize = mapPut->getAreaSize();
                            CCPoint mapPos = mapPut->getPosition();
                            CCRect mapRect = CCRect(mapPos.x - mapPosSize.width / 2, mapPos.y - mapPosSize.height / 2, mapPosSize.width, mapPosSize.height);
                            if (mapRect.containsPoint(enemyPos)) {
                                mapPut->setIsCanPutOnMap(true);
                                mapPut->setIsDealed(true);
                            }
                        }
                    }
                }
            }
            this->spriteHurtedAniStart(enemy->getPosition());
			enemy->removeFromParentAndCleanup(true);
			gameCurMoney += score->getMoneyScore();
			HUDClass::sharedHUD()->setHUDMoney(gameCurMoney);
        }
        enemyArray->removeObjectsInArray(deadSpriteArray);
        deadSpriteArray->removeAllObjects();
    }
    
    if (gameModeType == GAME_MODE_TYPE_ADVENTURE) {
        if (enemyMonsterArray->count() > 0) {
            for (int i = 0; i < enemyMonsterArray->count(); i++) {
                EnemySpriteClass* enemy = (EnemySpriteClass*)enemyMonsterArray->objectAtIndex(i);
                if (enemy->getEnemyType() == GAME_ENEMY_TYPE_MONSTERS) {
                    if (proCaraton->checkCaratonIsBited(enemy->getPosition(), enemy->getContentSize())) {
                        
                        int life = proCaraton->getCaratonCurLifeValue();
                        
                        if (userSelEnemy == enemy) {
                            userSelEnemy = NULL;
                            userSelEnemyPointSprite->setVisible(false);
                        }
                        
                        enemy->setCurLifeValue(-1);
                        monstersNum -= 1;
                        this->spriteHurtedAniStart(proCaraton->getPosition());
                        if (life >= 0) {
                            
                            life -= 1;
                            proCaraton->setCaratonCurLifeValue(life);
                            
                            
                            
                            if (life <= 0) {
                                //you lose
                                
                                GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_ITEM_GAME_LOSE);
                                
                                isGameRealStartNow = false;
                                proCaraton->stopAllActions();
                                proCaraton->stopHLBAllAction();
                                proCaraton->setVisible(false);
                                isLayerOver = true;
                                isGamePause = true;
                                this->gamePauseOrSpeedSpriteState(false,true);
                                if (GameStageConClass::sharedStageCon()->getIsGameWahleCurLevell() && isGameShowWhale) {
                                    gameWhale->stopAllActions();
                                    gameWhale->setVisible(false);
                                    gameWhale->setTouchEnabled(false);
                                    this->whaleLayerCallBack();
                                }
                                
//                                this->unscheduleUpdate();
                                gameWinLoseStruct tmp;
                                tmp.curRoundIndex = GameStageConClass::sharedStageCon()->getGameStageRoundIndex();
                                tmp.curSubRoundIndex = GameStageConClass::sharedStageCon()->getGameStageSubRoundIndex();
                                tmp.gameModeType = GAME_MODE_TYPE_ADVENTURE;
                                tmp.gameWinLoseType = GAME_WINLOSE_TYPE_LOSE;
                                tmp.totalSubRoundNum = GameStageConClass::sharedStageCon()->getGameStageSubRoundNum();
                                ShowWinLoseClass::sharedShow(tmp)->showGameOver(this);
                                
                                {
                                    //write user data
                                
                                }
                                return;
                            }
                        }
                        
                    }
                }
            }
        }

    }
    
//    if (monstersNum <= 0 && isAddMonstersFinish) {
    if ((enemyMonsterArray->count() == 0) && isAddMonstersFinish) {
        if (gameModeType == GAME_MODE_TYPE_ADVENTURE) {
            if (addEnemyPlan->setGameStageNextSubRound()) {
                isLayerOver = true;
                isGameRealStartNow = false;
                proCaraton->stopAllActions();
                proCaraton->stopHLBAllAction();
                GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_ITEM_GAME_WIN);
                this->gamePauseOrSpeedSpriteState(false,true);
//                this->unscheduleUpdate();
                if (GameStageConClass::sharedStageCon()->getIsGameWahleCurLevell() && isGameShowWhale) {
                    gameWhale->stopAllActions();
                    gameWhale->setVisible(false);
                    gameWhale->setTouchEnabled(false);
                    this->whaleLayerCallBack();
                }
                gameWinLoseStruct tmp;
                tmp.curRoundIndex = GameStageConClass::sharedStageCon()->getGameStageRoundIndex();
                tmp.curSubRoundIndex = GameStageConClass::sharedStageCon()->getGameStageSubRoundIndex();
                tmp.gameModeType = GAME_MODE_TYPE_ADVENTURE;
                tmp.gameWinLoseType = GAME_WINLOSE_TYPE_WIN;
                tmp.totalSubRoundNum = GameStageConClass::sharedStageCon()->getGameStageSubRoundNum();
                ShowWinLoseClass::sharedShow(tmp)->showGameOver(this);
                
                {
                    gameLevelInfoStruct info;
                    int life = proCaraton->getCaratonCurLifeValue();
                    
                    info.isLevelLocked = false;
                    info.isClearAllObject = isAllObjectClear;
                    info.UserGained = 0;
                    
                    if (life >=1 && life <=5) {
                        info.UserGained = 1;
                    }
                    else if(life >= 6 && life <=9){
                        info.UserGained = 2;
                    }
                    else if (life == 10){
                        info.UserGained = 3;
                    }
                    
                    HUDClass::sharedHUD()->setGameCurLevelInfo(info, (GAME_STAGE_TYPE)GameStageConClass::sharedStageCon()->getGameStageIndex(), GameStageConClass::sharedStageCon()->getGameStageRoundIndex());
                    
                    
                    int tmpStageRoundNum = GameStageConClass::sharedStageCon()->getGameStageRoundNum();
                    int tmpStageRoundIndex = GameStageConClass::sharedStageCon()->getGameStageRoundIndex();
                    
                    if (GameStageConClass::sharedStageCon()->getGameModeType() == GAME_MODE_TYPE_ADVENTURE) {
                        int tmpStageNum = GameStageConClass::sharedStageCon()->getGameStageNum();
                        int tmpStageIndex = GameStageConClass::sharedStageCon()->getGameStageIndex();
                        
                        info.isClearAllObject = false;
                        info.UserGained = 0;
                        info.isLevelLocked = false;
                        
                        
                        if (tmpStageRoundIndex < tmpStageRoundNum) {
                            tmpStageRoundIndex += 1;
                            HUDClass::sharedHUD()->setGameCurLevelInfo(info, (GAME_STAGE_TYPE)tmpStageIndex, tmpStageRoundIndex);
                        }
                        else if(tmpStageIndex < tmpStageNum)
                        {
                            tmpStageIndex += 1;
                            HUDClass::sharedHUD()->setGameCurLevelInfo(info, (GAME_STAGE_TYPE)tmpStageIndex, 0);
                        }
                        
                    }
                }
                
                return;
            }
            else
            {
                memset(pBuffer, 0, sizeof(pBuffer));
                sprintf(pBuffer, "%02d",GameStageConClass::sharedStageCon()->getGameStageSubRoundIndex());
                curLevelLab->setString(pBuffer);
            }
        }
    }
	else
	{
		addEnemyPlan->setMonsterNum(monstersNum);
	}

    

    
    
	//if (gameCurMoney != HUDClass::sharedHUD()->getHUDMoney())
	{
		gameCurMoney = HUDClass::sharedHUD()->getHUDMoney();
		sprintf(pBuffer,"%d",gameCurMoney);
		updateGameCurMoneyLab->setString(pBuffer);
	}
    
    if (userTowerAdd)
	{
		if (userTowerAdd->getIsShowAddTowerType())
		{
			userTowerAdd->updateAddTowerShowState();
		}
		
	}
    
    if (towerShowPad) {
        if (towerShowPad->getIsShowTowerPAD()) {
            towerShowPad->updateTowerSelPadState();
        }
    }
	
    if (GameStageConClass::sharedStageCon()->getIsGameGiftCurLevel() && !isGameShowGift) {
        if (GameStageConClass::sharedStageCon()->getGameGiftCurLevel() == GameStageConClass::sharedStageCon()->getGameStageSubRoundIndex()) {
            isGameShowGift = true;
            
            PetsDropClass* pets = PetsDropClass::create();
            this->addChild(pets,GAMEING_SHOW_GIFT_WHALE_ZORDER);
        }
        
    }
    
    if (gameModeType == GAME_MODE_TYPE_ADVENTURE) {
        
        
        if (GameStageConClass::sharedStageCon()->getGameStageSubRoundIndex() == (GameStageConClass::sharedStageCon()->getGameStageSubRoundNum()) && !isLastFinall) {
            
            isLastFinall = true;
            comSpriteActionClass* finalWave = comSpriteActionClass::create(COM_ANI_TYPE_FINAL_ATTACKING);
            this->addChild(finalWave,GAMEING_SHOW_COM_ANI);
        }
    }
    
    if ((gameModeType == GAME_MODE_TYPE_ADVENTURE) && GameStageConClass::sharedStageCon()->getIsGameWahleCurLevell() && !isGameShowWhale) {
        if (GameStageConClass::sharedStageCon()->getgameWahleCurLevel() == GameStageConClass::sharedStageCon()->getGameStageSubRoundIndex()) {
            isGameShowWhale = true;
            
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
            gameWhale = WhaleClass::create(this, callfunc_selector(GameStartLayerClass::whaleLayerCallBack));
            
            menuCenterBG->setVisible(false);
            gameSpeed2XMenu->setVisible(false);
            gameWhale->getGameCurLevelAndTotalLevel(GameStageConClass::sharedStageCon()->getGameStageSubRoundIndex(), GameStageConClass::sharedStageCon()->getGameStageSubRoundNum());
            
            gameWhale->setContentSize(LcdAdapClass::sharedLCDADAP()->getWinSize());
            this->addChild(gameWhale,GAMEING_SHOW_GIFT_WHALE_ZORDER);
        }
    }
    
    if (userSelEnemy != NULL && userSelEnemy->retainCount() > 0) {
        if (userSelEnemyPointSprite->isVisible()) {
            CCPoint enemyPos = userSelEnemy->getPosition();
            CCSize enemySize = userSelEnemy->getContentSize();
            CCSize enemyBloodSize = userSelEnemy->getEnemyBloodUISize();
            
            userSelEnemyPointSprite->setPosition(ccp(enemyPos.x,enemyPos.y + enemySize.height + enemyBloodSize.height));
        }
    }
    
    if (enemyObjectArray->count() == 0 && !isAllObjectClear) {
        comSpriteActionClass* allOBClear = comSpriteActionClass::create(COM_ANI_TYPE_OBJECT_CLEAR_ALL);
        this->addChild(allOBClear,GAMEING_SHOW_COM_ANI);
        isAllObjectClear = true;
    }
    
    

}

void GameStartLayerClass::addEnemyByPlan(float dt)
{
    
}

void GameStartLayerClass::addGameTowerType(GAME_TOWER_TYPE towerType, cocos2d::CCPoint addPos)
{
    CCAssert(!(towerType == GAME_TOWER_TYPE_NONE || towerType == GAME_TOWER_TYPE_MAX), "cannot be NULL");
    
    
    
    AttackTowerClass* tower = NULL;
    CCSpriteBatchNode* batchNode = NULL;
    switch (towerType) {
        case GAME_TOWER_TYPE_ANCHOR:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_ANCHOR);
            tower->setBulletBatchParent(towerAnchorBatch);
            batchNode = towerAnchorBatch;
        }
            break;
        case GAME_TOWER_TYPE_ARROW:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_ARROW);
            tower->setBulletBatchParent(towerArrowBatch);
            batchNode = towerArrowBatch;
        }
            break;
        case GAME_TOWER_TYPE_BALL:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_BALL);
            tower->setBulletBatchParent(towerBallBatch);
            batchNode = towerBallBatch;
        }
            break;
        case GAME_TOWER_TYPE_BLUESTAR:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_BLUESTAR);
            tower->setBulletBatchParent(towerBlueStarBatch);
            batchNode = towerBlueStarBatch;
        }
            break;
        case GAME_TOWER_TYPE_BOTTLE:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_BOTTLE);
            tower->setBulletBatchParent(towerBottleBatch);
            batchNode = towerBottleBatch;
        }
            break;
        case GAME_TOWER_TYPE_BUFF:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_BUFF);
            tower->setBulletBatchParent(towerBuffBatch);
            batchNode = towerBuffBatch;
        }
            break;
        case GAME_TOWER_TYPE_CUTTLE:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_CUTTLE);
            tower->setBulletBatchParent(towerCuttleBatch);
            batchNode = towerCuttleBatch;
        }
            break;
        case GAME_TOWER_TYPE_FAN:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_FAN);
            tower->setBulletBatchParent(towerFanBatch);
            batchNode = towerFanBatch;
        }
            break;
        case GAME_TOWER_TYPE_FIREBOTTLE:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_FIREBOTTLE);
            tower->setBulletBatchParent(towerFireBottleBatch);
            batchNode = towerFireBottleBatch;
        }
            break;
        case GAME_TOWER_TYPE_FISH:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_FISH);
            tower->setBulletBatchParent(towerFishBatch);
            batchNode = towerFishBatch;
        }
            break;
        case GAME_TOWER_TYPE_MUSHROOM:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_MUSHROOM);
            tower->setBulletBatchParent(towerMushRoomBatch);
            batchNode = towerMushRoomBatch;
        }
            break;
        case GAME_TOWER_TYPE_PIN:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_PIN);
            tower->setBulletBatchParent(towerPinBatch);
            batchNode = towerPinBatch;
        }
            break;
        case GAME_TOWER_TYPE_PLANE:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_PLANE);
            tower->setBulletBatchParent(towerPlaneBatch);
            batchNode = towerPlaneBatch;
        }
            break;
        case GAME_TOWER_TYPE_ROCKET:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_ROCKET);
            tower->setBulletBatchParent(towerRocketBatch);
            batchNode = towerRocketBatch;
        }
            break;
        case GAME_TOWER_TYPE_SHIT:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_SHIT);
            tower->setBulletBatchParent(towerShitBatch);
            batchNode = towerShitBatch;
        }
            break;
        case GAME_TOWER_TYPE_SNOW:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_SNOW);
            tower->setBulletBatchParent(towerSnowBatch);
            batchNode = towerSnowBatch;
        }
            break;
        case GAME_TOWER_TYPE_STAR:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_STAR);
            tower->setBulletBatchParent(towerStarBatch);
            batchNode = towerStarBatch;
        }
            break;
        case GAME_TOWER_TYPE_SUN:
        {
            tower = AttackTowerClass::create(GAME_TOWER_TYPE_SUN);
            tower->setBulletBatchParent(towerSunBatch);
            batchNode = towerSunBatch;
        }
            break;
        default:
            break;
    }
    
    if (tower != NULL && batchNode != NULL) {
//        tower->setPosition(addPos);
        tower->setTowerParentAndPos(this, addPos);
        tower->setEnemyMonsterArray(enemyMonsterArray);
        tower->setEnemyArray(enemyArray, deadSpriteArray);
        if (towerType == GAME_TOWER_TYPE_ANCHOR) {
            tower->setEnemyObjectArray(enemyObjectArray);
        }
        tower->setTowerBulletEffectArray(bulletArray, bulletEffectArray);
        tower->setIsSpeed2X(isGameSpeed2X);
        tower->setIsTowerPause(isGamePause);
//        this->addChild(tower,GAMEING_TOWER_ZORDER);
        towerArray->addObject(tower);
    }
}

void GameStartLayerClass::addTowerSelCallBack()
{
    if (userTowerAdd) {
        GAME_TOWER_TYPE selTower = userTowerAdd->getAddTowerType();
        this->addGameTowerType(selTower,userTouchPos);
        userTowerAdd->hideAddTowerType();
        isSelPutTower = false;
        
        if (isShowGameHelp) {
            HELP_PLAYGAME_STATE_TYPE type  = showHelpPL->getHelpStateType();
            type = (HELP_PLAYGAME_STATE_TYPE)(type + 1);
            showHelpPL->setHelpStateType(type);
            this->showGameHelpCallBack();
        }
    }
}



void GameStartLayerClass::updateEnemyUI()
{
//    if (enemyArray->count() > 0) {
//        for (int i = 0; i < enemyArray->count(); i++) {
//            EnemySpriteClass* enemy = (EnemySpriteClass*)enemyArray->objectAtIndex(i);
//            if (enemy->getIsAttacked()) {
//                enemy->updateLifeUI();
//            }
//        }
//    }
}


void GameStartLayerClass::selTowerPadCallBack()
{
    bool upOrSell = towerShowPad->getUserUpOrSellTower();
    
    userSelTower->setZOrder(GAMEING_TOWER_ZORDER);
    if (upOrSell) {
        GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_ITEM_TOWER_UPDATE);
        if (isShowGameHelp) {
            showHelpPL->setHelpStateType(HELP_PLAYGAME_STATE_TYPE_UPDATE_TOWER);
            this->showGameHelpCallBack();
            }
    }
    else
    {
        towerArray->removeObject(userSelTower);
        if (isShowGameHelp) {
            showHelpPL->setHelpStateType(HELP_PLAYGAME_STATE_TYPE_SELL_TOWER);
            this->showGameHelpCallBack();
        }
    }
    
    
    
    userSelTower = NULL;
}

void GameStartLayerClass::update(float dt)
{
    
    if (towerArray->count() > 0) {
        int count = towerArray->count();
        int curMoney = gameCurMoney;
        
        for (int i = 0; i < count; i++) {
            
            AttackTowerClass* tower = (AttackTowerClass*)towerArray->objectAtIndex(i);
            if (tower->getTowerPayMoney() > curMoney) {
                tower->setIsShowTowerUpGrade(false);
            }
            else if((tower->getTowerPayMoney() <= curMoney))
            {
                if (towerShowPad->getIsShowTowerPAD() == false) {
                    tower->setIsShowTowerUpGrade(true);
                }
            }
        }
    }
    
    if (isGameRealStartNow) {
        this->updateGameSpriteState();
        if (!isGamePause && isNowAddMonster) {
            addEnemyPlan->updateAddEnemy(this, dt,pathArray,enemyArray,enemyMonsterArray,deadSpriteArray,isGameSpeed2X);
        }
    }
    
    
    
}

