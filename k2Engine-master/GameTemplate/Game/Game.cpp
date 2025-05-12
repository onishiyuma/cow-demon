#include "stdafx.h"
#include "Game.h"
#include "Enemy.h"
#include "LittleEnemy.h"
#include "BossEnemy.h"
#include "AnnoyingEnemy.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "RingBell.h"
#include "CrossHair.h"
#include "Stone.h"
#include "Lantern.h"
#include "LanternAttack.h"
#include "MiniMap.h"
#include "UIStone.h"
#include "UItukuyomi.h"
#include "UIskill.h"
#include "UISimenawa.h"
#include "UIcurseBar.h"
#include "UIheal.h"
#include "GameClear.h"
#include "GameOver.h"
#include "random"
#include "Fade.h"

bool Game::Start()
{
	//インスタンスアドレスを検索。
	m_fade = FindGO<Fade>("fade");

	//ステージ全体を暗くする。
	g_sceneLight->SetAmbient(Vector3(0.0001f, 0.0001f, 0.0001f));

	g_sceneLight->SetDirectionLight(0, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));


	//オブジェクトの作成。
	CreateObject();

	//火打石の作成。
	CreateStone();

	//灯籠の作成。
	CreateLantern();

	//攻撃用灯籠の作成。
	CreateAttackLantern();

	/*if (m_fade->m_loadingProgress >= 2.0f)
	{
		//UIの作成。
		CreateUI();
		//Enemyの作成。
		CreateEnemy();
	}*/

	//UIの作成。
	CreateUI();
	//Enemyの作成。
	CreateEnemy();
	return true;
}

Game::Game()
{

}

Game::~Game()
{
	//牛鬼。
	for (auto* enemy : m_enemyList)
	{
		DeleteGO(enemy);
	}

	//ミニ牛鬼。
	for (auto* littleEnemy : m_littleEnemyList) 
	{
		DeleteGO(littleEnemy);
	}

	//ボス牛鬼。
	for (auto* bossEnemy : m_bossEnemyList)
	{
		DeleteGO(bossEnemy);
	}

	//ウザイ敵。
	for (auto* annoyingEnemy : m_annoyingEnemyList)
	{
		DeleteGO(annoyingEnemy);
	}

	DeleteGO(m_player);//プレイヤー。
	DeleteGO(m_gameCamera);//ゲームカメラ。
	DeleteGO(m_backGround);//ステージ。
	DeleteGO(m_crossHair);//クロスヘアー。
	DeleteGO(m_ringBell);//ベル。

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

	//攻撃用灯籠。
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
	//DeleteGO(m_miniMap);
}

void Game::Update()
{	
	//タイマーを表示する用関数。
	UITimer();
	//ゲームーオーバーやゲームクリアーを呼び出す関数。
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

//本殿の方向を見させる関数。
void Game::LookingMain()
{



}

//オブジェクト作成用関数。
void Game::CreateObject()
{
	//制限時間の設定。
	m_timeLimit = 120.0f;

	//背景の作成。
	m_backGround = NewGO<BackGround>(0);

	//ベルの作成。
	m_ringBell = NewGO<RingBell>(0, "ringbell");

	//プレイヤーの作成。
	m_player = NewGO<Player>(0, "player");

	//ゲームカメラの作成。
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
}

Vector3 Game::Random()
{
	Vector3 position;
	int m_spawnRandom = rand() % 3;

	switch (m_spawnRandom)
	{
	case 0:
		position = { 0.0f, -10.0f, 3000.0f };
		break;
	case 1:
		position = { 800.0f, -10.0f, 3000.0f };
		break;
	case 2:
		position = { -800.0f, -10.0f, 3000.0f };
		break;
	}

	return position;
	Vector3 m_position;
	//ランダムにポジションを当てはめる
	m_position.x = rand() % 800 - 400;
	m_position.y = 0.0f;
	m_position.z = rand() % 1000 + 500;
	return m_position;
}

//火打石作成用関数。
void Game::CreateStone()
{
	// 火打石を表示。
	m_stone1 = NewGO<Stone>(0, "stone1");
	m_stone1->m_position = { 1000.0f,0.0f,-500.0f };
	m_stone1->m_firstPosition = m_stone1->m_position;
	//m_stone1 = FindGO<Stone>("stone");

	m_stone2 = NewGO<Stone>(0, "stone2");
	m_stone2->m_position = { 200.0f,0.0f,-2000.0f };
	m_stone2->m_firstPosition = m_stone2->m_position;
	//m_stone2 = FindGO<Stone>("stone");

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

//敵を生成用関数。
void Game::CreateEnemy()
{
	//タイマーを増やす。
	m_timer += g_gameTime->GetFrameDeltaTime();
	//1分目
	if (m_timer > 120.0f && m_timer < 180.0f)
	{
		m_maxCount = 5;
	}
	//2分目
	else if (m_timer > 180.0f && m_timer < 240.0f)
	{
		m_maxCount = 10;
	}
	//3分目
	else
	{
		m_maxCount = 20;
	}

	m_totalCount = m_enemyList.size() + m_littleEnemyList.size();

	/*while (m_enemyList.size()+m_littleEnemyList.size()<m_maxCount)*/
	if (m_totalCount < m_maxCount)
	{
		for (int i = 0; i < 5; ++i)
		{
			int r = rand() % 100;

			if (r >= 95) {
				//ボス。
				BossEnemy* boss = NewGO<BossEnemy>(1, "bossEnemy");
				boss->SetPosition(Random());
				m_bossEnemyList.push_back(boss);
			}
			else if (r >= 80) {
				//ウザイ敵
				AnnoyingEnemy* annoying = NewGO<AnnoyingEnemy>(1, "annoyingEnemy");
				annoying->SetPosition(Random());
				m_annoyingEnemyList.push_back(annoying);
			}
			else if (r >= 40) {
				//普通の敵。
				Enemy* enemy = NewGO<Enemy>(1, "enemy");
				enemy->SetPosition(Random());
				m_enemyList.push_back(enemy);
			}
			else {
				//雑魚敵。
				LittleEnemy* little = NewGO<LittleEnemy>(1, "littleEnemy");
				little->SetPosition(Random());
				m_littleEnemyList.push_back(little);
			}
		}
	}
}
	
//UI作成用関数。
void Game::CreateUI()
{
	//クロスヘアーを表示。
	m_crossHair = NewGO<CrossHair>(0);


	//月読の加護のUI
	m_uiTukuyomi = NewGO<UItukuyomi>(0, "uitukuyomi");
	//スキルUI
	m_uiSkill = NewGO<UIskill>(0, "uiskill");
	//しめ縄UI
	m_uiSimenawa = NewGO<UISimenawa>(0, "uisimenawa");
	//ミニマップ
	//m_miniMap = NewGO<MiniMap>(0, "minimap");
	//呪ゲージ
	m_uiCurseBar = NewGO<UIcurseBar>(0, "uicursebar");
	//回復
	m_uiHeal = NewGO <UIheal>(0, "uiheal");
	//火打石のカウントを表示。
	m_uiStone = NewGO<UIStone>(0, "uiStone");
}

void Game::UITimer()
{
	//タイマーの表示
	wchar_t wcsbuf[256];

	int minute = (int)m_timer / 60;

	int sec = (int)m_timer % 60;
	swprintf_s(wcsbuf, 256, L"AM%01d:%02d", minute, sec);

	//フォントを設定。
	m_timerFontRender.SetText(wcsbuf);
	//フォントの大きさを設定。
	m_timerFontRender.SetScale(1.5f);
	//フォントの位置を設定。
	m_timerFontRender.SetPosition(Vector3(0.0f, 500.0f, 0.0f));
	//フォントの色を設定。
	m_timerFontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	m_timer += g_gameTime->GetFrameDeltaTime();
}

void Game::Render(RenderContext& rc)
{
	m_timerFontRender.Draw(rc);
}