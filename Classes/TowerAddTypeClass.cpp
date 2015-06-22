//
//  TowerAddTypeClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-8-15.
//
//

#include "TowerAddTypeClass.h"
#include "HUDClass.h"
#include "GameParam.h"
#include "LcdAdapClass.h"
#include "Util.h"

//精灵图片参考的默认LCD宽度大小{
#define PIC_MAINLCD_WIDTH   (624)
#define PIC_MAINLCD_HEIGHT  (416)
//}

#define TOWER_WIDTH (50)
#define TOWER_HEIGHT    (52)
#define PAD_ROW_MAX_NUM  (4)
#define PAD_CUL_MAX_NUM  (4)
#define PAD_DELTA_SPACE_X  (2)
#define PAD_DELTA_SPACE_Y  (2)


static int addTowerMoneyBuffer[GAME_TOWER_TYPE_MAX] = {0};

TowerAddTypeClass::TowerAddTypeClass()
{

}

TowerAddTypeClass::~TowerAddTypeClass()
{

}

bool TowerAddTypeClass::init(CCObject *target, SEL_CallFunc selector)
{
    CCAssert(!(target == NULL), "target cannot be NULL");
    CCAssert(!(selector == NULL), "selector cannot be NULL");

    isShowAddTowerType = false;
    isHideAddTowerType = false;
    validTowerType = 0;
	addTowerMoneyValue = 0;
    addTowerType = GAME_TOWER_TYPE_NONE;
    myTarget = target;
    mySelector = selector;
    anchor = NULL;
    arrow = NULL;
    ball = NULL;
    bluestar = NULL;
    bottle = NULL;
    buff = NULL;
    cuttle = NULL;
    fan = NULL;
    firebottle = NULL;
    fish = NULL;
    mushroom = NULL;
    pin = NULL;
    plane = NULL;
    rocket = NULL;
    shit = NULL;
    snow = NULL;
    star = NULL;
    sun = NULL;
    selBG = NULL;

	memset(addTowerMoneyBuffer,0,sizeof(addTowerMoneyBuffer));
    return true;
}

TowerAddTypeClass* TowerAddTypeClass::create(cocos2d::CCObject *target, SEL_CallFunc selector)
{
    CCAssert(!(target == NULL), "target cannot be NULL");
    CCAssert(!(selector == NULL), "selector cannot be NULL");

    TowerAddTypeClass* addTower = new TowerAddTypeClass();
    if (addTower && addTower->init(target, selector)) {
        addTower->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(addTower);
    }
    addTower->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
    addTower->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());
    return addTower;
}

void TowerAddTypeClass::setValidTowerType(int type)
{
    validTowerType = type;
}

void TowerAddTypeClass::showAddTowerType()
{
    if (!isShowAddTowerType)
    {
        bool isAddFlg = false;
        int towerNum = 0;
        int tmpValidTowerNum = validTowerType;
        int tmpValidValue = 1;
        int index = 0;
        int colIndex = 0;
        float xPos = 0;
        float yPos = 0;
        float x0 = 0;
        float y0 = 0;
        int rowNum = 0;
        int colNum = 0;
        char pBuffer[100] = {0};
        float xScale = LcdAdapClass::sharedLCDADAP()->getXScale();
        float yScale = LcdAdapClass::sharedLCDADAP()->getYScale();
        CCSize bgSize = LcdAdapClass::sharedLCDADAP()->getWinSize();
        CCSize addPadSize = CCSize(0, 0);
        CCPoint curPos = this->getPosition();
        CCArray* itemArray = CCArray::create();
        
        for (int i = 0; i < 32; i++) {
            tmpValidTowerNum = tmpValidTowerNum >> 1;
            if (tmpValidTowerNum & tmpValidValue) {
                towerNum++;
            }
        }
        if (towerNum == 0) {
            return;
        }
        
        rowNum = (towerNum - 1)/ PAD_CUL_MAX_NUM + 1;
        colNum = (towerNum >= PAD_ROW_MAX_NUM)?PAD_CUL_MAX_NUM:((towerNum - 1)% PAD_ROW_MAX_NUM + 1);
        
        if (towerNum > 3) {
            x0 = -(3* TOWER_WIDTH / 2 + PAD_DELTA_SPACE_X * 3 / 2);
            addPadSize.width = (TOWER_WIDTH * 2 + PAD_DELTA_SPACE_X * 3/2.0) * 2;
        }
        else if (towerNum > 2)
        {
            x0 = -(TOWER_WIDTH + PAD_DELTA_SPACE_X);
            addPadSize.width = (TOWER_WIDTH * 3/2.0 + PAD_DELTA_SPACE_X) * 2;
        }
        else if (towerNum > 1)
        {
            x0 = -(TOWER_WIDTH / 2 + PAD_DELTA_SPACE_X / 2);
            addPadSize.width = (TOWER_WIDTH + PAD_DELTA_SPACE_X/2.0) * 2;
        }
        else if (towerNum == 1)
        {
            x0 = 0;
            addPadSize.width = (TOWER_WIDTH/2.0) * 2;
        }
        
        
        
        
        if (ccpLength(ccpSub(curPos, ccp(bgSize.width,curPos.y))) < ((addPadSize.width / 2.0) * LcdAdapClass::sharedLCDADAP()->getXScale())) {
            x0 = -((PAD_DELTA_SPACE_X + TOWER_WIDTH) * (colNum - 1));
        }
        else if(ccpLength(ccpSub(curPos, ccp(0,curPos.y))) < ((addPadSize.width / 2.0) * LcdAdapClass::sharedLCDADAP()->getXScale()))
        {
            x0 = 0;
        }
        
//        if (ccpLength(ccpSub(curPos, ccp(curPos.x,bgSize.height))) > ((PAD_DELTA_SPACE_Y + TOWER_HEIGHT) * (rowNum)))
        if (ccpLength(ccpSub(curPos, ccp(curPos.x,bgSize.height))) > (((PAD_DELTA_SPACE_Y + TOWER_HEIGHT) * (rowNum + 1)) * LcdAdapClass::sharedLCDADAP()->getYScale())) {
            y0 = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * rowNum;
            colIndex = rowNum;
            isAddFlg = true;
        }
        else
        {
            y0 = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * 1;
            isAddFlg = false;
            colIndex = 1;
        }
        
        xPos = x0;
        yPos = y0;
        if ((validTowerType & GAME_ADD_TOWER_TYPE_BOTTLE) == GAME_ADD_TOWER_TYPE_BOTTLE) {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TBottle");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_BOTTLE] = GAME_TOWER_TYPE_BOTTLE_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_BOTTLE_BUY_MONEY) {
                bottle = CCMenuItemImage::create("Bottle01.png", "Bottle01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                bottle = CCMenuItemImage::create("Bottle00.png", "Bottle00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				bottle->setEnabled(false);
            }
            bottle->setPosition(ccp(xPos,yPos));
            bottle->setTag(GAME_ADD_TOWER_TYPE_BOTTLE);
//            bottle->setScaleX(xScale);
//            bottle->setScaleY(yScale);
            itemArray->addObject(bottle);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
            
        }
        if ((validTowerType & GAME_ADD_TOWER_TYPE_ANCHOR) == GAME_ADD_TOWER_TYPE_ANCHOR)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TAnchor");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_ANCHOR] = GAME_TOWER_TYPE_ANCHOR_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_ANCHOR_BUY_MONEY) {
                anchor = CCMenuItemImage::create("Anchor01.png", "Anchor01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                anchor = CCMenuItemImage::create("Anchor00.png", "Anchor00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				anchor->setEnabled(false);
            }
            anchor->setPosition(ccp(xPos,yPos));
            anchor->setTag(GAME_ADD_TOWER_TYPE_ANCHOR);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(anchor);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        if ((validTowerType & GAME_ADD_TOWER_TYPE_ARROW) == GAME_ADD_TOWER_TYPE_ARROW)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TArrow");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_ARROW] = GAME_TOWER_TYPE_ARROW_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_ARROW_BUY_MONEY) {
                arrow = CCMenuItemImage::create("Arrow01.png", "Arrow01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                arrow = CCMenuItemImage::create("Arrow00.png", "Arrow00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				arrow->setEnabled(false);
            }
            arrow->setPosition(ccp(xPos,yPos));
            arrow->setTag(GAME_ADD_TOWER_TYPE_ARROW);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(arrow);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        
        if ((validTowerType & GAME_ADD_TOWER_TYPE_BALL) == GAME_ADD_TOWER_TYPE_BALL)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TBall");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_BALL] = GAME_TOWER_TYPE_ANCHOR_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_ANCHOR_BUY_MONEY) {
                ball = CCMenuItemImage::create("Ball01.png", "Ball01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                ball = CCMenuItemImage::create("Ball00.png", "Ball00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				ball->setEnabled(false);
            }
            ball->setPosition(ccp(xPos,yPos));
            ball->setTag(GAME_ADD_TOWER_TYPE_BALL);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(ball);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        
        if ((validTowerType & GAME_ADD_TOWER_TYPE_BLUESTAR) == GAME_ADD_TOWER_TYPE_BLUESTAR)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TBlueStar");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_BLUESTAR] = GAME_TOWER_TYPE_BLUESTAR_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_BLUESTAR_BUY_MONEY) {
                bluestar = CCMenuItemImage::create("BStar01.png", "BStar01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                bluestar = CCMenuItemImage::create("BStar00.png", "BStar00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				bluestar->setEnabled(false);
            }
            bluestar->setPosition(ccp(xPos,yPos));
            bluestar->setTag(GAME_ADD_TOWER_TYPE_BLUESTAR);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(bluestar);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        if ((validTowerType & GAME_ADD_TOWER_TYPE_BUFF) == GAME_ADD_TOWER_TYPE_BUFF)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TBuff");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_BUFF] = GAME_TOWER_TYPE_BUFF_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_BUFF_BUY_MONEY) {
                buff = CCMenuItemImage::create("Buff01.png", "Buff01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                buff = CCMenuItemImage::create("Buff00.png", "Buff00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				buff->setEnabled(false);
            }
            buff->setPosition(ccp(xPos,yPos));
            buff->setTag(GAME_ADD_TOWER_TYPE_BUFF);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(buff);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        if ((validTowerType & GAME_ADD_TOWER_TYPE_CUTTLE) == GAME_ADD_TOWER_TYPE_CUTTLE)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TCuttle");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_CUTTLE] = GAME_TOWER_TYPE_CUTTLE_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_CUTTLE_BUY_MONEY) {
                cuttle = CCMenuItemImage::create("Cuttle01.png", "Cuttle01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                cuttle = CCMenuItemImage::create("Cuttle00.png", "Cuttle00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				cuttle->setEnabled(false);
            }
            cuttle->setPosition(ccp(xPos,yPos));
            cuttle->setTag(GAME_ADD_TOWER_TYPE_CUTTLE);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(cuttle);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        if ((validTowerType & GAME_ADD_TOWER_TYPE_FAN) == GAME_ADD_TOWER_TYPE_FAN)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TFan");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_FAN] = GAME_TOWER_TYPE_FAN_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_FAN_BUY_MONEY) {
                fan = CCMenuItemImage::create("Fan01.png", "Fan01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                fan = CCMenuItemImage::create("Fan00.png", "Fan00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				fan->setEnabled(false);
            }
            fan->setPosition(ccp(xPos,yPos));
            fan->setTag(GAME_ADD_TOWER_TYPE_FAN);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(fan);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        if ((validTowerType & GAME_ADD_TOWER_TYPE_FIREBOTTLE) == GAME_ADD_TOWER_TYPE_FIREBOTTLE)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TFireBottle");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_FIREBOTTLE] = GAME_TOWER_TYPE_FIREBOTTLE_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_FIREBOTTLE_BUY_MONEY) {
                firebottle = CCMenuItemImage::create("FBottle01.png", "FBottle01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                firebottle = CCMenuItemImage::create("FBottle00.png", "FBottle00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				firebottle->setEnabled(false);
            }
            firebottle->setPosition(ccp(xPos,yPos));
            firebottle->setTag(GAME_ADD_TOWER_TYPE_FIREBOTTLE);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(firebottle);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        if ((validTowerType & GAME_ADD_TOWER_TYPE_FISH) == GAME_ADD_TOWER_TYPE_FISH)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TFish");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_FISH] = GAME_TOWER_TYPE_FISH_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_FISH_BUY_MONEY) {
                fish = CCMenuItemImage::create("Fish01.png", "Fish01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                fish = CCMenuItemImage::create("Fish00.png", "Fish00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				fish->setEnabled(false);
            }
            fish->setPosition(ccp(xPos,yPos));
            fish->setTag(GAME_ADD_TOWER_TYPE_FISH);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(fish);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        if ((validTowerType & GAME_ADD_TOWER_TYPE_MUSHROOM) == GAME_ADD_TOWER_TYPE_MUSHROOM)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TMushroom");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_MUSHROOM] = GAME_TOWER_TYPE_MUSHROOM_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_MUSHROOM_BUY_MONEY) {
                mushroom = CCMenuItemImage::create("Mushroom01.png", "Mushroom01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                mushroom = CCMenuItemImage::create("Mushroom00.png", "Mushroom00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				mushroom->setEnabled(false);
            }
            mushroom->setPosition(ccp(xPos,yPos));
            mushroom->setTag(GAME_ADD_TOWER_TYPE_MUSHROOM);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(mushroom);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        if ((validTowerType & GAME_ADD_TOWER_TYPE_PIN) == GAME_ADD_TOWER_TYPE_PIN)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TPin");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_PIN] = GAME_TOWER_TYPE_PIN_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_PIN_BUY_MONEY) {
                pin = CCMenuItemImage::create("Pin01.png", "Pin01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                pin = CCMenuItemImage::create("Pin00.png", "Pin00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				pin->setEnabled(false);
            }
            pin->setPosition(ccp(xPos,yPos));
            pin->setTag(GAME_ADD_TOWER_TYPE_PIN);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(pin);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        
        if ((validTowerType & GAME_ADD_TOWER_TYPE_PLANE) == GAME_ADD_TOWER_TYPE_PLANE)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TPlane");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_PLANE] = GAME_TOWER_TYPE_PLANE_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_PLANE_BUY_MONEY) {
                plane = CCMenuItemImage::create("Plane01.png", "Plane01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                plane = CCMenuItemImage::create("Plane00.png", "Plane00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				plane->setEnabled(false);
            }
            plane->setPosition(ccp(xPos,yPos));
            plane->setTag(GAME_ADD_TOWER_TYPE_PLANE);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(plane);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        
        if ((validTowerType & GAME_ADD_TOWER_TYPE_ROCKET) == GAME_ADD_TOWER_TYPE_ROCKET)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TRocket");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_ROCKET] = GAME_TOWER_TYPE_ROCKET_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_ROCKET_BUY_MONEY) {
                rocket = CCMenuItemImage::create("Rocket01.png", "Rocket01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                rocket = CCMenuItemImage::create("Rocket00.png", "Rocket00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				rocket->setEnabled(false);
            }
            rocket->setPosition(ccp(xPos,yPos));
            rocket->setTag(GAME_ADD_TOWER_TYPE_ROCKET);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(rocket);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        if ((validTowerType & GAME_ADD_TOWER_TYPE_SHIT) == GAME_ADD_TOWER_TYPE_SHIT)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TShit");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_SHIT] = GAME_TOWER_TYPE_SHIT_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_SHIT_BUY_MONEY) {
                shit = CCMenuItemImage::create("Shit01.png", "Shit01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                shit = CCMenuItemImage::create("Shit00.png", "Shit00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				shit->setEnabled(false);
            }
            shit->setPosition(ccp(xPos,yPos));
            shit->setTag(GAME_ADD_TOWER_TYPE_SHIT);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(shit);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        if ((validTowerType & GAME_ADD_TOWER_TYPE_SNOW) == GAME_ADD_TOWER_TYPE_SNOW)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TSnow");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_SNOW] = GAME_TOWER_TYPE_SNOW_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_SNOW_BUY_MONEY) {
                snow = CCMenuItemImage::create("Snow01.png", "Snow01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                snow = CCMenuItemImage::create("Snow00.png", "Snow00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				snow->setEnabled(false);
            }
            snow->setPosition(ccp(xPos,yPos));
            snow->setTag(GAME_ADD_TOWER_TYPE_SNOW);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(snow);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        if ((validTowerType & GAME_ADD_TOWER_TYPE_STAR) == GAME_ADD_TOWER_TYPE_STAR)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TStar");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_STAR] = GAME_TOWER_TYPE_STAR_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_STAR_BUY_MONEY) {
                star = CCMenuItemImage::create("Star01.png", "Star01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                star = CCMenuItemImage::create("Star00.png", "Star00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				star->setEnabled(false);
            }
            star->setPosition(ccp(xPos,yPos));
            star->setTag(GAME_ADD_TOWER_TYPE_STAR);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(star);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH + PAD_DELTA_SPACE_X);
            }
        }
        if ((validTowerType & GAME_ADD_TOWER_TYPE_SUN) == GAME_ADD_TOWER_TYPE_SUN)
        {
//            memset(pBuffer, 0, sizeof(pBuffer));
//            sprintf(pBuffer, SPRITE_HD_NAME,"Themes/Towers/TSun");
//            strcat(pBuffer, ".plist");
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pBuffer);
            //check user money is enough to buy tower
            int userMoney = HUDClass::sharedHUD()->getHUDMoney();

			addTowerMoneyBuffer[GAME_TOWER_TYPE_SUN] = GAME_TOWER_TYPE_SUN_BUY_MONEY;
            if (userMoney > GAME_TOWER_TYPE_SUN_BUY_MONEY) {
                sun = CCMenuItemImage::create("Sun01.png", "Sun01.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
            }
            else
            {
                sun = CCMenuItemImage::create("Sun00.png", "Sun00.png",this, menu_selector(TowerAddTypeClass::towerAddMenuCallBack));
				sun->setEnabled(false);
            }
            sun->setPosition(ccp(xPos,yPos));
            sun->setTag(GAME_ADD_TOWER_TYPE_SUN);
            //        bottle->setScaleX(xScale);
            //        bottle->setScaleY(yScale);
            itemArray->addObject(sun);
            index++;
            if (index >= colNum && rowNum > 0) {
                xPos = x0;
                
                index = 0;
                if (isAddFlg) {
                    colIndex -= 1;
                    yPos = (TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
                else
                {
                    colIndex += 1;
                    yPos = -(TOWER_HEIGHT + PAD_DELTA_SPACE_Y) * colIndex;
                }
            }
            else
            {
                xPos += (TOWER_WIDTH+ PAD_DELTA_SPACE_X);
            }
        }
        
        CCMenu* Menu = CCMenu::createWithArray(itemArray);
        Menu->setPosition(CCPointZero);
//        float xScale = LcdAdapClass::sharedLCDADAP()->getXScale();
//        float yScale = LcdAdapClass::sharedLCDADAP()->getYScale();
//        Menu->setScaleX(xScale);
//        Menu->setScaleY(yScale);
        this->addChild(Menu,88);
        
        selBG = CCSprite::createWithSpriteFrameName("select_01.png");
        selBG->setPosition(ccp(0,0));
//        LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(selBG, ccp(0,0));
        CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName("selAnim");
        CCSize selSize = selBG->getContentSize();
        selBG->runAction(CCRepeatForever::create((CCSequence*)(CCSequence::create(CCAnimate::create(animation),NULL))));
        this->addChild(selBG,88);
        
//        this->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
//        this->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());
    }
    isShowAddTowerType = true;
    isHideAddTowerType = false;
}

void TowerAddTypeClass::hideAddTowerType()
{
//    if (!isHideAddTowerType) {
        {
            if (selBG) {
                selBG->stopAllActions();
                selBG->removeFromParentAndCleanup(true);
                selBG = NULL;
            }
            if (anchor) {
                anchor->removeFromParentAndCleanup(true);
                anchor = NULL;
            }
            if (arrow) {
                arrow->removeFromParentAndCleanup(true);
                arrow = NULL;
            }
            if (ball) {
                ball->removeFromParentAndCleanup(true);
                ball = NULL;
            }
            if (bluestar) {
                bluestar->removeFromParentAndCleanup(true);
                bluestar = NULL;
            }
            if (bottle) {
                bottle->removeFromParentAndCleanup(true);
                bottle = NULL;
            }
            if (buff) {
                buff->removeFromParentAndCleanup(true);
                buff = NULL;
            }
            if (cuttle) {
                cuttle->removeFromParentAndCleanup(true);
                cuttle = NULL;
            }
            if (fan) {
                fan->removeFromParentAndCleanup(true);
                fan = NULL;
            }
            if (firebottle) {
                firebottle->removeFromParentAndCleanup(true);
                firebottle = NULL;
            }
            if (fish) {
                fish->removeFromParentAndCleanup(true);
                fish = NULL;
            }
            if (mushroom) {
                mushroom->removeFromParentAndCleanup(true);
                mushroom = NULL;
            }
            
            if (pin) {
                pin->removeFromParentAndCleanup(true);
                pin = NULL;
            }
            if (plane) {
                plane->removeFromParentAndCleanup(true);
                plane = NULL;
            }
            if (rocket) {
                rocket->removeFromParentAndCleanup(true);
                rocket = NULL;
            }
            if (shit) {
                shit->removeFromParentAndCleanup(true);
                shit = NULL;
            }
            if (snow) {
                snow->removeFromParentAndCleanup(true);
                snow = NULL;
            }
            if (star) {
                star->removeFromParentAndCleanup(true);
                star = NULL;
            }
            if (sun) {
                sun->removeFromParentAndCleanup(true);
                sun = NULL;
            }
        }
        isHideAddTowerType = true;
        isShowAddTowerType = false;
//    }
}

void TowerAddTypeClass::updateAddTowerShowState()
{
	int hudMoney = HUDClass::sharedHUD()->getHUDMoney();
	int towerMoney = 0;
    CCSpriteFrame* frame = NULL;
    
    
	if (anchor) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_ANCHOR];
		if (hudMoney >= towerMoney )
		{
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Anchor01.png");
			
			anchor->setEnabled(true);
		}
		else
		{
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Anchor00.png");
			anchor->setEnabled(false);
		}
		anchor->setNormalSpriteFrame(frame);
	}
	if (arrow) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_ARROW];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Arrow01.png");
			arrow->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Arrow00.png");
			arrow->setEnabled(false);
		}
		arrow->setNormalSpriteFrame(frame);
	}
	if (ball) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_ANCHOR];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Ball01.png");
			ball->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Ball00.png");
			ball->setEnabled(false);
		}
		ball->setNormalSpriteFrame(frame);
	}
	if (bluestar) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_BLUESTAR];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BStar01.png");
			bluestar->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BStar00.png");
			bluestar->setEnabled(false);
		}
		bluestar->setNormalSpriteFrame(frame);
	}
	if (bottle) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_BOTTLE];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Bottle01.png");
			bottle->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Bottle00.png");
			bottle->setEnabled(false);
		}
		bottle->setNormalSpriteFrame(frame);
	}
	if (buff) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_BUFF];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Buff01.png");
			buff->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Buff00.png");
			buff->setEnabled(false);
		}
		buff->setNormalSpriteFrame(frame);
	}
	if (cuttle) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_CUTTLE];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Cuttle01.png");
			cuttle->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Cuttle00.png");
			cuttle->setEnabled(false);
		}
		cuttle->setNormalSpriteFrame(frame);
	}
	if (fan) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_FAN];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Fan01.png");
			fan->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Fan00.png");
			fan->setEnabled(false);
		}
		fan->setNormalSpriteFrame(frame);
	}
	if (firebottle) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_FIREBOTTLE];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("FBottle01.png");
			firebottle->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("FBottle00.png");
			firebottle->setEnabled(false);
		}
		firebottle->setNormalSpriteFrame(frame);
	}
	if (fish) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_FISH];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Fish01.png");
			fish->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Fish00.png");
			fish->setEnabled(false);
		}
		fish->setNormalSpriteFrame(frame);
	}
	if (mushroom) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_MUSHROOM];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Mushroom01.png");
			mushroom->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Mushroom00.png");
			mushroom->setEnabled(false);
		}
		mushroom->setNormalSpriteFrame(frame);
	}

	if (pin) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_PIN];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Pin01.png");
			pin->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Pin00.png");
			pin->setEnabled(false);
		}
		pin->setNormalSpriteFrame(frame);
	}
	if (plane) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_PLANE];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Plane01.png");
			plane->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Plane00.png");
			plane->setEnabled(false);
		}
		plane->setNormalSpriteFrame(frame);
	}
	if (rocket) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_ROCKET];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Rocket01.png");
			rocket->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Rocket00.png");
			rocket->setEnabled(false);
		}
		rocket->setNormalSpriteFrame(frame);
	}
	if (shit) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_SHIT];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Shit01.png");
			shit->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Shit00.png");
			shit->setEnabled(false);
		}
		shit->setNormalSpriteFrame(frame);
	}
	if (snow) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_SNOW];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Snow01.png");
			snow->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Snow00.png");
			snow->setEnabled(false);
		}
		snow->setNormalSpriteFrame(frame);
	}
	if (star) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_STAR];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Star01.png");
			star->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Star00.png");
			star->setEnabled(false);
		}
		star->setNormalSpriteFrame(frame);
	}
	if (sun) {
		towerMoney = addTowerMoneyBuffer[GAME_TOWER_TYPE_SUN];
		if (hudMoney >= towerMoney )
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sun01.png");
			sun->setEnabled(true);
		}
		else
		{
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sun00.png");
			sun->setEnabled(false);
		}
		sun->setNormalSpriteFrame(frame);
	}
}

void TowerAddTypeClass::setIsShowAddTowerType(bool flag)
{
    isShowAddTowerType = flag;
}
bool TowerAddTypeClass::getIsShowAddTowerType()
{
    return isShowAddTowerType;
}

void TowerAddTypeClass::setIsHideAddTowerType(bool flag)
{
    isHideAddTowerType = flag;
}

bool TowerAddTypeClass::getIsHideAddTowerType()
{
    return isHideAddTowerType;
}

void TowerAddTypeClass::setAddTowerType(GAME_TOWER_TYPE type)
{
    addTowerType = type;
}

GAME_TOWER_TYPE TowerAddTypeClass::getAddTowerType()
{
    return addTowerType;
}

void TowerAddTypeClass::towerAddMenuCallBack(cocos2d::CCObject *parent)
{
	if (parent) {
		Util::getInstance()->performWithDelay(0, [=](){
			CCMenuItem* menu = static_cast<CCMenuItem*>(parent);
			int hudMoney = HUDClass::sharedHUD()->getHUDMoney();

			switch (menu->getTag()) {
				case GAME_ADD_TOWER_TYPE_ANCHOR:
					addTowerType = GAME_TOWER_TYPE_ANCHOR;
					break;
				case GAME_ADD_TOWER_TYPE_ARROW:
					addTowerType = GAME_TOWER_TYPE_ARROW;
					break;
				case GAME_ADD_TOWER_TYPE_BALL:
					addTowerType = GAME_TOWER_TYPE_BALL;
					break;
				case GAME_ADD_TOWER_TYPE_BLUESTAR:
					addTowerType = GAME_TOWER_TYPE_BLUESTAR;
					break;
				case GAME_ADD_TOWER_TYPE_BOTTLE:
					addTowerType = GAME_TOWER_TYPE_BOTTLE;
					break;
				case GAME_ADD_TOWER_TYPE_BUFF:
					addTowerType = GAME_TOWER_TYPE_BUFF;
					break;
				case GAME_ADD_TOWER_TYPE_CUTTLE:
					addTowerType = GAME_TOWER_TYPE_CUTTLE;
					break;
				case GAME_ADD_TOWER_TYPE_FAN:
					addTowerType = GAME_TOWER_TYPE_FAN;
					break;
				case GAME_ADD_TOWER_TYPE_FIREBOTTLE:
					addTowerType = GAME_TOWER_TYPE_FIREBOTTLE;
					break;
				case GAME_ADD_TOWER_TYPE_FISH:
					addTowerType = GAME_TOWER_TYPE_FISH;
					break;
				case GAME_ADD_TOWER_TYPE_MUSHROOM:
					addTowerType = GAME_TOWER_TYPE_MUSHROOM;
					break;
				case GAME_ADD_TOWER_TYPE_PIN:
					addTowerType = GAME_TOWER_TYPE_PIN;
					break;
				case GAME_ADD_TOWER_TYPE_PLANE:
					addTowerType = GAME_TOWER_TYPE_PLANE;
					break;
				case GAME_ADD_TOWER_TYPE_ROCKET:
					addTowerType = GAME_TOWER_TYPE_ROCKET;
					break;
				case GAME_ADD_TOWER_TYPE_SHIT:
					addTowerType = GAME_TOWER_TYPE_SHIT;
					break;
				case GAME_ADD_TOWER_TYPE_SNOW:
					addTowerType = GAME_TOWER_TYPE_SNOW;
					break;
				case GAME_ADD_TOWER_TYPE_STAR:
					addTowerType = GAME_TOWER_TYPE_STAR;
					break;
				case GAME_ADD_TOWER_TYPE_SUN:
					addTowerType = GAME_TOWER_TYPE_SUN;
					break;
            
				default:
					break;
			}

			hudMoney -= addTowerMoneyBuffer[addTowerType];
			HUDClass::sharedHUD()->setHUDMoney(hudMoney);
			this->setIsHideAddTowerType(true);
		
			(myTarget->*mySelector)();
		});
    }
}
