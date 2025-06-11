#include "stdafx.h"
#include "UIZero.h"

UIZero::UIZero()
{

}

UIZero::~UIZero()
{

}

bool UIZero::Start()
{

	m_spriteRender.Init("Assets/sprite/Zero.DDS", 192, 108);

	m_spriteRender.SetPosition(m_firstPosition);

	m_spriteRender.SetScale(m_scaleEnd);

	m_spriteRender.SetMulColor(m_color);

	return true;
}

void UIZero::Update()
{
	m_spriteRender.Update();
	m_spriteRender.SetPosition(m_firstPosition);
	m_spriteRender.SetScale(m_scaleEnd);
	m_spriteRender.SetMulColor(m_color);

	m_timer += g_gameTime->GetFrameDeltaTime();

	if (m_timer >= 1.0f) {
		if (!m_isMove)
		{
			//フォントのフェードアウトの処理。
			m_color.r -= 0.01f * m_timer / m_maxTime;
			m_color.g -= 0.01f * m_timer / m_maxTime;
			m_color.b -= 0.01f * m_timer / m_maxTime;
			m_color.a -= 0.01f * m_timer / m_maxTime;
			m_spriteRender.SetMulColor(m_color);
			if (m_color.a <= 0.0f)
			{
				m_isMove = true;
				m_color.r = 0.0f;
				m_color.g = 0.0f;
				m_color.b = 0.0f;
				m_color.a = 0.0f;
				m_spriteRender.SetMulColor(m_color);
				DeleteGO(this);
			}
		}
	}
	
}

void UIZero::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
