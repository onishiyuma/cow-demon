#pragma once
#include "graphics/effect/EffectEmitter.h"
#include "EnemyBase.h"
#include "Game.h"


class Poison;
class Collision;
class EnemyBase;
class Player;
class Game;
class EnemyUI;
class GameCamera;
class RingBell;
class LanternAttack;

class LittleEnemy :public EnemyBase
{
public:
	//敵のステータスの列挙型。
	enum EnEnemyState {
		enEnemyState_Idle,			//静止状態。
		enEnemyState_Chase,			//追跡状態。
		enEnemyState_Honden,        //本殿を目指す状態
		enEnemyState_Poison,		//毒攻撃状態。
		enEnemyState_Damage,		//ダメージ状態。
		enEnemyState_Down			//ダウン状態。
	};
	///アニメーションの種類。
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Run,
		enAnimationClip_Poison,
		enAnimationClip_Damage,
		enAnimationClip_Down,
		enAnimationClip_Num
	};

public:
	LittleEnemy();
	virtual ~LittleEnemy();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc);

	//ボス専用の処理。
	void PoisonAttack();                        //毒攻撃。
	void ManageState() override;                //状態管理。
	void Chase() override;                      //追跡行動。
	void Collision() override;                  //衝突処理。
	void Rotation() override;                   //当たり判定処理。
	const bool SearchPlayer() const override;   //プレイヤー探索。
	const bool IsCanAttack() const;             //攻撃可能判定。
	void PlayAnimation() ;              //アニメーション再生。
	void MakePoison();                          //毒の生成。
	void DeathEffect();                        //死亡エフェクト。
	const bool SearchMain() const;            //本殿を探す。
	void IsHonden();                            //本殿へ行く処理。

	//各ステートの遷移処理。
	void ProcessIdleStateTransition() override;         //待機。
	void ProcessPoisonAttackStateTransition();          //毒攻撃。
	void ProcessDamageStateTransition() override;       //被ダメージ。
	void ProcessHondenStateTransition();                //本殿移動
	void ProcessChaseStateTransition() override;        //追跡。
	void OneAnimationEvent(const wchar_t* clipName, const wchar_t* eventName) ; //アニメーションイベント。
	void ProcessCommonStateTransition() override;       //共通処理。
	void ProcessDownStateTransition() override;         //ダウン。

	//座標をセットする関数。
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}	

	const Vector3& GetPosition()const
	{
		return m_position;
	}

	//回転をセットする関数。
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	//大きさをセットする関数。
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	bool IsDead() const
	{
		return m_isDeadFlag;
	}

	float GetHP()const
	{
		return	m_enemyHP;
	}

	float GetMaxHP()const
	{
		return m_enemyMaxHP;
	}

	
private:
	//メンバ変数
	Vector3 m_position;
	Vector3 m_scale;
	Quaternion m_rotation;
	/*Player* m_player=nullptr;*/
	EffectEmitter* m_effectEmitter = nullptr;	//エフェクトの参照
	Game* m_game = nullptr;
	GameCamera*			m_gameCamera=nullptr;								//カメラ。
	RingBell*           m_ringBell = nullptr;						//鈴。
	LanternAttack*      m_lanternAttack;
	
	AnimationClip		m_animationClips[enAnimationClip_Num];		//アニメーションのクリップ。
	EnEnemyState		m_enemyState = enEnemyState_Idle;			//敵の状態。
	const Vector3		m_stopMove = Vector3::Zero;					//動きを完全停止。
	int                 m_enemyHP = 10;                             //体力
	int                 m_enemyMaxHP = m_enemyHP;                   //最大体力
	float				m_leaveTimer = 0.0f;						//退散時間。
	float				m_idleTimer = 0.0f;							//待機時間。
	float				m_ChaseTimer = 0.0f;						//追跡時間。
	float				m_poisonAttackCoolDown = 0.0f;				//毒攻撃のクールダウン。
	float				m_stopTimer = 0.0f;							//拘束時間。
	float				m_mainTimer = 0.0f;							//本殿の時間。
	float               m_hondenTimer = 0.0f;
	float               m_deathEffectTimer = 0.0f;                  // 死亡エフェクトの表示時間
	bool				m_isStopped = false;						//動いているか。
	bool				m_gameoverFlag = false;						//ゲームオーバーか。
	bool				m_isUnderAttack = false;					//攻撃を受けたか。
	public:
	bool m_isDeadFlag = false;					//死亡フラグ。
	bool m_isDead = false;
	bool m_isDeleted = false; // メンバ追加
    EnemyUI*            m_enemyUI = nullptr;						//敵のUI。
};


