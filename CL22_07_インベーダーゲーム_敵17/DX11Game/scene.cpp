//=============================================================================
//
// シーン遷移処理 [scene.cpp]
// Author : 前地智貴
//
//=============================================================================
#include "scene.h"
#include "title.h"
#include "game.h"
#include "gameover.h"
#include "gameclear.h"
#include "gameRanking.h"
#include "SceneStart.h"



//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int 	g_nScene = SCENE_NOTE;				// 現在のシーン



//=============================================================================
// シーンの初期化処理
//=============================================================================
HRESULT InitScene()
{
	SetScene(SCENE_START);//SCENE_TITLE);			// 最初はタイトル画面
	return S_OK;
}



//=============================================================================
// シーンの終了処理
//=============================================================================
void UninitScene()
{
	SetScene(SCENE_NOTE);			// 現在のシーンを終了
}



//=============================================================================
// シーンの更新処理
//=============================================================================
void UpdateScene()
{
	switch (g_nScene) 
	{
	case SCENE_START:		// スタート画面
		UpdateSceneStart();
		break;

	case SCENE_TITLE:		// タイトル画面
		UpdateTitle();
		break;

	case SCENE_GAME:		// ゲーム画面
		UpdateGame();
		break;

	case SCENE_GAMEOVER:		// ゲームオーバー画面
		Updategameover();
		break;

	case SCENE_GAMECLEAR:		// ゲームクリア画面
		UpdategameClear();
		break;

	case SCENR_RANKING:			// ランキング
		UpdategameRanking();	
		break;
	}
}



//=============================================================================
// シーン描画処理
//=============================================================================
void DrawScene()
{
	switch (g_nScene)
	{
	case SCENE_START:		// スタート画面
		DrawSceneStart();
		break;

	case SCENE_TITLE:		// タイトル画面
		DrawTitle();
		break;

	case SCENE_GAME:		// ゲーム画面
		DrawGame();
		break;

	case SCENE_GAMEOVER:		// ゲームオーバー画面
		Drawgameover();
		break;

	case SCENE_GAMECLEAR:		// ゲームクリア画面
		DrawgameClear();
		break;

	case SCENR_RANKING:			// ランキング
		DrawgameRanking();
		break;
	}
}



//=============================================================================
// シーン切り替え処理
//=============================================================================
void SetScene(int nScene)
{
	// 現在のシーンを終了
	switch (nScene)
	{
	case SCENE_START:		// スタート画面
		UninitSceneStart();
		break;

	case SCENE_TITLE:	// タイトル画面
		UninitSceneStart();
		UninitgameRanking();
		UninitSceneStart();
		UninitTitle();
		break;

	case SCENE_GAME:	// ゲーム画面
		UninitTitle();
		UninitGame();
		break;

	case SCENE_GAMEOVER:	// ゲームオーバー画面
		UninitGame();
		Uninitgameover();
		break;

	case SCENE_GAMECLEAR:		// ゲームクリア画面
		UninitGame();
		UninitgameClear();
		break;

	case SCENR_RANKING:			// ランキング
		UninitgameClear();
		Uninitgameover();
		UninitgameRanking();
		break;
	}
	g_nScene = nScene;
	// 次のシーンを初期化
	switch (nScene)
	{
	case SCENE_START:		// スタート画面
		InitSceneStart();
		break;

	case SCENE_TITLE:	// タイトル画面
		// 初期化
		InitTitle();
			break;

	case SCENE_GAME:	// ゲーム画面
		// 初期化
		InitGame();
			break;

	case SCENE_GAMEOVER:	// ゲーム画面
		// 初期化
		Initgameover();
		break;

	case SCENE_GAMECLEAR:		// ゲームクリア画面
		// 初期化
		InitgameClear();
		break;

	case SCENR_RANKING:			// ランキング
		// 初期化
		InitgameRanking();
		break;
	}
}
