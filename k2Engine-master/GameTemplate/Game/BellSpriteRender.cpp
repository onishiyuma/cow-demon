#include "stdafx.h"
#include "BellSpriteRender.h"

namespace
{
	Vector3 SPRITE_POSITION = { 300.0f, -150.0f, 0.0f };
	Vector3 SPRITE_SCALE = { 1.0f,1.0f,1.0f };
}

bool BellSpriteRender::Start()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/bell.DDS", 600.0f, 400.0f);
	//座標の設定。
	m_spriteRender.SetPosition(SPRITE_POSITION); 
	//大きさの設定。
	m_spriteRender.SetScale(SPRITE_SCALE);
	m_spriteRender.Update();

	return true;

}

BellSpriteRender::BellSpriteRender()
{

}

BellSpriteRender::~BellSpriteRender()
{

}

void BellSpriteRender::Update()
{
	//現在の座標をセット。
	m_spriteRender.SetPosition(m_position);
}

void BellSpriteRender::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
