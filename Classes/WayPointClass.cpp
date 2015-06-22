//
//  WayPointClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-7-26.
//
//

#include "WayPointClass.h"

WayPointClass::WayPointClass()
{

}

WayPointClass::~WayPointClass()
{
    nextPosArray->release();
}

bool WayPointClass::init(void)
{
    nextPosArray = CCArray::create();
    nextPosArray->retain();

    curPosIndex = 0;
    this->setPosition(CCPointZero);
    return true;
}

WayPointClass* WayPointClass::create(void)
{
    WayPointClass* way = new WayPointClass();
    if (way && way->init()) {
        way->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(way);
    }
    return way;
}

void WayPointClass::addMoveNextTargetPos(cocos2d::CCPoint pos)
{
    CCAssert(!(nextPosArray == NULL), "cannot be NULL");
    CCNode* tmpPos = CCNode::create();
    tmpPos->setPosition(pos);
    nextPosArray->addObject(tmpPos);
    
}

CCPoint WayPointClass::getNextTargetPos()
{
    CCAssert(!(nextPosArray == NULL), "cannot be NULL");
	return CCPoint(0, 0);
}

