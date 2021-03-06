//
//  ObjectClass.h
//  CaratonFatans
//
//  Created by jack on 13-7-24.
//
//

#ifndef __CaratonFatans__ObjectClass__
#define __CaratonFatans__ObjectClass__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class ObjectClass:public CCSprite
{
public:
    ObjectClass();
    ~ObjectClass();
    bool init(const char *pFilename);
    static ObjectClass* createObject(const char *pFilename);
    void setCurLifeValue(int value);
    int getCurLifeValue(void);
    void setTotalLifeValue(int value);
    int getTotalLifeValue(void);
    bool getIsDead(void);
    bool getIsDealed();
    void setIsDealed(bool flag);
    void setMoveSpeed(float speed);
    float getMoveSpeed(void);
    void setIsSpeed2X(bool flag);
    bool getIsSpeed2X();
    void setIsCanMove(bool flag);
    bool getIsCanMove();
    CCPoint getTargetPos();
    void setTargetPos(CCPoint pos,float speed);
    virtual void update(float dt);
    virtual void ToTargetPosCallBack(void);
    
    void setDeathArray(CCArray* death);
private:
    bool isDealed;//已经被处理过，如用于死亡时回收
    bool isSpeed2X;//移动速度加快两倍
    bool isCanMove;
    bool isDead;
    float moveSpeed;
    int curLifeValue;
    int totalLifeValue;
    CCPoint mTargetPos;
    CCArray* deathArray;
};



#endif /* defined(__CaratonFatans__ObjectClass__) */
