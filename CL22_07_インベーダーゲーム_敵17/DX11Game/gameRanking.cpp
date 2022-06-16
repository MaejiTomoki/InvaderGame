//=============================================================================
//
// タイトル画面処理 [gameRanking.cpp]
// Author : 前地智貴
//
//=============================================================================
#include "gameRanking.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "scene.h"
#include "fade.h"
#include "number.h"
#include "score.h"
#include "Sound.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAMEOVER_TEXTURENAME	L"data/texture/GameClear.png"	// テクスチャファイル名

#define GAMERANKING_POS_X		0								// ポリゴンの表示位置
#define GAMERANKING_POS_Y		0								// ポリゴンの表示位置
#define GAMERANKING_SIZE_X		SCREEN_WIDTH					// ポリゴンのサイズ
#define GAMERANKING_SIZE_Y		SCREEN_HEIGHT					// ポリゴンのサイズ
#define GAMERANKING_TIMER		(60+30)
#define GAMERANKING_SCORE	6								// ゲームランキングの最大スコア



//****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// テクスチャ
static int g_nTimer;
static int							g_nScoreGameClear;		// スコアの値
XMFLOAT2							g_vPosGameClear;		// 数字の位置
XMFLOAT2							g_vPosGameClearlastTime1;// 前回スコアの数字の位置
XMFLOAT2							g_vPosGameClearlastTime2;// 前回スコアの数字の位置
XMFLOAT2							g_vPosGameClearlastTime3;// 前回スコアの数字の位置
XMFLOAT2							g_vPosGameClearlastTime4;// 前回スコアの数字の位置
XMFLOAT2							g_vPosGameClearlastTime5;// 前回スコアの数字の位置
CScore								g_ScoreGameClear;		// スコア
int									g_nScoreArra[GAMERANKING_SCORE] = { 0,0,0,0,0,0 };		// スコア保存用
FILE *								fp = NULL;



//=============================================================================
// 背景表示の初期化処理
//=============================================================================
HRESULT InitgameRanking()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		GAMEOVER_TEXTURENAME, &g_pTexture);

	g_nTimer = GAMERANKING_TIMER;

	// スコアの場所の初期化
	g_vPosGameClear = XMFLOAT2(-210.0f, 280.0f);
	g_vPosGameClearlastTime1 = XMFLOAT2(-160.0f, 100.0f);
	g_vPosGameClearlastTime2 = XMFLOAT2(-160.0f,   25.0f);
	g_vPosGameClearlastTime3 = XMFLOAT2(-160.0f, -50.0f);
	g_vPosGameClearlastTime4 = XMFLOAT2(-160.0f, -125.0f);
	g_vPosGameClearlastTime5 = XMFLOAT2(-160.0f, -200.0f);

	// 現在のスコアの値を持ってくる
	g_nScoreGameClear = g_ScoreGameClear.GetScore();

	// デバッグ用
	// g_nScoreGameClear = 900;

	int		age1 = 0;
	int		age2 = 0;
	int		age3 = 0;
	int		age4 = 0;
	int		age5 = 0;
	int		temp = 0;
	int		j = 0;

	//	読み込みモードでファイルを開く
	fopen_s(&fp, "data/txt/Ranking.txt", "r");

	//	ファイル終端まで1行ずつ変数へ読み込む
	while (fscanf_s(fp, " %d\n%d\n%d\n%d\n%d\n ", &age1,&age2, &age3, &age4, &age5) != EOF)
	{
		g_nScoreArra[0] = age1;
		g_nScoreArra[1] = age2; 
		g_nScoreArra[2] = age3;
		g_nScoreArra[3] = age4;
		g_nScoreArra[4] = age5;
	}
	
	fclose(fp);

	g_nScoreArra[5] = g_nScoreGameClear;

	// 数字の大きさを比べて大きい順に並べる
	for (int i = 0; i < GAMERANKING_SCORE; ++i)
	{
		for (j = i + 1; j < GAMERANKING_SCORE; ++j)
		{
			if (g_nScoreArra[i] < g_nScoreArra[j])
			{

				temp = g_nScoreArra[i];
				g_nScoreArra[i] = g_nScoreArra[j];
				g_nScoreArra[j] = temp;

			}
		}
	}

	// ファイルの書き換え呼び出し
	fopen_s(&fp, "data/txt/Ranking.txt", "w");

	// 現在のスコアにファイルの書き換え
	fprintf(fp, "%d\n%d\n%d\n%d\n%d\n", g_nScoreArra[0], g_nScoreArra[1], g_nScoreArra[2], g_nScoreArra[3], g_nScoreArra[4]);

	// ファイルを閉じる
	fclose(fp);

	// BGM停止
	CSound::Stop(BGM_000);

	// BGMスタート
	CSound::Play(BGM_111);

	return hr;
}



//=============================================================================
// 背景表示の終了処理
//=============================================================================
void UninitgameRanking()
{
	//g_nScoreArra[0] = g_nScoreGameClear;
	// BGM停止
	// CSound::Stop(BGM_000);

	// テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}



//=============================================================================
// 背景表示の更新処理
//=============================================================================
void UpdategameRanking()
{
	// スコアの値を持ってくる
	//g_nScoreGameClear = g_ScoreGameClear.GetScore();

	// スペースキーを押したらゲーム開始
	if (GetKeyRelease(VK_SPACE)) {
		if (GetKeyRelease(VK_SPACE)) {
			SetFadeOut(SCENE_TITLE);
		}
	}
}



//=============================================================================
// 背景表示処理
//=============================================================================
void DrawgameRanking()
{
	// 背景描画
	SetPolygonPos(GAMERANKING_POS_X, GAMERANKING_POS_Y);
	SetPolygonSize(GAMERANKING_SIZE_X, GAMERANKING_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());

	// 色の変化
	SetPolygonColor(0.0f, 1.0f, 0.0f);

	// スコア表示
	DrawNumber(&g_vPosGameClear,
		(unsigned)g_nScoreGameClear, SCORE_WIDTH, 50, 100);

	// 色の変化
	SetPolygonColor(1.0f, 0.0f, 0.0f);

	// 前回用
	if (g_nScoreArra[0] == g_nScoreGameClear)
	{
		// 色の変化
		SetPolygonColor(0.0f, 1.0f, 0.0f);

		DrawNumber(&g_vPosGameClearlastTime1,
			(unsigned)g_nScoreArra[0], SCORE_WIDTH, 37, 75);

		// 色の変化
		SetPolygonColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		DrawNumber(&g_vPosGameClearlastTime1,
			(unsigned)g_nScoreArra[0], SCORE_WIDTH, 37, 75);
	}
	

	if (g_nScoreArra[1] == g_nScoreGameClear)
	{
		// 色の変化
		SetPolygonColor(0.0f, 1.0f, 0.0f);

		DrawNumber(&g_vPosGameClearlastTime2,
			(unsigned)g_nScoreArra[1], SCORE_WIDTH, 37, 75);

		// 色の変化
		SetPolygonColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		DrawNumber(&g_vPosGameClearlastTime2,
			(unsigned)g_nScoreArra[1], SCORE_WIDTH, 37, 75);
	}

	if (g_nScoreArra[2] == g_nScoreGameClear)
	{
		// 色の変化
		SetPolygonColor(0.0f, 1.0f, 0.0f);

		DrawNumber(&g_vPosGameClearlastTime3,
			(unsigned)g_nScoreArra[2], SCORE_WIDTH, 37, 75);

		// 色の変化
		SetPolygonColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		DrawNumber(&g_vPosGameClearlastTime3,
			(unsigned)g_nScoreArra[2], SCORE_WIDTH, 37, 75);
	}

	if (g_nScoreArra[3] == g_nScoreGameClear)
	{
		// 色の変化
		SetPolygonColor(0.0f, 1.0f, 0.0f);

		DrawNumber(&g_vPosGameClearlastTime4,
			(unsigned)g_nScoreArra[3], SCORE_WIDTH, 37, 75);

		// 色の変化
		SetPolygonColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		DrawNumber(&g_vPosGameClearlastTime4,
			(unsigned)g_nScoreArra[3], SCORE_WIDTH, 37, 75);
	}

	if (g_nScoreArra[4] == g_nScoreGameClear)
	{
		// 色の変化
		SetPolygonColor(0.0f, 1.0f, 0.0f);

		DrawNumber(&g_vPosGameClearlastTime5,
			(unsigned)g_nScoreArra[4], SCORE_WIDTH, 37, 75);

		// 色の変化
		SetPolygonColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		DrawNumber(&g_vPosGameClearlastTime5,
			(unsigned)g_nScoreArra[4], SCORE_WIDTH, 37, 75);
	}

}
