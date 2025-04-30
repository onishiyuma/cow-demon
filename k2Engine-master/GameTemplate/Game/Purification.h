#pragma once
#include "graphics/effect/EffectEmitter.h"
class Player;
class GameCamera;


//通常攻撃クラス。
class Purification:public IGameObject
{
public:
	Purification();
	~Purification();
	void Update();
	bool Start();
	//コリジョンの作成。
	void CreateCollision();
	//エフェクトの作成。
	void CreateEffect();

	//座標をセット。
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	//座標を取得。
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	//移動方向。
	void SetVelocity(const Vector3& velocity)
	{
		m_velocity = velocity;
	}
	//回転をセット。
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	

	//メンバ変数。
	Player* m_player;//プレイヤー。
	GameCamera* m_gameCamera;//カメラ。
	CollisionObject* m_collisionObj;//コリジョンオブジェクト。
	EffectEmitter* m_effectEmitter;//エフェクト。
	Vector3 m_toCameraPos;//注視点から視点に向かうベクトル。
	Vector3 m_velocity;//速度。
	Vector3 m_position;//座標。
	Vector3 m_direction;//移動方向。
	Vector3 m_moveSpeed;//移動速度。
	Vector3 m_scale = Vector3::One;//大きさ。(等倍)
	Vector3 m_moveVec;//移動するベクトル。
	Quaternion m_rotation;//回転。
	const float m_purificationSpeed = 2000.0f;//お祓いの移動速度。
	float m_deleteTimer = 0.0f;//削除を管理するタイマー。
};