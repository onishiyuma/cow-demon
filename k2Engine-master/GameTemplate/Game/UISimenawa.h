#pragma once
#include "Game.h";
class UISimenawa :public IGameObject
{
public:
	UISimenawa();

	~UISimenawa();

	bool Start();

	void Update();

	void Render(RenderContext& rc);

	Player* m_player; 
	SpriteRender m_ropeSprite;
	SpriteRender m_ropeGage;
	float m_ropeTimer = 0.0f;

};

