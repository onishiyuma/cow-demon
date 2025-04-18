#include "stdafx.h"
#include "UIStone.h"
#include "Stone.h"
#include "Player.h"


bool UIStone::Start() 
{
	m_player = FindGO<Player>("player");

	return true;
}

UIStone::UIStone() 
{

}

UIStone::~UIStone() 
{
	//DeleteGO(this);
}

void UIStone::Update() 
{
	wchar_t wcsbuf2[256];
	swprintf_s(wcsbuf2, 256, L"火打石の数:%d", int(m_player->m_stoneCount));

	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf2);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(200.0f, 500.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(1.5f);
	//フォントの色を設定。
	m_fontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });
}

void UIStone::Render(RenderContext& rc) 
{
	m_fontRender.Draw(rc);
}
