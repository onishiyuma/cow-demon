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

private:
	//メンバ変数。
	Game*				m_game;						//ゲーム。
	SpriteRender		m_spriteRender;				//スプライトレンダー。
	float 				m_titleTime=0.0f;			//タイトルに戻るまでの時間。
	const float 		m_maxTitleTIme=2.0f;		//タイトルに戻るまでの最大時間。
};

