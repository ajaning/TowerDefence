//
//  AdventureModeMainClass.cpp
//  CaratonFatans
//
//  Created by  Jack on 13-12-5.
//
//

#include "AdventureModeMainClass.h"
#include "LcdAdapClass.h"
#include "WelcomeLayerClass.h"
#include "HelpLayerClass.h"
#include "AdventureLevelClass.h"
#include "GameStageConClass.h"
#include "GameParam.h"
#include "HUDClass.h"
#include "GameMusicConClass.h"

#define SCROLL_DELTA_LEN    (20)
#define GAME_LEVEL_NUM_MAX (8)

#define MENU_ID_HOME_TAG    (2)
#define MENU_ID_HELP_TAG   (5)

#define MENU_ID_LEFT_TAG (10)
#define MENU_ID_RIGHT_TAG (12)

static char comBuffer[255] = {0};

//static gameStageInfoStruct stageInfo[] = {
//    {false,0,0,GAME_STAGE_TYPE_NONE},
//    {false,12,0,GAME_STAGE_TYPE_SKY},
//    {false,12,0,GAME_STAGE_TYPE_JUNG},
//    {false,12,0,GAME_STAGE_TYPE_DESERT},
//    {false,0,0,GAME_STAGE_TYPE_RESERVERD},
//    {true,20,0,GAME_STAGE_TYPE_EXTRE},
//    {false,18,0,GAME_STAGE_TYPE_DEEPSEA},
//    {false,0,0,GAME_STAGE_TYPE_MAX},
//};


AdventureModeMainClass::AdventureModeMainClass()
{

}

AdventureModeMainClass::~AdventureModeMainClass()
{
    userPointArray->release();

    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();

}

bool AdventureModeMainClass::init()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(this);
    
    curPageIndex = HUDClass::sharedHUD()->getGameStageLastesdID();
    
    userPointArray = CCArray::create();
    userPointArray->retain();
    
    loadWaitSprite = CCSprite::create("loading-hd.png");
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(loadWaitSprite, ccp(size.width /2, size.height /2));
    this->addChild(loadWaitSprite,GAMING_LOADING_ZODER);
    
    
    
//    this->gotoPageIndexNow(1);
    
    return true;
}

CCScene* AdventureModeMainClass::createScene()
{
    CCScene* scene = NULL;
    
    do {
        scene = CCScene::create();
        CC_BREAK_IF(!scene);
        
        AdventureModeMainClass* adventure = AdventureModeMainClass::create();
        CC_BREAK_IF(!adventure);
        
        scene->addChild(adventure);
        
    } while (0);
    
    return scene;
}


void AdventureModeMainClass::loadResAndInit()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/scene/stages_bg-hd.plist");
    for (int i = 0; i < 3; i++) {
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "Themes/scene/themescene%d-hd.plist",(i + 1));
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(comBuffer);
    }
    
    scrollLayer = CCLayer::create();
    scrollLayer->setContentSize(CCSize(size.width * GAME_LEVEL_NUM_MAX,size.height));
    this->addChild(scrollLayer,10);
    
    CCSprite* sprite = NULL;
    CCSprite* spriteCN = NULL;
    CCSprite* bookMarkSP = NULL;
    for (int i = 0; i < 7; i++) {
        memset(comBuffer, 0, sizeof(comBuffer));
        if (i == 0) {
            sprintf(comBuffer, "%s","giftthisapp.png");
            sprite = CCSprite::createWithSpriteFrameName(comBuffer);
            CCSize spriteSize = sprite->getContentSize();
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%s","giftthisapp_CN.png");
            spriteCN = CCSprite::createWithSpriteFrameName(comBuffer);
            spriteCN->setPosition(ccp(spriteSize.width/2, spriteSize.height/2));
            sprite->addChild(spriteCN,1);
        }
        else
        {
            int  j =  i;
            
            if (i == 4) {
                j += 1;
            }
            else if (i == 5)
            {
                j -= 1;
            }
            
            sprintf(comBuffer, "theme_pack%02d.png",j);
            sprite = CCSprite::createWithSpriteFrameName(comBuffer);
            CCSize spriteSize = sprite->getContentSize();
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "theme_pack%02d_CN.png",j);
            spriteCN = CCSprite::createWithSpriteFrameName(comBuffer);
            spriteCN->setPosition(ccp(spriteSize.width/2, spriteSize.height/2));
            sprite->addChild(spriteCN,1);
            //read data from xml
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "bookmark_12-12.png");
            bookMarkSP = CCSprite::createWithSpriteFrameName(comBuffer);
            bookMarkSP->setPosition(ccp(spriteSize.width*85/100, spriteSize.height*6/100));
            sprite->addChild(bookMarkSP,2);
        }
        
        //        sprite->setPosition(ccp(size.width *(i + 1/2), size.height / 2));
        LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(sprite, ccp((size.width)*(i + 1.0/2.0), size.height / 2));
        scrollLayer->addChild(sprite,1);
    }
    scrollLayer->setPosition(ccp((size.width) * (-curPageIndex), 0));
    
    CCSprite* bgSprite = CCSprite::createWithSpriteFrameName("theme_bg.png");
    CCSize bgSize = bgSprite->getContentSize();
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(bgSprite, ccp(size.width/2, size.height/2));
    this->addChild(bgSprite,1);
    
    
    CCSprite* bgCN = CCSprite::createWithSpriteFrameName("theme_bg_CN.png");
    bgCN->setPosition(ccp(bgSize.width/2,bgSize.height/2));
    bgSprite->addChild(bgCN,10);
    
    
    for (int i = 0; i < 8; i++) {
        CCSprite* point = NULL;
        if (i == curPageIndex) {
            point = CCSprite::createWithSpriteFrameName("theme_pos_active.png");
        }
        else
        {
            point = CCSprite::createWithSpriteFrameName("theme_pos_normal.png");
        }
        
        
        point->setPosition(ccp(bgSize.width * (40 + i * 2)/100, bgSize.height/20));
        bgSprite->addChild(point,1);
        userPointArray->addObject(point);
    }
    
    
    
    
    
    leftPointMenu = CCMenuItemImage::create("theme_pointleft_normal.png", "theme_pointleft_pressed.png", this, menu_selector(AdventureModeMainClass::selMenuCallBack));
    leftPointMenu->setTag(MENU_ID_LEFT_TAG);
    leftPointMenu->setPosition(ccp(bgSize.width * 10/100, bgSize.height/2));
    
    rightPointMenu = CCMenuItemImage::create("theme_pointright_normal.png", "theme_pointright_pressed.png", this, menu_selector(AdventureModeMainClass::selMenuCallBack));
    rightPointMenu->setTag(MENU_ID_RIGHT_TAG);
    rightPointMenu->setPosition(ccp(bgSize.width * 90/100, bgSize.height/2));
    
    
    CCMenuItemImage* homeBtn = CCMenuItemImage::create("theme_home_normal.png", "theme_home_pressed.png", this, menu_selector(AdventureModeMainClass::selMenuCallBack));
    homeBtn->setTag(MENU_ID_HOME_TAG);
    homeBtn->setPosition(ccp(bgSize.width/25, bgSize.height * 95.5 / 100));
    
    CCMenuItemImage* helpBtn = CCMenuItemImage::create("ss_help_normal.png", "ss_help_pressed.png", this, menu_selector(AdventureModeMainClass::selMenuCallBack));
    helpBtn->setTag(MENU_ID_HELP_TAG);
    helpBtn->setPosition(ccp(bgSize.width * 24/25, bgSize.height * 95.5 / 100));
    
    
    CCMenu* menu = CCMenu::create(leftPointMenu,rightPointMenu,homeBtn,helpBtn,NULL);
    menu->setPosition(CCPointZero);
    bgSprite->addChild(menu,2);
    
    loadWaitSprite->removeFromParentAndCleanup(true);
}

void AdventureModeMainClass::gotoPageIndexNow(int index)
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    
    CCFiniteTimeAction* mto = CCMoveTo::create(0.25, ccp((size.width) * (-index), 0));
    scrollLayer->runAction((CCActionInterval*)CCSequence::create(mto,CCCallFunc::create(this, callfunc_selector(AdventureModeMainClass::gotoPageIndexActionCallBack)),NULL));
}


void AdventureModeMainClass::gotoPageIndexActionCallBack()
{
    
    GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_ITEM_MENU_SELECT);
}


void AdventureModeMainClass::selMenuCallBack(CCObject* menu)
{
    CCAssert(!(menu == NULL), "cannot be NULL");
    
    CCMenu* selMenu = (CCMenu*)menu;
    
    GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_MAIN_SELECT);
    switch (selMenu->getTag()) {
        case MENU_ID_HOME_TAG:
        {
            CCDirector::sharedDirector()->replaceScene(WelcomeLayerClass::welcomSceneCreate());
        }
            break;
        case MENU_ID_HELP_TAG:
        {
//            CCDirector::sharedDirector()->replaceScene(HelpLayerClass::createHelp());
        }
            break;
        case MENU_ID_LEFT_TAG:
            {
                
                memset(comBuffer, 0, sizeof(comBuffer));
                sprintf(comBuffer, "%s","theme_pos_normal.png");

                
                CCSprite* posSP = (CCSprite*)userPointArray->objectAtIndex(curPageIndex);
                posSP->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
                
                
                curPageIndex += 1;
                if (curPageIndex >= (GAME_LEVEL_NUM_MAX - 1)) {
                    curPageIndex = GAME_LEVEL_NUM_MAX - 1;
                }
                
                memset(comBuffer, 0, sizeof(comBuffer));
                sprintf(comBuffer, "%s","theme_pos_active.png");
                posSP = (CCSprite*)userPointArray->objectAtIndex(curPageIndex);
                posSP->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
                this->gotoPageIndexNow(curPageIndex);
            }
            break;
        case MENU_ID_RIGHT_TAG:
            {
                
                memset(comBuffer, 0, sizeof(comBuffer));
                sprintf(comBuffer, "%s","theme_pos_normal.png");
                
                
                CCSprite* posSP = (CCSprite*)userPointArray->objectAtIndex(curPageIndex);
                posSP->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
                
                curPageIndex -= 1;
                if (curPageIndex <= 0) {
                    curPageIndex = 0;
                }
            
                memset(comBuffer, 0, sizeof(comBuffer));
                sprintf(comBuffer, "%s","theme_pos_active.png");
                posSP = (CCSprite*)userPointArray->objectAtIndex(curPageIndex);
                posSP->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
                this->gotoPageIndexNow(curPageIndex);
            }
            break;
        default:
            break;
    }
}





void AdventureModeMainClass::onEnter()
{
    CCLayer::onEnter();
    this->loadResAndInit();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void AdventureModeMainClass::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

bool AdventureModeMainClass::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    userTouchStartPos = this->convertToNodeSpace(pTouch->getLocation());
    
    return true;
}

void AdventureModeMainClass::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint curPos = scrollLayer->convertToNodeSpace(pTouch->getLocation());
    CCPoint prePos = scrollLayer->convertToNodeSpace(pTouch->getPreviousLocation());
    
    
    CCLOG("curPos x = %f  y = %f",curPos.x,curPos.y);
    
    CCPoint diffPos = ccpSub(curPos, prePos);
    
    CCPoint myPos = scrollLayer->getPosition();
    scrollLayer->setPosition(ccpAdd(ccp(myPos.x, myPos.y), ccp(diffPos.x, 0)));
}

void AdventureModeMainClass::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint curPos = this->convertToNodeSpace(pTouch->getLocation());
    CCPoint prePos = userTouchStartPos;
    CCPoint diffPos = ccpSub(curPos, prePos);
    
    if (ccpLength(ccp(diffPos.x, 0)) > SCROLL_DELTA_LEN) {
        if (diffPos.x < 0) {
            
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%s","theme_pos_normal.png");
            CCSprite* posSP = (CCSprite*)userPointArray->objectAtIndex(curPageIndex);
            posSP->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
            curPageIndex += 1;
            if (curPageIndex >= (GAME_LEVEL_NUM_MAX - 1)) {
                curPageIndex = GAME_LEVEL_NUM_MAX - 1;
            }
            
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%s","theme_pos_active.png");
            posSP = (CCSprite*)userPointArray->objectAtIndex(curPageIndex);
            posSP->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
        }
        else
        {
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%s","theme_pos_normal.png");
            CCSprite* posSP = (CCSprite*)userPointArray->objectAtIndex(curPageIndex);
            posSP->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
            
            curPageIndex -= 1;
            if (curPageIndex <= 0) {
                curPageIndex = 0;
            }
            
            
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%s","theme_pos_active.png");
            posSP = (CCSprite*)userPointArray->objectAtIndex(curPageIndex);
            posSP->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
        }
        
        this->gotoPageIndexNow(curPageIndex);
    }
    else
    {
        GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_MAIN_SELECT);
        if (curPageIndex >= 1 && curPageIndex <= 5) {
            GameStageConClass::sharedStageCon()->setGameStageNum(5);

            
            if (curPageIndex == 4) {
                GameStageConClass::sharedStageCon()->setGameStageIndex(curPageIndex + 2);//6
            }
            else
            {
                GameStageConClass::sharedStageCon()->setGameStageIndex(curPageIndex);//1,2,3,5
            }
            HUDClass::sharedHUD()->setGameStageLastedid((GAME_STAGE_TYPE)curPageIndex);
            CCDirector::sharedDirector()->replaceScene(AdventureLevelClass::createScene());
        }
    }
}


