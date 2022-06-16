//=============================================================================
//
// �^�C�g����ʏ��� [gameclear.cpp]
// Author : �O�n�q�M
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
// �}�N����`
//*****************************************************************************
#define GAMECLEAR_TEXTURENAME	L"data/texture/GameClear_02.png"	// �e�N�X�`���t�@�C����

#define GAMECLEAR_POS_X		0								// �|���S���̕\���ʒu
#define GAMECLEAR_POS_Y		0								// �|���S���̕\���ʒu
#define GAMECLEAR_SIZE_X		SCREEN_WIDTH					// �|���S���̃T�C�Y
#define GAMECLEAR_SIZE_Y		SCREEN_HEIGHT					// �|���S���̃T�C�Y
#define GAMECLEAR_TIMER		(60+30)



//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// �e�N�X�`��
static int g_nTimer;



//=============================================================================
// �w�i�\���̏���������
//=============================================================================
HRESULT InitgameClear()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		GAMECLEAR_TEXTURENAME, &g_pTexture);

	g_nTimer = GAMECLEAR_TIMER;

	return hr;
}



//=============================================================================
// �w�i�\���̏I������
//=============================================================================
void UninitgameClear()
{
	// �e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}



//=============================================================================
// �w�i�\���̍X�V����
//=============================================================================
void UpdategameClear()
{
	// �X�y�[�X�L�[����������Q�[���J�n
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
// �w�i�\������
//=============================================================================
void DrawgameClear()
{
	// �w�i�`��
	SetPolygonPos(GAMECLEAR_POS_X, GAMECLEAR_POS_Y);
	SetPolygonSize(GAMECLEAR_SIZE_X, GAMECLEAR_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());
}
