//
//  FontShowClass.h
//  CaratonFatans
//
//  Created by jack on 13-7-21.
//
//

#ifndef __CaratonFatans__FontShowClass__
#define __CaratonFatans__FontShowClass__

//#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class FontShowClass:public CCNode
{
private:
    FontShowClass();
    ~FontShowClass();
    bool init();
    CREATE_FUNC(FontShowClass);
public:
    FontShowClass* sharedFont();
    
};
#endif /* defined(__CaratonFatans__FontShowClass__) */
