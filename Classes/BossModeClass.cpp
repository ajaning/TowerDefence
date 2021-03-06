//
//  BossModeClass.cpp
//  CaratonFatans
//
//  Created by  Jack on 13-12-3.
//
//

#include "BossModeClass.h"
#include "LcdAdapClass.h"
#include "WelcomeLayerClass.h"
#include "HelpLayerClass.h"
#include "GameSpriteParm.h"
#include "GameStartLayerClass.h"
#include "GameStageConClass.h"

#define SCROLL_DELTA_LEN    (5)
#define BOSS_NUM_MAX    (16)

#define BOSS_MENU_HOME_ID   (2)
#define BOSS_MENU_HELP_ID   (3)
#define BOSS_MENU_STARTGAME_ID (4)

#define BOSS_GAMEBG_ZORDER (1)
#define BOSS_GAME_SHOW_BOSS_ZORDER  (2)
#define BOSS_MENU_ZORDER (5)

#define BOSS_BLOOD_ZORDER (7)

#define BOSS_COM_ZORDER  (10)

#define BOSS_GAMEBG_CN_ZORDER (90)

#define BOSS_LIGHT_ZORDER  (BOSS_COM_ZORDER - 1)

//typedef struct {
//    int bossID;
//    int bloodValueID;
//    int timeLimitID;
//}bossDataInfo;
//
//
//static bossDataInfo bossConfigData[] = {
//    {0,0,0},
//    {1,80000,90},
//    {2,20000,80},
//    {3,75000,80},
//    {4,110000,110},
//    {5,40000,90},
//    {6,110000,110},
//    {7,50000,110},
//    {8,50000,180},
//    {9,60000,100},
//    {10,80000,90},
//    {11,500000,60},
//    {12,400000,180},
//    {13,200000,130},
//    {14,200000,168},
//    {15,70000,60},
//    {16,400000,180},
//    {0,0,0},
//};

static char comBuffer[255] = {0};

BossModeClass::BossModeClass()
{

}

BossModeClass::~BossModeClass()
{
    bossNormalArray->release();
    bossShaderArray->release();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

bool BossModeClass::init()
{
    LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(this);
    
    bossIndex = 0;
    userTouchStartPos = ccp(0,0);
    curSelBossSprite = NULL;
    curHideShadeBossSprite = NULL;
    bossShaderArray = CCArray::create();
    bossShaderArray->retain();
    
    bossNormalArray = CCArray::create();
    bossNormalArray->retain();
    
        
    return true;
}

CCScene* BossModeClass::createScene()
{
    CCScene* scene = NULL;
    
    do {
        scene = CCScene::create();
        CC_BREAK_IF(!scene);
        
        BossModeClass* boss = BossModeClass::create();
        CC_BREAK_IF(!boss);
        
        scene->addChild(boss);
        
    } while (0);
    
    return scene;
}

void BossModeClass::loadResAndInit()
{
    
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/scene/stages_bg-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/scene/antiboss1-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/scene/antiboss2-hd.plist");
    
    gameStageInfoStruct stageInfo = HUDClass::sharedHUD()->getGameCurStageInfo(GAME_STAGE_TYPE_BOSS_MODE);
    bossIndex = (stageInfo.lastLevelIndex - 1);
    
    GameStageConClass::sharedStageCon()->setGameBossID((bossIndex + 1));
    GameStageConClass::sharedStageCon()->setBossMonsterTypeID(GAME_ENEMY_MONSTERS_BOSS_BIG);
    GameStageConClass::sharedStageCon()->setGameStageIndex(GAME_STAGE_TYPE_BOSS_MODE);
    
    gameBG = CCSprite::createWithSpriteFrameName("theme_bg.png");
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(gameBG, ccp(size.width / 2, size.height / 2));
    this->addChild(gameBG,BOSS_GAMEBG_ZORDER);
    CCSize bgSize = gameBG->getContentSize();
    
    CCMenuItemImage* homeMenu = CCMenuItemImage::create("theme_home_normal.png", "theme_home_pressed.png", this, menu_selector(BossModeClass::menuSelActionCallBack));
    homeMenu->setPosition(ccp(bgSize.width/25, bgSize.height * 95.5 / 100));
    homeMenu->setTag(BOSS_MENU_HOME_ID);
    
    
    
    CCMenuItemImage* helpMenu = CCMenuItemImage::create("ss_help_normal.png", "ss_help_pressed.png", this, menu_selector(BossModeClass::menuSelActionCallBack));
    helpMenu->setPosition(ccp(bgSize.width * 24/25, bgSize.height * 95.5 / 100));
    helpMenu->setTag(BOSS_MENU_HELP_ID);
    
    startBossMenuItem = CCMenuItemImage::create("theme_play_normal_CN.png", "theme_play_pressed_CN.png", this, menu_selector(BossModeClass::menuSelActionCallBack));
    startBossMenuItem->setPosition(ccp(bgSize.width * 65/100, bgSize.height * 13 / 100));
    startBossMenuItem->setTag(BOSS_MENU_STARTGAME_ID);
    
    
    CCMenu* menu = CCMenu::create(homeMenu,helpMenu,startBossMenuItem,NULL);
    menu->setPosition(CCPointZero);
    gameBG->addChild(menu,BOSS_MENU_ZORDER);
    
    
    lightSprite = CCSprite::createWithSpriteFrameName("light.png");
    lightSprite->setPosition(ccp(bgSize.width / 2,bgSize.height * 77 / 100));
    gameBG->addChild(lightSprite,BOSS_LIGHT_ZORDER);
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "name_%02d_normal.png",GameStageConClass::sharedStageCon()->getGameBossID());
    
    bossNameSprite = CCSprite::createWithSpriteFrameName(comBuffer);//default name
    bossNameSprite->setPosition(ccp(bgSize.width / 2, bgSize.height * 77 /100));
    gameBG->addChild(bossNameSprite,BOSS_COM_ZORDER);
    
//    userHonourSprite = CCSprite::createWithSpriteFrameName("gainhonor_1.png");//default
//    userHonourSprite->setPosition(ccp(bgSize.width * 13/20, bgSize.height * 9/20));
//    userHonourSprite->setVisible(true);
//    gameBG->addChild(userHonourSprite,BOSS_COM_ZORDER);
    
    CCSprite* blood = CCSprite::createWithSpriteFrameName("blood_bg.png");
    blood->setPosition(ccp(bgSize.width/2, bgSize.height *6 / 25));
    gameBG->addChild(blood,BOSS_BLOOD_ZORDER);
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "blood_%02d.png",GameStageConClass::sharedStageCon()->getBossBloodValue());
    
    bloodValueSprite = CCSprite::createWithSpriteFrameName(comBuffer);
    bloodValueSprite->setPosition(ccp(bgSize.width/2, bgSize.height * 6 /25));
    gameBG->addChild(bloodValueSprite,BOSS_COM_ZORDER);
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "timelimit_%02d_CN.png",GameStageConClass::sharedStageCon()->getBossTimeLimit());
    bossTimeLimitSprite = CCSprite::createWithSpriteFrameName(comBuffer);
    bossTimeLimitSprite->setPosition(ccp(bgSize.width * 2/5, bgSize.height * 13 /100));
    gameBG->addChild(bossTimeLimitSprite,BOSS_COM_ZORDER);
    
    CCSprite* bgcn = CCSprite::createWithSpriteFrameName("theme_bg_CN.png");//default
    bgcn->setPosition(ccp(bgSize.width/2, bgSize.height/2));
    gameBG->addChild(bgcn,BOSS_GAMEBG_CN_ZORDER);
    
    ccColor4B color;
    color.a = 125;
    color.b = 0;
    color.g = 0;
    color.r = 0;
    
    showBossLayer = CCLayer::create();//default pos is (0,0)
    showBossLayer->setContentSize(CCSize(size.width * BOSS_NUM_MAX / 2, size.height));
    gameBG->addChild(showBossLayer,BOSS_GAME_SHOW_BOSS_ZORDER);
    
    for (int i = 1; i < (BOSS_NUM_MAX + 1); i++) {
        
        gameLevelInfoStruct levelInfo = HUDClass::sharedHUD()->getGameCurLevelInfo(GAME_STAGE_TYPE_BOSS_MODE, i);
        
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "boss_%02d_normal.png",i);//boss name
        CCSprite* boss = CCSprite::createWithSpriteFrameName(comBuffer);
        CCSize bossSize = boss->getContentSize();
        
        bossNormalArray->addObject(boss);
        
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "%s","gainhonor_1.png");//这里要加个判断，判断用户的荣誉
        CCSprite* honorSP = NULL;
        if (levelInfo.UserGained > 0 && levelInfo.UserGained < 4) {
            sprintf(comBuffer, "gainhonor_%d.png",levelInfo.UserGained);
            honorSP = CCSprite::createWithSpriteFrameName(comBuffer);
            honorSP->setVisible(true);//要不要显示
        }
        else
        {
            honorSP = CCSprite::createWithSpriteFrameName(comBuffer);
            honorSP->setVisible(false);//要不要显示
        }
        
        honorSP->setPosition(ccp(bossSize.width * 84/100, bossSize.height * 22/100));
        boss->addChild(honorSP,1);
        
        CCSprite* allClearSP = CCSprite::createWithSpriteFrameName("gainhonor_4.png");
        if (!levelInfo.isClearAllObject) {
            allClearSP->setVisible(false);
        }
        allClearSP->setPosition(ccp(bossSize.width * 60/100, bossSize.height * 22/100));
        boss->addChild(allClearSP,1);
        
        CCLayerColor* layer = CCLayerColor::create(color);
        layer->setContentSize(bossSize);
        layer->setBlendFunc(ccBlendFunc{GL_DST_ALPHA,GL_SRC_ALPHA});
        CCRenderTexture* rt = CCRenderTexture::create(bossSize.width, bossSize.height);
        boss->setPosition(ccp(bossSize.width/2, bossSize.height/2));
        rt->begin();
        boss->visit();
        layer->visit();
        rt->end();
        
        CCSprite* bossShade = CCSprite::createWithTexture(rt->getSprite()->getTexture());
        
        bossShade->setFlipY(true);
        bossShade->setPosition(ccp((bgSize.width/2) * i, bgSize.height / 2));
        bossShaderArray->addObject(bossShade);
        
        boss->setPosition(ccp((bgSize.width/2) * i, bgSize.height / 2));
        
        showBossLayer->addChild(boss,1);
        showBossLayer->addChild(bossShade,1);
        
        if (i == (bossIndex + 1)) {//init curselbosssprite
            curSelBossSprite = boss;
            curHideShadeBossSprite = bossShade;
            bossShade->setVisible(false);
        }
        else
        {
            boss->setVisible(false);
            bossShade->setVisible(true);
        }
    }
    
    showBossLayer->setPosition(ccp((bgSize.width/2) * (-bossIndex), 0));

}

void BossModeClass::onEnter()
{
    CCLayer::onEnter();
    this->loadResAndInit();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void BossModeClass::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void BossModeClass::gotoBossIndexNow(int index)
{
    CCSize size = gameBG->getContentSize();//LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    
    CCMoveTo* mto = CCMoveTo::create(0.25, ccp((size.width/2) * (-index), 0));
    showBossLayer->runAction(CCSequence::create(mto,CCCallFunc::create(this, callfunc_selector(BossModeClass::gotoBossIndexActionCallBack)),NULL));
}

void BossModeClass::gotoBossIndexActionCallBack()
{
    if (curHideShadeBossSprite != NULL) {
        curHideShadeBossSprite->setVisible(true);
    }
    
    if (curSelBossSprite != NULL) {
        curSelBossSprite->setVisible(false);
    }
    
    GameStageConClass::sharedStageCon()->setGameBossID((bossIndex + 1));
    
    lightSprite->setVisible(true);
    curSelBossSprite = (CCSprite*)bossNormalArray->objectAtIndex(bossIndex);
    curSelBossSprite->setVisible(true);
    
    curHideShadeBossSprite = (CCSprite*)bossShaderArray->objectAtIndex(bossIndex);
    curHideShadeBossSprite->setVisible(false);
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "name_%02d_normal.png",GameStageConClass::sharedStageCon()->getGameBossID());
    bossNameSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "blood_%d.png",GameStageConClass::sharedStageCon()->getBossBloodValue());
    bloodValueSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "timelimit_%d_CN.png",GameStageConClass::sharedStageCon()->getBossTimeLimit());
    bossTimeLimitSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
}


bool BossModeClass::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    userTouchStartPos = this->convertToNodeSpace(pTouch->getLocation());
    
    return true;
}

void BossModeClass::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint curPos = showBossLayer->convertToNodeSpace(pTouch->getLocation());
    CCPoint prePos = showBossLayer->convertToNodeSpace(pTouch->getPreviousLocation());
    
    lightSprite->setVisible(false);
    
    CCLOG("curPos x = %f  y = %f",curPos.x,curPos.y);
    
    CCPoint diffPos = ccpSub(curPos, prePos);
    
    CCPoint myPos = showBossLayer->getPosition();
    showBossLayer->setPosition(ccpAdd(ccp(myPos.x, myPos.y), ccp(diffPos.x, 0)));
}

void BossModeClass::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint curPos = this->convertToNodeSpace(pTouch->getLocation());
    CCPoint prePos = userTouchStartPos;
    CCPoint diffPos = ccpSub(curPos, prePos);
    
    if (ccpLength(ccp(diffPos.x, 0)) > SCROLL_DELTA_LEN) {
        if (diffPos.x < 0) {
            bossIndex += 1;
            if (bossIndex >= (BOSS_NUM_MAX - 1)) {
                bossIndex = BOSS_NUM_MAX - 1;
            }
        }
        else
        {
            bossIndex -= 1;
            if (bossIndex <= 0) {
                bossIndex = 0;
            }
        }
        
        this->gotoBossIndexNow(bossIndex);
    }
    else
    {
        if (!GameStageConClass::sharedStageCon()->checkIsCurLevelLocked((bossIndex + 1))) {
            GameStageConClass::sharedStageCon()->setGameBossID(bossIndex + 1);
            GameStageConClass::sharedStageCon()->setGameStageRoundIndex(bossIndex + 1);
            CCDirector::sharedDirector()->replaceScene(GameStartLayerClass::createGameStart());
            
            gameStageInfoStruct stageInfo;
            stageInfo.isStageLocked = false;
            stageInfo.lastLevelIndex = bossIndex + 1;
            stageInfo.stageType = GAME_STAGE_TYPE_BOSS_MODE;
            HUDClass::sharedHUD()->setGameCurStageInfo(stageInfo);
        }
    }
}




void BossModeClass::menuSelActionCallBack(cocos2d::CCObject *object)
{
    CCMenuItemImage* menuitem = (CCMenuItemImage*)object;
    
    switch (menuitem->getTag()) {
        case BOSS_MENU_HOME_ID:
            {
                CCDirector::sharedDirector()->replaceScene(WelcomeLayerClass::welcomSceneCreate());
            }
            break;
        case BOSS_MENU_HELP_ID:
            {
//                CCDirector::sharedDirector()->replaceScene(HelpLayerClass::createHelp());
            }
            break;
        case BOSS_MENU_STARTGAME_ID:
            {
                if (!GameStageConClass::sharedStageCon()->checkIsCurLevelLocked((bossIndex + 1))) {
                    
                    GameStageConClass::sharedStageCon()->setGameBossID(bossIndex + 1);
                    GameStageConClass::sharedStageCon()->setGameStageRoundIndex(bossIndex + 1);
                    CCDirector::sharedDirector()->replaceScene(GameStartLayerClass::createGameStart());
                    
                    gameStageInfoStruct stageInfo;
                    stageInfo.isStageLocked = false;
                    stageInfo.lastLevelIndex = bossIndex + 1;
                    stageInfo.stageType = GAME_STAGE_TYPE_BOSS_MODE;
                    HUDClass::sharedHUD()->setGameCurStageInfo(stageInfo);
                }
            }
            break;
        default:
            break;
    }
}
