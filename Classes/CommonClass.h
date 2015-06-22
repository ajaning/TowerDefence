//
//  CommonClass.h
//  CaratonFatans
//
//  Created by jack on 13-9-27.
//
//

#ifndef __CaratonFatans__CommonClass__
#define __CaratonFatans__CommonClass__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class CommonClass:public CCNode
{
private:
    CommonClass();
    ~CommonClass();
    bool init();
    CREATE_FUNC(CommonClass);
public:
    static CommonClass* getSharedCommon();
    float ConvertSpeedToTime(float length,float speed);
    CCPoint getGameFromToRealPos(CCPoint fromPos,CCPoint toPos);
};
#endif /* defined(__CaratonFatans__CommonClass__) */
