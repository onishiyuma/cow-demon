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

		SpriteRender m_SkillSprite;
		SpriteRender m_SkillGage;

		float m_RunaTimer = 0.0f;
	
};

