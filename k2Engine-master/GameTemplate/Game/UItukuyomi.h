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

	Player* m_player;
	SpriteRender m_runaFrame;
	SpriteRender m_runaSprite;
	SpriteRender m_runaSprite2;
	FontRender m_fontRender;

	float m_fadeTime = 0.0f;//フェードまでの時間。
	float m_elapsedTime = 0.0f;//経過時間。
	float m_alpha = 0.0f;//α値
	float m_runaMax;//月読の加護のマックス。
	bool m_isVisible = false;

	float m_countDownTimer = 40.0;
	float m_CountDownTime = 1.0f;
	int m_displayTime = 0;
	float m_timer=0.0f;
	bool m_ResetFrag = false;
};

