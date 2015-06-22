//
//  ShowTowerFeatureClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-11-11.
//
//

#include "ShowTowerFeatureClass.h"
#include "LcdAdapClass.h"
ShowTowerFeatureClass::ShowTowerFeatureClass()
{

}

ShowTowerFeatureClass::~ShowTowerFeatureClass()
{
    
}


bool ShowTowerFeatureClass::init(GAME_SUBROUND_ADD_NEW_TOWER_TYPE towerShowType)
{
    char *pFileName = NULL;
    char buffer[100] = {0};
    
    ccColor4B color;
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    CCAssert(!(towerShowType == GAME_SUBROUND_ADD_NEW_TOWER_TYPE_NONE || towerShowType == GAME_SUBROUND_ADD_NEW_TOWER_TYPE_MAX), "must be valid");
    
    
    color.a = 125;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    
    CCLayerColor::initWithColor(color);
    
    for (int i = 0; i < 5; i++) {
        memset(buffer, 0, sizeof(buffer));
        if (i == 4) {
            sprintf(buffer, "Themes/Items/Items32-hd.plist");
        }
        else
        {
            sprintf(buffer, "Themes/Items/Items%02d-hd.plist",(4 + i));
        }
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(buffer);
    }
    
    towerBGSprite = CCSprite::createWithSpriteFrameName("NT-5.png");
    CCSize bgSize = towerBGSprite->getContentSize();
//    towerBGSprite->setPosition(ccp(size.width/2, size.height/2));
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(towerBGSprite, ccp(size.width/2, size.height/2));
    this->addChild(towerBGSprite,1);
    
    CCSprite* bgShowCN = CCSprite::createWithSpriteFrameName("NT-5_CN.png");
    bgShowCN->setPosition(ccp(bgSize.width / 2, (bgSize.height)/2));
    towerBGSprite->addChild(bgShowCN,2);
    
    bgShade1Sprite = CCSprite::createWithSpriteFrameName("NT-4.png");
    bgShade1Sprite->setPosition(ccp(bgSize.width / 2, bgSize.height / 2));
    //bgShade1Sprite->setRotation(-10);
    bgShade1Sprite->setVisible(false);
    towerBGSprite->addChild(bgShade1Sprite,-10);
    
    bgShade2Sprite = CCSprite::createWithSpriteFrameName("NT-4.png");
    bgShade2Sprite->setPosition(ccp(bgSize.width / 2, bgSize.height / 2));
    //bgShade2Sprite->setRotation(-8);
    bgShade2Sprite->setVisible(false);
    towerBGSprite->addChild(bgShade2Sprite,-10);
    
    bgShade3Sprite = CCSprite::createWithSpriteFrameName("NT-4.png");
    bgShade3Sprite->setPosition(ccp(bgSize.width / 2, bgSize.height / 2));
    //bgShade3Sprite->setRotation(-6);
    bgShade3Sprite->setVisible(false);
    towerBGSprite->addChild(bgShade3Sprite,-10);
    
    bgFlashSprite = CCSprite::createWithSpriteFrameName("NT-3.png");
    bgFlashSprite->setPosition(ccp(bgSize.width / 2, bgSize.height / 2));
    bgFlashSprite->setScaleX(1.1);
    bgFlashSprite->setScaleY(1.02);
    bgFlashSprite->setVisible(false);
    CCFadeIn* fadein = CCFadeIn::create(0.75);
    CCFadeOut* fadeout = CCFadeOut::create(0.75);
    bgFlashSprite->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(fadeout,fadein,NULL)));
    towerBGSprite->addChild(bgFlashSprite,-4);
    
    
    CCMenuItemImage* selMenu = CCMenuItemImage::create("NT-1.png", "NT-2.png", this, menu_selector(ShowTowerFeatureClass::selMenuCallBack));
    selMenu->setPosition(ccp(bgSize.width /2, (bgSize.height * 18) / 100));

    CCMenu* menu = CCMenu::create(selMenu,NULL);
    menu->setPosition(CCPointZero);
    towerBGSprite->addChild(menu,6);

    CCSprite* selMenuTXT = CCSprite::createWithSpriteFrameName("NT-1_CN.png");
    selMenuTXT->setPosition(ccp(bgSize.width /2, (bgSize.height * 18) / 100));
    towerBGSprite->addChild(selMenuTXT,7);
    
    
    switch (towerShowType) {
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_FAN:
            pFileName = "NT3_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_STAR:
            pFileName = "NT4_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_BALL:
            pFileName = "NT5_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_FIREBALL:
            pFileName = "NT6_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_BLUESTAR:
            pFileName = "NT7_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_SUN:
            pFileName = "NT8_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_ROCKET:
            pFileName = "NT9_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_PIN:
            pFileName = "NT10_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_ARROW:
            pFileName = "NT11_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_SNOW:
            pFileName = "NT12_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_PLANE:
            pFileName = "NT13_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_FISH:
            pFileName = "NT14_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_MUSHROOM:
            pFileName = "NT15_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_ANCHOR:
            pFileName = "NT16_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_CUTTLE:
            pFileName = "NT17_CN.png";
            break;
        case GAME_SUBROUND_ADD_NEW_TOWER_TYPE_BUFF:
            pFileName = "NT18_CN.png";
            break;
        default:
            break;
    }
    
    CCAssert(!(pFileName == NULL), "cannot be NULL");
    CCSprite* showTower = CCSprite::createWithSpriteFrameName(pFileName);
    showTower->setPosition(ccp(bgSize.width / 2,bgSize.height / 2));
    towerBGSprite->addChild(showTower,8);
    
    towerBGSprite->setScale(0.5);
    
    towerBGSprite->runAction(CCSequence::create(CCScaleTo::create(0.25, 1.5),CCFlipX3D::create(0.15),CCCallFunc::create(this, callfunc_selector(ShowTowerFeatureClass::towerBGFlipActionCallBack)),NULL));
    return true;
}

ShowTowerFeatureClass* ShowTowerFeatureClass::create(GAME_SUBROUND_ADD_NEW_TOWER_TYPE towerShowType)
{
    ShowTowerFeatureClass* showTower = new ShowTowerFeatureClass();
    
    if (showTower && showTower->init(towerShowType)) {
        showTower->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(showTower);
    }
    //LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(showTower);
    showTower->setContentSize(LcdAdapClass::sharedLCDADAP()->getWinSize());
    return showTower;
}

bool ShowTowerFeatureClass::init(GAME_SUBROUND_ADD_NEW_TOWER_TYPE towerShowType, cocos2d::CCObject *target, SEL_CallFunc selector)
{
    CCAssert(!(target == NULL || selector == NULL), "cannot be NULL");
    
    myTarget = target;
    mySelector = selector;
    
    this->init(towerShowType);
    
    return true;
}

ShowTowerFeatureClass* ShowTowerFeatureClass::create(GAME_SUBROUND_ADD_NEW_TOWER_TYPE towerShowType, cocos2d::CCObject *target, SEL_CallFunc selector){
    ShowTowerFeatureClass* showTower = new ShowTowerFeatureClass();
    
    if (showTower && showTower->init(towerShowType,target,selector)) {
        showTower->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(showTower);
    }
    showTower->setContentSize(LcdAdapClass::sharedLCDADAP()->getWinSize());
    //LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(showTower);
    return showTower;
}

void ShowTowerFeatureClass::towerBGFlipActionCallBack()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
    towerBGSprite->setGrid(NULL);
    bgFlashSprite->setVisible(true);
    //bgFlashSprite->setRotation(180);
    bgShade1Sprite->setVisible(true);
    bgShade1Sprite->setFlipX(true);
    bgShade2Sprite->setVisible(true);
    bgShade2Sprite->setFlipX(true);
    bgShade3Sprite->setVisible(true);

    
    bgShade1Sprite->runAction(CCMoveBy::create(0.5, ccp(-size.width * 2 /100, 0)));
    bgShade2Sprite->runAction(CCMoveBy::create(0.5, ccp(-size.width * 1 /100, 0)));
    bgShade3Sprite->runAction(CCMoveBy::create(0.5, ccp(size.width * 2 /100, 0)));
}


void ShowTowerFeatureClass::selMenuCallBack(CCObject *object)
{
    
//    CCAssert(!(myTarget == NULL), "cannot be NULL");
//    CCAssert(!(mySelector == NULL), "cannot be NULL");
    
    (myTarget->*mySelector)();
    this->removeFromParentAndCleanup(true);
}
