#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Game.h"


bool GameClear::Start()
{
	//ゲームクリアの画像を読み込む。
	m_spriteRender.Init("Assets/sprite/S.DDS", 1920.0f, 1080.0f);
	
	return true;
}

GameClear::GameClear()
{

}

GameClear::~GameClear()
{

}

void GameClear::Update()
{
	//タイトルに戻る処理。
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Title>(0);

		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}