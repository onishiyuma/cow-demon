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
	m_pointLight.SetColor(Vector3(0.35f, 0.5f, 0.5f));
	m_pointLight.SetRange(500.0f);
	m_pointLight.SetAffectPowParam(1.0f);

	

	return true;
}

void LanternLight::Update()
{
	m_pointLight.SetPosition(m_firstPosition);
	m_pointLight.Update();
}

void LanternLight::Render(RenderContext& rc)
{

}
