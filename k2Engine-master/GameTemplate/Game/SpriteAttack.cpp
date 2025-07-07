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
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/TutorialNomalAttack.DDS",1920,1080);
	//座標を設定。
	m_spriteRender.SetPosition(m_position);
	//大きさを設定。
	m_spriteRender.SetScale(m_scale);
	m_spriteRender.Update();

	return true;
}

void SpriteAttack::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA)) 
	{
		DeleteGO(this);
	}
}

void SpriteAttack::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
