#pragma once
#include "sound/SoundSource.h"

class Game;
class Load;
class Operation;

//タイトルクラス。
class Title:public IGameObject
{
public:
	//メンバ関数。
	Title();
	~Title();
	bool Start();
	void FadeIn();
	void FontFade();
	void SoulFade();
	void Update();
	void StartGame();
	void ShowOperation();
	void CleanupTitle();
	void Render(RenderContext& rc);
private:
	//メンバ変数。
	FontRender		m_fontRender;				//フォントレンダー。
	FontRender		m_fontDescription;				//フォントレンダー。
	SpriteRender	m_spriteRender;				//スプライトレンダー。
	SpriteRender    m_spriteBack;
	SpriteRender    m_spriteSoul;               //魂をフェードアウトするスプライトレンダー。
	SoundSource*    m_titleBGM;                 //タイトルのBGM。
	Game*			m_game;						//ゲーム。
	Load*			m_load;						//フェード。
	Operation*      m_operation;				//操作。
	Vector3         m_backPos = { 0.0f,0.0f,0.0f};
	Vector4         m_titleColor = { 1.0f,1.0f,1.0f,0.0f };	//色。
	Vector4         m_fontColor = { 0.0f,0.0f,0.0f,0.0f };	//フェード色。
	Vector4         m_fontDescriptionColor = { 0.0f,0.0f,0.0f,0.0f };	//フォントの説明の色。
	Vector4         m_soulColor = { 0.0f,0.0f,0.0f,0.0f };	//魂の色。
	int             m_fontFadeCount = 0;		//フォントフェードのカウント。	
	float			m_timer = 0.0f;					//タイマー。
	float 			m_titleTime = 0.0f;			//タイトルに戻るまでの時間。
	float 			m_soulTime = 5.0f;			//魂の時間。
	const float 	m_maxTitleTime = 5.0f;		//タイトルに戻るまでの最大時間。
	bool            m_isFadeIn = false;		    //フェードイン中かどうか。
	bool            m_isFontFade = false;		//フォントフェード中かどうか。
	bool            m_isSoulFade = false;		//魂フェード中かどうか。
};

