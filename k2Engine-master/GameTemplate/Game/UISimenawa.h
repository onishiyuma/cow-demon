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
	FontRender m_fontRender;
	float m_ropeTimer = 0.0f;
	float m_countDownTimer = 15.0;
	float m_CountDownTime = 1.0f;
	int m_displayTime =0;

	bool m_ResetFrag = false;
	float m_waitTimer = 0.1f;
};

