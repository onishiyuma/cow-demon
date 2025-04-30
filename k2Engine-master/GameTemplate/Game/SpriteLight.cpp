#include "stdafx.h"
#include "SpriteLight.h"

SpriteLight::SpriteLight() 
{

}

SpriteLight::~SpriteLight()
{

}

bool SpriteLight::Start() 
{
	m_spriteRender.Init("Assets/sprite/lightButton.DDS", 600.0f, 400.0f); //画像を読み込む
	m_spriteRender.SetPosition(Vector3(300.0f, -150.0f, 0.0f)); //座標の設定
	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f }); //大きさの設定
	m_spriteRender.Update();

	return true;
}

void SpriteLight::Move()
{

}

void SpriteLight::Update()
{
	m_spriteRender.SetPosition(m_position);
}

void SpriteLight::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}