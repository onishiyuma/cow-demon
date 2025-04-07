#pragma once

class Player;

class Shimenawa :public IGameObject
{
public:
	Shimenawa();
	~Shimenawa();

	bool Start();
	void Update();
	void Destroy();
	void Render(RenderContext& rc);

	void Place(Vector3 playerPosition);

	//座標をセット。
	void SetPosition(const Vector3& position)
	{
		m_position;
	}

	//座標を取得。
	const Vector3& GetPosition()const
	{
		return m_position;
	}


	//メンバ変数。
	Player* m_player;//プレイヤー。
	ModelRender m_modelRender;//モデルレンダー。
	Vector3 m_position;//座標。
	bool m_isCollected = false;//取得状態。
	bool m_isPlaced = false;//設置状態。
	float m_collectTimer = 0.0f;//取得タイマー。
	float m_elapsedTime = 0.0f;//経過時間。
	const float m_collectTime = 5.0f;//取得時間。
	const float m_placeDuration = 10.0f;//継続時間。
	float m_timer;

};