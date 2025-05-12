#include "stdafx.h"
#include "LanternAttackLight.h"
#include "LanternAttack.h"

LanternAttackLight::LanternAttackLight()
{

}

LanternAttackLight::~LanternAttackLight()
{

}

bool LanternAttackLight::Start()
{
	m_lanternAttack = FindGO<LanternAttack>("lanternAttack1");
	m_lanternAttack = FindGO<LanternAttack>("lanternAttack2");
	m_lanternAttack = FindGO<LanternAttack>("lanternAttack3");

	m_pointLight.Init();
	m_pointLight.SetColor(Vector3(0.5f, 0.35f, 0.35f));
	m_pointLight.SetRange(500.0f);
	m_pointLight.SetAffectPowParam(1.0f);

	return true;
}

void LanternAttackLight::Update()
{
	m_pointLight.SetPosition(m_firstPosition);
	m_pointLight.Update();
}

void LanternAttackLight::Render(RenderContext& rc)
{

}
