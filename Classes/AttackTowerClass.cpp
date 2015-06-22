//
//  AttackTowerClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-7-31.
//
//

#include "AttackTowerClass.h"
#include "TowerBulletClass.h"
#include "HUDClass.h"
#include "CommonClass.h"
#include "LcdAdapClass.h"
#define UPMENU_TAG  (15)
#define SELLMENU_TAG (25)

#define TOWER_ROTATE_TIME (0.2)

USING_NS_CC;

static char comBuffer[255] = {0};

AttackTowerClass::AttackTowerClass()
{
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(AttackTowerClass::enemyDeadNotification), ENEMY_DEAD_NOTIFICATION, NULL);
}

AttackTowerClass::~AttackTowerClass()
{
	setAttackObject(NULL);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, ENEMY_DEAD_NOTIFICATION);
    towerAni->release();
}

void AttackTowerClass::enemyDeadNotification(CCObject *object)
{
	EnemySpriteClass *enemy = dynamic_cast<EnemySpriteClass *>(object);
	if (enemy && enemy == attackObject)
	{
		setAttackObject(NULL);
	}
}

bool AttackTowerClass::init(const char* fileName,int killValue,float killRadius, float fireTime)
{
    CCAssert(!(fileName == NULL), "cannot be NULL");
    
    towerKillValue = killValue;
    towerKillRadius = killRadius;
    towerFireTime = fireTime;
	towerRoateTime = TOWER_ROTATE_TIME;
    fireTimeCounter = 0;
    towerRoate = 45;
    bulletVector = CCPoint(0.5,0.5);
//    isTowerShowPAD = false;
//    isTowerHidePAD = false;
    isTowerAttacking = false;
    isSpeed2X = false;
    enemyArray = NULL;
    enemyMonsterArray = NULL;
    enemyObjectArray = NULL;
    attackObject = NULL;
    isTowerPause = false;
    isShowTowerUpGrade = false;
    towerUpdateType = GAME_TOWER_UPDATE_TYPE_ZERO;
    towerType = GAME_TOWER_TYPE_NONE;
    bulletEffectArray = NULL;
    bulletArray = NULL;
	isTowerRotateToTarget = false;
    isTowerRotating = false;
    towerSubSprite = NULL;
    //CCSprite::initWithSpriteFrameName(fileName);
    
    this->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
    this->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());

    
    return true;
}

AttackTowerClass* AttackTowerClass::create(const char* fileName,int killValue,float killRadius, float fireTime)
{
    CCAssert(!(fileName == NULL), "cannot be NULL");
    AttackTowerClass* tower = new AttackTowerClass();
    if (tower && tower->init(fileName,killValue,killRadius,fireTime)) {
        tower->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(tower);
    }
    
    return tower;
}

bool AttackTowerClass::init(GAME_TOWER_TYPE type)
{
    CCAssert(!(type == GAME_TOWER_TYPE_NONE || type == GAME_TOWER_TYPE_MAX), "cannot be invalid");
    
    int aniCount = 0;
    int bulletKillValue = 0;
    float killRadius = 0;
    float fireTime = 0;
    char* pfileName = NULL;
    char pBuffer[50] = {0};
    CCArray *animFrames = CCArray::create();
    towerAniTime = 0.1;
    towerPayMoney = 999;
	towerSellMoney = 999;
    
    
    switch (type) {
        case GAME_TOWER_TYPE_ANCHOR:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_ANCHOR;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_ANCHOR;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_ANCHOR;
                pfileName = "Anchor";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_ARROW:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_ARROW;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_ARROW;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_ARROW;
                pfileName = "Arrow";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_BALL:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_BALL;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_BALL;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_BALL;
                pfileName = "Ball";
                aniCount = 4;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_BLUESTAR:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_BLUESTAR;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_BLUESTAR;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_BLUESTAR;
                pfileName = "BStar";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_BOTTLE:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_BOTTLE;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_BOTTLE;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_BOTTLE;
                pfileName = "Bottle";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_BUFF:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_BUFF;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_BUFF;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_BUFF;
                pfileName = "Buff";
                aniCount = 1;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_CUTTLE:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_CUTTLE;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_CUTTLE;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_CUTTLE;
                pfileName = "Cuttle";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_FAN:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_FAN;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_FAN;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_FAN;
                pfileName = "Fan";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_FIREBOTTLE:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_FIREBOTTLE;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_FIREBOTTLE;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_FIREBOTTLE;
                pfileName = "FBottle";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_FISH:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_FISH;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_FISH;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_FISH;
                pfileName = "Fish";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_MUSHROOM:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_MUSHROOM;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_MUSHROOM;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_MUSHROOM;
                pfileName = "Mushroom";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_PIN:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_PIN;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_PIN;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_PIN;
                pfileName = "Pin";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_PLANE:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_PLANE;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_PLANE;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_PLANE;
                pfileName = "Plane";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_ROCKET:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_ROCKET;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_ROCKET;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_ROCKET;
                pfileName = "Rocket";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_SHIT:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_SHIT;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_SHIT;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_SHIT;
                pfileName = "Shit";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_SNOW:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_SNOW;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_SNOW;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_SNOW;
                pfileName = "Snow";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_STAR:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_STAR;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_STAR;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_STAR;
                pfileName = "Star";
                aniCount = 3;
                towerAniTime = 0.1;
            }
            break;
        case GAME_TOWER_TYPE_SUN:
            {
                killRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_SUN;
                bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_SUN;
                fireTime = GAME_TOWER_FIRE_TIME_INTER_SUN;
                pfileName = "Sun";
                aniCount = 1;
                towerAniTime = 0.1;
            }
            break;
        default:
            break;
    }
    
    if(type != GAME_TOWER_TYPE_BALL && type != GAME_TOWER_TYPE_BUFF)
    {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-11.png",pfileName);
        towerBG = CCSprite::createWithSpriteFrameName(pBuffer);
        towerBG->setPosition(ccp(0, 0));
        this->addChild(towerBG,-1);
    }
    
    for (int i = 11; i < (11 + aniCount); i++) {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s%d.png",pfileName,i);
        if (i == 11) {
            this->init(pBuffer, bulletKillValue, killRadius, fireTime);
            towerSprite = CCSprite::createWithSpriteFrameName(pBuffer);
            towerSprite->setPosition(ccp(0,0));
            this->addChild(towerSprite,1);
        }
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pBuffer);
        animFrames->addObject(frame);
    }
    
    
    if (type != GAME_TOWER_TYPE_ARROW && type != GAME_TOWER_TYPE_BUFF) {
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "%s11.png",pfileName);//再加一个，动作完成后，变成它自己的模样
        animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
        
        
    }
    towerAni = CCAnimation::createWithSpriteFrames(animFrames, towerAniTime);
    towerAni->retain();
    
    if (type == GAME_TOWER_TYPE_SUN) {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s-11.png",pfileName);
        towerSubSprite = CCSprite::createWithSpriteFrameName(pBuffer);
        towerSubSprite->setPosition(ccp(0, 0));
        this->addChild(towerSubSprite,2);
    }
    
    towerType = type;
    towerAniNum = aniCount;
    
    animFrames->removeAllObjects();
    
    
    
    
    this->setTowerPayMoney();
    this->setTowerSellMoney();
    
    
    return true;
}

AttackTowerClass* AttackTowerClass::create(GAME_TOWER_TYPE type)
{
    CCAssert(!(type == GAME_TOWER_TYPE_NONE || type == GAME_TOWER_TYPE_MAX), "cannot be invalid");
    AttackTowerClass* tower = new AttackTowerClass();
    if (tower && tower->init(type)) {
        tower->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(tower);
    }
    
    return tower;
}

void AttackTowerClass::showTowerUpgrade()
{
    showUpgrade->setVisible(true);
}

void AttackTowerClass::hideTowerUpgrade()
{
    showUpgrade->setVisible(false);
}

void AttackTowerClass::setTowerParentAndPos(CCNode* parent,CCPoint pos)
{
    CCAssert(!(parent == NULL), "cannot be NULL");
    
    CCSize towerSize = towerSprite->getContentSize();
    
    CCArray* animFrames = CCArray::create();
    
    parent->addChild(this,GAMEING_TOWER_ZORDER);
    
    this->setPosition(pos);
    showUpgrade = CCSprite::createWithSpriteFrameName("showupgrade01.png");
    CCSize upSize = showUpgrade->getContentSize();
    parent->addChild(showUpgrade,GAMEING_TOWER_UPDATE_POINT_ZORDER);
    showUpgrade->setVisible(false);
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(showUpgrade, ccp(pos.x,pos.y + ((towerSize.height + upSize.height) * 2.0/5.0) * LcdAdapClass::sharedLCDADAP()->getYScale()));
    
    for (int i = 1; i < 3; i++) {
        memset(comBuffer, 0, sizeof(comBuffer));
        sprintf(comBuffer, "%s%02d.png","showupgrade",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer);
        animFrames->addObject(frame);
    }
    CCAnimation* upAni = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
    showUpgrade->runAction(CCRepeatForever::create(CCAnimate::create(upAni)));
}

void AttackTowerClass::removeTowerFromParent()
{
    showUpgrade->stopAllActions();
    showUpgrade->removeFromParentAndCleanup(true);
    
    if (getBulletBatchParent() != NULL) {
        if (towerType == GAME_TOWER_TYPE_BALL || towerType == GAME_TOWER_TYPE_FIREBOTTLE) {
            bulletArray->removeObjectsInArray(getBulletBatchParent()->getChildren());
            getBulletBatchParent()->removeAllChildren();
        }
    }
    
    this->removeFromParentAndCleanup(true);
}

void AttackTowerClass::setIsShowTowerUpGrade(bool showFlag)
{
    isShowTowerUpGrade = showFlag;
    if (towerUpdateType >= GAME_TOWER_UPDATE_TYPE_TWO) {
        isShowTowerUpGrade = false;
    }
    
    if (isShowTowerUpGrade) {
        this->showTowerUpgrade();
    }
    else
    {
        this->hideTowerUpgrade();
    }
}

bool AttackTowerClass::getIsShowTowerUpGrade()
{
    return isShowTowerUpGrade;
}

void AttackTowerClass::setTowerPayMoney()
{
    if (towerUpdateType < GAME_TOWER_UPDATE_TYPE_TWO) {
        switch (towerType) {
            case GAME_TOWER_TYPE_ANCHOR:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_ANCHOR_UPONE_320;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_ANCHOR_UPTWO_380;
                }
            }
                break;
            case GAME_TOWER_TYPE_ARROW:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_ARROW_UPONE_260;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_ARROW_UPTWO_380;
                }
            }
                break;
            case GAME_TOWER_TYPE_BALL:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_BALL_UPONE_320;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_BALL_UPTWO_480;
                }
            }
                break;
            case GAME_TOWER_TYPE_BLUESTAR:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_BLUESTAR_UPONE_260;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_BLUESTAR_UPTWO_320;
                }
            }
                break;
            case GAME_TOWER_TYPE_BOTTLE:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_BOTTLE_UPONE_180;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_BOTTLE_UPTWO_260;
                }
            }
                break;
            case GAME_TOWER_TYPE_BUFF:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_BUFF_UPONE_180;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_BUFF_UPTWO_260;
                }
            }
                break;
            case GAME_TOWER_TYPE_CUTTLE:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_CUTTLE_UPONE_260;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_CUTTLE_UPTWO_320;
                }
            }
                break;
            case GAME_TOWER_TYPE_FAN:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_FAN_UPONE_220;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_FAN_UPTWO_260;
                }
            }
                break;
            case GAME_TOWER_TYPE_FIREBOTTLE:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_FIREBOTTLE_UPONE_260;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_FIREBOTTLE_UPTWO_320;
                }
            }
                break;
            case GAME_TOWER_TYPE_FISH:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_FISH_UPONE_260;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_FISH_UPTWO_320;
                }
            }
                break;
            case GAME_TOWER_TYPE_MUSHROOM:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_MUSHROOM_UPONE_260;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_MUSHROOM_UPTWO_380;
                }
            }
                break;
            case GAME_TOWER_TYPE_PIN:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_PIN_UPONE_260;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_PIN_UPTWO_320;
                }
            }
                break;
            case GAME_TOWER_TYPE_PLANE:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_PLANE_UPONE_320;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_PLANE_UPTWO_380;
                }
            }
                break;
            case GAME_TOWER_TYPE_ROCKET:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_ROCKET_UPONE_260;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_ROCKET_UPTWO_380;
                }
            }
                break;
            case GAME_TOWER_TYPE_SHIT:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_SHIT_UPONE_220;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_SHIT_UPTWO_260;
                }
            }
                break;
            case GAME_TOWER_TYPE_SNOW:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_SNOW_UPONE_220;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_SNOW_UPTWO_320;
                }
            }
                break;
            case GAME_TOWER_TYPE_STAR:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_STAR_UPONE_220;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_STAR_UPTWO_260;
                }
            }
                break;
            case GAME_TOWER_TYPE_SUN:
            {
                if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
                    towerPayMoney = GAME_TOWER_SUN_UPONE_260;
                }
                else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
                {
                    towerPayMoney = GAME_TOWER_SUN_UPTWO_320;
                }
            }
                break;
            default:
                break;
        }
    }
    else
    {
        towerPayMoney = 0xffffffff;
    }
}

int AttackTowerClass::getTowerPayMoney()
{
    return towerPayMoney;
}

void AttackTowerClass::setTowerSellMoney()
{
	if (towerUpdateType < GAME_TOWER_UPDATE_TYPE_TRE) {
		switch (towerType) {
			case GAME_TOWER_TYPE_ANCHOR:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_ANCHOR_SELLONE_208;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_ANCHOR_SELLTWO_464;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_ANCHOR_SELLTHR_768;
					}
				}
				break;
			case GAME_TOWER_TYPE_ARROW:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_ARROW_SELLONE_176;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_ARROW_SELLTWO_384;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_ARROW_SELLTHR_688;
					}
					
				}
				break;
			case GAME_TOWER_TYPE_BALL:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_BALL_SELLONE_128;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_BALL_SELLTWO_384;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_BALL_SELLTHR_768;
					}
				}
				break;
			case GAME_TOWER_TYPE_BLUESTAR:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_BLUESTAR_SELLONE_144;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_BLUESTAR_SELLTWO_352;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_BLUESTAR_SELLTHR_608;
					}
				}
				break;
			case GAME_TOWER_TYPE_BOTTLE:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_BOTTLE_SELLONE_80;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_BOTTLE_SELLTWO_224;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_BOTTLE_SELLTHR_432;
					}
				}
				break;
			case GAME_TOWER_TYPE_BUFF:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_BUFF_SELLONE_80;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_BUFF_SELLTWO_224;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_BUFF_SELLTHR_432;
					}
				}
				break;
			case GAME_TOWER_TYPE_CUTTLE:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_CUTTLE_SELLONE_176;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_CUTTLE_SELLTWO_384;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_CUTTLE_SELLTHR_640;
					}
				}
				break;
			case GAME_TOWER_TYPE_FAN:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_FAN_SELLONE_128;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_FAN_SELLTWO_304;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_FAN_SELLTHR_512;
					}
				}
				break;
			case GAME_TOWER_TYPE_FIREBOTTLE:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_FIREBOTTLE_SELLONE_128;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_FIREBOTTLE_SELLTWO_336;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_FIREBOTTLE_SELLTHR_592;
					}
				}
				break;
			case GAME_TOWER_TYPE_FISH:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_FISH_SELLONE_144;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_FISH_SELLTWO_352;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_FISH_SELLTHR_608;
					}
				}
				break;
			case GAME_TOWER_TYPE_MUSHROOM:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_MUSHROOM_SELLONE_176;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_MUSHROOM_SELLTWO_384;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_MUSHROOM_SELLTHR_688;
					}
				}
				break;
			case GAME_TOWER_TYPE_PIN:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_PIN_SELLONE_128;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_PIN_SELLTWO_336;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_PIN_SELLTHR_592;
					}
				}
				break;
			case GAME_TOWER_TYPE_PLANE:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_PLANE_SELLONE_176;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_PLANE_SELLTWO_432;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_PLANE_SELLTHR_736;
					}
				}
				break;
			case GAME_TOWER_TYPE_ROCKET:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_ROCKET_SELLONE_176;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_ROCKET_SELLTWO_384;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_ROCKET_SELLTHR_688;
					}
				}
				break;
			case GAME_TOWER_TYPE_SHIT:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_SHIT_SELLONE_96;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_SHIT_SELLTWO_272;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_SHIT_SELLTHR_480;
					}
				}
				break;
			case GAME_TOWER_TYPE_SNOW:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_SNOW_SELLONE_128;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_SNOW_SELLTWO_304;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_SNOW_SELLTHR_560;
					}
				}
				break;
			case GAME_TOWER_TYPE_STAR:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_STAR_SELLONE_128;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_STAR_SELLTWO_304;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_STAR_SELLTHR_512;
					}
				}
				break;
			case GAME_TOWER_TYPE_SUN:
				{
					if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ZERO) {
						towerSellMoney = GAME_TOWER_SUN_SELLONE_144;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
					{
						towerSellMoney = GAME_TOWER_SUN_SELLTWO_352;
					}
					else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
					{
						towerSellMoney = GAME_TOWER_SUN_SELLTHR_608;
					}
				}
				break;
			default:
				break;
		}
	}
	else
	{
		towerPayMoney = 0xffffffff;
	}
}

int AttackTowerClass::getTowerSellMoney()
{
	return towerSellMoney;
}



void AttackTowerClass::setTowerUpdate(GAME_TOWER_UPDATE_TYPE type)
{
    char pBuffer[100] = {0};
    char *pfileName = NULL;
    int index = 11;
    int curIndex = 11;
    int bgIndex = 11;//炮塔底座
    CCArray *aniArray = CCArray::create();
    
    if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
        index = 21;
        bgIndex = 12;
    }
    else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
    {
        index = 31;
        bgIndex = 13;
    }
    
    
    CCSpriteFrame* frame = NULL;
    
    
    towerUpdateType = type;
    
    switch (towerType) {
        case GAME_TOWER_TYPE_ANCHOR:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_ANCHOR;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_ANCHOR;
            }
            
            pfileName = "Anchor";
        }
            break;
        case GAME_TOWER_TYPE_ARROW:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_ARROW;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_ARROW;
            }
            pfileName = "Arrow";
        }
            break;
        case GAME_TOWER_TYPE_BALL:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_BALL;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_BALL;
            }
            pfileName = "Ball";

        }
            break;
        case GAME_TOWER_TYPE_BLUESTAR:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_BLUESTAR;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_BLUESTAR;
            }
            pfileName = "BStar";

        }
            break;
        case GAME_TOWER_TYPE_BOTTLE:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_BOTTLE;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_BOTTLE;
            }
            pfileName = "Bottle";
            bgIndex = 11;
        }
            break;
        case GAME_TOWER_TYPE_BUFF:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_BUFF;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_BUFF;
            }
            pfileName = "Buff";

        }
            break;
        case GAME_TOWER_TYPE_CUTTLE:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_CUTTLE;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_CUTTLE;
            }
            pfileName = "Cuttle";

        }
            break;
        case GAME_TOWER_TYPE_FAN:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_FAN;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_FAN;
            }
            pfileName = "Fan";
            
        }
            break;
        case GAME_TOWER_TYPE_FIREBOTTLE:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_FIREBOTTLE;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_FIREBOTTLE;
            }
            pfileName = "FBottle";
            
        }
            break;
        case GAME_TOWER_TYPE_FISH:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_FISH;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_FISH;
            }
            pfileName = "Fish";
            
        }
            break;
        case GAME_TOWER_TYPE_MUSHROOM:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_MUSHROOM;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_MUSHROOM;
            }
            pfileName = "Mushroom";
            
        }
            break;
        case GAME_TOWER_TYPE_PIN:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_PIN;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_PIN;
            }
            pfileName = "Pin";
            
        }
            break;
        case GAME_TOWER_TYPE_PLANE:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_PLANE;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_PLANE;
            }
            pfileName = "Plane";
            
        }
            break;
        case GAME_TOWER_TYPE_ROCKET:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_ROCKET;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_ROCKET;
            }
            pfileName = "Rocket";
            
        }
            break;
        case GAME_TOWER_TYPE_SHIT:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_SHIT;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_SHIT;
            }
            pfileName = "Shit";
            
        }
            break;
        case GAME_TOWER_TYPE_SNOW:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_SNOW;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_SNOW;
            }
            pfileName = "Snow";
            
        }
            break;
        case GAME_TOWER_TYPE_STAR:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_STAR;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_STAR;
            }
            pfileName = "Star";
            
        }
            break;
        case GAME_TOWER_TYPE_SUN:
        {
            if (type == GAME_TOWER_UPDATE_TYPE_ONE) {
                towerKillRadius = GAME_TOWER_UPDATEONE_KILLRADIUS_SUN;
            }
            else if (type == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                towerKillRadius = GAME_TOWER_UPDATETWO_KILLRADIUS_SUN;
            }
            pfileName = "Sun";
            
        }
            break;
        default:
            break;
    }
    

    if (towerType != GAME_TOWER_TYPE_BUFF) {
        
        towerSprite->stopAllActions();
        for (int i = index; i < (index + towerAniNum); i++) {
            memset(pBuffer, 0, sizeof(pBuffer));
            sprintf(pBuffer, "%s%d.png",pfileName,i);
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pBuffer);
            if (i == index) {
                towerSprite->setDisplayFrame(frame);
            }
            aniArray->addObject(frame);
        }
        
        towerAni->release();
        towerAni = NULL;
        
        if (towerType != GAME_TOWER_TYPE_ARROW) {
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%s%d.png",pfileName,index);
            aniArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
            towerAni = CCAnimation::createWithSpriteFrames(aniArray, 0.015);
            towerAni->retain();
        }
        else
        {
            towerAni = CCAnimation::createWithSpriteFrames(aniArray, 0.1);
            towerAni->retain();
        }
        
        if (towerType == GAME_TOWER_TYPE_SUN) {
            memset(pBuffer, 0, sizeof(pBuffer));
            if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE) {
                sprintf(pBuffer, "%s-12.png",pfileName);
            }
            else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_TWO)
            {
                sprintf(pBuffer, "%s-13.png",pfileName);
            }
            
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pBuffer);
            towerSubSprite->setDisplayFrame(frame);
        }
        else if(towerType != GAME_TOWER_TYPE_FIREBOTTLE && towerType != GAME_TOWER_TYPE_PLANE && towerType != GAME_TOWER_TYPE_BALL)
        {
            memset(comBuffer, 0, sizeof(comBuffer));
            sprintf(comBuffer, "%s-%d.png",pfileName,bgIndex);
            towerBG->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(comBuffer));
        }
    }
    
    

    this->setTowerPayMoney();
    this->setTowerSellMoney();
}

bool AttackTowerClass::userSetAttackObject(EnemySpriteClass* object)
{
    bool isValid = checkAttackObjectIsValid(object);
    
    if (towerType == GAME_TOWER_TYPE_FIREBOTTLE || towerType == GAME_TOWER_TYPE_BALL) {
        
        if (getBulletBatchParent() != NULL) {
            getBulletBatchParent()->removeAllChildren();
        }
        
        if (bulletArray != NULL) {
            for (int i = 0; i < bulletArray->count(); i++) {
                TowerBulletClass* bullet = (TowerBulletClass*)bulletArray->objectAtIndex(i);
                
                if (bullet->getBulletParentTowerType() == towerType) {
                    bulletArray->removeObject(bullet);
                }
            }
        }
    }
    
    return isValid;
}

void AttackTowerClass::setAttackObject(EnemySpriteClass* object)
{
//    CCAssert(!(object == NULL), "cannot be NULL");
    if (object != NULL && object != attackObject) {

        attackObject = object;
        isTowerRotateToTarget = false;
        isTowerRotating = false;
        isTowerAttacking = false;
    }
    else if(object == NULL)
    {
        isTowerAttacking = false;
        attackObject = NULL;
		isTowerRotateToTarget = false;
        isTowerRotating = false;
    }
}

void AttackTowerClass::setEnemyArray(cocos2d::CCArray *enemy,CCArray* death)
{
    if (enemy != NULL && death != NULL) {
        this->unscheduleUpdate();
        attackObject = NULL;
        enemyArray = enemy;
        enemyDeathArray = death;
        this->scheduleUpdate();
    }
}

void AttackTowerClass::setEnemyMonsterArray(cocos2d::CCArray *enemy)
{
    if (enemy != NULL) {
        enemyMonsterArray = enemy;
        
    }
}

void AttackTowerClass::setEnemyObjectArray(cocos2d::CCArray *enemy)
{
    if (enemy != NULL) {
        enemyObjectArray = enemy;
    }
}


CCPoint AttackTowerClass::updateFireVector(cocos2d::CCPoint curPos, cocos2d::CCPoint targetPos)
{
	CCPoint location = curPos;
    
	float o = targetPos.x - location.x;
	float a = targetPos.y - location.y ;
	float at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );
    
	if( a < 0 )
	{
		if(  o < 0 )
			at = 180 + fabs(at);
		else
			at = 180 - fabs(at);
	}
    this->towerRoate = at;
	return ccpNormalize(CCPoint(o,a));
    
}

CCSpriteBatchNode* AttackTowerClass::getBulletBatchParent()
{
    if (bulletBatchParent) {
        return bulletBatchParent;
    }
    
    return NULL;
}

EnemySpriteClass* AttackTowerClass::getAttackObject()
{
    if (attackObject) {
        return attackObject;
    }
    
    return NULL;
}

void AttackTowerClass::towerRotateActionCallBack(cocos2d::CCNode *psender)
{
    isTowerRotateToTarget = true;
    isTowerRotating = false;
}

void AttackTowerClass::rotateTowerFireNow()
{

    if (this->getBulletBatchParent() && this->getAttackObject()
        && !this->getAttackObject()->getIsDead() && this->getAttackObject()->retainCount() > 0) {
            CCSize towerSize = towerSprite->getContentSize();
            float towerRLen = (towerSize.height/ 2) * LcdAdapClass::sharedLCDADAP()->getYScale();
            CCPoint pos = this->getPosition();
            if (towerType == GAME_TOWER_TYPE_PLANE) {
                towerRLen = 0;
            }

            if (towerType == GAME_TOWER_TYPE_ARROW) {
                
                int bulletNum = 0;
                
                float PAI = 3.14159;
                CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
                
                CCPoint posBuffer0[] = {
                    CCPoint(-0.268,1 ),
                    CCPoint(0.268,1 ),
                };
                CCPoint posBuffer1[] = {
                    CCPoint(-0.466,1 ),
                    CCPoint(0.466,1 ),
                    CCPoint(0,1 ),
                };
                
                CCPoint posBuffer2[] = {
                    CCPoint(-0.466,1 ),
                    CCPoint(0.466,1 ),
                    CCPoint(0,1 ),
                    CCPoint(-0.839,1),
                    CCPoint(0.839,1)
                };
                
                CCPoint *posBuffer = NULL;
                
                switch (towerUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        {
                            
                            bulletNum = 2;
                            posBuffer = posBuffer0;
                            for (int i = 0; i < bulletNum; i++) {
                                
                                float at0 = (float)CC_RADIANS_TO_DEGREES( atanf( posBuffer[i].x/posBuffer[i].y) );
                                if( posBuffer[i].y < 0 )
                                {
                                    if(  posBuffer[i].x < 0 )
                                        at0 = 180 + (at0);
                                    else
                                        at0 = 180 - fabs(at0);
                                }
                                
                                
                                
                                float deltaY  = 1.0;
                                float deltaX  = 1.0;
                                
                                deltaX = sinf((this->towerRoate + at0) * PAI / 180.0);
                                deltaY = cosf((this->towerRoate + at0) * PAI / 180.0);
                                
                                CCPoint norMalPos = ccpNormalize(CCPoint(deltaX,deltaY));
                                

//                                pos = ccpAdd(pos, ccpMult(norMalPos, 15 ));
                                CCPoint tarPos = ccpAdd(pos, ccpMult(norMalPos, ccpLength(CCPoint(size.width, size.height))));
                                
                                TowerBulletClass* bullet = TowerBulletClass::create(pos, towerType, towerUpdateType, this->getAttackObject(),tarPos);
                                bullet->setRotation(this->towerRoate + at0);
                                if (isSpeed2X) {
                                    bullet->setIsSpeed2X(isSpeed2X);
                                }
                                
                                this->getBulletBatchParent()->addChild(bullet);
                                bullet->setEnemyArray(enemyArray);
                                bullet->setBulletKillRadius(towerKillRadius);
                                bullet->setBulletEffectArray(bulletEffectArray);
                                bullet->setBulletArray(bulletArray);
                                if (bulletArray != NULL) {
                                    bulletArray->addObject(bullet);
                                }
                            }
                            
                        }
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        {
                            bulletNum = 3;
                            posBuffer = posBuffer1;
                            for (int i = 0; i < bulletNum; i++) {
                                
                                float at0 = (float)CC_RADIANS_TO_DEGREES( atanf( posBuffer[i].x/posBuffer[i].y) );
                                if( posBuffer[i].y < 0 )
                                {
                                    if(  posBuffer[i].x < 0 )
                                        at0 = 180 + (at0);
                                    else
                                        at0 = 180 - fabs(at0);
                                }
                                
                                
                                
                                float deltaY  = 1.0;
                                float deltaX  = 1.0;
                                
                                deltaX = sinf((this->towerRoate + at0) * PAI / 180.0);
                                deltaY = cosf((this->towerRoate + at0) * PAI / 180.0);
                                
                                CCPoint norMalPos = ccpNormalize(CCPoint(deltaX,deltaY));
                                
                                
//                                pos = ccpAdd(pos, ccpMult(norMalPos, 15 ));
                                CCPoint tarPos = ccpAdd(pos, ccpMult(norMalPos, ccpLength(CCPoint(size.width, size.height))));
                                
                                TowerBulletClass* bullet = TowerBulletClass::create(pos, towerType, towerUpdateType, this->getAttackObject(),tarPos);
                                bullet->setRotation(this->towerRoate + at0);
                                if (isSpeed2X) {
                                    bullet->setIsSpeed2X(isSpeed2X);
                                }
                                
                                this->getBulletBatchParent()->addChild(bullet);
                                bullet->setEnemyArray(enemyArray);
                                bullet->setBulletKillRadius(towerKillRadius);
                                bullet->setBulletEffectArray(bulletEffectArray);
                                bullet->setBulletArray(bulletArray);
                                if (bulletArray != NULL) {
                                    bulletArray->addObject(bullet);
                                }
                            }
                        }
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        {
                            bulletNum = 5;
                            posBuffer = posBuffer2;
                            for (int i = 0; i < bulletNum; i++) {
                                
                                float at0 = (float)CC_RADIANS_TO_DEGREES( atanf( posBuffer[i].x/posBuffer[i].y) );
                                if( posBuffer[i].y < 0 )
                                {
                                    if(  posBuffer[i].x < 0 )
                                        at0 = 180 + (at0);
                                    else
                                        at0 = 180 - fabs(at0);
                                }
                                
                                
                                
                                float deltaY  = 1.0;
                                float deltaX  = 1.0;
                                
                                deltaX = sinf((this->towerRoate + at0) * PAI / 180.0);
                                deltaY = cosf((this->towerRoate + at0) * PAI / 180.0);
                                
                                CCPoint norMalPos = ccpNormalize(CCPoint(deltaX,deltaY));
                                
                                
                                //pos = ccpAdd(pos, ccpMult(norMalPos, 5 ));
                                CCPoint tarPos = ccpAdd(pos, ccpMult(norMalPos, ccpLength(CCPoint(size.width, size.height))));
                                
                                TowerBulletClass* bullet = TowerBulletClass::create(pos, towerType, towerUpdateType, this->getAttackObject(),tarPos);
                                bullet->setRotation(this->towerRoate + at0);
                                if (isSpeed2X) {
                                    bullet->setIsSpeed2X(isSpeed2X);
                                }
                                
                                this->getBulletBatchParent()->addChild(bullet);
                                bullet->setEnemyArray(enemyArray);
                                bullet->setBulletKillRadius(towerKillRadius);
                                bullet->setBulletEffectArray(bulletEffectArray);
                                bullet->setBulletArray(bulletArray);
                                if (bulletArray != NULL) {
                                    bulletArray->addObject(bullet);
                                }
                            }
                        }
                        break;
                }
            }
            else
            {
                TowerBulletClass* bullet = TowerBulletClass::create(ccpAdd(pos, ccpMult(this->bulletVector, towerRLen)), towerType, towerUpdateType, this->getAttackObject());
                if (towerType == GAME_TOWER_TYPE_BOTTLE) {
                    bullet->setRotation(this->towerRoate);
                }
                bullet->setBulletKillRadius(towerKillRadius);
                bullet->setBulletEffectArray(bulletEffectArray);
                bullet->setEnemyArray(enemyArray);
                bullet->setBulletArray(bulletArray);
                if (towerType == GAME_TOWER_TYPE_ANCHOR) {
                    CCAssert(!(enemyObjectArray == NULL), "cannote be NULL");
                    bullet->setEnemyObjectArray(enemyObjectArray);
                }
                if (towerType == GAME_TOWER_TYPE_FIREBOTTLE) {
                    bullet->setBulletParentPosAndSize(this->getPosition(), towerSprite->getContentSize());
                }
                this->getBulletBatchParent()->addChild(bullet);
                if (bulletArray != NULL) {
                    bulletArray->addObject(bullet);
                }
            }

            

    }
    else
    {
        this->setAttackObject(NULL);
    }
}

void AttackTowerClass::TowerShotActionThenFire()
{
    
    if (towerAni) {
        towerSprite->runAction(CCAnimate::create(towerAni));
    }
    this->rotateTowerFireNow();
}



bool AttackTowerClass::checkAttackObjectIsValid(EnemySpriteClass* object)
{
    EnemySpriteClass* enemy = (EnemySpriteClass*)object;
    
    
    if ((enemy != NULL) && enemy->getIsDead() == false && enemy->retainCount() > 0) {
        CCPoint enemyPos = enemy->getPosition();
        CCPoint offsetPos = ccpSub(this->getPosition(), enemyPos);
        float lcdScale = LcdAdapClass::sharedLCDADAP()->getTowerKillRadiusScale();
        if (ccpLength(offsetPos) <= towerKillRadius * lcdScale) {
            this->setAttackObject(enemy);
            return true;
        }
//        this->setAttackObject(NULL);
//        return false;
    }
    this->setAttackObject(NULL);
    return false;
}


void AttackTowerClass::attackObjectFire()
{
    if (checkAttackObjectIsValid(attackObject)) {
        this->bulletVector = this->updateFireVector(this->getPosition(), attackObject->getPosition());
        
        CCActionInterval* roate = CCRotateTo::create(0.01, this->towerRoate);
        
        CCActionInterval* action = (CCActionInterval*)CCSequence::create(roate,CCCallFuncN::create(this, callfuncN_selector(AttackTowerClass::towerRotateActionCallBack)),NULL);
        towerSprite->runAction(action);
    }
}

void AttackTowerClass::setBulletBatchParent(cocos2d::CCSpriteBatchNode *bulletParent)
{
    CCAssert(!(bulletParent == NULL), "cannot be NULL");
    bulletBatchParent = bulletParent;
}

void AttackTowerClass::setIsSpeed2X(bool flag)
{
	isSpeed2X = flag;
    if (isSpeed2X) {
        towerRoateTime /= 2;
        towerFireTime /= 2;
//        this->unschedule(schedule_selector(AttackTowerClass::attackObjectFire));
//        this->schedule(schedule_selector(AttackTowerClass::attackObjectFire), towerFireTime);
    }
    else if (!isSpeed2X)
    {
        towerRoate *= 2;
        towerFireTime *= 2;
//        this->unschedule(schedule_selector(AttackTowerClass::attackObjectFire));
//        this->schedule(schedule_selector(AttackTowerClass::attackObjectFire), towerFireTime);
    }
	
}

bool AttackTowerClass::getIsSpeed2X()
{
    return isSpeed2X;
}

void AttackTowerClass::setIsTowerPause(bool flag)
{
//    if (flag && !isGamePause) {
//        //this->unschedule(schedule_selector(AttackTowerClass::attackObjectFire));
//    }
//    else if (isGamePause)
//    {
////        this->unschedule(schedule_selector(AttackTowerClass::attackObjectFire));
////        this->schedule(schedule_selector(AttackTowerClass::attackObjectFire), towerFireTime);
//    }
//    isGamePause = true;
    isTowerPause = flag;
    if (flag) {
        this->unscheduleUpdate();
    }
    else
    {
        this->unscheduleUpdate();
        this->scheduleUpdate();
    }
}

bool AttackTowerClass::getIsTowerPause()
{
    return isTowerPause;
}

void AttackTowerClass::setTowerType(GAME_TOWER_TYPE type)
{
    towerType = type;
}

GAME_TOWER_TYPE AttackTowerClass::getTowerType()
{
    return towerType;
}

GAME_TOWER_UPDATE_TYPE AttackTowerClass::getTowerUpdateType()
{
    return towerUpdateType;
}

float AttackTowerClass::getTowerKillRadius()
{
    return towerKillRadius;
}

void AttackTowerClass::setTowerBulletEffectArray(cocos2d::CCArray *bullet, cocos2d::CCArray *effect)
{
    if (bullet != NULL) {
        bulletArray = bullet;
    }
    
    if (effect != NULL) {
        bulletEffectArray = effect;
    }
}

//void AttackTowerClass::showUpSelPad()
//{
//    if (towerType != GAME_TOWER_TYPE_NONE && towerType != GAME_TOWER_TYPE_MAX) {
////        char pBuffer[100] = {0};
////        char pBuffer2[100] = {0};
//        char upNameBuffer[100] = {0};
//        char sellNameBuffer[100] = {0};
//        char rangeNameBuffer[100] = {0};
//        switch (towerType) {
//            case GAME_TOWER_TYPE_BOTTLE:
//                {
//                    
//                    if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_NONE) {
//                        sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_BOTTLE_UPONE_180);
//                        sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BOTTLE_SELLONE_80);
//                        sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_BOTTLE_RANGEONE_100);
//                        
//                    }
//                    else if (towerUpdateType == GAME_TOWER_UPDATE_TYPE_ONE)
//                    {
//                        sprintf(upNameBuffer, "upgrade_%d.png",GAME_TOWER_BOTTLE_UPTWO_260);
//                        sprintf(sellNameBuffer, "sell_%d.png",GAME_TOWER_BOTTLE_SELLTWO_224);
//                        sprintf(rangeNameBuffer, "range_%d.png",GAME_TOWER_BOTTLE_RANGETWO_120);
//                    }
//                }
//                break;
//                
//            default:
//                break;
//        }
//        CCSize bgSize = LcdAdapClass::sharedLCDADAP()->getWinSize();
//        CCPoint centerPos = this->getPosition();
//        CCSize towerSize = this->getContentSize();
//        
//        selSprite = CCSprite::createWithSpriteFrameName("select_01.png");
//        selSprite->setPosition(ccp(towerSize.width / 2, towerSize.height / 2));
//        CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName("selAnim");
//        CCSize selSize = selSprite->getContentSize();
//        selSprite->runAction(CCRepeatForever::create((CCSequence*)(CCSequence::create(CCAnimate::create(animation),NULL))));
//        this->addChild(selSprite,-1);
//        
//        
//        killZoneSprite = CCSprite::createWithSpriteFrameName(rangeNameBuffer);
//        killZoneSprite->setPosition(ccp(towerSize.width / 2, towerSize.height / 2));
//        this->addChild(killZoneSprite,2);
//        //add upmenu sellmenu
//        
//        CCMenuItemImage* upBtn = CCMenuItemImage::create(upNameBuffer, upNameBuffer, this, menu_selector(AttackTowerClass::towerSelMenuCallBack));
//        upBtn->setTag(UPMENU_TAG);
//        CCSize upBtnSize = upBtn->getContentSize();
//        if ((centerPos.y + towerKillRadius) >= bgSize.height) {
//            upBtn->setPosition(ccp(towerSize.width / 2 + selSize.width / 2 + upBtnSize.width / 2, towerSize.height / 2));
//        }
//        else
//        {
//            upBtn->setPosition(ccp(towerSize.width / 2, towerSize.height / 2 + selSize.height / 2 + upBtnSize.height / 2));
//        }
//        upMenu = CCMenu::create(upBtn,NULL);
//        upMenu->setPosition(CCPointZero);
//        this->addChild(upMenu,20);
//        
//        CCMenuItemImage* sellBtn = CCMenuItemImage::create(sellNameBuffer, sellNameBuffer, this, menu_selector(AttackTowerClass::towerSelMenuCallBack));
//        sellBtn->setTag(SELLMENU_TAG);
//        CCSize sellBtnSize = sellBtn->getContentSize();
//        if ((centerPos.y - towerKillRadius) < 0) {
//            sellBtn->setPosition(ccp(towerSize.width / 2 + selSize.width / 2 + sellBtnSize.width / 2, towerSize.height / 2));
//        }
//        else
//        {
//            sellBtn->setPosition(ccp(towerSize.width / 2, towerSize.height / 2 - selSize.height / 2 - sellBtnSize.height / 2));
//        }
//        sellMenu = CCMenu::create(sellBtn,NULL);
//        sellMenu->setPosition(CCPointZero);
//        this->addChild(sellMenu,20);
//        isTowerShowPAD = true;
//        isTowerHidePAD = false;
//    }
//    
//    
//}
//
//void AttackTowerClass::hideUpSelPad()
//{
////    upMenu->removeAllChildren();
//    if (upMenu != NULL && sellMenu != NULL && selSprite != NULL && killZoneSprite != NULL) {
//        upMenu->removeFromParentAndCleanup(true);
//        upMenu = NULL;
//        //sellMenu->removeAllChildren();
//        sellMenu->removeFromParentAndCleanup(true);
//        sellMenu = NULL;
//        killZoneSprite->removeFromParentAndCleanup(true);
//        killZoneSprite = NULL;
//        selSprite->stopAllActions();
//        selSprite->removeFromParentAndCleanup(true);
//        selSprite = NULL;
//        isTowerShowPAD = false;
//        isTowerHidePAD = true;
//    }
//}
//
//
//
//bool AttackTowerClass::getIsShowTowerPAD()
//{
//    return isTowerShowPAD;
//}
//
//void AttackTowerClass::setIsHideTowerPAD(bool flag)
//{
//    isTowerHidePAD = flag;
//}
//
//bool AttackTowerClass::getIsHideTowerPAD()
//{
//    return isTowerHidePAD;
//}
//
//void AttackTowerClass::towerSelMenuCallBack(cocos2d::CCObject *parent)
//{
//    if (parent != NULL) {
//        CCMenu* menu = (CCMenu*)parent;
//        switch (menu->getTag()) {
//            case UPMENU_TAG:
//                {
//                    this->hideUpSelPad();
//                }
//                break;
//            case SELLMENU_TAG:
//                {
//                    this->hideUpSelPad();
//                }
//                break;
//            default:
//                break;
//        }
//    }
//}

//void AttackTowerClass::draw()
//{
//    //CCSprite::draw();
//}

void AttackTowerClass::rotateTowerNow()
{
//    if (checkAttackObjectIsValid(attackObject)) {
    if (this->getAttackObject()
        && !this->getAttackObject()->getIsDead() && this->getAttackObject()->retainCount() > 0) {
        
        isTowerRotating = true;
        this->bulletVector = this->updateFireVector(this->getPosition(), attackObject->getPosition());
        
        CCActionInterval* roate = CCRotateTo::create(towerRoateTime, this->towerRoate);
        
        CCActionInterval* action = (CCActionInterval*)CCSequence::create(roate,CCCallFuncN::create(this, callfuncN_selector(AttackTowerClass::towerRotateActionCallBack)),NULL);
        towerSprite->runAction(action);
    }
}

void AttackTowerClass::FanStarTowerFire()
{
    if (checkAttackObjectIsValid(attackObject)) {
        this->bulletVector = this->updateFireVector(this->getPosition(), attackObject->getPosition());
        if (towerType == GAME_TOWER_TYPE_CUTTLE) {
            float deltaLen = 0;
            CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
            float maxLen = ccpLength(ccp(size.width,size.height));
            float at0 = 0;
            
            switch (towerUpdateType) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    {
                        CCPoint posBuffer[] = {
                            ccp(1,1),
                            ccp(-1,1),
                            ccp(-1,-1),
                            ccp(1,-1),
                        };
                        
                        
                        for (int i = 0; i < 4; i++) {
                            TowerBulletClass* bullet0 = TowerBulletClass::create(ccpAdd(this->getPosition(), ccpMult(posBuffer[i], 5)), towerType, towerUpdateType, this->getAttackObject(),ccpAdd(this->getPosition(), ccpMult(posBuffer[i], maxLen)));
                            at0 = (float)CC_RADIANS_TO_DEGREES( atanf( posBuffer[i].x/posBuffer[i].y) );
                            if( posBuffer[i].y < 0 )
                            {
                                if(  posBuffer[i].x < 0 )
                                    at0 = 180 + (at0);
                                else
                                    at0 = 180 - fabs(at0);
                            }
                            bullet0->setRotation(at0);
                            if (isSpeed2X) {
                                bullet0->setIsSpeed2X(isSpeed2X);
                            }
                            bullet0->setEnemyArray(enemyArray);
                            this->getBulletBatchParent()->addChild(bullet0);
                            bullet0->setBulletEffectArray(bulletEffectArray);
                            bullet0->setBulletArray(bulletArray);
                            if (bulletArray != NULL) {
                                bulletArray->addObject(bullet0);
                            }
                        }
                    }
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    {
                        CCPoint posBuffer[] = {
                            ccp(1,1),
                            ccp(-1,1),
                            ccp(-1,-1),
                            ccp(1,-1),
                            ccp(1,0),
                            ccp(0,1),
                            ccp(-1,0),
                            ccp(0,-1)
                        };
                        
						for (int i = 0; i < 8; i++) {
                            TowerBulletClass* bullet0 = TowerBulletClass::create(ccpAdd(this->getPosition(), ccpMult(posBuffer[i], 5)), towerType, towerUpdateType, this->getAttackObject(),ccpAdd(this->getPosition(), ccpMult(posBuffer[i], maxLen)));
                            
                            at0 = (float)CC_RADIANS_TO_DEGREES( atanf( posBuffer[i].x/posBuffer[i].y) );
                            if( posBuffer[i].y < 0 )
                            {
                                if(  posBuffer[i].x < 0 )
                                    at0 = 180 + (at0);
                                else
                                    at0 = 180 - fabs(at0);
                            }
                            bullet0->setRotation(at0);
                            if (isSpeed2X) {
                                bullet0->setIsSpeed2X(isSpeed2X);
                            }
                            bullet0->setEnemyArray(enemyArray);
                            this->getBulletBatchParent()->addChild(bullet0);
                            bullet0->setBulletEffectArray(bulletEffectArray);
                            bullet0->setBulletArray(bulletArray);
                            if (bulletArray != NULL) {
                                bulletArray->addObject(bullet0);
                            }
                        }

                    }
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    {
                        CCPoint posBuffer[] = {
                            ccp(0.58,1),
                            ccp(-0.58,1),
                            ccp(0.58,-1),
                            ccp(-0.58,-1),
                            ccp(1,0),
                            ccp(0,1),
                            ccp(-1,0),
                            ccp(0,-1),
                            ccp(1.73,1),
                            ccp(-1.73,1),
                            ccp(1.73,-1),
                            ccp(-1.73,-1),
                        };
                        
						for (int i = 0; i < 12; i++) {
                            TowerBulletClass* bullet0 = TowerBulletClass::create(ccpAdd(this->getPosition(), ccpMult(posBuffer[i], 5)), towerType, towerUpdateType, this->getAttackObject(),ccpAdd(this->getPosition(), ccpMult(posBuffer[i], maxLen)));

                            at0 = (float)CC_RADIANS_TO_DEGREES( atanf( posBuffer[i].x/posBuffer[i].y) );
                            if( posBuffer[i].y < 0 )
                            {
                                if(  posBuffer[i].x < 0 )
                                    at0 = 180 + (at0);
                                else
                                    at0 = 180 - fabs(at0);
                            }
                            bullet0->setRotation(at0);
                            
                            if (isSpeed2X) {
                                bullet0->setIsSpeed2X(isSpeed2X);
                            }
                            bullet0->setEnemyArray(enemyArray);
                            this->getBulletBatchParent()->addChild(bullet0);
                            bullet0->setBulletEffectArray(bulletEffectArray);
                            bullet0->setBulletArray(bulletArray);
                            if (bulletArray != NULL) {
                                bulletArray->addObject(bullet0);
                            }
                        }

                    }
                    break;
                case GAME_TOWER_UPDATE_TYPE_TRE:
                    {
                        TowerBulletClass* bullet = TowerBulletClass::create(ccpAdd(this->getPosition(), ccpMult(this->bulletVector, 5)), towerType, towerUpdateType, this->getAttackObject());
                        this->getBulletBatchParent()->addChild(bullet);
                        bullet->setBulletEffectArray(bulletEffectArray);
                        if (bulletArray != NULL) {
                            bulletArray->addObject(bullet);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        else{
            
            CCSize towerSize = towerSprite->getContentSize();

            TowerBulletClass* bullet = TowerBulletClass::create(this->getPosition(), towerType, towerUpdateType, this->getAttackObject());
            if (isSpeed2X) {
                bullet->setIsSpeed2X(isSpeed2X);
            }

            if (towerType == GAME_TOWER_TYPE_BALL) {
                bullet->setBulletParentPosAndSize(this->getPosition(), towerSprite->getContentSize());
            }
            
            bullet->setEnemyArray(enemyArray);
            bullet->setBulletKillRadius(towerKillRadius);
            this->getBulletBatchParent()->addChild(bullet);
            bullet->setBulletEffectArray(bulletEffectArray);
            bullet->setBulletArray(bulletArray);
            if (bulletArray != NULL) {
                bulletArray->addObject(bullet);
            }
            
        }
        if (towerAni) {
            towerSprite->runAction(CCAnimate::create(towerAni));
        }
    }
}

void AttackTowerClass::SunTowerFire()
{
    if (checkAttackObjectIsValid(attackObject)) {
//        this->bulletVector = this->updateFireVector(this->getPosition(), attackObject->getPosition());
        
        TowerBulletClass* bullet = TowerBulletClass::create(this->getPosition(), towerType, towerUpdateType, this->getAttackObject());
        if (isSpeed2X) {
            bullet->setIsSpeed2X(isSpeed2X);
        }
		bullet->setEnemyArray(enemyArray);
        bullet->setBulletKillRadius(towerKillRadius);
        this->getBulletBatchParent()->addChild(bullet);
        bullet->setBulletEffectArray(bulletEffectArray);
        bullet->setBulletArray(bulletArray);
        if (bulletArray != NULL) {
            bulletArray->addObject(bullet);
        }
    }
}

void AttackTowerClass::setTowerFireNow()
{
    switch (towerType) {
        case GAME_TOWER_TYPE_ANCHOR:
            {
                //this->rotateTowerThenFire();
                this->TowerShotActionThenFire();
            }
            break;
        case GAME_TOWER_TYPE_ARROW:
            {
                //this->rotateTowerThenFire();
                this->TowerShotActionThenFire();
            }
            break;
        case GAME_TOWER_TYPE_BALL:
            {
                this->FanStarTowerFire();
            }
            break;
        case GAME_TOWER_TYPE_BLUESTAR:
            {
                this->FanStarTowerFire();
            }
            break;
        case GAME_TOWER_TYPE_BOTTLE:
            {
                //this->rotateTowerThenFire();
                this->TowerShotActionThenFire();
            }
            break;
        case GAME_TOWER_TYPE_BUFF:
            {
                this->FanStarTowerFire();
            }
            break;
        case GAME_TOWER_TYPE_CUTTLE:
            {
                this->FanStarTowerFire();
            }
            break;
        case GAME_TOWER_TYPE_FAN:
            {
                this->FanStarTowerFire();
            }
            break;
        case GAME_TOWER_TYPE_FIREBOTTLE:
            {
                //this->rotateTowerThenFire();
                this->TowerShotActionThenFire();
            }
            break;
        case GAME_TOWER_TYPE_FISH:
            {
                //this->rotateTowerThenFire();
                this->TowerShotActionThenFire();
            }
            break;
        case GAME_TOWER_TYPE_MUSHROOM:
            {
//                if (!attackObject->getIsAttackedByMushRoom()) {
//                    this->SunTowerFire();
//                    attackObject->setIsAttackedByMushRoom(true);
//                }
                this->SunTowerFire();
            }
            break;
        case GAME_TOWER_TYPE_PIN:
            {
                //this->rotateTowerThenFire();
                this->TowerShotActionThenFire();
            }
            break;
        case GAME_TOWER_TYPE_PLANE:
            {
                //this->rotateTowerThenFire();
                this->TowerShotActionThenFire();
            }
            break;
        case GAME_TOWER_TYPE_ROCKET:
            {
                //this->rotateTowerThenFire();
                this->TowerShotActionThenFire();
            }
            break;
        case GAME_TOWER_TYPE_SHIT:
            {
                this->FanStarTowerFire();
            }
            break;
        case GAME_TOWER_TYPE_SNOW:
            {
//                this->FanStarTowerFire();
                this->SunTowerFire();
            }
            break;
        case GAME_TOWER_TYPE_STAR:
            {
                this->FanStarTowerFire();
            }
            break;
        case GAME_TOWER_TYPE_SUN:
            {
                this->SunTowerFire();
            }
            break;
        default:
            break;
    }
}

void AttackTowerClass::checkCanAttackEenmy()
{
    
    if (enemyMonsterArray && !attackObject) {
        EnemySpriteClass* object = NULL;
        int index = 0;
        do {
            if (index < enemyMonsterArray->count()) {
                object = (EnemySpriteClass*)enemyMonsterArray->objectAtIndex(index++);
                if (this->checkAttackObjectIsValid(object)) {
                    break;
                }
            }
            else
            {
                break;
            }
            
        } while (object != NULL);
    }
}



void AttackTowerClass::towerUpdateFire(float dt)
{
    
    fireTimeCounter += dt;
    if (fireTimeCounter >= towerFireTime) {
        fireTimeCounter = 0;
        if (attackObject && !attackObject->getIsDead() && attackObject->retainCount() > 0) {
            if (towerType == GAME_TOWER_TYPE_FIREBOTTLE || towerType == GAME_TOWER_TYPE_BALL) {
                if (!isTowerAttacking && (!isTowerRotating)) {
                    isTowerAttacking = true;
                    this->setTowerFireNow();
                }
            }
            else if(!isTowerRotating)
            {
                this->setTowerFireNow();
            }
        }
        else
        {
            fireTimeCounter = 0;
            this->setAttackObject(NULL);
        }
        //add
    }
    
}

void AttackTowerClass::updateTowerRotateByeEnemy()
{
    if (attackObject == NULL) {
        return;
    }
    else if (attackObject && (attackObject->getIsDead() || attackObject->retainCount() == 0))
    {
        this->setAttackObject(NULL);
        return;
    }
    else if (!checkAttackObjectIsValid(attackObject)) {
        return;
    }
    


	this->bulletVector = this->updateFireVector(this->getPosition(), attackObject->getPosition());
    switch (towerType) {
        case GAME_TOWER_TYPE_ANCHOR:
        {
            //this->rotateTowerThenFire();
			if (!isTowerRotateToTarget && !isTowerRotating)
			{
				this->rotateTowerNow();
			}
			else if(!isTowerRotating)
			{
				towerSprite->setRotation(this->towerRoate);
			}
			
            
        }
            break;
        case GAME_TOWER_TYPE_ARROW:
        {
            //this->rotateTowerThenFire();
			if (!isTowerRotateToTarget && !isTowerRotating)
			{
				this->rotateTowerNow();
			}
			else if(!isTowerRotating)
			{
				towerSprite->setRotation(this->towerRoate);
			}
        }
            break;
        case GAME_TOWER_TYPE_BALL:
        {
            //this->FanStarTowerFire();
        }
            break;
        case GAME_TOWER_TYPE_BLUESTAR:
        {
            //this->FanStarTowerFire();
        }
            break;
        case GAME_TOWER_TYPE_BOTTLE:
        {
            //this->rotateTowerThenFire();
			if (!isTowerRotateToTarget && !isTowerRotating)
			{
				this->rotateTowerNow();
			}
			else if(!isTowerRotating)
			{
				towerSprite->setRotation(this->towerRoate);
			}
        }
            break;
        case GAME_TOWER_TYPE_BUFF:
        {
            
        }
            break;
        case GAME_TOWER_TYPE_CUTTLE:
        {
            //this->FanStarTowerFire();
        }
            break;
        case GAME_TOWER_TYPE_FAN:
        {
            //this->FanStarTowerFire();
        }
            break;
        case GAME_TOWER_TYPE_FIREBOTTLE:
        {
            //this->rotateTowerThenFire();
			if (!isTowerRotateToTarget && !isTowerRotating)
			{
				this->rotateTowerNow();
			}
			else if(!isTowerRotating)
			{
				towerSprite->setRotation(this->towerRoate);
			}
        }
            break;
        case GAME_TOWER_TYPE_FISH:
        {
            //this->rotateTowerThenFire();
			if (!isTowerRotateToTarget && !isTowerRotating)
			{
				this->rotateTowerNow();
			}
			else if(!isTowerRotating)
			{
				towerSprite->setRotation(this->towerRoate);
			}
        }
            break;
        case GAME_TOWER_TYPE_MUSHROOM:
        {
            //this->SunTowerFire();
        }
            break;
        case GAME_TOWER_TYPE_PIN:
        {
            //this->rotateTowerThenFire();
			if (!isTowerRotateToTarget && !isTowerRotating)
			{
				this->rotateTowerNow();
			}
			else if(!isTowerRotating)
			{
				towerSprite->setRotation(this->towerRoate);
			}
        }
            break;
        case GAME_TOWER_TYPE_PLANE:
        {
            //this->rotateTowerThenFire();
			if (!isTowerRotateToTarget && !isTowerRotating)
			{
				this->rotateTowerNow();
			}
			else if(!isTowerRotating)
			{
				towerSprite->setRotation(this->towerRoate);
			}
        }
            break;
        case GAME_TOWER_TYPE_ROCKET:
        {
            //this->rotateTowerThenFire();
			if (!isTowerRotateToTarget && !isTowerRotating)
			{
				this->rotateTowerNow();
			}
			else if(!isTowerRotating)
			{
				towerSprite->setRotation(this->towerRoate);
			}
        }
            break;
        case GAME_TOWER_TYPE_SHIT:
        {
            //this->FanStarTowerFire();
        }
            break;
        case GAME_TOWER_TYPE_SNOW:
        {
            //this->SunTowerFire();
        }
            break;
        case GAME_TOWER_TYPE_STAR:
        {
            //this->FanStarTowerFire();
        }
            break;
        case GAME_TOWER_TYPE_SUN:
        {
            //this->SunTowerFire();
        }
            break;
        default:
            break;
    }
}

void AttackTowerClass::update(float dt)
{
    this->checkCanAttackEenmy();
    this->updateTowerRotateByeEnemy();
    this->towerUpdateFire(dt);
}

