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
#include "LanternLight.h"
#include "LanternAttack.h"
#include "BlueFlame.h"
#include "LanternAttackLight.h"
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
#include "EnemyUI.h"
#include "Fade.h"
#include "graphics/effect/EffectEmitter.h"

bool Game::Start()
{
	//インスタンスアドレスを検索。
	m_fade = FindGO<Fade>("fade");


	//ステージ全体を暗くする。
	g_sceneLight->SetAmbient(Vector3(0.0001f, 0.0001f, 0.0001f));

	g_sceneLight->SetDirectionLight(0, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));

	//空の作成
	SkyCube* skyCube = NewGO<SkyCube>(0);
	skyCube->SetType(enSkyCubeType_NightToon_2);
	skyCube->SetScale(1000.0f);
	skyCube->SetLuminance(0.0005f);//空の光の強さ

	g_renderingEngine->SetAmbientByIBLTexture(skyCube->GetTextureFilePath(), 0.0004f);//空の光から影響する環境光の強さ

	//オブジェクトの作成。
	CreateObject();

	//火打石の作成。
	CreateStone();

	//灯籠の作成。
	CreateLantern();

	//攻撃用灯籠の作成。
	CreateAttackLantern();

	//UIの作成。
	CreateUI();

	//Enemyの作成。
	//CreateEnemy();

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

	//灯籠用ライト
	DeleteGO(m_lanternLight1);
	DeleteGO(m_lanternLight2);
	DeleteGO(m_lanternLight3);
	DeleteGO(m_lanternLight4);

	//灯籠用エフェクト
	DeleteGO(m_blueFlame1);
	DeleteGO(m_blueFlame2);
	DeleteGO(m_blueFlame3);
	DeleteGO(m_blueFlame4);

	//攻撃用灯籠。
	DeleteGO(m_lanternAttack1);
	DeleteGO(m_lanternAttack2);
	DeleteGO(m_lanternAttack3);

	//攻撃灯籠用ライト
	DeleteGO(m_lanternAttackLight1);
	DeleteGO(m_lanternAttackLight2);
	DeleteGO(m_lanternAttackLight3);

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
	if (m_fade->isFade())
	{
		return;
	}
	
	//タイマーを表示する用関数。
	UITimer();

	//ゲームーオーバーやゲームクリアーを呼び出す関数。
	GameManager();
  
    //灯籠用ライトのステート
	LanternLightState();
	//灯籠用ライトの作成
	CreateLanternLight();
	//灯籠用エフェクトの作成
	//CreateLanternEffect();

	//攻撃灯籠用ライトのステート
	LanternAttackLightState();
	//攻撃灯籠用ライトの作成
	CreateLanternAttackLight();

	//プレイヤーが四つ灯籠に火を灯したら
	if (m_player->m_enemyIsCanAttack != false) {
		//エネミーの作成
		CreateEnemy();
	}

}

//ゲームクリア、ゲームオーバーの判定処理。
void Game::GameManager()
{
	//タイマーを減らす処理。
	//m_timeLimit -= g_gameTime->GetFrameDeltaTime();

	//敵から本殿を守り切ったらゲームクリア。
	if (m_timer >= 300.0f)
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
	m_timeLimit = 180.0f;

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

//灯籠用ライトのステート
void Game::LanternLightState()
{
	//プレイヤーと灯籠の距離をそれぞれ計算する
	Vector3 m_lanternDiff1 = m_player->m_position - m_lantern1->m_position;//1つ目
	Vector3 m_lanternDiff2 = m_player->m_position - m_lantern2->m_position;//2つ目
	Vector3 m_lanternDiff3 = m_player->m_position - m_lantern3->m_position;//3つ目
	Vector3 m_lanternDiff4 = m_player->m_position - m_lantern4->m_position;//4つ目

	m_lanternLightState = 0;//灯籠用ライトステートを常に初期化
	m_lanternEffectState = 0;

	//1つ目の灯籠に火が灯ったら
	if (m_lantern1->m_isLight == true) {
		//かつ、1つ目の灯籠と距離が近かったら
		if (m_lanternDiff1.Length() <= 100.0f) {
			m_lanternLightState = 1;
			m_lanternEffectState = 1;
		}
	}
	//2つ目の灯籠に火が灯ったら
	if (m_lantern2->m_isLight == true) {
		//かつ、2つ目の灯籠と距離が近かったら
		if (m_lanternDiff2.Length() <= 100.0f) {
			m_lanternLightState = 2;
			m_lanternEffectState = 2;
		}
	}
	//3つ目の灯籠に火が灯ったら
	if (m_lantern3->m_isLight == true) {
		//かつ、3つ目の灯籠と距離が近かったら
		if (m_lanternDiff3.Length() <= 100.0f) {
			m_lanternLightState = 3;
			m_lanternEffectState = 3;
		}
	}
	//4つ目の灯籠に火が灯ったら
	if (m_lantern4->m_isLight == true) {
		//かつ、4つ目の灯籠と距離が近かったら
		if (m_lanternDiff4.Length() <= 100.0f) {
			m_lanternLightState = 4;
			m_lanternEffectState = 4;
		}
	}
	
}

//灯籠用ライトの作成
void Game::CreateLanternLight()
{
	switch (m_lanternLightState)
	{
		//1つ目の灯籠に火が灯ったら
	case 1:
			//1つ目の灯籠用ライトが灯っていなかったら
			if (m_lanternLightFlag1 == false) {
				//1つ目の灯籠用ライトを作成する
				m_lanternLight1 = NewGO<LanternLight>(0, "lanternLight1");
				m_lanternLight1->m_position = { 500.0f,50.0f,500.0f };
				m_lanternLight1->m_firstPosition = m_lanternLight1->m_position;
				//1つ目の灯籠用エフェクトを作成する
				m_blueFlame1 = NewGO<BlueFlame>(0, "blueFlame1");
				m_blueFlame1->m_position = { 500.0f,100.0f,500.0f };
				m_blueFlame1->m_firstPosition = m_blueFlame1->m_position;
				m_lanternLightFlag1 = true;//灯っている判定にする
			}
		break;
		//2つ目の灯籠に火が灯ったら
	case 2:
			//2つ目の灯籠用ライトが灯っていなかったら
			if (m_lanternLightFlag2 == false) {
				//2つ目の灯籠用ライトを作成する
				m_lanternLight2 = NewGO<LanternLight>(0, "lanternLight2");
				m_lanternLight2->m_position = { 500.0f,50.0f,-500.0f };
				m_lanternLight2->m_firstPosition = m_lanternLight2->m_position;
				//2つ目の灯籠用エフェクトを作成する
				m_blueFlame2 = NewGO<BlueFlame>(0, "blueFlame2");
				m_blueFlame2->m_position = { 500.0f,100.0f,-500.0f };
				m_blueFlame2->m_firstPosition = m_blueFlame2->m_position;
				m_lanternLightFlag2 = true;//灯っている判定にする
			}
		break;
		//3つ目の灯籠に火が灯ったら
	case 3:	
			//3つ目の灯籠用ライトが灯っていなかったら
			if (m_lanternLightFlag3 == false) {
				//3つ目の灯籠用ライトを作成する
				m_lanternLight3 = NewGO<LanternLight>(0, "lanternLight3");
				m_lanternLight3->m_position = { -500.0f,50.0f,500.0f };
				m_lanternLight3->m_firstPosition = m_lanternLight3->m_position;
				//3つ目の灯籠用エフェクトを作成する
				m_blueFlame3 = NewGO<BlueFlame>(0, "blueFlame3");
				m_blueFlame3->m_position = { -500.0f,100.0f,500.0f };
				m_blueFlame3->m_firstPosition = m_blueFlame3->m_position;
				m_lanternLightFlag3 = true;//灯っている判定にする
			}
		break;
		//4つ目の灯籠に火が灯ったら
	case 4:
			//4つ目の灯籠用ライトが灯っていなかったら
			if (m_lanternLightFlag4 == false) {
				//4つ目の灯籠用ライトを作成する
				m_lanternLight4 = NewGO<LanternLight>(0, "lanternLight4");
				m_lanternLight4->m_position = { -500.0f,50.0f,-500.0f };
				m_lanternLight4->m_firstPosition = m_lanternLight4->m_position;
				//4つ目の灯籠用エフェクトを作成する
				m_blueFlame4 = NewGO<BlueFlame>(0, "blueFlame4");
				m_blueFlame4->m_position = { 500.0f,100.0f,-500.0f };
				m_blueFlame4->m_firstPosition = m_blueFlame4->m_position;
				m_lanternLightFlag4 = true;//灯っている判定にする
			}
		break;
	}
}

//灯籠用エフェクトの作成
void Game::CreateLanternEffect()
{
	switch (m_lanternEffectState)
	{
	case 1:
		if (m_lanternEffectFlag1 == false) {
			//1つ目の灯籠用エフェクトを作成する
			m_blueFlame1 = NewGO<BlueFlame>(0, "blueFlame1");
			m_blueFlame1->m_position = { 0.0f,100.0f,0.0f };
			m_blueFlame1->m_firstPosition = m_blueFlame1->m_position;
			m_lanternEffectFlag1 = true;
		}
		break;
	case 2:
		if (m_lanternEffectFlag2 == false) {
			//2つ目の灯籠用エフェクトを作成する
			m_blueFlame2 = NewGO<BlueFlame>(0, "blueFlame2");
			m_blueFlame2->m_position = { 500.0f,100.0f,-500.0f };
			m_blueFlame2->m_firstPosition = m_blueFlame2->m_position;
			m_lanternEffectFlag2 = true;
		}
		break;
	case 3:
		if (m_lanternEffectFlag3 == false) {
			//3つ目の灯籠用エフェクトを作成する
			m_blueFlame3 = NewGO<BlueFlame>(0, "blueFlame3");
			m_blueFlame3->m_position = { -500.0f,100.0f,500.0f };
			m_blueFlame3->m_firstPosition = m_blueFlame3->m_position;
			m_lanternEffectFlag3 = true;
		}
		break;
	case 4:
		if (m_lanternEffectFlag4 == false) {
			//4つ目の灯籠用エフェクトを作成する
			m_blueFlame4 = NewGO<BlueFlame>(0, "blueFlame4");
			m_blueFlame4->m_position = { 500.0f,100.0f,-500.0f };
			m_blueFlame4->m_firstPosition = m_blueFlame4->m_position;
			m_lanternEffectFlag4 = true;
		}
		break;
	}
}

//攻撃灯籠の作成用関数
void Game::CreateAttackLantern()
{
	//攻撃用灯籠のモデルを表示
	m_lanternAttack1 = NewGO<LanternAttack>(0, "lanternAttack1");
	m_lanternAttack1->m_position = { 700.0f,-50.0f,4000.0f };
	m_lanternAttack1->m_firstPosition = m_lanternAttack1->m_position;
	//m_lantern1 = FindGO<Lantern>("lantern1");

	m_lanternAttack2 = NewGO<LanternAttack>(0, "lanternAttack2");
	m_lanternAttack2->m_position = { -700.0f,-50.0f,4000.0f };
	m_lanternAttack2->m_firstPosition = m_lanternAttack2->m_position;
	//m_lantern2 = FindGO<Lantern>("lantern2");

	m_lanternAttack3 = NewGO<LanternAttack>(0, "lanternAttack3");
	m_lanternAttack3->m_position = { 100.0f,-50.0f,3000.0f };
	m_lanternAttack3->m_firstPosition = m_lanternAttack3->m_position;
	//m_lantern3= FindGO<Lantern>("lantern3");
}

//攻撃灯籠用ライトのステート
void Game::LanternAttackLightState()
{
	//プレイヤーと攻撃灯籠の距離をそれぞれ計算する
	Vector3 LanternAttackDiff1 = m_player->m_position - m_lanternAttack1->m_position;//1つ目
	Vector3 LanternAttackDiff2 = m_player->m_position - m_lanternAttack2->m_position;//2つ目
	Vector3 LanternAttackDiff3 = m_player->m_position - m_lanternAttack3->m_position;//3つ目

	m_lanternAttackLightState = 0;//攻撃灯籠用ライトステートを常に初期化

	//1つ目の攻撃灯籠に火が灯ったら
	if (m_lanternAttack1->m_isLight == true) {
		//かつ、1つ目の攻撃灯籠と距離が近かったら
		if (LanternAttackDiff1.Length() <= 100.0f) {
			m_lanternAttackLightState = 1;
		}
	}
	//2つ目の攻撃灯籠に火が灯ったら
	if (m_lanternAttack2->m_isLight == true) {
		//かつ、2つ目の攻撃灯籠と距離が近かったら
		if (LanternAttackDiff2.Length() <= 100.0f) {
			m_lanternAttackLightState = 2;
		}
	}
	//3つ目の攻撃灯籠に火が灯ったら
	if (m_lanternAttack3->m_isLight == true) {
		//かつ、3つ目の攻撃灯籠と距離が近かったら
		if (LanternAttackDiff3.Length() <= 100.0f) {
			m_lanternAttackLightState = 3;
		}
	}
}

//攻撃灯籠用ライトを作成
void Game::CreateLanternAttackLight()
{
	switch (m_lanternAttackLightState)
	{
		//1つ目の攻撃灯籠に火が灯ったら
	case 1:
		//1つ目の攻撃灯籠用ライトが灯っていなかったら
		if (m_lanternAttackLightFlag1 == false) {
			//1つ目の攻撃灯籠用ライトを作成する
			m_lanternAttackLight1 = NewGO<LanternAttackLight>(0, "lanternAttackLight1");
			m_lanternAttackLight1->m_position = { 700.0f,80.0f,4000.0f };
			m_lanternAttackLight1->m_firstPosition = m_lanternAttackLight1->m_position;
			m_lanternAttackLightFlag1 = true;//灯っている判定にする
		}
		break;
		//2つ目の攻撃灯籠に火が灯ったら
	case 2:
		//2つ目の攻撃灯籠用ライトが灯っていなかったら
		if (m_lanternAttackLightFlag2 == false) {
			//2つ目の攻撃灯籠用ライトを作成する
			m_lanternAttackLight2 = NewGO<LanternAttackLight>(0, "lanternAttackLight2");
			m_lanternAttackLight2->m_position = { -700.0f,80.0f,4000.0f };
			m_lanternAttackLight2->m_firstPosition = m_lanternAttackLight2->m_position;
			m_lanternAttackLightFlag2 = true;//灯っている判定にする
		}
		break;
		//3つ目の攻撃灯籠に火が灯ったら
	case 3:
		//3つ目の攻撃灯籠用ライトが灯っていなかったら
		if (m_lanternAttackLightFlag3 == false) {
			//3つ目の攻撃灯籠用ライトを作成する
			m_lanternAttackLight3 = NewGO<LanternAttackLight>(0, "lanternAttackLight3");
			m_lanternAttackLight3->m_position = { 100.0f,80.0f,3000.0f };
			m_lanternAttackLight3->m_firstPosition = m_lanternAttackLight3->m_position;
			m_lanternAttackLightFlag3 = true;//灯っている判定にする
		}
		break;
	}
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

	m_totalCount = m_enemyList.size() + m_littleEnemyList.size()+m_annoyingEnemyList.size()+m_bossEnemyList.size();

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
				EnemyUI* enemyUI = NewGO<EnemyUI>(1,"enemyui");
				enemyUI->SetBossEnemy(boss);
			}
			else if (r >= 80) {
				//ウザイ敵
				AnnoyingEnemy* annoying = NewGO<AnnoyingEnemy>(1, "annoyingEnemy");
				annoying->SetPosition(Random());
				m_annoyingEnemyList.push_back(annoying);
				EnemyUI* enemyUI = NewGO<EnemyUI>(1,"enemyui");
				enemyUI->SetAnnoyingEnemy(annoying);
			}
			else if (r >= 40) {
				//普通の敵。
				Enemy* enemy = NewGO<Enemy>(1, "enemy");
				enemy->SetPosition(Random());
				m_enemyList.push_back(enemy);
				EnemyUI* enemyUI = NewGO<EnemyUI>(1,"enemyui");
				enemyUI->SetEnemy(enemy);
			}
			else {
				//雑魚敵。
				LittleEnemy* little = NewGO<LittleEnemy>(1, "littleEnemy");
				little->SetPosition(Random());
				m_littleEnemyList.push_back(little);
				EnemyUI* enemyUI = NewGO<EnemyUI>(1,"enemyui");
				enemyUI->SetLittleEnemy(little);
			}
		}
		//タイマーを減らす処理。
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
		m_totalCount = m_enemyList.size() + m_littleEnemyList.size() + m_annoyingEnemyList.size() + m_bossEnemyList.size();
		/*while (m_enemyList.size()+m_littleEnemyList.size()<m_maxCount)*/
		if (m_totalCount < m_maxCount)
		{
			int ram = rand() % 100;

			if (ram > 30) {
				for (int i = 0; i < 5; i++)
				{
					int ram = rand() % 100;

					if (ram > 30)
					{
						Enemy* enemy = NewGO<Enemy>(1, "enemy");
						enemy->SetPosition(Random());
						m_enemyList.push_back(enemy);//敵リストに追加
						m_enemyList.push_back(enemy);//敵リストに追加する。
						m_enemyList.push_back(enemy);//謨ｵ繝ｪ繧ｹ繝医↓霑ｽ蜉
						EnemyUI* enemyUI = NewGO<EnemyUI>(1,"enemyui");
						enemyUI->SetEnemy(enemy);
					}
					else {
						LittleEnemy* m_littleEnemy = NewGO<LittleEnemy>(1, "littleEnemy");
						m_littleEnemy->SetPosition(Random());
						m_littleEnemyList.push_back(m_littleEnemy);//リトル敵リストに追加
						m_enemyUI = NewGO<EnemyUI>(1,"enemyui");
						m_enemyUI->SetLittleEnemy(m_littleEnemy);
						if (ram > 30)
						{
							LittleEnemy* littleEnemy = NewGO<LittleEnemy>(1, "littleEnemy");
							littleEnemy->SetPosition(Random());
							m_littleEnemyList.push_back(littleEnemy);//リトル敵リストに追加
							m_littleEnemyList.push_back(littleEnemy);//雑魚敵を敵のリストに追加する。
							m_enemyUI = NewGO<EnemyUI>(1,"enemyui");
							m_enemyUI->SetLittleEnemy(littleEnemy);
						}
						if (ram > 30)
						{
							BossEnemy* bossEnemy = NewGO<BossEnemy>(1, "bossEnemy");
							bossEnemy->SetPosition(Random());
							m_bossEnemyList.push_back(bossEnemy);//ボスエネミーを敵のリストに追加する。
							m_enemyUI = NewGO<EnemyUI>(1,"enemyui");
							m_enemyUI->SetBossEnemy(bossEnemy);
						}
					}
				}
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
	m_timerFontRender.SetPosition(Vector3(-80.0f, 500.0f, 0.0f));
	//フォントの色を設定。
	m_timerFontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	m_timer += g_gameTime->GetFrameDeltaTime();
}

void Game::Render(RenderContext& rc)
{
	m_timerFontRender.Draw(rc);
}