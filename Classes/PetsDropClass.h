//
//  PetsDropClass.h
//  CaratonFatans
//
//  Created by  Jack on 13-11-21.
//
//

#ifndef __CaratonFatans__PetsDropClass__
#define __CaratonFatans__PetsDropClass__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class PetsDropClass:public CCLayer
{
private:
    PetsDropClass();
    ~PetsDropClass();
    bool init();
    bool init(CCObject* target,SEL_CallFunc func);
    
    
    void generateGiftsType();
    char* generateGiftsEggType();
    void showGift(char* pFileName,char* pFileCNName,char* eggFileName,int scoreNum);
    
    void menuBtnCallBack(CCObject* object);
    
    void spriteActionCallBack(CCNode* object);
public:
    static PetsDropClass* create();
    static PetsDropClass* create(CCObject* target,SEL_CallFunc func);
    void showWaleGift();//当鲸鱼死亡的时候展示鲸鱼蛋
private:
    CCObject* myTarget;
    SEL_CallFunc myFunc;
};
#endif /* defined(__CaratonFatans__PetsDropClass__) */
