#pragma once

class Player;
class Enemy;
class Game;

class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//メンバ変数。
	Game* m_game;//ゲーム。
	SpriteRender m_spriteRender;//スプライトレンダー。
	int m_timeLimit;//ゲームの制限時間。
};

