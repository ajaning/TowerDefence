//
//  GameMusicConClass.h
//  CaratonFatans
//
//  Created by jack on 13-12-20.
//
//

#ifndef __CaratonFatans__GameMusicConClass__
#define __CaratonFatans__GameMusicConClass__

#include <iostream>
#include "cocos2d.h"
#include "GameMusicKey.h"

USING_NS_CC;
class GameMusicConClass:public CCObject
{
private:
    GameMusicConClass();
    ~GameMusicConClass();
    bool init();
    CREATE_FUNC(GameMusicConClass);
public:
    static GameMusicConClass* sharedMusicCon();
    void loadGameMusicEffectRes();
    
    void playGameById(GAME_MUSIC_EFFECT_TYPE musicType);
    
    void pauseBGMusic(bool flag);
    void pauseGameMusicEffect(bool flag);
private:
    
};


#endif /* defined(__CaratonFatans__GameMusicConClass__) */
