#pragma once
#include "graphics/effect/EffectEmitter.h"
	class LittleEnemy;
	class BossEnemy;
	class Player;


	class Poison :public IGameObject
	{
	public:
		//敵の型の列挙型。
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
		void CreateEffect();

		//座標を設定。
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}

		//回転を設定。
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		//ステータスを設定。
		void SetEnEnemy(const EnEnemy enEnemy)
		{
			m_enEnemy = enEnemy;
		}

		//座標を取得。
		const Vector3& GetPosition()const
		{
			return m_position;
		}

		//メンバ変数。
		bool				m_isDelete = false;				//削除フラグ。
	private:
		Player*				m_player;						//プレイヤー。
		LittleEnemy*		m_littleEnemy;					//小さい敵。
		BossEnemy*          m_bossEnemy;					//ボス敵。
		CollisionObject*	m_collisionObj;					//コリジョンオブジェクト。
		EffectEmitter*		m_effectEmitter;				//エフェクトエミッター。
		Vector3				m_position;						//座標。
		Quaternion			m_rotation;						//回転。
		Vector3				m_moveSpeed;					//移動速度。
		Vector3				m_scale = Vector3::One;			//大きさ。
		EnEnemy				m_enEnemy = enPoison_None;		//敵の型。
		float				m_timer = 0.0f;					//時間。
	};



