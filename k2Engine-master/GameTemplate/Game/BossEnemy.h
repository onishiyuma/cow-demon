#pragma once
#include "graphics/effect/EffectEmitter.h"
#include "EnemyBase.h"
#include "Game.h"

class Poison;
class Collision;
class EnemyBase;
class Player;
class Game;
class GameCamera;
class RingBell;

class BossEnemy: public EnemyBase
{
public:
	//ボスのステートの列挙型。
	enum EnEnemyState {
		enEnemyState_Idle,			//待機中。
		enEnemyState_Honden,        //本殿追跡処理
		enEnemyState_Chase,			//追跡中。
		enEnemyState_Attack,        //攻撃処理
		enEnemyState_Poison,		//毒攻撃中。
		enEnemyState_Damage,		//被ダメ中。
		enEnemyState_Down			//ダウン状態。
	};

	//使用するアニメーションの種類。
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_walk,
		enAnimationClip_Run,
		enAnimationClip_Attack,
		enAnimationClip_Poison,
		enAnimationClip_Damage,
		enAnimationClip_Down,
		enAnimationClip_Num
	};

public:
	//メンバ関数。
	BossEnemy();
	virtual~BossEnemy();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc);

	//ボス専用の処理。
	void Attack();                              //攻撃
	void MakeAttackCollision();                 //攻撃衝突処理
	void PoisonAttack();                        //毒攻撃。
	void ManageState() override;                //状態管理。
	void Chase() override;                      //追跡行動。
	void Collision() override;                  //衝突処理。
	void Rotation() override;                   //当たり判定処理。
	const bool SearchPlayer() const override;   //プレイヤー探索。
	const bool SearchHonden() const;            //本殿を探す。
	void IsHonden();                            //本殿へ行く処理。
	const bool IsCanAttack() const;             //攻撃可能判定。
	void PlayAnimation() override;              //アニメーション再生。
	void MakePoison();                          //毒の生成。
	void DeathEffect();                         //死亡エフェクト生成。                  

	//各ステートの遷移処理。
	void ProcessIdleStateTransition() override;         //待機。
	void ProcessPoisonAttackStateTransition();          //毒攻撃。
	void ProcessDamageStateTransition() override;       //被ダメージ。
	void ProcessAttackStateTransition();                //攻撃
	void ProcessChaseStateTransition() override;        //追跡。
	void ProcessHondenStateTransition();                //本殿
	void OneAnimationEvent(const wchar_t* clipName, const wchar_t* eventName) override; //アニメーションイベント。
	void ProcessCommonStateTransition() override;       //共通処理（状態遷移）。
	void ProcessDownStateTransition() override;         //ダウン。


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

	float GetHP()const
	{
		return	m_enemyHP;
	}

	float GetMaxHP()const
	{
		return m_enemyMaxHP;
	}


private:
	//メンバ変数。
	GameCamera*			m_gameCamera = nullptr;                      //カメラ参照。
	RingBell*           m_ringBell = nullptr;                        //本殿参照
	AnimationClip		m_animationClips[enAnimationClip_Num];		 //アニメーションクリップ。
	EnEnemyState		m_enemyState = enEnemyState_Idle;            //現在のステート。
	EffectEmitter*      m_effectEmitter = nullptr;                   //エフェクト参照。

	const Vector3		m_stopMove = Vector3::Zero;                  //移動できないようにする。
	int m_BossFangBoneID = -3;
    int m_enemyHP = 100;
	int m_enemyMaxHP = m_enemyHP;                               

	//各種タイマー。
	float		m_leaveTimer = 0.0f;           //退散用タイマー。
	float		m_idleTImer = 0.0f;            //待機用タイマー。
	float		m_chaseTimmer = 0.0f;          //追跡用タイマー。
	float		m_poisonAttackCoolDown = 0.0f; //毒攻撃クールタイム。
	float		m_stopTimer = 0.0f;            //拘束時間。
	float       m_hondenTimer = 0.0f;          //本殿追跡用タイマー
	float       m_deathTimer = 0.0f;            //死亡エフェクト用タイマー。

	//各種フラグ。
	int		m_isUnderAttack = false;        //攻撃を受けているか。
	bool		m_isStopped = false;            //動きが止まっているか。
	bool		m_isGameOverFlag = false;       //ゲームオーバーか。
	bool        m_isDeadFlag = false;               //死亡フラグ。     
};

