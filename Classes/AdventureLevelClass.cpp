//
//  AdventureLevelClass.cpp
//  CaratonFatans
//
//  Created by  Jack on 13-12-5.
//
//

#include "AdventureLevelClass.h"
#include "LcdAdapClass.h"
#include "WelcomeLayerClass.h"
#include "HelpLayerClass.h"
#include "GameStageConClass.h"
#include "GameStartLayerClass.h"
#include "GameParam.h"
#include "AdventureModeMainClass.h"
#include "GameMusicConClass.h"

#define SCROLL_DELTA_LEN    (20)

#define MENU_ID_START_TAG   (10)

#define MENU_ID_HOME_TAG    (2)
#define MENU_ID_HELP_TAG   (5)

static char comBuffer[255] = {0};

static int  skylineWave[] = {15,15,20,20,20,25,20,25,20,20,20,10};
static int  jungleWave[] = {15,20,20,20,25,20,20,25,20,20,20,30};
static int  desertWave[] = {15,20,20,20,25,20,20,30,20,25,20,20};
static int  extremeWave[] = {15,15,20,20,20,25,20,25,20,20,20,15,20,20,20,25,20,20,25,30};
static int  deepseaWave[] = {15,25,30,20,20,15,20,25,20,25,20,20,20,25,20,30,20,15};

typedef struct {
    GAME_STAGE_TYPE stage;
    int LevelNum;
    int *waveBuffer;
}gameStageLevelInfo;


static gameStageLevelInfo stageLevleConfig[] = {
    {GAME_STAGE_TYPE_NONE,0},
    
    {GAME_STAGE_TYPE_SKY,(sizeof(skylineWave)/sizeof(int)),skylineWave},
    {GAME_STAGE_TYPE_JUNG,(sizeof(jungleWave)/sizeof(int)),jungleWave},
    {GAME_STAGE_TYPE_DESERT,(sizeof(desertWave)/sizeof(int)),desertWave},
    {GAME_STAGE_TYPE_NONE,0,NULL},
    {GAME_STAGE_TYPE_EXTRE,(sizeof(extremeWave)/sizeof(int)),extremeWave},
    {GAME_STAGE_TYPE_DEEPSEA,(sizeof(deepseaWave)/sizeof(int)),deepseaWave},
    
    {GAME_STAGE_TYPE_MAX,0},
};

AdventureLevelClass::AdventureLevelClass()
{

}

AdventureLevelClass::~AdventureLevelClass()
{
    levelNormalArray->release();
    levelShadeArray->release();

    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    
}

bool AdventureLevelClass::init()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(this);
    
    levelNormalArray = CCArray::create();
    levelNormalArray->retain();
    
    levelShadeArray = CCArray::create();
    levelShadeArray->retain();
    
    userTouchStartPos = ccp(0, 0);
    
    levelNum = stageLevleConfig[GameStageConClass::sharedStageCon()->getGameStageIndex()].LevelNum;
    
    gameStageInfoStruct stageInfo = HUDClass::sharedHUD()->getGameCurStageInfo((GAME_STAGE_TYPE)(GameStageConClass::sharedStageCon()->getGameStageIndex()));
    curPageIndex = (stageInfo.lastLevelIndex - 1);
    
    
    CCLog("cur stage = %d",GameStageConClass::sharedStageCon()->getGameStageIndex());
    
    loadWaitSprite = CCSprite::create("loading-hd.png");
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(loadWaitSprite, ccp(size.width /2, size.height /2));
    this->addChild(loadWaitSprite,GAMING_LOADING_ZODER);
    
    return true;
}

void AdventureLevelClass::loadResAndInit()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/scene/stages_bg-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/scene/themescene1-hd.plist");
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "Themes/scene/stages_theme%d-hd.plist",GameStageConClass::sharedStageCon()->getGameStageIndex());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(comBuffer);
    
    
    bgSprite = CCSprite::createWithSpriteFrameName("ss_bg.png");
    CCSize bgSize = bgSprite->getContentSize();
    //    bgSprite->setPosition(ccp(size.width / 2, size.height / 2));
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(bgSprite, ccp(size.width / 2, size.height / 2));
    this->addChild(bgSprite,1);
    
    CCSprite* bgCN = CCSprite::createWithSpriteFrameName("ss_bg_CN.png");
    bgCN->setPosition(ccp(bgSize.width/2, bgSize.height/2));
    bgSprite->addChild(bgCN,1);
    
    
    if (GameStageConClass::sharedStageCon()->getGameStageIndex() != GAME_STAGE_TYPE_EXTRE) {
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "ss_towers_%02d.png",(curPageIndex + 1));
        levelTowerTypeSP = CCSprite::createWithSpriteFrameName(comBuffer);//default
        levelTowerTypeSP->setPosition(ccp(bgSize.width/2, bgSize.height * 18/100));
        bgSprite->addChild(levelTowerTypeSP,3);
        
        levelNumSP = CCSprite::createWithSpriteFrameName("ss_waves_10.png");//default
        levelNumSP->setPosition(ccp(bgSize.width/2, bgSize.height * 84/100));
        bgSprite->addChild(levelNumSP,3);
        
        CCSprite* leftCloud = CCSprite::createWithSpriteFrameName("ss_cloud.png");
        CCSize cloudSize = leftCloud->getContentSize();
        leftCloud->setPosition(ccp(bgSize.width / 2, bgSize.height / 2));
        bgSprite->addChild(leftCloud,5);
    }
    
    ccColor4B color;
    color.a = 125;
    color.b = 0;
    color.g = 0;
    color.r = 0;
    
    scrollLayer = CCLayer::create();//default pos is (0,0)
    scrollLayer->setContentSize(CCSize(size.width * levelNum / 2, size.height));
    bgSprite->addChild(scrollLayer,15);
    
    
    
    for (int i = 0; i < levelNum; i++) {
        
        gameLevelInfoStruct levelInfo = HUDClass::sharedHUD()->getGameCurLevelInfo((GAME_STAGE_TYPE)(GameStageConClass::sharedStageCon()->getGameStageIndex()), (i + 1));
        
        
        
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "ss_map%02d.png",(i + 1));
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(comBuffer);
        CCSize spriteSize = sprite->getContentSize();
        //sprite->setPosition(ccp(size.width / 2, size.height / 2));
        
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
        
        honorSP->setPosition(ccp(spriteSize.width * 84/100, spriteSize.height * 22/100));
        sprite->addChild(honorSP,1);
        
        CCSprite* allClearSP = CCSprite::createWithSpriteFrameName("gainhonor_4.png");
        if (!levelInfo.isClearAllObject) {
            allClearSP->setVisible(false);
        }
        allClearSP->setPosition(ccp(spriteSize.width * 60/100, spriteSize.height * 22/100));
        sprite->addChild(allClearSP,1);
        
        levelNormalArray->addObject(sprite);//normal
        
        CCLayerColor* layer = CCLayerColor::create(color);
        layer->setContentSize(spriteSize);
		ccBlendFunc blend = {GL_DST_ALPHA, GL_SRC_ALPHA};
		layer->setBlendFunc(blend);
        
        CCRenderTexture* rt = CCRenderTexture::create(spriteSize.width, spriteSize.height);
        sprite->setPosition(ccp(spriteSize.width/2, spriteSize.height/2));
        rt->begin();
        sprite->visit();
        layer->visit();
        rt->end();
        
        CCSprite* levelShade = CCSprite::createWithTexture(rt->getSprite()->getTexture());
        levelShade->setFlipY(true);
        levelShade->setPosition(ccp((bgSize.width/2) * (i + 1), bgSize.height / 2));
        levelShadeArray->addObject(levelShade);
        
        sprite->setPosition(ccp((bgSize.width/2) * (i + 1), bgSize.height / 2));
        sprite->setVisible(false);
        scrollLayer->addChild(levelShade,1);
        scrollLayer->addChild(sprite,1);
        
        if (i == curPageIndex) {//加个判断，哪一个关卡点亮
            curShadeLevelSprite = levelShade;
            curNormalLevelSprite = sprite;
            curShadeLevelSprite->setVisible(false);
            curNormalLevelSprite->setVisible(true);
        }
    }
    
    gameStartMenu = CCMenuItemImage::create("ss_play_normal_CN.png", "ss_play_pressed_CN.png", this, menu_selector(AdventureLevelClass::selMenuCallBack));
    
    if (GameStageConClass::sharedStageCon()->checkIsCurLevelLocked((curPageIndex + 1))) {
        gameStartMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ss_locked_CN.png"));
        gameStartMenu->setEnabled(false);
    }
    
    gameStartMenu->setTag(MENU_ID_START_TAG);
    gameStartMenu->setPosition(ccp(bgSize.width/2, bgSize.height * 8/ 100));
    
    CCMenuItemImage* homeBtn = CCMenuItemImage::create("ss_back_normal.png", "ss_back_pressed.png", this, menu_selector(AdventureLevelClass::selMenuCallBack));
    homeBtn->setTag(MENU_ID_HOME_TAG);
    homeBtn->setPosition(ccp(bgSize.width/25, bgSize.height * 95.5 / 100));
    
    CCMenuItemImage* helpBtn = CCMenuItemImage::create("ss_help_normal.png", "ss_help_pressed.png", this, menu_selector(AdventureLevelClass::selMenuCallBack));
    helpBtn->setTag(MENU_ID_HELP_TAG);
    helpBtn->setPosition(ccp(bgSize.width * 24/25, bgSize.height * 95.5 / 100));
    
    
    CCMenu* menu = CCMenu::create(homeBtn,helpBtn,gameStartMenu,NULL);
    menu->setPosition(CCPointZero);
    bgSprite->addChild(menu,2);
    
    loadWaitSprite->removeFromParentAndCleanup(true);
//    this->gotoPageIndexNow(curPageIndex);
    
    scrollLayer->setPosition(ccp((bgSize.width/2) * (-curPageIndex), 0));
}

CCScene* AdventureLevelClass::createScene()
{
    CCScene* scene = NULL;
    
    do {
        scene = CCScene::create();
        CC_BREAK_IF(!scene);
        
        AdventureLevelClass* adventure = AdventureLevelClass::create();
        CC_BREAK_IF(!adventure);
        
        scene->addChild(adventure);
        
    } while (0);
    
    return scene;
}

void AdventureLevelClass::selMenuCallBack(cocos2d::CCObject *menu)
{
    CCMenu* selMenu = (CCMenu*)menu;
    
    GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_MAIN_SELECT);
    switch (selMenu->getTag()) {
        case MENU_ID_HOME_TAG:
        {
            CCDirector::sharedDirector()->replaceScene(AdventureModeMainClass::createScene());
        }
            break;
        case MENU_ID_HELP_TAG:
        {
//            CCDirector::sharedDirector()->replaceScene(HelpLayerClass::createHelp());
        }
            break;
        case MENU_ID_START_TAG:
            {
                
                if (!GameStageConClass::sharedStageCon()->checkIsCurLevelLocked((curPageIndex + 1))) {
                    GameStageConClass::sharedStageCon()->setGameStageIndex(GameStageConClass::sharedStageCon()->getGameStageIndex());//一会儿修改
                    GameStageConClass::sharedStageCon()->setGameStageRoundIndex(curPageIndex + 1);
                    CCDirector::sharedDirector()->replaceScene(GameStartLayerClass::createGameStart());
                    
                    gameStageInfoStruct stageInfo;
                    stageInfo.isStageLocked = false;
                    stageInfo.lastLevelIndex = curPageIndex + 1;
                    stageInfo.stageType = (GAME_STAGE_TYPE)GameStageConClass::sharedStageCon()->getGameStageIndex();
                    HUDClass::sharedHUD()->setGameCurStageInfo(stageInfo);
                }
            }
            break;
    }
}

void AdventureLevelClass::onEnter()
{
    CCLayer::onEnter();
    this->loadResAndInit();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void AdventureLevelClass::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

bool AdventureLevelClass::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    userTouchStartPos = this->convertToNodeSpace(pTouch->getLocation());
    return true;
}

void AdventureLevelClass::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint curPos = scrollLayer->convertToNodeSpace(pTouch->getLocation());
    CCPoint prePos = scrollLayer->convertToNodeSpace(pTouch->getPreviousLocation());
    
    
    CCLOG("curPos x = %f  y = %f",curPos.x,curPos.y);
    
    CCPoint diffPos = ccpSub(curPos, prePos);
    
    CCPoint myPos = scrollLayer->getPosition();
    scrollLayer->setPosition(ccpAdd(ccp(myPos.x, myPos.y), ccp(diffPos.x, 0)));
}

void AdventureLevelClass::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint curPos = this->convertToNodeSpace(pTouch->getLocation());
    CCPoint prePos = userTouchStartPos;
    CCPoint diffPos = ccpSub(curPos, prePos);
    
    if (ccpLength(ccp(diffPos.x, 0)) > SCROLL_DELTA_LEN) {
        if (diffPos.x < 0) {
            
            curPageIndex += 1;
            if (curPageIndex >= (levelNum - 1)) {
                curPageIndex = levelNum - 1;
            }
        }
        else
        {
            curPageIndex -= 1;
            if (curPageIndex <= 0) {
                curPageIndex = 0;
            }
            
        }
        
        this->gotoPageIndexNow(curPageIndex);
    }
    else
    {
        GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_MAIN_SELECT);
        if (!GameStageConClass::sharedStageCon()->checkIsCurLevelLocked((curPageIndex + 1))) {
            GameStageConClass::sharedStageCon()->setGameStageIndex(GameStageConClass::sharedStageCon()->getGameStageIndex());//一会儿修改
            GameStageConClass::sharedStageCon()->setGameStageRoundIndex(curPageIndex + 1);
            CCDirector::sharedDirector()->replaceScene(GameStartLayerClass::createGameStart());
            
            gameStageInfoStruct stageInfo;
            stageInfo.isStageLocked = false;
            stageInfo.lastLevelIndex = curPageIndex + 1;
            stageInfo.stageType = (GAME_STAGE_TYPE)GameStageConClass::sharedStageCon()->getGameStageIndex();
            HUDClass::sharedHUD()->setGameCurStageInfo(stageInfo);
        }
    }
}

void AdventureLevelClass::gotoPageIndexNow(int index)
{
    CCSize size = bgSprite->getContentSize();//LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    
    CCMoveTo* mto = CCMoveTo::create(0.25, ccp((size.width/2) * (-index), 0));
    scrollLayer->runAction(CCSequence::create(mto,CCCallFunc::create(this, callfunc_selector(AdventureLevelClass::gotoPageIndexActionCallBack)),NULL));
}

void AdventureLevelClass::gotoPageIndexActionCallBack()
{
    
    GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_ITEM_MENU_SELECT);
    
    if (curShadeLevelSprite != NULL) {
        curShadeLevelSprite->setVisible(true);
    }
    
    if (curNormalLevelSprite != NULL) {
        curNormalLevelSprite->setVisible(false);
    }
    
    if (!GameStageConClass::sharedStageCon()->checkIsCurLevelLocked((curPageIndex + 1))) {
        gameStartMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ss_locked_CN.png"));
        gameStartMenu->setEnabled(false);
    }
    else
    {
        gameStartMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ss_play_normal_CN.png"));
        gameStartMenu->setEnabled(false);
    }
    
    if (GameStageConClass::sharedStageCon()->getGameStageIndex() != GAME_STAGE_TYPE_EXTRE) {
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "ss_towers_%02d.png",(curPageIndex + 1));
        levelTowerTypeSP->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
        
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "ss_waves_%d.png",stageLevleConfig[GameStageConClass::sharedStageCon()->getGameStageIndex()].waveBuffer[curPageIndex]);
        levelNumSP->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
    }
    
    

    curShadeLevelSprite = (CCSprite*)levelShadeArray->objectAtIndex(curPageIndex);
    curShadeLevelSprite->setVisible(true);
    
    curNormalLevelSprite = (CCSprite*)levelNormalArray->objectAtIndex(curPageIndex);
    curNormalLevelSprite->setVisible(true);


}


