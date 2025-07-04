#include "stdafx.h"
#include "UIStone.h"
#include "Stone.h"
#include "Player.h"

namespace
{
	const Vector3 FONT_POS(500.0f, 430.0f, 0.0f);
	const float FONT_SCALE = 1.0f;
}

bool UIStone::Start() 
{
	//インスタンスアドレスを検索。
	m_player = FindGO<Player>("player");

	return true;
}

UIStone::UIStone() 
{

}

UIStone::~UIStone() 
{

}

void UIStone::Update() 
{
	//火打石の数を表示。
	wchar_t wcsbuf2[256];
	swprintf_s(wcsbuf2, 256, L"火打石:%dコ", int(m_player->m_stoneCount));

	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf2);
	//フォントの位置を設定。
	m_fontRender.SetPosition(FONT_POS);
	//フォントの大きさを設定。
	m_fontRender.SetScale(FONT_SCALE);
	//フォントの色を設定。
	m_fontRender.SetColor(g_vec4White);
}

void UIStone::Render(RenderContext& rc) 
{
	m_fontRender.Draw(rc);
}
