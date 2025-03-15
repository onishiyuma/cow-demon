#include "stdafx.h"
#include "GameOver.h"
#include "Game.h"
#include "Title.h"


bool GameOver::Start()
{
	//ゲームオーバーの画像を読み込む。
	m_spriteRender.Init("TukuyomiMax.DDS", 1920.0f, 1080.0f);

	return true;
}

GameOver::GameOver()
{

}

GameOver::~GameOver()
{
	DeleteGO(this);
}

void GameOver::Update()
{
	if (g_pad[0]->IsPressAnyKey())
	{
		//ゲーム外にする。
		m_game->enOutGame;
		NewGO<Title>(0, "title");

		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{

}