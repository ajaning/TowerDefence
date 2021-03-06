//
//  GameParam.h
//  CaratonFatans
//
//  Created by jack on 13-7-15.
//
//

#ifndef CaratonFatans_GameParam_h
#define CaratonFatans_GameParam_h

#if 1
#define SPRITE_HD_NAME  "%s-hd"
#else
#define SPRITE_HD_NAME  "%s"
#endif

//TOP height{
#define TOPHEIGHT   (100)
#define TOP_VALIDHEIGHT_VALULE (100)
//}


//{zorder
#define WELCOMELAYER_SCENE_ZORDER  (1)

//being in game 处于游戏中时的精灵位置ZORDER{
#define GAMING_LOADING_ZODER    (1)//游戏加载动画

#define GAMEING_BGMAP_ZORDER   (2)   //游戏背景地图
#define GAMEING_PATH_ZODER      (5)//


#define GAMEING_VALIDPOS_ZORDER	(9)
#define GAMEING_TOWER_ZORDER   (10)
#define GAMEING_ENEMY_OBJECT_ZORDER  (15)

#define GAMEING_ENEMY_ZORDER   (25)

#define GAMEING_START_POS_ZORDER    (27)//

#define GAMEING_TOWER_BULLET_ZORDER    (28)

#define GAMEING_USER_SEL_ENEMY_ZORDER   (30)

#define GAMEING_USER_SEL_ENEMY_POINT_ZORDER (35)
#define GAMEING_ENEMY_BLOOD_UI_ZORDER   (40)



#define GAMEING_TOWER_UPDATE_POINT_ZORDER (45)//炮塔可升级的标志的位置

#define GAMEING_ENEMY_TO_SCORE_ZORDER (50)


#define GAMEING_SEL_TOWER_ZORDER    (80)

#define GAMEING_CARATON_ZORDER  (84)//胡萝卜的位置
#define GAMEING_TOWER_SHOWPAD_ZODER (85)
#define GAMING_TOWER_ADD_ZODER (89)

#define GAMEING_SHOW_COM_ANI    (90)
#define GAMEING_MENUITEM_ZODER      (94)
#define GAMEING_SHOW_GO_ZODER      (95)
#define GAMEING_BOSS_BLOOD_ZORDER   (98)
#define GAMEING_SHOW_HELP_ZODER   (100)



#define GAMEING_SHOW_STOP_ICON_ZORDER   (250)

#define GAMEING_MENU_ZORDER    (300)

#define GAMEING_SHOW_GIFT_WHALE_ZORDER  (350)

#define GAMEING_SHOW_NEWTOWER_FEATURE_ZORDER    (400)
//}

//}

//for user pet data info {
#define USER_PET_NUM_MAX    (20) //宠物最大数量
#define USER_BIG_NEST_NUM_MAX (1)//大窝数量  用于鲸鱼宝宝
#define USER_NEST_NUM_MAX      (20) //20个宠物当然有20个窝了
//}



#endif
