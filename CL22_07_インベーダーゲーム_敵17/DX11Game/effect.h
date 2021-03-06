//=============================================================================
//
// 各種エフェクト処理 [effect.h]
// Author : 前地智貴
//
//=============================================================================
#pragma once

#include "main.h"



//*****************************************************************************
// 定数定義
//*****************************************************************************
enum EEffectType {
	EEFECT_DEAD000 = 0,	// 敵消滅

	MAX_EFFECTTYPE
};



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect();
void UninitEffect();
void UpdateEffect();
void DrawEffect();
int StartEffect(XMFLOAT2* pPos, int nType);
