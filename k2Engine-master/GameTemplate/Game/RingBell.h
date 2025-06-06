#pragma once

class Player;

class RingBell:public IGameObject
{
public:
	//矢印の移動管理。
	enum MoveState
	{
		enMoveState_UP,
		enMoveState_Down
	};

public:
	//メンバ関数。
	RingBell();
	~RingBell();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//コリジョンの作成。
	void CreateCollision();
	void MoveArrow();

	//座標を取得。
	const Vector3& GetPosition()const
	{
		return m_position;
	}

private:
	//メンバ変数。
	PhysicsStaticObject			m_physicsStaticObject;								//判定。
	CollisionObject*			m_collisionObject;									//コリジョンオブジェクト。
	Player*						m_player;											//プレイヤー。
	ModelRender					m_modelRender;										//モデルレンダー。
	ModelRender					m_arrowModel;										//矢印のオブジェクト。
	Quaternion					m_rotation;											//回転。
	MoveState					m_moveState=enMoveState_UP;							//矢印の移動ステータス。
	Vector3						m_position = { 70.0f, 90.0f, -1345.0f };			//座標。
	Vector3						m_currentPosition;									//現在の座標。
	Vector3						m_arrwPosition = { 70.0f, 200.0f, -1265.0f };		//矢印の座標。
	Vector3						m_collisionScale = { 240.0f,50.0f,200.0f };			//コリジョンの大きさ。
};