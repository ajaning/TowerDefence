//
//  HelpPlayGame.h
//  CaratonFatans
//
//  Created by jack on 13-11-19.
//
//

#ifndef __CaratonFatans__HelpPlayGame__
#define __CaratonFatans__HelpPlayGame__

#include <iostream>
#include "cocos2d.h"
#include "GameSpriteParm.h"
USING_NS_CC;

class HelpPlayGame:public CCLayer
{
private:
    HelpPlayGame();
    ~HelpPlayGame();
    bool init(CCObject* target, SEL_CallFunc func,CCPoint padPos);
    
    
    void helpBGActionCallBack();
    void jumpBGActionCallBack();
    void jumpMenuCallBack(CCObject *object);
    
    void helpBGShowTopMidBottomTxtCallBack();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
public:
    static HelpPlayGame* create(CCObject* target, SEL_CallFunc func,CCPoint padPos);
    
    HELP_PLAYGAME_STATE_TYPE getHelpStateType();
    void setHelpStateType(HELP_PLAYGAME_STATE_TYPE type);
    void restartHelpNow();//重新开始
    void setPadDictorPos(CCPoint pos);
    void updateShowHelpPlayState(void);
private:
    int showTopMidBottomTxtIndex;
    
    CCPoint padDictorPos;
    CCArray* pointArray;//指向位置的POINT
    
    CCObject* myTarget;
    SEL_CallFunc mySelector;
    
    CCNode* helpNode;
    HELP_PLAYGAME_STATE_TYPE helpStateType;
    CCPoint selPadPoint;
    
    CCSprite* handSprite;
    
    CCSprite* helpBGSprite;
    CCSprite* helpPicSprite;
    CCSprite* helpPicTextSprite;
    
    CCSprite* helpBGTopTxtSprite;
    CCSprite* helpBGMidTxtSprite;
    CCSprite* helpBGBottomTxtSprite;
    
    CCSprite* selPadSprite;
    CCSprite* jumpBGSprite;
};
#endif /* defined(__CaratonFatans__HelpPlayGame__) */
