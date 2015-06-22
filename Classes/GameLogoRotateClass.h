//
//  GameLogoRotateClass.h
//  CaratonFatans
//
//  Created by jack on 13-8-1.
//
//

#ifndef __CaratonFatans__GameLogoRotateClass__
#define __CaratonFatans__GameLogoRotateClass__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class GameLogoRotateClass:public CCSprite
{
private:
	GameLogoRotateClass();
	~GameLogoRotateClass();
	bool init(CCPoint pos,CCObject* target,SEL_CallFunc selector);
	void rotateLogoCallBack();
	void gameGoCallBack();
public:
	static GameLogoRotateClass* create(CCPoint pos,CCObject* target,SEL_CallFunc selector);
private:
	int numIndex;
	CCSprite* numberSprite;
	CCSprite* rotateLogo;
    CCObject* myTarget;
    SEL_CallFunc mySelector;
};


#endif /* defined(__CaratonFatans__GameLogoRotateClass__) */
