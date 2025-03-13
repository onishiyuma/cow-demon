#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"


bool Game::Start()
{
	//プレイヤーオブジェクトの作成
	m_player = NewGO<Player>(0,"player");
	//カメラオブジェクトの作成
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");

	return true;
}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{
	
}