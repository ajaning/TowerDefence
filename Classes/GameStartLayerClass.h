//
//  GameStartLayerClass.h
//  CaratonFatans
//
//  Created by jack on 13-7-24.
//
//

#ifndef __CaratonFatans__GameStartLayerClass__
#define __CaratonFatans__GameStartLayerClass__

#include <iostream>
#include "cocos2d.h"
#include "EnemySpriteClass.h"
#include "AttackTowerClass.h"
#include "MapPassClass.h"
#include "TowerSelPadClass.h"
#include "TowerAddTypeClass.h"
#include "TowerBulletClass.h"
#include "HUDClass.h"
#include "GameParam.h"
#include "GameSpriteParm.h"
#include "LcdAdapClass.h"
#include "TowerBulletEffectClass.h"
#include "CommonClass.h"
#include "GameAddEnemyClass.h"
#include "CaratonProClass.h"
#include "HelpPlayGame.h"
#include "ShowTowerFeatureClass.h"
#include "WhaleClass.h"

USING_NS_CC;

class GameStartLayerClass:public CCLayer
{
private:
    GameStartLayerClass();
    ~GameStartLayerClass();
    bool init();
    void initGame();//加载资源与初始化
    void initTower(void);
	void initShowValidPos();
    void loadCommonImgAndInitGameMenu();//加载通用图片与初始化游戏菜单
    CREATE_FUNC(GameStartLayerClass);
    
    void loadingAniCallBack();
    
    bool checkIsCanPutOnMap(CCPoint pos);
    void updateGameSpriteState(void);
    void checkSpriteStateOnThread();
    void checkUserTouchValidOnThread();
    
    void addGameTowerType(GAME_TOWER_TYPE towerType,CCPoint addPos);
    
    void checkTowerBulletAttackedEnemyOnThread();
    void updateEnemyUI();
    void addTowerSelCallBack();
    void selTowerPadCallBack();
    
    void gameMenuSelCallBack(CCObject* parent);
    
    void gamePauseOrSpeedSpriteState(bool isSpeed,bool flag);//isSpeed == true,means is Speed2x
    
    
    void addEnemyByPlan(float dt);
    
    void logoShowOverCallBack();
    
    
    void gameShowGoBgAniStart();
    void gameShowGoBgAniCallBack(CCNode* node);
    void gameShowGoAniCallBack(CCNode* node);
    void gameShowGoMoveAniCallBack(CCNode* node);
    
    void checkGameDoBeforeStart();//在游戏正式开始前需要判断是显示游戏帮助还是直接显示LOGO
    
    void showGameHelpCallBack();
    void updateShowGameHelpState(CCPoint pos);
    
    void whaleLayerCallBack();
    
    void spriteHurtedAniStart(CCPoint pos);
    void spriteHurtedAniCallBack(CCNode* node);
    
    void gameShowStopIconAniStart(CCPoint pos);
    void gameShowStopIconAniCallBack(CCNode* node);
    
    void gameShowStartAni(bool restart);////游戏开始前都有一个动画箭头,重新开始游戏只有4个动画，默认有8个
    void gameShowStartAniCallBack(CCNode* node);
    
    void showTowerFeatureBeforeGameCallBack();//展示新炮塔结束后回调
  
 //for bossMode{
    void initBossTimeBG();
    void initBossTimeBGAniCallBack();
    void updateBossModeBloodValue();
    void updateBossTimeBgState(float delta);
//}
    
    
    void updateUserTouchEndEvent(CCPoint pos);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
public:
    static CCScene* createGameStart();
private:
    
    bool isNowAddMonster;//添加怪物开始的标志
    
    bool isGameShowGift;//当前关卡中的礼物只能出现一次
    bool isGameShowWhale;//当前关卡中的鲸鱼只能出现一次
    
    bool isGameRealStartNow;//游戏真正开始了，敌军可以出现了，炮塔可以放置了
    bool isShowGameHelp;//当第一关第一轮时显示游戏示例
    bool isLogoShowOver;
    bool isLayerOver;//本布景结束，即将被切换
    bool isLastFinall;//最后一波攻击标志
    bool isAllObjectClear;
    bool isAllMonstersDead;
    bool isCheckTouchValiding;
    bool isUserTouched;
    bool isSelPutTower;//et用户选择放置炮塔，true放置炮塔
    bool isGameSpeed2X;
    bool isGamePause;
    bool isGameSelItem;
    int AllObjectNum;//障碍物数量
    float xScale;
    float yScale;
    int addEnemyNum;
	int gameCurMoney;
    float addEnemyTimeCounter;
    
    GAME_MODE_TYPE gameModeType;//adventure,boss
    
//{for bossMode
    int bossTypeID;//
    int bossCurTime;
    EnemySpriteClass* bossSelSprite;
    
    CCSprite* bossTimeBGSprite;
    CCLabelAtlas* timeLab;
    CCSprite* bossKOSprite;
    
    CCSprite* bossBloodBG;//血量背景
    CCSprite* bossBloodMvSprite;//滑动显示血量
//}

    CCSprite* gameGoBgSprite;//go
    
    CCSprite* loadWaitSprite;//加载等待画面
    CCPoint showHelpPlayGamePos;
    CCPoint userTouchPos;
    CCArray* deadSpriteArray;
    CCArray* pathArray;
    CCArray* enemyArray;
    CCArray* enemyMonsterArray;
    CCArray* enemyObjectArray;
    CCArray* mapPutArray;
    CCArray* towerArray;
    CCArray* bulletArray;
    CCArray* bulletEffectArray;
    CCArray* towerShowUpArray;
    CCTMXObjectGroup* mapObjectGroup;
    CCSpriteBatchNode* towerAnchorBatch;
    CCSpriteBatchNode* towerArrowBatch;
    CCSpriteBatchNode* towerBallBatch;
    CCSpriteBatchNode* towerBlueStarBatch;
    CCSpriteBatchNode* towerBottleBatch;
    CCSpriteBatchNode* towerBuffBatch;
    CCSpriteBatchNode* towerCuttleBatch;
    CCSpriteBatchNode* towerFanBatch;
    CCSpriteBatchNode* towerFireBottleBatch;
    CCSpriteBatchNode* towerFishBatch;
    CCSpriteBatchNode* towerMushRoomBatch;
    CCSpriteBatchNode* towerPinBatch;
    CCSpriteBatchNode* towerPlaneBatch;
    CCSpriteBatchNode* towerRocketBatch;
    CCSpriteBatchNode* towerShitBatch;
    CCSpriteBatchNode* towerSnowBatch;
    CCSpriteBatchNode* towerStarBatch;
    CCSpriteBatchNode* towerSunBatch;
    
    CCLabelAtlas* updateGameCurMoneyLab;
    CCLabelAtlas* curLevelLab;
    CCLabelAtlas* totalLevelLab;
    CCMenuItemImage* gameSpeed2XMenu;
    CCMenuItemImage* gamePauseMenu;
    CCMenuItemImage* gameSelItemMenu;
    CCSprite* menuCenterBG;
    
    CCSprite* gameBGSprite;
    CCLayerColor* gameSelItemLayer;
    
    AttackTowerClass* userSelTower;
    EnemySpriteClass* userSelObject;
    TowerSelPadClass* towerShowPad;
    TowerAddTypeClass* userTowerAdd;
    GAME_USER_TOUCH_TYPE userTouchType;
    CCSize gameMapTiledSize;
    
    GameAddEnemyClass* addEnemyPlan;
    CaratonProClass* proCaraton;
    HelpPlayGame* showHelpPL;
    
    CCSprite* userSelEnemyPointSprite;
    EnemySpriteClass* userSelEnemy;
    
    ShowTowerFeatureClass* showNewTowerFeature;
    WhaleClass* gameWhale;
};
#endif /* defined(__CaratonFatans__GameStartLayerClass__) */
