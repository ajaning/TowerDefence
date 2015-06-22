#include "GameLogoRotateClass.h"
#define NUMBER_MAX	(3)

GameLogoRotateClass::GameLogoRotateClass()
{

}

GameLogoRotateClass::~GameLogoRotateClass()
{

}

bool GameLogoRotateClass::init(CCPoint pos,CCObject* target,SEL_CallFunc selector)
{
	char* pFileName = "countdown_11.png";
	char* rotateFileName = "countdown_12.png";
	char* numFileName = "countdown_";
	float angle = (-360 * 3);
    char buffer[100] = {0};
    CCArray* aniArray = CCArray::create();
	
    CCAssert(!(target == NULL), "cannot be NULL");
    CCAssert(!(selector == NULL), "cannot be NULL");
    
    myTarget = target;
    mySelector = selector;
    
	numIndex = 0;
	CCSprite::initWithSpriteFrameName(pFileName);
	this->setPosition(pos);

    CCSize size = this->getContentSize();
	rotateLogo = CCSprite::createWithSpriteFrameName(rotateFileName);
	this->addChild(rotateLogo,1);
	rotateLogo->setPosition(ccp(size.width / 2,size.height / 2));

	CCRotateBy* roBy = CCRotateBy::create(3,angle);
	CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(GameLogoRotateClass::rotateLogoCallBack));
	rotateLogo->runAction(CCSequence::create(roBy,NULL));

    for (int i = 1; i < 4; i++) {
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%s%02d.png",numFileName,i);
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
        CCAssert(!(frame == NULL), "cannot be NULL");
        aniArray->addObject(frame);
        if (i == 1) {
            numberSprite = CCSprite::createWithSpriteFrame(frame);
            numberSprite->setPosition(ccp(size.width / 2,size.height / 2));
            this->addChild(numberSprite,2);
        }
    }
    
	CCAssert(!(numberSprite == NULL), "cannot be NULL");
    CCAnimation* ani = CCAnimation::createWithSpriteFrames(aniArray, 1);
    numberSprite->runAction((CCActionInterval*)CCSequence::create(CCAnimate::create(ani),CCCallFunc::create(this, callfunc_selector(GameLogoRotateClass::rotateLogoCallBack)),NULL));
    
    return true;
}


GameLogoRotateClass* GameLogoRotateClass::create(CCPoint pos,CCObject* target,SEL_CallFunc selector)
{
	GameLogoRotateClass* logo = new GameLogoRotateClass();

	if (logo && logo->init(pos,target,selector))
	{
		logo->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(logo);
	}
	return logo;
}

void GameLogoRotateClass::rotateLogoCallBack()
{
//	char buffer[100] = {0};
//
//	{
//		CCArray* aniArray = CCArray::create();
//        CCSize size = this->getContentSize();
//
//		rotateLogo->setVisible(false);
//		numberSprite->setVisible(false);
//		CCSprite* go = CCSprite::createWithSpriteFrameName("countdown_13.png");
//		go->setPosition(ccp(size.width / 2, size.height / 2));
//		CCAnimation* ani = CCAnimation::createWithSpriteFrames(aniArray, 2);
//		CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(GameLogoRotateClass::gameGoCallBack));
//		go->runAction((CCActionInterval*)CCSequence::create(CCAnimate::create(ani),CCMoveBy::create(2, ccp(0, 0)),callfunc,NULL));
//
//		this->addChild(go,100);
//
//		
//	}
    this->gameGoCallBack();
}


void GameLogoRotateClass::gameGoCallBack()
{
    (myTarget->*mySelector)();
    
	this->removeFromParentAndCleanup(true);
}
