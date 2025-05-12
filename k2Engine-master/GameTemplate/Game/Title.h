#pragma once

class Game;
class Fade;

//タイトルクラス。
class Title:public IGameObject
{
public:
	Title();
	~Title();
	//メンバ関数。
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	FontRender m_fontRender;
	SpriteRender m_spriteRender;//スプライトレンダー。
	Game* m_game;//ゲーム。
	Fade* m_fade;//フェード。

	float m_timer;

};

