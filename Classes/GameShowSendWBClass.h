//
//  GameShowSendWBClass.h
//  CaratonFatans
//
//  Created by jack on 13-12-7.
//
//

#ifndef __CaratonFatans__GameShowSendWBClass__
#define __CaratonFatans__GameShowSendWBClass__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class GameShowSendWBClass:public CCLayer
{
private:
    GameShowSendWBClass();
    ~GameShowSendWBClass();
    bool init();
    
    
    void wbBtnCallBack(CCObject* object);
    
public:
    static CCScene* createScene();
    CREATE_FUNC(GameShowSendWBClass);
private:
    CCTextFieldTTF* inputContentTTF;
    CCSprite* wbShowBGSprite;
    CCSprite* sendPicSprite;
    
    CCMenuItemImage* fansMenu;
    CCLabelTTF* inputNumLab;
    CCLabelTTF* userNameLab;
};
#endif /* defined(__CaratonFatans__GameShowSendWBClass__) */
