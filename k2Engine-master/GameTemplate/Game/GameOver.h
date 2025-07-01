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
	void SoulFade();
	void FontFade();
	void SpriteFade();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	Vector3         m_soulPos = { 0.0f,350.0f,0.0f };					//魂の位置。
	Vector3         m_backPos;											//背景の位置。
	Vector4         m_color = {0.0f,0.0f,0.0f,0.0f};					//色。
	Vector4         m_soulColor = { 1.0f,1.0f,1.0f,1.0f };				//魂の色。  
	Vector4         m_fontColor = { 0.0f,0.0f,0.0f,0.0f };				//フォントの色。
	SpriteRender    m_backGround;										//背景のスプライトレンダー。
	SpriteRender	m_spriteRender;										//スプライトレンダー。
	SpriteRender    m_soul;												//魂のスプライトレンダー。
	FontRender		m_fontRender;										//フォントレンダー。
	SoundSource*	m_gameOverBGM;										//サウンドソース。
	Game*			m_game;												//ゲーム。
	int             m_count = 0;										//カウント。	
	float 			m_titleTime=0.0f;									//タイトルに戻るまでの時間。
	float           m_soulTime = 5.0f;									//魂の時間。
	float           m_soulMaxTime = 5.0f;								//魂の最大時間。
	float           m_fontTime = 5.0f;									//フォントのフェード時間。
	float           m_fontMaxTime = 5.0f;								//フォントの最大フェード時間。
	float           m_sprTime = 5.0f;									//スプライトのフェード時間。
	float           m_sprMaxTime = 5.0f;								//スプライトの最大フェード時間。
	const float 	m_maxTitleTIme=5.0f;								//タイトルに戻るまでの最大時間。
	bool            m_isSoulFade = false;								//魂のフェードが終わったか。
	bool            m_isSpriteFade = false;								//スプライトのフェードが終わったか。
	bool			m_isFontFade = false;								//フォントのフェードが終わったか。
};