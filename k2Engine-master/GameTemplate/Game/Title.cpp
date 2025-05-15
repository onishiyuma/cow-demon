#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Fade.h"
#include "DebugScene.h"


bool Title::Start()
{
	//タイトルの画像を読み込む。
	m_spriteRender.Init("Assets/sprite/cowDemonTitle.DDS", 1920.0f, 1080.0f);
	
	//文字の表示。
	m_fontRender.SetText(L"Please Press AnyKey");
	m_fontRender.SetPosition({ -250.0f,-300.0f,0.0f });
	m_fontRender.SetColor(g_vec4White);

	return true;
}

Title::Title()
{

}

Title::~Title()
{
	
}

void Title::Update()
{
	m_timer+= g_gameTime->GetFrameDeltaTime();

	//タイトルからインゲームへ移行。
	if (m_timer>0.1f&&g_pad[0]->IsPressAnyKey())
	{
		NewGO<Fade>(1, "fade");
		m_spriteRender.Update();
		//自身を削除する。
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}