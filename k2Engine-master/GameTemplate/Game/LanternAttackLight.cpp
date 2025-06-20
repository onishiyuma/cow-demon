#include "stdafx.h"
#include "LanternAttackLight.h"
#include "LanternAttack.h"

namespace
{
	Vector3 POINTRIGHT_COLOR = Vector3(0.25f, 0.15f, 0.15f);
	float POINTRIGHT_RANGE = 400.0f;
	float POINTRIGHT_POW_PARAM = 1.0f;
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
	m_pointLight.SetColor(POINTRIGHT_COLOR);
	//ポイントライトの範囲を設定。
	m_pointLight.SetRange(POINTRIGHT_RANGE);
	//ポイントライトの影響力を設定。
	m_pointLight.SetAffectPowParam(POINTRIGHT_POW_PARAM);

	return true;
}

LanternAttackLight::LanternAttackLight()
{

}

LanternAttackLight::~LanternAttackLight()
{

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
