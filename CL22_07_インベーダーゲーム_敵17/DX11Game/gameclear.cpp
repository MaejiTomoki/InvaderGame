//=============================================================================
//
// タイトル画面処理 [gameclear.cpp]
// Author : 前地智貴
//
//=============================================================================
//#include "title.h"
#include "gameclear.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "scene.h"
#include "fade.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAMECLEAR_TEXTURENAME	L"data/texture/GameClear_02.png"	// テクスチャファイル名

#define GAMECLEAR_POS_X		0								// ポリゴンの表示位置
#define GAMECLEAR_POS_Y		0								// ポリゴンの表示位置
#define GAMECLEAR_SIZE_X		SCREEN_WIDTH					// ポリゴンのサイズ
#define GAMECLEAR_SIZE_Y		SCREEN_HEIGHT					// ポリゴンのサイズ
#define GAMECLEAR_TIMER		(60+30)



//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// テクスチャ
static int g_nTimer;



//=============================================================================
// 背景表示の初期化処理
//=============================================================================
HRESULT InitgameClear()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		GAMECLEAR_TEXTURENAME, &g_pTexture);

	g_nTimer = GAMECLEAR_TIMER;

	return hr;
}



//=============================================================================
// 背景表示の終了処理
//=============================================================================
void UninitgameClear()
{
	// テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}



//=============================================================================
// 背景表示の更新処理
//=============================================================================
void UpdategameClear()
{
	// スペースキーを押したらゲーム開始
	if (GetKeyRelease(VK_SPACE)) 
	{
		if (GetKeyRelease(VK_SPACE)) 
		{
			SetFadeOut(SCENR_RANKING);
		}
	}
	--g_nTimer;
	if (g_nTimer <= 0) 
	{
		SetFadeOut(SCENR_RANKING);
	}
}



//=============================================================================
// 背景表示処理
//=============================================================================
void DrawgameClear()
{
	// 背景描画
	SetPolygonPos(GAMECLEAR_POS_X, GAMECLEAR_POS_Y);
	SetPolygonSize(GAMECLEAR_SIZE_X, GAMECLEAR_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());
}
