#pragma once

class SpriteClear:public IGameObject
{
public:
	//メンバ関数。
	SpriteClear();
	~SpriteClear();
	bool Start();
	void Update();
	void Fade();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	SpriteRender	m_spriteRender;//スプライトレンダー。
	Vector3			m_position = { 0.0f,50.0f,0.0f };//座標。
	Vector3			m_scale=Vector3::One;//大きさ。
	Vector4			m_color = { 1.0f,1.0f,1.0f,1.0f };//色。（ここでは白色）
	float			m_timer = 0.0f;//タイマー。
	float			m_fadeTimer = 2.0f;//フェードタイマー。
	const float		m_fadeMaxTimer = 2.0f;//フェードタイマーの上限。
	bool			m_isFadeOut = false;
};

