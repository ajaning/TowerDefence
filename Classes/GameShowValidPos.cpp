#include "GameShowValidPos.h"
#define NUMBER_MAX	(3)

GameShowValidPos::GameShowValidPos()
{

}

GameShowValidPos::~GameShowValidPos()
{
	showAni->release();
}

bool GameShowValidPos::init()
{
	char* pFileName = "select_00.png";
	char buffer[100] = {0};
    CCArray* aniArray = CCArray::create();
    
	showIndex = 0;
	CCSprite::initWithSpriteFrameName(pFileName);
	

	for (int i = 0; i < 1;i++)
	{
		memset(buffer, 0, sizeof(buffer));
		sprintf(buffer, "%s%02d.png","select_",i);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
		aniArray->addObject(frame);
		if (i == 0) {
			CCSprite::initWithSpriteFrame(frame);
		}
	}

	showAni = CCAnimation::createWithSpriteFrames(aniArray, 1);
    
	showAni->retain();
    CCFadeOut* out  = CCFadeOut::create(1);
	CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(GameShowValidPos::toShowPosCallBack));
	this->runAction((CCActionInterval*)CCSequence::create(CCAnimate::create(showAni),out,CCAnimate::create(showAni),out,CCAnimate::create(showAni),out,callfunc,NULL));
    
    return true;
}


void GameShowValidPos::toShowPosCallBack()
{

//	showIndex++;
//
//	this->stopAllActions();
//	if (showIndex < NUMBER_MAX)
//	{
//        CCFadeOut* out  = CCFadeOut::create(1);
//        CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(GameShowValidPos::toShowPosCallBack));
//        this->runAction((CCActionInterval*)CCSequence::create(CCAnimate::create(showAni),out,callfunc,NULL));
//	}
//	else
	{
		this->removeFromParentAndCleanup(true);
	}
	
}
