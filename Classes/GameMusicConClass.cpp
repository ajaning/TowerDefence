//
//  GameMusicConClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-12-20.
//
//

#include "GameMusicConClass.h"
#include "SimpleAudioEngine.h"

#define MUISC_MP3_TYPE  ".mp3"
#define MUSIC_OGG_TYPE  ".ogg"

#define GAME_MUSIC_EFFECT_TYPE_MAIN_BG_MUSIC_PATH "Music/Main/BGMusic"
#define GAME_MUSIC_EFFECT_TYPE_MAIN_COMPLISH_PATH "Music/Main/Accomplish"
#define GAME_MUSIC_EFFECT_TYPE_MAIN_SELECT_PATH "Music/Main/Select"
#define GAME_MUSIC_EFFECT_TYPE_MAIN_UNLOCK_PATH "Music/Main/Unlock"

#define GAME_MUSIC_EFFECT_TYPE_ITEM_MENU_SELECT_PATH "Music/Items/MenuSelect"
#define GAME_MUSIC_EFFECT_TYPE_ITEM_COUNT_DOWN_PATH "Music/Items/CountDown"
#define GAME_MUSIC_EFFECT_TYPE_ITEM_GO_PATH "Music/Items/GO"
#define GAME_MUSIC_EFFECT_TYPE_ITEM_TOWER_SELECT_PATH "Music/Items/TowerSelect"
#define GAME_MUSIC_EFFECT_TYPE_ITEM_BOMB_PATH "Music/Items/bomb"
#define GAME_MUSIC_EFFECT_TYPE_ITEM_TOWER_UPDATE_PATH "Music/Items/TowerUpdata"
#define GAME_MUSIC_EFFECT_TYPE_ITEM_GAME_LOSE_PATH "Music/Items/Lose"
#define GAME_MUSIC_EFFECT_TYPE_ITEM_GAME_WIN_PATH "Music/Items/Perfect"



static GameMusicConClass* sharedCon = NULL;

static char comBuffer[255] = {0};

GameMusicConClass::GameMusicConClass()
{

}

GameMusicConClass::~GameMusicConClass()
{
    
}

bool GameMusicConClass::init()
{
    
    
    return true;
}


GameMusicConClass* GameMusicConClass::sharedMusicCon()
{
    if (sharedCon == NULL) {
        sharedCon = new GameMusicConClass();
        sharedCon->init();
    }
    
    return sharedCon;
}

void GameMusicConClass::loadGameMusicEffectRes()
{
    char* pType = NULL;
    
    pType = MUISC_MP3_TYPE;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    pType = MUISC_MP3_TYPE;
//#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    pType = MUISC_MP3_TYPE;
//#endif
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.99);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.99);
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%s%s",GAME_MUSIC_EFFECT_TYPE_MAIN_BG_MUSIC_PATH,pType);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(comBuffer);
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%s%s",GAME_MUSIC_EFFECT_TYPE_MAIN_COMPLISH_PATH,pType);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(comBuffer);
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%s%s",GAME_MUSIC_EFFECT_TYPE_MAIN_SELECT_PATH,pType);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(comBuffer);
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%s%s",GAME_MUSIC_EFFECT_TYPE_MAIN_UNLOCK_PATH,pType);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(comBuffer);
    
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%s%s",GAME_MUSIC_EFFECT_TYPE_ITEM_MENU_SELECT_PATH,pType);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(comBuffer);
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%s%s",GAME_MUSIC_EFFECT_TYPE_ITEM_COUNT_DOWN_PATH,pType);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(comBuffer);
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%s%s",GAME_MUSIC_EFFECT_TYPE_ITEM_GO_PATH,pType);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(comBuffer);
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%s%s",GAME_MUSIC_EFFECT_TYPE_ITEM_TOWER_SELECT_PATH,pType);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(comBuffer);
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%s%s",GAME_MUSIC_EFFECT_TYPE_ITEM_BOMB_PATH,pType);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(comBuffer);
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%s%s",GAME_MUSIC_EFFECT_TYPE_ITEM_TOWER_UPDATE_PATH,pType);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(comBuffer);
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%s%s",GAME_MUSIC_EFFECT_TYPE_ITEM_GAME_LOSE_PATH,pType);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(comBuffer);
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%s%s",GAME_MUSIC_EFFECT_TYPE_ITEM_GAME_WIN_PATH,pType);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(comBuffer);
    
}

void GameMusicConClass::playGameById(GAME_MUSIC_EFFECT_TYPE musicType)
{
    CCAssert(!(musicType == GAME_MUSIC_EFFECT_TYPE_NONE || musicType == GAME_MUSIC_EFFECT_TYPE_MAX), "invalid");
    
    char* pFileName = NULL;
    
    char* pType = NULL;

    pType = MUISC_MP3_TYPE;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    pType = MUISC_MP3_TYPE;
//#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    pType = MUSIC_OGG_TYPE;
//#endif
    
    switch (musicType) {
        case GAME_MUSIC_EFFECT_TYPE_MAIN_BG_MUSIC:
            pFileName = GAME_MUSIC_EFFECT_TYPE_MAIN_BG_MUSIC_PATH;
            break;
        case GAME_MUSIC_EFFECT_TYPE_MAIN_COMPLISH:
            pFileName = GAME_MUSIC_EFFECT_TYPE_MAIN_COMPLISH_PATH;
            break;
        case GAME_MUSIC_EFFECT_TYPE_MAIN_SELECT:
            pFileName = GAME_MUSIC_EFFECT_TYPE_MAIN_SELECT_PATH;
            break;
        case GAME_MUSIC_EFFECT_TYPE_MAIN_UNLOCK:
            pFileName = GAME_MUSIC_EFFECT_TYPE_MAIN_UNLOCK_PATH;
            break;
        case GAME_MUSIC_EFFECT_TYPE_ITEM_MENU_SELECT:
            pFileName = GAME_MUSIC_EFFECT_TYPE_ITEM_MENU_SELECT_PATH;
            break;
        case GAME_MUSIC_EFFECT_TYPE_ITEM_COUNT_DOWN:
            pFileName = GAME_MUSIC_EFFECT_TYPE_ITEM_COUNT_DOWN_PATH;
            break;
        case GAME_MUSIC_EFFECT_TYPE_ITEM_GO:
            pFileName = GAME_MUSIC_EFFECT_TYPE_ITEM_GO_PATH;
            break;
        case GAME_MUSIC_EFFECT_TYPE_ITEM_TOWER_SELECT:
            pFileName = GAME_MUSIC_EFFECT_TYPE_ITEM_TOWER_SELECT_PATH;
            break;
        case GAME_MUSIC_EFFECT_TYPE_ITEM_BOMB:
            pFileName = GAME_MUSIC_EFFECT_TYPE_ITEM_BOMB_PATH;
            break;
        case GAME_MUSIC_EFFECT_TYPE_ITEM_TOWER_UPDATE:
            pFileName = GAME_MUSIC_EFFECT_TYPE_ITEM_TOWER_UPDATE_PATH;
            break;
        case GAME_MUSIC_EFFECT_TYPE_ITEM_GAME_LOSE:
            pFileName = GAME_MUSIC_EFFECT_TYPE_ITEM_GAME_LOSE_PATH;
            break;
        case GAME_MUSIC_EFFECT_TYPE_ITEM_GAME_WIN:
            pFileName = GAME_MUSIC_EFFECT_TYPE_ITEM_GAME_WIN_PATH;
            break;
            
        default:
            pFileName = GAME_MUSIC_EFFECT_TYPE_MAIN_UNLOCK_PATH;
            break;
    }
    
    memset(comBuffer, 0, sizeof(comBuffer));
    sprintf(comBuffer, "%s%s",pFileName,pType);
    if (musicType == GAME_MUSIC_EFFECT_TYPE_MAIN_BG_MUSIC) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(comBuffer, true);
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(comBuffer);
    }
    
}


void GameMusicConClass::pauseBGMusic(bool flag)
{
    if (flag) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
}

void GameMusicConClass::pauseGameMusicEffect(bool flag)
{
    if (flag) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    }
}

