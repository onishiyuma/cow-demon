#pragma once
#include "EnemyBase.h"
class Player;
class BackGround;
class Collision;
class RingBell;
class EnemyBase;
class Game;

class Enemy : public EnemyBase
{

public:
	enum EnEnemyState {
		enEnemyState_Idle,
		enEnemyState_Honden,
		enEnemyState_Chase,
		enEnemyState_Attack,
		enEnemyState_Damage,
		enEnemyState_Down
	};
public:
	Enemy();
	virtual ~Enemy();
	bool Start()override;
	void Update()override;
	void Rotation()override;
	void Render(RenderContext& rc)override;
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	const Vector3& GetPosition()const
	{
		return m_position;
	}

	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	void SetHP(const int hp)
	{
		m_hp = hp;
	}


//private:
	//追いかける
	void Chase()override;
	//プレイヤー発見
	const bool SearchPlayer() const override;
	//本殿発見
	const bool SearchHonden()const;

	//ステート管理
	void ManageState()override;
	
	//本殿を目指す
	void IsHonden();
	//コリジョン
	void Collision()override;
	//攻撃
	void Attack();
	//攻撃用コリジョン
	void MakeAttackCollision();

	void OneAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	void ProcessCommonStateTransition()override;

	void ProcessIdleStateTransition()override;

	void ProcessChaseStateTransition()override;

	void ProcessAttackStateTransition();

	void ProcessDamageStateTransition()override;

	void ProcessHondenStateTransition();

	void ProcessDownStateTransition()override;

	void PlayAnimation()override;

	const bool IsCanAttack() const;

	//アニメーション
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Attack,
		enAnimationClip_Damage,
		enAnimationClip_Down,
		enAnimationClip_Num
	};
	AnimationClip m_animationClips[enAnimationClip_Num];
	Player* m_player = nullptr;
	RingBell* m_ringBell = nullptr;
	BackGround * m_backGround= nullptr;
	Game* m_game;
	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 m_farstPosition=Vector3::Zero;
	Vector3 m_forward = Vector3::AxisZ;
	Vector3 m_moveSpeed;
	const Vector3 m_stopMove = Vector3::Zero;
	Vector3 m_scale;
	Quaternion m_rotation;
	//CharacterController m_charaCon;
	EnEnemyState m_enemyState = enEnemyState_Idle;
	int m_hp = 0;
	float m_chaseTimer = 0.0f;
	float m_idleTimer = 0.0f;
	int m_isUnderAttack = false;
	int m_FangBoneId = -1;
	float m_stopTimer=0.0f;//拘束時間。
	float m_hondenTimer = 0.0f;
	bool m_isStopped = false;//動きを止めるフラグ。
	bool m_gameoverFlag=false;//ゲームオーバーを呼ぶための変数。
};

