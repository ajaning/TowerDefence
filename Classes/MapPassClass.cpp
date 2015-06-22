//
//  MapPassClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-8-4.
//
//

#include "MapPassClass.h"

MapPassClass::MapPassClass()
{

}

MapPassClass::~MapPassClass()
{

}

bool MapPassClass::init(CCPoint pos,CCSize size)
{
    isCanPutOnMap = false;
    this->setPosition(pos);
    areaSize = size;
    isDealed = false;
    return true;
}

MapPassClass* MapPassClass::create(CCPoint pos,CCSize size)
{
    MapPassClass* map = new MapPassClass();
    if (map && map->init(pos,size)) {
        map->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(map);
    }
    
    return map;
}

bool MapPassClass::getIsCanPutOnMap()
{
    return isCanPutOnMap;
}

void MapPassClass::setIsCanPutOnMap(bool flag)
{
    isCanPutOnMap = flag;
}

CCSize MapPassClass::getAreaSize()
{
    return areaSize;
}

bool MapPassClass::getIsDealed()
{
    return isDealed;
}

void MapPassClass::setIsDealed(bool flag)
{
    isDealed = flag;
}


