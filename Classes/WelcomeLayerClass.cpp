//
//  WelcomeLayerClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-7-15.
//
//

#include "WelcomeLayerClass.h"
#include "GameParam.h"
#include "HelpLayerClass.h"
#include "GameMainLevelClass.h"
#include "LcdAdapClass.h"
#include "PetsNestClass.h"
#include "BossModeClass.h"
#include "GameStageConClass.h"
#include "AdventureModeMainClass.h"
#include "GameMusicConClass.h"

//#include "gameADConClass.h"
#include "gameADShowClass.h"

#define MENU_ID_ADVENTURE_MODE   (2)
#define MENU_ID_BOSS_MODE   (3)
#define MENU_ID_MONSTER_NEST (4)
#define MENU_ID_GAME_SETTING (5)
#define MENU_ID_GAME_HELP (6)



WelcomeLayerClass::WelcomeLayerClass()
{

}

WelcomeLayerClass::~WelcomeLayerClass()
{

}

bool WelcomeLayerClass::init()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    
    LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(this);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/scene/mainscene1-hd.plist");

    
    CCSprite* bg = CCSprite::createWithSpriteFrameName("mainbg.png");
    CCSize bgSize = bg->getContentSize();

    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(bg, ccp(size.width/2.0,size.height / 2.0));
    this->addChild(bg,10);
    
    CCSprite* bird = CCSprite::createWithSpriteFrameName("bird.png");
    bird->setPosition(ccp(bgSize.width * 15 / 100.0, bgSize.height * 70 / 100.0));
    CCActionInterval* moveby = CCMoveBy::create(2, ccp(0, -bgSize.height / 10));
    CCActionInterval* reback = moveby->reverse();
    bird->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(moveby,reback,NULL)));
    bg->addChild(bird,10);
    
    CCSprite* bgLogo = CCSprite::createWithSpriteFrameName("mainbg_CN.png");
    bgLogo->setPosition(ccp(bgSize.width / 2, bgSize.height/2));
//    welSpriteBatch->addChild(bgLogo,99);
    bg->addChild(bgLogo,100);
    
    
    CCSprite* carrot = CCSprite::createWithSpriteFrameName("carrot.png");

    CCSize carrotSize = carrot->getContentSize();
    carrot->setPosition(ccp(bgSize.width * 50 / 100.0, bgSize.height * 45 / 100.0));
    carrot->runAction(CCMoveTo::create(0.1, ccp(bgSize.width * 50 / 100.0, bgSize.height * 55 / 100.0)));
    bg->addChild(carrot,50);
    
    
    
    CCSprite* leaf2 = CCSprite::createWithSpriteFrameName("leaf-2.png");

    leaf2->setAnchorPoint(ccp(0.5, 0.1));
    leaf2->setPosition(ccp(carrotSize.width/2.0, carrotSize.height * 88/100.0));
    CCSize leaf2Size = leaf2->getContentSize();
//    leaf2->setPosition(ccp(size.width / 2, size.height / 2 + carrotSize.height - 5));
    
    CCActionInterval* rotateby = CCRotateBy::create(0.1, 15);
    CCActionInterval* norot2 = CCRotateBy::create(0.9, 0);
    CCActionInterval* interval = CCRotateBy::create(5, 0.0f);
    leaf2->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(interval,rotateby,rotateby->reverse(),rotateby,rotateby->reverse(),rotateby,rotateby->reverse(),norot2,NULL)));
//    welSpriteBatch->addChild(leaf2,97);
    carrot->addChild(leaf2,10);
    
    
    CCSprite* leaf3 = CCSprite::createWithSpriteFrameName("leaf-3.png");
    leaf3->setPosition(ccp(carrotSize.width * 65 / 100.0, carrotSize.height * 112/100.0));
    leaf3->setAnchorPoint(ccp(0.1, 0.5));
    
    leaf3->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(interval,norot2,rotateby,rotateby->reverse(),rotateby,rotateby->reverse(),rotateby,rotateby->reverse(),NULL)));
    carrot->addChild(leaf3,8);
    
    CCSprite* leaf1 = CCSprite::createWithSpriteFrameName("leaf-1.png");
    leaf1->setPosition(ccp(carrotSize.width * 24/100.0, carrotSize.height * 117/100.0));
    carrot->addChild(leaf1,8);
    
    CCSprite* cloud2 = CCSprite::createWithSpriteFrameName("cloud2.png");
    cloud2->setTag(2);
    CCSize cloudSize = cloud2->getContentSize();
//    cloud2->setPosition(ccp(-cloudSize.width, size.height - cloudSize.height));
    cloud2->setPosition(ccp(bgSize.width * -12/100.0, bgSize.height * 87 /100.0));
    CCActionInterval* moveInter = CCRotateBy::create(3, 0);
    CCActionInterval* cloud2moveBy = CCMoveBy::create(30, ccp(bgSize.width + cloudSize.width, 0));
    
    CCCallFuncN* call = CCCallFuncN::create(this, callfuncN_selector(WelcomeLayerClass::cloudMoveByCallBack));
    cloud2->runAction((CCActionInterval*)CCSequence::create(moveInter,cloud2moveBy,call,NULL));
//    welSpriteBatch->addChild(cloud2,94);
    bg->addChild(cloud2,90);
    
    CCSprite* cloud1 = CCSprite::createWithSpriteFrameName("cloud1.png");
    cloud1->setTag(1);
    CCSize cloud1Size = cloud1->getContentSize();
//    cloud1->setPosition(ccp(-cloud1Size.width, size.height - cloud1Size.height*2));
    cloud1->setPosition(ccp(bgSize.width * -5 / 100.0, bgSize.height * 78 /100.0));
    CCActionInterval* cloud1moveBy = CCMoveBy::create(20, ccp(size.width + cloud1Size.width, 0));
    CCCallFuncN* cloud1call = CCCallFuncN::create(this, callfuncN_selector(WelcomeLayerClass::cloudMoveByCallBack));
    cloud1->runAction(CCSequence::create(moveInter,cloud1moveBy,cloud1call,NULL));
    bg->addChild(cloud1,80);
    
	CCSprite* btn_adventure_normal_CN = CCSprite::createWithSpriteFrameName("btn_adventure_normal_CN.png");
    CCMenuItemImage* adventureBtn = CCMenuItemImage::create("btn_adventure_normal_CN.png", "btn_adventure_pressed_CN.png", this, menu_selector(WelcomeLayerClass::selMenuCallBack));
    adventureBtn->setTag(MENU_ID_ADVENTURE_MODE);
    adventureBtn->setPosition(ccp(bgSize.width * 20 / 100, bgSize.height * 12 / 100.0));
    
    
    CCMenuItemImage* bossBtn = CCMenuItemImage::create("btn_boss_normal_CN.png", "btn_boss_pressed_CN.png", this, menu_selector(WelcomeLayerClass::selMenuCallBack));
    bossBtn->setTag(MENU_ID_BOSS_MODE);
    bossBtn->setPosition(ccp(bgSize.width / 2, bgSize.height * 12/100.0));
    
    if(1)//i will add lock here
    {
        CCSprite* bossLock = CCSprite::createWithSpriteFrameName("locked.png");

        bossLock->setPosition(ccp(bgSize.width * 63 / 100.0, bgSize.height * 10 / 100.0));
        bg->addChild(bossLock,50);
    }
    
    CCMenuItemImage* nestBtn = CCMenuItemImage::create("btn_nest_normal_CN.png", "btn_nest_pressed_CN.png", this, menu_selector(WelcomeLayerClass::selMenuCallBack));
    nestBtn->setTag(MENU_ID_MONSTER_NEST);

    nestBtn->setPosition(ccp(bgSize.width * 80/100.0, bgSize.height * 12 /100.0));
    
    if(1)//i will add lock here
    {
        CCSprite* nestLock = CCSprite::createWithSpriteFrameName("locked.png");
        nestLock->setPosition(ccp(bgSize.width * 93 / 100.0, bgSize.height * 10 / 100.0));
        bg->addChild(nestLock,50);
    }
    
    
//    CCMenuItemImage* settingBtn = CCMenuItemImage::create("btn_setting_normal.png", "btn_setting_pressed.png", this, menu_selector(WelcomeLayerClass::selMenuCallBack));
//    settingBtn->setTag(MENU_ID_GAME_SETTING);
//    settingBtn->setPosition(ccp(bgSize.width * 20 / 100, bgSize.height * 35 / 100.0));

    CCLabelTTF* settingBtnLAB = CCLabelTTF::create("广告演示", "Arial", 20);
    ccColor3B color;
    
    color.r = 255;
    color.g = 0;
    color.b = 0;
    settingBtnLAB->setColor(color);
    CCMenuItemLabel* settingBtn = CCMenuItemLabel::create(settingBtnLAB, this, menu_selector(WelcomeLayerClass::selMenuCallBack));
    settingBtn->setTag(MENU_ID_GAME_SETTING);
    settingBtn->setPosition(ccp(bgSize.width * 20 /100.0, bgSize.height * 35 / 100.0));
    
    CCMenuItemImage* helpBtn = CCMenuItemImage::create("btn_help_normal.png", "btn_help_pressed.png", this, menu_selector(WelcomeLayerClass::selMenuCallBack));
    helpBtn->setTag(MENU_ID_GAME_HELP);
    helpBtn->setPosition(ccp(bgSize.width * 80 / 100.0, bgSize.height * 35 / 100.0));

    
    CCMenu* welMenu = CCMenu::create(adventureBtn,bossBtn,nestBtn,settingBtn,helpBtn,NULL);
    welMenu->setPosition(CCPointZero);
    bg->addChild(welMenu,20);
    GameMusicConClass::sharedMusicCon()->loadGameMusicEffectRes();
    
    GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_MAIN_BG_MUSIC);

    
    
    return true;
}

CCScene* WelcomeLayerClass::welcomSceneCreate()
{
    CCScene* scene = NULL;
    
    do {
        scene = CCScene::create();
        CC_BREAK_IF(!scene);
        
        WelcomeLayerClass* welGaem = WelcomeLayerClass::create();
        CC_BREAK_IF(!welGaem);
        
        scene->addChild(welGaem,WELCOMELAYER_SCENE_ZORDER);
        
    } while (0);
    
    return scene;
}


void WelcomeLayerClass::cloudMoveByCallBack(cocos2d::CCNode *parent)
{
    CCAssert(!(parent == NULL), "parent cannot be  NULL");
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    CCNode* cloud = parent;
    CCSize cloudSize = cloud->getContentSize();
    CCActionInterval* moveBy = NULL;
    if (cloud->getTag() == 2) {
        cloud->setPosition(ccp(-cloudSize.width, size.height - cloudSize.height));
        moveBy = CCMoveBy::create(30, ccp(size.width + cloudSize.width, 0));
    }
    else
    {
        cloud->setPosition(ccp(-cloudSize.width, size.height - cloudSize.height*2));
        moveBy = CCMoveBy::create(20, ccp(size.width + cloudSize.width, 0));
    }
    
    CCActionInterval* moveInter = CCRotateBy::create(3, 0);
    CCCallFuncN* call = CCCallFuncN::create(this, callfuncN_selector(WelcomeLayerClass::cloudMoveByCallBack));
    cloud->runAction((CCActionInterval*)CCSequence::create(moveInter,moveBy,call,NULL));
}


void WelcomeLayerClass::selMenuCallBack(cocos2d::CCObject *parent)
{
    CCAssert(!(parent == NULL), "cannot be NULL");
    CCMenu* menu = (CCMenu*)parent;
    CCLOG("this menu tag = %d",menu->getTag());
    
    GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_MAIN_SELECT);
    
    switch (menu->getTag()) {
        case MENU_ID_ADVENTURE_MODE:
            {
                
                GameStageConClass::sharedStageCon()->setGameModeType(GAME_MODE_TYPE_ADVENTURE);
//                CCDirector::sharedDirector()->replaceScene(GameMainLevelClass::createMainLevel());
                CCDirector::sharedDirector()->replaceScene(AdventureModeMainClass::createScene());
            }
            break;
        case MENU_ID_BOSS_MODE:
            {
                GameStageConClass::sharedStageCon()->setGameModeType(GAME_MODE_TYPE_BOSS);
                CCDirector::sharedDirector()->replaceScene(BossModeClass::createScene());
            }
            break;
        case MENU_ID_MONSTER_NEST:
        {
            CCDirector::sharedDirector()->replaceScene(PetsNestClass::createScene());
        }
            break;
        case MENU_ID_GAME_SETTING:
        {
//            gameADConClass* gamecon = gameADConClass::create();
//            gamecon->showADNow();
//            gameADConClass::shareGameADCon()->gameLoadDMOfferWallList();
//            gameADShowClass* showLayer = gameADShowClass::create();
//            this->addChild(showLayer,1000);
            CCDirector::sharedDirector()->replaceScene(gameADShowClass::createMyScene());
        }
            break;
        case MENU_ID_GAME_HELP:
        {
//            CCDirector::sharedDirector()->replaceScene(HelpLayerClass::createHelp());
        }
            break;
            
            
        default:
            break;
    }
    
    
    
}
