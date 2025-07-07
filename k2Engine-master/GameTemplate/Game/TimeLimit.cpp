#include "stdafx.h"
#include "TimeLimit.h"
#include "Game.h"

namespace
{
	//フォントの大きさ。
	const float FONT_SCALE = 1.5f;
	//タイマーの最大時間。
	const float MAX_TIMER = 6.0f;
}

TimeLimit::TimeLimit()
{

}

TimeLimit::~TimeLimit()
{

}

bool TimeLimit::Start() 
{
	//文字を設定する。
	m_fontRender.SetText(L"夜明けまであと1時間だ");
	//座標を設定する。
	m_fontRender.SetPosition(m_position);
	//色を設定する。
	m_fontRender.SetColor(m_color);
	//大きさを設定する。
	m_fontRender.SetScale(FONT_SCALE);

	return true;
}

void TimeLimit::Update()
{
	m_fontRender.SetPosition(m_position);

	m_fontRender.SetScale(FONT_SCALE);

	Flash();

	m_timerCount += g_gameTime->GetFrameDeltaTime();

	if (m_timerCount >= MAX_TIMER)
	{
		DeleteGO(this);
	}
}

void TimeLimit::Flash()
{
	if (!m_isflash) {

		m_color.r += 0.01f * m_timer / m_maxTimer;
		m_color.a += 0.01f * m_timer / m_maxTimer;
		m_fontRender.SetColor(m_color);

		if (m_color.a >= 1.0f) {
			m_color.r = 1.0f;
			m_color.a = 1.0f;
			m_isflash = true;
			m_fontRender.SetColor(m_color);
		}
	}
	else {

		m_color.r -= 0.01f * m_timer / m_maxTimer;
		m_color.a -= 0.01f * m_timer / m_maxTimer;
		m_fontRender.SetColor(m_color);

		if (m_color.a <= 0.0f) {
			m_color.r = 0.0f;
			m_color.a = 0.0f;
			m_isflash = false;
			m_fontRender.SetColor(m_color);
		}
	}

}

void TimeLimit::Render(RenderContext&rc)
{
	m_fontRender.Draw(rc);
}