#pragma once
#include"Game.h"
class UItukuyomi:public IGameObject
{
 public:
	UItukuyomi();

	~UItukuyomi();

	bool Start();

	void Update();

	void Render(RenderContext& rc);

	Player* m_player = nullptr;

	SpriteRender m_RunaFrame;
	SpriteRender m_RunaSprite;
	SpriteRender m_RunaSprite2;

	float m_RunaTimer = 0.0f;
};

