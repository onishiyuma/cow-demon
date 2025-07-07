#include "stdafx.h"
#include "sound/SoundEngine.h"
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
#include "BlueFlame.h"
#include "LanternArrow.h"
#include "Mountain.h"
#include "Tree.h"
#include "UIStone.h"
#include "UItukuyomi.h"
#include "UIskill.h"
#include "UISimenawa.h"
#include "UIcurseBar.h"
#include "UIMPBar.h"
#include "UIheal.h"
#include "GameClear.h"
#include "GameOver.h"
#include "random"
#include "EnemyUI.h"
#include "Poison.h"
#include "Load.h"
#include "UIOne.h"
#include "UITwo.h"	
#include "UIThree.h"
#include "UIZero.h"
#include "TimeLimit.h"


namespace
{
	const Vector3	SET_AMBIENT = { 0.0001f, 0.0001f, 0.0001f };				//環境光の初期値。
	const Vector3	SET_SKY_AMBIENT = { 1.0f, 1.0f, 1.0f };						//空の環境光の初期値。
	const Vector3	SET_DIRECTION = { 0.0f, 0.0f, 0.0f };						//方向光の初期値。
	const Vector3	SET_DIRECTION_LIGHT_COLOR = { 0.0f, 0.0f, 0.0f };			//方向光の色の初期値。
	const Vector3	SET_DIRECTION_LIGHT = { 1.0f, 1.0f, 1.0f };					//方向光の強さ。
	const Vector3	ENEMY_SPAWN_POSITION_Mid = { 0.0f, 0.0f, 3000.0f };			//敵のスポーン位置。
	const Vector3	ENEMY_SPAWN_POSITION_Left = { -1000.0f, 0.0f, 3000.0f };	//敵のスポーン位置。
	const Vector3	ENEMY_SPAWN_POSITION_Right = { 1000.0f, 0.0f, 3000.0f };	//敵のスポーン位置。
	const Vector3   BOSS_SPAWN_POSITION_Mid = { 0.0f, 0.0f, 3400.0f };			//ボスのスポーン位置。
	const Vector3	BOSS_SPAWN_POSITION_Left = { -1200.0f, 0.0f, 3200.0f };	//敵のスポーン位置。
	const Vector3	BOSS_SPAWN_POSITION_Right = { 1200.0f, 0.0f, 3200.0f };	//敵のスポーン位置。
	const Vector3	FONT_RENDER_POSITION = { - 200.0f, 500.0f, 0.0f};			//フォントの表示位置。
	const float		SET_SKY_LUMINANCE = 1000.0f;								//空の光の強さ。
	const float		ENEMY_SPAWN_TIME = 150.0f;									//敵のスポーン時間。
	const float		TIME_LIMIT_NOTIFY = 240.0f;									//時間制限の通知時間。
	const float		GAMELEAR_TIME = 300.0f;										//ゲームクリアの時間。
	const float		NONE_PLAYER_HP=0;											//プレイヤーのHPがなくなった。
	const float		TIMELIIT_TIME = 180.0f;										//制限時間。
	const float		SET_FONT_SCALE = 1.5f;										//フォントのスケール。
	const float		SET_FONT_NOTIFY_SCALE = 2.0f;								//フォントの通知スケール。
	const float		NOTIFY_SCROLL_SPEED = 230.0f;								//敵出現通知のスクロール速度。
	const float		NOTIFY_POSITION_X = -1400;									//敵出現通知のX座標。
	const float		NOTIFY_POSITION_Y = 400.0f;									//敵出現通知のY座標。
	const float		LANTERN_EFFECT_TRIGGER_DISTANCE = 100.0f;					//灯籠用エフェクトの判定距離。
	const int		MAX_LANTERN_COUNT = 4;										//灯籠の最大数。
	const int		SECONDS_IN_MINUTE = 60;										//1分の秒数。
	const int		WCS_BUFFER_SIZE = 256;										//バッファサイズ。
}

bool Game::Start()
{
	//ステージ全体を暗くする。
	g_sceneLight->SetAmbient(SET_AMBIENT);
	g_sceneLight->SetDirectionLight(0, SET_DIRECTION_LIGHT,SET_DIRECTION_LIGHT_COLOR);

	//空の作成。
	m_skyCube = NewGO<SkyCube>(0, "skyCube");
	m_skyCube->SetType(enSkyCubeType_NightToon);
	m_skyCube->SetScale(SET_SKY_LUMINANCE);

	//空の光の強さ。
	m_skyCube->SetLuminance(m_skyLuminance);

	//空の光から影響する環境光の強さ
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(),m_skyAmbient);

	//敵出現通知のX座標。
	m_notifyx = 1000.0f;	

	//オブジェクトの作成。
	CreateObject();
	//火打石の作成。
	CreateStone();
	//灯籠の作成。
	CreateLantern();
	//UIの作成。
	CreateUI();
	//ボタンUIの作成。
	ButtonUI();
	//灯籠用矢印の作成。
	CreateLanternArrow();

	//インスタンスアドレスを検索。
	m_load = FindGO<Load>("load");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_enemy = FindGO<Enemy>("enemy");

	m_spriteRender.Init("Assets/sprite/white.DDS", 1920.0f, 1080.0f);
	m_spriteRender.SetScale({ 2.0f,2.0f,1.0f });
	m_spriteRender.SetMulColor(m_spriteColor);

	m_isEndGame = false;

	return true;
}

Game::Game()
{

}

Game::~Game()
{


	DeleteGO(m_player);			//プレイヤー。
	DeleteGO(m_gameCamera);		//ゲームカメラ。
	DeleteGO(m_backGround);		//ステージ。
	DeleteGO(m_mountain);		//山。
	DeleteGO(m_tree);			//木。
	DeleteGO(m_crossHair);		//クロスヘアー。
	DeleteGO(m_ringBell);		//ベル。

	//火打石。
	//オブジェクトがある場合削除
	if (m_stone4 != nullptr) {
		DeleteGO(m_stone4);
		m_stone4 = nullptr;
	}

	if (m_stone5 != nullptr) {
		DeleteGO(m_stone5);
		m_stone5 = nullptr;
	}

	if (m_stone6 != nullptr) {
		DeleteGO(m_stone6);
		m_stone6 = nullptr;
	}

	if (m_stone7 != nullptr) {
		DeleteGO(m_stone7);
		m_stone7 = nullptr;
	}

	//灯籠。
	DeleteGO(m_lantern1);
	DeleteGO(m_lantern2);
	DeleteGO(m_lantern3);
	DeleteGO(m_lantern4);

	//灯籠用ライト。
	DeleteGO(m_lanternLight1);
	DeleteGO(m_lanternLight2);
	DeleteGO(m_lanternLight3);
	DeleteGO(m_lanternLight4);

	//灯籠用エフェクト。
	DeleteGO(m_blueFlame1);
	DeleteGO(m_blueFlame2);
	DeleteGO(m_blueFlame3);
	DeleteGO(m_blueFlame4);

	//灯籠用矢印。
	DeleteGO(m_lanternArrow1);
	DeleteGO(m_lanternArrow2);
	DeleteGO(m_lanternArrow3);
	DeleteGO(m_lanternArrow4);

	//UI関連。
	DeleteGO(m_uiTukuyomi);
	DeleteGO(m_uiSkill);
	DeleteGO(m_uiSimenawa);
	DeleteGO(m_uiCurseBar);
	DeleteGO(m_uiMPBar);
	DeleteGO(m_uiHeal);
	DeleteGO(m_uiStone);
	DeleteGO(m_enemyUI);
	DeleteGO(m_skyCube);

	if(m_stage != nullptr)
	{
		DeleteGO(m_stage);
	}
}

void Game::Update()
{	
	//ロードが完了していない場合はUpdateしない。
	if (m_isLoad && m_load->isLoad())
	{
		return;
	}
	
	//カウントダウンを開始。
	if (!m_isCowntDownStart)
	{
		//カウントダウンの開始。
		StartCountDown();

	}
	else if (m_isCowntDownStart) {

		if (!m_isGameStart) {
			//カウントダウンが終わったら、ゲーム開始。
			m_uiZero = NewGO<UIZero>(0, "UIZero");
			//スタートの音を鳴らす。
			g_soundEngine->ResistWaveFileBank(2, "Assets/sound/gameStart.wav");
			m_gameStartSound = NewGO<SoundSource>(2);
			m_gameStartSound->Init(2);
			m_gameStartSound->Play(false);

			//火打石のカウントを表示。
			m_uiStone = NewGO<UIStone>(0, "uiStone");

			//ゲームスタートのフラグを立てる。
			m_isGameStart = true;
		}
		//エネミーの管理
		EnemyManager();
		//タイマーを表示する用関数。
		UITimer();
		//ゲームーオーバーやゲームクリアーを呼び出す関数。
		GameManager();
		//灯籠用ライトのステート。
		LanternLightState();
		//灯籠用ライトの作成。
		CreateLanternLight();
		//灯籠用エフェクトの作成
		CreateLanternEffect();
		//空の明るさ調整。
		SetSkyLight();
		//敵のスポーン処理と敵が来たことを通知する。
		NotifiyEnemy();



		if (m_timer >= ENEMY_SPAWN_TIME) {
			//一定時間経過したら敵をスポーンさせる。
			CreateEnemy();
		}


		if (m_timer >= 240.0f) {
			if (m_timer >= TIME_LIMIT_NOTIFY) {
				if (!m_isTimeLimit) {
					//ゲームクリアが近いことを知らせる。
					m_timeLimit1 = NewGO<TimeLimit>(0, "timeLimit");
					m_isTimeLimit = true;
				}
			}
		}
	}
}

	

//ゲームクリア、ゲームオーバーの判定処理。
void Game::GameManager()
{
	//敵から本殿を守り切ったらゲームクリア。
	if (m_timer >= GAMELEAR_TIME)
	{
		m_isEndGame = true;
		DeleteGO(m_stage);//ステージのBGMを止める。
		//ゲームクリアの音を鳴らす。
		if (!m_isGameClear) {
			g_soundEngine->ResistWaveFileBank(92, "Assets/sound/stage.wav");
			m_clearBGM = NewGO<SoundSource>(92);
			m_clearBGM->Init(92);
			m_clearBGM->Play(false);
			m_isGameClear = true;
		}
		m_gameClearFont.SetText(L"あなたは本殿を守り抜いた");
		m_gameClearFont.SetPosition(Vector3(-400.0f, 350.0f, 0.0f));
		m_gameClearFont.SetScale(1.5f);
		m_gameClearFont.SetColor({ 1.0f,1.0f,0.0f,1.0f });
		SpriteFade();
		m_spriteRender.Update();
	}

	if (m_timer >= 305.0f) 
	{
		DeleteGO(m_clearBGM);
		NewGO<GameClear>(0);
		DeleteGO(this);
		/*m_EndTimer += g_gameTime->GetFrameDeltaTime();
		if (m_EndTimer >= 0.5f) {
			
		}*/
	}
	

	//敵が本殿に入ったらイージングしてゲームオーバー。
	if (m_gameCamera->m_isCameraRotationFin && m_gameCamera->m_callGameOverTime >= m_gameCamera->m_waitTime)
	{
		m_isEndGame = true;
		NewGO<GameOver>(0);
		DeleteGO(this);
		/*m_EndTimer += g_gameTime->GetFrameDeltaTime();
		if (m_EndTimer >= 0.5f) {
			DeleteGO(this);
		}*/
	}
	
	//呪いの抵抗値がなくなったら。
	if (m_player->m_playerHP <= NONE_PLAYER_HP)
	{
		m_isEndGame = true;
	    NewGO<GameOver>(0);
		DeleteGO(this);
		/*m_EndTimer += g_gameTime->GetFrameDeltaTime();
		if (m_EndTimer >= 0.5f) {
			DeleteGO(this);
		}*/
	}

}

//空の設定。
void Game::SetSkyLight()
{
	//m_skyTimer += g_gameTime->GetFrameDeltaTime();
	////4時になるまでの明るさ設定。
	//if (m_timer < 240.0f) {
	//	if (m_skyTimer >= 1.0f) {
	//		//夜の明るさに設定。
	//		m_luminance += m_luminanceNight;
	//		//それぞれ夜の明るさに変更する。
	//		m_skyLuminance = m_luminance;
	//		m_skyAmbient = m_luminance;
	//		//適用。
	//		g_renderingEngine->SetAmbientByIBLTextureLuminance(m_skyAmbient);
	//		g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), m_skyAmbient);
	//		m_skyCube->SetLuminance(m_skyLuminance);
	//		m_skyTimer = 0.0f;//夜の明るさに設定したら、タイマーをリセット。
	//	}
	//}
	////４時以降の明るさ設定。
	//else if (m_timer >= 240.0f) {
	//	if (m_skyTimer >= 1.0f) {
	//		//真夜中の明るさに設定。
	//		m_luminance += m_luminanceNight;
	//		//それぞれ真夜中の明るさに変更する。
	//		m_skyLuminance = m_luminance;
	//		m_skyAmbient = m_luminance;
	//		//適用。
	//		g_renderingEngine->SetAmbientByIBLTextureLuminance(m_skyAmbient);
	//		g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), m_skyAmbient);
	//		m_skyCube->SetLuminance(m_skyLuminance);
	//		m_skyTimer = 0.0f;//真夜中の明るさに設定したら、タイマーをリセット。
	//	}
	//}
	//完全な夜。
	if (m_timer > m_phase1Start && m_timer < m_phase2Start) {
		if (!m_isNight) {
			//夜の明るさに設定。
			m_luminance += m_luminanceNight;
			//それぞれ夜の明るさに変更する。
			m_skyLuminance = m_luminance;
			m_skyAmbient = m_luminance;
			//適用。
			m_skyCube->SetLuminance(m_skyLuminance);
			g_renderingEngine->SetAmbientByIBLTextureLuminance(m_skyAmbient);
			g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), m_skyAmbient);
			m_isNight = true;
		}
	}
	//真夜中。
	else if (m_timer > m_phase2Start && m_timer < m_phase3Start) {
		if (!m_isMidNight1) {
			//真夜中の明るさに設定。
			m_luminance = m_luminanceMidNight1;
			//それぞれ真夜中の明るさに変更する。
			m_skyLuminance = m_luminance;
			m_skyAmbient = m_luminance;
			//適用。
			m_skyCube->SetLuminance(m_skyLuminance);
			g_renderingEngine->SetAmbientByIBLTextureLuminance(m_skyAmbient);
			g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), m_skyAmbient);
			m_isMidNight1 = true;
		}
	}
	////真夜中。
	//else if (m_timer > m_phase3Start && m_timer < m_phase4Start) {
	//	if (!m_isMidNight2) {
	//		//真夜中の明るさに設定。
	//		m_luminance = m_luminanceMidNight2;
	//		//それぞれ真夜中の明るさに変更する。
	//		m_skyLuminance = m_luminance;
	//		m_skyAmbient = m_luminance;
	//		//適用。
	//		m_skyCube->SetLuminance(m_skyLuminance);
	//		g_renderingEngine->SetAmbientByIBLTextureLuminance(m_skyAmbient);
	//		g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), m_skyAmbient);
	//		m_isMidNight2 = true;
	//	}
	//}
	//日の出開始。
	else if (m_timer > m_phase4Start && m_timer < m_phase5Start) {
		if (!m_isSunrise) {
			//日の出の明るさに設定。
			m_luminance = m_luminanceSunrise;
			//それぞれ日の出の明るさに変更する。
			m_skyLuminance = m_luminance;
			m_skyAmbient = m_luminance;
			//適用。
			m_skyCube->SetLuminance(m_skyLuminance);
			g_renderingEngine->SetAmbientByIBLTextureLuminance(m_skyAmbient);
			g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), m_skyAmbient);
			//ステージ全体の光の影響を調整する。
			g_sceneLight->SetAmbient(SET_SKY_AMBIENT);
			g_sceneLight->SetDirectionLight(0, SET_DIRECTION_LIGHT, SET_DIRECTION_LIGHT_COLOR);
			m_isSunrise = true;
		}
	}
}

//ゲーム前のカウントダウンを行う関数。
void Game::StartCountDown()
{
	m_countDownTimer -= g_gameTime->GetFrameDeltaTime();

	if (m_countDownTimer <= 3.0f && !m_isThree) {
		m_uiThree = NewGO<UIThree>(0, "UIThree");
		m_isThree = true;
	}
	else if (m_countDownTimer < 2.0f && m_countDownTimer > 1.0f && !m_isTwo) {
		if (m_uiThree != nullptr && m_uiThree->m_isMove) {
			DeleteGO(m_uiThree);
			m_uiThree = nullptr;
			m_uiTwo = NewGO<UITwo>(0, "UITwo");
			m_isTwo = true;
		}
	}
	else if (m_countDownTimer < 1.0f && m_countDownTimer > 0.0f && !m_isOne) {
		if (m_uiTwo != nullptr && m_uiTwo->m_isMove) {
			DeleteGO(m_uiTwo);
			m_uiTwo = nullptr;
			m_uiOne = NewGO<UIOne>(0, "UIOne");
			m_isOne = true;
		}
	}
	else if (m_countDownTimer <= 0.0f) {
		if (m_uiOne != nullptr && m_uiOne->m_isMove) {
			m_uiOne = nullptr;
			m_countDownTimer = 0.0f;//カウントダウンをリセット。
			m_isCowntDownStart = true;
		}
	}
}

//オブジェクト作成用関数。
void Game::CreateObject()
{
	//制限時間の設定。
	m_timeLimit = TIMELIIT_TIME;
	//背景の作成。
	m_backGround = NewGO<BackGround>(0);
	//ベルの作成。
	m_ringBell = NewGO<RingBell>(0, "ringbell");
	//山の作成。
	m_mountain = NewGO<Mountain>(0, "mountain");
	//木の作成。
	m_tree = NewGO<Tree>(0, "tree");
	//プレイヤーの作成。
	m_player = NewGO<Player>(0, "player");
	//ゲームカメラの作成。
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
}

Vector3 Game::Random()
{
	Vector3 position;
	int spawnRandom = rand() % 3;

	switch (spawnRandom)
	{
	case 0:
		position = ENEMY_SPAWN_POSITION_Mid;
		break;
	case 1:
		position = ENEMY_SPAWN_POSITION_Right;
		break;
	case 2:
		position = ENEMY_SPAWN_POSITION_Left;
		break;
	}

	return position;
}

Vector3 Game::BossRandom()
{
	Vector3 position;
	int spawnRandom = rand() % 3;

	switch (spawnRandom)
	{
	case 0:
		position = BOSS_SPAWN_POSITION_Mid;
		break;
	case 1:
		position = BOSS_SPAWN_POSITION_Right;
		break;
	case 2:
		position = BOSS_SPAWN_POSITION_Left;
		break;
	}

	return position;
}

//火打石作成用関数。
void Game::CreateStone()
{
	// 火打石を表示。
	m_stone4 = NewGO<Stone>(0, "stone4");
	m_stone4->m_position ={ -700.0f,-25.0f,-400.0f };
	m_stone4->m_firstPosition = m_stone4->m_position;

	m_stone5 = NewGO<Stone>(0, "stone5");
	m_stone5->m_position = { -700.0f,-25.0f,1100.0f };
	m_stone5->m_firstPosition = m_stone5->m_position;

	m_stone6 = NewGO<Stone>(0, "stone6");
	m_stone6->m_position = { 700.0f,-25.0f,500.0f };
	m_stone6->m_firstPosition = m_stone6->m_position;

	m_stone7 = NewGO<Stone>(0, "stone7");
	m_stone7->m_position = { 0.0f,-25.0f,-500.0f };
	m_stone7->m_firstPosition = m_stone7->m_position;
}

//灯籠作成用関数。
void Game::CreateLantern()
{
	//灯籠のモデルを表示。
	m_lantern1 = NewGO<Lantern>(0, "lantern1");
	m_lantern1->m_position = { 500.0f,-50.0f,1000.0f };
	m_lantern1->m_firstPosition = m_lantern1->m_position;

	m_lantern2 = NewGO<Lantern>(0, "lantern2");
	m_lantern2->m_position = { 500.0f,-50.0f,-500.0f };
	m_lantern2->m_firstPosition = m_lantern2->m_position;

	m_lantern3 = NewGO<Lantern>(0, "lantern3");
	m_lantern3->m_position = { -500.0f,-50.0f,1000.0f };
	m_lantern3->m_firstPosition = m_lantern3->m_position;

	m_lantern4 = NewGO<Lantern>(0, "lantern4");
	m_lantern4->m_position = { -500.0f,-50.0f,-500.0f };
	m_lantern4->m_firstPosition = m_lantern4->m_position;
}

//灯籠用ライトのステート。
void Game::LanternLightState()
{
	//プレイヤーと灯籠の距離をそれぞれ計算する。
	Vector3 lanternDiff1 = m_player->m_position - m_lantern1->m_position;//1つ目。
	Vector3 lanternDiff2 = m_player->m_position - m_lantern2->m_position;//2つ目。
	Vector3 lanternDiff3 = m_player->m_position - m_lantern3->m_position;//3つ目。
	Vector3 lanternDiff4 = m_player->m_position - m_lantern4->m_position;//4つ目。

	//m_lanternLightState = 0;//灯籠用ライトステートを常に初期化。
	m_lanternEffectState = 0;

	//1つ目の灯籠に火が灯ったら。
	if (m_lantern1->m_isLight)
	{
		//かつ、1つ目の灯籠と距離が近かったら。
		if (lanternDiff1.Length() <= LANTERN_EFFECT_TRIGGER_DISTANCE)
		{
			m_lanternEffectState = 1;
		}
	}
	//2つ目の灯籠に火が灯ったら。
	if (m_lantern2->m_isLight) 
	{
		//かつ、2つ目の灯籠と距離が近かったら。
		if (lanternDiff2.Length() <= LANTERN_EFFECT_TRIGGER_DISTANCE)
		{
			m_lanternEffectState = 2;
		}
	}
	//3つ目の灯籠に火が灯ったら。
	if (m_lantern3->m_isLight) 
	{
		//かつ、3つ目の灯籠と距離が近かったら。
		if (lanternDiff3.Length() <= LANTERN_EFFECT_TRIGGER_DISTANCE)
		{
			m_lanternEffectState = 3;
		}
	}
	//4つ目の灯籠に火が灯ったら。
	if (m_lantern4->m_isLight) 
	{
		//かつ、4つ目の灯籠と距離が近かったら。
		if (lanternDiff4.Length() <= LANTERN_EFFECT_TRIGGER_DISTANCE)
		{
			m_lanternEffectState = 4;
		}
	}
	
}

//灯籠用ライトの作成。
void Game::CreateLanternLight()
{
	if (m_player->m_lanternCount == MAX_LANTERN_COUNT) {
		if (!m_lanternLightFlag) {

			//火打石の数の表示を削除する。
			DeleteGO(m_uiStone);

			//MP回復のアドバイスを表示する。
			m_adviceMP.SetText(L"灯籠に近づくとMPを回復できるぞ");
			m_adviceMP.SetPosition(Vector3(-350.0f, -350.0f, 0.0f));
			m_adviceMP.SetScale(1.0f);
			m_adviceMP.SetColor({ 0.0f,1.0f,1.0f,1.0f });

			m_missionTask.SetText(L"5時まで本殿を守ろう");
			m_missionTask.SetPosition(Vector3(200.0f, 500.0f, 0.0f));
			m_missionTask.SetScale(1.5f);
			m_missionTask.SetColor({ 1.0f,0.5f,0.0f,1.0f });

			//1つ目の灯籠用ライトを作成する。
			m_lanternLight1 = NewGO<LanternLight>(0, "lanternLight1");
			m_lanternLight1->m_position = { 500.0f,80.0f,1000.0f };
			m_lanternLight1->m_firstPosition = m_lanternLight1->m_position;
			//2つ目の灯籠用ライトを作成する。
			m_lanternLight2 = NewGO<LanternLight>(0, "lanternLight2");
			m_lanternLight2->m_position = { 500.0f,80.0f,-500.0f };
			m_lanternLight2->m_firstPosition = m_lanternLight2->m_position;
			//3つ目の灯籠用ライトを作成する。
			m_lanternLight3 = NewGO<LanternLight>(0, "lanternLight3");
			m_lanternLight3->m_position = { -500.0f,80.0f,1000.0f };
			m_lanternLight3->m_firstPosition = m_lanternLight3->m_position;
			//4つ目の灯籠用ライトを作成する。
			m_lanternLight4 = NewGO<LanternLight>(0, "lanternLight4");
			m_lanternLight4->m_position = { -500.0f,80.0f,-500.0f };
			m_lanternLight4->m_firstPosition = m_lanternLight4->m_position;
			//灯籠用ライトが灯っている判定にする。
			m_lanternLightFlag = true;
		}

		LanternMPState();//灯籠用MPステートを呼び出す。
		LanternHealMP();//灯籠用MP回復を呼び出す。
	}
}

//灯籠用エフェクトの作成。
void Game::CreateLanternEffect()
{
	switch (m_lanternEffectState)
	{
	case 1:
		if (!m_lanternEffectFlag1) 
		{
			//1つ目の灯籠用エフェクトを作成する。
			m_blueFlame1 = NewGO<BlueFlame>(0, "blueFlame1");
			m_blueFlame1->m_position = { 500.0f,40.0f,1000.0f };
			m_blueFlame1->m_firstPosition = m_blueFlame1->m_position;
			m_lanternEffectFlag1 = true;
		}
		break;
	case 2:
		if (!m_lanternEffectFlag2) 
		{
			//2つ目の灯籠用エフェクトを作成する。
			m_blueFlame2 = NewGO<BlueFlame>(0, "blueFlame2");
			m_blueFlame2->m_position = { 500.0f,40.0f,-500.0f };
			m_blueFlame2->m_firstPosition = m_blueFlame2->m_position;
			m_lanternEffectFlag2 = true;
		}
		break;
	case 3:
		if (!m_lanternEffectFlag3)
		{
			//3つ目の灯籠用エフェクトを作成する。
			m_blueFlame3 = NewGO<BlueFlame>(0, "blueFlame3");
			m_blueFlame3->m_position = { -500.0f,40.0f,1000.0f };
			m_blueFlame3->m_firstPosition = m_blueFlame3->m_position;
			m_lanternEffectFlag3 = true;
		}
		break;
	case 4:
		if (!m_lanternEffectFlag4) 
		{
			//4つ目の灯籠用エフェクトを作成する。
			m_blueFlame4 = NewGO<BlueFlame>(0, "blueFlame4");
			m_blueFlame4->m_position = { -500.0f,40.0f,-500.0f };
			m_blueFlame4->m_firstPosition = m_blueFlame4->m_position;
			m_lanternEffectFlag4 = true;
		}
		break;
	}
}

void Game::CreateLanternArrow()
{
	//灯籠用の矢印を作成。
	m_lanternArrow1 = NewGO<LanternArrow>(0, "lanternArrow1");
	m_lanternArrow1->m_position = { 500.0f,140.0f,1000.0f };
	m_lanternArrow1->m_firstPosition = m_lanternArrow1->m_position;

	m_lanternArrow2 = NewGO<LanternArrow>(0, "lanternArrow2");
	m_lanternArrow2->m_position = { 500.0f,140.0f,-500.0f };
	m_lanternArrow2->m_firstPosition = m_lanternArrow2->m_position;

	m_lanternArrow3 = NewGO<LanternArrow>(0, "lanternArrow3");
	m_lanternArrow3->m_position = { -500.0f,140.0f,1000.0f };
	m_lanternArrow3->m_firstPosition = m_lanternArrow3->m_position;

	m_lanternArrow4 = NewGO<LanternArrow>(0, "lanternArrow4");
	m_lanternArrow4->m_position = { -500.0f,140.0f,-500.0f };
	m_lanternArrow4->m_firstPosition = m_lanternArrow4->m_position;
}

void Game::LanternMPState()
{
	//プレイヤーと灯籠の距離をそれぞれ計算する。
	Vector3 lanternMP1 = m_player->m_position - m_lantern1->m_position;//1つ目。
	Vector3 lanternMP2 = m_player->m_position - m_lantern2->m_position;//2つ目。
	Vector3 lanternMP3 = m_player->m_position - m_lantern3->m_position;//3つ目。
	Vector3 lanternMP4 = m_player->m_position - m_lantern4->m_position;//4つ目。

	m_lanternMPState = 0;//灯籠用MPステートを常に初期化。

	//1つ目の灯籠に火が灯ったら。
	if (m_lantern1->m_isLight)
	{
		//かつ、1つ目の灯籠と距離が近かったら。
		if (lanternMP1.Length() <= 150.0f)
		{
			m_lanternMPState = 1;
		}
	}
	//2つ目の灯籠に火が灯ったら。
	if (m_lantern2->m_isLight)
	{
		//かつ、2つ目の灯籠と距離が近かったら。
		if (lanternMP2.Length() <= 150.0f)
		{
			m_lanternMPState = 2;
		}
	}
	//3つ目の灯籠に火が灯ったら。
	if (m_lantern3->m_isLight)
	{
		//かつ、3つ目の灯籠と距離が近かったら。
		if (lanternMP3.Length() <= 150.0f)
		{
			m_lanternMPState = 3;
		}
	}
	//4つ目の灯籠に火が灯ったら。
	if (m_lantern4->m_isLight)
	{
		//かつ、4つ目の灯籠と距離が近かったら。
		if (lanternMP4.Length() <= 150.0f)
		{
			m_lanternMPState = 4;
		}
	}
}

void Game::LanternHealMP()
{
	m_healMPTimer += g_gameTime->GetFrameDeltaTime();//灯籠用MP回復タイマーを更新。

	//灯籠用MPステートに応じて、プレイヤーのMPを回復する。
	switch (m_lanternMPState)
	{
	case 1:
		
		if (m_healMPTimer >= 1.0f) {
			//プレイヤーのMPを回復する。
			m_player->m_playerMP += 20;
			//MPが最大値を超えないようにする。
			if (m_player->m_playerMP > m_player->m_playerMaxMP) {
				m_player->m_playerMP = m_player->m_playerMaxMP;
			}
			//灯籠用MP回復タイマーをリセット。
			m_healMPTimer = 0.0f;
		}
		break;
	case 2:
		
		if (m_healMPTimer >= 1.0f) {
			//プレイヤーのMPを回復する。
			m_player->m_playerMP += 20;
			//MPが最大値を超えないようにする。
			if (m_player->m_playerMP > m_player->m_playerMaxMP) {
				m_player->m_playerMP = m_player->m_playerMaxMP;
			}
			//灯籠用MP回復タイマーをリセット。
			m_healMPTimer = 0.0f;
		}
		break;
	case 3:
		
		if (m_healMPTimer >= 1.0f) {
			//プレイヤーのMPを回復する。
			m_player->m_playerMP += 20;
			//MPが最大値を超えないようにする。
			if (m_player->m_playerMP > m_player->m_playerMaxMP) {
				m_player->m_playerMP = m_player->m_playerMaxMP;
			}
			//灯籠用MP回復タイマーをリセット。
			m_healMPTimer = 0.0f;
		}
		break;
	case 4:
		
		if (m_healMPTimer >= 1.0f) {
			//プレイヤーのMPを回復する。
			m_player->m_playerMP += 20;
			//MPが最大値を超えないようにする。
			if (m_player->m_playerMP > m_player->m_playerMaxMP) {
				m_player->m_playerMP = m_player->m_playerMaxMP;
			}
			//灯籠用MP回復タイマーをリセット。
			m_healMPTimer = 0.0f;
		}
		break;
	}
}

//敵を生成用関数。
void Game::CreateEnemy()
{
	m_spawnTimer += g_gameTime->GetFrameDeltaTime();

	//1分目。
	if (m_timer >= 120.0f && m_timer <= 180.0f)
	{
		m_maxCount = 4;
	}
	//2分目。
	else if (m_timer >= 180.0f && m_timer <= 240.0f)
	{
		m_maxCount = 9;
	}
	//3分目。
	else
	{
		m_maxCount = 14;
	}

	if (m_spawnTimer >= 1.0f && m_totalCount < m_maxCount) {

		int r = rand() % 100;

		if (r >= 80) {
			//ウザイ敵。
			AnnoyingEnemy* annoying = NewGO<AnnoyingEnemy>(1, "annoyingEnemy");
			annoying->SetPosition(Random());
			m_annoyingEnemyList.push_back(annoying);
			EnemyUI* enemyUI = NewGO<EnemyUI>(1, "enemyui");
			enemyUI->SetAnnoyingEnemy(annoying);
			m_enemyUIList.push_back(enemyUI);
			m_totalCount++;
			//m_spawnTimer = 0.0f;
		}
		else if (r >= 40) {
			//普通の敵。
			Enemy* enemy = NewGO<Enemy>(1,"enemy");
			enemy->SetPosition(Random());
			m_enemyList.push_back(enemy);
			EnemyUI* enemyUI = NewGO<EnemyUI>(1, "enemyui");
			enemyUI->SetEnemy(enemy);
			m_enemyUIList.push_back(enemyUI);
			m_totalCount++;
			//m_spawnTimer = 0.0f;
		}
		else {
			//雑魚敵。
			LittleEnemy* littleEnemy = NewGO<LittleEnemy>(1, "littleEnemy");
			littleEnemy->SetPosition(Random());
			m_littleEnemyList.push_back(littleEnemy);
			EnemyUI* enemyUI = NewGO<EnemyUI>(1, "enemyui");
			enemyUI->SetLittleEnemy(littleEnemy);
			littleEnemy->m_enemyUI = enemyUI;   // ここ！ペア化
			m_enemyUIList.push_back(enemyUI);
			m_totalCount++;
			//m_spawnTimer = 0.0f;
		}

		///*m_totalCount++;
		m_spawnTimer = 0.0f;


	}
		
	if (!m_isBoss) {
		//ボス。
		BossEnemy* boss = NewGO<BossEnemy>(1, "bossEnemy");
		boss->SetPosition(BossRandom());
		m_bossEnemyList.push_back(boss);
		EnemyUI* enemyUI = NewGO<EnemyUI>(1,"enemyui");
		enemyUI->SetBossEnemy(boss);
		boss->m_enemyUI = enemyUI;   // ここ！ペア化
		m_enemyUIList.push_back(enemyUI);
		m_isBoss = true;
	}
}
//減った分の補充
void Game::CreateDeletedEnemy()
{
	//m_dieCount　倒された敵のカウント
	if (m_dieCount > 0) {
		for (int i = 0; i < m_dieCount; i++) {
			int r = rand() % 100;


			if (r >= 80) {
				//ウザイ敵。
				AnnoyingEnemy* annoying = NewGO<AnnoyingEnemy>(1, "annoyingEnemy");
				annoying->SetPosition(Random());
				m_annoyingEnemyList.push_back(annoying);
				EnemyUI* enemyUI = NewGO<EnemyUI>(1,"enemyui");
				enemyUI->SetAnnoyingEnemy(annoying);
				annoying->m_enemyUI = enemyUI;   // ここ！ペア化
				m_enemyUIList.push_back(enemyUI);
			}
			else if (r >= 40) {
				//普通の敵。
				Enemy* enemy = NewGO<Enemy>(1, "enemy");
				enemy->SetPosition(Random());
				m_enemyList.push_back(enemy);
				EnemyUI* enemyUI = NewGO<EnemyUI>(1,"enemyui");
				enemyUI->SetEnemy(enemy);
				enemy->m_enemyUI = enemyUI;   // ここ！ペア化
				m_enemyUIList.push_back(enemyUI);
			}
			else {
				//雑魚敵。
				LittleEnemy* little = NewGO<LittleEnemy>(1, "littleEnemy");
				little->SetPosition(Random());
				m_littleEnemyList.push_back(little);
				EnemyUI* enemyUI = NewGO<EnemyUI>(1, "enemyui");
				enemyUI->SetLittleEnemy(little);
				little->m_enemyUI = enemyUI;   // ここ！ペア化
				m_enemyUIList.push_back(enemyUI);
			}
		}
	}
}

void Game::UnlinkAllEnemyUI(Enemy* enemy) {
	for (auto* ui : m_enemyUIList) {
		if (ui->GetEnemy() == enemy) {
			ui->UnlinkEnemy();
		}
	}
}
void Game::UnlinkAllLittleEnemyUI(LittleEnemy* little) {
	for (auto* ui : m_enemyUIList) {
		if (ui->GetLittleEnemy() == little) {
			ui->UnlinkLittleEnemy();
		}
	}
}
void Game::UnlinkAllAnnoyingEnemyUI(AnnoyingEnemy* annoying) {
	for (auto* ui : m_enemyUIList) {
		if (ui->GetAnnoyingEnemy() == annoying) {
			ui->UnlinkAnnoyingEnemy();
		}
	}
}
void Game::UnlinkAllBossEnemyUI(BossEnemy* boss) {
	for (auto* ui : m_enemyUIList) {
		if (ui->GetBossEnemy() == boss) {
			ui->UnlinkBossEnemy();
		}
	}
}


void Game::EnemyManager()
{
	auto Normal_it = m_enemyList.begin();
	while (Normal_it != m_enemyList.end()) {
		Enemy* enemy = *Normal_it;
		if (enemy->m_isDead) {
			UnlinkAllEnemyUI(enemy);
			DeleteGO(enemy);
			Normal_it = m_enemyList.erase(Normal_it);
			if (m_isEndGame == false){
				m_totalCount--;  // ここで減らす！（Gameの側で）
			}
		}
		else {
			++Normal_it;
		}
	}

	auto Little_it = m_littleEnemyList.begin();
	while (Little_it != m_littleEnemyList.end()) {
		LittleEnemy* littleEnemy = *Little_it;
		if (littleEnemy->m_isDead) {
			UnlinkAllLittleEnemyUI(littleEnemy);
			DeleteGO(littleEnemy);
			Little_it = m_littleEnemyList.erase(Little_it);
			if (m_isEndGame == false) {
				m_totalCount--;  // ここで減らす！（Gameの側で）
			}
		}
		else {
			++Little_it;
		}
	}

	auto Fox_it = m_annoyingEnemyList.begin();
	while (Fox_it != m_annoyingEnemyList.end()) {
		AnnoyingEnemy* annoyingEnemy = *Fox_it;
		if (annoyingEnemy->m_isDead) {
			UnlinkAllAnnoyingEnemyUI(annoyingEnemy);
			DeleteGO(annoyingEnemy);
			Fox_it = m_annoyingEnemyList.erase(Fox_it);
			if(m_isEndGame==false){
			m_totalCount--;  // ここで減らす！（Gameの側で）
			}
		}
		else {
			++Fox_it;
		}
	}

	auto Boss_it = m_bossEnemyList.begin();
	while (Boss_it != m_bossEnemyList.end()) {
		BossEnemy* bossEnemy = *Boss_it;
		if (bossEnemy->m_isDead) {
			UnlinkAllBossEnemyUI(bossEnemy);
			DeleteGO(bossEnemy);
			Boss_it = m_bossEnemyList.erase(Boss_it);
			if (m_isEndGame == false) {
				m_isBoss = false;
			}
		}
		else {
			++Boss_it;
		}
	}

	auto Poison_it = m_poisonList.begin();
	while (Poison_it != m_poisonList.end()) {
		Poison*poison = *Poison_it;
		if (poison->m_isDelete) {
			DeleteGO(poison);
			Poison_it = m_poisonList.erase(Poison_it);
		}
		else {
			++Poison_it;
		}
	}
}

//void Game::DeleteAllEnemy()
//{
//	// Poison削除
//	for (auto* poison : m_poisonList)
//	{
//		DeleteGO(poison);
//		poison = nullptr;
//	}
//	m_poisonList.clear();
//
//	// UIやエフェクトも必要に応じて消す
//	for (auto* enemyUI : m_enemyUIList)
//	{
//		DeleteGO(enemyUI);
//		enemyUI = nullptr;
//	}
//	m_enemyUIList.clear();
//
//	// エネミー削除
//	for (auto* Normal : m_enemyList)
//	{
//		UnlinkAllEnemyUI(Normal);
//		DeleteGO(Normal);
//		Normal = nullptr;
//
//	}
//    m_enemyList.clear();
//	for (auto* Little : m_littleEnemyList)
//	{
//		UnlinkAllLittleEnemyUI(Little);
//		DeleteGO(Little);
//		Little = nullptr;
//	}
//    m_littleEnemyList.clear();
//	for (auto* Boss : m_bossEnemyList)
//	{
//		UnlinkAllBossEnemyUI(Boss);
//		DeleteGO(Boss);
//		Boss = nullptr;
//	}
//    m_bossEnemyList.clear();
//	for (auto* Annoying : m_annoyingEnemyList)
//	{
//		UnlinkAllAnnoyingEnemyUI(Annoying);
//		DeleteGO(Annoying);
//		Annoying = nullptr;
//	}
//	m_annoyingEnemyList.clear();
//}

//UI作成用関数。
void Game::CreateUI()
{
	//クロスヘアーを表示。
	m_crossHair = NewGO<CrossHair>(0, "crosshair");
	//月読の加護のUI。
	m_uiTukuyomi = NewGO<UItukuyomi>(0, "uitukuyomi");
	//スキルUI。
	m_uiSkill = NewGO<UIskill>(0, "uiskill");
	//しめ縄UI。
	m_uiSimenawa = NewGO<UISimenawa>(0, "uisimenawa");
	//呪ゲージ。
	m_uiCurseBar = NewGO<UIcurseBar>(0, "uicursebar");
	//MPゲージ。
	m_uiMPBar = NewGO<UIMPBar>(0, "uimpbar");
	//回復。
	m_uiHeal = NewGO <UIheal>(0, "uiheal");
	
}

void Game::ButtonUI()
{


	//通常攻撃
	m_fontNormalAttackButton.SetText(L":通常攻撃");
	m_fontNormalAttackButton.SetPosition(Vector3(-750.0f, -250.0f, 0.0f));
	m_fontNormalAttackButton.SetScale(1.0f);
	m_fontNormalAttackButton.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	//HP
	m_hp.SetText(L"HP:");
	m_hp.SetPosition(Vector3(-330.0f, -420.0f, 0.0f));
	m_hp.SetScale(1.0f);
	m_hp.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	//MP
	m_mp.SetText(L"MP:");
	m_mp.SetPosition(Vector3(-330.0f, -470.0f, 0.0f));
	m_mp.SetScale(1.0f);
	m_mp.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	//回復カウント
	m_healCount.SetText(L"回復回数");
	m_healCount.SetPosition(Vector3(-850.0f, -320.0f, 0.0f));
	m_healCount.SetScale(1.0f);
	m_healCount.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	//Xボタン
	m_buttonX.Init("Assets/sprite/X.DDS", 1920, 1080);
	m_buttonX.SetPosition({ 710.0f,-520.0f,0.0f });
	m_buttonX.SetScale({ 0.3f,0.3f,0.3f });
	m_buttonX.Update();

	//Yボタン
	m_buttonY.Init("Assets/sprite/Y.DDS", 1920, 1080);
	m_buttonY.SetPosition({ 420.0f,-520.0f,0.0f });
	m_buttonY.SetScale({ 0.3f,0.3f,0.3f });
	m_buttonY.Update();

	//LTボタン
	m_buttonLT.Init("Assets/sprite/LT.DDS", 1920, 1080);
	m_buttonLT.SetPosition({ 570.0f,-520.0f,0.0f });
	m_buttonLT.SetScale({ 0.3f,0.3f,0.3f });
	m_buttonLT.Update();

	//RTボタン
	m_buttonRT.Init("Assets/sprite/RT.DDS", 1920, 1080);
	m_buttonRT.SetPosition({ -830.0f,-280.0f,0.0f });
	m_buttonRT.SetScale({ 0.5f,0.5f,0.5f });
	m_buttonRT.Update();
}

void Game::UITimer()
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	//タイマーの表示。
	wchar_t wcsbuf[WCS_BUFFER_SIZE];

	int minute = (int)m_timer / SECONDS_IN_MINUTE;

	int sec = (int)m_timer % SECONDS_IN_MINUTE;
	swprintf_s(wcsbuf, WCS_BUFFER_SIZE, L"午前%01d時%02d分", minute, sec);

	//フォントを設定。
	m_timerFontRender.SetText(wcsbuf);
	//フォントの大きさを設定。
	m_timerFontRender.SetScale(SET_FONT_SCALE);
	//フォントの位置を設定。
	m_timerFontRender.SetPosition(FONT_RENDER_POSITION);
	//フォントの色を設定。
	m_timerFontRender.SetColor(g_vec4White);

	m_missionLantern.SetText(L"すべての灯籠に火を灯そう");
	m_missionLantern.SetPosition(Vector3(180.0f, 500.0f, 0.0f));
	m_missionLantern.SetScale(1.5f);
	m_missionLantern.SetColor({ 1.0f,0.5f,0.0f,1.0f });

	wchar_t wcsbuf2[256];
	swprintf_s(wcsbuf2, 256, L"残りの灯籠:%dコ", int(m_player->m_lanternMaxCount));

	//表示するテキストを設定。
	m_lanternCountFont.SetText(wcsbuf2);
	//フォントの位置を設定。
	m_lanternCountFont.SetPosition(Vector3(200.0f, 430.0f, 0.0f));
	//フォントの大きさを設定。
	m_lanternCountFont.SetScale(1.0f);
	//フォントの色を設定。
	m_lanternCountFont.SetColor({ 1.0f,1.0f,1.0f,1.0f });
}

void Game::HitCrossHair()
{

}

void Game::NotifiyEnemy()
{
	//ゲーム開始から30秒経ったら。
	if (m_timer >=ENEMY_SPAWN_TIME)
	{
		////エネミーの作成。
		//CreateEnemy();
		//敵が来たことを通知する。
		m_notifyEnemyFontRender.SetText(L"敵が来るぞ");
		m_notifyEnemyFontRender.SetColor(g_vec4Red);
		m_notifyEnemyFontRender.SetScale(SET_FONT_NOTIFY_SCALE);
		if (!m_isGameBGM) {
			//ステージ用のBGMを鳴らす。
			g_soundEngine->ResistWaveFileBank(62, "Assets/sound/game.wav");
			m_stage = NewGO<SoundSource>(62);
			m_stage->Init(62);
			m_stage->Play(false);
			m_isGameBGM = true;
		}
		m_isShowNotify = true;
	}

	if (m_isShowNotify)
	{
		m_notifyx -= NOTIFY_SCROLL_SPEED * g_gameTime->GetFrameDeltaTime();
		m_notifyEnemyFontRender.SetPosition(m_notifyx, NOTIFY_POSITION_Y, 0.0f);

		if (m_notifyx < NOTIFY_POSITION_X)
		{
			m_isShowNotify = false;
		}
	}
}

void Game::SpriteFade()
{
	
	//スプライトのフェードインの処理。
	if (!m_isSpriteFade)
	{
		m_spriteColor.r += 0.01f * m_fadeTime / m_fadeMaxTime;
		m_spriteColor.g += 0.01f * m_fadeTime / m_fadeMaxTime;
		m_spriteColor.b += 0.01f * m_fadeTime / m_fadeMaxTime;
		m_spriteColor.a += 0.01f * m_fadeTime / m_fadeMaxTime;
		m_spriteRender.SetMulColor(m_spriteColor);
		if (m_spriteColor.a >= 1.0f)
		{
			m_isSpriteFade = true;
			m_spriteColor.r = 1.0f;
			m_spriteColor.g = 1.0f;
			m_spriteColor.b = 1.0f;
			m_spriteColor.a = 1.0f;
			m_spriteRender.SetMulColor(m_spriteColor);
		}
	}

}

void Game::Render(RenderContext& rc)
{
	m_timerFontRender.Draw(rc);
	m_notifyEnemyFontRender.Draw(rc);
	m_fontNormalAttackButton.Draw(rc);
	m_buttonX.Draw(rc);
	m_buttonY.Draw(rc);
	m_buttonLT.Draw(rc);
	m_buttonRT.Draw(rc);
	m_healCount.Draw(rc);
	m_hp.Draw(rc);
	m_mp.Draw(rc);
	if (!m_player->m_enemyIsCanAttack) {
		m_missionLantern.Draw(rc);
		m_lanternCountFont.Draw(rc);
	}
	if (m_timer < 300.0f) {
		m_missionTask.Draw(rc);
		m_adviceMP.Draw(rc);
	}
	m_gameClearFont.Draw(rc);
	m_spriteRender.Draw(rc);	
	
}