#pragma once


class RingBell:public IGameObject
{
public:
	//メンバ関数。
	RingBell();
	~RingBell();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//コリジョンの作成。
	void CreateCollision();

	//座標を取得。
	const Vector3& GetPosition()const
	{
		return m_position;
	}

private:
	//メンバ変数。
	PhysicsStaticObject			m_physicsStaticObject;								//判定。
	CollisionObject*			m_collisionObject;									//コリジョンオブジェクト。
	ModelRender					m_modelRender;										//モデルレンダー。
	Vector3						m_position = Vector3{ 70.0f, 90.0f, -1345.0f };		//座標。
	Vector3						m_collisionScale = Vector3{ 240.0f,50.0f,200.0f };	//コリジョンの大きさ。
};