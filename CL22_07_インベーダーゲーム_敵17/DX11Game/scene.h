//=============================================================================
//
// シーン遷移処理 [scene.h]
// Author : 前地智貴
//
//=============================================================================
#pragma once

#include "main.h"
//*****************************************************************************
// 定数
//*****************************************************************************
enum EScene {
	SCENE_NOTE = 0,		// 未設定
	SCENE_START,		// スタートを通してからスタート
	SCENE_TITLE,		// タイトル画面
	SCENE_GAME,			// ゲーム画面
	SCENE_GAMEOVER,		// ゲームオーバー画面
	SCENE_GAMECLEAR,	// クリア画面
	SCENR_RANKING,		// ランキング画面

	MAX_SCENE
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScene();	
void UninitScene();
void UpdateScene();
void DrawScene();

void SetScene(int nScene);	// シーン切り替え


