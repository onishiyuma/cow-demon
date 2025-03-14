#include "stdafx.h"
#include "Title.h"
#include "Game.h"

bool Title::Start()
{
	m_spriteRender.Init("Assets/sirite/TukuyomiMax.dds",1920.0f,1080.0f);
	
	return true;
}

Title::Title()
{

}

Title::~Title()
{
	DeleteGO(this);
}

void Title::Update()
{
	//タイトルからインゲームへ移行
	if (g_pad[0]->IsPressAnyKey())
	{
		NewGO<Game>(0, "game");
		m_spriteRender.Update();
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}