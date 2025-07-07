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
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/TutorialTukuyomi.DDS", 1920, 1080);
	//座標を設定。
	m_spriteRender.SetPosition(m_position);
	//大きさを設定。
	m_spriteRender.SetScale(m_scale);

	return true;
}

void SpriteTukuyomi::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA)) 
	{
		DeleteGO(this);
	}
}

void SpriteTukuyomi::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
