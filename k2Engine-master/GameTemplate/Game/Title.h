#pragma once

class Game;
class Load;

//タイトルクラス。
class Title:public IGameObject
{
public:
	//メンバ関数。
	Title();
	~Title();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	FontRender		m_fontRender;				//フォントレンダー。
	SpriteRender	m_spriteRender;				//スプライトレンダー。
	Game*			m_game;						//ゲーム。
	Load*			m_load;						//フェード。
	float			m_timer;					//タイマー。
	float 			m_titleTime = 0.0f;			//タイトルに戻るまでの時間。
	const float 	m_maxTitleTIme = 2.0f;		//タイトルに戻るまでの最大時間。
};

