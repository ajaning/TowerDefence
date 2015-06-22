//
//  TowerSelPadClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-8-11.
//
//

#include "TowerSelPadClass.h"
#include "GameSpriteParm.h"
#include "GameParam.h"
#include "HUDClass.h"
#include "LcdAdapClass.h"
#include "Util.h"
#define UPMENU_TAG  (15)
#define SELLMENU_TAG (25)

static AttackTowerClass* userSelTower = NULL;

TowerSelPadClass::TowerSelPadClass()
{

}

TowerSelPadClass::~TowerSelPadClass()
{

}

bool TowerSelPadClass::init()
{
    isTowerShowPAD = false;
    isTowerHidePAD = false;
    isUserUpOrSellTower = false;
    upMenu = NULL;
    sellMenu = NULL;
    selSprite = NULL;
    killZoneSprite = NULL;
    selTowerUpdateType = GAME_TOWER_UPDATE_TYPE_ZERO;
    selTowerType = GAME_TOWER_TYPE_NONE;
    mySelector = NULL;
    myTarget = NULL;
    
    updatePayMoney = 0;
    return true;
}

bool TowerSelPadClass::init(cocos2d::CCObject *target, SEL_CallFunc func)
{

    this->init();
    
    myTarget = target;
    mySelector = func;
    
    this->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
    this->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());
    return true;
}


TowerSelPadClass* TowerSelPadClass::create(cocos2d::CCObject *target, SEL_CallFunc func)
{
    TowerSelPadClass* sel = new TowerSelPadClass();
    
    if (sel && sel->init(target, func)) {
        sel->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(sel);
    }
    
    return sel;
}

void TowerSelPadClass::showUpSelPad(AttackTowerClass *tower)
{
    if (tower) {
        {
            GAME_TOWER_TYPE towerType = tower->getTowerType();
            GAME_TOWER_UPDATE_TYPE towerUpdateType = tower->getTowerUpdateType();
            
            float towerKillRadius = tower->getTowerKillRadius();
            CCPoint centerPos = tower->getPosition();

            
            selTowerType = towerType;
            selTowerUpdateType = towerUpdateType;//(GAME_TOWER_UPDATE_TYPE)(towerUpdateType + 1);
            this->setPosition(centerPos);
            if (towerType != GAME_TOWER_TYPE_NONE && towerType != GAME_TOWER_TYPE_MAX) {
                //        char pBuffer[100] = {0};
                //        char pBuffer2[100] = {0};
                char upNameBuffer[100] = {0};
                char sellNameBuffer[100] = {0};
                char rangeNameBuffer[100] = {0};
                switch (towerType) {
                    case GAME_TOWER_TYPE_ANCHOR:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_ANCHOR_UPONE_320);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_ANCHOR_SELLONE_208);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_ANCHOR);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_ANCHOR_UPTWO_380);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_ANCHOR_SELLTWO_464);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_ANCHOR);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_ANCHOR_SELLTHR_768);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_ANCHOR);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_ARROW:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_ARROW_UPONE_260);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_ARROW_SELLONE_176);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_ARROW);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_ARROW_UPTWO_380);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_ARROW_SELLTWO_384);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_ARROW);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_ARROW_SELLTHR_688);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_ARROW);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_BALL:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_BALL_UPONE_320);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BALL_SELLONE_128);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_BALL);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_BALL_UPTWO_480);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BALL_SELLTWO_384);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_BALL);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BALL_SELLTHR_768);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_BALL);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_BLUESTAR:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_BLUESTAR_UPONE_260);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BLUESTAR_SELLONE_144);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_BLUESTAR);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_BLUESTAR_UPTWO_320);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BLUESTAR_SELLTWO_352);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_BLUESTAR);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BLUESTAR_SELLTHR_608);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_BLUESTAR);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_BOTTLE:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_BOTTLE_UPONE_180);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BOTTLE_SELLONE_80);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_BOTTLE);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_BOTTLE_UPTWO_260);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BOTTLE_SELLTWO_224);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_BOTTLE);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BOTTLE_SELLTHR_432);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_BOTTLE);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_BUFF:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_BUFF_UPONE_180);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BUFF_SELLONE_80);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_BUFF);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_BUFF_UPTWO_260);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BUFF_SELLTWO_224);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_BUFF);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BUFF_SELLTHR_432);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_BUFF);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_CUTTLE:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_CUTTLE_UPONE_260);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BOTTLE_SELLONE_80);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_CUTTLE);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_CUTTLE_UPTWO_320);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_CUTTLE_SELLTWO_384);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_CUTTLE);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BOTTLE_SELLTHR_432);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_CUTTLE);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_FAN:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_FAN_UPONE_220);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_FAN_SELLONE_128);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_FAN);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_FAN_UPTWO_260);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_FAN_SELLTWO_304);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_FAN);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_FAN_SELLTHR_512);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_FAN);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_FIREBOTTLE:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_FIREBOTTLE_UPONE_260);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_FIREBOTTLE_SELLONE_128);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_FIREBOTTLE);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_FIREBOTTLE_UPTWO_320);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_FIREBOTTLE_SELLTWO_336);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_FIREBOTTLE);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_FIREBOTTLE_SELLTHR_592);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_FIREBOTTLE);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_FISH:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_FISH_UPONE_260);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_FISH_SELLONE_144);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_FISH);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_FISH_UPTWO_320);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_FISH_SELLTWO_352);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_FISH);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_FISH_SELLTHR_608);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_FISH);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_MUSHROOM:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_MUSHROOM_UPONE_260);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_MUSHROOM_SELLONE_176);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_MUSHROOM);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_MUSHROOM_UPTWO_380);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_MUSHROOM_SELLTWO_384);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_MUSHROOM);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_MUSHROOM_SELLTHR_688);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_MUSHROOM);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_PIN:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_PIN_UPONE_260);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_PIN_SELLONE_128);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_PIN);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_PIN_UPTWO_320);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_PIN_SELLTWO_336);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_PIN);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_PIN_SELLTHR_592);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_PIN);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_PLANE:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_PLANE_UPONE_320);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_PLANE_SELLONE_176);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_PLANE);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_PLANE_UPTWO_380);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_PLANE_SELLTWO_432);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_PLANE);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_PLANE_SELLTHR_736);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_PLANE);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_ROCKET:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_ROCKET_UPONE_260);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_ROCKET_SELLONE_176);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_ROCKET);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_ROCKET_UPTWO_380);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_ROCKET_SELLTWO_384);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_ROCKET);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_ROCKET_SELLTHR_688);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_ROCKET);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_SHIT:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_SHIT_UPONE_220);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_SHIT_SELLONE_96);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_SHIT);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_SHIT_UPTWO_260);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_SHIT_SELLTWO_272);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_SHIT);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_SHIT_SELLTHR_480);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_SHIT);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_SNOW:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_SNOW_UPONE_220);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_SNOW_SELLONE_128);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_SNOW);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_SNOW_UPTWO_320);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_SNOW_SELLTWO_304);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_SNOW);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_SNOW_SELLTHR_560);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_SNOW);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_STAR:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_STAR_UPONE_220);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_STAR_SELLONE_128);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_STAR);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_STAR_UPTWO_260);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_STAR_SELLTWO_304);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_STAR);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_STAR_SELLTHR_512);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_STAR);
                        }
                    }
                        break;
                    case GAME_TOWER_TYPE_SUN:
                    {
                        
                        if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_SUN_UPONE_260);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_SUN_SELLONE_144);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATEONE_KILLRADIUS_SUN);
                            
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                        {
                            sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_SUN_UPTWO_320);
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_SUN_SELLTWO_352);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_SUN);
                        }
                        else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
                        {
                            
                            sprintf(upNameBuffer, "upgrade_0_CN.png");
                            sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_SUN_SELLTHR_608);
                            sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_UPDATETWO_KILLRADIUS_SUN);
                        }
                    }
                        break;
                        
                    default:
                        break;
                }
                
                
                CCSize bgSize = LcdAdapClass::sharedLCDADAP()->getWinSize();
                
                selSprite = CCSprite::createWithSpriteFrameName("select_01.png");
                selSprite->setPosition(ccp(0,0));
                CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName("selAnim");
                CCSize selSize = selSprite->getContentSize();
                selSprite->runAction(CCRepeatForever::create((CCSequence*)(CCSequence::create(CCAnimate::create(animation),NULL))));
                this->addChild(selSprite,1);
                
                
                killZoneSprite = CCSprite::createWithSpriteFrameName(rangeNameBuffer);
                killZoneSprite->setPosition(ccp(0,0));
                this->addChild(killZoneSprite,2);
                //add upmenu sellmenu
                
                upMenu = CCMenuItemImage::create(upNameBuffer, upNameBuffer, this, menu_selector(TowerSelPadClass::towerSelMenuCallBack));
                upMenu->setTag(UPMENU_TAG);
                CCSize upBtnSize = upMenu->getContentSize();
                
                
                if (ccpLength(ccpSub(centerPos, ccp(centerPos.x,bgSize.height))) < (upBtnSize.height * 2 * LcdAdapClass::sharedLCDADAP()->getYScale()))
                {
                    if (ccpLength(ccpSub(centerPos, ccp(bgSize.width,centerPos.y))) < (upBtnSize.width * LcdAdapClass::sharedLCDADAP()->getXScale())) {
                        upMenu->setPosition(ccp(-selSize.width / 2 - upBtnSize.width / 2, 0));
                    }
                    else
                    {
                        upMenu->setPosition(ccp(selSize.width / 2 + upBtnSize.width / 2, 0));
                    }
                }
                else
                {
                    upMenu->setPosition(ccp(0,  selSize.height / 2 + upBtnSize.height / 2));
                }
                
//                if ((centerPos.y + towerKillRadius) >= (bgSize.height - TOPHEIGHT)) {
//                    upMenu->setPosition(ccp(selSize.width / 2 + upBtnSize.width / 2, 0));
//                }
//                else
//                {
//                    upMenu->setPosition(ccp(0,  selSize.height / 2 + upBtnSize.height / 2));
//                }
                
                sellMenu = CCMenuItemImage::create(sellNameBuffer, sellNameBuffer, this, menu_selector(TowerSelPadClass::towerSelMenuCallBack));
                sellMenu->setTag(SELLMENU_TAG);
                CCSize sellBtnSize = sellMenu->getContentSize();
                
                if (ccpLength(ccpSub(centerPos, ccp(centerPos.x,0))) < (sellBtnSize.height * 2 *  LcdAdapClass::sharedLCDADAP()->getYScale()))
                {
                    if (ccpLength(ccpSub(centerPos, ccp(bgSize.width,centerPos.y))) < (sellBtnSize.width * LcdAdapClass::sharedLCDADAP()->getXScale())) {
                        sellMenu->setPosition(ccp(-selSize.width / 2 - upBtnSize.width / 2, 0));
                    }
                    else
                    {
                        sellMenu->setPosition(ccp(selSize.width / 2 + sellBtnSize.width / 2, 0));
                    }
                }
                else
                {
                    sellMenu->setPosition(ccp(0,  -selSize.height / 2 - upBtnSize.height / 2));
                }
//                if ((centerPos.y - towerKillRadius) < 0) {
//                    sellMenu->setPosition(ccp(selSize.width / 2 + sellBtnSize.width / 2, 0));
//                }
//                else
//                {
//                    sellMenu->setPosition(ccp(0, - selSize.height / 2 - sellBtnSize.height / 2));
//                }
                CCMenu* menu = CCMenu::create(upMenu,sellMenu,NULL);
                menu->setPosition(CCPointZero);
                this->addChild(menu,20);
                isTowerShowPAD = true;
                isTowerHidePAD = false;
                userSelTower = tower;
                tower->hideTowerUpgrade();
            }
            
            
        }
    }
}

void TowerSelPadClass::updateTowerSelPadState()
{
    bool isEnable = false;
    char upNameBuffer[100] = {0};
    int payMoney = 0;
    CCSpriteFrame* frame = NULL;
    
    switch (selTowerType) {
    case GAME_TOWER_TYPE_ANCHOR:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_ANCHOR_UPONE_320;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_ANCHOR_UPTWO_380;
        }
        
    }
        break;
    case GAME_TOWER_TYPE_ARROW:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_ARROW_UPONE_260;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_ARROW_UPTWO_380;
        }
    }
        break;
    case GAME_TOWER_TYPE_BALL:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_BALL_UPONE_320;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_BALL_UPTWO_480;
        }
    }
        break;
    case GAME_TOWER_TYPE_BLUESTAR:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_BLUESTAR_UPONE_260;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_BLUESTAR_UPTWO_320;
        }
    }
        break;
    case GAME_TOWER_TYPE_BOTTLE:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_BOTTLE_UPONE_180;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_BOTTLE_UPTWO_260;
        }
    }
        break;
    case GAME_TOWER_TYPE_BUFF:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_BUFF_UPONE_180;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_BUFF_UPTWO_260;
        }
    }
        break;
    case GAME_TOWER_TYPE_CUTTLE:
    {
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_CUTTLE_UPONE_260;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_CUTTLE_UPTWO_320;
        }
    }
        break;
    case GAME_TOWER_TYPE_FAN:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_FAN_UPONE_220;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_FAN_UPTWO_260;
        }
    }
        break;
    case GAME_TOWER_TYPE_FIREBOTTLE:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_FIREBOTTLE_UPONE_260;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_FIREBOTTLE_UPTWO_320;
        }
    }
        break;
    case GAME_TOWER_TYPE_FISH:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_FISH_UPONE_260;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_FISH_UPTWO_320;
        }
    }
        break;
    case GAME_TOWER_TYPE_MUSHROOM:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_MUSHROOM_UPONE_260;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_MUSHROOM_UPTWO_380;
        }
    }
        break;
    case GAME_TOWER_TYPE_PIN:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_PIN_UPONE_260;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_PIN_UPTWO_320;
        }
    }
        break;
    case GAME_TOWER_TYPE_PLANE:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_PLANE_UPONE_320;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_PLANE_UPTWO_380;
        }
    }
        break;
    case GAME_TOWER_TYPE_ROCKET:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_ROCKET_UPONE_260;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_ROCKET_UPTWO_380;
        }
    }
        break;
    case GAME_TOWER_TYPE_SHIT:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_SHIT_UPONE_220;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_SHIT_UPTWO_260;
        }
    }
        break;
    case GAME_TOWER_TYPE_SNOW:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_SNOW_UPONE_220;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_SNOW_UPTWO_320;
        }
    }
        break;
    case GAME_TOWER_TYPE_STAR:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_STAR_UPONE_220;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_STAR_UPTWO_260;
        }
    }
        break;
    case GAME_TOWER_TYPE_SUN:
    {
        
        if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
            
            payMoney = GAME_TOWER_SUN_UPONE_260;
        }
        else if (selTowerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
        {
            payMoney = GAME_TOWER_SUN_UPTWO_320;
        }
    }
        break;
        
    default:
        break;
    }

    
    if (HUDClass::sharedHUD()->getHUDMoney() < payMoney) {
        sprintf(upNameBuffer, "upgrade_-%d.png",payMoney);
        isEnable = false;
    }
    else
    {
        sprintf(upNameBuffer, "upgrade_%d.png",payMoney);
        isEnable = true;
    }
    
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(upNameBuffer);
    updatePayMoney = payMoney;
    if (frame) {
        upMenu->setNormalSpriteFrame(frame);
        upMenu->setEnabled(isEnable);

    }

}


void TowerSelPadClass::hideUpSelPad(AttackTowerClass *tower)
{
    if (tower) {
        
        tower->setIsShowTowerUpGrade(tower->getIsShowTowerUpGrade());
        if (upMenu != NULL && sellMenu != NULL && selSprite != NULL && killZoneSprite != NULL) {
            upMenu->removeFromParentAndCleanup(true);
            upMenu = NULL;
            //sellMenu->removeAllChildren();
            sellMenu->removeFromParentAndCleanup(true);
            sellMenu = NULL;
            killZoneSprite->removeFromParentAndCleanup(true);
            killZoneSprite = NULL;
            selSprite->stopAllActions();
            selSprite->removeFromParentAndCleanup(true);
            selSprite = NULL;
            isTowerShowPAD = false;
            isTowerHidePAD = true;
            userSelTower = NULL;
        }
    }
}

bool TowerSelPadClass::getIsHideTowerPAD()
{
    return isTowerHidePAD;
}

bool TowerSelPadClass::getIsShowTowerPAD()
{
    return isTowerShowPAD;
}

void TowerSelPadClass::setIsHideTowerPAD(bool flag)
{
    isTowerHidePAD = flag;
}

bool TowerSelPadClass::getUserUpOrSellTower()
{
    return isUserUpOrSellTower;
}

void TowerSelPadClass::towerSelMenuCallBack(cocos2d::CCObject *parent)
{
    if (parent != NULL) {
		Util::getInstance()->performWithDelay(0, [=](){
			CCMenuItem* menu = (CCMenuItem*)parent;
			int money = 0;
        
			switch (menu->getTag()) {
				case UPMENU_TAG:
				{
					if (selTowerUpdateType < GAME_TOWER_UPDATE_TYPE_TRE) {
                    
						selTowerUpdateType = (GAME_TOWER_UPDATE_TYPE)(selTowerUpdateType + 1);
						if (selTowerUpdateType >= GAME_TOWER_UPDATE_TYPE_TWO) {
							selTowerUpdateType = GAME_TOWER_UPDATE_TYPE_TWO;
						}
                    
						userSelTower->setTowerUpdate(selTowerUpdateType);
						money = HUDClass::sharedHUD()->getHUDMoney();
						money -= updatePayMoney;
						HUDClass::sharedHUD()->setHUDMoney(money);
                    
					}
				
					this->hideUpSelPad(userSelTower);
					
					isUserUpOrSellTower = true;
					if (myTarget && mySelector) {
						(myTarget->*mySelector)();
					}
				}
					break;
				case SELLMENU_TAG:
				{
					AttackTowerClass* selTower = userSelTower;

					money = selTower->getTowerSellMoney();
					money += HUDClass::sharedHUD()->getHUDMoney();

					HUDClass::sharedHUD()->setHUDMoney(money);
					this->hideUpSelPad(userSelTower);
					if (selTower) {
						selTower->removeTowerFromParent();
					}
					isUserUpOrSellTower = false;
					if (myTarget && mySelector) {
						(myTarget->*mySelector)();
					}
				}
					break;
				default:
					break;
			}
		});
    }
}
