#pragma once
#include "Game.h";
#include "Player.h"


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
 SpriteRender m_skillGageSprite;
 FontRender m_fontRender;
 int m_skillGage = 0.0f;//スキルゲージ。
 int m_skillMax=0.0f;//スキルがマックスになったら。
};

