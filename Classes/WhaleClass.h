//
//  WhaleClass.h
//  CaratonFatans
//
//  Created by jack on 13-11-13.
//
//

#ifndef __CaratonFatans__WhaleClass__
#define __CaratonFatans__WhaleClass__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class WhaleClass:public CCLayer
{
private:
    WhaleClass();
    ~WhaleClass();
    bool init();
    static WhaleClass* create();
    bool init(CCObject* target, SEL_CallFunc func);
    
    void whaleMovePathAni();
    void whaleMovePathAniTarget1CallBack();
    void whaleMovePathAniTarget2CallBack();
    void whaleMovePathAniTarget3CallBack();
    
    void checkWhaleWhichSpeechShowWhileByTouched();
    void setWhaleSpeechShowID(int index);
    void whaleSpeechShowOrNotCallBack(float delta);
    
    bool checkUserPointInWhaliBody(CCPoint curPoint);
    
    virtual void update(float dt);
    
    void updateWhaleAniShowByID(int aniId,bool isShow);
    void updateWhaleLifeValue(int value);
    
    void cutWhaleAniStart(CCPoint beginPos,CCPoint lastPos);
    
    void cutWhaleAniCallBack(CCNode* object);
    
    void gameLevelHideActCallBack(CCNode* node);//游戏关卡隐藏动画，动画结束后，鲸鱼血量开始出现
    
    virtual void onEnter();
    virtual void onExit();
    //virtual void registerWithTouchDispatcher(void);
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
public:
    //CREATE_FUNC(WhaleClass);
    
    static WhaleClass* create(CCObject* target, SEL_CallFunc func);
    int getCurLifeValue();
    int getTotalLifeValue();
    void getGameCurLevelAndTotalLevel(int curLevel,int totalLevel);
    
    void whaleGiftShowWhileDead();
private:
    bool isWhaleSpeechShow;//鲸鱼台词显现
    int whaleSpeechId;
    bool isUpdateTimerStart;//检测this->scheduleupdate();是否有效，防止重复开启
    int userTouchNum;//用户当前触摸手指数
    int userTouchMovedCounter;//当USER一直滑动，但没有抬起，当判定最后的点在update时间内计数一定的时间都是一样的数值就认为用户一个方向的滑动结束
    
    int whaleTotalLifeValue;
    int whaleCurLifeValue;
    
    CCObject* myTarget;
    SEL_CallFunc myFunc;
    
    CCSprite* whaleBlood1;//整个血量
    CCSprite* whaleBlood2;//移动显示减少的血量
    
    CCArray* userTouch1Array;//0-beging,1-curpoint,2-prepoint,3-diffpoint
    CCArray* userTouch2Array;
    CCArray* userTouch3Array;
    CCArray* userTouch4Array;
    CCArray* userTouch5Array;
    
    CCSprite* whaleBody;//鲸鱼身体
    CCSprite* whaleEye;//鲸鱼眼睛
    CCSprite* whaleEyePupil;//鲸鱼瞳孔
    CCSprite* whaleSpray;//鲸鱼喷水柱
    CCSprite* whaleTail;//鲸鱼尾巴
    
    CCSprite* whaleSpeechBG;//鲸鱼台词背景
    CCSprite* whaleAngry;//鲸鱼生气表情
    CCSprite* whaleBodyGauze;//鲸鱼身体中间贴邦迪
    CCSprite* whaleTailGauze;//鲸鱼尾巴邦迪
    CCSprite* whaleWarnning;//鲸鱼警告标志
    CCSprite* whaleBleeding;//鲸鱼流血了
    CCSprite* whaleEyePanicBegin;//鲸鱼开始惊恐的眼神
    CCSprite* whaleEyePanicNow;//鲸鱼眼神惊恐大了
    CCSprite* whaleEyeTear;//鲸鱼流泪了
    CCSprite* whaleleftEyeHurt;//鲸鱼左边眼珠流出来了
};
#endif /* defined(__CaratonFatans__WhaleClass__) */
