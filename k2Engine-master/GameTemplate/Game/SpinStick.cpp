#include "stdafx.h"
#include "SpinStick.h"


bool SpinStick::Start()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/spinStick.DDS", 600.0f, 400.0f);
	//座標の設定。
	m_spriteRender.SetPosition(m_position);
	//大きさの設定。
	m_spriteRender.SetScale(m_scale);
	m_spriteRender.Update();

	return true;
}

SpinStick::SpinStick()
{

}

SpinStick::~SpinStick()
{

}

void SpinStick::Update()
{

}

void SpinStick::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
