#include "stdafx.h"
#include "SpriteAttack.h"

SpriteAttack::SpriteAttack()
{

}

SpriteAttack::~SpriteAttack()
{

}

bool SpriteAttack::Start()
{
	m_spriteRender.Init("Assets/sprite/TutorialNomalAttack.DDS",1920,1080);

	m_spriteRender.SetPosition(m_position);

	m_spriteRender.SetScale({0.7f,0.7f,0.7f});

	return true;
}

void SpriteAttack::Update()
{
	m_spriteRender.Update();
	m_spriteRender.SetPosition(m_position);
	m_spriteRender.SetScale({ 0.7f,0.7f,0.7f });

	if (g_pad[0]->IsTrigger(enButtonA)) {
		DeleteGO(this);
	}
}

void SpriteAttack::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
