#pragma once

class Player;
class GameCamera;

//御札クラス・
class Amulet:public IGameObject
{
public:
	Amulet();
	~Amulet();
	void Update();
	bool Start();
	//コリジョンの作成。
	void CreateCollision();

	//座標をセットする。
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	//座標を取得する。
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	//移動方向
	void SetVelocity(const Vector3& velocity)
	{
		m_velocity = velocity;
	}

	//回転をセットする。
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}



	//メンバ変数。
	Player* m_player;//プレイヤー。
	GameCamera* m_gameCamera;//カメラ。
	CollisionObject* m_collisionObj;//コリジョンオブジェクト。
	Vector3 m_toCameraPos;//注視点から視点に向かうベクトル。
	Vector3 m_velocity;//速度。
	Vector3 m_position;//座標。
	Vector3 m_direction;//移動方向。
	Vector3 m_moveSpeed;//移動速度。
	Vector3 m_scale = Vector3::One;//大きさ。(等倍)
	Vector3 m_moveVec;//移動するベクトル。
	Quaternion m_rotation;//回転。
	const float m_amuletSpeed= 2000.0f;//御札の移動速度。
	float m_deleteTimer = 0.0f;//削除を管理するタイマー。

};

