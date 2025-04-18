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
#include "UISimenawa.h"
#include "UIcurseBar.h"
#include "UIheal.h"
#include "RingBell.h"
#include "GameClear.h"
#include "GameOver.h"


bool Game::Start()
{
	//制限時間の設定。
	m_timeLimit =180.0f;

	//デバック用。
	//m_timeLimit = 3.0f;

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

	//賽銭箱を表示（鈴）。
	m_ringBell = NewGO<RingBell>(0);

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
	

	m_uitukuyomi = NewGO<UItukuyomi>(0,"uitukuyomi");
	//スキルUI
	m_uiskill = NewGO<UIskill>(0, "uiskill");
	//しめ縄UI
	m_uisimenawa = NewGO<UISimenawa>(0, "m_uisimenawa");
	//ミニマップ
	m_miniMap = NewGO<MiniMap>(0,"minimap");
	//呪ゲージ
	m_uicursebar = NewGO<UIcurseBar>(0, "m_uicursebar");
	//回復
	m_uiheal = NewGO <UIheal>(0, "uiheal");
	//��̔w�i�쐬
	m_skyCube=NewGO<SkyCube>(0);
	m_skyCube->SetType(enSkyCubeType_NightToon);
	m_skyCube->SetScale(1000.0f);


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
	DeleteGO(m_ringBell);
	DeleteGO(m_skyCube);

	DeleteGO(m_uitukuyomi);
	DeleteGO(m_uiskill);
	DeleteGO(m_uisimenawa);
	DeleteGO(m_uicursebar);
	DeleteGO(m_uiheal);
	DeleteGO(m_miniMap);
}

void Game::Update()
{
	GameManager();
}


//ゲームクリア、ゲームオーバーの判定処理。
void Game::GameManager()
{
	//タイマーを減らす処理。
	m_timeLimit -= g_gameTime->GetFrameDeltaTime();

	//敵から本殿を守り切ったらゲームクリア。
	if (m_timeLimit <= 0)
	{
		NewGO<GameClear>(0);
		DeleteGO(this);
	}


	//呪いの抵抗値がなくなったら。
	if (m_player->m_playerHP <= 0)
	{
		NewGO<GameOver>(0);
		DeleteGO(this);
	}

}


void Game::Render(RenderContext& rc)
{

}