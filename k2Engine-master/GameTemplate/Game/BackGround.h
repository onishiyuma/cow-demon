#pragma once

class GameManagement;

class BackGround : public IGameObject
{
public:
	//メンバ関数。
	BackGround();
	~BackGround();
	void Update();
	bool Start();
	void Render(RenderContext& rc);
	//コリジョンの作成。
	void CreateCollision();

	GameManagement* m_gameManagement;

private:
	//メンバ変数。
	ModelRender				m_modelRender;				//モデルレンダー。
	ModelRender             m_tutorialStage;            //チュートリアル用ステージ
	PhysicsStaticObject		m_physicsStaticObject;		//静的物理オブジェクト。
	CollisionObject*		m_collisionObject;			//コリジョンオブジェクト。
	Vector3					m_position = Vector3{ 0.0f, 95.0f, -1325.0f };			//ステージの配置座標。
	Quaternion m_rot;
	const Vector3			m_collisionScale = Vector3{ 400.0f,50.0f,190.0f };		//コリジョンの大きさ。
};