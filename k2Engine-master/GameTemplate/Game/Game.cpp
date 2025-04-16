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
#include "MiniMap.h"
#include "UItukuyomi.h"
#include "UIskill.h";
#include "UISimenawa.h";
#include "UIcurseBar.h";
#include "UIheal.h";


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
		m_stone1 = NewGO<Stone>(0, "stone1");
		m_stone1->m_position = { 1000.0f,0.0f,-500.0f };
		m_stone1->m_firstPosition = m_stone1->m_position;
		//m_stone = FindGO<Stone>("stone");

		m_stone2 = NewGO<Stone>(0, "stone2");
		m_stone2->m_position = { 200.0f,0.0f,-4000.0f };
		m_stone2->m_firstPosition = m_stone2->m_position;
		//m_stone1 = FindGO<Stone>("stone");

		m_stone3 = NewGO<Stone>(0, "stone3");
		m_stone3->m_position = { -1200.0f,0.0f,500.0f };
		m_stone3->m_firstPosition = m_stone3->m_position;

		m_stone4 = NewGO<Stone>(0, "stone4");
		m_stone4->m_position = { 2000.0f,0.0f,-3000.0f };
		m_stone4->m_firstPosition = m_stone4->m_position;

		m_stone5 = NewGO<Stone>(0, "stone5");
		m_stone5->m_position = { -2300.0f,0.0f,-3200.0f };
		m_stone5->m_firstPosition = m_stone5->m_position;

		m_stone6 = NewGO<Stone>(0, "stone6");
		m_stone6->m_position = { 0.0f,0.0f,500.0f };
		m_stone6->m_firstPosition = m_stone6->m_position;

		m_stone7 = NewGO<Stone>(0, "stone7");
		m_stone7->m_position = { 0.0f,0.0f,-500.0f };
		m_stone7->m_firstPosition = m_stone7->m_position;

		//火打石のカウントを表示。
		m_uiStone = NewGO<UIStone>(0, "uiStone");
		m_uiStone = FindGO<UIStone>("uiStone");
		
		//灯籠のモデルを表示
		m_lantern1 = NewGO<Lantern>(0, "lantern1");
		m_lantern1->m_position = { 500.0f,-50.0f,500.0f };
		m_lantern1->m_firstPosition = m_lantern1->m_position;
		//m_lantern1 = FindGO<Lantern>("lantern1");

		m_lantern2 = NewGO<Lantern>(0, "lantern2");
		m_lantern2->m_position = { 500.0f,-50.0f,-500.0f };
		m_lantern2->m_firstPosition = m_lantern2->m_position;
		//m_lantern2 = FindGO<Lantern>("lantern2");

		m_lantern3 = NewGO<Lantern>(0, "lantern3");
		m_lantern3->m_position = { -500.0f,-50.0f,500.0f };
		m_lantern3->m_firstPosition = m_lantern3->m_position;
		//m_lantern3= FindGO<Lantern>("lantern3");

		m_lantern4 = NewGO<Lantern>(0, "lantern4");
		m_lantern4->m_position = { -500.0f,-50.0f,-500.0f };
		m_lantern4->m_firstPosition = m_lantern4->m_position;
		//m_lantern4 = FindGO<Lantern>("lantern4");

		//攻撃用灯籠のモデルを表示
		m_lanternAttack1 = NewGO<LanternAttack>(0, "lanternAttack1");
		m_lanternAttack1->m_position = { 700.0f,-50.0f,2000.0f };
		m_lanternAttack1->m_firstPosition = m_lanternAttack1->m_position;
		//m_lantern1 = FindGO<Lantern>("lantern1");

		m_lanternAttack2 = NewGO<LanternAttack>(0, "lanternAttack2");
		m_lanternAttack2->m_position = { -700.0f,-50.0f,2000.0f };
		m_lanternAttack2->m_firstPosition = m_lanternAttack2->m_position;
		//m_lantern2 = FindGO<Lantern>("lantern2");

		m_lanternAttack3 = NewGO<LanternAttack>(0, "lanternAttack3");
		m_lanternAttack3->m_position = { 100.0f,-50.0f,1600.0f };
		m_lanternAttack3->m_firstPosition = m_lanternAttack3->m_position;
		//m_lantern3= FindGO<Lantern>("lantern3");
		
		//�X�e�[�W�I�u�W�F�N�g�̍쐬
		m_backGround = NewGO<BackGround>(0);
		
		m_uitukuyomi = NewGO<UItukuyomi>(0,"uitukuyomi");
		//スキルUI
		m_uiskill = NewGO<UIskill>(0, "uiskill");
		//しめ縄UI
		m_uisimenaw = NewGO<UISimenaw>(0, "m_uisimenawa");
		//ミニマップ
		m_miniMap = NewGO<MiniMap>(0,"minimap");
		//呪ゲージ
		m_uicursebar = NewGO<UIcurseBar>(0, "m_uicursebar");
		//回復
		m_uiheal = NewGO <UIheal>(0, "uiheal");
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
	DeleteGO(m_stone1);
	DeleteGO(m_stone2);
	DeleteGO(m_stone3);
	DeleteGO(m_stone4);
	DeleteGO(m_stone5);
	DeleteGO(m_stone6);
	DeleteGO(m_stone7);
	DeleteGO(m_lantern1);
	DeleteGO(m_lantern2);
	DeleteGO(m_lantern3);
	DeleteGO(m_lantern4);
	DeleteGO(m_lanternAttack1);
	DeleteGO(m_lanternAttack2);
	DeleteGO(m_lanternAttack3);
	DeleteGO(m_uitukuyomi);
	DeleteGO(m_uiskill);
	DeleteGO(m_uisimenaw);
	DeleteGO(m_uicursebar);
	DeleteGO(m_uiheal);
	DeleteGO(m_miniMap);
}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{

}