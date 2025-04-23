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
#include "UIskill.h"
#include "UISimenawa.h"
#include "UIcurseBar.h"
#include "UIheal.h"
#include "RingBell.h"
#include "GameClear.h"
#include "GameOver.h"


bool Game::Start()
{

	//ステージ全体を暗くする。
	g_sceneLight->SetAmbient(Vector3(0.0001f, 0.0001f, 0.0001f));

	g_sceneLight->SetDirectionLight(0, Vector3(0.01f, 0.01f, 0.01f), Vector3(1.0f, 1.0f, 1.0f));



	//制限時間の設定。
	m_timeLimit =120.0f;


	//背景の作成。
	m_backGround = NewGO<BackGround>(0);

	//ベルの作成。
	m_ringBell = NewGO<RingBell>(0, "ringbell");

	//プレイヤーの作成。
	m_player = NewGO<Player>(0, "player");

	//ゲームカメラの作成。
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	
	//エネミーの作成。
	m_enemy = NewGO<Enemy>(0,"enemy");

	//クロスヘアーを表示。
	m_crossHair = NewGO<CrossHair>(0);
	
	//火打石の作成。
	CreateStone();

	//灯籠の作成。
	CreateLantern();

	//攻撃用灯籠の作成。
	CreateAttackLantern();

	//火打石のカウントを表示。
	m_uiStone = NewGO<UIStone>(0, "uiStone");

	//UIの作成
	CreateUI();
	
	return true;
}

Game::Game()
{
	
}

Game::~Game()
{
	//オブジェクトなど。
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_enemy);
	DeleteGO(m_backGround);
	DeleteGO(m_crossHair);
	DeleteGO(m_ringBell);


	//火打石。
	DeleteGO(m_stone1);
	DeleteGO(m_stone2);
	DeleteGO(m_stone3);
	DeleteGO(m_stone4);
	DeleteGO(m_stone5);
	DeleteGO(m_stone6);
	DeleteGO(m_stone7);


	//灯籠。
	DeleteGO(m_lantern1);
	DeleteGO(m_lantern2);
	DeleteGO(m_lantern3);
	DeleteGO(m_lantern4);


	//攻撃用ランタン。
	DeleteGO(m_lanternAttack1);
	DeleteGO(m_lanternAttack2);
	DeleteGO(m_lanternAttack3);


	//UI関連。
	DeleteGO(m_uiTukuyomi);
	DeleteGO(m_uiSkill);
	DeleteGO(m_uiSimenawa);
	DeleteGO(m_uiCurseBar);
	DeleteGO(m_uiHeal);
	DeleteGO(m_uiStone);
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

//火打石作成用関数。
void Game::CreateStone()
{
	// 火打石を表示。
	m_stone1 = NewGO<Stone>(0, "stone1");
	m_stone1->m_position = { 1000.0f,0.0f,-500.0f };
	m_stone1->m_firstPosition = m_stone1->m_position;
	//m_stone = FindGO<Stone>("stone");

	m_stone2 = NewGO<Stone>(0, "stone2");
	m_stone2->m_position = { 200.0f,0.0f,-2000.0f };
	m_stone2->m_firstPosition = m_stone2->m_position;
	//m_stone1 = FindGO<Stone>("stone");

	m_stone3 = NewGO<Stone>(0, "stone3");
	m_stone3->m_position = { -1200.0f,0.0f,500.0f };
	m_stone3->m_firstPosition = m_stone3->m_position;

	m_stone4 = NewGO<Stone>(0, "stone4");
	m_stone4->m_position = { 2000.0f,0.0f,-2000.0f };
	m_stone4->m_firstPosition = m_stone4->m_position;

	m_stone5 = NewGO<Stone>(0, "stone5");
	m_stone5->m_position = { -2300.0f,0.0f,-2200.0f };
	m_stone5->m_firstPosition = m_stone5->m_position;

	m_stone6 = NewGO<Stone>(0, "stone6");
	m_stone6->m_position = { 0.0f,0.0f,500.0f };
	m_stone6->m_firstPosition = m_stone6->m_position;

	m_stone7 = NewGO<Stone>(0, "stone7");
	m_stone7->m_position = { 0.0f,0.0f,-500.0f };
	m_stone7->m_firstPosition = m_stone7->m_position;
}

//灯籠作成用関数。
void Game::CreateLantern()
{
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
}

//攻撃灯籠の作成用関数
void Game::CreateAttackLantern()
{
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
}

//UI作成用関数。
void Game::CreateUI()
{
	//月読の加護のUI
	m_uiTukuyomi = NewGO<UItukuyomi>(0, "uitukuyomi");
	//スキルUI
	m_uiSkill = NewGO<UIskill>(0, "uiskill");
	//しめ縄UI
	m_uiSimenawa = NewGO<UISimenawa>(0, "uisimenawa");
	//ミニマップ
	m_miniMap = NewGO<MiniMap>(0, "minimap");
	//呪ゲージ
	m_uiCurseBar = NewGO<UIcurseBar>(0, "uicursebar");
	//回復
	m_uiHeal = NewGO <UIheal>(0, "uiheal");
}


void Game::Render(RenderContext& rc)
{

}