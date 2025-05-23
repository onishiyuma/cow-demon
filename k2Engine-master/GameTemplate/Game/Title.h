#pragma once

class Game;
class Fade;

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
	FontRender		m_fontRender;		//フォントレンダー。
	SpriteRender	m_spriteRender;		//スプライトレンダー。
	Game*			m_game;				//ゲーム。
	Fade*			m_fade;				//フェード。
	float			m_timer;			//タイマー。
};

