//
//  LcdAdapClass.h
//  CaratonFatans
//
//  Created by jack on 13-9-2.
//
//

#ifndef __CaratonFatans__LcdAdapClass__
#define __CaratonFatans__LcdAdapClass__

#include <iostream>

#include "cocos2d.h"

USING_NS_CC;

class LcdAdapClass:public CCNode
{
private:
    LcdAdapClass();
    ~LcdAdapClass();
    bool init();
    CREATE_FUNC(LcdAdapClass);
public:
    static LcdAdapClass* sharedLCDADAP();
    CCSize getWinSize();
    CCSize getFrameSize();
    void setAdaptorLayerSizeAndPos(CCLayer* layer);
    
    float getXScale();
    float getYScale();
    float getMapXScale();//for map
    float getMapYScale();//for map
    bool setAdaptorNodePos(CCNode* node,CCPoint pos);
    bool setAdaptorPos(CCNode* node,CCPoint pos);
    CCPoint setAdaptorMapPos(CCNode* node,CCPoint pos);
    CCPoint setAdaptorMapPos(CCPoint pos);
    CCSize getGameMapTiledSize();
    void setGameMapTiledSize(CCSize size);
	
    CCSize getLayerScaleSize();
    
    float getTowerKillRadiusScale();
    
private:
    float xScale;
    float yScale;
    float mapWidthScale;
    float mapHeightScale;
    CCSize gameMapTiledSize;
    CCSize validWinSize;
};


#endif /* defined(__CaratonFatans__LcdAdapClass__) */
