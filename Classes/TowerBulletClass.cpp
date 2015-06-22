//
//  TowerBulletClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-8-1.
//
//

#include "TowerBulletClass.h"
#include "CommonClass.h"
#include "TowerBulletEffectClass.h"
#include "LcdAdapClass.h"



TowerBulletClass::TowerBulletClass()
{
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(TowerBulletClass::enemyDeadNotification), ENEMY_DEAD_NOTIFICATION, NULL);
}

TowerBulletClass::~TowerBulletClass()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, ENEMY_DEAD_NOTIFICATION);

    if (bulletcomAct != NULL && bulletcomAct->retainCount() > 0) {
        bulletcomAct->release();
    }
    
    if (bulletAni != NULL && bulletAni->retainCount() > 0) {
        bulletAni->release();
    }
    
    targetObject = NULL;
    comFanArray->release();
}

void TowerBulletClass::enemyDeadNotification(CCObject *object)
{

}

bool TowerBulletClass::init(const char* fileName,EnemySpriteClass* object,float killValue)
{
    CCAssert(!(fileName == NULL), "cannot be NULL");
    CCAssert(!(object == NULL), "cannot be NULL");
    
    //ObjectClass::init(fileName);
    moveTime = 0.1f;
    isSpeed2X = false;
    isBulletPause = false;
    isDrawNow = false;
    targetObject = object;
    bulletKillValue = killValue;
    bulletParentPos = ccp(0,0);
    bulletParentSize = CCSizeMake(0, 0);
    bulletVector = CCPointZero;
    bulletEffectArray = NULL;
    enemyObjectArray = NULL;
    enemyMonsterArray = NULL;
    bulletArray = NULL;
    CCSprite::initWithSpriteFrameName(fileName);
//    this->setTargetPos(object->getPosition(), 200);
//    this->setIsCanMove(true);
    return true;
}

TowerBulletClass* TowerBulletClass::create(const char* fileName,EnemySpriteClass* object,float killValue)
{
    CCAssert(!(fileName == NULL), "cannot be NULL");
    CCAssert(!(object == NULL), "cannot be NULL");
    
    TowerBulletClass* bullet = new TowerBulletClass();
    if (bullet && bullet->init(fileName, object,killValue)) {
        bullet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(bullet);
    }
    return bullet;
}


bool TowerBulletClass::init(CCPoint pos,GAME_TOWER_TYPE tower,GAME_TOWER_UPDATE_TYPE type ,EnemySpriteClass* object)
{
    CCAssert(!(tower == GAME_TOWER_TYPE_NONE || tower == GAME_TOWER_TYPE_MAX), "cannot be NULL");
    CCAssert(!(object == NULL), "cannot be NULL");
    char pFileName[50] = {0};
    char buffer[50] = {0};
    char buffer2[100] = {0};
    
    moveTime = 0.1f;
    isSpeed2X = false;
    isBulletPause = false;
    targetObject = object;
    bulletKillValue = 5;
    bulletKillRadius = 100;
    toRealPos = ccp(0,0);
    selFunc = NULL;
    isCanHurtTarget = true;
    bulletParentType = tower;
    bulletSpeed = 1;
    bulletParentUpdateType = type;
    saveTargetSpeed = 50;
    enemyArray = NULL;
    bulletcomAct = NULL;
    timeCounter = 0;
    isAnchorDir = false;
    enemyMonsterArray = NULL;
    comFanArray = CCArray::create();
    comFanArray->retain();
    bulletArray = NULL;
    
    CCArray *animFrames = CCArray::create();
    int count = 0;
    int index = (type + 1) * 10 + 1;
    float aniTime = 0.01;
    
    switch (tower) {
        case GAME_TOWER_TYPE_ANCHOR:
            {
                sprintf(pFileName, "%s","PAnchor");
                count = 2;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_ANCHOR;
                aniTime = 0.25;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_ANCHOR;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_ANCHOR;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_ANCHOR;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_ARROW:
            {
                sprintf(pFileName, "%s","PArrow");
                count = 2;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_ARROW;
                aniTime = 0.25;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_ARROW;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_ARROW;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_ARROW;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_BALL:
            {
                sprintf(pFileName, "%s","PBall");
                count = 4;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_BALL;
                aniTime = 0.05;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_BALL;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_BALL;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_BALL;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_BLUESTAR:
            {
                sprintf(pFileName, "%s","PBStar");
                count = 1;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_BLUESTAR;
                aniTime = 0.25;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_BLUESTAR;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_BLUESTAR;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_BLUESTAR;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_BOTTLE:
            {
                sprintf(pFileName, "%s","PBottle");
                count = 3;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_BOTTLE;
                aniTime = 0.25;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_BOTTLE;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_BOTTLE;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_BOTTLE;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_BUFF:
            {
                sprintf(pFileName, "%s","PBuff");
                count = 5;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_BUFF;
                aniTime = 0.05;
                index = 11;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_BUFF;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_BUFF;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_BUFF;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_CUTTLE:
            {
                sprintf(pFileName, "%s","PCuttle");
                count = 2;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_CUTTLE;
                aniTime = 0.25;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_CUTTLE;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_CUTTLE;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_CUTTLE;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_FAN:
            {
                sprintf(pFileName, "%s","PFan");
                count = 1;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_FAN;
                selFunc = callfunc_selector(TowerBulletClass::setFanTarget);
                aniTime = 0.25;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_FAN;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_FAN;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_FAN;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_FIREBOTTLE:
            {
                sprintf(pFileName, "%s","PFBottle");
                count = 2;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_FIREBOTTLE;
                aniTime = 0.01;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_FIREBOTTLE;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_FIREBOTTLE;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_FIREBOTTLE;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_FISH:
            {
                sprintf(pFileName, "%s","PFish");
                count = 1;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_FISH;
                aniTime = 0.25;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_FISH;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_FISH;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_FISH;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_MUSHROOM:
            {
                sprintf(pFileName, "%s","PMushroom");
                count = 5;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_MUSHROOM;
                aniTime = 0.05;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_MUSHROOM;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_MUSHROOM;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_MUSHROOM;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_PIN:
            {
                sprintf(pFileName, "%s","PPin");
                count = 2;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_PIN;
                aniTime = 0.25;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_PIN;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_PIN;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_PIN;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_PLANE:
            {
                sprintf(pFileName, "%s","PPlane");
                count = 3;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_PLANE;
                aniTime = 0.02;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_PLANE;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_PLANE;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_PLANE;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_ROCKET:
            {
                sprintf(pFileName, "%s","PRocket");
                count = 5;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_ROCKET;
                aniTime = 0.25;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_ROCKET;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_ROCKET;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_ROCKET;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_SHIT:
            {
                sprintf(pFileName, "%s","PShit");
                count = 2;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_SHIT;
                aniTime = 0.25;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_SHIT;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_SHIT;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_SHIT;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_SNOW:
            {
                sprintf(pFileName, "%s","PSnow");
                count = 5;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_SNOW;
                aniTime = 0.1;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_SNOW;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_SNOW;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_SNOW;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_STAR:
            {
                sprintf(pFileName, "%s","PStar");
                count = 1;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_STAR;
                aniTime = 0.25;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_STAR;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_STAR;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_STAR;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GAME_TOWER_TYPE_SUN:
            {
                sprintf(pFileName, "%s","PSun");
                count = 5;
                bulletSpeed = GAME_TOWER_BULLET_SPEED_SUN;
                selFunc = callfunc_selector(TowerBulletClass::setSunTarget);
                aniTime = 0.1;
                switch (bulletParentUpdateType) {
                    case GAME_TOWER_UPDATE_TYPE_ZERO:
                        bulletKillValue = GAME_TOWER_UPDATEONE_BULLET_KILLVALUE_SUN;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_ONE:
                        bulletKillValue = GAME_TOWER_UPDATETWO_BULLET_KILLVALUE_SUN;
                        break;
                    case GAME_TOWER_UPDATE_TYPE_TWO:
                        bulletKillValue = GAME_TOWER_UPDATETHREE_BULLET_KILLVALUE_SUN;
                        break;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }

    
    //if (count > 1)
    {
        for (int i = index; i < (index + count); i++) {
            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "%s%d.png",pFileName,i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            animFrames->addObject(frame);
        }
        bulletAni = CCAnimation::createWithSpriteFrames(animFrames, aniTime);
        bulletAni->retain();
        memset(buffer2, 0, sizeof(buffer2));
        sprintf(buffer2, "%s%d.png",pFileName,index);
        CCSprite::initWithSpriteFrameName(buffer2);
        this->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
        this->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());
    }
    comActTime = 0.1;
    this->setPosition(pos);
    this->setCommonTarget();
    return true;
}


TowerBulletClass* TowerBulletClass::create(CCPoint pos,GAME_TOWER_TYPE tower,GAME_TOWER_UPDATE_TYPE type ,EnemySpriteClass* object)
{
    CCAssert(!(tower == GAME_TOWER_TYPE_NONE || tower == GAME_TOWER_TYPE_MAX), "cannot be NULL");
    CCAssert(!(object == NULL), "cannot be NULL");
    
    TowerBulletClass* bullet = new TowerBulletClass();
    if (bullet && bullet->init(pos,tower,type,object)) {
        bullet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(bullet);
    }
    return bullet;
}

bool TowerBulletClass::init(cocos2d::CCPoint pos, GAME_TOWER_TYPE tower, GAME_TOWER_UPDATE_TYPE type, EnemySpriteClass *object, cocos2d::CCPoint targetPos)
{
    toTargetPos = targetPos;
    this->init(pos, tower, type, object);
    
    return true;
}

TowerBulletClass* TowerBulletClass::create(CCPoint pos,GAME_TOWER_TYPE tower,GAME_TOWER_UPDATE_TYPE type ,EnemySpriteClass* object,CCPoint targetPos)
{
    CCAssert(!(tower == GAME_TOWER_TYPE_NONE || tower == GAME_TOWER_TYPE_MAX), "cannot be NULL");
    CCAssert(!(object == NULL), "cannot be NULL");
    
    TowerBulletClass* bullet = new TowerBulletClass();
    if (bullet && bullet->init(pos,tower,type,object,targetPos)) {
        bullet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(bullet);
    }
    return bullet;
}


void TowerBulletClass::setEnemyArray(cocos2d::CCArray *enemy)
{
    if (enemy) {
        enemyArray = enemy;
    }
}

void TowerBulletClass::setBulletKillRadius(float value)
{
    bulletKillRadius = value * LcdAdapClass::sharedLCDADAP()->getTowerKillRadiusScale();
    
}

void TowerBulletClass::setBulletEffectArray(cocos2d::CCArray *effect)
{
    if (effect != NULL) {
        bulletEffectArray = effect;
    }
}

bool TowerBulletClass::checkEenemyIsCanAttackedBySunSnow()
{
    bool flag = false;
    if (enemyArray && (enemyArray->count() > 0)) {
        if (bulletParentType == GAME_TOWER_TYPE_SUN || bulletParentType == GAME_TOWER_TYPE_SNOW || bulletParentType == GAME_TOWER_TYPE_MUSHROOM || bulletParentType == GAME_TOWER_TYPE_PLANE) {
            
            for (int i = 0; i < enemyArray->count(); i++) {
                EnemySpriteClass* enemy = (EnemySpriteClass*)enemyArray->objectAtIndex(i);
                if (enemy && !enemy->getIsDead() && enemy->retainCount() > 0) {
                    
                    CCPoint enemyPos = enemy->getPosition();
                    CCPoint bulletPos = this->getPosition();
                    CCPoint subPos = ccpSub(enemyPos, bulletPos);
                    
                    
                    switch (bulletParentType) {
                        case GAME_TOWER_TYPE_SUN:
                            {
                                if (ccpLength(subPos) <= bulletKillRadius) {
                                    int lifeValue = enemy->getCurLifeValue();
                                    
                                    TowerBulletEffect* effect = TowerBulletEffect::create(GAME_TOWER_TYPE_SUN, bulletParentUpdateType, enemy);
									effect->setIsSpeed2X(isSpeed2X);
                                    this->getParent()->addChild(effect);
                                    if (bulletEffectArray) {
                                        bulletEffectArray->addObject(effect);
                                    }
                                    
                                    lifeValue -= this->bulletKillValue;
                                    if (lifeValue > 0) {
                                        enemy->setCurLifeValue(lifeValue);
                                        enemy->setIsAttacked(true);
                                    }
                                    else
                                    {
                                        enemy->setCurLifeValue(-1);
                                    }
                                    
                                }
                                
                            }
                            break;
                        case GAME_TOWER_TYPE_PLANE:
                        {
                            
                            if (this->checkEnemyIsLineCollion(enemy->getPosition(), enemy->getContentSize())) {
                                
                                int lifeValue = enemy->getCurLifeValue();
                                
                                TowerBulletEffect* effect = TowerBulletEffect::create(GAME_TOWER_TYPE_PLANE, bulletParentUpdateType, enemy);
                                effect->setIsSpeed2X(isSpeed2X);
                                this->getParent()->addChild(effect);
                                if (bulletEffectArray) {
                                    bulletEffectArray->addObject(effect);
                                }
                                
                                lifeValue -= this->bulletKillValue;
                                if (lifeValue > 0) {
                                    enemy->setCurLifeValue(lifeValue);
                                    enemy->setIsAttacked(true);
                                }
                                else
                                {
                                    enemy->setCurLifeValue(-1);
                                }
                                
                            }
                            
                        }
                            break;
                        case GAME_TOWER_TYPE_SNOW:
                            {
                                if ((ccpLength(subPos) <= bulletKillRadius) && (!enemy->getIsAttackedBySnow())) {

                                    int lifeValue = enemy->getCurLifeValue();
                                    
                                    if (enemy->getEnemyType() == GAME_ENEMY_TYPE_MONSTERS) {
                                        TowerBulletEffect* effect = TowerBulletEffect::create(GAME_TOWER_TYPE_SNOW, bulletParentUpdateType, enemy);
                                        effect->setIsSpeed2X(isSpeed2X);
										enemy->pauseSchedulerAndActions();
                                        enemy->setIsAttackedBySnow(true);
                                        this->getParent()->addChild(effect);
                                        if (bulletEffectArray) {
                                            bulletEffectArray->addObject(effect);
                                        }
                                    }
                                    
                                    lifeValue -= this->bulletKillValue;
                                    if (lifeValue > 0) {
                                        enemy->setCurLifeValue(lifeValue);
                                        enemy->setIsAttacked(true);
                                    }
                                    else
                                    {
                                        enemy->setCurLifeValue(-1);
                                    }
                                    
                                }
                            }
                            break;
                        case GAME_TOWER_TYPE_MUSHROOM:
                            {
                                if (ccpLength(subPos) <= bulletKillRadius) {
                                    
                                    int lifeValue = enemy->getCurLifeValue();
                                    
                                    if (enemy->getEnemyType() == GAME_ENEMY_TYPE_MONSTERS && !enemy->getIsAttackedByMushRoom()) {
                                        
                                        TowerBulletEffect* effect = TowerBulletEffect::create(GAME_TOWER_TYPE_MUSHROOM, bulletParentUpdateType, enemy);
                                        effect->setIsSpeed2X(isSpeed2X);
										this->getParent()->addChild(effect);
                                        enemy->setScale(0.8);
                                        effect->setsaveEnemyMoveSpeed(enemy->getMoveSpeed());
                                        enemy->setEnemySpeed(enemy->getMoveSpeed() / 2);
                                        enemy->setIsAttackedByMushRoom(true);
                                        if (bulletEffectArray) {
                                            bulletEffectArray->addObject(effect);
                                        }
                                    }
                                    lifeValue -= this->bulletKillValue;
                                    if (lifeValue > 0) {
                                        enemy->setCurLifeValue(lifeValue);
                                        enemy->setIsAttacked(true);
                                    }
                                    else
                                    {
                                        enemy->setCurLifeValue(-1);
                                    }
                                    
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
    
    return flag;
}

void TowerBulletClass::setShotTarget()
{
//    if (targetObject && !targetObject->getIsDead()  && targetObject->retainCount() > 0) {
//        
//        moveTime = CommonClass::getSharedCommon()->ConvertSpeedToTime(ccpLength(ccpSub(targetObject->getPosition(), this->getPosition())), bulletSpeed);
//        CCActionInterval* moveto = CCMoveTo::create(moveTime, targetObject->getPosition());
//        CCCallFuncN* callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletClass::toTargetObjectCallBack));
//        if (bulletAni) {
//            this->runAction(CCSpawn::create(CCAnimate::create(bulletAni),(CCActionInterval*)CCSequence::create(moveto,callfunc,NULL),NULL));
//        }
//        else
//        {
//            this->runAction((CCActionInterval*)CCSequence::create(moveto,callfunc,NULL));
//        }
//    }
//    else
//    {
//        this->removeFromParentAndCleanup(true);
//    }
}

void TowerBulletClass::setFanTarget()
{
	if (targetObject && !targetObject->getIsDead()  && targetObject->retainCount() > 0) {
		toRealPos = CommonClass::getSharedCommon()->getGameFromToRealPos(this->getPosition(),targetObject->getPosition());
        moveTime = CommonClass::getSharedCommon()->ConvertSpeedToTime(ccpLength(ccpSub(toRealPos, this->getPosition())), bulletSpeed);
		CCActionInterval* moveto = CCMoveTo::create(moveTime, toRealPos);
        CCActionInterval* rotate = CCRotateBy::create(0.1, 45);
		CCCallFuncN* callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletClass::toTargetFanCallBack));
		if (bulletAni) {
            this->runAction(CCRepeatForever::create(rotate));
            this->runAction(CCSpawn::create(CCAnimate::create(bulletAni),(CCActionInterval*)CCSequence::create(moveto,callfunc,NULL),NULL));
		}
		else
		{
//			this->runAction((CCActionInterval*)CCSequence::create(moveto,callfunc,NULL));
            this->runAction(CCSpawn::create(CCAnimate::create(bulletAni),(CCActionInterval*)CCSequence::create(moveto,callfunc,NULL),NULL));
		}
	}
    else
    {
        if (bulletArray != NULL && bulletArray->count() > 0) {
            bulletArray->removeObject(this);
        }
        this->removeFromParentAndCleanup(true);
    }
}

void TowerBulletClass::toTargetFanCallBack(CCNode* parent)
{
    this->stopAllActions();
    if (bulletArray != NULL && bulletArray->count() > 0) {
        bulletArray->removeObject(this);
    }
    this->removeFromParentAndCleanup(true);
}

void TowerBulletClass::setSunTarget()
{
    if (targetObject && !targetObject->getIsDead() && targetObject->retainCount() > 0){
        if (bulletAni) {
            this->runAction((CCActionInterval*)CCSequence::create(CCAnimate::create(bulletAni),CCCallFuncN::create(this, callfuncN_selector(TowerBulletClass::toTargetSunCallBack)),NULL));
        }
    
    }
    else
    {
        if (bulletArray != NULL && bulletArray->count() > 0) {
            bulletArray->removeObject(this);
        }
        this->removeFromParentAndCleanup(true);
    }
}

void TowerBulletClass::toTargetSunCallBack(cocos2d::CCNode *parent)
{
    this->stopAllActions();
    if (bulletArray != NULL && bulletArray->count() > 0) {
        bulletArray->removeObject(this);
    }
    this->removeFromParentAndCleanup(true);
}


void TowerBulletClass::setCommonTarget()
{
    {
        //if (targetObject && !targetObject->getIsDead()  && targetObject->retainCount() > 0)
        {
            
            toRealPos = CommonClass::getSharedCommon()->getGameFromToRealPos(this->getPosition(),targetObject->getPosition());

            switch (bulletParentType) {
                case GAME_TOWER_TYPE_ANCHOR:
                {
                    bulletcomAct = CCRepeatForever::create(CCRotateBy::create(0.1, 45));
                    bulletcomAct->retain();
                    toRealPos = targetObject->getPosition();
                    comActTime = 0.1;
                }
                    break;
                case GAME_TOWER_TYPE_ARROW:
                {

                    toRealPos = toTargetPos;
                    
                }
                    break;
                case GAME_TOWER_TYPE_BALL:
                {
                    float len = ccpLength(ccpSub(this->getPosition(), targetObject->getPosition()));
                    float ratio = len / (this->getContentSize().height);
                    this->setScaleY(ratio);
                    CCPoint delta = ccpSub(targetObject->getPosition(), this->getPosition());
                    float at = (float) CC_RADIANS_TO_DEGREES( atanf( delta.x/delta.y) );
                    CCPoint newPos = ccpAdd(this->getPosition(), ccpMult(ccpNormalize(delta), (this->getContentSize().height / 2) * ratio));
                    if( delta.y < 0 )
                    {
                        if(  delta.x < 0 )
                            at = 180 + (at);
                        else
                            at = 180 - fabs(at);
                    }
                    
                    this->setPosition(newPos);
                    this->setRotation(at);
                    toRealPos = targetObject->getPosition();
                }
                    break;
                case GAME_TOWER_TYPE_BLUESTAR:
                {
                    bulletcomAct = CCRepeatForever::create(CCRotateBy::create(0.1, 45));
                    bulletcomAct->retain();
                    comActTime = 0.1;
                }
                    break;
                case GAME_TOWER_TYPE_BOTTLE:
                {
                    toRealPos = targetObject->getPosition();
                }
                    break;
                case GAME_TOWER_TYPE_BUFF:
                {
                    bulletcomAct = CCRepeatForever::create(CCRotateBy::create(0.1, 45));
                    bulletcomAct->retain();
                    comActTime = 0.1;
                }
                    break;
                case GAME_TOWER_TYPE_CUTTLE:
                {
                    toRealPos = toTargetPos;
                }
                    break;
                case GAME_TOWER_TYPE_FAN:
                {
                    bulletcomAct = CCRepeatForever::create(CCRotateBy::create(0.1, 45));
                    bulletcomAct->retain();
                    comActTime = 0.1;
                }
                    break;
                case GAME_TOWER_TYPE_FIREBOTTLE:
                {
                    float len = ccpLength(ccpSub(this->getPosition(), targetObject->getPosition()));
                    CCSize bulletSize = this->getContentSize();
                    
                    float ratio = 0;
                    CCPoint delta = ccpSub(toRealPos, this->getPosition());
                    float at = (float) CC_RADIANS_TO_DEGREES( atanf( delta.x/delta.y) );
                    CCPoint newPos = CCPointZero;
                    
//                    bulletSize.width *= LcdAdapClass::sharedLCDADAP()->getXScale();
//                    bulletSize.height *= LcdAdapClass::sharedLCDADAP()->getYScale();
                    
                    ratio = (len + bulletSize.height/2.0)/ bulletSize.height;
                    this->setScaleY(ratio);
                    if (len > bulletSize.height/2) {
                        newPos = ccpAdd(this->getPosition(), ccpMult(ccpNormalize(delta), len/2.0 - bulletSize.height/4.0));
                    }
                    else
                    {
                        
                        newPos = ccpSub(this->getPosition(), ccpMult(ccpNormalize(delta), bulletSize.height/4.0 - len/2.0));
                    }
                    
                    if( delta.y < 0 )
                    {
                        if(  delta.x < 0 )
                            at = 180 + (at);
                        else
                            at = 180 - fabs(at);
                    }
                    
                    this->setPosition(newPos);
                    this->setRotation(at);
                    toRealPos = targetObject->getPosition();
                }
                    break;
                case GAME_TOWER_TYPE_FISH:
                {
                    CCPoint delta = ccpSub(targetObject->getPosition(), this->getPosition());
                    float at = (float) CC_RADIANS_TO_DEGREES( atanf( delta.x/delta.y) );
                    if( delta.y < 0 )
                    {
                        if(  delta.x < 0 )
                            at = 180 + (at);
                        else
                            at = 180 - fabs(at);
                    }
                    
                    this->setRotation(at);
                    toRealPos = targetObject->getPosition();
                }
                    break;
                case GAME_TOWER_TYPE_MUSHROOM:
                {

                }
                    break;
                case GAME_TOWER_TYPE_PIN:
                {
                    CCPoint delta = ccpSub(targetObject->getPosition(), this->getPosition());
                    float at = (float) CC_RADIANS_TO_DEGREES( atanf( delta.x/delta.y) );
                    if( delta.y < 0 )
                    {
                        if(  delta.x < 0 )
                            at = 180 + (at);
                        else
                            at = 180 - fabs(at);
                    }
                    
                    this->setRotation(at);
                    toRealPos = targetObject->getPosition();
                }
                    break;
                case GAME_TOWER_TYPE_PLANE:
                {
                    CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
                    CCSize bulletSize = this->getContentSize();
                    
//                    bulletSize.width *= LcdAdapClass::sharedLCDADAP()->getXScale();
//                    bulletSize.height *= LcdAdapClass::sharedLCDADAP()->getYScale();
                    
                    float maxLen = MAX(size.width, size.height);
                    float ratio = maxLen / bulletSize.height;
                    this->setScaleY(ratio);
                    CCPoint delta = ccpSub(toRealPos, this->getPosition());
                    float at = (float) CC_RADIANS_TO_DEGREES( atanf( delta.x/delta.y) );
                    CCPoint newPos = ccpAdd(this->getPosition(), ccpMult(ccpNormalize(delta), bulletSize.height/2 * ratio));
                    if( delta.y < 0 )
                    {
                        if(  delta.x < 0 )
                            at = 180 + (at);
                        else
                            at = 180 - fabs(at);
                    }
                    bulletVector = ccpNormalize(CCPoint(delta.x, delta.y));
                    this->setPosition(newPos);
                    this->setRotation(at);
                    
                }
                    break;
                case GAME_TOWER_TYPE_ROCKET:
                {
                    CCPoint delta = ccpSub(toRealPos, this->getPosition());
                    float at = (float) CC_RADIANS_TO_DEGREES( atanf( delta.x/delta.y) );
                    if( delta.y < 0 )
                    {
                        if(  delta.x < 0 )
                            at = 180 + (at);
                        else
                            at = 180 - fabs(at);
                    }
                    
                    this->setRotation(at);
                    
                }
                    break;
                case GAME_TOWER_TYPE_SHIT:
                {
                    CCPoint delta = ccpSub(targetObject->getPosition(), this->getPosition());
                    float at = (float) CC_RADIANS_TO_DEGREES( atanf( delta.x/delta.y) );
                    if( delta.y < 0 )
                    {
                        if(  delta.x < 0 )
                            at = 180 + (at);
                        else
                            at = 180 - fabs(at);
                    }
                    
                    this->setRotation(at);
                    toRealPos = targetObject->getPosition();
                }
                    break;
                case GAME_TOWER_TYPE_SNOW:
                {
                    
                }
                    break;
                case GAME_TOWER_TYPE_STAR:
                {
                    bulletcomAct = CCRepeatForever::create(CCRotateBy::create(0.1, 45));
                    bulletcomAct->retain();
                    toRealPos = targetObject->getPosition();
                    comActTime = 0.1;
                }
                    break;
                case GAME_TOWER_TYPE_SUN:
                {

                }
                    break;
                default:
                    break;
            }
            
            this->setCommonAction();
        }
    }
}

void TowerBulletClass::setCommonAction()
{
    
    moveTime = CommonClass::getSharedCommon()->ConvertSpeedToTime(ccpLength(ccpSub(toRealPos, this->getPosition())), bulletSpeed);
    
    if(bulletParentType == GAME_TOWER_TYPE_PLANE || bulletParentType == GAME_TOWER_TYPE_SUN || bulletParentType == GAME_TOWER_TYPE_FIREBOTTLE || bulletParentType == GAME_TOWER_TYPE_BALL || bulletParentType == GAME_TOWER_TYPE_MUSHROOM || bulletParentType == GAME_TOWER_TYPE_SNOW)
    {
        
        if (bulletParentType == GAME_TOWER_TYPE_FIREBOTTLE || bulletParentType == GAME_TOWER_TYPE_BALL) {
            
            this->runAction(CCRepeatForever::create(CCAnimate::create(bulletAni)));
            this->unscheduleUpdate();
            this->scheduleUpdate();
        }
        else
        {
            CCCallFuncN* callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletClass::toTargetCommonCallBack));
            this->runAction((CCActionInterval*)CCSequence::create(CCAnimate::create(bulletAni),callfunc,NULL));
        }
    }
    else
    {
        CCActionInterval* moveto = CCMoveTo::create(moveTime, toRealPos);
        
        CCCallFuncN* callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletClass::toTargetCommonCallBack));
        if (bulletcomAct) {
            this->runAction(bulletcomAct);
        }
        if (bulletAni) {
            
            this->runAction(CCSpawn::create(CCAnimate::create(bulletAni),(CCActionInterval*)CCSequence::create(moveto,callfunc,NULL),NULL));
            //this->runAction(CCAnimate::create(bulletAni));
        }
        else
        {
            this->runAction((CCActionInterval*)CCSequence::create(moveto,callfunc,NULL));
        }
        if (bulletParentType == GAME_TOWER_TYPE_FAN || bulletParentType == GAME_TOWER_TYPE_ROCKET || bulletParentType == GAME_TOWER_TYPE_BLUESTAR || bulletParentType == GAME_TOWER_TYPE_CUTTLE || bulletParentType == GAME_TOWER_TYPE_ARROW || bulletParentType == GAME_TOWER_TYPE_BUFF)
        {
            targetObject = NULL;
            this->unscheduleUpdate();
            this->scheduleUpdate();
        }
        
    }

}

void TowerBulletClass::toTargetCommonCallBack(cocos2d::CCNode *parent)
{
    CCLOG("bullet to target pos");
    
    if (bulletParentType == GAME_TOWER_TYPE_BOTTLE || bulletParentType == GAME_TOWER_TYPE_ANCHOR
      || bulletParentType == GAME_TOWER_TYPE_FISH || bulletParentType == GAME_TOWER_TYPE_PIN || bulletParentType == GAME_TOWER_TYPE_SHIT || bulletParentType == GAME_TOWER_TYPE_STAR) {
        
        bool isEnemyValid = false;//真实的检测敌军是否有效，有时候由于mainui update的原因，会导致这里不同步
        
        if (enemyArray != NULL && (enemyArray->count() > 0)) {
            for (int i = 0; i < enemyArray->count(); i++) {
                EnemySpriteClass* enemy = (EnemySpriteClass*)enemyArray->objectAtIndex(i);
                if (enemy == targetObject) {
                    isEnemyValid = true;
                    break;
                }
            }
        }
        
        
            if (isEnemyValid &&targetObject && !(targetObject->getIsDead())  && targetObject->retainCount() > 0)
            {
                
                int lifeValue = targetObject->getCurLifeValue();
                
                TowerBulletEffect* effect = TowerBulletEffect::create(bulletParentType,bulletParentUpdateType,targetObject);
                effect->setIsSpeed2X(isSpeed2X);
                this->getParent()->addChild(effect);
                if (bulletEffectArray) {
                    bulletEffectArray->addObject(effect);
                }
                
                lifeValue -= bulletKillValue;
                if (lifeValue > 0) {
                    targetObject->setCurLifeValue(lifeValue);
                    targetObject->setIsAttacked(true);
                }
                else
                {
                    targetObject->setCurLifeValue(-1);
                }
                
                if (bulletParentType == GAME_TOWER_TYPE_ANCHOR && targetObject->getEnemyType() == GAME_ENEMY_TYPE_MONSTERS && (enemyObjectArray != NULL &&  enemyObjectArray->count() > 0)) {
                    
                    int count = enemyObjectArray->count();
                    
                    int index = CCRANDOM_0_1() * count;
                    if (index >= count) {
                        index = count - 1;//
                    }
                    
                    EnemySpriteClass* object = (EnemySpriteClass*)enemyObjectArray->objectAtIndex(index);
                    
                    if (!object->getIsDead()) {
                        float time = ccpLength(ccpSub(this->getPosition(), object->getPosition())) / bulletSpeed;
                        
                        CCMoveTo* mto = CCMoveTo::create(time, object->getPosition());
                        this->runAction(CCSequence::create(mto,CCCallFunc::create(this, callfunc_selector(TowerBulletClass::anchorSecToTargetCallBack)),NULL));
                        targetObject = object;
                    }
                    else
                    {
                        if (bulletArray != NULL && bulletArray->count() > 0) {
                            bulletArray->removeObject(this);
                        }
                        this->removeFromParentAndCleanup(true);
                        return;
                    }
                    
                    return;
                }
                else
                {
                    if (bulletArray != NULL && bulletArray->count() > 0) {
                        bulletArray->removeObject(this);
                    }
                    this->removeFromParentAndCleanup(true);
                    return;
                }
        }
        else
        {
            if (bulletArray != NULL && bulletArray->count() > 0) {
                bulletArray->removeObject(this);
            }
            this->removeFromParentAndCleanup(true);
            return;
        }
            
    }
    if(bulletParentType != GAME_TOWER_TYPE_FIREBOTTLE && bulletParentType != GAME_TOWER_TYPE_BALL)
    {
        this->stopAllActions();
        if (bulletArray != NULL && bulletArray->count() > 0) {
            bulletArray->removeObject(this);
        }
        
    }
    switch (bulletParentType) {
        case GAME_TOWER_TYPE_ANCHOR:
        {
            this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_ARROW:
        {
            this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_BALL:
        {
            //this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_BLUESTAR:
        {
            this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_BOTTLE:
        {
            this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_BUFF:
        {
            this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_CUTTLE:
        {
            this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_FAN:
        {
            this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_FIREBOTTLE:
        {
            //this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_FISH:
        {
            this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_MUSHROOM://PMushroom01.png
        {

            this->checkEenemyIsCanAttackedBySunSnow();
            this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_PIN:
        {

            this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_PLANE:
        {
            this->checkEenemyIsCanAttackedBySunSnow();
            this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_ROCKET:
        {

            this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_SHIT:
        {

            this->checkEenemyIsCanAttackedBySunSnow();
            this->removeFromParentAndCleanup(true);
            

        }
            break;
        case GAME_TOWER_TYPE_SNOW:
        {

            this->checkEenemyIsCanAttackedBySunSnow();
            this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_STAR:
        {
            this->removeFromParentAndCleanup(true);
        }
            break;
        case GAME_TOWER_TYPE_SUN:
        {
            this->checkEenemyIsCanAttackedBySunSnow();
            this->removeFromParentAndCleanup(true);
        }
            break;
        default:
            break;
    }
    
    isCanHurtTarget = false;
    //this->removeFromParentAndCleanup(true);
    
}


//void TowerBulletClass::setBulletValid()
//{
//    if (targetObject) {
//        CCActionInterval* moveto = CCMoveTo::create(moveTime, targetObject->getPosition());
//        CCCallFuncN* callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletClass::toTargetObjectCallBack));
//        this->runAction((CCActionInterval*)CCSequence::create(moveto,callfunc,NULL));
//    }
//}

void TowerBulletClass::toTargetObjectCallBack(cocos2d::CCNode *parent)
{
    CCLOG("bullet to target pos");
    
//    if (targetObject && !(targetObject->getIsDead())) {
//        int lifeValue = targetObject->getCurLifeValue();
//        lifeValue -= bulletKillValue;
//        targetObject->setCurLifeValue(lifeValue);
////        targetObject->setCurLifeValue(lifeValue);
//        targetObject->setIsAttacked(true);
//    }
//    isCanHurtTarget = false;
    if (bulletArray != NULL && bulletArray->count() > 0) {
        bulletArray->removeObject(this);
    }
    this->removeFromParentAndCleanup(true);
}

void TowerBulletClass::anchorSecToTargetCallBack()
{
    CCLOG("bullet to target pos");
    
    bool isValid = false;
    
    if (enemyObjectArray != NULL) {
        for (int i = 0; i < enemyObjectArray->count(); i++) {
            EnemySpriteClass* object = (EnemySpriteClass*)enemyObjectArray->objectAtIndex(i);
            if (object == targetObject) {
                isValid = true;
                break;
            }
        }
    }
    
    if (isValid && targetObject && !(targetObject->getIsDead())) {
        TowerBulletEffect* effect = TowerBulletEffect::create(bulletParentType,bulletParentUpdateType,targetObject);
        effect->setIsSpeed2X(isSpeed2X);
        this->getParent()->addChild(effect);
        if (bulletEffectArray) {
            bulletEffectArray->addObject(effect);
        }
        
        int lifeValue = targetObject->getCurLifeValue();
        
        lifeValue -= bulletKillValue;
        if (lifeValue > 0) {
            targetObject->setCurLifeValue(lifeValue);
            targetObject->setIsAttacked(true);
        }
        else
        {
            targetObject->setCurLifeValue(-1);
        }
    }
    //    isCanHurtTarget = false;
    if (bulletArray != NULL && bulletArray->count() > 0) {
        bulletArray->removeObject(this);
    }
    this->removeFromParentAndCleanup(true);
}

void TowerBulletClass::ToTargetPosCallBack()
{
//    if (targetObject && !(targetObject->getIsDead())) {
//        float lifeValue = targetObject->getCurLifeValue();
//        lifeValue -= bulletKillValue;
//        targetObject->setCurLifeValue(lifeValue);
//        targetObject->setIsAttacked(true);
//    }
//    this->setIsCanMove(false);
//    this->removeFromParentAndCleanup(true);
}


void TowerBulletClass::setIsSpeed2X(bool flag)
{
	isSpeed2X = flag;
    
    this->stopAllActions();
    if (!flag) {
        bulletSpeed = bulletSpeed / 2.0;
        comActTime = comActTime * 2;
    }
    else
    {
        bulletSpeed = bulletSpeed * 2;
        comActTime = comActTime / 2.0;
    }
    
    if (bulletcomAct && bulletcomAct->retainCount() > 0)
    {
        bulletcomAct->release();
        bulletcomAct = CCRepeatForever::create(CCRotateBy::create(comActTime, 45));
        bulletcomAct->retain();
    }
    
    
    this->setCommonAction();
}

bool TowerBulletClass::getIsSpeed2X()
{
    return isSpeed2X;
}

void TowerBulletClass::setIsBulletPause(bool flag)
{
    isBulletPause = flag;
    
    this->stopAllActions();
    if (flag) {
        this->unscheduleUpdate();
        if (bulletAni && bulletParentType != GAME_TOWER_TYPE_SUN && bulletParentType != GAME_TOWER_TYPE_SNOW && bulletParentType != GAME_TOWER_TYPE_MUSHROOM) {
            this->runAction(CCRepeatForever::create(CCAnimate::create(bulletAni)));
        }
        if (bulletcomAct != NULL) {
            this->runAction(bulletcomAct);
        }
//        this->runEffect();
    }
    else
    {
        this->setCommonAction();
    }
}

bool TowerBulletClass::getIsBulletPause()
{
    return isBulletPause;
}

void TowerBulletClass::runEffect()
{
    
}

void TowerBulletClass::stopEffect()
{
    
}

void TowerBulletClass::setBulletParentPosAndSize(cocos2d::CCPoint pos, cocos2d::CCSize size)
{
    bulletParentSize = CCSize(size.width * LcdAdapClass::sharedLCDADAP()->getXScale(), size.height * LcdAdapClass::sharedLCDADAP()->getYScale());
    bulletParentPos = pos;
}

void TowerBulletClass::setEnemyObjectArray(cocos2d::CCArray *object)
{
    CCAssert(!(object == NULL), "cannote be NULL");
    
    enemyObjectArray = object;
}

void TowerBulletClass::setEnemyMonsterArray(cocos2d::CCArray *monster)
{
    CCAssert(!(monster == NULL), "cannote be NULL");
    
    enemyMonsterArray = monster;
}


GAME_TOWER_TYPE TowerBulletClass::getBulletParentTowerType()
{
    return bulletParentType;
}

void TowerBulletClass::setBulletArray(cocos2d::CCArray *array)
{
    bulletArray = array;
}

bool TowerBulletClass::checkAttackedEnemey(EnemySpriteClass *enemy)
{
//    if (enemy && !enemy->getIsDead() && isCanHurtTarget) {
//        CCSize enemySize = enemy->getContentSize();
//        CCPoint enemyPos = enemy->getPosition();
//        CCRect enemyRect = CCRect(enemyPos.x - enemySize.width / 2, enemyPos.y - enemySize.height / 2, enemySize.width, enemySize.height);
//        //CCSize bulletSize = this->getContentSize();
//        CCPoint bulletPos = this->getPosition();
//        CCRect bulletRect = CCRect(bulletPos.x - bulletKillRadius, bulletPos.y - bulletKillRadius, bulletKillRadius, bulletKillRadius);
//        switch (bulletParentType) {
//            case GAME_TOWER_TYPE_BOTTLE:
//            case GAME_TOWER_TYPE_FISH:
//                {
//                    if (bulletRect.intersectsRect(enemyRect)) {
//                        int lifeValue = enemy->getCurLifeValue() - this->bulletKillValue;
//                        enemy->setCurLifeValue(lifeValue);
//                        isCanHurtTarget = false;
//                        return false;
//                    }
//                }
//                break;
//                
//            default:
//                break;
//        }
//        return false;
//    }
    return false;
}

bool TowerBulletClass::checkEnemyIsLineCollion(cocos2d::CCPoint enemyPos, cocos2d::CCSize enemySize)
{
    bool isCollion = false;
    
    
    float at = this->getRotation();
    float PAI = 3.1415926;
    float bulletWidth = this->getContentSize().width * LcdAdapClass::sharedLCDADAP()->getXScale();
    float bulletHeight = this->getContentSize().height * LcdAdapClass::sharedLCDADAP()->getYScale();
    float bulletMaxX = 0;
    float bulletMinX = 0;
    float bulletMaxY = 0;
    float bulletMinY = 0;
    float enemyWidth = enemySize.width * LcdAdapClass::sharedLCDADAP()->getXScale();
    float enemyHeight = enemySize.height * LcdAdapClass::sharedLCDADAP()->getYScale();

    
    CCRect enemyRec = CCRect(enemyPos.x - (enemyWidth / 2.0), enemyPos.y - (enemyHeight / 2.0), enemyWidth, enemyHeight);
    CCRect bulletRec;
    
    CCPoint posBuffer[] = {
        ccp(0,0),//origin
        ccp(0,0),//rightbottom
        ccp(0,0),//rightTop
        ccp(0,0),//leftTop
    };
    
    CCPoint enemyPosBuffer[] = {
        enemyRec.origin,
        ccp(enemyRec.origin.x + enemyRec.size.width,enemyRec.origin.y),
        ccp(enemyRec.origin.x + enemyRec.size.width,enemyRec.origin.y + enemyRec.size.height),
        ccp(enemyRec.origin.x,enemyRec.origin.y + enemyRec.size.height),
    };
    
    
    if (bulletParentUpdateType <= GAME_TOWER_UPDATE_TYPE_ZERO  && bulletParentType == GAME_TOWER_TYPE_PLANE) {
        bulletWidth /=3.0;
    }
    

    CCPoint bulletLeftCenterDot1 = ccp(this->getPosition().x - (bulletWidth / 2.0) * cosf(((at) * PAI / 180.0)),this->getPosition().y + (bulletWidth/2.0) * sinf((at) * PAI / 180.0));
    CCPoint bulletRightCenterDot1 = ccp(this->getPosition().x + (bulletWidth / 2.0) * cosf(((at) * PAI / 180.0)),this->getPosition().y - (bulletWidth/2.0) * sinf((at) * PAI / 180.0));
    
    CCPoint bulletLetTopPos = ccp(bulletLeftCenterDot1.x - (bulletHeight/2.0) * cosf(((90 - at) * PAI)/180.0),bulletLeftCenterDot1.y - (bulletHeight/2.0) * sinf(((90 - at) * PAI)/180.0));
    CCPoint bulletRightTopPos = ccp(bulletLeftCenterDot1.x + (bulletHeight/2.0) * cosf(((90 - at) * PAI)/180.0),bulletLeftCenterDot1.y + (bulletHeight/2.0) * sinf(((90 - at) * PAI)/180.0));
    CCPoint bulletOriginPos = ccp(bulletRightCenterDot1.x - (bulletHeight/2.0) * cosf(((90 - at) * PAI)/180.0),bulletRightCenterDot1.y - (bulletHeight/2.0) * sinf(((90 - at) * PAI)/180.0));
    CCPoint bulletRightBottomPos = ccp(bulletRightCenterDot1.x + (bulletHeight/2.0) * cosf(((90 - at) * PAI)/180.0),bulletRightCenterDot1.y + (bulletHeight/2.0) * sinf(((90 - at) * PAI)/180.0));
    
    posBuffer[0].x = bulletOriginPos.x;
    posBuffer[0].y = bulletOriginPos.y;
    posBuffer[1].x = bulletRightBottomPos.x;
    posBuffer[1].y = bulletRightBottomPos.y;
    posBuffer[2].x = bulletRightTopPos.x;
    posBuffer[2].y = bulletRightTopPos.y;
    posBuffer[3].x = bulletLetTopPos.x;
    posBuffer[3].y = bulletLetTopPos.y;
    
//
//
    if (((int)at >= 0 && at <= 90) || (((int)at >= -360 && at < -270))) {
        bulletMaxX = bulletRightBottomPos.x;
        bulletMinX = bulletLetTopPos.x;
        bulletMaxY = bulletRightTopPos.y;
        bulletMinY = bulletOriginPos.y;
    }
    else if((at > 90 && at <= 180) || (at > -270 && at <= -180))
    {
        bulletMaxX = bulletRightTopPos.x;
        bulletMinX = bulletOriginPos.x;
        bulletMaxY = bulletLetTopPos.y;
        bulletMinY = bulletRightBottomPos.y;
    }
    else if((at > 180 && at <= 270) || (at > -180 && at <= -90))
    {
        bulletMaxX = bulletLetTopPos.x;
        bulletMinX = bulletRightBottomPos.x;
        bulletMaxY = bulletOriginPos.y;
        bulletMinY = bulletRightTopPos.y;
    }
    else if((at > 270 && at <= 360) || (at > -90 && ((int)at) < 0) )
    {
        bulletMaxX = bulletOriginPos.x;
        bulletMinX = bulletRightTopPos.x;
        bulletMaxY = bulletRightBottomPos.y;
        bulletMinY = bulletLetTopPos.y;
    }
    
    if (enemyPos.x > bulletMaxX || enemyPos.x < bulletMinX) {
        return false;
    }
    
    if (at == 90 || at == -90 || at == -270 || at == 270) {
        bulletRec = CCRect(this->getPosition().x - bulletHeight/2, this->getPosition().y - bulletWidth/2.0, bulletHeight, bulletWidth);
    }
    else if (at == 180 || at == -180 || at == 360 || ((int)at == 0) )
    {
        bulletRec = CCRect(this->getPosition().x - bulletWidth/2, this->getPosition().y - bulletHeight/2.0, bulletWidth, bulletHeight);
    }
    
    isCollion = this->checkEnemyIsLineCollion2(posBuffer[2], posBuffer[3], bulletRec, enemyRec);//采用的算法是：子弹的两个长边作为一个线段，如果与ENEMY相交，那么其中至少一条线段有交集
    
    isCollion |= this->checkEnemyIsLineCollion2(posBuffer[1], posBuffer[0], bulletRec, enemyRec);

    
    if (isCollion) {
        CCLog("collion,pos.x = %f   pos.y = %f",this->getPosition().x,this->getPosition().y);
    }
    
    
    return isCollion;
}

bool TowerBulletClass::checkEnemyIsLineCollion2(cocos2d::CCPoint firstPos, cocos2d::CCPoint secPos, cocos2d::CCRect bulletRect, cocos2d::CCRect enemyRect)
{
    bool isCollion = false;
    
    float ab0 = 0;
    float ac0 = 0;
    
    if ((((int)(firstPos.x - secPos.x)) == 0) || (((int)(firstPos.y - secPos.y)) == 0)) {
        ab0 = 0;
        ac0 = 0;
    }
    else
    {
        ab0 = (firstPos.y - secPos.y)/(firstPos.x - secPos.x);
        ac0 = (firstPos.y - ((firstPos.y - secPos.y)/(firstPos.x - secPos.x)) * firstPos.x);
    }
    
    
    if ((((int)(firstPos.x - secPos.x)) == 0) || (((int)(firstPos.y - secPos.y)) == 0)) {
        isCollion  = bulletRect.intersectsRect(enemyRect);
    }
    else
    {
        float x0 = (enemyRect.origin.y - ac0)/ab0;
        float y0 = 0;
        
        if (x0 >= enemyRect.origin.x && x0 <= (enemyRect.origin.x + enemyRect.size.width)) {
            
            isCollion = true;
        }
        else
        {
            x0 = (enemyRect.origin.y + enemyRect.size.height - ac0)/ab0;
            
            if (x0 >= enemyRect.origin.x && x0 <= (enemyRect.origin.x + enemyRect.size.width)) {
                
                isCollion = true;
            }
            else
            {
                y0 = ab0 * enemyRect.origin.x + ac0;
                
                if (y0 >= enemyRect.origin.y && y0<= (enemyRect.origin.y + enemyRect.size.height)) {
                    isCollion = true;
                }
                else
                {
                    y0 = ab0 * (enemyRect.origin.x + enemyRect.size.width) + ac0;
                    
                    if (y0 >= enemyRect.origin.y && y0<= (enemyRect.origin.y + enemyRect.size.height)) {
                        isCollion = true;
                    }
                }
            }
        }
    }
    
    
    return isCollion;
}


bool TowerBulletClass::checkIsCollionWithEnemy(EnemySpriteClass* enemy)
{
	if (enemy && !enemy->getIsDead() && enemy->retainCount() > 0)
	{
        float width = enemy->getContentSize().width;
        float height = enemy->getContentSize().height;
        
		CCPoint enemyPos = enemy->getPosition();
//        CCSize enemySize = CCSize(enemy->getContentSize().width, enemy->getContentSize().height);
        
        width *= LcdAdapClass::sharedLCDADAP()->getXScale();
        height *= LcdAdapClass::sharedLCDADAP()->getYScale();
        
		CCRect enemyRect = CCRect(enemyPos.x - width / 2.0, enemyPos.y - height / 2.0, width, height);
		
        width = this->getContentSize().width;
        height = this->getContentSize().height;
//        CCSize bulletSize = CCSize(this->getContentSize().width, this->getContentSize().height);
//        width *= LcdAdapClass::sharedLCDADAP()->getXScale();
//        height *= LcdAdapClass::sharedLCDADAP()->getYScale();
		CCPoint bulletPos = this->getPosition();
		CCRect bulletRect = CCRect(bulletPos.x - width / 2.0, bulletPos.y - height / 2.0, width, height);
		
		if (bulletRect.intersectsRect(enemyRect))
		{
			return true;
		}
        else if (enemyRect.intersectsRect(bulletRect))
        {
            return true;
        }
	}
	return false;
}

void TowerBulletClass::update(float dt)
{
    
    timeCounter += dt;
    
    {
        
        
        switch (bulletParentType) {
            case GAME_TOWER_TYPE_ANCHOR:
            {
                
            }
                break;
            case GAME_TOWER_TYPE_ARROW:
            {
                
            }
                break;
            case GAME_TOWER_TYPE_BALL:
            {
                if (targetObject && !targetObject->getIsDead()  && targetObject->retainCount() > 0) {
                    
                    bulletVector = ccp(0,0);
//                    float maxValue = MAX(bulletParentSize.width, bulletParentSize.height);
                    float towerRLen = 0;//bulletParentSize.height/2.0;//maxValue / 2 - maxValue / 3;
                    {
                        
                        CCPoint location = bulletParentPos;
                        CCPoint targetPos = targetObject->getPosition();
                        
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
                        bulletVector = ccpNormalize(CCPoint(o,a));
                        
                    }
                    
                    CCPoint newPos = ccpAdd(bulletParentPos, ccpMult(bulletVector, towerRLen));
                    this->setPosition(newPos);
                    
                    float len = ccpLength(ccpSub(this->getPosition(), targetObject->getPosition()));
                    
                    float towerLen =  ccpLength(ccpSub(bulletParentPos, targetObject->getPosition()));
                    
                    if (len <  bulletKillRadius) {
                        
                        CCSize bulletSize = this->getContentSize();

                        float ratio = len / (bulletSize.height);
                        this->setScaleY(ratio);
                        CCPoint delta = ccpSub(targetObject->getPosition(), this->getPosition());
                        float at = (float) CC_RADIANS_TO_DEGREES( atanf( delta.x/delta.y) );
                        CCPoint newPos = ccpAdd(this->getPosition(), ccpMult(ccpNormalize(delta), bulletSize.height/2 * ratio));
                        if( delta.y < 0 )
                        {
                            if(  delta.x < 0 )
                                at = 180 + (at);
                            else
                                at = 180 - fabs(at);
                        }
                        this->setPosition(newPos);
                        this->setRotation(at);
                        
                        if (!isBulletPause) {
                            if (timeCounter > 0.5) {
                                int lifeValue = targetObject->getCurLifeValue();
                                
                                timeCounter = 0;
                                TowerBulletEffect* effect = TowerBulletEffect::create(bulletParentType,bulletParentUpdateType,targetObject);
                                effect->setIsSpeed2X(isSpeed2X);
                                this->getParent()->addChild(effect);
                                if (bulletEffectArray) {
                                    bulletEffectArray->addObject(effect);
                                }
                                
                                lifeValue -= bulletKillValue;
                                if (lifeValue > 0) {
                                    targetObject->setCurLifeValue(lifeValue);
                                    targetObject->setIsAttacked(true);
                                }
                                else
                                {
                                    targetObject->setCurLifeValue(-1);
                                }
                                
                                
                            }
                        }
                        else
                        {
                            timeCounter = 0;
                        }
                    }
                    else
                    {
                        if (bulletArray != NULL && bulletArray->count() > 0) {
                            bulletArray->removeObject(this);
                        }
                        this->removeFromParentAndCleanup(true);
                        return;
                    }
                }
                else
                {
                    if (bulletArray != NULL && bulletArray->count() > 0) {
                        bulletArray->removeObject(this);
                    }
                    this->removeFromParentAndCleanup(true);
                    return;
                }
            }
                break;
            case GAME_TOWER_TYPE_BLUESTAR:
            {
                
            }
                break;
            case GAME_TOWER_TYPE_BOTTLE:
            {
                
            }
                break;
            case GAME_TOWER_TYPE_BUFF:
            {
                
            }
                break;
            case GAME_TOWER_TYPE_CUTTLE:
            {
                
            }
                break;
            case GAME_TOWER_TYPE_FAN:
            {
                
            }
                break;
            case GAME_TOWER_TYPE_FIREBOTTLE:
            {
                if (targetObject && !targetObject->getIsDead()  && targetObject->retainCount() > 0) {
                    
                    bulletVector = ccp(0,0);
                    float towerRLen = bulletParentSize.height * 50/100;//maxValue / 2 - maxValue / 3;
                    {
                        
                        CCPoint location = bulletParentPos;
                        CCPoint targetPos = targetObject->getPosition();
                        
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
                        bulletVector = ccpNormalize(CCPoint(o,a));
                        
                    }
                    
                    CCPoint newPos = ccpAdd(bulletParentPos, ccpMult(bulletVector, towerRLen));
                    this->setPosition(newPos);
                    
                    float len = ccpLength(ccpSub(this->getPosition(), targetObject->getPosition()));
                    if (ccpLength(ccpSub(bulletParentPos, targetObject->getPosition())) < (bulletKillRadius)) {

                        CCSize bulletSize = this->getContentSize();
                        
//                        bulletSize.width *= LcdAdapClass::sharedLCDADAP()->getXScale();
//                        bulletSize.height *= LcdAdapClass::sharedLCDADAP()->getYScale();
                        
                        float ratio = 0;
                        CCPoint delta = ccpSub(targetObject->getPosition(), this->getPosition());
                        float at = (float) CC_RADIANS_TO_DEGREES( atanf( delta.x/delta.y) );
                        CCPoint newPos = CCPointZero;
                        
                        ratio = (len + bulletSize.height/2.0)/ bulletSize.height;
                        this->setScaleY(ratio);
                        if (len > bulletSize.height/2) {
                            newPos = ccpAdd(this->getPosition(), ccpMult(ccpNormalize(delta), len/2.0 - bulletSize.height/4.0));
                        }
                        else
                        {
                            
                            newPos = ccpSub(this->getPosition(), ccpMult(ccpNormalize(delta), bulletSize.height/4.0 - len/2.0));
                        }

                        if( delta.y < 0 )
                        {
                            if(  delta.x < 0 )
                                at = 180 + (at);
                            else
                                at = 180 - fabs(at);
                        }
                        this->setPosition(newPos);
                        this->setRotation(at);
                        
                        if (!isBulletPause) {
                            if (timeCounter > 0.25) {
                                int lifeValue = targetObject->getCurLifeValue();
                                
                                timeCounter = 0;
                                TowerBulletEffect* effect = TowerBulletEffect::create(bulletParentType,bulletParentUpdateType,targetObject);
                                effect->setIsSpeed2X(isSpeed2X);
                                this->getParent()->addChild(effect);
                                if (bulletEffectArray) {
                                    bulletEffectArray->addObject(effect);
                                }
                                lifeValue -= bulletKillValue;
                                if (lifeValue > 0) {
                                    targetObject->setCurLifeValue(lifeValue);
                                    targetObject->setIsAttacked(true);
                                }
                                else
                                {
                                    targetObject->setCurLifeValue(-1);
                                }
                                
                            }
                        }
                        else
                        {
                            timeCounter = 0;
                        }
                    }
                    else
                    {
                        if (bulletArray != NULL && bulletArray->count() > 0) {
                            bulletArray->removeObject(this);
                        }
                        this->removeFromParentAndCleanup(true);
                        return;
                    }
                }
                else
                {
                    if (bulletArray != NULL && bulletArray->count() > 0) {
                        bulletArray->removeObject(this);
                    }
                    this->removeFromParentAndCleanup(true);
                    return;
                }
            }
                break;
            case GAME_TOWER_TYPE_FISH:
            {
                
            }
                break;
            case GAME_TOWER_TYPE_MUSHROOM:
            {
//                this->setPosition(targetObject->getPosition());
//                if (timeCounter > 5) {
//                    targetObject->setScale(1);
//                    targetObject->setIsAttackedByMushRoom(false);
//                    targetObject->setEnemySpeed(saveTargetSpeed);
//                }
            }
                break;
            case GAME_TOWER_TYPE_PIN:
            {
//                if (targetObject != NULL && !targetObject->getIsDead()  && targetObject->retainCount() > 0) {
//                    this->setPosition(targetObject->getPosition());
//                    if (timeCounter > 5) {
//                        targetObject->setEnemySpeed(saveTargetSpeed);
//                        targetObject->setIsAttackedByPin(false);
//                    }
//                }
//                else
//                {
//                    timeCounter = 0;
//                    this->unscheduleUpdate();
//                    this->removeFromParentAndCleanup(true);
//                    return;
//                }
            }
                break;
            case GAME_TOWER_TYPE_PLANE:
            {
                
            }
                break;
            case GAME_TOWER_TYPE_ROCKET:
            {
                
                
            }
                break;
            case GAME_TOWER_TYPE_SHIT:
            {
//                if (targetObject != NULL && !targetObject->getIsDead()  && targetObject->retainCount() > 0) {
//                    this->setPosition(targetObject->getPosition());
//                    if (timeCounter > 5) {
//                        targetObject->setEnemySpeed(saveTargetSpeed);
//                        targetObject->setisAttackedByShit(false);
//                    }
//                }
//                else
//                {
//                    timeCounter = 0;
//                    this->unscheduleUpdate();
//                    this->removeFromParentAndCleanup(true);
//                    return;
//                }
            }
                break;
            case GAME_TOWER_TYPE_SNOW:
            {
//                if (timeCounter > 5) {
//                    targetObject->resumeSchedulerAndActions();
//                }
            }
                break;
            case GAME_TOWER_TYPE_STAR:
            {
                
            }
                break;
            case GAME_TOWER_TYPE_SUN:
            {
                
            }
                break;
            default:
                break;
        }
        if (bulletParentType == GAME_TOWER_TYPE_FAN || bulletParentType == GAME_TOWER_TYPE_ROCKET ||  bulletParentType == GAME_TOWER_TYPE_BLUESTAR || bulletParentType == GAME_TOWER_TYPE_CUTTLE || bulletParentType == GAME_TOWER_TYPE_ARROW || bulletParentType == GAME_TOWER_TYPE_BUFF)
        {
			CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
			CCPoint pos = this->getPosition();
			CCSize bulletSize = this->getContentSize();
//            bulletSize.width *= LcdAdapClass::sharedLCDADAP()->getXScale();
//            bulletSize.height *= LcdAdapClass::sharedLCDADAP()->getYScale();
            
			if (enemyArray != NULL && enemyArray->count() > 0)
			{
                
                if (pos.x < (-bulletSize.width) || pos.x > (size.width + bulletSize.width) || pos.y < (-bulletSize.height) || pos.y > (size.height + bulletSize.height))
                {
                    if (bulletArray != NULL && bulletArray->count() > 0) {
                        bulletArray->removeObject(this);
                    }
                    this->removeFromParentAndCleanup(true);
                    return;
                }
                
				for (int i = 0; i < enemyArray->count();i++)
				{
					EnemySpriteClass* enemy = (EnemySpriteClass*)enemyArray->objectAtIndex(i);

                    if (comFanArray != NULL && comFanArray->count() > 0) {
                        for (int j = 0; j < comFanArray->count(); j++) {
                            EnemySpriteClass* enemyAttacked = (EnemySpriteClass*)comFanArray->objectAtIndex(j);
                            if (enemyAttacked == enemy) {
                                return;
                            }
                        }
                    }
                    
                    
					if (enemy != NULL && !enemy->getIsDead()  && enemy->retainCount() > 0)
					{
						if (this->checkIsCollionWithEnemy(enemy))
						{
							int lifeValue = enemy->getCurLifeValue();

                            TowerBulletEffect* effect = TowerBulletEffect::create(bulletParentType,bulletParentUpdateType,enemy);
							effect->setIsSpeed2X(isSpeed2X);
							this->getParent()->addChild(effect);
                            if (bulletEffectArray) {
                                bulletEffectArray->addObject(effect);
                            }
                            
							lifeValue -= bulletKillValue;
							if (lifeValue > 0) {
                                enemy->setCurLifeValue(lifeValue);
                                enemy->setIsAttacked(true);
                                comFanArray->addObject(enemy);
                            }
                            else
                            {
                                enemy->setCurLifeValue(-1);
                            }

							
                            if (bulletParentType == GAME_TOWER_TYPE_CUTTLE || bulletParentType == GAME_TOWER_TYPE_ARROW ) {
                                if (bulletArray != NULL && bulletArray->count() > 0) {
                                    bulletArray->removeObject(this);
                                }
                                this->removeFromParentAndCleanup(true);
                                return;
                            }
                            
                            if (enemy->getEnemyType() == GAME_ENEMY_TYPE_OBJECT) {
                                if (bulletArray != NULL && bulletArray->count() > 0) {
                                    bulletArray->removeObject(this);
                                }
                                this->removeFromParentAndCleanup(true);
                                return;
                            }
                            
                            break;
						}
					}

				}
                

			}
			
        }
        else if (timeCounter > 5  && bulletParentType != GAME_TOWER_TYPE_FIREBOTTLE && bulletParentType != GAME_TOWER_TYPE_BALL) {
            timeCounter = 0;
            this->unscheduleUpdate();
            if (bulletArray != NULL && bulletArray->count() > 0) {
                bulletArray->removeObject(this);
            }
            this->removeFromParentAndCleanup(true);
        }
    }
}


