//
//  GameAddEnemyClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-7-15.
//
//

#include "GameAddEnemyClass.h"
#include "GameStageRounConfigAddEnemyPlan.h"
#include "EnemySpriteClass.h"
#include "GameStageConClass.h"
#include "GameParam.h"
#include "LcdAdapClass.h"


static gameAddEnemyStruct addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_MAX] = {{false,GAME_ENEMY_MONSTERS_NONE,0,0,0,0,0,0,0,0}};

static int gameAddMonsterOrderBuffer[GAME_ENEMY_MONSTERS_MAX] ={0};//添加怪物的顺序

GameAddEnemyClass::GameAddEnemyClass()
{

}

GameAddEnemyClass::~GameAddEnemyClass()
{

}


bool GameAddEnemyClass::init(int stage)
{
	isAddFinish = false;
	gameStageCurIndex = stage;
	gameStageRoundIndex = 1;
    startIndex = 0;
	gameStageRoundNum = 0;//(int)GET_GAME_ADD_ENEMY_ROUND_NUM_ON_STAGE(1);
	addMonsterNum = 0;
    addMonsterIndex = 0;
    addMonsterIndex = 0;
    this->getEnemyDataFromConfigOnStage();
//    this->setGameStageNextRound();
	this->setGameStageNextSubRound();

	return true;
}

GameAddEnemyClass* GameAddEnemyClass::create(int stage)
{

	GameAddEnemyClass* addEnemy = new GameAddEnemyClass();

	if (addEnemy && addEnemy->init(stage))
	{
		addEnemy->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(addEnemy);
	}
	
	return addEnemy;
}

void GameAddEnemyClass::setGameStageNextRound()
{
//    int i = 0;
//    
//    if (gameStageRoundIndex < gameStageRoundNum) {
//        this->setGameStageNextSubRound();
////        gameStageRoundIndex++;
//        GameStageConClass::sharedStageCon()->setGameStageRoundIndex(gameStageRoundIndex);
//    }
    
}


unsigned int GameAddEnemyClass::getAddMonsterNum()
{
	return addMonsterNum;
}

void GameAddEnemyClass::setMonsterNum(unsigned int value)
{
	addMonsterNum = value;
}

bool GameAddEnemyClass::checkIsAddMonstersFinish()
{
    bool isFinish = true;
    
//    for (int i = GAME_ENEMY_MONSTERS_BEGIN; i < GAME_ENEMY_MONSTERS_MAX;i++)
//	{
//		if (addEnemyTypeBuffer[i].addEnemyNum > 0)
//        {
//            isFinish &= addEnemyTypeBuffer[i].isAddFinish;
//        }
//    }
//    isAddFinish = isFinish;
    
    if (addMonsterIndex > 0 && addMonsterNum > 0) {
        for (int i = 0; i < addMonsterIndex;i++ ) {
            int monsterTypeIndex = gameAddMonsterOrderBuffer[i];
            
            if (addEnemyTypeBuffer[monsterTypeIndex].addEnemyNum > 0) {
                if (addEnemyTypeBuffer[monsterTypeIndex].addEnemyNumIndex < addEnemyTypeBuffer[monsterTypeIndex].addEnemyNum)
                {
                    isFinish = false;
                    break;
                }
            }
        }
    }
    
    isAddFinish = isFinish;
	return isFinish;
}

void GameAddEnemyClass::setStartIndex(int value)
{
//    int tmpStageSubRoundIndex = GameStageConClass::sharedStageCon()->getGameStageSubRoundIndex();
//    int tmpStageSubRoundNum = GameStageConClass::sharedStageCon()->getGameStageSubRoundNum();
//    int tmpStageRoundIndex = GameStageConClass::sharedStageCon()->getGameStageRoundIndex();
//    int tmpStageRoundNum = GameStageConClass::sharedStageCon()->getGameStageRoundNum();
//    
//    
//    startIndex = value;
//    if (tmpStageSubRoundIndex < tmpStageSubRoundNum)
//    {
//        startIndex += 0;
//    }
//    else if (tmpStageRoundIndex < tmpStageRoundNum)
//    {
//        startIndex += 1;
//        
//    }
//    GameStageConClass::sharedStageCon()->setConfigDataIndex(startIndex);
//    this->setGameStageNextSubRound();
}

bool GameAddEnemyClass::setGameStageNextSubRound()
{
	
	if (gameStageSubRoundIndex < gameStageSubRoundNum)
    {
        int j = 0;
        int enemyAddType = 0;
        int enemyTypeNum = GameEnemyConfig[startIndex].value;
        
		isAddFinish = false;
		addMonsterNum = 0;
        startIndex = GameStageConClass::sharedStageCon()->getConfigDataIndex();
        
        //{ check whale
        GameStageConClass::sharedStageCon()->setIsGameWahleCurLevel(GameEnemyConfig[startIndex].isWahle);
        GameStageConClass::sharedStageCon()->setGameWahleCurLevel(gameStageSubRoundIndex + 1);
        
        //}
        
        addMonsterIndex = 0;
        memset(addEnemyTypeBuffer, 0, sizeof(addEnemyTypeBuffer));
        for (j = (startIndex + 1); j < (startIndex + 1 + (enemyTypeNum * 5 - 1));) {
            
            enemyAddType = GameEnemyConfig[j].enemyType;
            
            if (enemyAddType & GAME_ADD_ENEMY_MONSTERS_BOSS_BIG)
            {
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_BOSS_BIG].type = GAME_ENEMY_MONSTERS_BOSS_BIG;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_BOSS_BIG].addEnemyNum = GameEnemyConfig[j].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_BOSS_BIG].addEnemyTime = GameEnemyConfig[j + 1].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_BOSS_BIG].addEnemySpeed = GameEnemyConfig[j + 2].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_BOSS_BIG].addEnemyLife = GameEnemyConfig[j + 3].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_BOSS_BIG].addEnemyMoney = GameEnemyConfig[j + 4].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_BOSS_BIG].addEnemyNumIndex = 0;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_BOSS_BIG].addEnemyTimeCounter = 0;
                addMonsterNum += addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_BOSS_BIG].addEnemyNum;
                
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_BOSS_BIG].addEnemyMonsterID = GameEnemyConfig[j].enemyType;
                gameAddMonsterOrderBuffer[addMonsterIndex] = GAME_ENEMY_MONSTERS_BOSS_BIG;
                addMonsterIndex++;
                
            }
            
            if (enemyAddType & GAME_ADD_ENEMY_MONSTERS_FAT_BOSS_GREEN)
            {
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN].type = GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN].addEnemyNum = GameEnemyConfig[j].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN].addEnemyTime = GameEnemyConfig[j + 1].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN].addEnemySpeed = GameEnemyConfig[j + 2].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN].addEnemyLife = GameEnemyConfig[j + 3].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN].addEnemyMoney = GameEnemyConfig[j + 4].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN].addEnemyNumIndex = 0;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN].addEnemyTimeCounter = 0;
                addMonsterNum += addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN].addEnemyNum;
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN].addEnemyMonsterID = GameEnemyConfig[j].enemyType;
                
                gameAddMonsterOrderBuffer[addMonsterIndex] = GAME_ENEMY_MONSTERS_FAT_BOSS_GREEN;
                addMonsterIndex++;
            }
            
            if (enemyAddType & GAME_ADD_ENEMY_MONSTERS_FAT_GREEN)
            {
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_GREEN].type = GAME_ENEMY_MONSTERS_FAT_GREEN;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_GREEN].addEnemyNum = GameEnemyConfig[j].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_GREEN].addEnemyTime = GameEnemyConfig[j + 1].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_GREEN].addEnemySpeed = GameEnemyConfig[j + 2].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_GREEN].addEnemyLife = GameEnemyConfig[j + 3].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_GREEN].addEnemyMoney = GameEnemyConfig[j + 4].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_GREEN].addEnemyNumIndex = 0;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_GREEN].addEnemyTimeCounter = 0;
                addMonsterNum += addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_GREEN].addEnemyNum;
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FAT_GREEN].addEnemyMonsterID = GameEnemyConfig[j].enemyType;
                
                gameAddMonsterOrderBuffer[addMonsterIndex] = GAME_ENEMY_MONSTERS_FAT_GREEN;
                addMonsterIndex++;
            }
            
            if (enemyAddType & GAME_ADD_ENEMY_MONSTERS_FLY_BLUE)
            {
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BLUE].type = GAME_ENEMY_MONSTERS_FLY_BLUE;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BLUE].addEnemyNum = GameEnemyConfig[j].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BLUE].addEnemyTime = GameEnemyConfig[j + 1].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BLUE].addEnemySpeed = GameEnemyConfig[j + 2].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BLUE].addEnemyLife = GameEnemyConfig[j + 3].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BLUE].addEnemyMoney = GameEnemyConfig[j + 4].value;
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BLUE].addEnemyNumIndex = 0;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BLUE].addEnemyTimeCounter = 0;
                addMonsterNum += addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BLUE].addEnemyNum;
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BLUE].addEnemyMonsterID = GameEnemyConfig[j].enemyType;
                
                gameAddMonsterOrderBuffer[addMonsterIndex] = GAME_ENEMY_MONSTERS_FLY_BLUE;
                addMonsterIndex++;
            }
            
            if (enemyAddType & GAME_ADD_ENEMY_MONSTERS_FLY_BOSS_BLUE)
            {
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE].type = GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE].addEnemyNum = GameEnemyConfig[j].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE].addEnemyTime = GameEnemyConfig[j + 1].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE].addEnemySpeed = GameEnemyConfig[j + 2].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE].addEnemyLife = GameEnemyConfig[j + 3].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE].addEnemyMoney = GameEnemyConfig[j + 4].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE].addEnemyNumIndex = 0;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE].addEnemyTimeCounter = 0;
                addMonsterNum += addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE].addEnemyNum;
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE].addEnemyMonsterID = GameEnemyConfig[j].enemyType;
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE].addEnemyMonsterID = GameEnemyConfig[j].enemyType;
                
                gameAddMonsterOrderBuffer[addMonsterIndex] = GAME_ENEMY_MONSTERS_FLY_BOSS_BLUE;
                addMonsterIndex++;
            }
            
            if (enemyAddType & GAME_ADD_ENEMY_MONSTERS_FLY_BOSS_YELLOW)
            {
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW].type = GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW].addEnemyNum = GameEnemyConfig[j].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW].addEnemyTime = GameEnemyConfig[j + 1].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW].addEnemySpeed = GameEnemyConfig[j + 2].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW].addEnemyLife = GameEnemyConfig[j + 3].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW].addEnemyMoney = GameEnemyConfig[j + 4].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW].addEnemyNumIndex = 0;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW].addEnemyTimeCounter = 0;
                addMonsterNum += addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW].addEnemyNum;
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW].addEnemyMonsterID = GameEnemyConfig[j].enemyType;
                
                gameAddMonsterOrderBuffer[addMonsterIndex] = GAME_ENEMY_MONSTERS_FLY_BOSS_YELLOW;
                addMonsterIndex++;
            }
            
            if (enemyAddType & GAME_ADD_ENEMY_MONSTERS_FLY_YELLOW)
            {
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_YELLOW].type = GAME_ENEMY_MONSTERS_FLY_YELLOW;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_YELLOW].addEnemyNum = GameEnemyConfig[j].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_YELLOW].addEnemyTime = GameEnemyConfig[j + 1].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_YELLOW].addEnemySpeed = GameEnemyConfig[j + 2].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_YELLOW].addEnemyLife = GameEnemyConfig[j + 3].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_YELLOW].addEnemyMoney = GameEnemyConfig[j + 4].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_YELLOW].addEnemyNumIndex = 0;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_YELLOW].addEnemyTimeCounter = 0;
                addMonsterNum += addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_YELLOW].addEnemyNum;
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_FLY_YELLOW].addEnemyMonsterID = GameEnemyConfig[j].enemyType;
                
                gameAddMonsterOrderBuffer[addMonsterIndex] = GAME_ENEMY_MONSTERS_FLY_YELLOW;
                addMonsterIndex++;
            }
            
            if (enemyAddType & GAME_ADD_ENEMY_MONSTERS_LAND_BOSS_NIMA)
            {
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA].type = GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA].addEnemyNum = GameEnemyConfig[j].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA].addEnemyTime = GameEnemyConfig[j + 1].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA].addEnemySpeed = GameEnemyConfig[j + 2].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA].addEnemyLife = GameEnemyConfig[j + 3].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA].addEnemyMoney = GameEnemyConfig[j + 4].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA].addEnemyNumIndex = 0;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA].addEnemyTimeCounter = 0;
                addMonsterNum += addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA].addEnemyNum;
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA].addEnemyMonsterID = GameEnemyConfig[j].enemyType;
                
                gameAddMonsterOrderBuffer[addMonsterIndex] = GAME_ENEMY_MONSTERS_LAND_BOSS_NIMA;
                addMonsterIndex++;
            }
            
            if (enemyAddType & GAME_ADD_ENEMY_MONSTERS_LAND_BOSS_PINK)
            {
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_PINK].type = GAME_ENEMY_MONSTERS_LAND_BOSS_PINK;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_PINK].addEnemyNum = GameEnemyConfig[j].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_PINK].addEnemyTime = GameEnemyConfig[j + 1].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_PINK].addEnemySpeed = GameEnemyConfig[j + 2].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_PINK].addEnemyLife = GameEnemyConfig[j + 3].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_PINK].addEnemyMoney = GameEnemyConfig[j + 4].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_PINK].addEnemyNumIndex = 0;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_PINK].addEnemyTimeCounter = 0;
                addMonsterNum += addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_PINK].addEnemyNum;
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_PINK].addEnemyMonsterID = GameEnemyConfig[j].enemyType;
                
                gameAddMonsterOrderBuffer[addMonsterIndex] = GAME_ENEMY_MONSTERS_LAND_BOSS_PINK;
                addMonsterIndex++;
            }
            
            if (enemyAddType & GAME_ADD_ENEMY_MONSTERS_LAND_BOSS_STAR)
            {
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_STAR].type = GAME_ENEMY_MONSTERS_LAND_BOSS_STAR;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_STAR].addEnemyNum = GameEnemyConfig[j].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_STAR].addEnemyTime = GameEnemyConfig[j + 1].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_STAR].addEnemySpeed = GameEnemyConfig[j + 2].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_STAR].addEnemyLife = GameEnemyConfig[j + 3].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_STAR].addEnemyMoney = GameEnemyConfig[j + 4].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_STAR].addEnemyNumIndex = 0;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_STAR].addEnemyTimeCounter = 0;
                addMonsterNum += addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_STAR].addEnemyNum;
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_BOSS_STAR].addEnemyMonsterID = GameEnemyConfig[j].enemyType;
                
                gameAddMonsterOrderBuffer[addMonsterIndex] = GAME_ENEMY_MONSTERS_LAND_BOSS_STAR;
                addMonsterIndex++;
            }
            
            
            if (enemyAddType & GAME_ADD_ENEMY_MONSTERS_LAND_NIMA)
            {
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_NIMA].type = GAME_ENEMY_MONSTERS_LAND_NIMA;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_NIMA].addEnemyNum = GameEnemyConfig[j].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_NIMA].addEnemyTime = GameEnemyConfig[j + 1].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_NIMA].addEnemySpeed = GameEnemyConfig[j + 2].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_NIMA].addEnemyLife = GameEnemyConfig[j + 3].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_NIMA].addEnemyMoney = GameEnemyConfig[j + 4].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_NIMA].addEnemyNumIndex = 0;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_NIMA].addEnemyTimeCounter = 0;
                addMonsterNum += addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_NIMA].addEnemyNum;
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_NIMA].addEnemyMonsterID = GameEnemyConfig[j].enemyType;
                
                gameAddMonsterOrderBuffer[addMonsterIndex] = GAME_ENEMY_MONSTERS_LAND_NIMA;
                addMonsterIndex++;
            }
            
            if (enemyAddType & GAME_ADD_ENEMY_MONSTERS_LAND_PINK)
            {
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_PINK].type = GAME_ENEMY_MONSTERS_LAND_PINK;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_PINK].addEnemyNum = GameEnemyConfig[j].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_PINK].addEnemyTime = GameEnemyConfig[j + 1].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_PINK].addEnemySpeed = GameEnemyConfig[j + 2].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_PINK].addEnemyLife = GameEnemyConfig[j + 3].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_PINK].addEnemyMoney = GameEnemyConfig[j + 4].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_PINK].addEnemyNumIndex = 0;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_PINK].addEnemyTimeCounter = 0;
                addMonsterNum += addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_PINK].addEnemyNum;
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_PINK].addEnemyMonsterID = GameEnemyConfig[j].enemyType;
                
                gameAddMonsterOrderBuffer[addMonsterIndex] = GAME_ENEMY_MONSTERS_LAND_PINK;
                addMonsterIndex++;
            }
            
            if (enemyAddType & GAME_ADD_ENEMY_MONSTERS_LAND_STAR)
            {
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_STAR].type = GAME_ENEMY_MONSTERS_LAND_STAR;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_STAR].addEnemyNum = GameEnemyConfig[j].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_STAR].addEnemyTime = GameEnemyConfig[j + 1].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_STAR].addEnemySpeed = GameEnemyConfig[j + 2].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_STAR].addEnemyLife = GameEnemyConfig[j + 3].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_STAR].addEnemyMoney = GameEnemyConfig[j + 4].value;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_STAR].addEnemyNumIndex = 0;
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_STAR].addEnemyTimeCounter = 0;
                addMonsterNum += addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_STAR].addEnemyNum;
                
                addEnemyTypeBuffer[GAME_ENEMY_MONSTERS_LAND_STAR].addEnemyMonsterID = GameEnemyConfig[j].enemyType;
                
                gameAddMonsterOrderBuffer[addMonsterIndex] = GAME_ENEMY_MONSTERS_LAND_STAR;
                addMonsterIndex++;
            }
            
            j += 5;
        }
        startIndex = j;
        GameStageConClass::sharedStageCon()->setConfigDataIndex(startIndex);
        gameStageSubRoundIndex++;
        GameStageConClass::sharedStageCon()->setGameStageSubRoundIndex(gameStageSubRoundIndex);
        return false;
    }
    else
    {
        return true;
    }
    
	

}

void GameAddEnemyClass::getEnemyDataFromConfigOnStage()
{
    int curIndex = 0;
    int tmpCurIndex = 0;
    int tmpValue = 0;
    int count = 0;
    int j = 0;
    int k = 0;
    int m = 0;
    int n = 0;
    int l = 0;
    int configNum = sizeof(GameEnemyConfig) / sizeof(gameAddEnemyDataStruct);
    
    for (int i = 0; i < configNum; ) {
        if (GameEnemyConfig[i].index == gameStageCurIndex) {
            startIndex = i;
            m = startIndex;
            n = GameEnemyConfig[i].value;
            gameStageRoundNum = GameEnemyConfig[startIndex].value;
			
            k = GameStageConClass::sharedStageCon()->getGameStageRoundIndex();
            for (l = 0; l < n; l++) {
                if (GameEnemyConfig[m + 1].index == ((100 + k))) {
                    startIndex = m + 1;
                    GameStageConClass::sharedStageCon()->setGameStageRoundMoney(GameEnemyConfig[startIndex].roundMoney);//get round money
					GameStageConClass::sharedStageCon()->setGameStageAddTowerType(GameEnemyConfig[startIndex].roundAddTowerType);
                    GameStageConClass::sharedStageCon()->setGameStageRoundNum(gameStageRoundNum);
                    
                    gameStageSubRoundNum = GameEnemyConfig[startIndex].value;
                    GameStageConClass::sharedStageCon()->setGameStageSubRoundNum(gameStageSubRoundNum);
                    GameStageConClass::sharedStageCon()->setIsGameGiftCurLevel(GameEnemyConfig[startIndex].isGift);
                    GameStageConClass::sharedStageCon()->setGameThemeBGColorID(GameEnemyConfig[startIndex].themeBGColorID);
                    GameStageConClass::sharedStageCon()->setShowNewTowerType((GAME_SUBROUND_ADD_NEW_TOWER_TYPE)GameEnemyConfig[startIndex].newTowerType);
                    break;
                }
                else
                {
                    if (GameEnemyConfig[m + 1].stageRoundType == GAME_STAGE_SUBROUND_TOTALNUM) {
                        tmpValue = GameEnemyConfig[m + 1].value;
                        
                        m = m + 1;
                        j = 0;
                        for (int p = 0; p < tmpValue; p++) {
                            j = GameEnemyConfig[m + 1].value;
                            j = j * 5;
                            m += (j + 1);
                        }
                    }
                    else
                    {
                        m += 1;
                    }
                }
            }
            
            break;
        }
        else
        {
            if (GameEnemyConfig[i].stageRoundType == GAME_STAGE_ROUND_TOTALNUM) {
                tmpValue = GameEnemyConfig[i].value;
                m = 0;
                k = 0;
                j = 0;
                l = 0;

                m = i + 1;
                
                for (int n = 0; n < tmpValue; n++) {
                    k = GameEnemyConfig[m].value;
                    for (int p = 0; p < k; p++) {
                        j = GameEnemyConfig[m + 1].value;
                        j = j * 5;
                        m += (j + 1);
                    }
                    //k += m;
                    m += 1;
                }
                i = m;
            }
            else
            {
                i += 1;
            }
        }
    }
    
    
    
    gameStageSubRoundIndex = 0;
    startIndex += 1;
    GameStageConClass::sharedStageCon()->setConfigDataIndex(startIndex);
    GameStageConClass::sharedStageCon()->setConfigDataFirstIndex(startIndex);
    gameStageRoundIndex =  GameStageConClass::sharedStageCon()->getGameStageRoundIndex();
}

void GameAddEnemyClass::gameAddEnemyStartAni(bool isGameSpeed2X, cocos2d::CCNode *parent, cocos2d::CCPoint pos, cocos2d::CCPoint secPos)
{
    CCAssert(!(parent == NULL), "cannot be NULL");
    float totalActTime = 0.5;
    float speedX = 1;
    float aniTime = 0.25;
    char buffer[20] = {0};
    CCArray* aniArray = CCArray::create();
    CCSprite* addEnemyAni = CCSprite::createWithSpriteFrameName("mcm01.png");
    
    LcdAdapClass::sharedLCDADAP()->setAdaptorNodePos(addEnemyAni, ccp(pos.x,pos.y + LcdAdapClass::sharedLCDADAP()->getGameMapTiledSize().height / 2));
    parent->addChild(addEnemyAni,GAMEING_SHOW_COM_ANI);
    
    for (int i = 1; i < 3; i++) {
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "mcm%02d.png",i);
        aniArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer));
    }
    if (isGameSpeed2X) {
        speedX = 2;
    }
    
    totalActTime /= speedX;
    aniTime /= speedX;
    
    CCPoint subPos = ccpSub(secPos, pos);
    int offx = subPos.x/5;
    int offy = subPos.y/5;
    CCMoveBy* mby = CCMoveBy::create(totalActTime, ccp(offx, offy));
    CCScaleBy* mscale = CCScaleBy::create(totalActTime, 1.5);
    
    addEnemyAni->runAction(CCSpawn::create(mby,mscale,CCSequence::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(aniArray,aniTime)),CCCallFuncN::create(this, callfuncN_selector(GameAddEnemyClass::gameAddEnemyStartAniCallBack)),NULL),NULL));
    
}

void GameAddEnemyClass::gameAddEnemyStartAniCallBack(cocos2d::CCNode *node)
{
    CCSprite* addAni = (CCSprite*)node;
    
    addAni->stopAllActions();
    addAni->removeFromParentAndCleanup(true);
}


void GameAddEnemyClass::updateAddEnemy(cocos2d::CCNode *node, float dt, cocos2d::CCArray *posArray, cocos2d::CCArray *parentArray1, cocos2d::CCArray *parentArray2, cocos2d::CCArray *deathArray, bool isSpeed2XFlag)
{
    CCAssert(!(node == NULL),"cannot be NULL");
    CCAssert(!(posArray == NULL),"cannot be NULL");
    CCAssert(!(parentArray1 == NULL),"cannot be NULL");
    CCAssert(!(parentArray2 == NULL),"cannot be NULL");
    CCAssert(!(deathArray == NULL),"cannot be NULL");
    
    static float timerCounter = 0;
    float addTimeMax = 1;
    
    //bool isAddAllMonsters = false;
    //int speedX = 1;
	
    if (isSpeed2XFlag) {
        //speedX = 2;
        addTimeMax /= 2;
    }
    
    timerCounter += dt;
    if (timerCounter >= addTimeMax) {
        timerCounter = 0;
        
        if (addMonsterIndex > 0 && addMonsterNum > 0) {
            for (int i = 0; i < addMonsterIndex; ) {
                int monsterTypeIndex = gameAddMonsterOrderBuffer[i];
                
                if (addEnemyTypeBuffer[monsterTypeIndex].addEnemyNum > 0) {
                    if (addEnemyTypeBuffer[monsterTypeIndex].addEnemyNumIndex < addEnemyTypeBuffer[monsterTypeIndex].addEnemyNum)
                    {
                        CCNode* node0 = (CCNode*)posArray->objectAtIndex(0);
                        CCNode* node1 = (CCNode*)posArray->objectAtIndex(1);
                        this->gameAddEnemyStartAni(isSpeed2XFlag,node, node0->getPosition(),node1->getPosition());
                        
                        EnemySpriteClass* enemy = EnemySpriteClass::createEnemy(addEnemyTypeBuffer[monsterTypeIndex].type,posArray);
                        enemy->setAddEnemyDirType(GAME_ADD_ENEMY_FROM_DIR_LEFT);
                        
                        enemy->setMoneyType((GAME_MONEY_SCORE_TYPE)addEnemyTypeBuffer[monsterTypeIndex].addEnemyMoney);
                        
                        
                        
                        if (isSpeed2XFlag) {
                            enemy->setEnemyLifeAndSpeed(addEnemyTypeBuffer[monsterTypeIndex].addEnemyLife, addEnemyTypeBuffer[monsterTypeIndex].addEnemySpeed * 2);
                        }
                        else
                        {
                            enemy->setEnemyLifeAndSpeed(addEnemyTypeBuffer[monsterTypeIndex].addEnemyLife, addEnemyTypeBuffer[monsterTypeIndex].addEnemySpeed);
                        }
                        
                        //enemy->setIsSpeed2X(isSpeed2XFlag);
                        enemy->setEnemyType(GAME_ENEMY_TYPE_MONSTERS);//only monster start run action
                        enemy->setDeathArray(deathArray);
                        parentArray1->addObject(enemy);
                        parentArray2->addObject(enemy);
                        node->addChild(enemy,GAMEING_ENEMY_ZORDER);
                        
                        addEnemyTypeBuffer[monsterTypeIndex].addEnemyNumIndex++;
                        break;
                    }
                    else
                    {
                        i += 1;
                        addEnemyTypeBuffer[monsterTypeIndex].isAddFinish = true;
                    }
                }
                else
                {
                    i += 1;
                }
            }
        }
        else
        {
            addMonsterIndex = 0;
        }
    }

    
    
    
//	for (int i = GAME_ENEMY_MONSTERS_BEGIN; i < GAME_ENEMY_MONSTERS_MAX;i++)
//	{
//		if (addEnemyTypeBuffer[i].addEnemyNum > 0)
//		{
//			addEnemyTypeBuffer[i].addEnemyTimeCounter += dt;
//			if (addEnemyTypeBuffer[i].addEnemyTimeCounter >= (addEnemyTypeBuffer[i].addEnemyTime/speedX))
//			{
//				if (addEnemyTypeBuffer[i].addEnemyNum > 0) {
//                    if (addEnemyTypeBuffer[i].addEnemyNumIndex < addEnemyTypeBuffer[i].addEnemyNum)
//                    {
//                        CCNode* node0 = (CCNode*)posArray->objectAtIndex(0);
//                        CCNode* node1 = (CCNode*)posArray->objectAtIndex(1);
//                        this->gameAddEnemyStartAni(isSpeed2XFlag,node, node0->getPosition(),node1->getPosition());
//                        
//                        EnemySpriteClass* enemy = EnemySpriteClass::createEnemy(addEnemyTypeBuffer[i].type,posArray);
//                        enemy->setAddEnemyDirType(GAME_ADD_ENEMY_FROM_DIR_LEFT);
//                        
//						enemy->setMoneyType((GAME_MONEY_SCORE_TYPE)addEnemyTypeBuffer[i].addEnemyMoney);
//                        
//                        
//                        
//                        if (isSpeed2XFlag) {
//                            enemy->setEnemyLifeAndSpeed(addEnemyTypeBuffer[i].addEnemyLife, addEnemyTypeBuffer[i].addEnemySpeed * 2);
//                        }
//                        else
//                        {
//                            enemy->setEnemyLifeAndSpeed(addEnemyTypeBuffer[i].addEnemyLife, addEnemyTypeBuffer[i].addEnemySpeed);
//                        }
//                        
//                        //enemy->setIsSpeed2X(isSpeed2XFlag);
//                        enemy->setEnemyType(GAME_ENEMY_TYPE_MONSTERS);//only monster start run action
//                        enemy->setDeathArray(deathArray);
//                        parentArray1->addObject(enemy);
//                        parentArray2->addObject(enemy);
//                        node->addChild(enemy,GAMEING_ENEMY_ZORDER);
//                        
//                        addEnemyTypeBuffer[i].addEnemyNumIndex++;
//                    }
//                    else
//                    {
//                        addEnemyTypeBuffer[i].isAddFinish = true;
//                    }
//                    
//                    addEnemyTypeBuffer[i].addEnemyTimeCounter = 0;
//                }
//			}
//			
//		}
//		
//	}
	
}
