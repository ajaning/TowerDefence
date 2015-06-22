//
//  MoneyScoreClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-10-20.
//
//

#include "MoneyScoreClass.h"

MoneyScoreClass::MoneyScoreClass()
{

}

MoneyScoreClass::~MoneyScoreClass()
{

}

bool MoneyScoreClass::init(GAME_MONEY_SCORE_TYPE type, CCPoint pos)
{
    CCAssert(!(type == GAME_MONEY_SCORE_TYPE_NONE || type == GAME_MONEY_SCORE_TYPE_MAX), "cannot be invalid");
    
    char* pfileName = NULL;
    moneyScore = 0;
    float delta = 20;
    
    switch (type) {
        case GAME_MONEY_SCORE_TYPE_2:
            pfileName = "money02.png";
            moneyScore = 2;
            break;
        case GAME_MONEY_SCORE_TYPE_5:
            pfileName = "money05.png";
            moneyScore = 5;
            break;
        case GAME_MONEY_SCORE_TYPE_14:
            pfileName = "money14.png";
            moneyScore = 14;
            break;
        case GAME_MONEY_SCORE_TYPE_50:
            pfileName = "money50.png";
            moneyScore = 50;
            break;
        case GAME_MONEY_SCORE_TYPE_75:
            pfileName = "money75.png";
            moneyScore = 75;
            break;
        case GAME_MONEY_SCORE_TYPE_85:
            pfileName = "money85.png";
            moneyScore = 85;
            break;
        case GAME_MONEY_SCORE_TYPE_150:
            pfileName = "money150.png";
            moneyScore = 150;
            break;
        case GAME_MONEY_SCORE_TYPE_168:
            pfileName = "money168.png";
            moneyScore = 168;
            break;
        case GAME_MONEY_SCORE_TYPE_268:
            pfileName = "money268.png";
            moneyScore = 268;
            break;
        case GAME_MONEY_SCORE_TYPE_999:
            pfileName = "money999.png";
            moneyScore = 999;
            break;
        case GAME_MONEY_SCORE_TYPE_1000:
            pfileName = "money1000.png";
            moneyScore = 1000;
            break;
        case GAME_MONEY_SCORE_TYPE_1500:
            pfileName = "money1500.png";
            moneyScore = 1500;
            break;
        case GAME_MONEY_SCORE_TYPE_2500:
            pfileName = "money2500.png";
            moneyScore = 2500;
            break;
        case GAME_MONEY_SCORE_TYPE_99999:
            pfileName = "money99999.png";
            moneyScore = 99999;
            break;
        default:
            break;
    }
    
    CCAssert(!(pfileName == NULL), "cannot be null");
    CCSprite::initWithSpriteFrameName(pfileName);
    this->setPosition(pos);
    
    
    CCMoveBy* mby = CCMoveBy::create(1, ccp(0, delta));
    CCCallFuncN* callfn = CCCallFuncN::create(this, callfuncN_selector(MoneyScoreClass::toTargetCallBack));
    this->runAction((CCActionInterval*)(CCSequence::create(mby,callfn,NULL)));
    return true;
}

MoneyScoreClass* MoneyScoreClass::create(GAME_MONEY_SCORE_TYPE type, CCPoint pos)
{
    MoneyScoreClass* money = new MoneyScoreClass();
    if (money && money->init(type,pos)) {
        money->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(money);
    }
    return money;
}

int MoneyScoreClass::getMoneyScore()
{
    return moneyScore;
}

void MoneyScoreClass::toTargetCallBack(cocos2d::CCNode *object)
{
    this->removeFromParentAndCleanup(true);
}
