#pragma once
#include "Game.h";
#include "Player.h";
class UIheal:public IGameObject 
{
public:

	UIheal();

	~UIheal();

	bool Start();

	void Update();

	void Render(RenderContext& rc);

	Player* m_player;

	SpriteRender m_soulSprite1;
	SpriteRender m_soulSprite2;
	SpriteRender m_soulSprite3;

};

