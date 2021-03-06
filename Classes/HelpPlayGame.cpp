//
//  HelpPlayGame.cpp
//  CaratonFatans
//
//  Created by jack on 13-11-19.
//
//

#include "HelpPlayGame.h"
#include "LcdAdapClass.h"



HelpPlayGame::HelpPlayGame()
{
    
}

HelpPlayGame::~HelpPlayGame()
{

}

bool HelpPlayGame::init(CCObject* target, SEL_CallFunc func,CCPoint padPos)
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();

    CCAssert(!(target == NULL), "cannot be NULL");
    CCAssert(!(func == NULL), "cannot be NULL");
    
    myTarget = target;
    mySelector = func;
    
    
    padDictorPos = padPos;
    
    showTopMidBottomTxtIndex = 0;
    helpStateType = HELP_PLAYGAME_STATE_TYPE_START;
    
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Themes/Items/Items03-hd.plist");
    
    helpBGSprite = CCSprite::createWithSpriteFrameName("howtoplay_0.png");
    CCSize bgSize = helpBGSprite->getContentSize();
//    helpBGSprite->setPosition(ccp((size.width * 83) / 100 , size.height * 1.25));
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(helpBGSprite, ccp((size.width * 74) / 100 , size.height * 1.25));
    this->addChild(helpBGSprite,2);
    
    CCSprite* bgtxt = CCSprite::createWithSpriteFrameName("howtoplay_0_CN.png");
    bgtxt->setPosition(ccp(bgSize.width / 2, bgSize.height / 2));
    helpBGSprite->addChild(bgtxt,1);
//    CCMoveBy* mvby = CCMoveBy::create(1, ccp(0,-size.height * 0.52));
//    helpBGSprite->runAction(CCSequence::create(mvby,CCCallFunc::create(this, callfunc_selector(HelpPlayGame::helpBGActionCallBack))));

    CCMoveTo* mto = CCMoveTo::create(0.5, ccp((size.width * 74) / 100 , (size.height * 65)/100));
    helpBGSprite->runAction(CCSequence::create(mto,CCCallFunc::create(this, callfunc_selector(HelpPlayGame::helpBGActionCallBack)),NULL));
    
    
    selPadSprite = CCSprite::createWithSpriteFrameName("howtoplay_1.png");
    selPadSprite->setPosition(padDictorPos);
    this->addChild(selPadSprite,-2);
    
    CCFadeIn* fin = CCFadeIn::create(0.5);
    CCFadeOut* fout = CCFadeOut::create(0.5);
    selPadSprite->runAction(CCRepeatForever::create(CCSequence::create(fin,fout,NULL)));
    
    handSprite = CCSprite::createWithSpriteFrameName("howtoplay_2.png");
    handSprite->setPosition(padDictorPos);
    this->addChild(handSprite,3);
    CCMoveBy* mv1 = CCMoveBy::create(1, ccp(45,-45));
    CCMoveBy* mvreverse = (CCMoveBy*)mv1->reverse();
    
    handSprite->runAction(CCRepeatForever::create(CCSequence::create(mv1,mvreverse,NULL)));
    
    helpPicSprite = CCSprite::createWithSpriteFrameName("howtoplay_3.png");
    CCSize helpPicBGSize = helpPicSprite->getContentSize();
    helpPicSprite->setPosition(ccp(bgSize.width / 2,bgSize.height * 35 / 100));
    helpBGSprite->addChild(helpPicSprite,3);
    helpPicTextSprite = CCSprite::createWithSpriteFrameName("howtoplay_3_CN.png");
    helpPicTextSprite->setPosition(ccp(bgSize.width / 2,bgSize.height * 35 / 100));
    helpBGSprite->addChild(helpPicTextSprite,4);
    
    helpBGTopTxtSprite = CCSprite::createWithSpriteFrameName("howtoplay_6_CN.png");
    helpBGTopTxtSprite->setPosition(ccp(bgSize.width / 2, bgSize.height /2));
    helpBGSprite->addChild(helpBGTopTxtSprite,5);
    helpBGTopTxtSprite->setVisible(false);
    
    helpBGMidTxtSprite = CCSprite::createWithSpriteFrameName("howtoplay_7_CN.png");
    helpBGMidTxtSprite->setPosition(ccp(bgSize.width / 2, 0));
    helpBGSprite->addChild(helpBGMidTxtSprite,5);
    helpBGMidTxtSprite->setVisible(false);
    
    helpBGBottomTxtSprite = CCSprite::createWithSpriteFrameName("howtoplay_8_CN.png");
    helpBGBottomTxtSprite->setPosition(ccp(bgSize.width / 2, 0));
    helpBGSprite->addChild(helpBGBottomTxtSprite,5);
    helpBGBottomTxtSprite->setVisible(false);
    
    jumpBGSprite = CCSprite::createWithSpriteFrameName("howtoplay_5.png");
    CCSize jumpBgSize = jumpBGSprite->getContentSize();
    
    jumpBGSprite->setPosition(ccp((bgSize.width * 78) /100, (bgSize.height * 5 / 100)));
    helpBGSprite->addChild(jumpBGSprite,-1);

    CCMenuItemImage* menuItem = CCMenuItemImage::create("howtoplay_5_CN.png", "howtoplay_5_CN.png", this, menu_selector(HelpPlayGame::jumpMenuCallBack));
    menuItem->setPosition(ccp(jumpBgSize.width / 2, jumpBgSize.height / 2));
    CCMenu* menu = CCMenu::create(menuItem,NULL);
    menu->setPosition(CCPointZero);
    jumpBGSprite->addChild(menu);
    
    //this->setTouchEnabled(true);
    return true;
}

//void HelpPlayGame::onEnter()
//{
//    CCLayer::onEnter();
//}
//
//void HelpPlayGame::onExit()
//{
//    CCLayer::onExit();
//}

HelpPlayGame* HelpPlayGame::create(CCObject* target, SEL_CallFunc func,CCPoint padPos)
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    HelpPlayGame* help = new HelpPlayGame();
    
    if (help && help->init(target,func,padPos)) {
        help->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(help);
    }
    help->setContentSize(size);
    return help;
}

void HelpPlayGame::setPadDictorPos(cocos2d::CCPoint pos)
{
    CCAssert(!(selPadSprite == NULL), "cannot be NULL");
    CCAssert(!(handSprite == NULL), "cannot be NULL");
    
    selPadSprite->setPosition(pos);
    handSprite->setPosition(pos);
}

HELP_PLAYGAME_STATE_TYPE HelpPlayGame::getHelpStateType()
{
    
    return helpStateType;
}

void HelpPlayGame::setHelpStateType(HELP_PLAYGAME_STATE_TYPE type)
{
    helpStateType = type;
}

void HelpPlayGame::restartHelpNow()
{
    helpStateType = HELP_PLAYGAME_STATE_TYPE_SELL_TOWER;
    this->updateShowHelpPlayState();
}

void HelpPlayGame::updateShowHelpPlayState()
{
    CCSpriteFrame* frame = NULL;
    CCSize helpBgSize = helpBGSprite->getContentSize();
    
//    helpStateType = (HELP_PLAYGAME_STATE_TYPE)(helpStateType + 1);

    switch (helpStateType) {
        case HELP_PLAYGAME_STATE_TYPE_START:
            {
                //CCNode* node = (CCNode*)pointArray->objectAtIndex(0);
                
                selPadSprite->setVisible(true);
                handSprite->setVisible(true);
                
//                selPadSprite->setPosition(node->getPosition());
//                handSprite->setPosition(node->getPosition());
                
                helpBGTopTxtSprite->setVisible(false);
                helpBGMidTxtSprite->setVisible(false);
                helpBGBottomTxtSprite->setVisible(false);
                
                helpPicSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("howtoplay_3.png"));
                helpPicTextSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("howtoplay_3_CN.png"));
                
            }
            break;
        case HELP_PLAYGAME_STATE_TYPE_PRE_SEL:
            {
                
                selPadSprite->setVisible(true);
                handSprite->setVisible(true);
                
//                selPadSprite->setPosition(node->getPosition());
//                handSprite->setPosition(node->getPosition());
            }
            break;
        case HELP_PLAYGAME_STATE_TYPE_SELECT_TOWER:
            {
                helpPicSprite->setVisible(false);
                helpPicTextSprite->setVisible(false);
                helpBGMidTxtSprite->setVisible(false);
                helpBGBottomTxtSprite->setVisible(false);
                handSprite->setVisible(false);
                
                helpBGTopTxtSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("howtoplay_6_CN.png"));
                helpBGTopTxtSprite->setScale(4);
                helpBGTopTxtSprite->setVisible(true);
                CCScaleTo* scale = CCScaleTo::create(0.25, 1);
                helpBGTopTxtSprite->runAction(CCSequence::create(scale,CCCallFunc::create(this, callfunc_selector(HelpPlayGame::helpBGShowTopMidBottomTxtCallBack)),NULL));
                
                
                
                
                
            }
            break;
        case HELP_PLAYGAME_STATE_TYPE_PRE_UPDATE:
            {
                
                selPadSprite->setVisible(true);
                handSprite->setVisible(true);
                
//                selPadSprite->setPosition(node->getPosition());
//                handSprite->setPosition(node->getPosition());
            }
            break;
        case HELP_PLAYGAME_STATE_TYPE_UPDATE_TOWER:
            {
                helpPicSprite->setVisible(false);
                helpPicTextSprite->setVisible(false);
                helpBGMidTxtSprite->setVisible(false);
                helpBGBottomTxtSprite->setVisible(false);
                handSprite->setVisible(false);
                selPadSprite->setVisible(false);
                
                helpBGTopTxtSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("howtoplay_9_CN.png"));
                helpBGTopTxtSprite->setScale(4);
                helpBGTopTxtSprite->setVisible(true);
                CCScaleTo* scale = CCScaleTo::create(0.25, 1);
                helpBGTopTxtSprite->runAction(CCSequence::create(scale,CCCallFunc::create(this, callfunc_selector(HelpPlayGame::helpBGShowTopMidBottomTxtCallBack)),NULL));
                
            }
            break;
        case HELP_PLAYGAME_STATE_TYPE_SELL_TOWER:
            {
                helpBGTopTxtSprite->setVisible(false);
                helpBGMidTxtSprite->setVisible(false);
                helpBGBottomTxtSprite->setVisible(false);
                
                
                selPadSprite->setVisible(true);
                handSprite->setVisible(true);
                
//                selPadSprite->setPosition(node->getPosition());
//                handSprite->setPosition(node->getPosition());
                
                helpPicSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("howtoplay_3.png"));
                helpPicTextSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("howtoplay_3_CN.png"));
                helpStateType = HELP_PLAYGAME_STATE_TYPE_START;//表示又从头开始
            }
            break;
        default:
            break;
    }
}

void HelpPlayGame::helpBGActionCallBack()
{
    CCSize bgSize = helpBGSprite->getContentSize();
    
    
    
    CCMoveTo* mto = CCMoveTo::create(0.5, ccp(bgSize.width * 78/100, -bgSize.height * 6 /100 ));
    jumpBGSprite->runAction(mto);
//    jumpBGSprite->runAction(CCSequence::create(mby,CCCallFunc::create(this, callfunc_selector(HelpPlayGame::jumpBGActionCallBack))));
    
}

void HelpPlayGame::jumpBGActionCallBack()
{
    CCSize jumpBgSize = jumpBGSprite->getContentSize();
    
//    CCMenuItemImage* menuItem = CCMenuItemImage::create("howtoplay_5_CN.png", "howtoplay_5_CN.png", this, menu_selector(HelpPlayGame::jumpMenuCallBack));
//    menuItem->setPosition(ccp(jumpBgSize.width / 2, jumpBgSize.height / 2));
//    CCMenu* menu = CCMenu::create(menuItem,NULL);
//    menu->setPosition(CCPointZero);
//    jumpBGSprite->addChild(menu);
}

void HelpPlayGame::jumpMenuCallBack(CCObject *object)
{
    helpStateType = HELP_PLAYGAME_STATE_TYPE_HELP_OVER;
    (myTarget->*mySelector)();
    this->removeFromParentAndCleanup(true);
}

void HelpPlayGame::helpBGShowTopMidBottomTxtCallBack()
{
    CCSize helpBgSize = helpBGSprite->getContentSize();
    
    showTopMidBottomTxtIndex++;
    
    if (showTopMidBottomTxtIndex == 1) {
        if (helpStateType == HELP_PLAYGAME_STATE_TYPE_SELECT_TOWER){
            helpBGMidTxtSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("howtoplay_7_CN.png"));
        }
        else if (helpStateType == HELP_PLAYGAME_STATE_TYPE_UPDATE_TOWER)
        {
            helpBGMidTxtSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("howtoplay_10_CN.png"));
        }
        
        helpBGMidTxtSprite->setPosition(ccp(helpBgSize.width / 2, 0));
        helpBGMidTxtSprite->setVisible(true);
        CCMoveBy* mvb1 = CCMoveBy::create(0.35, ccp(0, helpBgSize.height * 32 / 100));
        helpBGMidTxtSprite->runAction(CCSequence::create(mvb1,CCCallFunc::create(this, callfunc_selector(HelpPlayGame::helpBGShowTopMidBottomTxtCallBack)),NULL));

    }
    else if (showTopMidBottomTxtIndex == 2)
    {
        if (helpStateType == HELP_PLAYGAME_STATE_TYPE_SELECT_TOWER){
            helpBGBottomTxtSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("howtoplay_8_CN.png"));
        }
        else if (helpStateType == HELP_PLAYGAME_STATE_TYPE_UPDATE_TOWER)
        {
            helpBGBottomTxtSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("howtoplay_11_CN.png"));
        }

        helpBGBottomTxtSprite->setPosition(ccp(helpBgSize.width / 2, 0));
        helpBGBottomTxtSprite->setVisible(true);
        CCMoveBy* mvb2 = CCMoveBy::create(0.35, ccp(0, helpBgSize.height * 16 / 100));
        CCMoveBy* wait = CCMoveBy::create(1, ccp(0, 0));
        helpBGBottomTxtSprite->runAction(CCSequence::create(mvb2,wait,CCCallFunc::create(this, callfunc_selector(HelpPlayGame::helpBGShowTopMidBottomTxtCallBack)),NULL));
    }
    else if (showTopMidBottomTxtIndex == 3)
    {
        showTopMidBottomTxtIndex = 0;
        
        if (helpStateType == HELP_PLAYGAME_STATE_TYPE_SELECT_TOWER) {
            
            helpBGTopTxtSprite->setVisible(false);
            helpBGMidTxtSprite->setVisible(false);
            helpBGBottomTxtSprite->setVisible(false);
            helpPicSprite->setVisible(true);
            helpPicTextSprite->setVisible(true);
            
            selPadSprite->setVisible(true);
            handSprite->setVisible(true);
            
//            selPadSprite->setPosition(node->getPosition());
//            handSprite->setPosition(node->getPosition());
            
            helpPicSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("howtoplay_4.png"));
            helpPicTextSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("howtoplay_4_CN.png"));
        }
        else if (helpStateType == HELP_PLAYGAME_STATE_TYPE_UPDATE_TOWER)
        {
            helpPicSprite->setVisible(false);
            helpPicTextSprite->setVisible(false);
//            CCMoveBy* mby = CCMoveBy::create(3, ccp(0, 0));
//            helpPicSprite->runAction(CCSequence::create(mby,CCCallFunc::create(this, callfunc_selector(HelpPlayGame::jumpMenuCallBack))));
            this->jumpMenuCallBack(NULL);
        }
    }
    
}

void HelpPlayGame::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0,false);
}

void HelpPlayGame::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

bool HelpPlayGame::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void HelpPlayGame::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void HelpPlayGame::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSize padSize = selPadSprite->getContentSize();
    CCRect padRect = CCRect(padDictorPos.x - padSize.width / 2, padDictorPos.y - padSize.height / 2, padSize.width, padSize.height);
    
    CCPoint userPos = this->convertToNodeSpace(pTouch->getLocation());
    
    if (padRect.containsPoint(userPos)) {
        HELP_PLAYGAME_STATE_TYPE type = (HELP_PLAYGAME_STATE_TYPE)(helpStateType + 1);
        
        if (type < HELP_PLAYGAME_STATE_TYPE_UPDATE_TOWER) {
            helpStateType = type;
            (myTarget->*mySelector)();
        }
    }
}

