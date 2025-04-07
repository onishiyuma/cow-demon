#include "stdafx.h"
#include "Game.h"
#include "Enemy.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "CrossHair.h"


bool Game::Start()
{
	//�C���Q�[���łȂ���Ε\�����Ȃ��B
	if (m_gameState != enInGame)
	{
		//�X�e�[�W�I�u�W�F�N�g�̍쐬
		m_backGround = NewGO<BackGround>(0);
		//�v���C���[�I�u�W�F�N�g�̍쐬
		m_player = NewGO<Player>(0, "player");
		//�J�����I�u�W�F�N�g�̍쐬
		m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
		//�G�l�~�[�I�u�W�F�N�g�̍쐬
		m_enemy = NewGO<Enemy>(0,"enemy");
		//クロスヘアーを表示。
		m_crossHair = NewGO<CrossHair>(0);
		//しめ縄を表示。
		//m_shimenawa = NewGO<Shimenawa>(0);
		//��̔w�i�쐬
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
	DeleteGO(m_enemy);
	DeleteGO(m_backGround);
	DeleteGO(m_crossHair);
}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{

}