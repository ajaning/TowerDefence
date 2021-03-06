//
//  AttackTowerClass.h
//  CaratonFatans
//
//  Created by jack on 13-7-31.
//
//

#ifndef __CaratonFatans__AttackTowerClass__
#define __CaratonFatans__AttackTowerClass__

#include <iostream>
#include "cocos2d.h"
#include "GameSpriteParm.h"
#include "EnemySpriteClass.h"

class AttackTowerClass:public CCNode
{
private:
    AttackTowerClass();
    ~AttackTowerClass();
    bool init(GAME_TOWER_TYPE type);
    bool init(const char* fileName,int killValue,float killRadius, float fireTime);
    void attackObjectFire(void);
    cocos2d::CCPoint updateFireVector(cocos2d::CCPoint curPos, cocos2d::CCPoint targetPos);
    
    void setAttackObject(EnemySpriteClass* object);
    
    void TowerShotActionThenFire();
    void towerRotateActionCallBack(cocos2d::CCNode *psender);
    void towerSelMenuCallBack(cocos2d::CCObject *parent);

	void enemyDeadNotification(CCObject *object);
    
    
    //void towerFireStart();
    void setTowerFireNow();//设置开火
    void rotateTowerNow();
	void rotateTowerFireNow();
    void FanStarTowerFire();
    
    void SunTowerFire();
    
    void updateTowerRotateByeEnemy();
    
    void checkCanAttackEenmy();
    void towerUpdateFire(float dt);
    
        //virtual void draw();
    virtual void update(float dt);
public:
    static AttackTowerClass* create(const char* fileName,int killValue,float killRadius, float fireTime);
    static AttackTowerClass* create(GAME_TOWER_TYPE type);
    void setBulletBatchParent(CCSpriteBatchNode* bulletParent);
    void setTowerUpdate(GAME_TOWER_UPDATE_TYPE type);
    
    
    bool userSetAttackObject(EnemySpriteClass* object);
    
    void setEnemyArray(cocos2d::CCArray* enemy,CCArray* death);
    void setEnemyMonsterArray(cocos2d::CCArray* enemy);
    void setEnemyObjectArray(cocos2d::CCArray* enemy);
    bool checkAttackObjectIsValid(EnemySpriteClass* object);
    cocos2d::CCSpriteBatchNode* getBulletBatchParent();
    EnemySpriteClass* getAttackObject();
    void setIsSpeed2X(bool flag);
    bool getIsSpeed2X();
    bool getIsTowerPause();
    void setIsTowerPause(bool flag);
    void setTowerType(GAME_TOWER_TYPE type);
    GAME_TOWER_TYPE getTowerType(void);
    GAME_TOWER_UPDATE_TYPE getTowerUpdateType();
    
    //GAME_ATTACKING_TYPE getAttackingType();
    float getTowerKillRadius();
    
    
    void setTowerBulletEffectArray(CCArray* bullet,CCArray* effect);
    
    
    void setIsShowTowerUpGrade(bool showFlag);
    bool getIsShowTowerUpGrade();
    void setTowerPayMoney();
    int getTowerPayMoney();
    void setTowerSellMoney();
	int getTowerSellMoney();
    
    void showTowerUpgrade();
    void hideTowerUpgrade();

    void setTowerParentAndPos(CCNode* parent,CCPoint pos);
    void removeTowerFromParent();
    
private:
//    bool isTowerShowPAD;
//    bool isTowerHidePAD;
    bool isShowTowerUpGrade;
    bool isTowerPause;
    bool isSpeed2X;
    bool isTowerAttacking;
    bool isTowerRotating;
	bool isTowerRotateToTarget;
    int towerKillValue;
    int towerAniNum;
    int towerPayMoney;
	int towerSellMoney;
    float towerRoate;
    float towerFireTime;
    float towerAniTime;
	float towerRoateTime;
    float towerKillRadius;//杀伤半径
    float fireTimeCounter;
    //GAME_ATTACKING_TYPE attackingType;
    GAME_TOWER_UPDATE_TYPE towerUpdateType;
    GAME_TOWER_TYPE towerType;
    cocos2d::CCAnimation* towerAni;
    cocos2d::CCPoint bulletVector;
    cocos2d::CCSpriteBatchNode* bulletBatchParent;
    cocos2d::CCArray* enemyArray;
    CCArray* enemyMonsterArray;
    CCArray* enemyObjectArray;
    CCArray* enemyDeathArray;//当ENEMY死亡时，把其加入父节点的ARRAY中处理
    cocos2d::CCSprite* towerSprite;
    cocos2d::CCSprite* towerBG;
    cocos2d::CCSprite* towerSubSprite;
    cocos2d::CCArray* bulletArray;
    cocos2d::CCArray* bulletEffectArray;
    EnemySpriteClass* attackObject;
    CCSprite* showUpgrade;
};
#endif /* defined(__CaratonFatans__AttackTowerClass__) */
