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

	//ƒƒ“ƒo•Ï”B
	SpriteRender m_spriteRender;
	Game* m_game;
};