#pragma once

class Player;

class Shimenawa :public IGameObject
{
public:
	//メンバ関数。
	Shimenawa();
	~Shimenawa();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//コリジョンの作成。
	void CreateCollision();

	//削除時間。
	void DurationTime();

	//設置する関数。
	void Put();

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

private:
	//メンバ変数。
	CollisionObject*		m_collisionObject;				//コリジョンオブジェクト。
	Shimenawa*				m_shimenawa;					//しめ縄。
	Player*					m_player;						//プレイヤー。
	ModelRender				m_modelRender;					//モデルレンダー。
	Vector3					m_position;						//座標。
	Vector3					m_placePosition;				//設置座標。
	const float				m_duration = 5.0f;				//継続時間。
	float					m_durationTimer = 0.0f;			//削除までの時間。
};