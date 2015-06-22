//
//  ShowTowerFeatureClass.h
//  CaratonFatans
//
//  Created by jack on 13-11-11.
//
//

#ifndef __CaratonFatans__ShowTowerFeatureClass__
#define __CaratonFatans__ShowTowerFeatureClass__

#include <iostream>
#include "cocos2d.h"
#include "GameSpriteParm.h"
USING_NS_CC;

class ShowTowerFeatureClass:public CCLayerColor
{
private:
    ShowTowerFeatureClass();
    ~ShowTowerFeatureClass();
    bool init(GAME_SUBROUND_ADD_NEW_TOWER_TYPE towerShowType,CCObject *target, SEL_CallFunc selector);
    bool init(GAME_SUBROUND_ADD_NEW_TOWER_TYPE towerShowType);
    
    void towerBGFlipActionCallBack();
    
    void selMenuCallBack(CCObject *object);
public:
    //CREATE_FUNC(ShowTowerFeatureClass);
    static ShowTowerFeatureClass* create(GAME_SUBROUND_ADD_NEW_TOWER_TYPE towerShowType,CCObject *target, SEL_CallFunc selector);
    static ShowTowerFeatureClass* create(GAME_SUBROUND_ADD_NEW_TOWER_TYPE towerShowType);
private:
    CCObject* myTarget;
    SEL_CallFunc mySelector;
    
    CCSprite* towerBGSprite;
    CCSprite* bgShade1Sprite;
    CCSprite* bgShade2Sprite;
    CCSprite* bgShade3Sprite;
    CCSprite* bgFlashSprite;
    
};

#endif /* defined(__CaratonFatans__ShowTowerFeatureClass__) */
