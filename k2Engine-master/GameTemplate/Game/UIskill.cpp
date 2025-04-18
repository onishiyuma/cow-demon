#include "stdafx.h"
#include "UIskill.h"
#include "Game.h"
#include "Player.h"

namespace 
{
	//スキル
	Vector3 SKILL_FREME_POSITION = Vector3(600.0f, -425.0f, 0.0f);

	//スキルゲージ
	Vector3 SKILL_GAUGE_POSITION = Vector3(600.0f, -485.0f, 0.0f);
	//緑
	Vector4 GREEN = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	//薄い緑
	Vector4 LIGHT_GREEN = Vector4(0.0f, 1.0f, 0.0f, 0.2f);
}

UIskill::UIskill()
{

}

UIskill::~UIskill()
{

}

bool UIskill::Start()
{
	m_player = FindGO<Player>("player");
	//スキルゲージ
	m_SkillGageSprite.Init("Assets/UI/White.DDS", 120, 14);
	m_SkillGageSprite.SetPosition(SKILL_GAUGE_POSITION);
	m_SkillGageSprite.SetPivot(Vector2{ 0.5f,0.0f });

	//スキルスプライト
	m_skillSprite.Init("Assets/UI/skilmax.DDS", 130, 130);
	m_skillSprite.SetPosition(SKILL_FREME_POSITION);
	return true;
}

void UIskill::Update()
{
	m_skillGage = m_player->m_skillCharge;
	m_skillMax = m_player->m_skillMax;

	float wari = (float)m_skillGage / m_skillMax;

	Vector3 scale = { 1.0f,8.7,1.0f };


	if (m_skillGage>=m_skillMax) 
	{
		m_SkillGageSprite.SetScale(scale);
		m_SkillGageSprite.SetMulColor(GREEN);

	}
	else 
	{
		m_SkillGageSprite.SetMulColor(LIGHT_GREEN);
	}

	m_skillSprite.Update();
	m_SkillGageSprite.Update();
}

void UIskill::Render(RenderContext& rc)
{
	if (m_skillGage>0)
	{
		m_SkillGageSprite.Draw(rc);
	}

	m_skillSprite.Draw(rc);

}