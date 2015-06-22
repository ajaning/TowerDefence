//
//  MoneyScoreClass.h
//  CaratonFatans
//
//  Created by jack on 13-10-20.
//
//

#ifndef __CaratonFatans__MoneyScoreClass__
#define __CaratonFatans__MoneyScoreClass__

#include <iostream>
#include "cocos2d.h"
#include "GameSpriteParm.h"
USING_NS_CC;

class MoneyScoreClass:public CCSprite
{
private:
    MoneyScoreClass();
    ~MoneyScoreClass();
    bool init(GAME_MONEY_SCORE_TYPE type, CCPoint pos);
	void toTargetCallBack(CCNode* object);
public:
    static MoneyScoreClass* create(GAME_MONEY_SCORE_TYPE type, CCPoint pos);
    int getMoneyScore();
private:
    int moneyScore;
};
#endif /* defined(__CaratonFatans__MoneyScoreClass__) */
