//
//  GameMainLevelClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-7-22.
//
//

#include "GameMainLevelClass.h"
#include "GameSubLevelSelClass.h"
#include "WelcomeLayerClass.h"
#include "HelpLayerClass.h"
#include "SkyLineDetailClass.h"
#include "GameParam.h"
#include "LcdAdapClass.h"

#define MENU_ID_HOME_TAG    (2)
#define MENU_ID_HELP_TAG   (5)

GameMainLevelClass::GameMainLevelClass()
{

}

GameMainLevelClass::~GameMainLevelClass()
{

}

bool GameMainLevelClass::init()
{
    char pFileName[100] = {0};
    char pBuffer[100] = {0};
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    float xScale = 1.0f;
    float yScale = 1.0f;
    
    LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(this);
    
    for (int i = 0; i < 3; i++) {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "Themes/scene/themescene%d",(i + 1));
        memset(pFileName, 0, sizeof(pFileName));
        
        sprintf(pFileName, SPRITE_HD_NAME,pBuffer);
        strcat(pFileName, ".plist");
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pFileName);
    }
    CCSprite* bgSprite = CCSprite::createWithSpriteFrameName("theme_bg.png");
    CCSize bgSize = bgSprite->getContentSize();
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(bgSprite, ccp(size.width/2, size.height/2));
    this->addChild(bgSprite,1);
    selLevelScroll = ScrollViewClass::create();
    //selLevelScroll->setTouchPrio(0);
    for (int i = 0; i < 6; i++) {
        GameSubLevelSelClass* selLayer = GameSubLevelSelClass::create(this, callfunc_selector(GameMainLevelClass::selLevelCallBack));
        memset(pBuffer, 0, sizeof(pBuffer));
        if (i == 0) {
            sprintf(pBuffer, "%s","giftthisapp.png");
        }
        else
        {
            sprintf(pBuffer, "theme_pack%02d.png",i);
        }
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(pBuffer);
        sprite->setPosition(ccp(size.width / 2, size.height / 2));
        selLayer->addChild(sprite);
        selLevelScroll->addlayer(selLayer, true,1);
    }
    this->addChild(selLevelScroll,100);
    
    
    CCMenuItemImage* homeBtn = CCMenuItemImage::create("theme_home_normal.png", "theme_home_pressed.png", this, menu_selector(GameMainLevelClass::selMenuCallBack));
    homeBtn->setTag(MENU_ID_HOME_TAG);
    homeBtn->setPosition(ccp(bgSize.width/25, bgSize.height * 95.5 / 100));
    CCMenu* homeBtnMenu = CCMenu::create(homeBtn,NULL);
	homeBtnMenu->setPosition(CCPointZero);
    bgSprite->addChild(homeBtnMenu,92);
    
    CCMenuItemImage* helpBtn = CCMenuItemImage::create("ss_help_normal.png", "ss_help_pressed.png", this, menu_selector(GameMainLevelClass::selMenuCallBack));
    helpBtn->setTag(MENU_ID_HELP_TAG);
    helpBtn->setPosition(ccp(bgSize.width * 24/25, bgSize.height * 95.5 / 100));
    CCMenu* helpBtnMenu = CCMenu::create(helpBtn,NULL);
	helpBtnMenu->setPosition(CCPointZero);
    bgSprite->addChild(helpBtnMenu,92);
    
    return true;
}

CCScene* GameMainLevelClass::createMainLevel()
{
    CCScene* scene = NULL;
    
    do {
        scene = CCScene::create();
        CC_BREAK_IF(!scene);
        
        GameMainLevelClass* mainLevel = GameMainLevelClass::create();
        CC_BREAK_IF(!mainLevel);
        
        scene->addChild(mainLevel);
        
    } while (0);
    
    return scene;
}

void GameMainLevelClass::selLevelCallBack()
{
    int index  = selLevelScroll->getCurPageIndex();
    int total = selLevelScroll->getTotalPageNum();
    CCLog("hello sel touched index = %d",index);
    switch (index) {
        case 2:
            {
                CCDirector::sharedDirector()->replaceScene(SkyLineDetailClass::createSkyLine());
            }
            break;
            
        default:
            break;
    }
}

void GameMainLevelClass::selMenuCallBack(CCObject* menu)
{
    CCAssert(!(menu == NULL), "cannot be NULL");
    
    CCMenu* selMenu = (CCMenu*)menu;
    switch (selMenu->getTag()) {
        case MENU_ID_HOME_TAG:
            {
                CCDirector::sharedDirector()->replaceScene(WelcomeLayerClass::welcomSceneCreate());
            }
            break;
        case MENU_ID_HELP_TAG:
            {
                CCDirector::sharedDirector()->replaceScene(HelpLayerClass::createHelp());
            }
            break;
        default:
            break;
    }
}
