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
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/Zero.DDS", 192, 108);
	//初期座標を設定する。
	m_spriteRender.SetPosition(m_firstPosition);
	//大きさを設定する。
	m_spriteRender.SetScale(m_scaleEnd);
	//乗算カラーを設定する。
	m_spriteRender.SetMulColor(m_color);

	return true;
}

void UIZero::Update()
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

	if (m_timer >= m_maxTime && !m_isMove)
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

void UIZero::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
