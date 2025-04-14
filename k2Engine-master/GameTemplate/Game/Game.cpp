#include "stdafx.h"
#include "Game.h"
#include "Enemy.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "CrossHair.h"
#include "Stone.h"
#include "UIStone.h"
#include "Lantern.h"
#include "LanternAttack.h"
#include "DebugScene.h"


bool Game::Start()
{
	//�C���Q�[���łȂ���Ε\�����Ȃ��B
	if (m_gameState != enInGame)
	{

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
		// 火打石を表示。
		m_stone = NewGO<Stone>(0, "stone");
		m_stone->m_position = { 0.0f,0.0f,500.0f };
		m_stone->m_firstPosition = m_stone->m_position;
		m_stone = FindGO<Stone>("stone");

		m_stone1 = NewGO<Stone>(0, "stone");
		m_stone1->m_position = { 200.0f,0.0f,0.0f };
		m_stone1->m_firstPosition = m_stone->m_position;
		m_stone1 = FindGO<Stone>("stone");

		//火打石のカウントを表示。
		m_uiStone = NewGO<UIStone>(0, "uiStone");
		m_uiStone = FindGO<UIStone>("uiStone");
		
		
		
		//�X�e�[�W�I�u�W�F�N�g�̍쐬
		m_backGround = NewGO<BackGround>(0);
		
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
	DeleteGO(m_stone);
}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{

}