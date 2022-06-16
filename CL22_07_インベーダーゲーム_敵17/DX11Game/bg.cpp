//=============================================================================
//
// 背景表示処理 [bg.cpp]
// Author : 前地智貴
//
//=============================================================================
#include "bg.h"
#include "polygon.h"
#include "Texture.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_TEXTURENAME	L"data/texture/arena001.jpg"	// テクスチャファイル名

#define BG_POS_X		0								// ポリゴンの表示位置
#define BG_POS_Y		0								// ポリゴンの表示位置
#define BG_SIZE_X		SCREEN_WIDTH					// ポリゴンのサイズ
#define BG_SIZE_Y		SCREEN_HEIGHT					// ポリゴンのサイズ



//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// テクスチャ



//=============================================================================
// 背景表示の初期化処理
//=============================================================================
HRESULT InitBG()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		BG_TEXTURENAME, &g_pTexture);

	return hr;
}



//=============================================================================
// 背景表示の終了処理
//=============================================================================
void UninitBG()
{
	// テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}



//=============================================================================
// 背景表示の更新処理
//=============================================================================
void UpdateBG()
{
	// (何もしない)
}



//=============================================================================
// 背景表示処理
//=============================================================================
void DrawBG()
{
	// 背景描画
	SetPolygonPos(BG_POS_X, BG_POS_Y);
	SetPolygonSize(BG_SIZE_X, BG_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());
}
