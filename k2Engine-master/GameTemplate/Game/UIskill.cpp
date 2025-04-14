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
	//黒
	Vector4 BLACK = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
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
	m_SkillGage.Init("Assets/UI/Red.DDS", 120, 12);
	m_SkillGage.SetPosition(SKILL_GAUGE_POSITION);
	m_SkillGage.SetPivot(Vector2{ 0.5f,0.0f });
	m_SkillGage.SetMulColor(BLACK);

	//スキルスプライト
	m_SkillSprite.Init("Assets/UI/skilmax.DDS", 130, 130);
	m_SkillSprite.SetPosition(SKILL_FREME_POSITION);
	return true;
}

void UIskill::Update()
{
	int newSkillGage = m_player->m_skillCharge;
	float wari = (float)newSkillGage / 11;
	Vector3 scal = { 1.0f,1.0f,1.0f };
	scal.y += wari;

	if (m_player->m_skillCharge <= 100) {
		m_SkillGage.SetScale(scal);
	}
	else {

	}

	m_SkillSprite.Update();
	m_SkillGage.Update();
}

void UIskill::Render(RenderContext& rc)
{
	if (m_player->m_skillCharge > 0)
		m_SkillGage.Draw(rc);

	m_SkillSprite.Draw(rc);

}