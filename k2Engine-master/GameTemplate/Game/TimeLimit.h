#pragma once

class Game;

class TimeLimit:public IGameObject
{
public:
	//メンバ関数。
	TimeLimit();
	~TimeLimit();
	bool Start();
	void Update();
	void Flash();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	FontRender		m_fontRender;								//フォントレンダー。
	Game*			m_game;										//ゲーム。
	Vector3			m_firstPosition;							//初期座標。
	Vector3			m_position = { -400.0f,350.0f,0.0f };		//座標。
	Vector4			m_color = { 0.0f,0.0f,0.0f,0.0f };			//色。
	Vector3			m_scale = { 1.0f,1.0f,1.0f };				//大きさ。
	const float		m_maxTimer = 2.0f;							//タイマーの最大時間。
	float			m_timerCount = 0.0f;						//タイマーのカウント。
	float			m_timer = 2.0f;								//タイマーの時間。
	bool			m_isflash = false;							//フラッシュしているか。
};

