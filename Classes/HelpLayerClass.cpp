//
//  HelpLayerClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-7-18.
//
//

#include "HelpLayerClass.h"
#include "WelcomeLayerClass.h"
#include "GameParam.h"
#include "LcdAdapClass.h"
HelpLayerClass::HelpLayerClass()
{

}

HelpLayerClass::~HelpLayerClass()
{

}

bool HelpLayerClass::init()
{
    char pFileName[100] = {0};
    char pNum[100] = {0};
    float xScale = 1.0f;
    float yScale = 1.0f;
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(this);
    for (int i = 1; i < 4; i++) {
        memset(pFileName, 0, sizeof(pFileName));
        sprintf(pFileName, "Themes/scene/help_%d-hd.plist",i);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pFileName);
    }
    
    CCSprite* helpBg = CCSprite::createWithSpriteFrameName("help_bg.png");
    helpBg->setPosition(ccp(size.width / 2, size.height / 2));
    this->addChild(helpBg,1);
    
    CCMenuItemImage* homeBtn = CCMenuItemImage::create("help_home_normal.png", "help_home_pressed.png", this, menu_selector(HelpLayerClass::helpMenuCallBack));
    homeBtn->setTag(0);
    homeBtn->setScaleX(xScale);
    homeBtn->setScaleY(yScale);
    CCSize homeBtnSize = homeBtn->getContentSize();
    homeBtn->setPosition(ccp(homeBtnSize.width, size.height - homeBtnSize.height));
    CCMenu* homeBtnMenu = CCMenu::create(homeBtn,NULL);
	homeBtnMenu->setPosition(CCPointZero);
    this->addChild(homeBtnMenu,92);
    
    
    
    CCMenuItemImage* helpBtn = CCMenuItemImage::create("tips_normal_CN.png", "tips_selected_CN.png", this, menu_selector(HelpLayerClass::helpMenuCallBack));
    helpBtn->setTag(1);
    helpBtn->setScaleX(xScale);
    helpBtn->setScaleY(yScale);
    CCSize helpBtnSize = helpBtn->getContentSize();
    helpBtn->setPosition(ccp(helpBtnSize.width * 3, size.height - helpBtnSize.height));
    CCMenu* helpBtnMenu = CCMenu::create(helpBtn,NULL);
	helpBtnMenu->setPosition(CCPointZero);
    this->addChild(helpBtnMenu,92);
    
    CCMenuItemImage* monsterBtn = CCMenuItemImage::create("monster_normal_CN.png", "monster_selected_CN.png", this, menu_selector(HelpLayerClass::helpMenuCallBack));
    monsterBtn->setTag(2);
    monsterBtn->setScaleX(xScale);
    monsterBtn->setScaleY(yScale);
    CCSize monsterBtnSize = monsterBtn->getContentSize();
    monsterBtn->setPosition(ccp(size.width / 2, size.height - monsterBtnSize.height));
    CCMenu* monsterBtnMenu = CCMenu::create(monsterBtn,NULL);
	monsterBtnMenu->setPosition(CCPointZero);
    this->addChild(monsterBtnMenu,92);
    
    
    CCMenuItemImage* towerBtn = CCMenuItemImage::create("tower_normal_CN.png", "tower_selected_CN.png", this, menu_selector(HelpLayerClass::helpMenuCallBack));
    towerBtn->setTag(3);
    towerBtn->setScaleX(xScale);
    towerBtn->setScaleY(yScale);
    CCSize towerBtnSize = towerBtn->getContentSize();
    towerBtn->setPosition(ccp(size.width - towerBtnSize.width * 3, size.height - towerBtnSize.height));
    CCMenu* towerBtnMenu = CCMenu::create(towerBtn,NULL);
	towerBtnMenu->setPosition(CCPointZero);
    this->addChild(towerBtnMenu,92);
    
    HelpScrollView = ScrollViewClass::create();
    
    char pBuffer[100] = {0};
    for (int i = 0; i < 4; i++) {
        CCLayer* scrollLayer = CCLayer::create();
        scrollLayer->setContentSize(size);
        sprintf(pBuffer, "tips_%d.png",(i+1));
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(pBuffer);
        sprite->setPosition(ccp(size.width / 2, size.height / 2));
        scrollLayer->addChild(sprite);
        HelpScrollView->addLayer(scrollLayer);
        memset(pBuffer, 0, sizeof(pBuffer));
    }
    HelpScrollView->setTouchPrio(0);
    this->addChild(HelpScrollView,80);
    TowerScrollView = ScrollViewClass::create();
    for (int i = 0; i < 18; i++) {
        CCLayer* scrollLayer = CCLayer::create();
        scrollLayer->setContentSize(size);
        sprintf(pBuffer, "tower_%02d.png",(i+1));
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(pBuffer);
        sprite->setPosition(ccp(size.width / 2, size.height / 2));
        scrollLayer->addChild(sprite);
        TowerScrollView->addLayer(scrollLayer);
        memset(pBuffer, 0, sizeof(pBuffer));
    }
//    TowerScrollView->setTouchPrio(1);
    this->addChild(TowerScrollView,70);
    TowerScrollView->setVisible(false);
    
    monsterSprite = CCSprite::createWithSpriteFrameName("help_monster.png");
    monsterSprite->setPosition(ccp(size.width / 2, size.height / 2));
    this->addChild(monsterSprite,60);
    monsterSprite->setVisible(false);
    
    bottomNumSprite = CCSprite::createWithSpriteFrameName("bottom_num_HD.png");
    CCSize numSize = bottomNumSprite->getContentSize();
    bottomNumSprite->setPosition(ccp(size.width / 2, numSize.height));
    this->addChild(bottomNumSprite,91);
    
    return true;
}

CCScene* HelpLayerClass::createHelp()
{
    CCScene* scene = NULL;
    
    do {
        scene = CCScene::create();
        CC_BREAK_IF(!scene);
        
        HelpLayerClass* helpGaem = HelpLayerClass::create();
        CC_BREAK_IF(!helpGaem);
        
        scene->addChild(helpGaem);
        
    } while (0);
    
    return scene;
}


void HelpLayerClass::helpMenuCallBack(cocos2d::CCObject *menu)
{
    CCAssert(!(menu == NULL), "menu cannot be NULL");
    CCMenu *item = (CCMenu*)menu;
    switch (item->getTag()) {
        case 0:
            {
                CCDirector::sharedDirector()->replaceScene(WelcomeLayerClass::welcomSceneCreate());
            }
            break;
        case 1:
            {
                TowerScrollView->removeTouchDelegate();
                HelpScrollView->setTouchPrio(0);
                //TowerScrollView->setTouchPrio(1);
                TowerScrollView->setVisible(false);
                monsterSprite->setVisible(false);
                HelpScrollView->setVisible(true);
                bottomNumSprite->setVisible(true);
            }
            break;
        case 2:
            {
                TowerScrollView->setVisible(false);
                monsterSprite->setVisible(true);
                HelpScrollView->setVisible(false);
                bottomNumSprite->setVisible(false);
            }
            break;
            
        case 3:
            {
                HelpScrollView->removeTouchDelegate();
                TowerScrollView->setTouchPrio(0);
                TowerScrollView->setVisible(true);
                monsterSprite->setVisible(false);
                HelpScrollView->setVisible(false);
                bottomNumSprite->setVisible(true);
            }
            break;
        default:
            break;
    }  
    
}

