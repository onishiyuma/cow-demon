#include "stdafx.h"
#include "SpriteSimenawa.h"

SpriteSimenawa::SpriteSimenawa()
{

}

SpriteSimenawa::~SpriteSimenawa()
{

}

bool SpriteSimenawa::Start()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/TutorialSimenawa.DDS", 1920, 1080);
	//座標を設定する。
	m_spriteRender.SetPosition(m_position);
	//大きさを設定する。
	m_spriteRender.SetScale(m_scale);

	return true;
}

void SpriteSimenawa::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA)) 
	{
		DeleteGO(this);
	}
}

void SpriteSimenawa::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
