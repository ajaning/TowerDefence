//
//  TowerSelPadClass.h
//  CaratonFatans
//
//  Created by jack on 13-8-11.
//
//

#ifndef __CaratonFatans__TowerSelPadClass__
#define __CaratonFatans__TowerSelPadClass__

#include <iostream>
#include "AttackTowerClass.h"

class TowerSelPadClass:public CCNode
{
private:
    TowerSelPadClass();
    ~TowerSelPadClass();
    bool init();
    bool init(CCObject* target,SEL_CallFunc func);
    
    void towerSelMenuCallBack(cocos2d::CCObject *parent);
public:
    CREATE_FUNC(TowerSelPadClass);
    static TowerSelPadClass* create(CCObject* target,SEL_CallFunc func);
    bool getIsShowTowerPAD();
    bool getIsHideTowerPAD();
    void setIsHideTowerPAD(bool flag);
    void showUpSelPad(AttackTowerClass* tower);
    void hideUpSelPad(AttackTowerClass* tower);
    void updateTowerSelPadState();
    
    bool getUserUpOrSellTower();//1-up,0-sell
    
private:
    bool isUserUpOrSellTower;//1-up,0-sell
    bool isTowerShowPAD;
    bool isTowerHidePAD;
    int updatePayMoney;
    GAME_TOWER_UPDATE_TYPE selTowerUpdateType;
    GAME_TOWER_TYPE selTowerType;
    CCMenuItemImage* upMenu;
    CCMenuItemImage* sellMenu;
    CCSprite* selSprite;
    CCSprite* killZoneSprite;
    
    CCObject* myTarget;
    SEL_CallFunc mySelector;
};
#endif /* defined(__CaratonFatans__TowerSelPadClass__) */
