#include "stdafx.h"
#include "Title.h"
#include "Game.h"


bool Title::Start()
{
	//タイトルの画像を読み込む。
	m_spriteRender.Init("Assets/sprite/Title.DDS", 1920.0f, 1080.0f);
	//ゲーム外にする。
	m_game->enOutGame;

	//文字の表示。
	m_fontRender.SetText(L"Please Press AnyKey");
	m_fontRender.SetPosition({ -250.0f,-300.0f,0.0f });
	m_fontRender.SetColor({ 1.0f,1.0f,1.0f,0.0f });

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

	Font();

	//タイトルからインゲームへ移行。
	if (g_pad[0]->IsPressAnyKey())
	{
		//インゲームにする。
		m_game->enInGame;
		NewGO<Game>(0, "game");
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