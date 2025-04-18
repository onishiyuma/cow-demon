#pragma once
#include "Game.h";
	class UIskill: public IGameObject
{
	 public:
		UIskill();

		~UIskill();

		bool Start();

		void Update();

		void Render(RenderContext& rc);

		Player* m_player = nullptr;

		SpriteRender m_skillSprite;
		SpriteRender m_SkillGageSprite;
		int m_skillGage = 0.0f;//スキルゲージ。
		int m_skillMax=0.0f;//スキルがマックスになったら。

		float m_runaTimer = 0.0f;
	
};

