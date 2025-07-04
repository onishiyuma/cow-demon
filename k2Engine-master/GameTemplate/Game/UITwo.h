#pragma once

class UITwo : public IGameObject
{
public:
	//メンバ関数。
	UITwo();
	~UITwo();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//メンバ変数。
	bool					m_isMove = false;								//移動しているか。
private:
	SpriteRender			m_spriteRender;									//スプライトレンダー。
	const Vector3			m_scaleStart = { 1.0f, 1.0f, 1.0f };			//スケールの開始値。
	const Vector3			m_scaleEnd = { 5.0f, 5.0f, 5.0f };				//スケールの終了値。
	const Vector3			m_firstPosition = { 0.0f, 200.0f, 0.0f };		//最初の位置。
	const Vector4			m_color = { 1.0f, 1.0f, 1.0f, 0.8f };			//色。
	Vector3					m_position;										//現在の位置。
	float					m_timer = 0.0f;									//タイマー。
};

