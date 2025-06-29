#include "stdafx.h"
#include "TimeLimit.h"
#include "Game.h"

TimeLimit::TimeLimit()
{

}

TimeLimit::~TimeLimit()
{

}

bool TimeLimit::Start() 
{
	m_fontRender.SetText(L"夜明けまであと1時間だ");

	m_fontRender.SetPosition(m_position);

	m_fontRender.SetColor(m_color);

	m_fontRender.SetScale(1.5f);

	return true;
}

void TimeLimit::Update()
{
	m_fontRender.SetPosition(m_position);

	m_fontRender.SetScale(1.5f);

	Flash();

	m_timerCount += g_gameTime->GetFrameDeltaTime();

	if (m_timerCount >= 6.0f) {
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