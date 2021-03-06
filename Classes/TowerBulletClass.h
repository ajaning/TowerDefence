//
//  TowerBulletClass.h
//  CaratonFatans
//
//  Created by jack on 13-8-1.
//
//

#ifndef __CaratonFatans__TowerBulletClass__
#define __CaratonFatans__TowerBulletClass__

#include <iostream>
#include "EnemySpriteClass.h"
#include "GameSpriteParm.h"
#include "GameParam.h"
USING_NS_CC;

class TowerBulletClass:public CCSprite
{
private:
    TowerBulletClass();
    ~TowerBulletClass();
    bool init(const char* fileName,EnemySpriteClass* object,float killValue);
    bool init(CCPoint pos,GAME_TOWER_TYPE tower,GAME_TOWER_UPDATE_TYPE type ,EnemySpriteClass* object);
    bool init(CCPoint pos,GAME_TOWER_TYPE tower,GAME_TOWER_UPDATE_TYPE type ,EnemySpriteClass* object,CCPoint targetPos);
    void setCommonAction();

	void enemyDeadNotification(CCObject *object);
    
//fan
	void setFanTarget();
	void toTargetFanCallBack(CCNode* parent);
    
    void setSunTarget();
    void toTargetSunCallBack(CCNode* parent);
    
    void setCommonTarget();
    void toTargetCommonCallBack(CCNode* parent);
    
    void toTargetSecCommonCallBack(CCNode* parent);


    void setShotTarget();
    void toTargetObjectCallBack(CCNode* parent);
    
    bool checkEenemyIsCanAttackedBySunSnow();

    bool checkEnemyIsLineCollion(CCPoint enemyPos,CCSize enemySize);//采用直线相交判断是否碰撞,本游戏中比较适用于飞机炸弹
    bool checkEnemyIsLineCollion2(CCPoint firstPos,CCPoint secPos,CCRect bulletRect, CCRect enemyRect);
    
	bool checkIsCollionWithEnemy(EnemySpriteClass* enemy);//采用矩形检测碰撞

    void anchorSecToTargetCallBack();//当anchor击中怪物时，会反弹再去击中一个Object
    
    virtual void ToTargetPosCallBack(void);
    
    virtual void update(float dt);
public:
    static TowerBulletClass* create(const char* fileName,EnemySpriteClass* object,float killValue);
    static TowerBulletClass* create(CCPoint pos,GAME_TOWER_TYPE tower,GAME_TOWER_UPDATE_TYPE type ,EnemySpriteClass* object);
    static TowerBulletClass* create(CCPoint pos,GAME_TOWER_TYPE tower,GAME_TOWER_UPDATE_TYPE type ,EnemySpriteClass* object,CCPoint targetPos);
//    void setBulletValid();
    bool getIsBulletPause();
    void setIsBulletPause(bool flag);
    void setIsSpeed2X(bool flag);
    bool getIsSpeed2X();
    void runEffect();
    void stopEffect();
    void setAttackEnemy(EnemySpriteClass* object);
    bool checkAttackedEnemey(EnemySpriteClass* enemy);//检测是否击中敌军
    
    void setEnemyArray(CCArray* enemy);
    void setBulletKillRadius(float value);
    void setBulletEffectArray(CCArray* effect);
    void setBulletParentPosAndSize(CCPoint pos,CCSize size);
    //GAME_ATTACKING_TYPE getAttackingType();
    void setEnemyObjectArray(CCArray* object);
    void setEnemyMonsterArray(CCArray* monster);
    
    GAME_TOWER_TYPE getBulletParentTowerType();
    
    void setBulletArray(CCArray* array);
    
private:
    
    bool isDrawNow;
    
    bool isAnchorDir;//锚攻击目标击中后，第一次改变方向攻击其它任意目标
    bool isCanHurtTarget;//判断子弹能否击伤敌军，像有些子弹击中一次就消失，而有些却要飘到边界才消失
    bool isBulletPause;
    bool isSpeed2X;
    float bulletKillValue;
    float moveTime;
    float bulletKillRadius;
    float bulletSpeed;
    float timeCounter;
    float saveTargetSpeed;//攻击敌军时减慢其速度前，保存敌军攻击前的速度，这样攻击结束后恢复其移动速度
    float comActTime;//通用动作时间
    CCPoint bulletParentPos;
    CCSize bulletParentSize;
    CCPoint toRealPos;
    CCPoint toTargetPos;
    CCPoint bulletVector;
    GAME_TOWER_TYPE bulletParentType;
    GAME_TOWER_UPDATE_TYPE bulletParentUpdateType;
    SEL_CallFunc selFunc;
    CCArray* enemyArray;
    CCArray* enemyObjectArray;//当炮塔为anchor时，击中MONSTERS时再一分为二去击中存在的ENEMYOBJECT
    CCArray* enemyMonsterArray;//怪物。。。
    CCArray* bulletEffectArray;
    CCAnimation *bulletAni;
    CCActionInterval* bulletcomAct;
    EnemySpriteClass* targetObject;
    CCArray* comFanArray;//存放类似于FAN类型炮塔发射的子弹攻击时的对象，这些对象只能子弹被击中一次，防止反复击中
    CCArray* bulletArray;
    
    
};

#endif /* defined(__CaratonFatans__TowerBulletClass__) */
