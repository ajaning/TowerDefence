//
//  GameShowValidPos.h
//  CaratonFatans
//
//  Created by jack on 13-8-1.
//
//

#ifndef __CaratonFatans__GameShowValidPos__
#define __CaratonFatans__GameShowValidPos__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class GameShowValidPos:public CCSprite
{
private:
	GameShowValidPos();
	~GameShowValidPos();
	bool init();
	void toShowPosCallBack();
public:
	CREATE_FUNC(GameShowValidPos);
private:
	int showIndex;
	CCAnimation* showAni;
};


#endif /* defined(__CaratonFatans__GameShowValidPos__) */
