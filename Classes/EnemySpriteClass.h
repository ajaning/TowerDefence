//
//  EnemySpriteClass.h
//  CaratonFatans
//
//  Created by jack on 13-7-24.
//
//

#ifndef __CaratonFatans__EnemySpriteClass__
#define __CaratonFatans__EnemySpriteClass__

#include "cocos2d.h"
#include "GameSpriteParm.h"
USING_NS_CC;

class EnemySpriteClass:public CCSprite
{
private:
    EnemySpriteClass();
    ~EnemySpriteClass();
    bool init(const char *pFileName, int life, float moveSpeed,CCArray* posArray);
    bool init(GAME_ENEMY_MONSTERS_TYPE type,CCArray* posArray);
//    virtual void update(float dt);
    virtual void ToTargetPosCallBack(void);
//    virtual void draw();
    void setAttckInvalid(void);
    void moveRunAction();
    void runEffect();
public:
    static EnemySpriteClass* createEnemy(const char *pFileName, int life, float moveSpeed,CCArray* posArray);
    static EnemySpriteClass* createEnemy(GAME_ENEMY_MONSTERS_TYPE type,CCArray* posArray);

    void setIsAttacked(bool flag);
    void setEnemyType(GAME_ENEMY_TYPE type);
    GAME_ENEMY_TYPE getEnemyType();
    void setAddEnemyDirType(GAME_ADD_ENEMY_FROM_DIR_TYPE dir);
    void updateLifeUI();
    void setIsAttackedByMushRoom(bool flag);
    bool getIsAttackedByMushRoom();
    void setIsAttackedByPin(bool flag);
    bool getIsAttackedByPin();
    void setisAttackedByShit(bool flag);
    bool getisAttackedByShit();
    void setIsAttackedBySnow(bool flag);
    bool getIsAttackedBySnow();
    void setEnemySpeed(float value);
    
    void setEnemyPauseState(bool flag);
    bool getEnemyPauseState(void);
    void setIsSpeed2X(bool flag);
    bool getIsSpeed2X();
    
    void setMoneyType(GAME_MONEY_SCORE_TYPE type);
    GAME_MONEY_SCORE_TYPE getMoneyType();
    void setEnemyLifeAndSpeed(int life,float speed);
    
    void setDeathArray(CCArray* death);
    
    void setEnemyObjectID(int objectID);//针对OBJECT，其有个TYPE类型的ID，当其死亡时根据其ID分成不同的炮塔
    int getEnemyObjectID();
    
    void setEnemyObjectToTowerNum_X(int num);//针对OBJECT，其有个TYPE类型的ID，当其死亡时根据其ID分成不同的炮塔数量,在X方向
    int getEnemyObjectToTowerNum_X();
    
    void setEnemyObjectToTowerNum_Y(int num);//针对OBJECT，其有个TYPE类型的ID，当其死亡时根据其ID分成不同的炮塔数量,在X方向
    int getEnemyObjectToTowerNum_Y();
    
    void setEnemyMonsterTypeID(GAME_ENEMY_MONSTERS_TYPE  monsterID);//
    GAME_ENEMY_MONSTERS_TYPE getEnemyMonsterTypeID();
    
    void setCurLifeValue(int value);
    int getCurLifeValue(void);
    void setTotalLifeValue(int value);
    int getTotalLifeValue(void);
    bool getIsDead(void);
    
    void setMoveSpeed(float speed);
    float getMoveSpeed(void);

    void setIsCanMove(bool flag);
    bool getIsCanMove();
    
    void setTargetPos(CCPoint pos,float speed);
    CCPoint getTargetPos();
    
    CCSize getEnemyBloodUISize();
    
private:
    bool isSpeed2X;//移动速度加快两倍
    //bool isPauseState;//停止移动状态
    bool isCanMove;
    bool isAttackedByPin;//被Pin攻击时，只能降慢一次速度
    bool isAttackedByShit;//被Shit攻击时，只能降慢一次速度
    bool isAttackedByMushRoom;//被蘑菇攻击时，只能被泡包住一次
    bool isAttackedBySnow;//被SNOW攻击时，只能冻住一次
    int curPosIndex;
    
    float moveSpeed;
    int curLifeValue;
    int totalLifeValue;
    CCPoint mTargetPos;
    
    int enemyObjectId;//针对OBJECT，其有个TYPE类型的ID，当其死亡时根据其ID分成不同的炮塔
    int enemyObjectToTowerNum_X;//针对OBJECT，其有个TYPE类型的ID，当其死亡时根据其ID分成不同的炮塔数目
    int enemyObjectToTowerNum_Y;//针对OBJECT，其有个TYPE类型的ID，当其死亡时根据其ID分成不同的炮塔数目
//    float moveSpeed;
    GAME_ENEMY_TYPE enemyType;
    GAME_ADD_ENEMY_FROM_DIR_TYPE addEnemyDirType;
    GAME_MONEY_SCORE_TYPE moneyType;
    GAME_ENEMY_MONSTERS_TYPE enemyMonsterTypeID;//针对monster,GAME_ENEMY_MONSTERS_TYPE类型的值
//    CCPoint mTargetPos;
    CCSprite* fgLifeUI;
    CCSprite* bgLifeUI;
    CCArray* movePosArray;
    CCArray* deathArray;//当敌军死亡时，把其加入父节点的ARRAY中处理
    CCAnimation* enemyAni;

};
#endif /* defined(__CaratonFatans__EnemySpriteClass__) */
