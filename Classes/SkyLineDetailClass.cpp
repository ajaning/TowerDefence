//
//  SkyLineDetailClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-7-23.
//
//

#include "SkyLineDetailClass.h"
#include "GameSubLevelSelClass.h"
#include "GameMainLevelClass.h"
#include "GameStartLayerClass.h"
#include "HelpLayerClass.h"
#include "GameParam.h"
#include "GameStageConClass.h"

SkyLineDetailClass::SkyLineDetailClass()
{

}

SkyLineDetailClass::~SkyLineDetailClass()
{

}

bool SkyLineDetailClass::init()
{
    char pFileName[100] = {0};
    char pBuffer[100] = {0};
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    float xScale = 1.0f;
    float yScale = 1.0f;
    
    LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(this);
    sprintf(pFileName, SPRITE_HD_NAME,"Themes/scene/stages_bg");
    strcat(pFileName, ".plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pFileName);

    memset(pFileName, 0, sizeof(pFileName));
    sprintf(pFileName, SPRITE_HD_NAME,"Themes/scene/stages_theme1");
    strcat(pFileName, ".plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pFileName);

    
    CCSprite* bgSprite = CCSprite::createWithSpriteFrameName("ss_bg.png");
    bgSprite->setPosition(ccp(size.width / 2, size.height / 2));
    this->addChild(bgSprite,1);
    
    detailScroll = ScrollViewClass::create();
    detailScroll->setTouchPrio(0);
    for (int i = 0; i < 6; i++) {
        GameSubLevelSelClass* selLayer = GameSubLevelSelClass::create(this, callfunc_selector(SkyLineDetailClass::selScrollCallBack));
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "ss_map%02d.png",(i + 1));
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(pBuffer);
        sprite->setPosition(ccp(size.width / 2, size.height / 2));
        selLayer->addChild(sprite);
        detailScroll->addlayer(selLayer, true,1);
    }
    this->addChild(detailScroll,100);
    
    
    CCMenuItemImage* homeBtn = CCMenuItemImage::create("ss_back_normal.png", "ss_back_pressed.png", this, menu_selector(SkyLineDetailClass::selMenuCallBack));
    homeBtn->setTag(1);
    homeBtn->setScaleX(xScale);
    homeBtn->setScaleY(yScale);
    CCSize homeBtnSize = homeBtn->getContentSize();
    homeBtn->setPosition(ccp(homeBtnSize.width * 2, size.height - homeBtnSize.height));
    CCMenu* homeBtnMenu = CCMenu::create(homeBtn,NULL);
	homeBtnMenu->setPosition(CCPointZero);
    this->addChild(homeBtnMenu,92);
    
    CCMenuItemImage* helpBtn = CCMenuItemImage::create("ss_help_normal.png", "ss_help_pressed.png", this, menu_selector(SkyLineDetailClass::selMenuCallBack));
    helpBtn->setTag(2);
    helpBtn->setScaleX(xScale);
    helpBtn->setScaleY(yScale);
    CCSize helpBtnSize = helpBtn->getContentSize();
    helpBtn->setPosition(ccp(size.width - helpBtnSize.width * 2, size.height - helpBtnSize.height));
    CCMenu* helpBtnMenu = CCMenu::create(helpBtn,NULL);
	helpBtnMenu->setPosition(CCPointZero);
    this->addChild(helpBtnMenu,92);
    
    CCSprite* leftCloud = CCSprite::createWithSpriteFrameName("ss_cloud.png");
    CCSize cloudSize = leftCloud->getContentSize();
    leftCloud->setPosition(ccp(size.width / 2, size.height / 2));
    this->addChild(leftCloud,102);
    
    return true;
}

CCScene* SkyLineDetailClass::createSkyLine()
{
    CCScene* scene = NULL;
    
    do {
        scene = CCScene::create();
        CC_BREAK_IF(!scene);
        
        SkyLineDetailClass* sky = SkyLineDetailClass::create();
        CC_BREAK_IF(!sky);
        
        scene->addChild(sky);
        
    } while (0);
    
    return scene;
}

void SkyLineDetailClass::selScrollCallBack()
{
    int curIndex = detailScroll->getCurPageIndex();
    int totalNum = detailScroll->getTotalPageNum();
    CCLog("the skyline touch index = %d",curIndex);
    switch (curIndex) {
        case 0:
            {
                
            }
            break;
        case 1:
            {
                GameStageConClass::sharedStageCon()->setGameStageIndex(1);
                GameStageConClass::sharedStageCon()->setGameStageRoundIndex(0);
                CCDirector::sharedDirector()->replaceScene(GameStartLayerClass::createGameStart());
            }
            break;
        default:
            break;
    }
}

void SkyLineDetailClass::selMenuCallBack(cocos2d::CCObject *menu)
{
    CCAssert(!(menu == NULL), "cannot be NULL");
    
    CCMenu* selMenu = (CCMenu*)menu;
    switch (selMenu->getTag()) {
        case 1:
        {
            CCDirector::sharedDirector()->replaceScene(GameMainLevelClass::createMainLevel());
        }
            break;
        case 2:
        {
            CCDirector::sharedDirector()->replaceScene(HelpLayerClass::createHelp());
        }
            break;
        default:
            break;
    }
}

