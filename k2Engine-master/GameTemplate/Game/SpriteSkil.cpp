#include "stdafx.h"
#include "SpriteSkil.h"

SpriteSkil::SpriteSkil()
{

}

SpriteSkil::~SpriteSkil()
{

}

bool SpriteSkil::Start()
{
	m_spriteRender.Init("Assets/sprite/TutorialSkil.DDS", 1920, 1080);

	m_spriteRender.SetPosition(m_position);

	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f });

	return true;
}

void SpriteSkil::Update()
{
	m_spriteRender.Update();
	m_spriteRender.SetPosition(m_position);
	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f });

	if (g_pad[0]->IsTrigger(enButtonA)) {
		DeleteGO(this);
	}
}

void SpriteSkil::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
