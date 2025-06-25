#pragma once

class Game;

class LanternArrow:public IGameObject
{
public:
	//矢印の移動管理。
	enum MoveState
	{
		enMoveState_UP,
		enMoveState_Down
	};

public:
	//メンバ関数
	LanternArrow();
	~LanternArrow();
	bool Start();
	void Update();
	void Move();
	void Rotation();
	void Render(RenderContext& rc);

	//メンバ変数
	float m_timer = 0.0f; //タイマー	
	float m_moveTimer = 1.0f;
	MoveState m_moveState = enMoveState_UP;
	const Vector3 m_scale = { 0.7f,0.7f,0.7f }; //スケール
	Vector3 m_firstPosition; //初期位置
	Vector3 m_position; //現在位置
	Vector3 m_movePosition; //移動位置
	Quaternion m_rotation; //回転
	ModelRender m_modelRender; //モデルレンダラー
	ModelInitData m_initData;

	Game* m_game = nullptr; //ゲームオブジェクトへのポインタ
};

