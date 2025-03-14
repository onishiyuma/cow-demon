#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Game.h"


bool GameClear::Start()
{
	//ゲームクリアの画像を読み込む
	m_spriteRender.Init("Assets/sirite/TukuyomiMax.dds", 1920.0f, 1080.0f);

	m_game = FindGO<Game>("game");
	
	return true;
}

GameClear::GameClear()
{

}

GameClear::~GameClear()
{
	//DeleteGO(this);
}

void GameClear::Update()
{
	if (g_pad[0]->IsPressAnyKey())
	{
		//ゲーム外にする。
		m_game->enOutGame;
		NewGO<Title>(0, "title");

		//自身を削除。
		//DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	
}