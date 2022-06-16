//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 前地智貴
//
//=============================================================================
#include "title.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "scene.h"
#include "fade.h"
#include "Sound.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_TEXTURENAME	L"data/texture/title.png"	// テクスチャファイル名

#define TITLE_POS_X		0								// ポリゴンの表示位置
#define TITLE_POS_Y		0								// ポリゴンの表示位置
#define TITLE_SIZE_X		SCREEN_WIDTH					// ポリゴンのサイズ
#define TITLE_SIZE_Y		SCREEN_HEIGHT					// ポリゴンのサイズ



//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// テクスチャ



//=============================================================================
// 背景表示の初期化処理
//=============================================================================
HRESULT InitTitle()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		TITLE_TEXTURENAME, &g_pTexture);

	// BGM停止
	CSound::Stop(BGM_111);

	// 再生
	CSound::Play(BGM_001);

	return hr;
}



//=============================================================================
// 背景表示の終了処理
//=============================================================================
void UninitTitle()
{
	// テクスチャ開放
	SAFE_RELEASE(g_pTexture);

	// 終了
	CSound::Stop(BGM_001);
}

//=============================================================================
// 背景表示の更新処理
//=============================================================================
void UpdateTitle()
{
	// スペースキーを押したらゲーム開始
	if (GetKeyRelease(VK_SPACE)) 
	{
		if (GetKeyRelease(VK_SPACE))
		{
			// SE再生
			CSound::Play(SE_COIN);

			SetFadeOut(SCENE_GAME);
		}
	}
}



//=============================================================================
// 背景表示処理
//=============================================================================
void DrawTitle()
{
	// 背景描画
	SetPolygonPos(TITLE_POS_X, TITLE_POS_Y);
	SetPolygonSize(TITLE_SIZE_X, TITLE_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());
}
