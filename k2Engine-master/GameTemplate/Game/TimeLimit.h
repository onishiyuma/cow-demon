#pragma once

class Game;

class TimeLimit:public IGameObject
{
public:
	//メンバ関数
	TimeLimit();
	~TimeLimit();
	bool Start();
	void Update();
	void Flash();
	void Render(RenderContext& rc);

	//メンバ変数
	float m_timerCount = 0.0f;
	float m_timer = 2.0f;
	float m_maxTimer = 2.0f;
	bool m_isflash = false;

	Vector3 m_firstPosition;
	Vector3 m_position = { -400.0f,350.0f,0.0f };
	Vector4 m_color = { 0.0f,0.0f,0.0f,0.0f };
	Vector3 m_scale = { 1.0f,1.0f,1.0f };

	FontRender m_fontRender;
	Game* m_game;
};

