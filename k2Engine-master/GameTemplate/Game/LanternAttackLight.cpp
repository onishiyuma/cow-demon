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
	//各種インスタンスアドレスを検索する。
	m_lanternAttack = FindGO<LanternAttack>("lanternAttack1");
	m_lanternAttack = FindGO<LanternAttack>("lanternAttack2");
	m_lanternAttack = FindGO<LanternAttack>("lanternAttack3");

	//ポイントライトを初期化。
	m_pointLight.Init();
	//ポイントライトの色を設定。
	m_pointLight.SetColor(Vector3(0.25f, 0.15f, 0.15f));
	//ポイントライトの範囲を設定。
	m_pointLight.SetRange(400.0f);
	//ポイントライトの影響力を設定。
	m_pointLight.SetAffectPowParam(1.0f);

	return true;
}

void LanternAttackLight::Update()
{
	//ポイントライトの座標を設定。
	m_pointLight.SetPosition(m_firstPosition);
	//ポイントライトを更新。
	m_pointLight.Update();
}

void LanternAttackLight::Render(RenderContext& rc)
{

}
