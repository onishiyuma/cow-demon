#pragma once


class Player:public IGameObject
{
public:
	//メンバ関数。
	Player();
	~Player();

	bool Start();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);

	//移動処理。
	void Move();
	//回転処理。
	void Rotation();
	//ステート管理
	const void ManageState();


	//座標を取得する関数。
	const Vector3& GetPosition()const
	{
		return m_position;
	}


	//メンバ変数
	ModelRender m_modelRender;//モデルレンダー。
	CharacterController m_characterController;//キャラコン。
	Quaternion m_rotation;//回転。

	Vector3 m_position = Vector3::Zero;//座標。
	Vector3 m_forward = Vector3::AxisZ;//前方向
	Vector3 m_moveSpeed;//移動速度。

	int m_characonRadius = 0.0f;//キャラコンの半径。
};

