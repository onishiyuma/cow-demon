#pragma once
class Shimenawa :public IGameObject
{
public:
	Shimenawa();
	~Shimenawa();
	bool Start();
	void Update();
	void Destroy();
	void Render(RenderContext& rc);

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

	Shimenawa(Vector3 pos, float dur);

	//メンバ変数。
	ModelRender m_modelRender;//モデルレンダー。
	bool m_isCollected = false;//取得状態。
	bool m_isPlaced = false;//設置状態。
	//float collectTimer = 0.0f;
	float placeTimer = 0.0f;
	Vector3 m_position;//座標。
	const float collectTimer = 5.0f;//5秒で取得。
	const float placeDuration = 10.0f;//10秒で消える。

};