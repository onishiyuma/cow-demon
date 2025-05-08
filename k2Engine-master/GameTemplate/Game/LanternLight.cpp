#include "stdafx.h"
#include "LanternLight.h"
#include "Lantern.h"

LanternLight::LanternLight()
{

}

LanternLight::~LanternLight()
{

}

bool LanternLight::Start()
{
	m_lantern = FindGO<Lantern>("lantern1");
	m_lantern = FindGO<Lantern>("lantern2");
	m_lantern = FindGO<Lantern>("lantern3");
	m_lantern = FindGO<Lantern>("lantern4");

	m_pointLight.Init();
	m_pointLight.SetPosition(m_lantern->m_position);
	m_pointLight.SetColor(Vector3(0.0f, 1.0f, 1.0f));
	m_pointLight.SetAffectPowParam(0.5f);
	m_pointLight.SetRange(1000.0f);

	return true;
}

void LanternLight::Update()
{
	Vector3 pointLightPosition = m_lantern->m_position;
	pointLightPosition.y += 50.0f;
	m_pointLight.SetPosition(pointLightPosition);
	//ポイントライトを更新
	m_pointLight.Update();
}

void LanternLight::Render(RenderContext& rc)
{

}
