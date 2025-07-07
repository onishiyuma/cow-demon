#include "stdafx.h"
#include "SpriteClear.h"

namespace 
{
	//フェード開始までの時間。
	const float START_FADE_DELAY = 1.0f;
}

SpriteClear::SpriteClear()
{

}

SpriteClear::~SpriteClear()
{

}

bool SpriteClear::Start()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/TutorialClear.DDS", 1920, 1080);
	//座標を設定。
	m_spriteRender.SetPosition(m_position);
	//大きさを設定。
	m_spriteRender.SetScale(m_scale);
	//色を設定。
	m_spriteRender.SetMulColor(g_vec4White);

	return true;
}

void SpriteClear::Update()
{
	m_spriteRender.SetMulColor(g_vec4White);
	
	//タイマーを加算。
	m_timer += g_gameTime->GetFrameDeltaTime();

	if (m_timer >= START_FADE_DELAY)
	{
		Fade();
	}
}

void SpriteClear::Fade()
{
	//フェードアウトしたら何もしない。
	if (m_isFadeOut) 
	{
		return;
	}

	//フェードアウトの処理。
	m_color.a -= 0.01f * m_fadeTimer / m_fadeMaxTimer;
	m_spriteRender.SetMulColor(m_color);

	if (m_color.a <= 0.0f)
	{
		m_color.a = 0.0f;
		m_isFadeOut = true;
	}
	m_spriteRender.SetMulColor(m_color);
}

void SpriteClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
