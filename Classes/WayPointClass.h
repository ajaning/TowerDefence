//
//  WayPointClass.h
//  CaratonFatans
//
//  Created by jack on 13-7-26.
//
//

#ifndef __CaratonFatans__WayPointClass__
#define __CaratonFatans__WayPointClass__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class WayPointClass:public CCNode
{
private:
    WayPointClass();
    ~WayPointClass();
    bool init();
public:
    static WayPointClass* create();
    void addMoveNextTargetPos(CCPoint pos);
    CCPoint getNextTargetPos();
private:
    CCArray* nextPosArray;
    int curPosIndex;
    
};
#endif /* defined(__CaratonFatans__WayPointClass__) */
