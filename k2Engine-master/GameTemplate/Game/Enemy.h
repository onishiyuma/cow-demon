#pragma once
	class Player;
	//class Tou;
	class Collision;

	class Enemy : public IGameObject
	{
	public:
		enum EnEnemyState {
			enEnemyState_Idle,
			enEnemyState_Goal,
			enEnemyState_Chase,
			enEnemyState_Attack,
			enEnemyState_Damage,
			enEnemyState_Down
		};
	public:
		Enemy();
		~Enemy();
		bool Start();
		void Update();
		void Rotation();
		void Render(RenderContext& rc);
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


	private:
		//追いかける
		void Chase();
		//プレイヤー発見
		const bool SearchPlayer() const;
		//本殿発見
		const bool SearchGoal()const;
		//ステート管理
		void ManageState();
		//本殿を目指す
		void Goal();
		//コリジョン
		void Collision();
		//攻撃
		void Attack();
		//攻撃用コリジョン
		void MakeAttackCollision();

		void OneAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

		void ProcessCommonStateTransition();

		void ProcessIdleStateTransition();

		void ProcessChaseStateTransition();

		void ProcessAttackStateTransition();

		void ProcessDamageStateTransition();

		void ProcessDownStateTransition();

		void ProcessGoalStateTransition() {};

		void PlayAnimation();

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
		/*Tou* m_tou = nullptr;*/
		ModelRender m_modelRender;
		Vector3 m_position;
		Vector3 m_forward = Vector3::AxisZ;
		Vector3 m_moveSpeed;
		Vector3 m_scale;
		Quaternion m_rotation;
		CharacterController m_charaCon;
		EnEnemyState m_enemyState = enEnemyState_Idle;
		int m_hp = 0;
		float m_chaseTimer = 0.0f;
		float m_idleTimer = 0.0f;
		int m_isUnderAttack = false;
		int m_FangBoneId = -1;
	};

