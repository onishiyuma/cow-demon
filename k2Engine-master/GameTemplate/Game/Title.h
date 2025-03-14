#pragma once

class Game;

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

	//メンバ変数。
	SpriteRender m_spriteRender;//スプライトレンダー
	Game* m_game;
};

