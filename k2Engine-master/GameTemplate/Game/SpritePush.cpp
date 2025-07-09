#include "stdafx.h"
#include "SpritePush.h"

namespace
{
	//座標。
	const Vector3 SPRITE_POSITION = { 300.0f, -150.0f, 0.0f };
}

SpritePush::SpritePush()
{

}

SpritePush::~SpritePush()
{

}

bool SpritePush::Start()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/push.DDS", 600.0f, 400.0f);
	//座標の設定。
	m_spriteRender.SetPosition(SPRITE_POSITION);
	//大きさの設定。
	m_spriteRender.SetScale(m_scale);
	m_spriteRender.Update();

	return true;
}

void SpritePush::Update()
{

}

void SpritePush::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}