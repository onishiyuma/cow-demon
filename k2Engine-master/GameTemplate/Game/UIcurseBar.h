#pragma once
#include "Game.h";
class UIcurseBar :public IGameObject
{
public:
	//メンバ関数。
	UIcurseBar();
	~UIcurseBar();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	Player*			m_player ;			//プレイヤー。
	SpriteRender	m_curseFrame;		//フレーム画像。
	SpriteRender	m_curseSprit;		//呪い画像。
};

