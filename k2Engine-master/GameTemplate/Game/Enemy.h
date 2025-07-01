#pragma once
#include "EnemyBase.h"
#include "graphics/effect/EffectEmitter.h"
class GameManagement;
class Player;
class BackGround;
class Collision;
class RingBell;
class EnemyBase;
class Tutorial;
class Game;
class GameCamera;
class GameOver;
class LanternAttack;
class EnemyUI;

class Enemy : public EnemyBase
{

public:
		//敵の状態を表す列挙型。
	enum EnEnemyState {
		enEnemyState_Idle,			//待機中。
		enEnemyState_Honden,		//本殿を目指す。
		enEnemyState_Chase,			//プレイヤーを追跡。
		enEnemyState_Attack,		//攻撃中。
		enEnemyState_Damage,		//ダメージを受けた状態。
		enEnemyState_Down			//ダウン状態か。
	};

	//アニメーション。
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Run,
		enAnimationClip_Attack,
		enAnimationClip_Damage,
		enAnimationClip_Down,
		enAnimationClip_Num
	};

public:
	Enemy();
	virtual ~Enemy();
	bool Start() override;
	void Update() override;
	void Rotation() override;
	void Render(RenderContext& rc) override;

	//座標をセット。
	void SetPosition(const Vector3& position) 
	{
		m_position = position; 
	}

	//回転をセット。
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	//大きさをセット。
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	void SetHP(const int hp)
	{
		m_enemyHP = hp;
	}

    bool IsDead() const
	{
		return m_isDeadFlag;
	}

	//座標を取得。
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	float GetHP()const
	{
		return	m_enemyHP;
	}

	float GetMaxHP()const
	{
		return m_enemyMaxHP;
	}

	

	//行動ロジック。
	void Chase() override;						//追跡。
	const bool SearchPlayer() const override;   //探す。
	const bool SearchMain() const;				//本殿を探す。
	void IsHonden();                            //本殿へ行く処理。
	void DeathEffect();                        //死亡エフェクト。

	//状態遷移処理。
	void ManageState() override;
	void ProcessCommonStateTransition() override;
	void ProcessIdleStateTransition() override;
	void ProcessChaseStateTransition() override;
	void ProcessAttackStateTransition();
	void ProcessDamageStateTransition() override;
	void ProcessMainStateTransition();
	void ProcessDownStateTransition() override;

	//アニメーション処理。
	void PlayAnimation() override;
	void OneAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)override;

	//攻撃処理。
	void Attack();
	void MakeAttackCollision(); //攻撃用コリジョン。
	const bool IsCanAttack() const;

	//コリジョン処理。
	void Collision() override;
	

private:
	//メンバ変数。
	GameManagement*     m_gameManagement = nullptr;
	GameCamera*			m_gameCamera = nullptr;						//ゲームカメラ。
	Player*				m_player = nullptr;							//プレイヤー。
	RingBell*			m_ringBell = nullptr;						//鈴。

	
	Game*				m_game = nullptr;							//ゲーム。
	EffectEmitter* m_effectEmitter = nullptr;					//エフェクトエミッター。
	GameOver*           m_gameOver = nullptr;						//ゲームオーバー。
	LanternAttack*      m_lanternAttack;

	AnimationClip		m_animationClips[enAnimationClip_Num];		//アニメーションデータ。
	ModelRender			m_modelRender;								//モデルレンダー。

	Vector3				m_position;									//現在位置。
	Vector3				m_farstPosition = Vector3::Zero;			//初期位置。
	Vector3				m_forward = Vector3::AxisZ;					//向きベクトル。
	Vector3				m_moveSpeed;								//移動速度。
	const Vector3		m_stopMove = Vector3::Zero;					//動いていない。
	Vector3				m_scale;									//モデルのスケール。
	Quaternion			m_rotation;									//回転。

	EnEnemyState		m_enemyState = enEnemyState_Idle;			//ステータス。


	int					m_enemyHP = 10;								//体力。
	int                 m_enemyMaxHP = m_enemyHP;					//最大体力。
	const int			m_enemyATK = 5;								//敵の攻撃力。									
	

	int					m_isUnderAttack = false;					//攻撃を受けているか
	int					m_FangBoneId = -1;							//攻撃判定を出すボーンID
	

	float				m_idleTimer = 0.0f;							//待機状態の経過時間。
	float				m_chaseTimer = 0.0f;						//追跡状態の経過時間。
	float				m_hondenTimer = 0.0f;						//本殿移動状態の経過時間。
	float				m_stopTimer = 0.0f;							//拘束状態の経過時間。
	float               m_deathEffectTimer = 0.0f;                  // 死亡エフェクトの表示時間

	bool				m_isStopped = false;						//拘束状態。
	bool				m_isGameOver = false;						//ゲームオーバーか。
	public:
	EnemyUI* m_enemyUI = nullptr;
	bool                m_isDeadFlag = false;                       //死亡フラグ。
	bool m_isDead = false;
	bool m_isDeleted = false; // 削除フラグ
};