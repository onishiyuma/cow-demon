#pragma once

class Player;
class GameCamera;

//遠距離攻撃のお祓いクラス。
class Purification:public IGameObject
{
public:
	Purification();
	~Purification();
	void Update();
	bool Start();
	//コリジョンの作成。
	void CreateCollision();
	//カメラのベクトル。
	void CameraVector();
	void Render(RenderContext& rc);

	//座標をセット。
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	//移動速度。
	void SetVelocity(const Vector3& velocity)
	{
		m_velocity = velocity;
	}

	//座標を取得。
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	//回転をセット。
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	//メンバ変数。
	GameCamera* m_gameCamera;//カメラ。
	CollisionObject* m_collisionObj;//コリジョンオブジェクト
	ModelRender* m_modelRender;//モデルレンダー。
	Vector3 m_toCameraPos;//注視点から視点に向かうベクトル。
	Vector3 m_velocity;//速度。
	Vector3 m_player;//プレイヤー。
	Vector3 m_position;//座標。
	Vector3 m_direction;//移動方向
	Vector3 m_moveSpeed;//移動速度。
	Vector3 m_scale = Vector3::One;//大きさ。(等倍)
	Quaternion m_rotation;//回転。
	float m_purificationSpeed = 2000.0f;//お祓いの移動速度
	const int Damage = 1;
	float m_timer = 0.0f;
};