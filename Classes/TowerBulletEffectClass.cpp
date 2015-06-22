//
//  TowerBulletEffectClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-10-10.
//
//

#include "TowerBulletEffectClass.h"
#include "LcdAdapClass.h"

TowerBulletEffect::TowerBulletEffect()
{
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(TowerBulletEffect::enemyDeadNotification), ENEMY_DEAD_NOTIFICATION, NULL);
}

TowerBulletEffect::~TowerBulletEffect()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, ENEMY_DEAD_NOTIFICATION);

	//effectAniFramesArray->removeAllObjects();
	effectAniFramesArray->release();
	effectAniFramesArray = NULL;
}

void TowerBulletEffect::enemyDeadNotification(CCObject *object)
{
	EnemySpriteClass *enemy = dynamic_cast<EnemySpriteClass *>(object);
	if (enemy && enemyObject && enemy == enemyObject)
	{
		enemyObject = NULL;
	}
}


bool TowerBulletEffect::init(GAME_TOWER_TYPE tower, GAME_TOWER_UPDATE_TYPE update,EnemySpriteClass* enemy)
{
    CCAssert(!(tower == GAME_TOWER_TYPE_NONE || tower == GAME_TOWER_TYPE_MAX), "can not be Invalid");
    CCAssert(!(enemy == NULL), "cannot be NULL");
    
    int count = 0;
    int index = 1;
    float aniTime = 0.1;
    char* pFileName = NULL;
    float bulletKillValue = 50;
    char buffer[50] = {0};
    effectAniFramesArray = CCArray::create();
    effectAniFramesArray->retain();
    
    enemyObject = enemy;
    towerType = tower;
    IsBulletEffectPause = false;
	isSpeed2X = false;
    enemySpeed = enemyObject->getMoveSpeed();
    saveEnemyMoveSpeed = enemyObject->getMoveSpeed();
    BulletEffectArray = NULL;
    
    switch (towerType) {
        case GAME_TOWER_TYPE_ANCHOR:
        {
            //sprintf(pFileName, "%s","PAnchor");
            pFileName = "PAnchor-";
            count = 6;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_ANCHOR;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_ANCHOR;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_ANCHOR;
                    break;
                default:
                    break;
            }
            aniTime = 0.05;
            index = 11;
        }
            break;
        case GAME_TOWER_TYPE_ARROW:
        {
            //sprintf(pFileName, "%s","PArrow");
            pFileName = "PArrow";
            count = 2;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_ARROW;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_ARROW;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_ARROW;
                    break;
                default:
                    break;
            }
            aniTime = 0.05;
        }
            break;
        case GAME_TOWER_TYPE_BALL:
        {
            //sprintf(pFileName, "%s","PBall");
            pFileName = "PBall";
            count = 2;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_BALL;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_BALL;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_BALL;
                    break;
                default:
                    break;
            }
            aniTime = 0.1;
        }
            break;
        case GAME_TOWER_TYPE_BLUESTAR:
        {
            //sprintf(pFileName, "%s","PBStar");
            pFileName = "PBStar";
            count = 2;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_BLUESTAR;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_BLUESTAR;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_BLUESTAR;
                    break;
                default:
                    break;
            }
            aniTime = 0.05;
        }
            break;
        case GAME_TOWER_TYPE_BOTTLE:
        {
            //sprintf(pFileName, "%s","PBottle");
            pFileName = "PBottle";
            count = 2;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_BOTTLE;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_BOTTLE;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_BOTTLE;
                    break;
                default:
                    break;
            }
            aniTime = 0.25;
        }
            break;
        case GAME_TOWER_TYPE_BUFF:
        {
            //sprintf(pFileName, "%s","PBuff");
            pFileName = "PBuff";
            count = 1;
            index = 1;
            
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_BUFF;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_BUFF;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_BUFF;
                    break;
                default:
                    break;
            }
            aniTime = 0.25;
        }
            break;
        case GAME_TOWER_TYPE_CUTTLE:
        {
            //sprintf(pFileName, "%s","PCuttle");
            pFileName = "PCuttle";
            count = 4;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_CUTTLE;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_CUTTLE;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_CUTTLE;
                    break;
                default:
                    break;
            }
            aniTime = 0.05;
        }
            break;
        case GAME_TOWER_TYPE_FAN:
        {
            //sprintf(pFileName, "%s","PFan");
            pFileName = "PFan";
            count = 2;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_FAN;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_FAN;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_FAN;
                    break;
                default:
                    break;
            }
            aniTime = 0.05;
        }
            break;
        case GAME_TOWER_TYPE_FIREBOTTLE:
        {
            //sprintf(pFileName, "%s","PFBottle");
            pFileName = "PFBottle";
            count = 2;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_FIREBOTTLE;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_FIREBOTTLE;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_FIREBOTTLE;
                    break;
                default:
                    break;
            }
            aniTime = 0.25;
        }
            break;
        case GAME_TOWER_TYPE_FISH:
        {
            //sprintf(pFileName, "%s","PFish");
            pFileName = "PFish";
            count = 1;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_FISH;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_FISH;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_FISH;
                    break;
                default:
                    break;
            }
            aniTime = 0.25;
        }
            break;
        case GAME_TOWER_TYPE_MUSHROOM:
        {
            //sprintf(pFileName, "%s","PMushroom");
            pFileName = "PMushroom-";
            count = 1;
            
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_MUSHROOM;
                    index = 11;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_MUSHROOM;
                    index = 21;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_MUSHROOM;
                    index = 21;
                    break;
                default:
                    break;
            }
            aniTime = 1;
        }
            break;
        case GAME_TOWER_TYPE_PIN:
        {
            //sprintf(pFileName, "%s","PPin");
            pFileName = "PPin";
            count = 4;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_PIN;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_PIN;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_PIN;
                    break;
                default:
                    break;
            }
            aniTime = 0.25;
//            if (enemyObject->getEnemyType() == GAME_ENEMY_TYPE_MONSTERS && !enemyObject->getIsAttackedByPin()) {
//                enemySpeed = enemyObject->getMoveSpeed();
//                enemyObject->setEnemySpeed(enemySpeed / 2);
//                enemyObject->setIsAttackedByPin(true);
//            }
        }
            break;
        case GAME_TOWER_TYPE_PLANE:
        {
            //sprintf(pFileName, "%s","PPlane");
            pFileName = "PPlane";
            count = 5;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_PLANE;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_PLANE;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_PLANE;
                    break;
                default:
                    break;
            }
            aniTime = 0.01;
        }
            break;
        case GAME_TOWER_TYPE_ROCKET:
        {
            //sprintf(pFileName, "%s","PRocket");
            pFileName = "PRocket";
            count = 2;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_ROCKET;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_ROCKET;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_ROCKET;
                    break;
                default:
                    break;
            }
            aniTime = 0.05;
        }
            break;
        case GAME_TOWER_TYPE_SHIT:
        {
            //sprintf(pFileName, "%s","PShit");
            pFileName = "PShit";
            count = 2;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_SHIT;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_SHIT;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_SHIT;
                    break;
                default:
                    break;
            }
            aniTime = 0.1;
            
        }
            break;
        case GAME_TOWER_TYPE_SNOW:
        {
            //sprintf(pFileName, "%s","PSnow");
            pFileName = "PSnow";
            count = 2;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_SNOW;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_SNOW;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_SNOW;
                    break;
                default:
                    break;
            }
            aniTime = 0.1;
        }
            break;
        case GAME_TOWER_TYPE_STAR:
        {
            //sprintf(pFileName, "%s","PStar");
            pFileName = "PStar";
            count = 6;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_STAR;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_STAR;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_STAR;
                    break;
                default:
                    break;
            }
            aniTime = 0.05;
        }
            break;
        case GAME_TOWER_TYPE_SUN:
        {
            //sprintf(pFileName, "%s","PSun");
            pFileName = "PSun";
            count = 3;
            switch (update) {
                case GAME_TOWER_UPDATE_TYPE_ZERO:
                    bulletKillValue = GAME_TOWER_UPDATEONE_KILLRADIUS_SUN;
                    break;
                case GAME_TOWER_UPDATE_TYPE_ONE:
                    bulletKillValue = GAME_TOWER_UPDATETWO_KILLRADIUS_SUN;
                    break;
                case GAME_TOWER_UPDATE_TYPE_TWO:
                    bulletKillValue = GAME_TOWER_UPDATETHREE_KILLRADIUS_SUN;
                    break;
                default:
                    break;
            }
            aniTime = 0.1;
        }
            break;
        default:
            break;
    }
    
    for (int i = index; i < (index + count); i++) {
        
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%s%02d.png",pFileName,i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
        effectAniFramesArray->addObject(frame);
        if (i == index) {
            CCSprite::initWithSpriteFrameName(buffer);
            this->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
            this->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());
        }
    }
    effectAniTime = aniTime;
    
    this->setPosition(enemy->getPosition());
    CCAnimation* ani = CCAnimation::createWithSpriteFrames(effectAniFramesArray, aniTime);
    CCCallFuncN* callfunc = NULL;

	if (towerType == GAME_TOWER_TYPE_SHIT || towerType == GAME_TOWER_TYPE_PIN)
	{
        if (towerType == GAME_TOWER_TYPE_SHIT) {
            if (enemyObject->getEnemyType() == GAME_ENEMY_TYPE_MONSTERS && !enemyObject->getisAttackedByShit()) {
                
                enemyObject->setEnemySpeed(enemySpeed / 2);
                enemyObject->setisAttackedByShit(true);
                callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletEffect::effectFirstActionCallBack));
            }
            else
            {
                callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletEffect::noEffectAniCallBack));
            }
        }
        else if (towerType == GAME_TOWER_TYPE_PIN){
            if (enemyObject->getEnemyType() == GAME_ENEMY_TYPE_MONSTERS && !enemyObject->getIsAttackedByPin()) {
                
                enemyObject->setEnemySpeed(enemySpeed / 2);
                enemyObject->setIsAttackedByPin(true);
                callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletEffect::effectAniCallBack));
            }
            else
            {
                callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletEffect::noEffectAniCallBack));
            }
        }
		
	}
	else
	{
		callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletEffect::effectAniCallBack));
	}
	

    this->runAction((CCActionInterval*)CCSequence::create(CCAnimate::create(ani),callfunc,NULL));
    this->scheduleUpdate();
    return true;
}

TowerBulletEffect* TowerBulletEffect::create(GAME_TOWER_TYPE tower, GAME_TOWER_UPDATE_TYPE update, EnemySpriteClass *enemy)
{
    TowerBulletEffect* effect = new TowerBulletEffect();
    if (effect && effect->init(tower, update, enemy)) {
        effect->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(effect);
    }
    
    return effect;
}


void TowerBulletEffect::setsaveEnemyMoveSpeed(float speed)
{
    saveEnemyMoveSpeed = speed;
}


void TowerBulletEffect::setIsBulletEffectPause(bool flag)
{
    IsBulletEffectPause = flag;
    
    if (IsBulletEffectPause) {
        this->pauseSchedulerAndActions();
    }
    else
    {
        this->resumeSchedulerAndActions();
    }
}

void TowerBulletEffect::setIsSpeed2X(bool flag)
{
//	isSpeed2X = flag;
//
//	this->stopAllActions();
//	if (isSpeed2X)
//	{
//		effectAniTime /= 2;
//		
//	}
//	else
//	{
//		effectAniTime *= 2;
//	}
	
//	CCAnimation* ani = CCAnimation::createWithSpriteFrames(effectAniFramesArray, effectAniTime);
//	CCCallFuncN* callfunc = NULL;
//    
//	if (towerType == GAME_TOWER_TYPE_SHIT || towerType == GAME_TOWER_TYPE_PIN)
//	{
//        if (towerType == GAME_TOWER_TYPE_SHIT) {
//            if (enemyObject->getEnemyType() == GAME_ENEMY_TYPE_MONSTERS) {
//                
//                enemyObject->setEnemySpeed(enemySpeed / 2);
//                enemyObject->setisAttackedByShit(true);
//                callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletEffect::effectFirstActionCallBack));
//            }
//            else
//            {
//                callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletEffect::effectAniCallBack));
//            }
//        }
//        else if (towerType == GAME_TOWER_TYPE_PIN){
//            if (enemyObject->getEnemyType() == GAME_ENEMY_TYPE_MONSTERS ) {
//                
//                enemyObject->setEnemySpeed(enemySpeed / 2);
//                enemyObject->setIsAttackedByPin(true);
//                callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletEffect::effectFirstActionCallBack));
//            }
//            else
//            {
//                callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletEffect::effectAniCallBack));
//            }
//        }
//		
//	}
//	else
//	{
//		callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletEffect::effectAniCallBack));
//	}
//
//	this->runAction((CCActionInterval*)CCSequence::create(CCAnimate::create(ani),callfunc,NULL));
}

bool TowerBulletEffect::getIsBulletEffectPause()
{
    return IsBulletEffectPause;
}

void TowerBulletEffect::effectFirstActionCallBack(cocos2d::CCNode *parent)
{
	if (enemyObject && !enemyObject->getIsDead()  && enemyObject->retainCount() > 0)
	{
		if (enemyObject->getEnemyType() == GAME_ENEMY_TYPE_MONSTERS)
		{
			char* pFileName = NULL;
			int count = 0;
			int index = 11;
			char buffer[100] = {0};

			effectAniFramesArray->removeAllObjects();
			if (towerType == GAME_TOWER_TYPE_SHIT)
			{
                
				pFileName = "PShit-";
				count = 2;
			}
//			else if (towerType == GAME_TOWER_TYPE_PIN)
//			{
//
//				pFileName = "Pin-";
//				count = 3;
//			}
//			
			for (int i = index; i < (index + count);i++)
			{
				memset(buffer, 0, sizeof(buffer));
				sprintf(buffer, "%s%d.png",pFileName,i);
				CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
				effectAniFramesArray->addObject(frame);
				if (i == index) {
					this->setDisplayFrame(frame);
				}
			}
			CCAnimation* ani = CCAnimation::createWithSpriteFrames(effectAniFramesArray, 1);
			CCCallFuncN* callfunc = CCCallFuncN::create(this, callfuncN_selector(TowerBulletEffect::effectAniCallBack));
			this->runAction((CCActionInterval*)CCSequence::create(CCAnimate::create(ani),callfunc,NULL));
		}
		
	}
	else
	{
        if (BulletEffectArray != NULL && BulletEffectArray->count() > 0) {
            BulletEffectArray->removeObject(this);
        }
		this->removeFromParentAndCleanup(true);
	}
	
}

void TowerBulletEffect::effectAniCallBack(cocos2d::CCNode *parent)
{
    if (towerType == GAME_TOWER_TYPE_MUSHROOM) {
        enemyObject->setScale(1.5);
        enemyObject->setIsAttackedByMushRoom(false);
        enemyObject->setEnemySpeed(saveEnemyMoveSpeed);
    }
    else if (towerType == GAME_TOWER_TYPE_SNOW)
    {
        enemyObject->resumeSchedulerAndActions();
        enemyObject->setIsAttackedBySnow(false);
    }
    else if (towerType == GAME_TOWER_TYPE_PIN)
    {
        if (enemyObject->getEnemyType() == GAME_ENEMY_TYPE_MONSTERS) {
            enemyObject->setEnemySpeed(saveEnemyMoveSpeed);
            enemyObject->setisAttackedByShit(false);
        }
    }
    else if (towerType == GAME_TOWER_TYPE_SHIT)
    {
        if (enemyObject->getEnemyType() == GAME_ENEMY_TYPE_MONSTERS) {
            enemyObject->setEnemySpeed(saveEnemyMoveSpeed);
            enemyObject->setisAttackedByShit(false);
        }
    }
    
    this->stopAllActions();
    this->unscheduleUpdate();
    if (BulletEffectArray != NULL && BulletEffectArray->count() > 0) {
        BulletEffectArray->removeObject(this);
    }
    
    this->removeFromParentAndCleanup(true);
}

void TowerBulletEffect::noEffectAniCallBack(cocos2d::CCNode *parent)
{
    
    if (BulletEffectArray != NULL && BulletEffectArray->count() > 0) {
        BulletEffectArray->removeObject(this);
    }
    
    this->removeFromParentAndCleanup(true);
}

void TowerBulletEffect::setBulletEffectArray(cocos2d::CCArray *array)
{
    BulletEffectArray = array;
}


void TowerBulletEffect::update(float dt)
{
    if (enemyObject && !enemyObject->getIsDead() && enemyObject->retainCount() > 0) {
        this->setPosition(enemyObject->getPosition());
    }
    else
    {
        enemyObject = NULL;
        this->stopAllActions();
        this->unscheduleUpdate();
        if (BulletEffectArray != NULL && BulletEffectArray->count() > 0) {
            BulletEffectArray->removeObject(this);
        }
        this->removeFromParentAndCleanup(true);
    }
}
