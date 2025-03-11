#include "stdafx.h"
#include "Game.h"
#include "Player.h"


bool Game::Start()
{
	//プレイヤーオブジェクトの作成
	m_player = NewGO<Player>(0,"player");
	return true;
}

void Game::Update()
{
	// g_renderingEngine->DisableRaytracing();
	m_modelRender.Update();
}

void Game::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}