#pragma once
#include "Game.h";
class UISimenaw :public IGameObject
{
public:
	UISimenaw();

	~UISimenaw();

	bool Start();

	void Update();

	void Render(RenderContext& rc);

	Player* m_player = nullptr; 
	SpriteRender m_RopeSprite;
	SpriteRender m_RopeGage;
	float m_RopeTimer = 0.0f;


};

