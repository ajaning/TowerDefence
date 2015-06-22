//
//  EnemySpriteClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-7-24.
//
//

#include "EnemySpriteClass.h"
#include "LcdAdapClass.h"
#include "GameStageConClass.h"
#include "GameMusicConClass.h"

//#define MIN_OFFSET  (5.0f)
#define MAX_NUM (34)
#define ATTACK_TIME (2.0f)

EnemySpriteClass::EnemySpriteClass()
{

}

EnemySpriteClass::~EnemySpriteClass()
{
	CCNotificationCenter::sharedNotificationCenter()->postNotification(ENEMY_DEAD_NOTIFICATION, this);
//    movePosArray->release();
    if (enemyAni != NULL && enemyAni->retainCount() > 0) {
        enemyAni->release();
    }
    curLifeValue = 0;
    totalLifeValue = 0;
}

bool EnemySpriteClass::init(const char *pFileName, int life, float moveSpeed, cocos2d::CCArray *posArray)
{
    CCAssert(!(pFileName == NULL), "cannot be NULL");
    CCAssert(!(posArray == NULL), "cannot be NULL");

    //ObjectClass::init(pFileName);
    CCSprite::initWithSpriteFrameName(pFileName);
    
    curLifeValue = 50;
    totalLifeValue = 50;

    
    enemyObjectId = 0;
    enemyObjectToTowerNum_X = 0;
    enemyObjectToTowerNum_Y = 0;
    isAttackedByPin = false;
    isAttackedByShit = false;
    isAttackedBySnow = false;
    enemyAni = NULL;
    deathArray = NULL;
    moneyType = GAME_MONEY_SCORE_TYPE_150;
    enemyMonsterTypeID = GAME_ENEMY_MONSTERS_NONE;
    this->isAttackedByMushRoom = false;
    this->setTotalLifeValue(life);
//    this->setMoveSpeed(moveSpeed);
    isCanMove = true;
//    isSpeed2X = false;
    addEnemyDirType = GAME_ADD_ENEMY_FROM_DIR_NONE;
    enemyType = GAME_ENEMY_TYPE_NONE;
    curPosIndex = 1;

    movePosArray = posArray;
    CCNode* node = (CCNode*)movePosArray->objectAtIndex(0);
    CCNode* node2 = (CCNode*)movePosArray->objectAtIndex(1);
    CCPoint curPos = ccp(node->getPosition().x,node->getPosition().y + LcdAdapClass::sharedLCDADAP()->getGameMapTiledSize().height / 2);
    
    this->setTargetPos(node2->getPosition(), moveSpeed);
    this->setPosition(curPos);

    
    this->setScaleX(LcdAdapClass::sharedLCDADAP()->getXScale());
    this->setScaleY(LcdAdapClass::sharedLCDADAP()->getYScale());
    
    CCSize monsterSize = this->getContentSize();
    
    fgLifeUI = CCSprite::createWithSpriteFrameName("MonsterHP01.png");
    fgLifeUI->setPosition(ccp(monsterSize.width/2, monsterSize.height));
    CCSize fgSize = fgLifeUI->getContentSize();
    fgLifeUI->setVisible(false);
    this->addChild(fgLifeUI,2);
    
    bgLifeUI = CCSprite::createWithSpriteFrameName("MonsterHP02.png");
    bgLifeUI->setPosition(ccp(fgSize.width, fgSize.height/2));
    fgLifeUI->addChild(bgLifeUI,1);
    bgLifeUI->setScaleX(0);
    
    return true;
}

EnemySpriteClass* EnemySpriteClass::createEnemy(const char *pFileName, int life, float moveSpeed, cocos2d::CCArray *posArray)
{
    CCAssert(!(pFileName == NULL), "cannot be NULL");
    CCAssert(!(posArray == NULL), "cannot be NULL");
    EnemySpriteClass* enemy = new EnemySpriteClass();
    if (enemy && enemy->init(pFileName, life, moveSpeed, posArray)) {
        enemy->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(enemy);
    }
    return enemy;
}

bool EnemySpriteClass::init(GAME_ENEMY_MONSTERS_TYPE type, cocos2d::CCArray *posArray)
{
    CCAssert(!(type == GAME_ENEMY_MONSTERS_MAX), "cannot be INVALID");
    CCAssert(!(posArray == NULL), "cannot be NULL");
    
    char *pfileName = NULL;
    float moveSpeed = 10;
    float liveValue = 10;
    int aniNum = 2;
    char pBuffer[100] = {0};
    CCArray* aniArray = CCArray::create();
    
    switch (type) {
        case GAME_ENEMY_MONSTERS_BOSS_BIG:
            {
                pfileName = "boss_big";
                moveSpeed = GAME_ENEMY_MONSTERS_BOSS_BIG_SPEED;
                liveValue = GAME_ENEMY_MONSTERS_BOSS_BIG_LIFE;
                
            }
            break;
        case GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN:
            {
                pfileName = "fat_boss_green";
                moveSpeed = GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN_SPEED;
                liveValue = GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN_LIFE;
            }
            break;
        case GAME_ENEMY_MONSTERS_FAT_GREEN:
            {
                pfileName = "fat_green";
                moveSpeed = GAME_ENEMY_MONSTERS_FAT_GREEN_SPEED;
                liveValue = GAME_ENEMY_MONSTERS_FAT_GREEN_LIFE;
            }
            break;
        case GAME_ENEMY_MONSTERS_FLY_BLUE:
            {
                pfileName = "fly_blue";
                moveSpeed = GAME_ENEMY_MONSTERS_FLY_BLUE_SPEED;
                liveValue = GAME_ENEMY_MONSTERS_FLY_BLUE_LIFE;
            }
            break;
        case GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE:
            {
                pfileName = "fly_boss_blue";
                moveSpeed = GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE_SPEED;
                liveValue = GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE_LIFE;
            }
            break;
        case GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW:
            {
                pfileName = "fly_boss_yellow";
                moveSpeed = GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW_SPEED;
                liveValue = GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW_LIFE;
            }
            break;
        case GAME_ENEMY_MONSTERS_FLY_YELLOW:
            {
                pfileName = "fly_yellow";
                moveSpeed = GAME_ENEMY_MONSTERS_FLY_YELLOW_SPEED;
                liveValue = GAME_ENEMY_MONSTERS_FLY_YELLOW_LIFE;
            }
            break;
        case GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA:
            {
                pfileName = "land_boss_nima";
                moveSpeed = GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA_SPEED;
                liveValue = GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA_LIFE;
            }
            break;
        case GAME_ENEMY_MONSTERS_LAND_BOSS_PINK:
            {
                pfileName = "land_boss_pink";
                moveSpeed = GAME_ENEMY_MONSTERS_LAND_BOSS_PINK_SPEED;
                liveValue = GAME_ENEMY_MONSTERS_LAND_BOSS_PINK_LIFE;
            }
            break;
        case GAME_ENEMY_MONSTERS_LAND_BOSS_STAR:
            {
                pfileName = "land_boss_star";
                moveSpeed = GAME_ENEMY_MONSTERS_LAND_BOSS_STAR_SPEED;
                liveValue = GAME_ENEMY_MONSTERS_LAND_BOSS_STAR_LIFE;
            }
            break;
        case GAME_ENEMY_MONSTERS_LAND_NIMA:
            {
                pfileName = "land_nima";
                moveSpeed = GAME_ENEMY_MONSTERS_LAND_NIMA_SPEED;
                liveValue = GAME_ENEMY_MONSTERS_LAND_NIMA_LIFE;
            }
            break;
        case GAME_ENEMY_MONSTERS_LAND_PINK:
            {
                pfileName = "land_pink";
                moveSpeed = GAME_ENEMY_MONSTERS_LAND_PINK_SPEED;
                liveValue = GAME_ENEMY_MONSTERS_LAND_PINK_LIFE;
            }
            break;
        case GAME_ENEMY_MONSTERS_LAND_STAR:
            {
                pfileName = "land_star";
                moveSpeed = GAME_ENEMY_MONSTERS_LAND_STAR_SPEED;
                liveValue = GAME_ENEMY_MONSTERS_LAND_STAR_LIFE;
            }
            break;
        default:
            break;
    }
    
    for (int i = 1; i <= aniNum; i++) {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "%s%02d.png",pfileName,i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pBuffer);
        CCAssert(!(frame == NULL), "cannot be NULL");
        aniArray->addObject(frame);
        if (i == 1) {
            this->init(pBuffer, liveValue, moveSpeed, posArray);
        }
    }
    
    enemyMonsterTypeID = type;
    enemyAni = CCAnimation::createWithSpriteFrames(aniArray, 0.25);
    enemyAni->retain();
    this->runAction(CCRepeatForever::create(CCAnimate::create(enemyAni)));
    
    return true;
}

EnemySpriteClass* EnemySpriteClass::createEnemy(GAME_ENEMY_MONSTERS_TYPE type, cocos2d::CCArray *posArray)
{
    CCAssert(!(type == GAME_ENEMY_MONSTERS_MAX), "cannot be INVALID");
    CCAssert(!(posArray == NULL), "cannot be NULL");
    EnemySpriteClass* enemy = new EnemySpriteClass();
    if (enemy && enemy->init(type,posArray)) {
        enemy->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(enemy);
    }
    return enemy;
}

void EnemySpriteClass::setEnemyType(GAME_ENEMY_TYPE type)
{
    enemyType = type;
    if (type == GAME_ENEMY_TYPE_MONSTERS) {
        this->moveRunAction();
    }
}

GAME_ENEMY_TYPE EnemySpriteClass::getEnemyType()
{
    return enemyType;
}

void EnemySpriteClass::setAddEnemyDirType(GAME_ADD_ENEMY_FROM_DIR_TYPE dir)
{
    addEnemyDirType = dir;
}

void EnemySpriteClass::moveRunAction()
{
    CCPoint cPos = this->getPosition();
    float time = abs(this->getTargetPos().x - cPos.x) / this->getMoveSpeed();
    if (time == 0) {
        time =abs(this->getTargetPos().y - cPos.y) / this->getMoveSpeed();
    }
    CCMoveTo* mto = CCMoveTo::create(time, this->getTargetPos());
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(EnemySpriteClass::ToTargetPosCallBack));
    this->runAction(CCSequence::create(mto,call,NULL));

}

void EnemySpriteClass::setEnemySpeed(float value)
{
    this->stopAllActions();
    this->setMoveSpeed(value);
    this->moveRunAction();
    if (enemyAni != NULL) {
        this->runAction(CCRepeatForever::create(CCAnimate::create(enemyAni)));
    }
}

void EnemySpriteClass::setEnemyPauseState(bool flag)
{
    this->setIsCanMove(flag);
    this->stopAllActions();
    if (flag) {
        
        if (enemyAni != NULL) {
            this->runAction(CCRepeatForever::create(CCAnimate::create(enemyAni)));
        }
    }
    else
    {
        this->moveRunAction();
        if (enemyAni != NULL) {
            this->runAction(CCRepeatForever::create(CCAnimate::create(enemyAni)));
        }
    }
}

bool EnemySpriteClass::getEnemyPauseState()
{
    return (this->getIsCanMove());
}


void EnemySpriteClass::ToTargetPosCallBack()
{
    int count  = movePosArray->count();
    CCNode* node = NULL;
    //if (curPosIndex < count)
    {
        
        CCPoint pos = this->getPosition();
        

        if (GameStageConClass::sharedStageCon()->getGameModeType() == GAME_MODE_TYPE_ADVENTURE) {
            if ((curPosIndex >= count)) {
                return;
            }
        }
        else if (GameStageConClass::sharedStageCon()->getGameModeType() == GAME_MODE_TYPE_BOSS){
            if ((curPosIndex >= count)) {
                curPosIndex = 0;
            }
        }
        
        node = (CCNode*)movePosArray->objectAtIndex(curPosIndex);
        
        this->setTargetPos(node->getPosition(), this->getMoveSpeed());
        curPosIndex++;
        
        if (addEnemyDirType == GAME_ADD_ENEMY_FROM_DIR_LEFT) {
            if (pos.x > node->getPosition().x) {
                this->setFlipX(true);
            }
            else
            {
                if (this->isFlipX()) {
                    this->setFlipX(false);
                }
            }
        }
        else if (addEnemyDirType == GAME_ADD_ENEMY_FROM_DIR_RIGHT)
        {
            if (pos.x < node->getPosition().x) {
                this->setFlipX(true);
            }
            else
            {
                if (this->isFlipX()) {
                    this->setFlipX(false);
                }
            }
        }
        this->moveRunAction();
    }
}


void EnemySpriteClass::setIsAttacked(bool flag)
{

    if (!this->getIsDead()) {
        
        if ((GameStageConClass::sharedStageCon()->getGameModeType() == GAME_MODE_TYPE_BOSS) && enemyMonsterTypeID == GameStageConClass::sharedStageCon()->getBossMonsterTypeID()) {
            
        }
        else
        {
            CCLog("cur lif = %d",this->getCurLifeValue());
            CCLog("cur total = %d",this->getTotalLifeValue());
            CCLog("cur retaincout = %d",this->retainCount());
            
            fgLifeUI->setVisible(true);
            fgLifeUI->stopAllActions();
            fgLifeUI->runAction(CCSequence::create(CCMoveBy::create(2, ccp(0, 0)),CCCallFunc::create(this, callfunc_selector(EnemySpriteClass::setAttckInvalid)),NULL));
            this->updateLifeUI();
        }
        
        
    }
}

void EnemySpriteClass::setAttckInvalid()
{
    fgLifeUI->setVisible(false);
    
//    bgLifeUI->setVisible(false);
//    fgLifeUI->setVisible(false);
//    this->unschedule(schedule_selector(EnemySpriteClass::setAttckInvalid));
}



void EnemySpriteClass::setisAttackedByShit(bool flag)
{
    isAttackedByShit = flag;
}

bool EnemySpriteClass::getisAttackedByShit()
{
    return isAttackedByShit;
}

void EnemySpriteClass::setIsAttackedByPin(bool flag)
{
    isAttackedByPin = flag;
}

bool EnemySpriteClass::getIsAttackedByPin()
{
    return isAttackedByPin;
}

void EnemySpriteClass::setIsAttackedByMushRoom(bool flag)
{
    isAttackedByMushRoom = flag;
}

bool EnemySpriteClass::getIsAttackedByMushRoom()
{
    return isAttackedByMushRoom;
}

void EnemySpriteClass::setIsAttackedBySnow(bool flag)
{
    isAttackedBySnow = flag;
}

bool EnemySpriteClass::getIsAttackedBySnow()
{
    return isAttackedBySnow;
}

void EnemySpriteClass::setEnemyObjectID(int objectID)
{
    enemyObjectId = objectID;
}

int EnemySpriteClass::getEnemyObjectID()
{
    return (enemyObjectId);
}

void EnemySpriteClass::setEnemyObjectToTowerNum_X(int num)
{
    enemyObjectToTowerNum_X = num;
}

int EnemySpriteClass::getEnemyObjectToTowerNum_X()
{
    return enemyObjectToTowerNum_X;
}

void EnemySpriteClass::setEnemyObjectToTowerNum_Y(int num)
{
    enemyObjectToTowerNum_Y = num;
}

int EnemySpriteClass::getEnemyObjectToTowerNum_Y()
{
    return enemyObjectToTowerNum_Y;
}

void EnemySpriteClass::setEnemyMonsterTypeID(GAME_ENEMY_MONSTERS_TYPE monsterID)
{
    enemyMonsterTypeID = monsterID;
}

GAME_ENEMY_MONSTERS_TYPE EnemySpriteClass::getEnemyMonsterTypeID()
{
    return enemyMonsterTypeID;
}

void EnemySpriteClass::setCurLifeValue(int value)
{
    curLifeValue = value;
    if (this->getIsDead() == true) {
        //this->removeFromParentAndCleanup(true);//i will change here on mainui
        CCAssert(!(deathArray == NULL), "cannot be NULL");
        if (this->retainCount() > 0) {//means 从来没有加入死亡之组
            deathArray->addObject(this);
        }
    }
    
    if (curLifeValue <= 0) {
        GameMusicConClass::sharedMusicCon()->playGameById(GAME_MUSIC_EFFECT_TYPE_ITEM_BOMB);
    }
    
}

int EnemySpriteClass::getCurLifeValue()
{
    return curLifeValue;
}


void EnemySpriteClass::setTotalLifeValue(int value)
{
    totalLifeValue = value;
    curLifeValue = totalLifeValue;
}

int EnemySpriteClass::getTotalLifeValue()
{
    return totalLifeValue;
}

bool EnemySpriteClass::getIsDead()
{
    bool isDead = false;
    
    if ((curLifeValue <= 0) || (this->retainCount() == 0) || (totalLifeValue == 0)) {
        isDead = true;
    }

    return isDead;
}

void EnemySpriteClass::setTargetPos(cocos2d::CCPoint pos, float speed)
{
    mTargetPos = pos;
    moveSpeed = speed;
}

void EnemySpriteClass::setMoveSpeed(float speed)
{
    moveSpeed = speed;
}

float EnemySpriteClass::getMoveSpeed()
{
    return moveSpeed;
}

CCPoint EnemySpriteClass::getTargetPos()
{
    return mTargetPos;
}

void EnemySpriteClass::setIsCanMove(bool flag)
{
    isCanMove = flag;
}

bool EnemySpriteClass::getIsCanMove()
{
    return isCanMove;
}

CCSize EnemySpriteClass::getEnemyBloodUISize()
{
    return fgLifeUI->getContentSize();
}

void EnemySpriteClass::runEffect()
{
    
}

void EnemySpriteClass::updateLifeUI()
{
    int tLife = this->getTotalLifeValue();
    int cLife = this->getCurLifeValue();
    
    CCSize fgSize = fgLifeUI->getContentSize();
    CCSize bgSize = bgLifeUI->getContentSize();
    
    float validWidth = fgSize.width - this->getCurLifeValue() * fgSize.width/this->getTotalLifeValue();
    
    bgLifeUI->setPosition(ccp((this->getCurLifeValue() * fgSize.width/this->getTotalLifeValue() + validWidth/2), fgSize.height/2));
    bgLifeUI->setScaleX(validWidth/bgSize.width);

}
//
void EnemySpriteClass::setIsSpeed2X(bool flag)
{
	float speed = this->getMoveSpeed();
   
   if (flag) {
       speed *= 2;
   }
   else if (!flag)
   {
       speed = speed / 2;
   }
   isSpeed2X = flag;
   this->setEnemySpeed(speed);
}

bool EnemySpriteClass::getIsSpeed2X()
{
   return isSpeed2X;
}

void EnemySpriteClass::setMoneyType(GAME_MONEY_SCORE_TYPE type)
{
    moneyType = type;
}

GAME_MONEY_SCORE_TYPE EnemySpriteClass::getMoneyType()
{
    return moneyType;
}

void EnemySpriteClass::setEnemyLifeAndSpeed(int life, float speed)
{
    this->setMoveSpeed(speed);
    this->setTotalLifeValue(life);
}

void EnemySpriteClass::setDeathArray(cocos2d::CCArray *death)
{
    CCAssert(!(death == NULL), "cannot be NULL");
    deathArray = death;
}

//void EnemySpriteClass::draw()
//{
//    if (isAttacked) {
//        
//        float offset = 8;
//        float bgoffset = 8;
//        float totalLen = MAX_NUM;
//        float life =  (this->getCurLifeValue() * MAX_NUM) / this->getTotalLifeValue();
//        CCSize s = this->getContentSize();
//        ccDrawColor4B(0, 255, 0, 255);
//        glLineWidth(1);
//        ccDrawRect(ccp(0,s.height), ccp(totalLen,s.height + offset));
//        ccDrawColor4B(0, 125, 0, 255);
//        glLineWidth(bgoffset);
//        ccDrawLine(CCPoint(0,s.height + 4), CCPoint(totalLen,s.height + 4));
//        ccDrawColor4B(0, 255, 0, 255);
//        glLineWidth(bgoffset);
//        ccDrawLine(CCPoint(0,s.height + 4), CCPoint(life,s.height + 4));
//    }
//    CCSprite::draw();
//}


