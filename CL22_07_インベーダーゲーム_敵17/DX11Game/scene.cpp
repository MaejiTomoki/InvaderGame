//=============================================================================
//
// �V�[���J�ڏ��� [scene.cpp]
// Author : �O�n�q�M
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
// �O���[�o���ϐ�
//*****************************************************************************
static int 	g_nScene = SCENE_NOTE;				// ���݂̃V�[��



//=============================================================================
// �V�[���̏���������
//=============================================================================
HRESULT InitScene()
{
	SetScene(SCENE_START);//SCENE_TITLE);			// �ŏ��̓^�C�g�����
	return S_OK;
}



//=============================================================================
// �V�[���̏I������
//=============================================================================
void UninitScene()
{
	SetScene(SCENE_NOTE);			// ���݂̃V�[�����I��
}



//=============================================================================
// �V�[���̍X�V����
//=============================================================================
void UpdateScene()
{
	switch (g_nScene) 
	{
	case SCENE_START:		// �X�^�[�g���
		UpdateSceneStart();
		break;

	case SCENE_TITLE:		// �^�C�g�����
		UpdateTitle();
		break;

	case SCENE_GAME:		// �Q�[�����
		UpdateGame();
		break;

	case SCENE_GAMEOVER:		// �Q�[���I�[�o�[���
		Updategameover();
		break;

	case SCENE_GAMECLEAR:		// �Q�[���N���A���
		UpdategameClear();
		break;

	case SCENR_RANKING:			// �����L���O
		UpdategameRanking();	
		break;
	}
}



//=============================================================================
// �V�[���`�揈��
//=============================================================================
void DrawScene()
{
	switch (g_nScene)
	{
	case SCENE_START:		// �X�^�[�g���
		DrawSceneStart();
		break;

	case SCENE_TITLE:		// �^�C�g�����
		DrawTitle();
		break;

	case SCENE_GAME:		// �Q�[�����
		DrawGame();
		break;

	case SCENE_GAMEOVER:		// �Q�[���I�[�o�[���
		Drawgameover();
		break;

	case SCENE_GAMECLEAR:		// �Q�[���N���A���
		DrawgameClear();
		break;

	case SCENR_RANKING:			// �����L���O
		DrawgameRanking();
		break;
	}
}



//=============================================================================
// �V�[���؂�ւ�����
//=============================================================================
void SetScene(int nScene)
{
	// ���݂̃V�[�����I��
	switch (nScene)
	{
	case SCENE_START:		// �X�^�[�g���
		UninitSceneStart();
		break;

	case SCENE_TITLE:	// �^�C�g�����
		UninitSceneStart();
		UninitgameRanking();
		UninitSceneStart();
		UninitTitle();
		break;

	case SCENE_GAME:	// �Q�[�����
		UninitTitle();
		UninitGame();
		break;

	case SCENE_GAMEOVER:	// �Q�[���I�[�o�[���
		UninitGame();
		Uninitgameover();
		break;

	case SCENE_GAMECLEAR:		// �Q�[���N���A���
		UninitGame();
		UninitgameClear();
		break;

	case SCENR_RANKING:			// �����L���O
		UninitgameClear();
		Uninitgameover();
		UninitgameRanking();
		break;
	}
	g_nScene = nScene;
	// ���̃V�[����������
	switch (nScene)
	{
	case SCENE_START:		// �X�^�[�g���
		InitSceneStart();
		break;

	case SCENE_TITLE:	// �^�C�g�����
		// ������
		InitTitle();
			break;

	case SCENE_GAME:	// �Q�[�����
		// ������
		InitGame();
			break;

	case SCENE_GAMEOVER:	// �Q�[�����
		// ������
		Initgameover();
		break;

	case SCENE_GAMECLEAR:		// �Q�[���N���A���
		// ������
		InitgameClear();
		break;

	case SCENR_RANKING:			// �����L���O
		// ������
		InitgameRanking();
		break;
	}
}
