#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"


bool Game::Start()
{
	//インゲームでなければ表示しない。
	if (m_gameState != enInGame)
	{
		//プレイヤーオブジェクトの作成
		m_player = NewGO<Player>(0, "player");
		//カメラオブジェクトの作成
		m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
		//ステージオブジェクトの作成
		m_backGround = NewGO<BackGround>(0);
		//空の背景作成
		SkyCube* skyCube = NewGO<SkyCube>(0);
		skyCube->SetType(enSkyCubeType_NightToon);
		skyCube->SetScale(1000.0f);

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