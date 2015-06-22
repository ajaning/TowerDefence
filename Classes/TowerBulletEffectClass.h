//
//  TowerBulletEffectClass.h
//  CaratonFatans
//
//  Created by jack on 13-10-10.
//
//

#ifndef __CaratonFatans__TowerBulletEffectClass__
#define __CaratonFatans__TowerBulletEffectClass__

#include <iostream>
#include "cocos2d.h"
#include "EnemySpriteClass.h"
#include "GameSpriteParm.h"
USING_NS_CC;

class TowerBulletEffect:public CCSprite
{
private:
    TowerBulletEffect();
    ~TowerBulletEffect();
    bool init(GAME_TOWER_TYPE tower, GAME_TOWER_UPDATE_TYPE update,EnemySpriteClass* enemy);
    virtual void update(float dt);
	void effectFirstActionCallBack(CCNode* parent);
    void effectAniCallBack(CCNode* parent);
    void noEffectAniCallBack(CCNode* parent);

	void enemyDeadNotification(CCObject *object);

public:
    static TowerBulletEffect*create(GAME_TOWER_TYPE tower, GAME_TOWER_UPDATE_TYPE update,EnemySpriteClass* enemy);
    void setsaveEnemyMoveSpeed(float speed);
    void setIsBulletEffectPause(bool flag);
    bool getIsBulletEffectPause(void);
	void setIsSpeed2X(bool flag);
	bool getIsSpeed2X();
    void setBulletEffectArray(CCArray* array);
    //GAME_ATTACKING_TYPE getAttackingType();
private:
	bool isSpeed2X;
    bool IsBulletEffectPause;
    float saveEnemyMoveSpeed;
	float effectAniTime;
    float enemySpeed;
	CCArray* effectAniFramesArray;
    //GAME_ATTACKING_TYPE attackingType;
    GAME_TOWER_TYPE towerType;
    EnemySpriteClass* enemyObject;
    CCArray* BulletEffectArray;
    
};

#endif /* defined(__CaratonFatans__TowerBulletEffectClass__) */
