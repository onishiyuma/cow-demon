#pragma once
#include "graphics/effect/EffectEmitter.h"
#include "EnemyBase.h"
#include "Game.h"

class Poison;
class Collision;
class Player;
class Game;
class GameCamera;

class AnnoyingEnemy : public EnemyBase
{
public:
	//敵の状態を定義する列挙型。
	enum EnEnemyState {
		enEnemyState_Idle,			//待機中。
		/*enenemyState_goal,*/		//ゴール。
		enEnemyState_Chase,			//追跡。
		enEnemyState_Leave,			//退避行動。
		enEnemyState_Poison,		//毒攻撃。
		enEnemyState_Damage,		//ダメージを受けている。
		enEnemyState_Down			//倒されている状態。
	};

	//使用するアニメーションクリップを定義。
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_walk,
		enAnimationClip_Run,
		enAnimationClip_Poison,
		enAnimationClip_Damage,
		enAnimationClip_Down,
		enAnimationClip_Num
	};

public:
	//メンバ関数。
	AnnoyingEnemy();
	~AnnoyingEnemy();
	// 基本処理。
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);

	// 各行動処理。
	void PoisonAttack();                      //毒攻撃のロジック。
	void ManageState() override;              //状態管理。
	void Chase() override;                    //追跡行動。
	void Collision() override;                //衝突処理。
	void Rotation() override;                 //向きの更新処理。
	const bool SearchPlayer() const override; //プレイヤーの探索。
	void Leave();                             //離脱行動。
	const bool IsCanAttack() const;           //攻撃可能かどうかを判定。
	const bool IsLeave() const;               //離脱状態かどうかを判定。
	void PlayAnimation() override;            //アニメーション切り替え。
	void MakePoison();    

	//状態ごとの処理。
	void ProcessIdleStateTransition() override;
	void ProcessPoisonAttackStateTransition();
	void ProcessDamageStateTransition();
	void ProcessLeaveStateTransition();
	void ProcessChaseStateTransition() override;
	void ProcessCommonStateTransition() override;
	void ProcessDownStateTransition() override;

	//アニメーションイベントを処理。
	void OneAnimationEvent(const wchar_t* clipName, const wchar_t* eventName) override;


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



private:
	//メンバ変数。
	GameCamera*		m_gameCamera = nullptr;                     //ゲームカメラへの参照。
	AnimationClip	m_animationClips[enAnimationClip_Num];		//アニメーションクリップ配列。
	EnEnemyState	m_enemyState = enEnemyState_Idle;			//現在の状態。

	const Vector3	m_stopMove = Vector3::Zero;					//移動を停止するためのベクトル。

	//各種タイマー。
	float	m_leaveTimer = 0.0f;              //離脱タイマー。
	float	m_idleTimer = 0.0f;               //待機タイマー。
	float	m_chaseTimer = 0.0f;              //追跡タイマー。
	float	m_poisonAttackCoolDown = 0.0f;    //毒攻撃のクールダウン。
	float	m_stopTimer = 0.0f;               //拘束（動きが止まる）タイマー。

	//フラグ。
	bool	m_isUnderAttack = false;          //ダメージを受けているかどうか。
	bool	m_isStopped = false;              //動きを止められているか。
	bool	m_isGameOverFlag = false;         //ゲームオーバー呼び出し用フラグ。
};

