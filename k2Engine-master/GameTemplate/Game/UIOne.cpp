#include "stdafx.h"
#include "UIOne.h"

UIOne::UIOne()
{

}

UIOne::~UIOne()
{

}

bool UIOne::Start()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/One.DDS", 192, 108);
	//座標を設定する。
	m_spriteRender.SetPosition(m_firstPosition);
	//大きさを設定する。
	m_spriteRender.SetScale(m_scaleEnd);
	//色を設定する。
	m_spriteRender.SetMulColor(m_color);

	return true;
}

void UIOne::Update()
{
	//画像を更新する。
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
		DeleteGO(this);
	}	

}

void UIOne::Render(RenderContext&rc)
{
	m_spriteRender.Draw(rc);
}
