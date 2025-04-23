#pragma once
#include "graphics/effect/EffectEmitter.h"
#include "EnemyBase.h"
#include "Game.h"
class Poison;
class Collision;
class EnemyBase;
class Player;
class Game;

class LittleEnemy :public EnemyBase
{
public:
	enum EnEnemyState {
		enEnemyState_Idle,
		/*	enEnemyState_Goal,*/
		enEnemyState_Chase,
		enEnemyState_Leave,
		enEnemyState_Poison,
		enEnemyState_Damage,
		enEnemyState_Down
	};

	LittleEnemy();
	~LittleEnemy();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
	void SetPosition(const Vector3& position)
	{
		m_position = position;
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
		m_enemyHP = hp;
	}
	void PoisonAttack();
	void ManageState()override;
	void Chase()override;
	void Collision()override;
	void Rotation()override;
	const bool SearchPlayer()const override;
	void Leave();
	const bool IsCanAttack()const;
	const bool IsLeave()const;
	void PlayAnimation()override;
	void MakePoison();
	void ProcessIdleStateTransition()override;
	void ProcessPoisonAttackStateTransition();
	void ProcessDamageStateTransition()override;
	void ProcessLeaveStateTransition();
	void ProcessChaseStateTransition()override;
	void OneAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)override;
	void ProcessCommonStateTransition()override;
	void ProcessDownStateTransition()override;


	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Poison,
		enAnimationClip_Damage,
		enAnimationClip_Down,
		enAnimationClip_Num
	};

	AnimationClip m_animationClips[enAnimationClip_Num];
	EnEnemyState m_enemyState = enEnemyState_Idle;
	float m_leaveTimer = 0.0f;
	float m_idleTimer = 0.0f;
	float m_ChaseTimer = 0.0f;
	float m_poisonAttackCoolDown = 0.0f;
	bool m_isUnderAttack = false;
};


