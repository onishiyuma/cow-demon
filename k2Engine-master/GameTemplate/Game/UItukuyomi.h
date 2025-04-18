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

	float m_fadeTime = 0.0f;//フェードまでの時間。
	float m_elapsedTime = 0.0f;//経過時間。
	float m_alpha = 0.0f;//α値
	float m_runaMax;//月読の加護のマックス。
	bool m_isVisible = false;
};

