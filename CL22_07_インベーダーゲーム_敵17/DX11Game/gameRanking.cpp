//=============================================================================
//
// �^�C�g����ʏ��� [gameRanking.cpp]
// Author : �O�n�q�M
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
// �}�N����`
//*****************************************************************************
#define GAMEOVER_TEXTURENAME	L"data/texture/GameClear.png"	// �e�N�X�`���t�@�C����

#define GAMERANKING_POS_X		0								// �|���S���̕\���ʒu
#define GAMERANKING_POS_Y		0								// �|���S���̕\���ʒu
#define GAMERANKING_SIZE_X		SCREEN_WIDTH					// �|���S���̃T�C�Y
#define GAMERANKING_SIZE_Y		SCREEN_HEIGHT					// �|���S���̃T�C�Y
#define GAMERANKING_TIMER		(60+30)
#define GAMERANKING_SCORE	6								// �Q�[�������L���O�̍ő�X�R�A



//****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// �e�N�X�`��
static int g_nTimer;
static int							g_nScoreGameClear;		// �X�R�A�̒l
XMFLOAT2							g_vPosGameClear;		// �����̈ʒu
XMFLOAT2							g_vPosGameClearlastTime1;// �O��X�R�A�̐����̈ʒu
XMFLOAT2							g_vPosGameClearlastTime2;// �O��X�R�A�̐����̈ʒu
XMFLOAT2							g_vPosGameClearlastTime3;// �O��X�R�A�̐����̈ʒu
XMFLOAT2							g_vPosGameClearlastTime4;// �O��X�R�A�̐����̈ʒu
XMFLOAT2							g_vPosGameClearlastTime5;// �O��X�R�A�̐����̈ʒu
CScore								g_ScoreGameClear;		// �X�R�A
int									g_nScoreArra[GAMERANKING_SCORE] = { 0,0,0,0,0,0 };		// �X�R�A�ۑ��p
FILE *								fp = NULL;



//=============================================================================
// �w�i�\���̏���������
//=============================================================================
HRESULT InitgameRanking()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		GAMEOVER_TEXTURENAME, &g_pTexture);

	g_nTimer = GAMERANKING_TIMER;

	// �X�R�A�̏ꏊ�̏�����
	g_vPosGameClear = XMFLOAT2(-210.0f, 280.0f);
	g_vPosGameClearlastTime1 = XMFLOAT2(-160.0f, 100.0f);
	g_vPosGameClearlastTime2 = XMFLOAT2(-160.0f,   25.0f);
	g_vPosGameClearlastTime3 = XMFLOAT2(-160.0f, -50.0f);
	g_vPosGameClearlastTime4 = XMFLOAT2(-160.0f, -125.0f);
	g_vPosGameClearlastTime5 = XMFLOAT2(-160.0f, -200.0f);

	// ���݂̃X�R�A�̒l�������Ă���
	g_nScoreGameClear = g_ScoreGameClear.GetScore();

	// �f�o�b�O�p
	// g_nScoreGameClear = 900;

	int		age1 = 0;
	int		age2 = 0;
	int		age3 = 0;
	int		age4 = 0;
	int		age5 = 0;
	int		temp = 0;
	int		j = 0;

	//	�ǂݍ��݃��[�h�Ńt�@�C�����J��
	fopen_s(&fp, "data/txt/Ranking.txt", "r");

	//	�t�@�C���I�[�܂�1�s���ϐ��֓ǂݍ���
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

	// �����̑傫�����ׂđ傫�����ɕ��ׂ�
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

	// �t�@�C���̏��������Ăяo��
	fopen_s(&fp, "data/txt/Ranking.txt", "w");

	// ���݂̃X�R�A�Ƀt�@�C���̏�������
	fprintf(fp, "%d\n%d\n%d\n%d\n%d\n", g_nScoreArra[0], g_nScoreArra[1], g_nScoreArra[2], g_nScoreArra[3], g_nScoreArra[4]);

	// �t�@�C�������
	fclose(fp);

	// BGM��~
	CSound::Stop(BGM_000);

	// BGM�X�^�[�g
	CSound::Play(BGM_111);

	return hr;
}



//=============================================================================
// �w�i�\���̏I������
//=============================================================================
void UninitgameRanking()
{
	//g_nScoreArra[0] = g_nScoreGameClear;
	// BGM��~
	// CSound::Stop(BGM_000);

	// �e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}



//=============================================================================
// �w�i�\���̍X�V����
//=============================================================================
void UpdategameRanking()
{
	// �X�R�A�̒l�������Ă���
	//g_nScoreGameClear = g_ScoreGameClear.GetScore();

	// �X�y�[�X�L�[����������Q�[���J�n
	if (GetKeyRelease(VK_SPACE)) {
		if (GetKeyRelease(VK_SPACE)) {
			SetFadeOut(SCENE_TITLE);
		}
	}
}



//=============================================================================
// �w�i�\������
//=============================================================================
void DrawgameRanking()
{
	// �w�i�`��
	SetPolygonPos(GAMERANKING_POS_X, GAMERANKING_POS_Y);
	SetPolygonSize(GAMERANKING_SIZE_X, GAMERANKING_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());

	// �F�̕ω�
	SetPolygonColor(0.0f, 1.0f, 0.0f);

	// �X�R�A�\��
	DrawNumber(&g_vPosGameClear,
		(unsigned)g_nScoreGameClear, SCORE_WIDTH, 50, 100);

	// �F�̕ω�
	SetPolygonColor(1.0f, 0.0f, 0.0f);

	// �O��p
	if (g_nScoreArra[0] == g_nScoreGameClear)
	{
		// �F�̕ω�
		SetPolygonColor(0.0f, 1.0f, 0.0f);

		DrawNumber(&g_vPosGameClearlastTime1,
			(unsigned)g_nScoreArra[0], SCORE_WIDTH, 37, 75);

		// �F�̕ω�
		SetPolygonColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		DrawNumber(&g_vPosGameClearlastTime1,
			(unsigned)g_nScoreArra[0], SCORE_WIDTH, 37, 75);
	}
	

	if (g_nScoreArra[1] == g_nScoreGameClear)
	{
		// �F�̕ω�
		SetPolygonColor(0.0f, 1.0f, 0.0f);

		DrawNumber(&g_vPosGameClearlastTime2,
			(unsigned)g_nScoreArra[1], SCORE_WIDTH, 37, 75);

		// �F�̕ω�
		SetPolygonColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		DrawNumber(&g_vPosGameClearlastTime2,
			(unsigned)g_nScoreArra[1], SCORE_WIDTH, 37, 75);
	}

	if (g_nScoreArra[2] == g_nScoreGameClear)
	{
		// �F�̕ω�
		SetPolygonColor(0.0f, 1.0f, 0.0f);

		DrawNumber(&g_vPosGameClearlastTime3,
			(unsigned)g_nScoreArra[2], SCORE_WIDTH, 37, 75);

		// �F�̕ω�
		SetPolygonColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		DrawNumber(&g_vPosGameClearlastTime3,
			(unsigned)g_nScoreArra[2], SCORE_WIDTH, 37, 75);
	}

	if (g_nScoreArra[3] == g_nScoreGameClear)
	{
		// �F�̕ω�
		SetPolygonColor(0.0f, 1.0f, 0.0f);

		DrawNumber(&g_vPosGameClearlastTime4,
			(unsigned)g_nScoreArra[3], SCORE_WIDTH, 37, 75);

		// �F�̕ω�
		SetPolygonColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		DrawNumber(&g_vPosGameClearlastTime4,
			(unsigned)g_nScoreArra[3], SCORE_WIDTH, 37, 75);
	}

	if (g_nScoreArra[4] == g_nScoreGameClear)
	{
		// �F�̕ω�
		SetPolygonColor(0.0f, 1.0f, 0.0f);

		DrawNumber(&g_vPosGameClearlastTime5,
			(unsigned)g_nScoreArra[4], SCORE_WIDTH, 37, 75);

		// �F�̕ω�
		SetPolygonColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		DrawNumber(&g_vPosGameClearlastTime5,
			(unsigned)g_nScoreArra[4], SCORE_WIDTH, 37, 75);
	}

}
