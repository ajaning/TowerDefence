//
//  SkyLineDetailClass.h
//  CaratonFatans
//
//  Created by jack on 13-7-23.
//
//

#ifndef __CaratonFatans__SkyLineDetailClass__
#define __CaratonFatans__SkyLineDetailClass__

#include <iostream>
#include "cocos2d.h"
#include "ScrollViewClass.h"
class SkyLineDetailClass:public CCLayer
{
private:
    SkyLineDetailClass();
    ~SkyLineDetailClass();
    bool init();
    CREATE_FUNC(SkyLineDetailClass);
    void selScrollCallBack();
    void selMenuCallBack(CCObject* menu);
public:
    static CCScene* createSkyLine();
private:
    ScrollViewClass* detailScroll;
};

#endif /* defined(__CaratonFatans__SkyLineDetailClass__) */
