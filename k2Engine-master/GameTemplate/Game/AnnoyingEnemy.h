#pragma once
#include "graphics/effect/EffectEmitter.h"
#include "EnemyBase.h"
#include "Game.h"
#include "EnemyUI.h"

class Poison;
class Collision;
class Player;
class Game;
class GameCamera;
class RingBell;
class EnemyUI;
class AnnoyingEnemy : public EnemyBase
{
public:
	//敵の状態を定義する列挙型。
	enum EnEnemyState {
		enEnemyState_Idle,				//待機中。
		enEnemyState_Main,				//本殿へ行く。
		enEnemyState_Chase,				//追跡。
		enEnemyState_Explode,			//爆発。
		enEnemyState_Poison,			//毒攻撃。
		enEnemyState_Damage,			//ダメージを受けている。
		enEnemyState_Down			    //倒されている状態。
	};

public:
	//メンバ関数。
	bool Start() override;
	AnnoyingEnemy();
	~AnnoyingEnemy();
	// 基本処理。
	void Update() override;

	void MakeExplosion();						//爆発コリジョンとエフェクトを作成。
	void DeathEffect();                         //死亡エフェクト生成。        
	void ManageState() override;				//状態管理。
	void Chase() override;						//追跡行動。
	void Collision() override;					//衝突処理。
	void Rotation() override;					//向きの更新処理。
	const bool SearchPlayer() const override;	//プレイヤーの探索
	const bool IsCanAttack() const;				//攻撃可能かどうかを判定。
	const bool SearchHonden() const;            //本殿を探す。
	void IsHonden();                            //本殿へ行く処理。
	void PlayAnimation() override;				//アニメーション切り替え。
	void MakePoison();    

	//状態ごとの処理。
	void ProcessIdleStateTransition() override;
	void ProcessPoisonAttackStateTransition();
	void ProcessDamageStateTransition();
	void ProcessExplodeStateTransition();
	void ProcessHondenStateTransition();
	void ProcessChaseStateTransition() override;
	void ProcessCommonStateTransition() override;
	void ProcessDownStateTransition() override;

	//アニメーションイベントを処理。
	void OneAnimationEvent(const wchar_t* clipName, const wchar_t* eventName) override;
	//描画処理。
	void Render(RenderContext& rc);
public:
	//座標をセットする関数。
	void SetPosition(const Vector3& position)
	{
		m_position = position;
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

	//HPをセットする関数。
	void SetHP(const int& hp)
	{
		m_enemyHP = hp;
	}

	//死亡しているか判定する関数。
    bool IsDead() const 
	{
		return m_isDeadFlag; 
	}

	//HPを取得する関数。
	int GetHP()const
	{
		return	m_enemyHP;
	}

	//最大HPを取得する関数。
	int GetMaxHP()const
	{
		return m_enemyMaxHP;
	}

	EnemyUI*        m_enemyUI = nullptr;						//敵のUIへの参照。
private:
	//メンバ変数。
	Vector3			m_scale = { 0.7f,0.7f,0.7f };//大きさ。
	GameCamera*		m_gameCamera = nullptr;                     //ゲームカメラへの参照。
	Game*			m_game = nullptr;							//ゲームへの参照。
	RingBell*		m_ringBell = nullptr;                       //本殿への参照。
	
	EffectEmitter*  m_effectEmitter = nullptr;					//effectへの参照。
	EnEnemyState	m_enemyState = enEnemyState_Idle;			//現在の状態。
	int				m_ExplosionBoneId = -2;						//攻撃判定を出すボーンID
	int				m_enemyHP = 5;								//HP
	const int		m_enemyMaxHP = m_enemyHP;					//最大体力。
	const Vector3	m_stopMove = Vector3::Zero;					//移動を停止するためのベクトル。

	//各種タイマー。
	float		m_idleTimer = 0.0f;					//待機タイマー。
	float		m_chaseTimer = 0.0f;				//追跡タイマー。
	float		m_stopTimer = 0.0f;					//拘束タイマー。
	float		m_explosionTimer = 0.0f;			//爆発タイマー。
	float		m_mainTimer = 0.0f;					//本殿へ行くタイマー。
	float		m_explodeTimer = 0.0f;				//爆発してから消滅までの猶予タイマー
	float		m_deathEffectTimer = 0.0f;			//死亡エフェクトの表示時間
	
	//フラグ。
	bool		m_isUnderAttack = false;			//ダメージを受けているかどうか。
	bool		m_isStopped = false;				//動きを止められているか。
	bool		m_isGameOverFlag = false;			//ゲームオーバー呼び出し用フラグ。
    bool		m_hasExploded = false;				//爆発処理を一度だけ行うためのフラグ
	public:
	bool		m_isDeadFlag = false;				//死亡フラグ。
	bool m_isDead = false;
	bool m_isDeleted = false; // メンバ追加
};

