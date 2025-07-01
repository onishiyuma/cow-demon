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
	void FontFade();
	void SpriteFade();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	Game*				m_game;										//ゲーム。
	SpriteRender		m_spriteRender;								//スプライトレンダー。
	SpriteRender        m_background;								//背景スプライトレンダー。
	FontRender			m_fontRender;								//フォントレンダー。
	Vector4             m_spriteColor = { 0.0f,0.0f,0.0f,0.0f };	//スプライトの色。
	Vector4             m_fontColor = { 0.0f,0.0f,0.0f,0.0f };		//フォントの色。
	float 				m_titleTime=0.0f;							//タイトルに戻るまでの時間。
	const float 		m_fadeTime = 5.0f;							//フェード時間。
	const float 		m_fadeMaxTime = 5.0f;						//フェードの最大時間。
	const float 		m_maxTitleTIme=5.0f;						//タイトルに戻るまでの最大時間。
	bool                m_isSpriteFade = false;						//スプライトのフェードが終わったか。
	bool                m_isFontFade = false;						//フォントのフェードが終わったか。
};

