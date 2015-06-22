LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp\
		../../Classes/AdventureLevelClass.cpp\
		../../Classes/AdventureModeMainClass.cpp\
		../../Classes/AttackTowerClass.cpp\
		../../Classes/BossModeClass.cpp\
		../../Classes/CaratonProClass.cpp\
		../../Classes/CommonClass.cpp\
		../../Classes/comSpriteActionClass.cpp\
		../../Classes/EnemySpriteClass.cpp\
		../../Classes/FontShowClass.cpp\
		../../Classes/ShowWinLoseClass.cpp\
../../Classes/gameADConClass.cpp\
com_game_ad_gameADCon.cpp \
../../Classes/gameShopClass.cpp \
../../Classes/gameADShowClass.cpp\
../../Classes/GameMusicConClass.cpp\
../../Classes/ShowTowerFeatureClass.cpp\
../../Classes/ScrollViewClass.cpp\
../../Classes/PetsNestClass.cpp\
../../Classes/PetsDropClass.cpp\
../../Classes/PetsBreedClass.cpp\
../../Classes/MoneyScoreClass.cpp\
../../Classes/MapPassClass.cpp\
../../Classes/LcdAdapClass.cpp\
../../Classes/HUDClass.cpp\
../../Classes/HelpPlayGame.cpp\
../../Classes/HelpLayerClass.cpp\
../../Classes/GameSubLevelSelClass.cpp\
../../Classes/GameStartLayerClass.cpp\
../../Classes/GameStageConClass.cpp\
../../Classes/GameShowValidPos.cpp\
../../Classes/GameMainLevelClass.cpp\
../../Classes/GameLogoRotateClass.cpp\
../../Classes/GameAddEnemyClass.cpp\
../../Classes/SkyLineDetailClass.cpp\
../../Classes/TowerAddTypeClass.cpp\
../../Classes/TowerBulletClass.cpp\
../../Classes/TowerBulletEffectClass.cpp\
../../Classes/TowerSelPadClass.cpp\
../../Classes/WayPointClass.cpp\
../../Classes/WelcomeLayerClass.cpp\
../../Classes/WhaleClass.cpp\
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
