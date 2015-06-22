//
//  GameShowSendWBClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-12-7.
//
//

#include "GameShowSendWBClass.h"
#include "LcdAdapClass.h"
#include "GameWBConClass.h"

#define MENU_ANDFRIEND_ID   (2)
#define MENU_FANS_ID     (5)
#define MENU_SEND_ID    (10)
#define MENU_CLOSE_ID   (15)
#define MENU_CHANGE_USER_ID (20)

static char comBuffer[255] = {0};

GameShowSendWBClass::GameShowSendWBClass()
{

}

GameShowSendWBClass::~GameShowSendWBClass()
{
    
}

bool GameShowSendWBClass::init()
{
    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
//    LcdAdapClass::sharedLCDADAP()->setAdaptorLayerSizeAndPos(this);
    
    CCSprite* topBGSprite = CCSprite::create("Themes/wbbg/share_topbg.png");
    CCSize topBGSize = topBGSprite->getContentSize();
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(topBGSprite, ccp(size.width/2, size.height * 3/4));
    this->addChild(topBGSprite,1);
    
    
    CCSprite* leaf = CCSprite::create("Themes/wbbg/share_leaf.png");
    leaf->setPosition(ccp(topBGSize.width/25, topBGSize.height * 84/100));
    topBGSprite->addChild(leaf,1);
    
    sendPicSprite = CCSprite::create("Themes/wbbg/share_picbg.png");
    sendPicSprite->setPosition(ccp(topBGSize.width * 12 /100, topBGSize.height /5));
    topBGSprite->addChild(sendPicSprite,1);
    
    CCSprite* dot1 = CCSprite::create("Themes/wbbg/share_sepdot.png");
    dot1->setPosition(ccp(topBGSize.width * 24/100, topBGSize.height/5));
    topBGSprite->addChild(dot1,1);
    
    CCMenuItemImage* atBtn = CCMenuItemImage::create("Themes/wbbg/share_at_normal.png", "Themes/wbbg/share_at_pressed.png", this, menu_selector(GameShowSendWBClass::wbBtnCallBack));
    atBtn->setTag(MENU_ANDFRIEND_ID);
    atBtn->setPosition(ccp(topBGSize.width * 3/10, topBGSize.height /5));
    //this->addChild(atBtn,1);
    
    fansMenu = CCMenuItemImage::create("Themes/wbbg/share_fan_active.png", "Themes/wbbg/share_fan_active.png", this, menu_selector(GameShowSendWBClass::wbBtnCallBack));
    fansMenu->setTag(MENU_FANS_ID);
    fansMenu->setPosition(ccp(topBGSize.width * 53/100, topBGSize.height /5));
    //this->addChild(fansMenu,1);
    
    CCSprite* numBG = CCSprite::create("Themes/wbbg/share_numbg.png");
    CCSize numBGSize = numBG->getContentSize();
    numBG->setPosition(ccp(topBGSize.width * 76/100, topBGSize.height/5));
    topBGSprite->addChild(numBG,1);
    
//    inputNumLab = CCLabelAtlas::create("0", "Themes/Pets/mystone_num.png", 13, 26, 46);
//    inputNumLab->setPosition(ccp(numBGSize.width /5, numBGSize.height * 45 /100));
//    numBG->addChild(inputNumLab,1);

    ccColor3B color;
    color.r = 255;
    color.b = 0;
    color.g = 0;
    
    
    inputNumLab = CCLabelTTF::create("76", "Georgia", 36);
    inputNumLab->setPosition(ccp(numBGSize.width /2, numBGSize.height/2));
    inputNumLab->setColor(color);
    numBG->addChild(inputNumLab,1);
    
    CCSprite* dot2 = CCSprite::create("Themes/wbbg/share_sepdot.png");
    dot2->setPosition(ccp(topBGSize.width * 85/100, topBGSize.height/5));
    topBGSprite->addChild(dot2,1);
    
    CCMenuItemImage* sendBtn = CCMenuItemImage::create("Themes/wbbg/share_btn_normal.png", "Themes/wbbg/share_btn_pressed.png", this, menu_selector(GameShowSendWBClass::wbBtnCallBack));
    sendBtn->setScaleX(0.5);
    sendBtn->setTag(MENU_SEND_ID);
    sendBtn->setPosition(ccp(topBGSize.width * 94/100, topBGSize.height /5));
    //this->addChild(sendBtn,1);
    
    CCMenuItemImage* closeBtn = CCMenuItemImage::create("Themes/wbbg/close_normal.png", "Themes/wbbg/close_pressed.png", this, menu_selector(GameShowSendWBClass::wbBtnCallBack));
    closeBtn->setTag(MENU_SEND_ID);
    closeBtn->setPosition(ccp(topBGSize.width * 95/100, topBGSize.height * 87 /100));
    //this->addChild(closeBtn,1);
    
//    int  diffy = (size.height/2)/128;//128是share_pattern.png高度
//    int mody = (((int)size.height)/2)%128;//判断是否有余数，若有余数则加+1
//    if (mody > 0) {
//        diffy += 1;
//    }
//    float diffx = (size.width)/128;//128是share_pattern.png宽度
//    int modx = (((int)size.width))%128;
//    if (modx > 0) {
//        diffx += 1;
//    }
    
    topBGSprite->getTexture()->setAliasTexParameters();
    
    CCSprite* bottomBG = CCSprite::create("Themes/wbbg/share_pattern.png", CCRect(0, 0, size.width, size.height/2));
    ccTexParams tp = {GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
    bottomBG->getTexture()->setTexParameters(&tp);
//    bottomBG->setPosition(ccp(size.width/2,size.height/4));
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(bottomBG, ccp(size.width/2,size.height/4));
    CCSize bottomBGSize =  bottomBG->getContentSize();
    this->addChild(bottomBG,11);
    bottomBG->getTexture()->setAliasTexParameters();
    
    CCLabelTTF* curText = CCLabelTTF::create("当前帐号", "Georgia", 24);
    curText->setPosition(ccp(bottomBGSize.width/2,bottomBGSize.height * 80/100));
    bottomBG->addChild(curText,1);
    
    CCSprite* septorSprite = CCSprite::create("Themes/wbbg/share_sepline.png");
    septorSprite->setPosition(ccp(bottomBGSize.width/2,bottomBGSize.height * 75/100));
    bottomBG->addChild(septorSprite,1);
    
    
    userNameLab = CCLabelTTF::create("风云不帅小子", "Georgia-BOLD", 36);
    userNameLab->setPosition(ccp(bottomBGSize.width/2, bottomBGSize.height * 56/100));
    bottomBG->addChild(userNameLab,1);
    
    CCMenuItemImage* changeBtn = CCMenuItemImage::create("Themes/wbbg/share_btn_normal.png", "Themes/wbbg/share_btn_pressed.png", this, menu_selector(GameShowSendWBClass::wbBtnCallBack));
    changeBtn->setTag(MENU_CHANGE_USER_ID);
    changeBtn->setPosition(ccp(bottomBGSize.width/2, bottomBGSize.height * 42 /100));
    
    CCSprite* logoSprite = CCSprite::create("Themes/wbbg/share_logo.png");
    logoSprite->setPosition(ccp(bottomBGSize.width/2, bottomBGSize.height * 16/100));
    bottomBG->addChild(logoSprite,1);
    
    
    CCMenu* menu = CCMenu::create(atBtn,fansMenu,sendBtn,closeBtn,NULL);
    menu->setPosition(CCPointZero);
    topBGSprite->addChild(menu,1);
    
    
    CCMenu* bmenu = CCMenu::create(changeBtn,NULL);
    bmenu->setPosition(CCPointZero);
    bottomBG->addChild(bmenu,11);
    
    GameWBConClass::sharedWBCON()->loginSinaWB();
    
    return true;
}

CCScene* GameShowSendWBClass::createScene()
{
    CCScene* scene = NULL;
    
    do {
        scene = CCScene::create();
        CC_BREAK_IF(!scene);
        
        GameShowSendWBClass* wbshow = GameShowSendWBClass::create();
        CC_BREAK_IF(!wbshow);
        
        scene->addChild(wbshow);
        
    } while (0);
    
    return scene;
}

void GameShowSendWBClass::wbBtnCallBack(cocos2d::CCObject *object)
{
    
}
