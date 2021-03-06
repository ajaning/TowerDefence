//
//  GameAddEnemyClass.h
//  CaratonFatans
//
//  Created by jack on 13-7-15.
//
//

#ifndef __CaratonFatans__GameAddEnemyClass__
#define __CaratonFatans__GameAddEnemyClass__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class GameAddEnemyClass:public CCNode
{
private:
    GameAddEnemyClass();
    ~GameAddEnemyClass();
    bool init(int stage);

    void gameAddEnemyStartAni(bool isGameSpeed2X,CCNode* parent,CCPoint pos,CCPoint secPos);
    void gameAddEnemyStartAniCallBack(CCNode* node);
    void getEnemyDataFromConfigOnStage(void);
public:
	static GameAddEnemyClass* create(int stage);
	void updateAddEnemy(CCNode* node,float dt,CCArray* posArray,CCArray* parentArray1,CCArray* parentArray2,CCArray* deathArray,bool isSpeed2XFlag);
	void setGameStageNextRound();
    bool setGameStageNextSubRound();
	unsigned int getAddMonsterNum();
	void setMonsterNum(unsigned int value);//update by main ui
	bool checkIsAddMonstersFinish();
    void setStartIndex(int value);
    
private:
	
	bool isAddFinish;
    int addMonsterIndex;//添加MONSTER的顺序
    int addMonsterTotalNum;
    int startIndex;
	int gameStageCurIndex;
	int gameStageRoundNum;
	int gameStageRoundIndex;
    int gameStageSubRoundIndex;
    int gameStageSubRoundNum;
	unsigned int addMonsterNum;
};


#endif /* defined(__CaratonFatans__GameAddEnemyClass__) */
