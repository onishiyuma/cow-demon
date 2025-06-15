#pragma once

class Tutorial;

class SpriteClear:public IGameObject
{
public:
	//メンバ関数
	SpriteClear();
	~SpriteClear();
	bool Start();
	void Update();
	void Fade();
	void Render(RenderContext& rc);

	//メンバ変数
	int m_timer = 0.0f;
	int m_fadeTimer = 2.0f;
	int m_fadeMaxTimer = 2.0f;

	bool m_isFadeOut = false;

	Vector3 m_position = { 0.0f,50.0f,0.0f };
	Vector3 m_scale;
	Vector4 m_color = { 1.0f,1.0f,1.0f,1.0f };
	SpriteRender m_spriteRender;

	Tutorial* m_tutorial;
};

