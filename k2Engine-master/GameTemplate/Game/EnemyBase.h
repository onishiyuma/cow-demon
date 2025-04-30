#pragma once
class Player;
class Game;


class EnemyBase :public IGameObject
{
public:

	EnemyBase();
	virtual ~EnemyBase();

	bool Start();
	void EnemySpeed();
	/*Vector3 RandPos();*/

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
		m_enemyHP = hp;
	}

	float GetHP()const
	{
		return m_enemyHPMax;
	}

	float GetSpeed()const
	{
		return m_enemySpeed;
	}

	/*virtual void GameSet() = 0;*/
	virtual void Update() = 0;
	virtual void BaseAction();
	virtual void Rotation() = 0;
	virtual void Render(RenderContext& rc) = 0;
	virtual void ManageState() = 0;
	virtual void Chase() = 0;
	virtual const bool SearchPlayer()const = 0;

	/*virtual void MakePoison()=0;*/
	virtual void ProcessCommonStateTransition() = 0;
	virtual void Collision() = 0;
	//virtual void MakeAttackCollision()=0;
	virtual void OneAnimationEvent(const wchar_t* clipName, const wchar_t* eventName) = 0;
	virtual void ProcessIdleStateTransition() = 0;
	/*virtual void ProcessRunStateTransition() = 0;*/
	virtual void ProcessChaseStateTransition() = 0;
	//virtual void ProcessAttackStateTransition()=0;
	virtual void ProcessDamageStateTransition() = 0;
	virtual void ProcessDownStateTransition() = 0;
	//virtual void ProcessGoalStateTransition() =0;
	//virtual void InitEnemyModel() = 0;
	virtual void PlayAnimation() = 0;

protected:
	Game* m_game = nullptr;
	Player* m_player = nullptr;
	ModelRender m_modelRender;
	ModelRender m_modelRender2;
	Vector3 m_position;
	Vector3 m_forward = Vector3::AxisZ;
	Vector3 m_moveSpeed;
	Vector3 m_scale;
	Quaternion m_rotation;
	CharacterController m_charaCon;
	/*EnEnemyState m_enemyState = enEnemyState_Idle;*/
	//派生クラスからいじる変数

	float m_enemyHP = 0;
	float m_enemyHPMax = 0;
	float m_enemySpeed = 0;
	float m_chaseTimer = 0.0f;
	float m_idleTimer = 0.0f;
	int m_isUnderAttack = false;
	int m_FangBoneId = -1;
};

