//
//  LcdAdapClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-9-2.
//
//

#include "LcdAdapClass.h"

//精灵图片参考的默认LCD宽度大小{
#define PIC_MAINLCD_WIDTH   (624.0)
#define PIC_MAINLCD_HEIGHT  (416.0)
//}

#define MAINLCD_STANDARD_WIDTH  (960.0)
#define MAINLCD_STANDARD_HEIGHT (640.0)

#define MAP_DEFAULT_WIDTH (960.0)
#define MAP_DEFAULT_HEIGHT (640.0)

#define TILEDMAP_WIDTH (80.0)
#define TILEDMAP_HEIGHT (80.0)

static LcdAdapClass* sharedLCDInstance = NULL;

LcdAdapClass::LcdAdapClass()
{
    
}

LcdAdapClass::~LcdAdapClass()
{
    
}

bool LcdAdapClass::init()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCSize frameSize = CCDirector::sharedDirector()->getWinSize();//CCEGLView::sharedOpenGLView()->getFrameSize();
    
#else
    CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
#endif
    float wh = PIC_MAINLCD_WIDTH/PIC_MAINLCD_HEIGHT;
    float tmpWidth = frameSize.height;
    float tmpHeight = frameSize.width;
    
    validWinSize = CCSize(1, 1);
    tmpWidth = tmpHeight * wh;
    if (tmpWidth > frameSize.width) {
        tmpWidth = frameSize.width;
        tmpHeight = frameSize.width / wh;
        if (tmpHeight > frameSize.height) {
            tmpHeight = frameSize.height;
            tmpWidth = tmpHeight * wh;
        }
    }
    
    validWinSize.width = tmpWidth;
    validWinSize.height = tmpHeight;
    
    xScale = validWinSize.width / PIC_MAINLCD_WIDTH;
    yScale = validWinSize.height / PIC_MAINLCD_HEIGHT;
    
    mapWidthScale = validWinSize.width / MAP_DEFAULT_WIDTH;
    mapHeightScale = validWinSize.height / MAP_DEFAULT_HEIGHT;
    
    gameMapTiledSize = CCSizeMake(TILEDMAP_WIDTH, TILEDMAP_HEIGHT);
    CCLOG("the lcdsizeclass xScale = %f yScale = %f",xScale,yScale);
    return true;
}

LcdAdapClass* LcdAdapClass::sharedLCDADAP()
{
    if (sharedLCDInstance == NULL) {
        //sharedLCDInstance = LcdAdapClass::create();
        sharedLCDInstance = new LcdAdapClass();
        sharedLCDInstance->init();
    }
    
    return sharedLCDInstance;
}

float LcdAdapClass::getXScale()
{
    return xScale;
}

float LcdAdapClass::getYScale()
{
    return yScale;
}

bool LcdAdapClass::setAdaptorNodePos(cocos2d::CCNode *node, cocos2d::CCPoint pos)
{
    CCAssert(!(node == NULL), "node cannot be NULL");
    CCSize nodeSize = node->getContentSize();
    
    if ((nodeSize.width < validWinSize.width) && (nodeSize.height < validWinSize.height)) {
        node->setScaleX(xScale);
        node->setScaleY(yScale);
    }
    node->setPosition(pos);
    return true;
}

bool LcdAdapClass::setAdaptorPos(cocos2d::CCNode *node, cocos2d::CCPoint pos)
{
    CCAssert(!(node == NULL), "node cannot be NULL");
    float x = pos.x * xScale;
    float y = pos.y * yScale;
    
    node->setPosition(ccp(x,y));
    return true;
}

CCPoint LcdAdapClass::setAdaptorMapPos(cocos2d::CCNode *node, cocos2d::CCPoint pos)
{
    CCAssert(!(node == NULL), "node cannot be NULL");
    
    float x = pos.x * mapWidthScale;
    float y = pos.y * mapHeightScale;
    
    node->setPosition(ccp(x,y));
    
    return ccp(x,y);
}


CCPoint LcdAdapClass::setAdaptorMapPos(cocos2d::CCPoint pos)
{
    float x = pos.x * mapWidthScale;
    float y = pos.y * mapHeightScale;
    
    
    return ccp(x,y);
}

float LcdAdapClass::getMapXScale()
{
    return mapWidthScale;
}

float LcdAdapClass::getMapYScale()
{
    return mapHeightScale;
}

void LcdAdapClass::setGameMapTiledSize(cocos2d::CCSize size)
{
    gameMapTiledSize = size;
}

CCSize LcdAdapClass::getGameMapTiledSize()
{
    return CCSizeMake(gameMapTiledSize.width * mapWidthScale, gameMapTiledSize.height * mapHeightScale);
}

CCSize LcdAdapClass::getWinSize()
{
    return validWinSize;
}

CCSize LcdAdapClass::getFrameSize()
{
    return CCEGLView::sharedOpenGLView()->getFrameSize();
}

void LcdAdapClass::setAdaptorLayerSizeAndPos(cocos2d::CCLayer *layer)
{
    CCAssert(!(layer == NULL), "cannot be NULL");
    //CCSize frameSize = CCEGLView::sharedOpenGLView()->getViewRealSize();//CCEGLView::sharedOpenGLView()->getFrameSize();
    
    layer->setContentSize(validWinSize);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    layer->setPosition(CCPoint(0, 0));
#else
    CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    layer->setPosition(ccp((frameSize.width - validWinSize.width) / 2, (frameSize.height - validWinSize.height) / 2.0));
#endif
}

CCSize LcdAdapClass::getLayerScaleSize()
{
    CCSize scaleSize = CCSize(validWinSize.width / MAINLCD_STANDARD_WIDTH, validWinSize.height / MAINLCD_STANDARD_HEIGHT);
    
    return scaleSize;
}

float LcdAdapClass::getTowerKillRadiusScale()
{
    //TOWER中的杀伤半径是我在960*640的调制的，你可以根据你的喜好设置
    float scale = 1;
    float maxValue = MAX((int)validWinSize.width, (int)validWinSize.height);
    
    scale = maxValue / MAINLCD_STANDARD_WIDTH;//ccpLength(ccp(validWinSize.width / MAINLCD_STANDARD_WIDTH, validWinSize.height / MAINLCD_STANDARD_HEIGHT));
    
    return scale;
}
