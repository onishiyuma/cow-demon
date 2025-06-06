#include "stdafx.h"
#include "UIThree.h"

UIThree::UIThree()
{

}

UIThree::~UIThree()
{

}

bool UIThree::Start()
{
	m_spriteRender.Init("Assets/sprite/Three.DDS", 192, 108);

	m_spriteRender.SetPosition(m_firstPosition);

	m_spriteRender.SetScale(m_scaleEnd);

	m_spriteRender.SetMulColor(m_color);

	return true;
}

void UIThree::Update()
{
	m_spriteRender.Update();
	m_spriteRender.SetPosition(m_firstPosition);
	m_spriteRender.SetScale(m_scaleEnd);
	m_spriteRender.SetMulColor(m_color);

	m_timer += g_gameTime->GetFrameDeltaTime();

	if (m_timer >= 1.0f) {
		if (!m_isMove) {
			m_isMove = true;
			//DeleteGO(this);
		}
	}

}

void UIThree::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}