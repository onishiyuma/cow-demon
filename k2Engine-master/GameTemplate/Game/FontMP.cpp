#include "stdafx.h"
#include "FontMP.h"

FontMP::FontMP()
{

}

FontMP::~FontMP()
{

}

bool FontMP::Start()
{
	//文字を設定。
	m_fontRenderer.SetText(L"MPが足りない");
	//座標を設定。
	m_fontRenderer.SetPosition(m_position);
	//色を設定。
	m_fontRenderer.SetColor(m_color);
	//大きさを設定。
	m_fontRenderer.SetScale(m_scale);

	return true;
}

void FontMP::Update()
{
	m_timer += g_gameTime->GetFrameDeltaTime();

	if (m_timer >= 5.0f) {
		DeleteGO(this);
	}
	m_fontRenderer.SetPosition(m_position);
	m_fontRenderer.SetColor(m_color);
	m_fontRenderer.SetScale(m_scale);
}

void FontMP::Render(RenderContext&rc)
{
	m_fontRenderer.Draw(rc);
}