#pragma once
#include"Game.h"
class UItukuyomi:public IGameObject
{
 public:
	 //メンバ関数。
	UItukuyomi();
	~UItukuyomi();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	Player*				m_player;					//プレイヤー。
	SpriteRender		m_runaFrame;				//月読の加護のフレーム。
	SpriteRender		m_runaSprite;				//月読の加護の画像。
	SpriteRender		m_runaSpriteMax;			//月読の加護のマックス画像。
	FontRender			m_fontRender;				//フォントレンダー。
	float				m_drawTime = 0.0f;			//表示する時間。
	float				m_elapsedTime = 0.0f;		//経過時間。
	float				m_alpha = 0.0f;				//α値。
	float				m_runaMax;					//月読の加護のマックス。
	float				m_timer = 0.0f;				//タイマー。
	float				m_countDownTimer = 0.0f;	//カウントダウンタイマーの初期値。
	float				m_countDownTime = 0.0f;		//カウントダウンの時間。
	int					m_displayTime = 0;			//表示する時間。
	bool				m_isVisible = false;		//表示するかどうか。
	bool				m_isReset = false;			//リセットできるか。
};

