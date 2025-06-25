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

	m_fontRenderer.SetText(L"MPが足りない");
	m_fontRenderer.SetPosition(m_position);
	m_fontRenderer.SetColor(m_color);
	m_fontRenderer.SetScale(1.0f);


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
	m_fontRenderer.SetScale(1.0f);
}

void FontMP::Render(RenderContext&rc)
{
	m_fontRenderer.Draw(rc);
}