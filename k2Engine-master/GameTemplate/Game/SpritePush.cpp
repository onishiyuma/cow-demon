#include "stdafx.h"
#include "SpritePush.h"

SpritePush::SpritePush()
{

}

SpritePush::~SpritePush()
{

}

bool SpritePush::Start()
{
	m_spriteRender.Init("Assets/sprite/push.DDS", 600.0f, 400.0f); //‰æ‘œ‚ğ“Ç‚İ‚Ş
	m_spriteRender.SetPosition(Vector3(300.0f, -150.0f, 0.0f)); //À•W‚Ìİ’è
	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f }); //‘å‚«‚³‚Ìİ’è
	m_spriteRender.Update();

	return true;
}

void SpritePush::Update()
{
	m_spriteRender.SetPosition(m_position);
}

void SpritePush::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}