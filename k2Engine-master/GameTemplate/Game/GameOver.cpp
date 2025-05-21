#include "stdafx.h"
#include "GameOver.h"
#include "Game.h"
#include "Title.h"


bool GameOver::Start()
{
	//ゲームオーバーの画像を読み込む。
	m_spriteRender.Init("Assets/sprite/GameOver.DDS", 1920.0f, 1080.0f);

	return true;
}

GameOver::GameOver()
{

}

GameOver::~GameOver()
{

}

void GameOver::Update()
{
	//タイトルに戻る処理。
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Title>(0);

		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}