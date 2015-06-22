//
//  PetsNestClass.h
//  CaratonFatans
//
//  Created by  Jack on 13-11-25.
//
//

#ifndef __CaratonFatans__PetsNestClass__
#define __CaratonFatans__PetsNestClass__

#include <iostream>
#include "cocos2d.h"
#include "ScrollViewClass.h"
#include "GameSpriteParm.h"
USING_NS_CC;

class PetsNestClass:public CCLayer
{
private:
    PetsNestClass();
    ~PetsNestClass();
    bool init();
    CREATE_FUNC(PetsNestClass);
    
    //static PetsNestClass* create();
    void initPetLayer();
    
    void initTipsBG();
    
    void gotoPage(int index);
    void menuSelActionCallBack(CCObject* object);
    
    void updateUserNumLab();
    
    void showPopUpBG();
    
    void popupMenuSelCallBack(CCObject* object);
    
    void updateFarmPets();
    
    void updateUserFoodsNumAndPets();
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
public:
    static CCScene* createScene();
private:
    
    bool isShowPopUP;
    int layerNum;
    int layerPosIndex;
    
    PETS_BREED_EGG_TYPE selEggType;
    PETS_EGG_STATE_TYPE selEggState;
    
    
    CCLabelAtlas* userMilkNumLab;
    CCLabelAtlas* userCookiNumLab;
    CCLabelAtlas* userNestNumLab;
    
    CCPoint startTouchPos;
    
    CCArray* petsEggArray;
    
    CCSprite* gameBG;
    CCSprite* whaleBG;
    CCLayer* farmLayer;
    
    
    CCLabelAtlas* userMedicneNumLab;
    CCSprite* tipShowBG;
    CCSprite* tipLeftIconBG;
    CCSprite* tipLeftSprite;
    CCSprite* tipCenterTextSprite;
    
    CCMenuItemImage* popupYESMenuItem;
    CCSprite* menuYESText;    
    
    CCSprite* shareWBSprite;
};

#endif /* defined(__CaratonFatans__PetsNestClass__) */
