//
//  ShowWinLoseClass.h
//  CaratonFatans
//
//  Created by jack on 13-10-30.
//
//

#ifndef __CaratonFatans__ShowWinLoseClass__
#define __CaratonFatans__ShowWinLoseClass__

#include <iostream>
#include "cocos2d.h"
#include "GameSpriteParm.h"
USING_NS_CC;
class ShowWinLoseClass:public CCLayerColor
{
private:
    ShowWinLoseClass();
    ~ShowWinLoseClass();
    bool init();
    CREATE_FUNC(ShowWinLoseClass);
    void menuSelCallBack(CCObject* object);
public:
    static ShowWinLoseClass* sharedShow(gameWinLoseStruct winLoseData);
    void setGameWinLoseData(gameWinLoseStruct winLoseData);
    void showGameOver(CCNode* parent);
private:
    gameWinLoseStruct gameWinLoseData;
};
#endif /* defined(__CaratonFatans__ShowWinLoseClass__) */
