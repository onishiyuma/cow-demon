#pragma once
#include "Game.h";
class UIcurseBar :public IGameObject
{
public:
	UIcurseBar();

	~UIcurseBar();

	bool Start();

	void Update();

	void Render(RenderContext& rc);

	Player* m_player ;

	SpriteRender m_curseFrame;

	SpriteRender m_curseSprit;

};

