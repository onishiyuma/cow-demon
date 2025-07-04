#pragma once
#include "Game.h";
#include "Player.h";

class UIheal:public IGameObject 
{
public:
	//メンバ変数。
	UIheal();
	~UIheal();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//メンバ変数。
	bool			m_isDelete = false;		//削除できるか。
	int				m_useHeal = 0;			//回復回数。
private:
	Player*			m_player;				//プレイヤー。
	SpriteRender	m_soulSprite1;			//魂の画像1。
	SpriteRender	m_soulSprite2;			//魂の画像2。
	SpriteRender	m_soulSprite3;			//魂の画像3。
};

