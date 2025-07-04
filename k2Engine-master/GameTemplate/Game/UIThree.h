#pragma once

class UIThree : public IGameObject
{
public:
	//メンバ関数。
	UIThree();
	~UIThree();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	//メンバ変数。
	bool						m_isMove = false;							//移動中か。
private:
	SpriteRender				m_spriteRender;								//スプライトレンダー。
	const Vector3				m_scaleStart = { 1.0f, 1.0f, 1.0f };		//スケールの開始値。
	const Vector3				m_scaleEnd = { 5.0f, 5.0f, 5.0f };			//スケールの終了値。
	const Vector3				m_firstPosition = { 0.0f, 200.0f, 0.0f };	//初期座標。
	const Vector4				m_color = { 1.0f, 1.0f, 1.0f, 0.8f };		//色。
	Vector3						m_position;									//座標。
	float						m_timer = 0.0f;								//タイマー。
};

