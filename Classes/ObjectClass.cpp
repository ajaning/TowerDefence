//
//  ObjectClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-7-24.
//
//

#include "ObjectClass.h"
#define MIN_OFFSET  (5.0f)

ObjectClass::ObjectClass()
{

}

ObjectClass::~ObjectClass()
{

}

bool ObjectClass::init(const char *pFilename)
{
    CCAssert(!(pFilename == NULL), "cannot be NULL");
    
    deathArray = NULL;
    curLifeValue = 50;
    totalLifeValue = 50;
    isDealed = false;
    isDead = false;
    CCSprite::initWithSpriteFrameName(pFilename);
    return true;
}

ObjectClass* ObjectClass::createObject(const char *pFilename)
{
    CCAssert(!(pFilename == NULL), "cannot be NULL");
    ObjectClass* object = new ObjectClass();
    if (object && object->init(pFilename)) {
        object->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(object);
    }
    return object;
}

void ObjectClass::setCurLifeValue(int value)
{
    curLifeValue = value;
    if (this->getIsDead() == true) {
        //this->removeFromParentAndCleanup(true);//i will change here on mainui
        CCAssert(!(deathArray == NULL), "cannot be NULL");
        if (this->retainCount() > 0) {//means 从来没有加入死亡之组
            deathArray->addObject(this);
        }
    }
}

void ObjectClass::setDeathArray(cocos2d::CCArray *death)
{
    CCAssert(!(death == NULL), "cannot be NULL");
    
    deathArray = death;
}

int ObjectClass::getCurLifeValue()
{
    return curLifeValue;
}

void ObjectClass::setTotalLifeValue(int value)
{
    totalLifeValue = value;
    curLifeValue = totalLifeValue;
}

int ObjectClass::getTotalLifeValue()
{
    return totalLifeValue;
}

bool ObjectClass::getIsDead()
{
    if ((curLifeValue <= 0) || (this->retainCount() == 0)) {
        isDead = true;
    }
    else
    {
        isDead = false;
    }
    return isDead;
}

bool ObjectClass::getIsDealed()
{
    return isDealed;
}

void ObjectClass::setIsDealed(bool flag)
{
    isDealed = flag;
}


void ObjectClass::setIsSpeed2X(bool flag)
{
    
    if (flag && !isSpeed2X) {
        moveSpeed = moveSpeed * 2;
    }
    else if (isSpeed2X)
    {
        moveSpeed = moveSpeed / 2;
    }
    isSpeed2X = flag;
}

bool ObjectClass::getIsSpeed2X()
{
    return isSpeed2X;
}

void ObjectClass::setMoveSpeed(float speed)
{
    moveSpeed = speed;
}

float ObjectClass::getMoveSpeed()
{
    return moveSpeed;
}

void ObjectClass::setIsCanMove(bool flag)
{
    if (flag) {
//        this->unscheduleUpdate();
//        this->scheduleUpdate();
    }
    else
    {
//        this->unscheduleUpdate();
    }
    isCanMove = flag;
}

bool ObjectClass::getIsCanMove()
{
    return isCanMove;
}

void ObjectClass::setTargetPos(cocos2d::CCPoint pos, float speed)
{
    mTargetPos = pos;
    moveSpeed = speed;
}

CCPoint ObjectClass::getTargetPos()
{
    return mTargetPos;
}

void ObjectClass::update(float dt)
{
    if (isCanMove) {
        CCPoint offset = ccpSub(mTargetPos, this->getPosition());
        
        if (ccpLength(offset) == 0) {
            this->ToTargetPosCallBack();
            CCPoint pos = this->getPosition();
            CCLOG("i moved to target ");
            return;
        }
        
        if (ccpLength(offset) < MIN_OFFSET) {
            this->setPosition(mTargetPos);
            CCLOG("i moved to target ");
            return;
        }
        
        CCPoint targetVector = ccpNormalize(offset);
        CCPoint targetPerSpeed = ccpMult(targetVector, moveSpeed);
        CCPoint actuTarget = ccpAdd(this->getPosition(), ccpMult(targetPerSpeed, dt));
        
        this->setPosition(actuTarget);
        CCLog("set pos x = %f y = %f",actuTarget.x,actuTarget.y);
    }
    
}

void ObjectClass::ToTargetPosCallBack()
{
    
}
