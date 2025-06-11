#pragma once
#include "sound/SoundSource.h"

class Game;

class GameOver:public IGameObject
{
public:
	GameOver();
	~GameOver();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	SpriteRender	m_spriteRender;				//スプライトレンダー。
	SoundSource*	m_gameOverBGM;				//サウンドソース。
	Game*			m_game;						//ゲーム。
	float 			m_titleTime=0.0f;			//タイトルに戻るまでの時間。
	const float 	m_maxTitleTIme=2.0f;		//タイトルに戻るまでの最大時間。
};