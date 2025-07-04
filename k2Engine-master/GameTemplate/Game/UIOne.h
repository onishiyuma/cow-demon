#pragma once

class UIOne :public IGameObject
{
public:
	//メンバ関数。
	UIOne();
	~UIOne();
	bool Start();
	void Update();
	void Move();
	void Render(RenderContext& rc);

	//メンバ変数。
	bool m_isMove = false;
private:
	SpriteRender			m_spriteRender;									//スプライトレンダー。
	const Vector3			m_scaleStart = { 1.0f, 1.0f, 1.0f };			//スケールの開始値。
	const Vector3			m_scaleEnd = { 5.0f, 5.0f, 5.0f };				//スケールの終了値。
	const Vector3			m_firstPosition = { 0.0f, 200.0f, 0.0f };		//初期座標。
	const Vector4			m_color = { 1.0f, 1.0f, 1.0f, 0.8f };			//色。
	Vector3					m_position;										//座標。
	float					m_timer = 0.0f;									//タイマー。
};

