//
//  MapPassClass.h
//  CaratonFatans
//
//  Created by jack on 13-8-4.
//
//

#ifndef __CaratonFatans__MapPassClass__
#define __CaratonFatans__MapPassClass__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class MapPassClass:public CCNode
{
private:
    MapPassClass();
    ~MapPassClass();
    bool init(CCPoint pos,CCSize size);
public:
    static MapPassClass* create(CCPoint pos,CCSize size);
    bool getIsCanPutOnMap();
    void setIsCanPutOnMap(bool flag);
    CCSize getAreaSize();
    bool getIsDealed();
    void setIsDealed(bool flag);
private:
    bool isDealed;
    bool isCanPutOnMap;
    CCSize areaSize;
};
#endif /* defined(__CaratonFatans__MapPassClass__) */
