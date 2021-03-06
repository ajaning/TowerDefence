//
//  GameStageConClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-11-2.
//
//

#include "GameStageConClass.h"
#include "GameStageRounConfigAddEnemyPlan.h"
#include "HUDClass.h"

static GameStageConClass* sharedCon = NULL;

typedef struct {
    int bossID;
    int bloodValueID;
    int timeLimitID;
}bossDataInfo;

static bossDataInfo bossConfigData[] = {
    {0,0,0},
    {1,80000,90},
    {2,20000,80},
    {3,75000,80},
    {4,110000,110},
    {5,40000,90},
    {6,110000,110},
    {7,50000,110},
    {8,50000,180},
    {9,60000,100},
    {10,80000,90},
    {11,500000,60},
    {12,400000,180},
    {13,200000,130},
    {14,200000,168},
    {15,70000,60},
    {16,400000,180},
    {0,0,0},
};

GameStageConClass::GameStageConClass()
{

}

GameStageConClass::~GameStageConClass()
{
    
}

bool GameStageConClass::init()
{
    isGameRestart = false;
    gameStageNum = 0;
    gameStageIndex = 0;
    gameStageRoundNum = 0;
    gameStageRoundIndex = 0;
    gameStageSubRoundNum = 0;
    gameStageSubRoundIndex = 0;
    configDataIndex = 0;
    configDataFirstIndex = 0;
    isFromGameing = false;
	gameStageAddTowerType = 0;
    isGameGiftCurLevel = false;
    gameThemeBGColorID = 1;
    gameBossTimeLimit = 0;
    gameBossBloodValue = 0;
    isGameWahleCurLevel = false;
    gameGiftCurLevel = 0;
    gameWahleCurLevel = 0;
    gameBossID = 0;
    gameBossTimeLast = 0;
    bossMonsterTypeID = GAME_ENEMY_MONSTERS_NONE;
    showNewTowerType = GAME_SUBROUND_ADD_NEW_TOWER_TYPE_NONE;
    return true;
}

GameStageConClass* GameStageConClass::create()
{
    GameStageConClass* con = new GameStageConClass();
    
    if (con && con->init()) {
        
    }
    else
    {
        CC_SAFE_DELETE(con);
    }
    
    return con;
}

GameStageConClass* GameStageConClass::sharedStageCon()
{
    if (sharedCon == NULL) {
        sharedCon = GameStageConClass::create();
    }
    
    return sharedCon;
}

void GameStageConClass::setGameModeType(GAME_MODE_TYPE type)
{
    gameModeType = type;
    //read config data while set mode
    gameStageNum = gameStageRoundConfig[type].gameStageNum;
}

GAME_MODE_TYPE GameStageConClass::getGameModeType()
{
    return gameModeType;
}

void GameStageConClass::setGameStageNum(int value)
{
    gameStageNum = value;
}

int GameStageConClass::getGameStageNum()
{
    return gameStageNum;
}

void GameStageConClass::setGameStageIndex(int value)
{
    gameStageIndex = value;
}

int GameStageConClass::getGameStageIndex()
{
    return gameStageIndex;
}

void GameStageConClass::setGameStageRoundNum(int value)
{
    gameStageRoundNum = value;
}

int GameStageConClass::getGameStageRoundNum()
{
    return gameStageRoundNum;
}

void GameStageConClass::setGameStageRoundIndex(int value)
{
    gameStageRoundIndex = value;
}

int GameStageConClass::getGameStageRoundIndex()
{
    return gameStageRoundIndex;
}

void GameStageConClass::setGameStageSubRoundNum(int value)
{
    gameStageSubRoundNum = value;
}

int GameStageConClass::getGameStageSubRoundNum()
{
    return gameStageSubRoundNum;
}

void GameStageConClass::setGameStageSubRoundIndex(int value)
{
    gameStageSubRoundIndex = value;
}

int GameStageConClass::getGameStageSubRoundIndex()
{
    return gameStageSubRoundIndex;
}

void GameStageConClass::setConfigDataFirstIndex(int value)
{
    configDataFirstIndex = value;
}

int GameStageConClass::getConfigDataFirstIndex()
{
    return configDataFirstIndex;
}

void GameStageConClass::setConfigDataIndex(int value)
{
    configDataIndex = value;
}

int GameStageConClass::getConfigDataIndex()
{
    return configDataIndex;
}

void GameStageConClass::setIsFromGameing(bool flag)
{
    isFromGameing = flag;
}

bool GameStageConClass::getIsFromGameing()
{
    return isFromGameing;
}

int GameStageConClass::getGameStageRoundMoney()
{
    return gameStageRoundMoney;
}

void GameStageConClass::setGameStageRoundMoney(int value)
{
    gameStageRoundMoney = value;
}

void GameStageConClass::setGameStageAddTowerType(int value)
{
	gameStageAddTowerType = value;
}

int GameStageConClass::getGameStageAddTowerType()
{
	return gameStageAddTowerType;
}


void GameStageConClass::setGameThemeBGColorID(int colorId)
{
    if (colorId < 1) {
        colorId = 1;
    }
    else if (colorId > 2){
        colorId = 2;
    }
    
    gameThemeBGColorID = colorId;
}

int GameStageConClass::getGameThemeBGColorID()
{
    return gameThemeBGColorID;
}

void GameStageConClass::setIsGameGiftCurLevel(bool isGift)
{
    isGameGiftCurLevel = isGift;
    
    if (gameStageSubRoundNum > 0) {
        int index = CCRANDOM_0_1() * gameStageSubRoundNum + 5;//礼物出现于5波之后
        this->setGameGiftCurLevel(index);
    }
}

bool GameStageConClass::getIsGameGiftCurLevel()
{
    return isGameGiftCurLevel;
}

void GameStageConClass::setGameGiftCurLevel(int index)
{
    gameGiftCurLevel = index;
}

int GameStageConClass::getGameGiftCurLevel()
{
    return gameGiftCurLevel;
}

void GameStageConClass::setBossTimeLimit(int time)
{
    //gameBossTimeLimit = time;
}

int GameStageConClass::getBossTimeLimit()
{
    //return gameBossTimeLimit;
    return bossConfigData[gameBossID].timeLimitID;
}

void GameStageConClass::setBossBloodValue(int value)
{
    //gameBossBloodValue = value;
}

int GameStageConClass::getBossBloodValue()
{
    //return gameBossBloodValue;
    return bossConfigData[gameBossID].bloodValueID;
}

void GameStageConClass::setIsGameReStart(bool flag)
{
    isGameRestart = flag;
    
    if (flag) {
        isGameGiftCurLevel = false;
    }
}

bool GameStageConClass::getIsGameReStart()
{
    return isGameRestart;
}


bool GameStageConClass::getIsGameWahleCurLevell()
{
    return isGameWahleCurLevel;
}

void GameStageConClass::setIsGameWahleCurLevel(bool isWhale)
{
    isGameWahleCurLevel = isWhale;
}

int GameStageConClass::getgameWahleCurLevel()
{
    return gameWahleCurLevel;
}

void GameStageConClass::setGameWahleCurLevel(int index)
{
    gameWahleCurLevel = index;
}

void GameStageConClass::setGameBossID(int index)
{
    CCAssert(!(index < 1 || index > 16), "cannot be INVALID");
    
    gameBossID = index;
}

int GameStageConClass::getGameBossID()
{
    return bossConfigData[gameBossID].bossID;
}

char* GameStageConClass::getBossIDName()
{
    char* pFileName = NULL;
    
    switch (gameBossID) {
        case 1:
            pFileName = "woowala";
            break;
        case 2:
            pFileName = "pinky ninja";
            break;
        case 3:
            pFileName = "twisty fork";
            break;
        case 4:
            pFileName = "flydevils";
            break;
        case 5:
            pFileName = "cyclops";
            break;
        case 6:
            pFileName = "popbowling";
            break;
        case 7:
            pFileName = "gremlins";
            break;
        case 8:
            pFileName = "sadgeezer";
            break;
        case 9:
            pFileName = "firefeet";
            break;
        case 10:
            pFileName = "unicorn";
            break;
        case 11:
            pFileName = "dark angel";
            break;
        case 12:
            pFileName = "fat mummy";
            break;
        case 13:
            pFileName = "conchking";
            break;
        case 14:
            pFileName = "hotstar";
            break;
        case 15:
            pFileName = "dr.octopus";
            break;
        case 16:
            pFileName = "hugechela";
            break;
        default:
            break;
    }
    
    return pFileName;
}


void GameStageConClass::setBossMonsterTypeID(GAME_ENEMY_MONSTERS_TYPE monsterID)
{
    bossMonsterTypeID = monsterID;
}

GAME_ENEMY_MONSTERS_TYPE GameStageConClass::getBossMonsterTypeID()
{
    return bossMonsterTypeID;
}

void GameStageConClass::setShowNewTowerType(GAME_SUBROUND_ADD_NEW_TOWER_TYPE towerType)
{
    showNewTowerType = towerType;
}

GAME_SUBROUND_ADD_NEW_TOWER_TYPE GameStageConClass::getShowNewTowerType()
{
    return showNewTowerType;
}


void GameStageConClass::setGameBossLastTime(int time)
{
    gameBossTimeLast = time;
}

int GameStageConClass::getGameBossLastTime()
{
    return gameBossTimeLast;
}

bool GameStageConClass::checkIsCurLevelLocked(int index)
{
    bool isLocked = false;
    
    if (index == 1) {
        isLocked = false;
    }
    else
    {
        gameLevelInfoStruct info = HUDClass::sharedHUD()->getGameCurLevelInfo((GAME_STAGE_TYPE)GameStageConClass::sharedStageCon()->getGameStageIndex(), index);
        
        isLocked = info.isLevelLocked;
    }
    
    return false;
}
