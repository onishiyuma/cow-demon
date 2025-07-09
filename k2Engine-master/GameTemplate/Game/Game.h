#pragma once
#include "sound/SoundSource.h"
#include "Level3DRender/LevelRender.h"
#include <vector>

class Player;
class GameCamera;
class BackGround;
class Enemy;
class BossEnemy;
class CrossHair;
class Shimenawa;
class Stone;
class UIStone;
class Lantern;
class LanternLight;
class BlueFlame;
class RedFlame;
class LanternArrow;
class RingBell;
class Mountain;
class Tree;
class GameClear;
class GameOver;
class LittleEnemy;
class Poison;
class AnnoyingEnemy;
class UItukuyomi;
class UIskill;
class UISimenawa;
class UIcurseBar;
class UIheal;
class UIMPBar;
class MiniMap;
class EnemyUI;
class Load;
class UIOne;
class UITwo;
class UIThree;
class UIZero;
class TimeLimit;

class Game : public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	//オブジェクトを作成。
	void CreateObject();
	//火打石の生成。
	void CreateStone();
	//灯籠の生成。
	void CreateLantern();
	//UIの作成。
	void CreateUI();
	//ボタンを押すUIの作成。
	void ButtonUI();
	//UIのタイマー。
	void UITimer();
	//敵が照準の中に入ったか。
	void HitCrossHair();
	//敵の出現を通知。
	void NotifiyEnemy();
	//敵の生成。
	void CreateEnemy();
	//死んだ敵の数分敵を作成する。
	void CreateDeletedEnemy();
	//敵の動作を管理する。
	void GameManager();
	//灯籠用ライトのステート。
	void LanternLightState();
	//灯籠用ライトの作成。
	void CreateLanternLight();
	//灯籠用エフェクトの作成。
	void CreateLanternEffect();
	//灯籠用矢印の作成。
	void CreateLanternArrow();
	//灯籠のMP回復用ステート。
	void LanternMPState();
	//灯籠のMP回復用処理。
	void LanternHealMP();
	//空の明るさ調整用関数。
	void SetSkyLight();
	//カウントダウンの開始。
	void StartCountDown();
	//エネミーの管理
	void EnemyManager();
	//クリア後のスプライトフェード処理。
	void SpriteFade();
	//EnemyUIの切断用関数
	void UnlinkAllEnemyUI(Enemy* enemy);
	//LittleEnemyUIの切断用関数
	void UnlinkAllLittleEnemyUI(LittleEnemy* little);
	//狐のUIの切断用関数
	void UnlinkAllAnnoyingEnemyUI(AnnoyingEnemy* annoying);
	//ボスのUI切断用関数
	void UnlinkAllBossEnemyUI(BossEnemy* boss);


	//敵のリスト。
	std::vector<Enemy*>   m_enemyList;
	//小さい敵のリスト。
	std::vector<LittleEnemy*> m_littleEnemyList;
	//ボスのリスト。
	std::vector<BossEnemy*> m_bossEnemyList;
	//ウザイ敵のリスト。
	std::vector<AnnoyingEnemy*> m_annoyingEnemyList;
    //敵のUIリスト。
	std::vector<EnemyUI*>m_enemyUIList;	
	//ポイズンのリスト。
	std::vector<Poison*> m_poisonList;


	//敵のリストを取得する関数。
	const std::vector<Enemy*>& GetEnemies()const
	{
		return m_enemyList;
	}

	//小さい敵のリストを取得する関数。
	const std::vector<LittleEnemy*>& GetLittleEnemies() const
	{
		return m_littleEnemyList;
	}

	//ボスのリストを取得する関数。
	const std::vector<BossEnemy*>& GetBossEnemy() const
	{
		return m_bossEnemyList;
	}

	//ウザイ敵のリストを取得する関数。
	const std::vector<AnnoyingEnemy*>& GetAnnoyingEnemy() const
	{
		return m_annoyingEnemyList;
	}
	//エネミーのUIリストを取得する関数。
	const std::vector<EnemyUI*>& GetEnemyUI() const
	{
		return m_enemyUIList;
	}
	const std::vector<Poison*>& GetPoisonUI() const
	{
		return m_poisonList;
	}

	//メンバ変数。
	bool					m_isBoss = false;					//ボスかどうか。
	bool					m_isCowntDownStart = false;			//カウントダウン中かどうか
	bool					m_isLoad = true;					//ゲーム開始前でロードが終わっているか
	bool                    m_isEndGame = false;                //ゲームが終了しているかどうか
	float					m_luminance = 0.0f;					//空の明るさの変化量。
	int						m_dieCount = 0;						//倒された敵の数。
	int						m_maxCount = 0;						//敵の最大数。
	int						m_totalCount = 0;					//敵の合計。
private:
	GameClear*				m_gameClear;						//ゲームクリアー。
	RingBell*				m_ringBell;							//鈴。
	BackGround*				m_backGround;						//背景。
	Mountain*				m_mountain;							//山。
	Tree*					m_tree;								//木。
	GameCamera*				m_gameCamera;						//ゲームカメラ。
	Player*					m_player;							//プレイヤー。
	Enemy*					m_enemy;							//敵。
	LittleEnemy*			m_littleEnemy;						//小さい敵。
	AnnoyingEnemy*			m_annoyingEnemy;					//嫌な敵。
	BossEnemy*				m_bossEnemy;						//ボス。
	CrossHair*				m_crossHair;						//クロスヘアー。
	ModelRender				m_modelRender;						//モデルレンダー。
	Shimenawa*				m_shimenawa;						//しめ縄。
	Load*					m_load;								//ロード。
	SkyCube*				m_skyCube;							//スカイキューブ。
	SoundSource*			m_gameStartSound;					//ゲームスタート音。
	SoundSource*			m_stage; 							//ゲームスタート音。
	SoundSource*            m_clearBGM;							//ゲームBGM。	
	//火打石。
	Stone*					m_stone1;							//火打石。
	Stone*					m_stone2;							//火打石。
	Stone*					m_stone3;							//火打石。
	Stone*					m_stone4=nullptr;					//火打石。
	Stone*					m_stone5=nullptr;					//火打石。
	Stone*					m_stone6=nullptr;					//火打石。
	Stone*					m_stone7=nullptr;					//火打石。
	//灯籠。
	Lantern*				m_lantern;							//灯籠。
	Lantern*				m_lantern1;							//灯籠。
	Lantern*				m_lantern2;							//灯籠。
	Lantern*				m_lantern3;							//灯籠。
	Lantern*				m_lantern4;							//灯籠。
	//灯籠の位置を示す矢印。
	LanternArrow*			m_lanternArrow1;					//灯籠矢印。
	LanternArrow*			m_lanternArrow2;					//灯籠矢印。
	LanternArrow*			m_lanternArrow3;					//灯籠矢印。
	LanternArrow*			m_lanternArrow4;					//灯籠矢印。
	//灯籠用ライト。
	LanternLight*			m_lanternLight1;					//灯籠用ライト。
	LanternLight*			m_lanternLight2;					//灯籠用ライト。
	LanternLight*			m_lanternLight3;					//灯籠用ライト。
	LanternLight*			m_lanternLight4;					//灯籠用ライト。
	//青い炎。
	BlueFlame*				m_blueFlame1;						//青い炎。
	BlueFlame*				m_blueFlame2;						//青い炎。
	BlueFlame*				m_blueFlame3;						//青い炎。
	BlueFlame*				m_blueFlame4;						//青い炎。
	//UI。
	UItukuyomi*				m_uiTukuyomi;						//月読の加護のUI
	UIskill*				m_uiSkill;							//スキルのUI
	UISimenawa*				m_uiSimenawa;						//しめ縄のUI
	UIcurseBar*				m_uiCurseBar;						//呪いバーのUI
	UIMPBar*				m_uiMPBar;							//MPバーのUI
	UIheal*					m_uiHeal;							//回復のUI
	EnemyUI*				m_enemyUI;							//敵UI。
	UIStone*				m_uiStone;							//火打石UI。
	//カウントダウン用。
	UIThree*				m_uiThree = nullptr;				//カウントダウン3。
	UITwo*					m_uiTwo = nullptr;					//カウントダウン2。
	UIOne*					m_uiOne = nullptr;					//カウントダウン1。
	UIZero*					m_uiZero = nullptr;					//カウントダウン0。
	//タイムリミットを知らせるUI。
	TimeLimit*				m_timeLimit1;						//タイムリミット用UI。
	//スプライトレンダー・フォントレンダー。
	SpriteRender			m_spriteRender;						//スプライトレンダー。
	FontRender				m_timerFontRender;					//フォントレンダー。
	FontRender				m_notifyEnemyFontRender;			//敵出現通知用フォントレンダー。
	FontRender				m_fontNormalAttack;					//通常攻撃用フォントレンダー。
	FontRender              m_missionLantern;					//灯籠ミッション用フォントレンダー。
	FontRender              m_lanternCountFont;
	FontRender              m_lanternClear;					    //灯籠クリア用フォントレンダー。
	FontRender              m_missionTask;					    //「5時まで本殿を守ろう」用フォントレンダー。
	FontRender              m_gameClearFont;                    //「あなたは本殿を守り抜いた」
	FontRender              m_adviceMP;					        //MP回復のアドバイス用フォントレンダー。
	FontRender              m_hp;					            //HPのフォントレンダー。
	FontRender			    m_mp;					            //MPのフォントレンダー。
	FontRender              m_healCount;                        //回復のフォントレンダー。
	//ボタンUIの表示。
	SpriteRender			m_buttonB;							//Bボタン。
	FontRender				m_fontNormalAttackButton;			//通常攻撃用フォントレンダー。
	SpriteRender			m_buttonX;							//Xボタン。
	SpriteRender			m_buttonY;							//Yボタン。
	SpriteRender			m_buttonLT;							//LTボタン。
	SpriteRender			m_buttonRT;							//RTボタン。
	Vector3					m_EnemyRandompos;					//敵の座標。
	Vector3					Random();							//ランダムに敵を出現させる。
	Vector3                 BossRandom();						//ボスのランダム座標。
	Vector4                 m_spriteColor = { 0.0f,0.0f,0.0f,0.0f };//スプライトの色。
private:
	int						m_lanternLightState = 0;			//灯籠の光状態。
	int						m_spawnCount=0;						//出現した敵の数。
	int						m_lanternEffectState = 0;			//灯籠のエフェクト状態。
	int						m_endTimer = 0;						//ゲーム終了までの時間。
	int						m_timerCount = 0;					//タイマーのカウント。
	float					m_countDownTimer = 3.0f;			//カウントダウン時間。
	float					m_timer = 120.0f;					//タイマー。
	float					m_timeLimit = 0;					//タイムリミット。
	float					m_spawnTimer = 0.0f;				//敵出現タイマー。
	float                   m_EndTimer = 0.0f;
	float                   m_healMPTimer = 0.0f;				//MP回復タイマー。
	float					m_skyLuminance = 0.0002f;			//空の明るさ。
	float					m_skyAmbient = 0.0002f;				//空の明るさの影響を受ける環境光。
	float					m_notifyx = 0.0f;					//敵出現通知のX座標。	
	float                   m_skyTimer = 0.0f;					//空の明るさの変化タイマー。
	const float             m_fadeTime = 1.0f;					//フェード時間。	
	const float				m_fadeMaxTime = 5.0f;				//カウントダウン時間。
	const float				m_nightStart = 0.0f;				//始まり
	const float				m_phase1Start = 120.0f;				//夜明けの始まり。
	const float				m_phase2Start = 180.0f;				//少し明るくなる。
	const float				m_phase3Start = 210.0f;				//少し明るくなる。
	const float				m_phase4Start = 240.0f;				//日の出開始。
	const float				m_phase5Start = 250.0f;				//少しずつ明ける。
	const float				m_phase6Start = 260.0f;				//少しずつ明ける。
	const float				m_phase7Start = 270.0f;				//少しずつ明ける。
	const float				m_dayStart = 290.0f;				//朝になる。
	const float				m_luminanceNight = 0.0003f;			//夜の明るさ。
	const float				m_luminanceMidNight1 = 0.0005f;		//夜の明るさ。
	const float				m_luminanceMidNight2 = 0.0007f;		//夜の明るさ。
	const float				m_luminanceSunrise = 0.001f;		//日の出。
	const float				m_luminanceDawn1 = 0.005f;			//夜明け。
	const float				m_luminanceDawn2 = 0.007f;			//夜明け。
	const float				m_luminanceDawn3 = 0.01f;			//夜明け。
	const float				m_luminanceDay = 0.05f;				//朝（最大）。
	bool					m_islanternAction = false;			//灯籠のアクションかどうか。
	bool					m_isShowNotify=false;				//敵出現通知を表示するかどうか。
	//灯籠用ライトのフラグ。
	bool					m_lanternLightFlag = false;
	bool					m_lanternLightFlag1 = false;
	bool					m_lanternLightFlag2 = false;
	bool					m_lanternLightFlag3 = false;
	bool					m_lanternLightFlag4 = false;
	//灯籠用エフェクトのフラグ。
	bool					m_lanternEffectFlag1 = false;
	bool					m_lanternEffectFlag2 = false;
	bool					m_lanternEffectFlag3 = false;
	bool					m_lanternEffectFlag4 = false;
	//灯籠用MP回復のフラグ。
	int				        m_lanternMPState = 0;				//灯籠のMP回復状態。
	bool					m_isLanternHealMP1 = false;			//灯籠のMP回復フラグ。
	bool					m_isLanternHealMP2 = false;			//灯籠のMP回復フラグ。
	bool					m_isLanternHealMP3 = false;			//灯籠のMP回復フラグ。
	bool					m_isLanternHealMP4 = false;			//灯籠のMP回復フラグ。
	//空の明るさのフラグ。
	bool					m_isNight = false;
	bool					m_isMidNight1 = false;
	bool					m_isMidNight2 = false;
	bool					m_isSunrise = false;
	bool					m_isDawn1 = false;
	bool					m_isDawn2 = false; 
	bool					m_isDawn3 = false;
	bool					m_isDay = false;
	//その他のフラグ。
	bool					m_isCountDownEnd = false;			//カウントダウン終了かどうか。
	bool					m_isOne = false;					//あと一秒かどうか。
	bool					m_isTwo = false;					//あと二秒かどうか。
	bool					m_isThree = false;					//あと三秒かどうか。
	bool					m_isGameStart = false;				//ゲームスタートフラグ。
	bool					m_isTimeLimit = false;				//タイムリミットかどうか。
	bool                    m_isDeathPlayer = false;			//プレイヤーが死んだかどうか。
	bool                    m_isInovate = false;                //
	bool                    m_GameDelete = false;				//ゲーム終了フラグ。
	bool                    m_isSpriteFade = false;				//スプライトフェードフラグ。
	bool                    m_isGameBGM = false;				//ゲームBGM。
	bool                    m_isGameClear = false;				//ゲームクリアフラグ。
};


