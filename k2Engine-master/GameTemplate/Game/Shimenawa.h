#pragma once

class Player;

class Shimenawa :public IGameObject
{
public:
	Shimenawa();
	~Shimenawa();

	bool Start();
	void Update();
	//コリジョンの作成。
	void CreateCollision();
	//削除時間。
	void DeleteTime();
	//設置する関数。
	void Put();
	void Render(RenderContext& rc);

	//しめ縄リセット用関数。
	void ResetShimenawa()
	{
		m_shimenawa = nullptr;
	}

	//座標をセット。
	void SetPosition(const Vector3& position)
	{
		m_position=position;
	}

	//座標を取得。
	const Vector3& GetPosition()const
	{
		return m_position;
	}


	//メンバ変数。
	CollisionObject* m_collisionObject;//コリジョンオブジェクト。
	Shimenawa* m_shimenawa;//しめ縄。
	Player* m_player;//プレイヤー。
	ModelRender m_modelRender;//モデルレンダー。
	Vector3 m_position;//座標。
	float m_deleteTimer = 0.0f;//削除までの時間。
	const float m_duration=5.0f;//継続時間。
	Vector3 m_placePosition;//設置座標。
};