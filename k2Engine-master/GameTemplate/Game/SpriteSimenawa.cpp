#include "stdafx.h"
#include "SpriteSimenawa.h"
#include "Tutorial.h"

SpriteSimenawa::SpriteSimenawa()
{

}

SpriteSimenawa::~SpriteSimenawa()
{

}

bool SpriteSimenawa::Start()
{
	m_tutorial = FindGO<Tutorial>("tutorial");

	m_spriteRender.Init("Assets/sprite/TutorialSimenawa.DDS", 1920, 1080);

	m_spriteRender.SetPosition(m_position);

	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f });

	return true;
}

void SpriteSimenawa::Update()
{
	m_spriteRender.Update();
	m_spriteRender.SetPosition(m_position);
	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f });

	if (g_pad[0]->IsTrigger(enButtonA)) {
		DeleteGO(this);
	}
}

void SpriteSimenawa::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
