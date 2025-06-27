#include "stdafx.h"
#include "SpriteClear.h"

SpriteClear::SpriteClear()
{

}

SpriteClear::~SpriteClear()
{

}

bool SpriteClear::Start()
{
	m_spriteRender.Init("Assets/sprite/TutorialClear.DDS", 1920, 1080);

	m_spriteRender.SetPosition(m_position);

	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f });

	m_spriteRender.SetMulColor(m_color);

	return true;
}

void SpriteClear::Update()
{
	m_spriteRender.SetPosition(m_position);

	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f });

	m_spriteRender.SetMulColor(m_color);
	
	//タイマーを加算。
	m_timer += g_gameTime->GetFrameDeltaTime();

	if (m_timer >= 1.0f) {
		Fade();
	}
}

void SpriteClear::Fade()
{
	if (!m_isFadeOut) {
		//フェードアウトの処理。
		m_color.a -= 0.01f * m_fadeTimer / m_fadeMaxTimer;
		m_spriteRender.SetMulColor(m_color);

		if (m_color.a <= 0.0f)
		{
			m_isFadeOut = true;
			m_color.a = 0.0f;
			m_spriteRender.SetMulColor(m_color);
		}
	}
}

void SpriteClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
