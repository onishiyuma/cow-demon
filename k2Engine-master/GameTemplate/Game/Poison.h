#pragma once
#include "graphics/effect/EffectEmitter.h"
	class LittleEnemy;
	class Player;


	class Poison :public IGameObject
	{
	public:
		enum EnEnemy
		{
			enPoison_None,
			enPoison_LittleEnemy,
			enPoison_BossEnemy
		};
		Poison();
		~Poison();
		bool Start();
		void Update();
		void CreatEffect();

		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}

		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		const Vector3& GetPosition()const
		{
			return m_position;
		}

		void SetEnEnemy(const EnEnemy enenemy)
		{
			m_enEnemy = enenemy;
		}
	private:
		//メンバ変数
		Player* m_player;
		LittleEnemy* m_littleenemy;
		CollisionObject* m_collisionObj;
		EffectEmitter* m_effectEmitter;
		Vector3 m_position;
		Quaternion m_rotation;
		Vector3 m_moveSpeed;
		Vector3 m_scale = Vector3::One;
		EnEnemy m_enEnemy = enPoison_None;
		float m_timer = 0.0f;
	};



