#include "stdafx.h"
#include "CrossHair.h"

bool CrossHair::Start()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/CrossHair.DDS", 120.0f, 120.0f);
	//座標をセット。
	m_spriteRender.SetPosition(m_position);
	//m_spriteRender.SetMulColor(g_vec4Red);

	return true;
}

CrossHair::CrossHair()
{

}

CrossHair::~CrossHair()
{
	DeleteGO(this);
}

void CrossHair::Update()
{

}

void CrossHair::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}