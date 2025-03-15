#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"


bool Game::Start()
{
	//インゲームでなければ表示しない。
	if (m_gameState != enInGame)
	{
		//プレイヤーオブジェクトの作成
		m_player = NewGO<Player>(0, "player");
		//カメラオブジェクトの作成
		m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	}

	return true;
}

Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{
	
}