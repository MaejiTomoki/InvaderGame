//=============================================================================
//
// フレア エフェクト処理 [flare.h]
// Author : 前地智貴
//
//=============================================================================
#pragma once
#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFlare(void);
void UninitFlare(void);
void UpdateFlare(void);
void DrawFlare(void);

int StartFlare(XMFLOAT2* pPos);
