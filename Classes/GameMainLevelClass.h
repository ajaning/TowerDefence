//
//  GameMainLevelClass.h
//  CaratonFatans
//
//  Created by jack on 13-7-22.
//
//

#ifndef __CaratonFatans__GameMainLevelClass__
#define __CaratonFatans__GameMainLevelClass__

#include "cocos2d.h"
#include "ScrollViewClass.h"
USING_NS_CC;

class GameMainLevelClass:public CCLayer
{
private:
    GameMainLevelClass();
    ~GameMainLevelClass();
    bool init();
    CREATE_FUNC(GameMainLevelClass);

    void selLevelCallBack(void);
    void selMenuCallBack(CCObject* menu);
public:
    static CCScene* createMainLevel();
private:
    ScrollViewClass* selLevelScroll;
    
};

#endif /* defined(__CaratonFatans__GameMainLevelClass__) */
