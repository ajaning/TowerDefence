//
//  TowerAddTypeClass.h
//  CaratonFatans
//
//  Created by jack on 13-8-15.
//
//

#ifndef __CaratonFatans__TowerAddTypeClass__
#define __CaratonFatans__TowerAddTypeClass__

#include <iostream>
#include "cocos2d.h"
#include "GameSpriteParm.h"

USING_NS_CC;
class TowerAddTypeClass:public CCNode
{
private:
    TowerAddTypeClass();
    ~TowerAddTypeClass();
    bool init(CCObject *target, SEL_CallFunc selector);
    void towerAddMenuCallBack(cocos2d::CCObject *parent);
public:
    static TowerAddTypeClass* create(CCObject *target, SEL_CallFunc selector);
    void setValidTowerType(int type);
    void showAddTowerType();
    void hideAddTowerType();
    void setAddTowerType(GAME_TOWER_TYPE type);
    GAME_TOWER_TYPE getAddTowerType();
    void updateTowerBueState();
	void updateAddTowerShowState();
    static TowerAddTypeClass* sharedTowerAdd();
    bool getIsShowAddTowerType();
    void setIsShowAddTowerType(bool flag);
    bool getIsHideAddTowerType();
    void setIsHideAddTowerType(bool flag);
private:
    bool isShowAddTowerType;
    bool isHideAddTowerType;
	int addTowerMoneyValue;
    int validTowerType;
    GAME_TOWER_TYPE addTowerType;
    CCSprite* selBG;
    CCMenuItemImage* anchor;
    CCMenuItemImage* arrow;
    CCMenuItemImage* ball;
    CCMenuItemImage* bluestar;
    CCMenuItemImage* bottle;
    CCMenuItemImage* buff;
    CCMenuItemImage* cuttle;
    CCMenuItemImage* fan;
    CCMenuItemImage* firebottle;
    CCMenuItemImage* fish;
    CCMenuItemImage* mushroom;
    CCMenuItemImage* pin;
    CCMenuItemImage* plane;
    CCMenuItemImage* rocket;
    CCMenuItemImage* shit;
    CCMenuItemImage* snow;
    CCMenuItemImage* star;
    CCMenuItemImage* sun;
    CCObject* myTarget;
    SEL_CallFunc mySelector;
};
#endif /* defined(__CaratonFatans__TowerAddTypeClass__) */
