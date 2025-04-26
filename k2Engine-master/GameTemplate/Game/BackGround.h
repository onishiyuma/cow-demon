#pragma once
class BackGround : public IGameObject
{
public:
	//メンバ関数
	BackGround();
	~BackGround();
	void Update();
	bool Start();
	//コリジョンの作成。
	void CreateCollision();
	void Render(RenderContext& rc);

	//メンバ変数
	ModelRender m_modelRender;//モデルレンダー。
	PhysicsStaticObject m_physicsStaticObject;
	CollisionObject*m_collisionObject;//コリジョン
	Vector3 m_position = Vector3{ 0.0f, 95.0f, -1325.0f };//座標。
	const Vector3 m_collisionScale = Vector3{ 400.0f,50.0f,190.0f };//コリジョンの大きさ。
};

