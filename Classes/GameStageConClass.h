//
//  GameStageConClass.h
//  CaratonFatans
//
//  Created by jack on 13-11-2.
//
//

#ifndef __CaratonFatans__GameStageConClass__
#define __CaratonFatans__GameStageConClass__

#include <iostream>
#include "cocos2d.h"
#include "GameSpriteParm.h"
USING_NS_CC;

class GameStageConClass:public CCObject
{
private:
    GameStageConClass();
    ~GameStageConClass();
    bool init();
    //CREATE_FUNC(GameStageConClass);
    static GameStageConClass* create();
    
public:
    static GameStageConClass* sharedStageCon();
    void  setGameModeType(GAME_MODE_TYPE type);
    GAME_MODE_TYPE getGameModeType();
    
    void setGameStageNum(int value);
    void setGameStageIndex(int value);
    void setGameStageRoundNum(int value);
    void setGameStageRoundIndex(int value);
    void setGameStageSubRoundIndex(int value);
    void setGameStageSubRoundNum(int value);
    int getGameStageNum();
    int getGameStageIndex();
    int getGameStageRoundNum();
    int getGameStageRoundIndex();
    int getGameStageSubRoundNum();
    int getGameStageSubRoundIndex();
    void setConfigDataIndex(int value);
    int getConfigDataIndex();
    void setConfigDataFirstIndex(int value);
    int getConfigDataFirstIndex();
    void setIsFromGameing(bool flag);
    bool getIsFromGameing(void);
	void setGameStageRoundMoney(int value);
	int getGameStageRoundMoney();
	void setGameStageAddTowerType(int value);
	int getGameStageAddTowerType();
    int getGameThemeBGColorID();
    void setGameThemeBGColorID(int colorId);
    
    bool getIsGameGiftCurLevel();
    void setIsGameGiftCurLevel(bool isGift);
    
    int getGameGiftCurLevel();
    void setGameGiftCurLevel(int index);
    
    bool getIsGameWahleCurLevell();
    void setIsGameWahleCurLevel(bool isWhale);
    
    int getgameWahleCurLevel();
    void setGameWahleCurLevel(int index);
    
    void setBossTimeLimit(int time);
    int getBossTimeLimit();
    
    void setBossBloodValue(int value);
    int getBossBloodValue();
    
    bool getIsGameReStart();
    void setIsGameReStart(bool flag);
    
    void setGameBossID(int index);//boss mode,the boss ID
    int getGameBossID();
    char* getBossIDName();
    
    GAME_ENEMY_MONSTERS_TYPE getBossMonsterTypeID();
    void setBossMonsterTypeID(GAME_ENEMY_MONSTERS_TYPE monsterID);
    
    GAME_SUBROUND_ADD_NEW_TOWER_TYPE getShowNewTowerType();
    void setShowNewTowerType(GAME_SUBROUND_ADD_NEW_TOWER_TYPE towerType );
    
    void setGameBossLastTime(int time);
    int getGameBossLastTime(void);
    
    bool checkIsCurLevelLocked(int index);
    
private:
    bool isGameRestart;
    
    bool isFromGameing;//判断游戏的开始是从选择关卡进入还是从一关游戏结束后点击继续游戏进入
    bool isGameGiftCurLevel;//判断当前关卡是否有礼物相送
    bool isGameWahleCurLevel;//判断当前游戏是否有鲸鱼出现
    int gameGiftCurLevel;//游戏中礼物出现的地方
    int gameWahleCurLevel;//游戏中鲸鱼出现的地方
    
    int gameThemeBGColorID;//1-blue,2-other,游戏主题背景
    int configDataFirstIndex;//游戏开始时的第一个索引数据
    int configDataIndex;
	int gameStageRoundMoney;//the first round money
    int gameStageNum;//游戏中的主题关卡数目
    int gameStageIndex;//游戏中的主题关卡INDEX
    int gameStageRoundNum;//每个主题关卡中含有的怪物关卡数目
    int gameStageRoundIndex;
    int gameStageSubRoundNum;//每个怪物关卡中敌军进攻波数
    int gameStageSubRoundIndex;
	int gameStageAddTowerType;
    
    GAME_SUBROUND_ADD_NEW_TOWER_TYPE showNewTowerType;
    
//{ for boss mode
    int gameBossTimeLimit;
    int gameBossBloodValue;
    int gameBossID;//1--16
    int gameBossTimeLast;//游戏最后剩余的时间
    GAME_MODE_TYPE gameModeType;
    GAME_ENEMY_MONSTERS_TYPE bossMonsterTypeID;//GAME_ENEMY_MONSTERS_TYPE类型的值
//}
};

#endif /* defined(__CaratonFatans__GameStageConClass__) */
