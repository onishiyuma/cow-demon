#include "stdafx.h"
#include "LanternLight.h"
#include "Lantern.h"

namespace
{
	const Vector3 POINTRIGHT_COLOR = {5.0f, 50.0f, 50.0f};
	const float POINTRIGHT_RANGE = 150.0f;
	const float POINTRIGHT_AFFECT_POW = 2.0f;
}

bool LanternLight::Start()
{
	//各種インスタンスアドレスを検索する。
	m_lantern = FindGO<Lantern>("lantern1");
	m_lantern = FindGO<Lantern>("lantern2");
	m_lantern = FindGO<Lantern>("lantern3");
	m_lantern = FindGO<Lantern>("lantern4");

	//ポイントライトの初期化。
	m_pointLight.Init();
	m_volumePointLight.Init(m_pointLight);
	//ポイントライトの色を設定。
	m_pointLight.SetColor(POINTRIGHT_COLOR * 0.0003f);
	//ポイントライトの範囲を設定。
	m_pointLight.SetRange(POINTRIGHT_RANGE);
	//ポイントライトの影響力を設定。
	m_pointLight.SetAffectPowParam(POINTRIGHT_AFFECT_POW);

	return true;
}

LanternLight::LanternLight()
{

}

LanternLight::~LanternLight()
{

}

void LanternLight::Update()
{
	//ポイントライトの座標を設定。
	m_pointLight.SetPosition(m_firstPosition);
	//ポイントライトの更新。
	m_pointLight.Update();
	m_volumePointLight.Update();
}

void LanternLight::Render(RenderContext& rc)
{

}
