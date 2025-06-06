#include "stdafx.h"
#include "UITwo.h"

UITwo::UITwo()
{

}

UITwo::~UITwo()
{

}

bool UITwo::Start()
{
	m_spriteRender.Init("Assets/sprite/Two.DDS", 192, 108);

	m_spriteRender.SetPosition(m_firstPosition);

	m_spriteRender.SetScale(m_scaleEnd);

	m_spriteRender.SetMulColor(m_color);

	return true;
}

void UITwo::Update()
{
	m_spriteRender.Update();
	m_spriteRender.SetPosition(m_firstPosition);
	m_spriteRender.SetScale(m_scaleEnd);
	m_spriteRender.SetMulColor(m_color);

	m_timer += g_gameTime->GetFrameDeltaTime();

	if (m_timer >= 1.0f) {
		if (!m_isMove) {
			m_isMove = true;
			DeleteGO(this);
		}
	}

}

void UITwo::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
