#pragma once
class UIZero:public IGameObject
{
public:
	//メンバ関数。
	UIZero();
	~UIZero();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	//メンバ変数。
	SpriteRender		m_spriteRender;								//スプライトレンダー。
	const Vector3		m_scaleStart = { 1.0f, 1.0f, 1.0f };		//スケールの開始値。
	const Vector3		m_scaleEnd = { 10.0f, 10.0f, 10.0f };		//スケールの終了値。
	const Vector3		m_firstPosition = { 0.0f, 200.0f, 0.0f };	//初期座標。
	Vector4				m_color = { 1.0f, 1.0f, 1.0f, 0.8f };		//色。
	Vector3				m_position;									//座標。
	const float			m_maxTime = 1.0f;							//最大時間。
	float				m_timer = 0.0f;								//タイマー。
	bool				m_isMove = false;							//動いているか。
};

