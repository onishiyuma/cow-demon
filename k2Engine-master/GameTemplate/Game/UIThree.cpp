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
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/Three.DDS", 192, 108);
	//座標を設定する。
	m_spriteRender.SetPosition(m_firstPosition);
	//大きさを設定する。
	m_spriteRender.SetScale(m_scaleEnd);
	//色を設定する。
	m_spriteRender.SetMulColor(m_color);

	return true;
}

void UIThree::Update()
{
	//画像の更新。
	m_spriteRender.Update();
	//座標を設定する。
	m_spriteRender.SetPosition(m_firstPosition);
	//大きさを設定する。
	m_spriteRender.SetScale(m_scaleEnd);
	//色を設定する。
	m_spriteRender.SetMulColor(m_color);

	m_timer += g_gameTime->GetFrameDeltaTime();

	if (m_timer >= 1.0f && !m_isMove)
	{
		m_isMove = true;
	}

}

void UIThree::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}