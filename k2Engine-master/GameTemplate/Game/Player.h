#pragma once

class GameManagement;
class Tutorial;
class Game;
class Shimenawa;
class GameCamera;
class PlayerLight;
class Lantern;
class UIheal;
class RingBell;
class GameCamera;
class BellSpriteRender;
class NoHeal;
class SpinStick;
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundSource.h"

class Player :public IGameObject
{	
public:
	enum enPlayerState
	{
		enPlayerState_None,			//何もない状態。
		enPlayerState_Poison,		//毒状態。
	};

	Player();
	~Player();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	//通常攻撃。
	void NormalAttack();
	//スキル。
	void Skill();
	//月読の加護。
	void SkillTukuyomiBlessing();
	//しめ縄。
	void ItemShimenawa();
	//通常攻撃作成。
	void MakeNormalAttack();
	//スキル作成。
	void MakeSkill();
    //月読の加護作成。
    void MakeTukuyomiBlessing();
	//しめ縄作成。
	void MakeShimenawa();
	//移動。
	void Move();
	//当たり判定。
	void Collision();
	//距離計算。
	void Distance();
	//カメラの回転。
	void RotationCamera();
	//HPの回復。
	void HealHP(int amount);
	//ステータスを更新する。
	void UpdateHealHint();
	//プレイヤーの攻撃。
	void PlayerAttack();
	//プレイヤーが毒状態の処理。
	void PoisonState();
	//鈴を鳴らすコリジョン。
	void RingBellCollision();
	//敵の攻撃判定用コリジョン。
	void EnemyAttackCollision();
	//ウザイ敵の攻撃判定用コリジョン。
	void AnnoyingEnemyAttackCollision();
	//ボスの攻撃判定用コリジョン
	void BossEnemyAttackCollision();
	//ボスの毒攻撃判定用コリジョン。
	void BossEnemyPoisonCollision();
	//小さい敵の毒攻撃判定用コリジョン。
	void LittleEnemyPoisonCollision();
	//爆発攻撃判定用コリジョン。
	void ExplosionCollision();
	//エフェクトの作成。
	void CreateEffect();




	//座標を取得。
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	//座標を設定。
	void SetPosition(Vector3 position)
	{
		m_position = position;
	}

public:
	//メンバ変数。
	SoundSource*		m_nomalAttack;								//通常攻撃の音。
	SoundSource*		m_skill;									//スキルの音。
	SoundSource*		m_simenawa;									//しめ縄の音。
	SoundSource*		m_hell;										//回復の音。
	enPlayerState		m_playerState = enPlayerState_None;			//プレイヤーの状態。
	Vector3				m_position = Vector3::Zero;					//座標。
	EffectEmitter*		m_effectEmitter = nullptr;                  //エフェクト参照。
	const float			m_collectTime = 15.0f;						//しめ縄を取る時間。
	const float			m_tukuyomiMax = 0.0f;						//月読の加護の最大値。
	const int			m_playerATK = 3;							//プレイヤーの攻撃力。
	const int			m_skillMax = 100;							//スキルの最大値。
	const int			m_skillMagnification = 1000;				//スキルの倍率。
	const float			m_TukuyomiMagnification = 0.5;				//月読の加護の倍率。
	const int			m_criticalRate = 20;						//クリティカル率。
	const int			m_cliticalDamage = 2;						//クリティカルダメージ。
	float				m_tukuyomiBlessingCoolDown = 0.0f;			//月読の加護のクールダウン。
	float				m_shimenawaGetTime = 0.0f;					//しめ縄を取る時間。
	bool				m_enemyIsCanAttack = false;					//敵に攻撃できるか。
	bool				m_isDisplay = false;						//表示するか。
	int					m_playerHP = 0;								//プレイヤーのHP。
	int					m_skillCharge = 0;							//スキルチャージ。
	int					m_normalATK = 0;							//通常攻撃。
	int					m_criticalATK = 0;							//クリティカル攻撃。
	int					m_skillATK = 100;							//スキル攻撃力。
	int					m_stoneCount = 0;							//火打石の所持数。
	int					m_tukuyomiATK = 5;							//月読の加護の攻撃力。
	int					m_lanternCount = 0;							//灯籠の灯っている数。
	int                 m_playerMaxMP = 100;						//プレイヤーの最大MP。
	int                 m_playerMP;								    //プレイヤーのMP。
private:
	NoHeal*				m_noHeal;									//回復できない。
	BellSpriteRender*	m_bellSpriteRender;							//鈴を使う画像。
	RingBell*			m_ringBell;									//鈴。
	UIheal*				m_uiHeal;									//回復のUI。
	SpinStick*			m_spinStick;								//「スティックを回せ」の画像。
	Lantern*			m_lantern;									//灯籠。
	GameCamera*			m_gameCamera;								//ゲームカメラ。
	Shimenawa*			m_shimenawa;								//しめ縄。
	ModelRender			m_modelRender;								//モデルレンダー。
	CharacterController m_characterController;						//キャラコン。
	FontRender			m_fontRender1;								//フォントレンダー。
	FontRender			m_fontRender2;								//フォントレンダー。
	PlayerLight*		m_playerLight;								//プレイヤーのライト。
	Tutorial*			m_tutorial;									//チュートリアルモード。
	Game*               m_game;										//ゲーム。
	GameManagement*     m_gameManagement;                           //ゲームの流れ管理。
	Vector3				m_forward = Vector3::AxisZ;					//方向。
	Vector3				m_moveSpeed;								//移動速度。
	const float			m_gravity = 10.5f;							//重力。
	const float			m_contactThresholdSq = 100.0f * 100.0f;		//接触の閾値。
	const float			m_poisonDuration = 4.0f;					//毒状態の時間。
	const float			m_invincibleTimeDuration=1.0f;				//無敵の継続時間。
	const int			m_poisonDamage = 1;							//毒ダメージ。
	const int			m_charaConRadius = 25;						//キャラコンの半径。
	const int			m_charaConHeight = 75;						//キャラコンの高さ。
	float				m_attackCoolDown = 0.0f;					//通常攻撃のクールダウン。
	float				m_healCoolDown = 0.0f;						//回復のクールダウン。
	float				m_deleteTimer = 0.0f;						//削除のタイマー。
	float				m_totalRotation = 0.0f;						//カメラの回転量。
	float				m_prevStickAngle = 0.0f;					//スティックの前の角度。
	float				m_distSq = 0.0f;							//距離の二乗。
	float				m_poisonTimer = 0.0f;						//毒状態のタイマー。
	float				m_poisonCoolDown = 0.0f;					//毒状態のクールダウン。
	float				m_invincibleTime_Enemy = 0.0f;				//敵の攻撃の無敵時間。
	float				m_invincibleTime_Annoying = 0.0f;			//ウザイ敵の攻撃の無敵時間。
	float               m_invincibleTime_BossEnemy = 0.0f;			//ボス敵の攻撃の無敵時間。
	float				m_invincibleTime_BossPoison = 0.0f;			//ボスの毒攻撃の無敵時間。
	float				m_invincibleTime_LittlePoison = 0.0f;		//小さい敵の毒攻撃の無敵時間。
	float				m_invincibleTime_Explosion = 0.0f;			//爆発攻撃の無敵時間。
	int					m_playerMaxHP = 100;						//プレイヤーの最大体力。
	bool				m_isDeleted = false;						//消されるか。
	bool				m_isRotating = false;						//回転中か。
	bool				m_isDamage_Enemy = false;					//敵からダメージを受けているか。
	bool                m_isDamage_BossEnemy = false;				//ボス敵からダメージを受けているか。
	bool				m_isDamage_Annoying = false;				//ウザイ敵からダメージを受けているか。
	bool				m_isDamage_BossPoison = false;				//ボスの毒ダメージを受けているか。
	bool				m_isDamage_LittlePoison = false;			//小さい敵の毒ダメージを受けているか。
	bool				m_isDamage_Explosion = false;				//爆発ダメージを受けているか。
	bool				m_isBellHit = false;						//回復用コリジョンに当たっているか。
	bool				m_isHealMode = false;						//回復モード。
};
