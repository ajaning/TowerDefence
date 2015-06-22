//
//  gameShopClass.h
//  CaratonFatans
//
//  Created by jack on 13-12-25.
//
//

#ifndef __CaratonFatans__gameShopClass__
#define __CaratonFatans__gameShopClass__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class gameShopClass:public CCLayer
{
private:
    gameShopClass();
    ~gameShopClass();
    bool init(void);
    bool init(CCObject* target,SEL_CallFunc func);

    void loadResAndInit();

    void updateMenuBuyState();
    void menuActionCallBack(CCObject* object);

    void generateEggType();
    void showBuySuccessTips(char* showText);

    void showBuySuccessCallBack(CCNode* node);

    virtual void onEnter();
    virtual void onExit();

public:
    CREATE_FUNC(gameShopClass);
    static gameShopClass* create(CCObject* target,SEL_CallFunc func);
private:

    int userStoneNum;
    CCLabelAtlas* userStoneNumLab;
    CCSprite* gameShopBgSprite;

    CCMenuItemImage* cookieBuyMenu;
    CCMenuItemImage* milkBuyMenu;
    CCMenuItemImage* nestBuyMenu;
    CCMenuItemImage* medicineBuyMenu;
    CCMenuItemImage* eggBuyMenu;

    CCObject* myTarget;
    SEL_CallFunc myFunc;
};



#endif /* defined(__CaratonFatans__gameShopClass__) */
