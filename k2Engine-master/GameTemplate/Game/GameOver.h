#pragma once

class Game;

class GameOver:public IGameObject
{
public:
	GameOver();
	~GameOver();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//メンバ変数。
	SpriteRender	m_spriteRender;		//スプライトレンダー。
	Game*			m_game;				//ゲーム。
};