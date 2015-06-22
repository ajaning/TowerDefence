//
//  comSpriteActionClass.h
//  CaratonFatans
//
//  Created by  Jack on 13-11-24.
//
//

#ifndef __CaratonFatans__comSpriteActionClass__
#define __CaratonFatans__comSpriteActionClass__

#include <iostream>
#include "cocos2d.h"
#include "GameSpriteParm.h"
USING_NS_CC;

class comSpriteActionClass:public CCSprite
{
private:
    comSpriteActionClass();
    ~comSpriteActionClass();
    bool init(COM_ANI_TYPE type);
    
    void aniActionCallBack();
public:
    static comSpriteActionClass* create(COM_ANI_TYPE type);
private:
    
};


#endif /* defined(__CaratonFatans__comSpriteActionClass__) */
