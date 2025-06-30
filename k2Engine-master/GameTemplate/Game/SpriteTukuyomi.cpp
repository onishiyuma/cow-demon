#include "stdafx.h"
#include "SpriteTukuyomi.h"

SpriteTukuyomi::SpriteTukuyomi()
{

}

SpriteTukuyomi::~SpriteTukuyomi()
{

}

bool SpriteTukuyomi::Start()
{
	m_spriteRender.Init("Assets/sprite/TutorialTukuyomi.DDS", 1920, 1080);

	m_spriteRender.SetPosition(m_position);

	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f });

	return true;
}

void SpriteTukuyomi::Update()
{
	m_spriteRender.Update();
	m_spriteRender.SetPosition(m_position);
	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f });

	if (g_pad[0]->IsTrigger(enButtonA)) {
		DeleteGO(this);
	}
}

void SpriteTukuyomi::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
