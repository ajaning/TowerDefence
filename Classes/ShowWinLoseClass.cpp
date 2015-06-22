//
//  ShowWinLoseClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-10-30.
//
//

#include "ShowWinLoseClass.h"
#include "LcdAdapClass.h"
#include "SkyLineDetailClass.h"
#include "GameStartLayerClass.h"
#include "GameStageConClass.h"
#include "AdventureLevelClass.h"
#include "BossModeClass.h"

#define SEL_ROUND_TAG       (2)
#define RETRY_GAME_TAG      (3)
#define CONTINUE_GAME_TAG   (4)


static ShowWinLoseClass* shared = NULL;

ShowWinLoseClass::ShowWinLoseClass()
{

}

ShowWinLoseClass::~ShowWinLoseClass()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

bool ShowWinLoseClass::init()
{
    char pFileName[100] = {0};
    
    
    gameWinLoseData.gameWinLoseType = GAME_WINLOSE_TYPE_NONE;
    gameWinLoseData.gameModeType = GAME_MODE_TYPE_NONE;
    gameWinLoseData.curRoundIndex = 0;
    gameWinLoseData.curSubRoundIndex = 0;
    gameWinLoseData.totalSubRoundNum = 0;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/scene/gameover-hd.plist");
    

    
    return true;
}

ShowWinLoseClass* ShowWinLoseClass::sharedShow(gameWinLoseStruct winLoseData)
{
    if (shared == NULL) {
        shared = ShowWinLoseClass::create();
    }
    shared->setGameWinLoseData(winLoseData);
    return shared;
}

void ShowWinLoseClass::setGameWinLoseData(gameWinLoseStruct winLoseData)
{
    gameWinLoseData.gameWinLoseType = winLoseData.gameWinLoseType;
    gameWinLoseData.gameModeType = winLoseData.gameModeType;
    gameWinLoseData.curRoundIndex = winLoseData.curRoundIndex;
    gameWinLoseData.curSubRoundIndex = winLoseData.curSubRoundIndex;
    gameWinLoseData.totalSubRoundNum = winLoseData.totalSubRoundNum;
    
//    if (gameWinLoseData.gameModeType == GAME_MODE_TYPE_ADVENTURE) {
//        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/scene/gameover0-hd.plist");
//        
//    }
//    else if (gameWinLoseData.gameModeType == GAME_MODE_TYPE_BOSS)
//    {
//        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/scene/gameover1-hd.plist");
//    }

}


void ShowWinLoseClass::showGameOver(cocos2d::CCNode *parent)
{
    char* bgFileName = NULL;
    char* subBgFileName = NULL;
    char* winLoseBgFileName = NULL;
    char buffer[20] = {0};
    
    CCMenuItemImage* newOrRetryMenuItem = NULL;
    
    CCAssert(!(parent == NULL), "parent cannot be NULL");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/scene/gameover-hd.plist");
    
    if (gameWinLoseData.gameModeType == GAME_MODE_TYPE_ADVENTURE) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/scene/gameover0-hd.plist");
        
    }
    else if (gameWinLoseData.gameModeType == GAME_MODE_TYPE_BOSS)
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/scene/gameover1-hd.plist");
    }
    
    if (gameWinLoseData.gameWinLoseType == GAME_WINLOSE_TYPE_WIN) {
        bgFileName = "win_bg.png";
        subBgFileName = "gainhonor_3.png";
        winLoseBgFileName = "win_bg_CN.png";
    }
    else if (gameWinLoseData.gameWinLoseType == GAME_WINLOSE_TYPE_LOSE)
    {
        bgFileName = "lose_bg.png";
        winLoseBgFileName = "lose_bg_CN.png";
    }
    
    CCAssert(!(bgFileName == NULL), "bgFileName cannot be NULL");
    CCSprite* bg = CCSprite::createWithSpriteFrameName(bgFileName);
    CCSize bgSize = bg->getContentSize();
    CCSize parentSize = LcdAdapClass::sharedLCDADAP()->getWinSize();
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(bg, ccp(parentSize.width / 2, parentSize.height / 2));
    parent->addChild(bg,5000);
    
    if (subBgFileName != NULL) {
        CCSprite* subBg = CCSprite::createWithSpriteFrameName(subBgFileName);
        subBg->setPosition(ccp(bgSize.width / 2,bgSize.height / 2 + bgSize.height / 3));
        bg->addChild(subBg);
    }
    
    CCAssert(!(winLoseBgFileName == NULL), "bgFileName cannot be NULL");
    CCSprite* winLoseBgSprite = CCSprite::createWithSpriteFrameName(winLoseBgFileName);
    CCSize winLoseBgSize = winLoseBgSprite->getContentSize();
    winLoseBgSprite->setPosition(ccp(bgSize.width / 2, bgSize.height / 2));
    bg->addChild(winLoseBgSprite);
    
    if (gameWinLoseData.gameModeType == GAME_MODE_TYPE_ADVENTURE) {
        sprintf(buffer, "%02d",gameWinLoseData.curSubRoundIndex);
        
        
        
        CCLabelAtlas* showSubRoundLab = CCLabelAtlas::create(buffer, "Themes/Items/numyellow0.png", 22, 20, 46);
        showSubRoundLab->setPosition(ccp(bgSize.width / 2 - bgSize.width / 27, bgSize.height / 2 + bgSize.height / 30));
        bg->addChild(showSubRoundLab);
        
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%02d",gameWinLoseData.totalSubRoundNum);
        
        CCLabelAtlas* showSubTotalRoundLab = CCLabelAtlas::create(buffer, "Themes/Items/numyellow0.png", 22, 20, 46);
        showSubTotalRoundLab->setPosition(ccp(bgSize.width / 2 + bgSize.width / 13, bgSize.height / 2 + bgSize.height / 30));
        bg->addChild(showSubTotalRoundLab);
        
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%d",gameWinLoseData.curRoundIndex);
        
        CCLabelAtlas* showRoundLab = CCLabelAtlas::create(buffer, "Themes/Items/numyellow0.png", 22, 20, 46);
        showRoundLab->setPosition(ccp(bgSize.width / 2 - bgSize.width / 10, bgSize.height / 2 - bgSize.height / 12));
        bg->addChild(showRoundLab);
    }
    else if (gameWinLoseData.gameModeType == GAME_MODE_TYPE_BOSS)
    {
        
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%02d",GameStageConClass::sharedStageCon()->getGameBossLastTime());
        
        CCLabelAtlas* gameLastTime = CCLabelAtlas::create(buffer, "Themes/Items/numyellow0.png", 22, 20, 46);
        gameLastTime->setPosition(ccp(bgSize.width * 46 /100, bgSize.height * 53 /100));
        bg->addChild(gameLastTime);

        
        
        CCLabelTTF* bossName = CCLabelTTF::create(GameStageConClass::sharedStageCon()->getBossIDName(), "Arial", 20);
        
        bossName->setPosition(ccp(bgSize.width/2, bgSize.height * 44/100));
        bg->addChild(bossName,10);
    }
    
    CCMenuItemImage* selRoundMenuItem = CCMenuItemImage::create("select_normal_CN.png", "select_pressed_CN.png", this, menu_selector(ShowWinLoseClass::menuSelCallBack));
    selRoundMenuItem->setTag(SEL_ROUND_TAG);
    //CCSize selRoundSize = selRoundMenuItem->getContentSize();
    selRoundMenuItem->setPosition(ccp(bgSize.width / 3, bgSize.height / 3 - bgSize.height / 15));
    
    if (gameWinLoseData.gameWinLoseType == GAME_WINLOSE_TYPE_WIN) {
        newOrRetryMenuItem = CCMenuItemImage::create("continue_normal_CN.png", "continue_pressed_CN.png", this, menu_selector(ShowWinLoseClass::menuSelCallBack));
        newOrRetryMenuItem->setTag(CONTINUE_GAME_TAG);
    }
    else if (gameWinLoseData.gameWinLoseType == GAME_WINLOSE_TYPE_LOSE)
    {
        newOrRetryMenuItem = CCMenuItemImage::create("retry_normal_CN.png", "retry_pressed_CN.png", this, menu_selector(ShowWinLoseClass::menuSelCallBack));
        newOrRetryMenuItem->setTag(RETRY_GAME_TAG);
    }
    CCAssert(!(newOrRetryMenuItem == NULL), "newOrRetryMenuItem cannot be NULL");
    newOrRetryMenuItem->setPosition(ccp(bgSize.width / 2 + bgSize.width / 6, bgSize.height / 3 - bgSize.height / 15));
    
    CCMenu* menu = CCMenu::create(selRoundMenuItem,newOrRetryMenuItem,NULL);
    menu->setPosition(CCPointZero);
    bg->addChild(menu);
}


void ShowWinLoseClass::menuSelCallBack(cocos2d::CCObject *object)
{
    CCMenu* menu = (CCMenu*)object;
    
    switch (menu->getTag()) {
        case SEL_ROUND_TAG:
            {
//                CCDirector::sharedDirector()->replaceScene(SkyLineDetailClass::createSkyLine());
                
                if (GameStageConClass::sharedStageCon()->getGameModeType() == GAME_MODE_TYPE_ADVENTURE){
                    CCDirector::sharedDirector()->replaceScene(AdventureLevelClass::createScene());
                }
                else if (GameStageConClass::sharedStageCon()->getGameModeType() == GAME_MODE_TYPE_BOSS){
                    CCDirector::sharedDirector()->replaceScene(BossModeClass::createScene());
                }
                
            }
            break;
        case CONTINUE_GAME_TAG:
            {
                int tmpStageRoundNum = GameStageConClass::sharedStageCon()->getGameStageRoundNum();
                int tmpStageRoundIndex = GameStageConClass::sharedStageCon()->getGameStageRoundIndex();
                
                if (GameStageConClass::sharedStageCon()->getGameModeType() == GAME_MODE_TYPE_ADVENTURE) {
                    int tmpStageNum = GameStageConClass::sharedStageCon()->getGameStageNum();
                    int tmpStageIndex = GameStageConClass::sharedStageCon()->getGameStageIndex();
                    
                    
                    
                    if (tmpStageRoundIndex < tmpStageRoundNum) {
                        tmpStageRoundIndex += 1;
                        GameStageConClass::sharedStageCon()->setGameStageRoundIndex(tmpStageRoundIndex);
                        CCDirector::sharedDirector()->replaceScene(GameStartLayerClass::createGameStart());
                    }
                    else if(tmpStageIndex < tmpStageNum)
                    {
                        tmpStageIndex += 1;
                        GameStageConClass::sharedStageCon()->setGameStageIndex(tmpStageIndex);
                        GameStageConClass::sharedStageCon()->setGameStageRoundIndex(0);
                        CCDirector::sharedDirector()->replaceScene(GameStartLayerClass::createGameStart());
                    }
                    else
                    {
                        CCDirector::sharedDirector()->replaceScene(AdventureLevelClass::createScene());
                    }
                }
                else if (GameStageConClass::sharedStageCon()->getGameModeType() == GAME_MODE_TYPE_BOSS)
                {
                    if (tmpStageRoundIndex < tmpStageRoundNum) {
                        tmpStageRoundIndex += 1;
                        
                        gameStageInfoStruct stageInfo;
                        stageInfo.isStageLocked = false;
                        stageInfo.lastLevelIndex = tmpStageRoundIndex;
                        stageInfo.stageType = GAME_STAGE_TYPE_BOSS_MODE;
                        HUDClass::sharedHUD()->setGameCurStageInfo(stageInfo);
                        
                        GameStageConClass::sharedStageCon()->setGameBossID(tmpStageRoundIndex);
                        GameStageConClass::sharedStageCon()->setGameStageRoundIndex(tmpStageRoundIndex);
                        CCDirector::sharedDirector()->replaceScene(GameStartLayerClass::createGameStart());
                    }
                    else
                    {
                        CCDirector::sharedDirector()->replaceScene(BossModeClass::createScene());
                    }
                }
            }
            break;
        case RETRY_GAME_TAG:
            {

                GameStageConClass::sharedStageCon()->setIsGameReStart(true);
                
                int tmpStageRoundIndex = GameStageConClass::sharedStageCon()->getGameStageRoundIndex();
                
                GameStageConClass::sharedStageCon()->setGameStageRoundIndex(tmpStageRoundIndex);
                CCDirector::sharedDirector()->replaceScene(GameStartLayerClass::createGameStart());
            }
            break;
        default:
            break;
    }
}
