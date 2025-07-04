#pragma once
#include "Game.h";
#include "Player.h"


class UIskill: public IGameObject
{
 public:
	 //メンバ関数。
	UIskill();
	~UIskill();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	Player*			m_player = nullptr;		//プレイヤー。
	SpriteRender	m_skillSprite;			//スキルの画像。
	SpriteRender	m_skillGageSprite;		//スキルゲージの画像。
	FontRender		m_fontRender;			//フォントレンダー。
	int				m_skillGage = 0;		//スキルゲージ。
	int				m_skillMax=0;		//スキルがマックスになったら。
};

