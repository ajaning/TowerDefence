package com.game.ad;

//import cn.domob.data.OErrorInfo;
import cn.domob.android.ads.DomobInterstitialAd;
import cn.domob.android.ads.DomobInterstitialAdListener;
import cn.domob.android.ads.DomobAdManager.ErrorCode;
import cn.domob.data.OErrorInfo;
import cn.domob.data.OManager;
import cn.domob.data.OManager.AddVideoWallListener;
import cn.domob.data.OManager.CacheVideoAdListener;
import cn.domob.data.OManager.CheckPointsListener;
import cn.domob.data.OManager.ConsumeListener;
import cn.domob.data.OManager.ConsumeStatus;
import android.content.Context;
import cn.domob.data.OManager.AddWallListener;


public class gameADCon{
	private static Context sContext;
	
	private static  OManager myDMOfferWallManager;
	private static  DomobInterstitialAd myDMInterManager;
	private static final String DMOfferWallPublisherID = "96ZJ2b8QzehB3wTAwQ";
	public static final String DMInterPublisherID = "56OJyM1ouMGoaSnvCK";
	public static final String DMIinterPlaceID = "16TLwebvAchksY6iOa7F4DXs";
	public static String DMInterUserIDString = "jack_android_game_yk";
	
	
	private static int GAME_AD_CUR_CLOSE = 2;
	private static int GAME_AD_SUCESS = 1;
	private static int GAME_AD_FAIL = -1;
	
	
	private static int dmAddWallListSuccess = 0;//-1-fail,1-success,2-close
	private static int dmCacheWallVideoSucess = 0;//缓存积分墙视频
	private static int dmPlayWallVideoSucess = 0;//播放积分墙视频成功与否
	private static int dmGetConsumePointSucess = 0;//获取用户总积分
	private static int dmConsumePointSucess = 0;//检测用户是否成功消费
	private static int dmUserTotalPoint = 0;//用户的总积分
	private static int dmUserConsumePoint = 0;//用户已经消费的积分
	private static int dmInterADLoadResult = 0;//广告加载效果
	
	private static native void dmOfferWallAddListStateCallBack(int state);
	private static native void dmOfferWallCacheVideoStateCallBack(int state);
	private static native void dmOfferWallPlayVideoStateCallBack(int state);
	private static native void dmOfferWallCheckPointsStateCallBack(int state,int totalPoint);
	private static native void dmOfferWallConsumePointStateCallBack(int state,int consumeTotalPoint);
	private static native void dmInterADLoadResulta(int state);
	
//	public void setDMManager(final OManager manager)
//	{
//		myOManager = manager;
//	}
	
//	public void handleDmAddWallListStateCallBack(int state)
//	{
//		gameADCon.dmAddWallListStateCallBack(state);
//	}
//	
//	public void handleDmCacheWallVideoStateCallBack(int state)
//	{
//		gameADCon.dmCacheWallVideoStateCallBack(state);
//	}
//	
//	public void handleDmPlayWallVideoStateCallBack(int state)
//	{
//		gameADCon.dmPlayWallVideoStateCallBack(state);
//	}
//	
//	public void handleDmCheckPointsStateCallBack(int state,int totalPoint)
//	{
//		gameADCon.dmCheckPointsStateCallBack(state, totalPoint);
//	}
//	
//	public void handleDmConsumePointStateCallBack(int state,int consumeTotalPoint)
//	{
//		gameADCon.dmConsumePointStateCallBack(state, consumeTotalPoint);
//	}
	
	
	public  void setContext(final Context pContext){
		gameADCon.sContext = pContext;
		myDMOfferWallManager = new OManager(pContext, DMOfferWallPublisherID);
		myDMInterManager = new DomobInterstitialAd(pContext, DMInterPublisherID, DMIinterPlaceID, DomobInterstitialAd.INTERSITIAL_SIZE_300X250);
		gameADCon.initGameDMAD();
	}
	
	public static void initGameDMAD()
	{
		myDMOfferWallManager.setAddWallListener(new AddWallListener() {
			
			@Override
			public void onAddWallSucess() {
				// TODO Auto-generated method stub
				dmAddWallListSuccess = GAME_AD_SUCESS;
				gameADCon.dmOfferWallAddListStateCallBack(GAME_AD_SUCESS);
			}
			
			@Override
			public void onAddWallFailed(OErrorInfo arg0) {
				// TODO Auto-generated method stub
				dmAddWallListSuccess = GAME_AD_FAIL;
				gameADCon.dmOfferWallAddListStateCallBack(GAME_AD_FAIL);
			}
			
			@Override
			public void onAddWallClose() {
				// TODO Auto-generated method stub
				dmAddWallListSuccess = GAME_AD_CUR_CLOSE;
				gameADCon.dmOfferWallAddListStateCallBack(GAME_AD_CUR_CLOSE);
				gameADCon.showDMOfferCheckPoints();
			}
		});
		
		myDMOfferWallManager.setCacheVideoListener(new CacheVideoAdListener() {
			
			@Override
			public void onCacheVideoSucess() {
				// TODO Auto-generated method stub
				dmCacheWallVideoSucess = GAME_AD_SUCESS;
				gameADCon.dmOfferWallCacheVideoStateCallBack(GAME_AD_SUCESS);
				myDMOfferWallManager.presentVideoWall();
			}
			
			@Override
			public void onCacheVideoFailed(OErrorInfo arg0) {
				// TODO Auto-generated method stub
				dmCacheWallVideoSucess = GAME_AD_FAIL;
				gameADCon.dmOfferWallCacheVideoStateCallBack(GAME_AD_FAIL);
				myDMOfferWallManager.presentVideoWall();
			}
		});
		
		myDMOfferWallManager.setAddVideoWallListener(new AddVideoWallListener() {
			
			@Override
			public void onAddWallSucess() {
				// TODO Auto-generated method stub
				dmPlayWallVideoSucess = GAME_AD_SUCESS;
				gameADCon.dmOfferWallPlayVideoStateCallBack(GAME_AD_SUCESS);
			}
			
			@Override
			public void onAddWallFailed(OErrorInfo arg0) {
				// TODO Auto-generated method stub
				dmPlayWallVideoSucess = GAME_AD_FAIL;
				gameADCon.dmOfferWallPlayVideoStateCallBack(GAME_AD_FAIL);
			}
			
			@Override
			public void onAddWallClose() {
				// TODO Auto-generated method stub
				dmPlayWallVideoSucess = GAME_AD_CUR_CLOSE;
				gameADCon.dmOfferWallPlayVideoStateCallBack(GAME_AD_CUR_CLOSE);
				gameADCon.showDMOfferCheckPoints();
			}
		});
		
		myDMOfferWallManager.setCheckPointsListener(new CheckPointsListener() {
			
			@Override
			public void onCheckPointsSucess(int arg0, int arg1) {
				// TODO Auto-generated method stub
				dmGetConsumePointSucess = GAME_AD_SUCESS;
				dmUserTotalPoint = (arg0 - arg1);
				gameADCon.dmOfferWallCheckPointsStateCallBack(GAME_AD_SUCESS, dmUserTotalPoint);
			}
			
			@Override
			public void onCheckPointsFailed(OErrorInfo arg0) {
				// TODO Auto-generated method stub
				dmGetConsumePointSucess = GAME_AD_FAIL;
				gameADCon.dmOfferWallCheckPointsStateCallBack(GAME_AD_FAIL, 0);
			}
		});
		
		myDMOfferWallManager.setConsumeListener(new ConsumeListener() {
			
			@Override
			public void onConsumeSucess(int arg0, int arg1, ConsumeStatus arg2) {
				// TODO Auto-generated method stub
				dmConsumePointSucess = GAME_AD_SUCESS;
				gameADCon.dmOfferWallConsumePointStateCallBack(GAME_AD_SUCESS, 0);
			}
			
			@Override
			public void onConsumeFailed(OErrorInfo arg0) {
				// TODO Auto-generated method stub
				dmConsumePointSucess = GAME_AD_FAIL;
				gameADCon.dmOfferWallConsumePointStateCallBack(GAME_AD_FAIL, 0);
			}
		});
		
		
		myDMInterManager.setInterstitialAdListener(new DomobInterstitialAdListener() {
			
			@Override
			public void onLandingPageOpen() {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onLandingPageClose() {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onInterstitialAdReady() {
				// TODO Auto-generated method stub
				dmInterADLoadResult = GAME_AD_SUCESS;
				gameADCon.dmInterADLoadResulta(GAME_AD_SUCESS);
				gameADCon.showDMInterAD();
			}
			
			@Override
			public void onInterstitialAdPresent() {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onInterstitialAdLeaveApplication() {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onInterstitialAdFailed(ErrorCode arg0) {
				// TODO Auto-generated method stub
				dmInterADLoadResult = GAME_AD_FAIL;
				gameADCon.dmInterADLoadResulta(GAME_AD_FAIL);
			}
			
			@Override
			public void onInterstitialAdDismiss() {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onInterstitialAdClicked(DomobInterstitialAd arg0) {
				// TODO Auto-generated method stub
				
			}
		});
	}
//	
	public static void showDMOfferWallList()
	{
		myDMOfferWallManager.loadOfferWall();
	}
//	
//	
	public static void showDMOfferCacheVideo()
	{
		myDMOfferWallManager.cacheVideoAd();
	}
	
	public static void showDMOfferVideo()
	{
		gameADCon.showDMOfferCacheVideo();
	}
	
	public static void showDMOfferCheckPoints()
	{
		myDMOfferWallManager.checkPoints();
	}
	
	public static void showDMOfferConsumeResult(int consumeTotal)
	{
		myDMOfferWallManager.consumePoints(consumeTotal);
	}
	
	public static void loadDMInterAD()
	{
		myDMInterManager.loadInterstitialAd();
	}
	
	public static void showDMInterAD()
	{
		myDMInterManager.showInterstitialAd(gameADCon.sContext);
	}
	
}